#include "fft.h"
#include <math.h>

/* FFT instance */
static arm_rfft_fast_instance_f32 fft_instance;

/* Buffers */
static float32_t fft_input[FFT_SIZE];
static float32_t fft_output[FFT_SIZE];

/* Janela de Hann. Reduz o vazamento espectral (spectral leakage)*/
static float32_t fft_window[FFT_SIZE];

/* Limites (em numero de bin) de cada banda exibida, espacados
 * logaritmicamente entre o bin 1 (~46.875 Hz) e o bin
 * correspondente a FFT_AUDIO_MAX_FREQ. Calculados uma unica vez
 * em FFT_Init(). */
static uint32_t fft_band_start[FFT_NUM_BARS];
static uint32_t fft_band_end[FFT_NUM_BARS];

/* Resultados */
float32_t fft_peak_frequency = 0.0f;
float32_t fft_peak_magnitude = 0.0f;
uint32_t fft_peak_bin = 0;

/* Espectro completo e barras normalizadas para o display */
float32_t fft_magnitudes[FFT_SIZE / 2];
float32_t fft_bars_norm[FFT_NUM_BARS];

/* -------------------------------------------------------------------------- */
/* Calcula os limites de cada banda (em numero de bin) com                   */
/* espacamento logaritmico, do bin 1 ate o bin correspondente a              */
/* FFT_AUDIO_MAX_FREQ.                                                       */
/*                                                                            */
/* Espacamento log = mais barras nas frequencias graves/medias (onde         */
/* ha mais conteudo musical) e menos nos agudos, ja que cada oitava          */
/* ocupa a mesma largura de tela independente de quantos Hz ela cobre.       */
/* So precisa ser calculado uma vez, na inicializacao.                       */
/* -------------------------------------------------------------------------- */

static void FFT_ComputeBands(void)
{
    uint32_t i;
    uint32_t max_bin;

    float32_t bin_hz = FFT_SAMPLE_RATE / (float32_t)FFT_SIZE;

    float32_t log_min;
    float32_t log_max;
    float32_t step;

    max_bin = (uint32_t)(FFT_AUDIO_MAX_FREQ / bin_hz);

    if (max_bin >= FFT_SIZE / 2)
    {
        max_bin = (FFT_SIZE / 2) - 1;
    }

    log_min = log10f(1.0f);
    log_max = log10f((float32_t)max_bin);
    step = (log_max - log_min) / (float32_t)FFT_NUM_BARS;

    for (i = 0; i < FFT_NUM_BARS; i++)
    {
        float32_t f_start = powf(10.0f, log_min + step * (float32_t)i);
        float32_t f_end = powf(10.0f, log_min + step * (float32_t)(i + 1));

        fft_band_start[i] = (uint32_t)f_start;

        if (fft_band_start[i] < 1)
        {
            fft_band_start[i] = 1;
        }

        fft_band_end[i] = (uint32_t)f_end;

        /*
         * Garante que cada banda tenha pelo menos 1 bin, mesmo nas
         * bandas mais graves onde o passo logaritmico pode arredondar
         * para o mesmo bin de inicio e fim.
         */
        if (fft_band_end[i] <= fft_band_start[i])
        {
            fft_band_end[i] = fft_band_start[i] + 1;
        }
    }

    /*
     * Garante que a ultima banda cubra ate o bin maximo definido por
     * FFT_AUDIO_MAX_FREQ, mesmo com erros de arredondamento acima.
     */
    fft_band_end[FFT_NUM_BARS - 1] = max_bin + 1;
}

/* -------------------------------------------------------------------------- */
/* Inicializa FFT                                                            */
/* -------------------------------------------------------------------------- */

