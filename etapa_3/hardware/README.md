# Hardware

O hardware do projeto consiste em dois módulos principais: um circuito analógico responsável pelo processamento do sinal de áudio e um módulo digital responsável pela aquisição e análise de suas frequências.

O circuito analógico utiliza dois amplificadores operacionais LMC660, totalizando oito amplificadores, alimentados por uma fonte simples de 5 V. O sinal de entrada é recebido por um conector P2 estéreo, convertido para mono e deslocado para uma referência de 2 V (Vref). Em seguida, é dividido entre três filtros ativos, responsáveis pelas bandas de graves (20–318 Hz), médios (248–1989 Hz) e agudos (1768 Hz–20 kHz). Cada banda possui um potenciômetro para ajuste independente de ganho, e os sinais são posteriormente combinados em um estágio somador. Um capacitor de saída remove o offset DC antes de disponibilizar o sinal ao conector P2 de saída.

O módulo digital utiliza uma placa STM32F411CEU6 (Black Pill), responsável pela aquisição do sinal analógico por meio do ADC e pelo processamento das amostras utilizando FFT. Os resultados são apresentados em um display ST7735, conectado ao microcontrolador por meio da interface SPI.

Ambos os módulos operam com alimentação de 5 V e compartilham a mesma referência de terra, permitindo o funcionamento integrado do equalizador e do sistema de análise espectral.

## Referências (links/datasheets/livros)

- [Texas Instruments — LMC660](https://www.ti.com/lit/ds/symlink/lmc660.pdf)
- [STMicroelectronics — STM32F411](https://www.st.com/en/microcontrollers-microprocessors/stm32f411.html)
