Este projeto utiliza um sistema embarcado com Arduino para exibir informações ambientais como hora/data, luminosidade, temperatura e umidade em um display LCD. Sensores e atuadores são integrados para facilitar o monitoramento visual e sonoro das condições ambientais.

--------

📦 **Pré-requisitos**

Arduino IDE instalado em sua máquina

Placa Arduino Uno (ou compatível)

Componentes conectados conforme o diagrama de circuito: (https://wokwi.com/projects/407336114585508865)

--------

📚 **Dependências**

#include <Wire.h>             // Comunicação I2C com o RTC

#include <LiquidCrystal.h>    // Controle do display LCD em modo 4 bits

#include <RTClib.h>           // Comunicação com o módulo RTC DS1307

#include <DHT.h>              // Leitura do sensor DHT22

--------

⚙️ **Componentes Utilizados**

Componente	Função

📟 LCD 16x2	Exibição de dados em tempo real

🕒 RTC DS1307	Controle de data e hora

🌡️ DHT22	Medição de temperatura e umidade

🔆 LDR	Medição de luminosidade ambiente

🔊 Buzzer	Alarme sonoro para níveis críticos

🔴🟡🟢 LEDs	Indicadores visuais de luminosidade

🔘 Botão	Navegação entre telas

--------

🚀 **Instalação**

Clone este repositório ou baixe o arquivo script.ino.

Abra o arquivo na Arduino IDE.

Conecte os componentes conforme o projeto Wokwi.

Selecione a porta e a placa correta.

Compile e faça o upload para a placa.

--------

🛠️ **Ferramentas Utilizadas**

Wokwi – para simulação do circuito e testes online

Arduino IDE – desenvolvimento e upload do código para o Arduino

--------

👨‍💻 **Autores**

Henrique Keigo Nakashima Minowa - RM:564091

Eduardo Delorenzo Moraes - RM:561749

Matheus Bispo Faria Barbosa - RM:562140

