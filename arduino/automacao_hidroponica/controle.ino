#include <OneWire.h>
#include <MsTimer2.h>
#include <DallasTemperature.h> 
#include <LiquidCrystal_I2C.h>

// valor para o sensor de temperatura
float temperatura;

// valores para o pH
float calibracao = 21.05; // mudar o valor da calibração
int analogPin = A0;  // define o pino da leitura do módulo do pH
unsigned long int avgValor;
int buf[10],temp;
float phValor;

// O fio de dados está conectado ao pino digital 4 do Arduino
#define ONE_WIRE_BUS 4

// Configura uma instância oneWire para se comunicar com qualquer dispositivo OneWire
OneWire oneWire(ONE_WIRE_BUS);
 
// Passa a referência oneWire para a biblioteca DallasTemperature 
DallasTemperature sensors(&oneWire);

//define o pino do botão
int botaoPin = 2;
//define o pino do LED
int ledPin = 3;
//define o pino da ventoinha
int ventoinha = 12;
//define o pino do compressor
int compressor = 5;

// valores para o led e seu tempo de ficar ligado
int estadobotao = 0;
unsigned long iniciartempo = 0;
const unsigned long duracao = 28800000; // 8 horas tempo do led ficar ligado em milissegundos
// 8h = 28800 segundos = 28800000 milissegundos

// Endereço I2C do LCD 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

void leituras(){
  //ph
  // faz 10 leituras e armazena elas no buf
  for(int i=0;i<10;i++){
   buf[i]=analogRead(analogPin);
   delay(30);
   }
  //organiza os valores em ordem crescente
  for(int i=0;i<9;i++){
   for(int j=i+1;j<10;j++){
     if(buf[i]>buf[j]){
       temp=buf[i];
       buf[i]=buf[j];
       buf[j]=temp;
      }
    }
  }
  //encontrar um valor médio
  avgValor=0;
  for(int i=2;i<8;i++){
   avgValor+=buf[i];
   //tranformar em uma tensão
   float pHVol=(float)avgValor*5.0/1024/6;
   //transformar no valor de pH
   phValor = -5.70 * pHVol + calibracao;
  }

  //temperatura
  // Envia o comando para obter a temperatura
  sensors.requestTemperatures(); 
 temperatura=sensors.getTempCByIndex(0);

  //LED
  //verifica o estado do botão
   estadobotao = digitalRead(botaoPin);
  if (estadobotao == HIGH) {
    // Armazena o tempo atual quando o botão é pressionado
    iniciartempo = millis();
    // Liga o módulo de relé (LED)
    digitalWrite(ledPin, LOW);
  }
  // Verifica se o tempo decorrido é maior que a duração (8 horas)
  if (millis() - iniciartempo >= duracao) {
    // Desliga o módulo de relé (LED) após 8 horas
    digitalWrite(ledPin, HIGH);
  }
}

void setup() {
  //entradas e saida de cada componente
  pinMode(botaoPin,INPUT);
  pinMode(ledPin,OUTPUT);
  pinMode(ventoinha,OUTPUT);
  pinMode(compressor, OUTPUT);

  // Inicia a biblioteca do sensor de temp
  sensors.begin(); 
  
  //inicializa o LCD e controla a luz de fundo
  lcd.init();
  lcd.backlight();

  //desliga o LED
  digitalWrite(ledPin, HIGH);

  // efetua a rotina d eleitura a cada 1 segundo
  MsTimer2::set(1000, leituras);
  MsTimer2::start();
}

void loop() {
  //imprime o valor do pH
  lcd.setCursor(0, 0);
  lcd.print("pH:");
  lcd.setCursor(3, 0);
  lcd.print(phValor); // Exibe o valor de pH com 2 casas decimais
  
  //imprime a temperatura em Celsius
  lcd.setCursor(0,1);
  lcd.print("Temp:");
  lcd.setCursor(5,1);
  lcd.print(temperatura);  // Exibe o valor de pH com 2 casas decimais
  lcd.setCursor(11,1);
  lcd.print("C");
  delay(200);

  //ligar o compressor de ar
  digitalWrite(compressor, LOW);

  //Ventoinha
  //LIgar de desligar a uma certa temperatura
  if (temperatura>26){
    digitalWrite(ventoinha, LOW);
    }
    else{
    digitalWrite(ventoinha, HIGH);
    }
}
