# Etapa 2

A Etapa 2 teve como objetivo consolidar o projeto do equalizador, definindo a arquitetura do circuito analógico, a estrutura do firmware, a interface de áudio do módulo e o esquemático elétrico. Ao final da etapa, foram concluídas as quatro subentregas previstas: o diagrama de blocos do circuito analógico, o projeto do firmware com seus diagramas de blocos e estados, a definição da interface com equipamentos externos e o esquemático analógico completo. A implementação foi organizada de forma a separar as funções de processamento analógico e digital, estabelecendo a estrutura que será utilizada nas etapas posteriores.

## Desenvolvimento

### Circuito analógico

A arquitetura definida para o circuito analógico é apresentada na *Figura 1*. O sinal de entrada é recebido por um conector P2 estéreo e inicialmente convertido para mono pela soma dos dois canais. Em seguida, é adicionado um offset de 2 V, necessário devido à utilização de alimentação simples de 0–5 V. O sinal é então encaminhado para os três caminhos de filtragem, correspondentes às bandas de baixa, média e alta frequência.

<img src="hardware/diagrama_blocos_hardware.jpeg" alt="Diagrama de blocos do circuito analógico" width="600">

*Figura 1 — Diagrama de blocos do circuito analógico.*

As frequências de corte definidas para a implementação atual são 20–318 Hz para a banda baixa, 248–1989 Hz para a banda média e 1768 Hz–20 kHz para a banda alta. A sobreposição entre as bandas foi definida intencionalmente, buscando uma resposta aproximadamente plana quando todas as bandas estiverem configuradas no máximo. Cada caminho possui um ajuste de ganho independente por meio de um potenciômetro analógico. Após a amplificação, os três caminhos são novamente somados. Um capacitor em série na saída remove o offset, permitindo que o sinal retorne a uma referência de 0 V antes de ser disponibilizado no conector P2 de saída.

O circuito utiliza dois circuitos integrados LMC660, totalizando oito amplificadores operacionais. A escolha desse componente considerou sua operação com baixa tensão de alimentação, característica rail-to-rail, baixo ruído de tensão e disponibilidade em encapsulamento DIP, adequado à montagem artesanal da placa. A disponibilidade do componente no mercado brasileiro também foi considerada, uma vez que outras alternativas com características semelhantes apresentavam menor disponibilidade.

A Figura 2 apresenta o esquemático analógico desenvolvido no KiCad. O circuito foi organizado em sete blocos funcionais: alimentação dos amplificadores (Supply), geração da tensão de referência (Reference), conversão estéreo para mono (Stereo → Mono), filtros de alta, média e baixa frequência e o estágio de soma das bandas com remoção do offset (Total Frequencies).

<img src="hardware/esquematico.jpeg" alt="Esquemático analógico completo" width="600">

*Figura 2 — Esquemático completo da seção analógica.*

| Componente     | Quantidade | Função                         |
| -------------- | ---------: | ------------------------------ |
| LMC660         |          2 | Amplificação e filtragem       |
| Potenciômetros |          3 | Ajuste de ganho das bandas     |
| Resistores     |          15| Ganho, polarização e filtragem |
| Capacitores    |          8 | Filtragem e remoção do offset  |
| Conectores P2  |          2 | Entrada e saída de áudio       |