void FFT_Init(void)
{
    arm_status status;
    uint32_t n;

    status = arm_rfft_fast_init_f32(&fft_instance, FFT_SIZE);

    if (status != ARM_MATH_SUCCESS)
    {
        /*
         * Inicializacao FFT falhou
         *
         * Se isso acontecer, para aqui.
         */
        while (1)
        {
            HAL_GPIO_TogglePin(LED_DEBUG_GPIO_Port, LED_DEBUG_Pin);
            HAL_Delay(100);
        }
    }

    /*
     * Pre-calcula a janela de Hann.
     */
    for (n = 0; n < FFT_SIZE; n++)
    {
        fft_window[n] =
            0.5f * (1.0f - arm_cos_f32(2.0f * PI * (float32_t)n / (float32_t)(FFT_SIZE - 1)));
    }

    FFT_ComputeBands();
}

/* -------------------------------------------------------------------------- */
/* Processa FFT                                                                */
/* -------------------------------------------------------------------------- */

void FFT_Process(uint16_t *adc_data)
{
    uint32_t n;
    uint32_t k;
    uint32_t b;

    uint32_t max_bin = 0;
    float32_t max_magnitude = 0.0f;

    float32_t real;
    float32_t imag;
    float32_t magnitude;

    /*
     * Copia as amostras do ADC para o buffer utilizado pela FFT.
     *
     * O ADC e uint16_t, enquanto a FFT trabalha com float32_t.
     */
    for (n = 0; n < FFT_SIZE; n++)
    {
        fft_input[n] = (float32_t)adc_data[n];
    }

    /*
     * Remove o nivel DC.
     */
    float32_t mean = 0.0f;

    for (n = 0; n < FFT_SIZE; n++)
    {
        mean += fft_input[n];
    }

    mean /= FFT_SIZE;

    /*
     * Remove o DC e aplica a janela de Hann na mesma passada.
     */
    for (n = 0; n < FFT_SIZE; n++)
    {
        fft_input[n] = (fft_input[n] - mean) * fft_window[n];
    }

    /*
     * Executa a FFT.
     */
    arm_rfft_fast_f32(
        &fft_instance,
        fft_input,
        fft_output,
        0
    );

    /*
     * Calcula a magnitude de todos os bins de frequencia positiva
     * e, de passagem, encontra o pico.
     */
    for (k = 1; k < FFT_SIZE / 2; k++)
    {
        real = fft_output[2 * k];
        imag = fft_output[2 * k + 1];

        magnitude = sqrtf(
            real * real +
            imag * imag
        );

        fft_magnitudes[k] = magnitude;

        if (magnitude > max_magnitude)
        {
            max_magnitude = magnitude;
            max_bin = k;
        }
    }

    fft_magnitudes[0] = 0.0f; /* bin DC nao e usado no espectro exibido */

    fft_peak_bin = max_bin;

    fft_peak_frequency =
        ((float32_t)max_bin * FFT_SAMPLE_RATE) /
        (float32_t)FFT_SIZE;

    fft_peak_magnitude = max_magnitude;

    /*
     * Agrupa os bins em FFT_NUM_BARS bandas (espacamento log), usando
     * o maior valor de magnitude dentro de cada banda, e converte
     * para altura normalizada (0.0 a 1.0) em escala ABSOLUTA.
     */
    for (b = 0; b < FFT_NUM_BARS; b++)
    {
        float32_t band_max = 0.0f;
        float32_t ratio;
        float32_t db;

        for (k = fft_band_start[b]; k < fft_band_end[b] && k < FFT_SIZE / 2; k++)
        {
            if (fft_magnitudes[k] > band_max)
            {
                band_max = fft_magnitudes[k];
            }
        }

        ratio = band_max / FFT_REF_MAGNITUDE;
        db = 20.0f * log10f(ratio + 1.0e-6f);

        if (db < FFT_DB_FLOOR)
        {
            db = FFT_DB_FLOOR;
        }
        if (db > 0.0f)
        {
            db = 0.0f;
        }

        /* Mapeia [FFT_DB_FLOOR, 0] dB para [0.0, 1.0] */
        fft_bars_norm[b] = (db - FFT_DB_FLOOR) / (0.0f - FFT_DB_FLOOR);
    }
}
