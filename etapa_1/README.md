# Etapa 1

A primeira etapa do projeto foi dedicada à pesquisa, definição do problema e planejamento do desenvolvimento de um equalizador de áudio analógico com visualização do espectro de frequências. O objetivo inicial foi definir uma arquitetura que permitisse receber um sinal de áudio, realizar sua equalização por meio de circuitos analógicos e, paralelamente, analisar o sinal utilizando um microcontrolador. Também foram pesquisadas alternativas de implementação para os circuitos de áudio, para a aquisição do sinal e para a apresentação das informações ao usuário. Durante essa etapa, foram considerados os requisitos de alimentação, processamento do sinal, disponibilidade dos componentes e possibilidade de fabricação do protótipo no laboratório da instituição.

## Desenvolvimento [TODO]

O projeto foi definido a partir da necessidade de desenvolver um sistema capaz de modificar a resposta em frequência de um sinal de áudio de forma analógica. Diferentemente de uma solução totalmente digital, na qual o áudio seria convertido e processado por software, a proposta utiliza circuitos analógicos para realizar a equalização. Essa abordagem permite estudar na prática o funcionamento de filtros, amplificadores operacionais e circuitos de condicionamento de sinais.

A arquitetura planejada para o projeto possui uma entrada de áudio, um estágio de condicionamento do sinal, os estágios responsáveis pela equalização das diferentes faixas de frequência e uma saída de áudio. Além desse caminho principal, parte do sinal será disponibilizada para o sistema digital responsável pela análise espectral. O microcontrolador realizará a aquisição do sinal e utilizará os dados obtidos para calcular seu espectro de frequências, que será apresentado em um display.

Uma das primeiras decisões de projeto foi utilizar uma alimentação simples para o circuito. Como o sinal de áudio é originalmente alternado e o sistema utiliza alimentação positiva única, foi necessário considerar uma referência de tensão para permitir o processamento adequado do sinal pelos amplificadores operacionais. A referência escolhida para o planejamento inicial é aproximadamente metade da tensão de alimentação, permitindo deslocar o sinal para uma região adequada de operação. Ao final do caminho analógico, esse deslocamento poderá ser removido antes da saída de áudio.

Também foi definido que o sistema trabalhará com um sinal estéreo convertido para mono antes da etapa de equalização. Dessa forma, os canais esquerdo e direito poderão ser combinados e processados pelo mesmo conjunto de filtros, simplificando o circuito e reduzindo a quantidade de componentes necessária para o protótipo.

Durante a pesquisa de componentes, foram analisadas diferentes opções de amplificadores operacionais adequados para aplicações de áudio e para a faixa de alimentação pretendida. Também foi considerada a disponibilidade dos componentes em encapsulamentos compatíveis com a fabricação das placas no laboratório. Essa restrição é importante porque o protótipo deverá ser produzido utilizando os recursos disponíveis na instituição, podendo limitar a utilização de componentes encontrados principalmente em encapsulamentos SMD.

Para a parte digital, foi escolhida inicialmente a utilização do microcontrolador STM32F411CEU6. O microcontrolador possui conversor analógico-digital e capacidade de processamento suficiente para realizar a aquisição do sinal e os cálculos necessários para a análise espectral. A visualização deverá ser realizada por meio de um display conectado ao microcontrolador, permitindo apresentar ao usuário uma representação gráfica das componentes de frequência presentes no áudio.

Também foi planejada a utilização do LTspice como ferramenta de apoio ao desenvolvimento. A simulação permite verificar o comportamento dos circuitos analógicos antes da montagem física, possibilitando analisar as respostas dos filtros e identificar problemas de funcionamento ainda durante a fase de desenvolvimento. Além de sinais de teste convencionais, pretende-se utilizar arquivos de áudio como entrada para avaliar o comportamento do circuito com sinais mais próximos da utilização final.

## Testes [TODO]

Nesta etapa, os testes tiveram caráter principalmente exploratório e de validação das alternativas consideradas para o projeto. Foram realizadas pesquisas e simulações preliminares com o objetivo de verificar a viabilidade do processamento analógico do áudio e do uso de uma referência de tensão para circuitos alimentados por fonte simples.

Também foram considerados testes utilizando sinais de áudio reais em simulação. Essa abordagem permite observar o comportamento do circuito diante de sinais complexos, diferentes de ondas senoidais isoladas, e será utilizada como apoio para as etapas seguintes do desenvolvimento.

Os testes definitivos de desempenho, resposta dos filtros, funcionamento da aquisição pelo microcontrolador e visualização do espectro serão realizados nas etapas posteriores, após a definição e montagem dos circuitos.

## Referências (links/datasheets/livros)

* [Analog Devices — Op Amp Applications Handbook](https://www.analog.com/en/resources/technical-books/op-amp-applications-handbook.html)
* [LTspice — Analog Devices](https://www.analog.com/en/resources/design-tools-and-calculators/ltspice-simulator.html)
* [STMicroelectronics — STM32F411](https://www.st.com/en/microcontrollers-microprocessors/stm32f411/documentation.html)

