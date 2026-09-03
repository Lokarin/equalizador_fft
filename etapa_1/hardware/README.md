# Hardware

## Estudo de viabilidade

Inicialmente, foram realizadas simulações do circuito utilizando o **LTspice** e o **Proteus**, com o objetivo de verificar a viabilidade da proposta e avaliar diferentes possibilidades de implementação. Foram analisadas diferentes topologias de filtros e configurações do circuito de condicionamento do sinal de áudio.

Os resultados obtidos indicaram que o circuito é realizável dentro das restrições estabelecidas para o projeto. A simulação permitiu também avaliar a complexidade crescente do circuito conforme o número de filtros e componentes utilizados, servindo como base para as decisões de arquitetura adotadas nesta etapa.

*IMAGENS (TODO).*

## Número de bandas

A partir dos resultados das simulações, foi definido inicialmente que o equalizador possuirá **três bandas de frequência**. Essa escolha busca estabelecer um equilíbrio entre a capacidade de processamento do sinal e a complexidade do circuito.

A utilização de quatro ou mais bandas aumentaria consideravelmente a quantidade de filtros passa-faixa necessários e, consequentemente, o número de amplificadores operacionais e componentes envolvidos. Além disso, isso aumentaria a complexidade da implementação e dos ajustes do circuito.

Também foi definido que os filtros utilizados serão inicialmente de **primeira ordem**. Embora filtros de ordens superiores permitam obter respostas mais seletivas, sua utilização exigiria uma quantidade maior de amplificadores operacionais e componentes, aumentando a complexidade do hardware. Como o objetivo desta etapa é estabelecer um circuito funcional e viável, optou-se inicialmente pela solução de menor complexidade.

*IMAGENS (TODO).*

## Faixa de frequência

As três bandas foram definidas inicialmente de acordo com a seguinte divisão:

| Banda              | Tipo de filtro | Faixa de frequência |
| ------------------ | -------------- | ------------------- |
| Baixas frequências | Passa-baixa    | Até 200 Hz          |
| Médias frequências | Passa-faixa    | 200 Hz a 2 kHz      |
| Altas frequências  | Passa-alta     | Acima de 2 kHz      |

Essa divisão foi escolhida para possibilitar o controle independente de regiões distintas do espectro audível, mantendo uma arquitetura simples de filtros.

Os valores apresentados são **preliminares** e poderão ser modificados durante a implementação e os testes do circuito. Os ensaios experimentais serão utilizados para verificar o comportamento real dos filtros e, caso necessário, ajustar suas frequências de corte para obter uma resposta mais adequada ao objetivo do projeto.

## Requisitos de interface

A interface de áudio foi definida considerando a utilização do equipamento como um dispositivo externo de processamento de sinal.

O sistema deverá possuir uma **entrada de áudio compatível com fontes externas**, como celulares, computadores e outros dispositivos que forneçam sinal de áudio através de uma conexão AUX. O sinal recebido será processado pelo circuito equalizador.

Após o processamento, o sinal deverá ser disponibilizado em uma **saída AUX**, permitindo sua conexão diretamente a um dispositivo externo que possua seu próprio estágio de amplificação, como caixas de som amplificadas ou outros equipamentos de áudio.

Dessa forma, o sistema deverá apresentar, como requisito básico de interface de áudio:

* Entrada de áudio para conexão de uma fonte externa;
* Processamento do sinal pelas três bandas do equalizador;
* Saída de áudio para conexão a um dispositivo com amplificação própria;
* Compatibilidade com sinais de áudio provenientes de equipamentos de uso comum, como computadores e celulares.

Além da interface de áudio, o sistema contará com uma interface de visualização baseada em display, utilizada pelo microcontrolador para apresentar as informações relacionadas ao funcionamento do equipamento.

## Definição do microcontrolador

O microcontrolador escolhido para o projeto foi o **STM32F411CEU6**, pertencente à família STM32 baseada na arquitetura ARM Cortex-M4.

A escolha foi motivada principalmente pela presença de uma **unidade de ponto flutuante (FPU)** e pelo suporte a instruções de ponto flutuante da arquitetura Cortex-M4, características relevantes para aplicações envolvendo processamento digital de sinais. O microcontrolador também possui recursos e bibliotecas amplamente utilizados em aplicações de processamento de sinais, facilitando o desenvolvimento do firmware necessário para o projeto.

Outro fator considerado foi a disponibilidade e popularidade do STM32F411CEU6, que facilita sua aquisição e o desenvolvimento utilizando ferramentas e documentação já consolidadas.

O microcontrolador também possui interfaces de comunicação adequadas aos periféricos previstos no projeto, destacando-se a **interface SPI**, que será utilizada para comunicação com o display.

Por fim, a escolha está alinhada às atividades desenvolvidas simultaneamente na unidade curricular de **Processamento Digital de Sinais 2**, na qual também está sendo utilizado um microcontrolador baseado em Cortex-M4. Isso permite aproveitar conhecimentos e ferramentas desenvolvidos ao longo do semestre.

## Requisitos de alimentação

Inicialmente, foi definido que o equipamento deverá ser alimentado por uma **fonte externa**, evitando a necessidade de utilizar baterias durante a operação normal do produto.

Entretanto, a definição da fonte de alimentação ainda é considerada preliminar. Conforme acordado com os professores, nesta etapa o foco principal será o desenvolvimento e a validação do restante do circuito. Por isso, os primeiros testes de bancada serão realizados utilizando uma **fonte de bancada**, permitindo maior facilidade para ajustar e monitorar as tensões utilizadas pelo circuito.

A definição da solução definitiva de alimentação, incluindo tensão de operação, reguladores e possíveis requisitos específicos de cada estágio, será refinada conforme o circuito for implementado e testado.
