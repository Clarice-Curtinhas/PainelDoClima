#include "constantes.h"
#include "globais.h"

void setup()
{
    Serial.begin(9600);

    // Inicializa o NeoPixel
    strip1.begin();
    strip2.begin();
    strip3.begin();
    strip4.begin();
    strip5.begin();
    strip6.begin();
    strip7.begin();
    strip8.begin();
    strip9.begin();
    strip10.begin();
    strip11.begin();
    strip12.begin();

    // Garante que todos os LEDs começam apagados
    strip1.show();
    strip2.show();
    strip3.show();
    strip4.show();
    strip5.show();
    strip6.show();
    strip7.show();
    strip8.show();
    strip9.show();
    strip10.show();
    strip11.show();
    strip12.show();

    // Inicializa botão e indica qual função ele irá chamar
    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);
    pinMode(21, INPUT_PULLUP);
    attachInterrupt(0, selecionaUmidade, FALLING);
    attachInterrupt(1, selecionaTemp, FALLING);
    attachInterrupt(2, selecionaQualidade, FALLING);
    
}

void loop()
{
    if (Serial.available())
    {
        String local = Serial.readStringUntil('\n');
        if (local[0] == 'D')
        {
            String temp = Serial.readStringUntil('\n');
            String umidade = Serial.readStringUntil('\n');
            String qualidade = Serial.readStringUntil('\n');
            Serial.println(local[6]);

            if (local[6] == 'U')
            {
                dadosUfes.temp = temp.toFloat();
                dadosUfes.umidade = umidade.toFloat();
                dadosUfes.qualidade = qualidade.toFloat();
                Serial.println(dadosUfes.temp);
                Serial.println(dadosUfes.umidade);
                Serial.println(dadosUfes.qualidade);
            }
            else if (local[6] == 'S')
            {
                dadosSPaulo.temp = temp.toFloat();
                dadosSPaulo.umidade = umidade.toFloat();
                dadosSPaulo.qualidade = qualidade.toFloat();
            }
            else if (local[6] == 'B')
            {
                dadosBrasilia.temp = temp.toFloat();
                dadosBrasilia.umidade = umidade.toFloat();
                dadosBrasilia.qualidade = qualidade.toFloat();
            }
        }
    }
    /*dadosUfes.temp = 25.0;
    dadosUfes.umidade = 50.0;
    dadosUfes.qualidade = 1.0;
    dadosSPaulo.temp = 15.0;
    dadosSPaulo.umidade = 0.0;
    dadosSPaulo.qualidade = 3.0;
    dadosBrasilia.temp = 40.0;
    dadosBrasilia.qualidade = 5.0;
    dadosBrasilia.umidade = 100.0;*/
    atualizaDados();

    int i;

    for (int i = 0; i < NUMPIXELS; i++)
    {
        defineCor(i, dadoAtual, dadoExt, dadoExt2);
        strip1.setPixelColor(i, strip1.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt, dadoExt2);
        strip2.setPixelColor(i, strip2.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt, dadoExt2);
        strip3.setPixelColor(i, strip3.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt, dadoExt2);
        strip4.setPixelColor(i, strip4.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt, dadoExt2);
        strip5.setPixelColor(i, strip5.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt, dadoExt2);
        strip6.setPixelColor(i, strip6.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt, dadoExt2);
        strip7.setPixelColor(i, strip7.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt, dadoExt2);
        strip8.setPixelColor(i, strip8.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt, dadoExt2);
        strip9.setPixelColor(i, strip9.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt, dadoExt2);
        strip10.setPixelColor(i, strip10.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt, dadoExt2);
        strip11.setPixelColor(i, strip11.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt, dadoExt2);
        strip12.setPixelColor(i, strip12.Color(cor[0], cor[1], cor[2]));

        fita = 1;
    }

    strip1.show();
    strip2.show();
    strip3.show();
    strip4.show();
    strip5.show();
    strip6.show();
    strip7.show();
    strip8.show();
    strip9.show();
    strip10.show();
    strip11.show();
    strip12.show();

    delay(50); // Aguarda 1 segundo
}

/**
 * @brief função para definir a cor de cada led na matriz de fitas criado
 *
 * @param i o índice do LED em determinada fita
 * @param dadoAtual aponta para o dado da ufes selecionado pelo botão
 * @param dadoExt aponta para o dado de Vitória selecionado pelo botão
 */
