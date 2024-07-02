#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_BMP085.h>

#define PIN_DHT 5
#define DHTTYPE DHT11

DHT dht(PIN_DHT, DHTTYPE);
TFT_eSPI tft = TFT_eSPI();
Adafruit_BMP085 bmp;

float temperaturadht;
float temperaturabmp;
//Solo descomentar la red wifi a utilizar

//const char* ssid[] = {"Maestros"};       
//const char* password[] = {"Maestros_2021"};
const char* ssid[] = {"Estudiantes"};       
const char* password[] = {"educar_2018"};
//const char* ssid[] = {"Vllamada"};       
//const char* password[] = {"Vllamada_2021"};

String URL = "http://api.openweathermap.org/data/2.5/weather?";
String ApiKey = "44d3a7d9ae8f99c1cdc98166cf3bb5f8";
String lat = "Temperley";
String lon = "Argentina";

bool showSensorData = true;
unsigned long previousMillis = 0;
const long interval = 5000;

void setup() {
  Serial.begin(9600);
  dht.begin();
  tft.init();
  bmp.begin();
  tft.fillScreen(TFT_BLACK);
  Serial.print("conectando WIFI...");
  WiFi.begin(*ssid, *password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado.");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

/*void SensorDht() {
  float humedad;
  temperaturadht = dht.readTemperature();
  humedad = dht.readHumidity();
  tft.setTextColor(TFT_RED);
  tft.setCursor(10, 190);
  tft.setTextFont(4);
  tft.print("Hume: ");
  tft.print(humedad);
  tft.println("%");
}*/

/*void SensorPresionAtmo() {
  float presion;
  temperaturabmp = bmp.readTemperature();
  presion = bmp.readPressure();
  tft.setTextColor(TFT_BLUE);
  tft.setTextFont(4);
  tft.setCursor(10, 120);
  tft.print("PRESION: %34,8");
  // tft.print(presion);
}*/

/*void TemperaturaPromedio() {
  float promedio = (temperaturadht + temperaturabmp) / 2.0;
  tft.setTextColor(TFT_RED);
  tft.setTextFont(4);
  tft.setCursor(10, 70);
  tft.print("TEMP: ");
  tft.print(promedio);
  tft.println("°C");
} */

void Ambiente(){
  float humedad;
  temperaturadht = dht.readTemperature();
  humedad = dht.readHumidity();
  
  tft.setTextColor(TFT_GREEN);
  tft.setCursor(60, 15);       
  tft.setTextFont(4);
  tft.print("AMBIENTE");
     //Temperatura
  tft.setTextColor(TFT_RED);
  tft.setCursor(26, 55);
  tft.setTextFont(7);
  tft.print(temperaturadht);
        //Humedad
  tft.setTextColor(TFT_ORANGE);
  tft.setCursor(26, 150);
  tft.setTextFont(4);
  tft.print("Humedad: ");
  tft.print(humedad);
  tft.println("%");
        //Presion Atmosferica
  tft.setTextColor(TFT_VIOLET);
  tft.setCursor(26, 180);
  tft.setTextFont(4);
  tft.print("P. Atmos: ");
  tft.print("NT");
}
void Meteorologico(float temp, float humidity){
  tft.setTextColor(TFT_GREEN);
  tft.setCursor(47, 15);       
  tft.setTextFont(4);
  tft.print("TEMPERLEY");
    //Temperatura
  tft.setTextColor(TFT_RED);
  tft.setCursor(17, 55);
  tft.setTextFont(7);
  tft.print(temp - 273.15);
      //Humedad
   tft.setTextColor(TFT_ORANGE);
  tft.setCursor(26, 150);
  tft.setTextFont(4);
  tft.print("Humedad: ");
  tft.print(humidity);
  tft.print(" %");
}
/*void PantallaOled(float temp, float humidity) {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextFont(5);
  tft.setCursor(10, 10);
  tft.print("TEMPERLEY");

  tft.setTextColor(TFT_RED);
  tft.setTextFont(4);
  tft.setCursor(10, 70);
  tft.print("TEMP: ");
  tft.print(temp - 273.15);
  tft.println("°C");

  tft.setTextColor(TFT_BLUE);
  tft.setTextFont(4);
  tft.setCursor(10, 120);
  tft.print("Humedad: ");
  tft.print(humidity);
  tft.print(" %");
}*/

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    tft.fillScreen(TFT_BLACK);
 
    if (showSensorData) {
      //TemperaturaPromedio();
      Ambiente();
      //SensorPresionAtmo();
    } else {
      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(URL + "q=" + lat + "," + lon + "&appid=" + ApiKey);
        int httpCode = http.GET();

        if (httpCode > 0) {
          String JSON_Data = http.getString();
          Serial.println(JSON_Data);

          DynamicJsonDocument doc(2048);
          deserializeJson(doc, JSON_Data);
          JsonObject obj = doc.as<JsonObject>();

          float temp = obj["main"]["temp"].as<float>();
          float humidity = obj["main"]["humidity"].as<float>();

          Meteorologico(temp, humidity);
        } else {
          Serial.println("¡Error al obtener datos!");
        }
        http.end();
      } else {
        Serial.println("WiFi desconectado.");
      }
    }
    showSensorData = !showSensorData;
  }
}
