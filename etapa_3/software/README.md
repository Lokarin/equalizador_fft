# Software

# Firmware: Analisador de Espectro de Áudio

Firmware em tempo real para STM32F411 (Black Pill) que captura um sinal de áudio, calcula seu espectro de frequências e o exibe em um display TFT ST7735 na forma de um gráfico de 40 barras.

## Funcionamento

1. **Aquisição:** o ADC amostra o sinal de áudio a 48 kHz, com transferência por DMA para um buffer de 1024 amostras.
2. **Processamento:** a FFT (biblioteca CMSIS-DSP) converte o buffer para o domínio da frequência, com resolução de 46,875 Hz por bin. As magnitudes são convertidas para dB em relação a uma referência fixa calibrada.
3. **Visualização:** os bins são agrupados em 40 barras, com mais resolução nas frequências graves, e desenhados no display ST7735 (160x128, paisagem), junto com uma faixa de texto com bin, frequência e magnitude.

## Tecnologias

- STM32F411CEU6 (HAL/CubeMX)
- FreeRTOS
- CMSIS-DSP (FFT)
- Display ST7735 via SPI

## Estrutura

- `main.c`: inicialização, tarefa principal e controle do ADC+DMA
- `fft.c` / `fft.h`: processamento do espectro (FFT, conversão para dB e agrupamento em barras)
- `display.c` / `display.h`: desenho do espectro e da faixa de texto no display ST7735

## Referências

- [1] [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html)
- [2] [FreeRTOS](https://www.freertos.org/)
- [3] [CMSIS-DSP](https://arm-software.github.io/CMSIS-DSP/latest/)
- [4] [ST7735](https://github.com/STMicroelectronics/stm32-st7735)
