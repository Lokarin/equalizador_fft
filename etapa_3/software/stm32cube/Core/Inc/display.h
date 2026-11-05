#ifndef DISPLAY_H
#define DISPLAY_H

#include "main.h"
#include "fft.h"

#define DISPLAY_WIDTH  160
#define DISPLAY_HEIGHT 128

/* Inicializa o driver do display e prepara a tela para o primeiro
 * quadro (chamar uma vez, antes do loop da task de display). */
void Display_Init(void);

/* Desenha um quadro completo: faixa de status (bin/freq/mag do
 * pico) + espectro de barras, a partir dos dados que fft.c ja
 * calculou (fft_peak_*, fft_bars_norm[]). */
void Display_Update(void);

#endif /* DISPLAY_H */