void defineCor(int i, float dadoAtual, float dadoExt, float dadoExt2)
{
    //Fitas dos graidentes
    if (fita >= 10){
        if (fita == 10){
            corQualidadeGradiente(i);
        }

        else if (fita == 11){
            corUmidadeGradiente(i);
        }

        else if (fita == 12){
            corTemperaturaGradiente(i);
        }
    }

    //Fitas com dados da Ufes
    else if (fita < 4){
        if (opcao == TEMPERATURA){
            corTemperatura(dadoAtual);
        }

        else if (opcao == UMIDADE){
            corUmidade(dadoAtual);
        }

        else if (opcao == QUALIDADE){
            corQualidade((int)dadoAtual);
        }
    }

    //Fitas com dados de São Paulo
    else if (fita >= 4 && fita < 7){
        if (opcao == TEMPERATURA){
            corTemperatura(dadoExt);
        }

        else if (opcao == UMIDADE){
            corUmidade(dadoExt);
        }

        else if (opcao == QUALIDADE){
            corQualidade((int)dadoExt);
        }
    }

    //Fitas com dados de Brasília
    else if (fita >= 7 && fita < 10){
        if (opcao == TEMPERATURA){
            corTemperatura(dadoExt2);
        }

        else if (opcao == UMIDADE){
            corUmidade(dadoExt2);
        }

        else if (opcao == QUALIDADE){
            corQualidade((int)dadoExt2);
        }
    }

  fita++;
}

//Define as cores do gradiente de temperatura
void corTemperaturaGradiente(int i){
    switch (i)
    {
    case 0:
        cor[0] = 0;
        cor[1] = 0;
        cor[2] = 255; //Azul escuro
    break;
    
    case  1:
        cor[0] = 0;
        cor[1] = 255;
        cor[2] = 255; //Azul claro
        break;

    case  2:
        cor[0] = 203;
        cor[1] = 252;
        cor[2] = 147; //Verde fraco
        break;

    case  3:
        cor[0] = 242;
        cor[1] = 248;
        cor[2] = 72; //Amarelo
        break;
    
    case 4:
        cor[0] = 255;
        cor[1] = 120;
        cor[2] = 0; //Laranja fraco
        break;

    case 5:
        cor[0] = 255;
        cor[1] = 50;
        cor[2] = 0; //Laranja forte
        break;

    case 6:
        cor[0] = 255;
        cor[1] = 0;
        cor[2] = 0; //Vermelho
        break;

    default:
        break;
    }
}

//Define a cor da fita de temperatura de acordo com a faixa em que se encontra a temperatura recebida
void corTemperatura(float temp){
    if (temp < 20){
        cor[0] = 0;
        cor[1] = 0;
        cor[2] = 255; //Azul escuro
    }

    else if (temp >= 20 && temp < 23){
        cor[0] = 0;
        cor[1] = 255;
        cor[2] = 255; //Azul claro
    }

    else if (temp >= 23 && temp < 26){
        cor[0] = 203;
        cor[1] = 252;
        cor[2] = 147; //Verde fraco
    }

    else if (temp >= 26 && temp < 29){
        cor[0] = 242;
        cor[1] = 248;
        cor[2] = 72; //Amarelo
    }

    else if (temp >= 29 && temp < 32){
        cor[0] = 255;
        cor[1] = 120;
        cor[2] = 0; //Laranja fraco
    }

    else if (temp >= 32 && temp < 35){
        cor[0] = 255;
        cor[1] = 50;
        cor[2] = 0; //Laranja forte
    }

    else if (temp >= 35){
        cor[0] = 255;
        cor[1] = 0;
        cor[2] = 0; //Vermelho
    }
}

//Define a cor da fita de umidade do ar de acordo com a faixa em que se encontra a umidade recebida
void corUmidadeGradiente(int i){
    switch (i)
    {
    case 0:
        cor[0] = 255;
        cor[1] = 0;
        cor[2] = 0; //Vermelho
    break;
    
    case  1:
        cor[0] = 255;
        cor[1] = 120;
        cor[2] = 0; //Laranja fraco
        break;

    case  2:
        cor[0] = 255;
        cor[1] = 255;
        cor[2] = 0; //Amarelo
        break;

    case  3:
        cor[0] = 100;
        cor[1] = 255;
        cor[2] = 0; //Verde
        break;
    
    case 4:
        cor[0] = 0;
        cor[1] = 255;
        cor[2] = 255; //Azul claro
        break;

    case 5:
        cor[0] = 0;
        cor[1] = 0;
        cor[2] = 255; //Azul escuro
        break;

    case 6:
        cor[0] = 255;
        cor[1] = 0;
        cor[2] = 255; //Roxo
        break;

    default:
        break;
    }
}

