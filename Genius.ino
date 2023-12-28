const int LedAzul = 9; // Pino do LED Azul
const int LedVerde = 10; // Pino do LED Verde
const int LedVermelho = 12; // Pino do LED Vermelho

const int btnVermelho = 2; // Pino do botão 2
const int btnVerde = 3; // Pino do botão 3
const int btnAzul = 4; // Pino do botão 4
const int btnAmarelo = 5; // Pino do botão 5

const int acerto = 11; // Pino de feedback de acerto
const int erro = 13; // Pino de feedback de erro


int dificuldade = 5; // Nível de dificuldade e tamanho do vetor sequência
int sequencia[5]; // Vetor que armazena a sequência gerada aleatoriamente
int index = 0; // Índice atual na sequência

void setup() {
  Serial.begin(9600);
  pinMode(LedAzul, OUTPUT);
  pinMode(LedVerde, OUTPUT);
  pinMode(LedVermelho, OUTPUT);
  
  pinMode(acerto, OUTPUT);
  pinMode(erro, OUTPUT);

  pinMode(btnVermelho, INPUT);
  pinMode(btnVerde, INPUT);
  pinMode(btnAzul, INPUT);
  pinMode(btnAmarelo, INPUT);
  randomSeed(analogRead(0));
  
  gerarSequencia();
}

void loop() {
  if(index == 0){
    inicio();
  }
  
  Serial.println("Start");
  
  for (int i = 0; i <= index; i++) {
    mostrarCor(sequencia[i]);
    delay(1000);
  }
  
  int flag = 0;
  
  for (int i = 0; i <= index; i++) {
    int btnpress = aguardarBotao();
    if(btnpress != sequencia[i]){
      errou();
      flag = 1;
    }   
  }
  
  if(flag == 0){
    acertou();
  }

  index++;
  
  if (index == 5) {
    ganhou();
  }
}

void inicio(){
  digitalWrite(acerto, HIGH);
  digitalWrite(LedAzul, HIGH);
  digitalWrite(LedVermelho, HIGH);
  digitalWrite(LedVerde, HIGH);
  digitalWrite(erro, HIGH);
  delay(3000);
  digitalWrite(acerto, LOW);
  digitalWrite(LedAzul, LOW);
  digitalWrite(LedVermelho, LOW);
  digitalWrite(LedVerde, LOW);
  digitalWrite(erro, LOW);
  delay(1000);
}

void mostrarCor(int cor) {
  if (cor == 1) {
    Vermelho();
  }
  else if(cor == 2){
    Verde();
  }
  else if(cor == 3){
    Azul();
  }
  else if(cor == 4){
    Amarelo();
  }
}

int aguardarBotao() {
  int botaoPressionado = 0;

  while (true) {
    if (digitalRead(btnVermelho) == HIGH) {
      botaoPressionado = 1;
      Vermelho();
      break;
    } else if (digitalRead(btnVerde) == HIGH) {
      botaoPressionado = 2;
      Verde();
      break;
    } else if (digitalRead(btnAzul) == HIGH) {
      botaoPressionado = 3;
      Azul();
      break;
    } else if (digitalRead(btnAmarelo) == HIGH) {
      botaoPressionado = 4;
      Amarelo();
      break;
    }
  }

  while (digitalRead(btnVermelho) == HIGH || digitalRead(btnVerde) == HIGH ||
         digitalRead(btnAzul) == HIGH || digitalRead(btnAmarelo) == HIGH) {
    // Espera até que todos os botões sejam soltos
  }

  return botaoPressionado;
}

void mostraVetor(){ // Função de teste para mostrar a sequência
  int tamanhoDoVetor = sizeof(sequencia) / sizeof(sequencia[0]);
  Serial.print("[");
    for (int i = 0; i < tamanhoDoVetor; i++) {
      Serial.print(sequencia[i]);
      if (i < tamanhoDoVetor - 1) {
        Serial.print(", ");
      }
    }
    Serial.println("]");
}

void gerarSequencia() {
  for (int i = 0; i < dificuldade; i++) {
    int numeroAleatorio = random(1, 5);
    sequencia[i] = numeroAleatorio;
  }
}

void acertou() {
  Serial.println("Você acertou!");
  digitalWrite(acerto, HIGH);
  delay(1000);
  digitalWrite(acerto, LOW);
}

void errou() {
  Serial.println("Você errou!");
  digitalWrite(erro, HIGH);
  delay(1000);
  index = -1;
  gerarSequencia();
  digitalWrite(erro, LOW);
}

void ganhou(){
  Serial.println("Você ganhou!");
  index = 0;
  gerarSequencia();

  digitalWrite(acerto, HIGH);
  digitalWrite(LedAzul, HIGH);
  digitalWrite(LedVermelho, HIGH);
  digitalWrite(LedVerde, HIGH);
  delay(1000);
  digitalWrite(acerto, LOW);
  digitalWrite(LedAzul, LOW);
  digitalWrite(LedVermelho, LOW);
  digitalWrite(LedVerde, LOW);
  delay(500);
}

void Vermelho() {
  digitalWrite(LedVermelho, HIGH);
  delay(1000);
  digitalWrite(LedVermelho, LOW);
  delay(500);
}

void Verde() {
  digitalWrite(LedVerde, HIGH);
  delay(1000);
  digitalWrite(LedVerde, LOW);
  delay(500);
}

void Azul() {
  digitalWrite(LedAzul, HIGH);
  delay(1000);
  digitalWrite(LedAzul, LOW);
  delay(500);
}

void Amarelo() {
  digitalWrite(LedVerde, HIGH);
  digitalWrite(LedVermelho, HIGH);
  delay(1000);
  digitalWrite(LedVerde, LOW);
  digitalWrite(LedVermelho, LOW);
  delay(500);
}
