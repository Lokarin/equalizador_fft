#include "display.h"
#include "st7735.h"
#include <stdio.h>

/*
 * Layout: uma faixa de status compacta no topo (bin/freq/mag),
 * espectro de barras ocupando o restante da altura, usando a
 * largura inteira da tela.
 */
#define STATUS_HEIGHT   14
#define SPECTRUM_Y      STATUS_HEIGHT
#define SPECTRUM_HEIGHT (DISPLAY_HEIGHT - STATUS_HEIGHT)

#define BAR_WIDTH 3
#define BAR_GAP   1
#define BAR_PITCH (BAR_WIDTH + BAR_GAP)  /* 4 px; FFT_NUM_BARS (40) * 4 = 160 px, exato */

/*
 * Altura (em pixels) desenhada de cada barra no quadro anterior.
 * Usada para desenhar so a diferenca entre quadros, em vez de
 * limpar e redesenhar a tela inteira. Reduz bastante o numero de
 * transacoes SPI por quadro.
 */
static uint16_t display_prev_height[FFT_NUM_BARS] = {0};

/* -------------------------------------------------------------------------- */
/* Desenha a faixa de status no topo da tela                                 */
/* -------------------------------------------------------------------------- */

static void Display_DrawStatus(void)
{
    char text[32];

    sprintf(text, "B:%lu F:%.0fHz M:%.0f", fft_peak_bin, fft_peak_frequency, fft_peak_magnitude);

    ST7735_FillRectangle(0, 0, DISPLAY_WIDTH, STATUS_HEIGHT, ST7735_BLACK);
    ST7735_WriteString(2, 2, text, Font_7x10, ST7735_WHITE, ST7735_BLACK);
}

/* -------------------------------------------------------------------------- */
/* Desenha as barras do espectro, redesenhando so o delta de altura          */
/* em relacao ao quadro anterior.                                            */
/* -------------------------------------------------------------------------- */

static void Display_DrawSpectrum(void)
{
    uint32_t b;

    for (b = 0; b < FFT_NUM_BARS; b++)
    {
        uint16_t new_height = (uint16_t)(fft_bars_norm[b] * SPECTRUM_HEIGHT);
        uint16_t old_height = display_prev_height[b];
        uint16_t x = (uint16_t)(b * BAR_PITCH);

        if (new_height > old_height)
        {
            /* Barra cresceu: pinta so o pedaco novo, no topo */
            ST7735_FillRectangle(
                x,
                SPECTRUM_Y + SPECTRUM_HEIGHT - new_height,
                BAR_WIDTH,
                new_height - old_height,
                ST7735_GREEN
            );
        }
        else if (new_height < old_height)
        {
            /* Barra encolheu: apaga so o pedaco que sobrou, no topo */
            ST7735_FillRectangle(
                x,
                SPECTRUM_Y + SPECTRUM_HEIGHT - old_height,
                BAR_WIDTH,
                old_height - new_height,
                ST7735_BLACK
            );
        }

        display_prev_height[b] = new_height;
    }
}

/* -------------------------------------------------------------------------- */
/* Funcoes publicas                                                           */
/* -------------------------------------------------------------------------- */

void Display_Init(void)
{
    ST7735_Init();
    ST7735_FillScreen(ST7735_BLACK);
}

void Display_Update(void)
{
    Display_DrawStatus();
    Display_DrawSpectrum();
}