void corUmidade(float umidade){
    if (umidade < 20){
        cor[0] = 255;
        cor[1] = 0;
        cor[2] = 0; //Vermelho
    }

    else if (umidade >= 20 && umidade < 32){
        cor[0] = 255;
        cor[1] = 120;
        cor[2] = 0; //Laranja fraco
    }

    else if (umidade >= 32 && umidade < 44){
        cor[0] = 255;
        cor[1] = 255;
        cor[2] = 0; //Amarelo
    }

    else if (umidade >= 44 && umidade < 56){
        cor[0] = 100;
        cor[1] = 255;
        cor[2] = 0; //Verde
    }

    else if (umidade >= 56 && umidade < 68){
        cor[0] = 0;
        cor[1] = 255;
        cor[2] = 255; //Azul claro
    }

    else if (umidade >= 68 && umidade < 80){
        cor[0] = 0;
        cor[1] = 0;
        cor[2] = 255; //Azul escuro
    }

    else if (umidade > 80){
        cor[0] = 150;
        cor[1] = 0;
        cor[2] = 255; //Roxo
    }
}

//Define as cores do gradiente de qualidade do ar
void corQualidadeGradiente(int i){
    switch (i)
    {
    case 0:
        cor[0] = 0;
        cor[1] = 0;
        cor[2] = 255; //Azul escuro
    break;
    
    case  1:
        cor[0] = 0;
        cor[1] = 255;
        cor[2] = 0; //Verde
        break;
    
    case 2:
        cor[0] = 255;
        cor[1] = 50;
        cor[2] = 0; //Laranja
        break;

    case 3:
        cor[0] = 255;
        cor[1] = 0;
        cor[2] = 0; //Vermelho
        break;

    case 4:
        cor[0] = 255;
        cor[1] = 0;
        cor[2] = 255; //Roxo
        break;

    default:
        break;
    }
}

//Define a cor da fita de qualidade do ar de acordo com o valor de qualidade recebido
void corQualidade(int qualidade){
    switch (qualidade)
    {
    case 1:
        cor[0] = 0;
        cor[1] = 0;
        cor[2] = 255; //Azul escuro
    break;
    
    case 2:
        cor[0] = 0;
        cor[1] = 255;
        cor[2] = 0; //Verde
        break;
    
    case 3:
        cor[0] = 255;
        cor[1] = 50;
        cor[2] = 0; //Laranja
        break;

    case 4:
        cor[0] = 255;
        cor[1] = 0;
        cor[2] = 0; //Vermelho
        break;

    case 5:
        cor[0] = 255;
        cor[1] = 0;
        cor[2] = 255; //Roxo
        break;

    default:
        break;
    }
}

// comentar
void selecionaTemp()
{
    opcao = TEMPERATURA;
    dadoAtual = dadosUfes.temp;
    dadoExt = dadosSPaulo.temp;
    dadoExt2 = dadosBrasilia.temp;
}

void selecionaUmidade()
{
    opcao = UMIDADE;
    dadoAtual = dadosUfes.umidade;
    dadoExt = dadosSPaulo.umidade;
    dadoExt2 = dadosBrasilia.temp;
}

void selecionaQualidade()
{
    opcao = QUALIDADE;
    dadoAtual = dadosUfes.qualidade;
    dadoExt = dadosSPaulo.qualidade;
    dadoExt2 = dadosBrasilia.temp;
}

void atualizaDados()
{
    if (opcao == TEMPERATURA)
    {
        dadoAtual = dadosUfes.temp;
        dadoExt = dadosSPaulo.temp;
        dadoExt2 = dadosBrasilia.temp;
    }
    else if (opcao == UMIDADE)
    {
        dadoAtual = dadosUfes.umidade;
        dadoExt = dadosSPaulo.umidade;
        dadoExt2 = dadosBrasilia.umidade;
    }
    else if (opcao == QUALIDADE)
    {
        dadoAtual = dadosUfes.qualidade;
        dadoExt = dadosSPaulo.qualidade;
        dadoExt2 = dadosBrasilia.qualidade;
    }
}
