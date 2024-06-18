#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

float temperaturabmp;
float presionatmos;

void setup() {
  Serial.begin(9600);
  bmp.begin();
}

void loop() {
  temperaturabmp = bmp.readTemperature();
  presionatmos = bmp.readPressure();
  Serial.print("Temperatura = ");
  Serial.print(temperaturabmp);
  Serial.println(" *C");

  Serial.print("Presion At ");
  Serial.print(presionatmos);
  Serial.println(" Pa");
  delay(500);
}
