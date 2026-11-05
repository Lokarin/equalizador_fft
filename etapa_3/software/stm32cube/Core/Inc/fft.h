#ifndef FFT_H
#define FFT_H

#include "main.h"
#include "arm_math.h"

/* FFT configuration */
#define FFT_SIZE        1024
#define FFT_SAMPLE_RATE 48000.0f

/*
 * Faixa de audio mostrada no espectro.
 *
 * O limite inferior real de resolucao da FFT e imposto por
 * FFT_SAMPLE_RATE / FFT_SIZE = 46.875 Hz/bin: o bin 0 e DC, entao
 * o menor dado de frequencia disponivel ja e ~46.875 Hz, mesmo que
 * o ouvido humano va ate 20 Hz.
 */
#define FFT_AUDIO_MAX_FREQ 20000.0f

/* Numero de barras exibidas no espectro do display (espacadas em
 * log de frequencia). 40 barras de 3px + 1px de espaco preenchem
 * exatamente os 160px de largura do display em paisagem. */
#define FFT_NUM_BARS 40

#define FFT_REF_MAGNITUDE 523776.0f
#define FFT_DB_FLOOR      -60.0f

/* Funcoes publicas */
void FFT_Init(void);
void FFT_Process(uint16_t *adc_data);

/* Resultado do pico (uso opcional no display) */
extern float32_t fft_peak_frequency;
extern float32_t fft_peak_magnitude;
extern uint32_t fft_peak_bin;

/* Espectro completo (bins positivos, escala linear) */
extern float32_t fft_magnitudes[FFT_SIZE / 2];

/*
 * Barras ja agrupadas (espacamento log em frequencia) e
 * normalizadas para exibicao: valores de 0.0f a 1.0f, prontos
 * para multiplicar pela altura em pixels da area do espectro
 * no display. Escala absoluta: depende de FFT_REF_MAGNITUDE.
 */
extern float32_t fft_bars_norm[FFT_NUM_BARS];

#endif /* FFT_H */
