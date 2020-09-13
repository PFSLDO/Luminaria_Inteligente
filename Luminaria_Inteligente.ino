//Autora: Pamela Fialho
//Data: 06/09/2020
//Função: ativar um lED RGB, conforme a luz ambiental, ou quando o sensor capacitivo é ativado

//Definindo as variáveis
int ldr = A0; //pino analógico do LDR - módulo sensor de luz
int touch = 8; //pino digital do sensor touch
int R = 9; //pino digital do terminal associado a cor vermelha do led RGB
int G = 10; //pino digital do terminal associado a cor verde do led RGB
int B = 11; //pino digital do terminal associado a cor azul do led RGB
int controle = 1; //variável de controle para controlar o loop do LDR

//Definindo as funções
void light(); //define a função do LDR
void choose(); //define a função do sensor touch
void dayCOLD(); //define a função da configuração de luz diurna
void afternoonWHITE(); //define a função da configuração de luz vespertina
void eveningWARM(); //define a função da configuração de luz tardia
void nightHOT(); //define a função da configuração de luz noturna
void lightOFF(); //define a função da configuração de luz apagada

void setup() {
  pinMode(ldr, INPUT); //define o pino do LDR como sensor/entrada
  pinMode(touch, INPUT); //define o pino do sensor como sensor/entrada
  pinMode(R, OUTPUT); //define o pino do terminal associado a cor vermelha do led RGB como saída
  pinMode(G, OUTPUT); //define o pino do terminal associado a cor verde do led RGB como saída
  pinMode(B, OUTPUT); //define o pino do terminal associado a cor azul do led RGB como saída
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(ldr)); //Mostra no monitor serial a leitura analógica do LDR
  light(); //chama a função que verifica se há toque no sensor capacitivo
}

//Função que acende o LED RGB conforme a luz ambiente
void light() {
  if ((analogRead(ldr) > 200) && controle == 1) { //caso o LDR detecte que está escuro, chama a função de luz ambiente noturna - luz mais quente para descansar a visão
    nightHOT(); //luz noturna
    controle = controle + 1; //incremendo na variável controle para impedir que a luz fique permanentemente acesa em um ambiente escuro
  }
  else { //caso o LDR detecte que não está escuro, chama a função de escolha da luz
    choose(); //função onde a pessoa escolhe se haverá luz ou não e o tipo dela
  }
}

//Função de escolha do estado do led a partir do toque capacitivo
void choose() {
  if (digitalRead(touch) == HIGH) { //Se o primeiro toque for detectado, a primeira configuração de luz será escolhida - nível lógico alto significa que algo foi detectado
    dayCOLD();
    delay(750);
    if (digitalRead(touch) == HIGH) { //Se o segundo toque for detectado, a segunda configuração de luz será escolhida
      afternoonWHITE();
      delay(750);
      if (digitalRead(touch) == HIGH) { //Se o terceiro toque for detectado, a terceira configuração de luz será escolhida
        eveningWARM();
        delay(750);
        if (digitalRead(touch) == HIGH) { //Se o quarto toque for detectado, a quarta configuração de luz será escolhida
          nightHOT();
          delay(750);
          if (digitalRead(touch) == HIGH) { //Se o terceiro toque for detectado, a luz será desligada
            lightOFF();
            delay(750);
          }
        }
      }
    }
  }
}

//Funções das configurações de cores adequadas à luz do ambiente
void dayCOLD() {
  analogWrite(R, 255);
  analogWrite(G, 242);
  analogWrite(B, 224);
}

void afternoonWHITE() {
  analogWrite(R, 255);
  analogWrite(G, 192);
  analogWrite(B, 127);
}

void eveningWARM() {
  analogWrite(R, 255);
  analogWrite(G, 124);
  analogWrite(B, 38);
}

void nightHOT() {
  analogWrite(R, 255);
  analogWrite(G, 108);
  analogWrite(B, 24);
}

//Função que apaga todas as cores - desliga o LED
void lightOFF() {
  analogWrite(R, LOW);
  analogWrite(G, LOW);
  analogWrite(B, LOW);
}
