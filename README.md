# Painel do Clima
Repositório do trabalho da disciplina de PIC 1 do curso de Engenharia de Computação da Universidade Federal do Espírito Santo.

## Sumário
* [Sumário](#sumario)
* [Resumo](#resumo)
* [Descrição](#descriçao)
* [Componentes e materiais](#componentes-e-materiais)
* [Alunos](#alunos)

## Resumo
O projeto executado foi um painel informativo das condições climáticas locais usando fitas de Led. 
A ideia é criar um objeto tridimensional para transmitir dados climáticos sobre o ambiente da UFES, as quais serão captadas ao ar livre por um outro dispositivo externo.
Esse dispositivo externo irá se comunicar em tempo real com o interno por meio do Protocolo MQTT.
As informações captadas serão comparadas com dados gerais de Vitória para demonstrar qual é o contraste e o impacto da arborização no ambiente. 
Os dados transmitidos serão temperatura, umidade e qualidade do ar. Além disso, haverá botões para alternar entre as informações.

## Descrição
O projeto seria feito com base em dois parâmetros, informações previamente coletadas sobre os valores adequados de temperatura, qualidade do ar e umidade do ar, e os dados coletados pelo grupo outdoor (que estará fazendo uma trilha pela UFES).
O arduino processará as entradas e irá compará-las com os referenciais, expondo percentualmente quão próximas do ideal elas estão.

Cada informação será exibida de maneira isolada, de forma que o observador deverá apertar um botão para mudar as indicações do gráfico. 
Dessa maneira, criamos um display mais acessível e interessante para quem o está utilizando.

A ideia é criar algo similar ao projeto "Respiramos", instalada na Praça Adolpho Bloch, em São Paulo.

## Componentes e Materiais
* Arduino Mega
* Fita de Led de 5 metros
* ESP
* Botão
* Protoboard
* Bateria de 5 volts
* Suporte para a bateria
* Jumpers

## Resultado
Video mostrando o resultado: [resultado]()

## Alunos
* Ana Luisa Casotti
* Clarice Curtinhas
* Mateus Lizardo
