#include "constantes.h"                                                                                                                                                                         
#include "globais.h"

void setup(){
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

    // Inicializa botão e indica qual função ele irá chamar
    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);
    pinMode(21, INPUT_PULLUP);
    attachInterrupt(0, selecionaTemp, FALLING);
    attachInterrupt(1, selecionaUmidade, FALLING);
    attachInterrupt(2, selecionaQualidade, FALLING);
}

void loop(){
    if(Serial.available()){
        String local = Serial.readStringUntil('\n');
          if(local[0]=='D'){
            String temp = Serial.readStringUntil('\n');
            String umidade = Serial.readStringUntil('\n');
            String qualidade = Serial.readStringUntil('\n');
            Serial.println(local[6]);
            
            if(local[6] == 'U'){
                Serial.print("teste");
                dadosUfes.temp = temp.toFloat();
                dadosUfes.umidade = umidade.toFloat();
                dadosUfes.qualidade = qualidade.toFloat();
                Serial.println(dadosUfes.temp);
                Serial.println(dadosUfes.umidade);
                Serial.println(dadosUfes.qualidade);
            }
            else if(local[6] == 'S'){
                dadosSPaulo.temp = temp.toFloat();
                dadosSPaulo.umidade = umidade.toFloat();
                dadosSPaulo.qualidade = qualidade.toFloat();
          } else if(local[6] == 'B'){
                dadosBrasilia.temp = temp.toFloat();
                dadosBrasilia.umidade = umidade.toFloat();
                dadosBrasilia.qualidade = qualidade.toFloat();
          }
        }
    }
    /*dadosUfes.temp = 25.0;
    dadosUfes.umidade = 50.0;
    dadosUfes.qualidade = 80.0;
    dadosSPaulo.temp = 15.0;
    dadosSPaulo.umidade = 0.0;
    dadosSPaulo.qualidade = 0.0;
    dadosBrasilia.temp = 40.0;
    dadosBrasilia.qualidade = 100.0;
    dadosBrasilia.umidade = 100.0;*/
    atualizaDados();
    
    int i;
    
    for (int i = 0; i < NUMPIXELS; i++){
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
    
    delay(50); // Aguarda 1 segundo
}

/**
 * @brief função para definir a cor de cada led na matriz de fitas criado
 * 
 * @param i o índice do LED em determinada fita
 * @param dadoAtual aponta para o dado da ufes selecionado pelo botão
 * @param dadoExt aponta para o dado de Vitória selecionado pelo botão
 */
void defineCor(int i, float dadoAtual, float dadoExt, float dadoExt2){

    if (fita == 10){
        if (opcao == TEMPERATURA){
            cor[0] = map(i, 0, 29, 0, 255);
            cor[1] = 0;
            cor[2] = map(i, 0, 29, 255, 0);
        }

        else if (opcao == UMIDADE){
            cor[0] = 0;
            cor[1] = map(i, 0, 29, 0, 255);
            cor[2] = map(i, 0, 29, 255, 0);
        }

        else if (opcao == QUALIDADE){
            cor[0] = map(i, 0, 29, 0, 255);
            cor[1] = map(i, 0, 29, 255, 0);
            cor[2] = 0;
            
        }
    }

    else if(fita < 4) {
        if (opcao == TEMPERATURA){
            cor[0] = map(dadoAtual, TEMPMIN_VIX, TEMPMAX_VIX, 0, 255);
            cor[1] = 0;
            cor[2] = map(dadoAtual, TEMPMIN_VIX, TEMPMAX_VIX, 255, 0);
        }

        else if (opcao == UMIDADE){
            cor[0] = 0;
            cor[1] = map(dadoAtual, UMDMIN, UMDMAX, 0, 255);
            cor[2] = map(dadoAtual, UMDMIN, UMDMAX, 255, 0);
        }

        else if (opcao == QUALIDADE){
            cor[0] = map(dadoAtual, QLDMIN_VIX, QLDMAX_VIX, 0, 255);
            cor[1] = map(dadoAtual, QLDMIN_VIX, QLDMAX_VIX, 255, 0);
            cor[2] = 0;
        }
    } 
    else if(fita >= 4 && fita < 7){
            if (opcao == TEMPERATURA){
            cor[0] = map(dadoExt, TEMPMIN_VIX, TEMPMAX_VIX, 0, 255);
            cor[1] = 0;
            cor[2] = map(dadoExt, TEMPMIN_VIX, TEMPMAX_VIX, 255, 0);
        }

        else if (opcao == UMIDADE){
            cor[0] = 0;
            cor[1] = map(dadoExt, UMDMIN, UMDMAX, 0, 255);
            cor[2] = map(dadoExt, UMDMIN, UMDMAX, 255, 0);
        }

        else if (opcao == QUALIDADE){
            cor[0] = map(dadoExt, QLDMIN_VIX, QLDMAX_VIX, 0, 255);
            cor[1] = map(dadoExt, QLDMIN_VIX, QLDMAX_VIX, 255, 0);
            cor[2] = 0;
        }
    } 
    else if(fita >= 7 && fita < 10){
            if (opcao == TEMPERATURA){
            cor[0] = map(dadoExt2, TEMPMIN_VIX, TEMPMAX_VIX, 0, 255);
            cor[1] = 0;
            cor[2] = map(dadoExt2, TEMPMIN_VIX, TEMPMAX_VIX, 255, 0);
        }

        else if (opcao == UMIDADE){
            cor[0] = 0;
            cor[1] = map(dadoExt2, UMDMIN, UMDMAX, 0, 255);
            cor[2] = map(dadoExt2, UMDMIN, UMDMAX, 255, 0);
        }

        else if (opcao == QUALIDADE){
            cor[0] = map(dadoExt2, QLDMIN_VIX, QLDMAX_VIX, 0, 255);
            cor[1] = map(dadoExt2, QLDMIN_VIX, QLDMAX_VIX, 255, 0);
            cor[2] = 0;
        }
    }

    fita++;
}

//comentar
void selecionaTemp(){
  opcao = TEMPERATURA;
  dadoAtual = dadosUfes.temp;
  dadoExt = dadosSPaulo.temp;
  dadoExt2 = dadosBrasilia.temp;
}

void selecionaUmidade(){
  opcao = UMIDADE;
  dadoAtual = dadosUfes.umidade;
  dadoExt = dadosSPaulo.umidade;
  dadoExt2 = dadosBrasilia.temp;
}

void selecionaQualidade(){
  opcao = QUALIDADE;
  dadoAtual = dadosUfes.qualidade;
  dadoExt = dadosSPaulo.qualidade;
  dadoExt2 = dadosBrasilia.temp;
}

void atualizaDados(){
    if (opcao == TEMPERATURA){
        dadoAtual = dadosUfes.temp;
        dadoExt = dadosSPaulo.temp;
        dadoExt2 = dadosBrasilia.temp;
    }
    else if (opcao == UMIDADE){
        dadoAtual = dadosUfes.umidade;
        dadoExt = dadosSPaulo.umidade;
        dadoExt2 = dadosBrasilia.umidade;
    }
    else if (opcao == QUALIDADE){
        dadoAtual = dadosUfes.qualidade;
        dadoExt = dadosSPaulo.qualidade;
        dadoExt2 = dadosBrasilia.qualidade;
    }
}