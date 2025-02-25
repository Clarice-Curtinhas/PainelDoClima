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
        else if(local[6] == 'V'){
            dadosVix.temp = temp.toFloat();
            dadosVix.umidade = umidade.toFloat();
            dadosVix.qualidade = qualidade.toFloat();
        }
    }
    /*dadosUfes.temp = 25.0;
    dadosUfes.umidade = 50.0;
    dadosUfes.qualidade = 80.0;
    dadosVix.temp = 30.0;
    dadosVix.umidade = 80.0;
    dadosVix.qualidade = 50.0;*/
    atualizaDados();
    
    int i;
    
    for (int i = 0; i < NUMPIXELS; i++){
        defineCor(i, dadoAtual, dadoExt);
        strip1.setPixelColor(i, strip1.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt);
        strip2.setPixelColor(i, strip2.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt);
        strip3.setPixelColor(i, strip3.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt);
        strip4.setPixelColor(i, strip4.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt);
        strip5.setPixelColor(i, strip5.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt);
        strip6.setPixelColor(i, strip6.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt);
        strip7.setPixelColor(i, strip7.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt);
        strip8.setPixelColor(i, strip8.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt);
        strip9.setPixelColor(i, strip9.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt);
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
void defineCor(int i, float dadoAtual, float dadoExt){

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

    else if(fita <= 4) {
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
    else if(fita >= 5 && fita < 10){
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
    /*else if(fita == 5){
            cor[0] = 255;
            cor[1] = 255;
            cor[2] = 255;
    }*/

    fita++;
}

//comentar
void selecionaTemp(){
  opcao = TEMPERATURA;
  dadoAtual = dadosUfes.temp;
  dadoExt = dadosVix.temp;
  Serial.println(opcao);
}

void selecionaUmidade(){
  opcao = UMIDADE;
  dadoAtual = dadosUfes.umidade;
  dadoExt = dadosVix.umidade;
  Serial.println(opcao);
}

void selecionaQualidade(){
  opcao = QUALIDADE;
  dadoAtual = dadosUfes.qualidade;
  dadoExt = dadosVix.qualidade;
  Serial.println(opcao);
}

void atualizaDados(){
    if (opcao == TEMPERATURA){
        dadoAtual = dadosUfes.temp;
        dadoExt = dadosVix.temp;
    }
    else if (opcao == UMIDADE){
        dadoAtual = dadosUfes.umidade;
        dadoExt = dadosVix.umidade;
    }
    else if (opcao == QUALIDADE){
        dadoAtual = dadosUfes.qualidade;
        dadoExt = dadosVix.qualidade;
    }
}