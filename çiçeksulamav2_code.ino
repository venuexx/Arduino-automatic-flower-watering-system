#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int OLED_RESET = 4;
Adafruit_SSD1306 display(OLED_RESET);

const int sensorPin = A0;
int buzzer = 2;
int role = 3;
int buzzer_time = 25;
int potPin = A3;
int potDeger;
int potGirdi;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(19, INPUT);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(30,12);
  display.println("Yukleniyor...");
  display.display();
  delay(3000);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  int percent = map(sensorValue, 355, 1023, 100, -10);
  potDeger = analogRead(potPin);
  potGirdi = potDeger / 10;

  Serial.print("Potansiyometre Okunan Deger= ");
  Serial.println(potGirdi);
  Serial.print("Toprak nemi: ");
  Serial.print(percent);
  Serial.println("%");
  delay(200);

  display.clearDisplay();
  display.setCursor(20,2);
  display.print("Toprak Nem: ");
  display.print(percent);
  display.println("%");
  display.setCursor(30,12);
  display.print("Min. Nem: ");
  display.println(potGirdi);
  display.setCursor(12,24);
  display.print("Venuex Technology");
  display.display();

  if (percent < potGirdi) {
    //digitalWrite(buzzer, HIGH);
    delay(buzzer_time);
    digitalWrite(buzzer, LOW);
    delay(buzzer_time);
    digitalWrite(role, LOW);
    delay(1000);
  }

  else {
    digitalWrite(buzzer, LOW);
    delay(50);
    digitalWrite(role, HIGH);
    delay(50);
  }
}
