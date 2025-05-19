#include <Wire.h>
#include <LiquidCrystal.h>
#include <RTClib.h>
#include <DHT.h>

// LCD (modo paralelo)
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
RTC_DS1307 rtc;

// DHT
#define DHTPIN A2        // Pino de dados do DHT22
#define DHTTYPE DHT22    // Tipo do sensor
DHT dht(DHTPIN, DHTTYPE);

// Pinos
const int ldrPin = A0;
const int botaoTrocaTela = 10;
const int ledVerde = 6;
const int ledAmarelo = 7;
const int ledVermelho = 8;
const int buzzer = 9;

// Constantes
#define MIN_LUZ 15
#define MAX_LUZ 820
#define UTC_OFFSET 0

int paginaAtual = 0;
bool ultimoEstadoBotao = HIGH;

// Caracteres personalizados
byte iconeRelogio[8] = {
  B00000,
  B01110,
  B10101,
  B10111,
  B10001,
  B01110,
  B00000,
  B00000
};

byte iconeSol[8] = {
  B00100,
  B10101,
  B01110,
  B11111,
  B01110,
  B10101,
  B00100,
  B00000
};

byte iconeTermometro[8] = {
  B00100,
  B00100,
  B00100,
  B01110,
  B01110,
  B11111,
  B11111,
  B01110
};

byte iconeGota[8] = {
  B00100,
  B00100,
  B01010,
  B01010,
  B10001,
  B10001,
  B10001,
  B01110
};

void setup() {
  pinMode(botaoTrocaTela, INPUT_PULLUP);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin();

  lcd.createChar(0, iconeRelogio);
  lcd.createChar(1, iconeSol);
  lcd.createChar(2, iconeTermometro);
  lcd.createChar(3, iconeGota);

  if (!rtc.begin()) {
    lcd.setCursor(0, 0);
    lcd.print("Erro no RTC");
    while (true);
  }

  lcd.setCursor(0, 0);
  lcd.print("Bem-vindo a");
  lcd.setCursor(0, 1);
  lcd.print("Vinheria Agnello");
  delay(3000);
  lcd.clear();
}

void loop() {
  bool estadoAtual = digitalRead(botaoTrocaTela);
  if (estadoAtual == LOW && ultimoEstadoBotao == HIGH) {
    transicaoTela();           // Transição antes de mudar a tela
    paginaAtual = (paginaAtual + 1) % 4;
    delay(300);
  }
  ultimoEstadoBotao = estadoAtual;

  switch (paginaAtual) {
    case 0: mostrarHoraData(); break;
    case 1: mostrarLuminosidade(); break;
    case 2: mostrarTemperatura(); break;
    case 3: mostrarUmidade(); break;
  }

  delay(500);
}

void transicaoTela() {
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 0);
    lcd.print(" ");
    lcd.setCursor(i, 1);
    lcd.print(" ");
    delay(20);
  }
}

void mostrarHoraData() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write(byte(0));
  lcd.print(" Hora/Data");

  DateTime now = rtc.now();
  now = DateTime(now.unixtime() + UTC_OFFSET * 3600);

  lcd.setCursor(0, 1);
  if (now.day() < 10) lcd.print("0");
  lcd.print(now.day());
  lcd.print("/");
  if (now.month() < 10) lcd.print("0");
  lcd.print(now.month());
  lcd.print("/");
  lcd.print(now.year());

  lcd.print(" ");
  if (now.hour() < 10) lcd.print("0");
  lcd.print(now.hour());
  lcd.print(":");
  if (now.minute() < 10) lcd.print("0");
  lcd.print(now.minute());
}

void mostrarLuminosidade() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write(byte(1));
  lcd.print(" Luminosidade");

  int leitura = 0;
  for (int i = 0; i < 10; i++) {
    leitura += analogRead(ldrPin);
    delay(5);
  }
  leitura /= 10;

  int luz = map(leitura, MIN_LUZ, MAX_LUZ, 0, 100);
  luz = constrain(luz, 0, 100);

  lcd.setCursor(0, 1);
  lcd.print(luz);
  lcd.print(" %");

  if (luz <= 30) {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
    noTone(buzzer);
  } else if (luz <= 70) {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW);
    tone(buzzer, 2000, 300);
  } else {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);
    noTone(buzzer);
  }
}

void mostrarTemperatura() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write(byte(2));
  lcd.print(" Temperatura");

  float tempC = dht.readTemperature();

  lcd.setCursor(0, 1);
  if (isnan(tempC)) {
    lcd.print("Erro leitura");
  } else {
    lcd.print(tempC, 1);
    lcd.print(" C");
  }
}

void mostrarUmidade() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write(byte(3));
  lcd.print(" Umidade");

  float umidade = dht.readHumidity();

  lcd.setCursor(0, 1);
  if (isnan(umidade)) {
    lcd.print("Erro leitura");
  } else {
    lcd.print(umidade, 1);
    lcd.print(" %");
  }
}
