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
#define TESTEOS 1

DHT dht(PIN_DHT, DHTTYPE);
TFT_eSPI tft = TFT_eSPI();
Adafruit_BMP085 bmp;

float temperaturadht;

//Solo descomentar la red wifi a utilizar
//const char* ssid = "Maestros";
//const char* password = "Maestros_2021";
const char* ssid = "Estudiantes";       
const char* password = "educar_2018";
//const char* ssid = "Vllamada";       
//const char* password = "Vllamada_2021";

String URL = "http://api.openweathermap.org/data/2.5/weather?";
String ApiKey = "44d3a7d9ae8f99c1cdc98166cf3bb5f8";
String lat = "Temperley";
String lon = "Argentina";

long tiempo = millis();
bool datoSensor = true;

void setup() {
  PruebasPuert();
  ArranqueSensores();
  //tft.fillScreen(TFT_BLACK)
  conectarWifi();     // Conectar a WiFi
}
void PruebasPuert(){
  if (TESTEOS){
  Serial.begin(9600);
  }
}
void ArranqueSensores(){
  dht.begin();
  tft.init();
  bmp.begin();
}
void conectarWifi() {
  if(TESTEOS){
    Serial.print("Conectando a WiFi...");
  }
  WiFi.begin(ssid, password);
  long inicioTiempo = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - inicioTiempo < 10000) {     // Intentar conectar por 10 segundos
    delay(500);
    if(TESTEOS){
    Serial.print(".");
    }
  }
  if (WiFi.status() == WL_CONNECTED) {
    ImagenWifi(TFT_GREEN);
  }else{
    ImagenWifi(TFT_BLACK);
  }
  if(TESTEOS){
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("");
      Serial.println("WiFi conectado.");
      Serial.println("Dirección IP: ");
      Serial.println(WiFi.localIP());
    } else {
    Serial.println("");
    Serial.println("No se pudo conectar a WiFi.");
    }
  }
}
void Ambiente() {
  float humedad;
  float presion = bmp.readPressure() / 100.0;
  temperaturadht = dht.readTemperature();
  humedad = dht.readHumidity();
  
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN);
  tft.setCursor(60, 15);       
  tft.setTextFont(4);
  tft.print("AMBIENTE");
  
  // Temperatura
  tft.setTextColor(TFT_RED);
  tft.setCursor(26, 55);
  tft.setTextFont(7);
  tft.print(temperaturadht);
  
  // Humedad
  tft.setTextColor(TFT_ORANGE);
  tft.setCursor(26, 150);
  tft.setTextFont(4);
  tft.print("Humedad: ");
  tft.print(humedad);
  tft.println("%");
  
  // Presión Atmosférica
  tft.setTextColor(TFT_VIOLET);
  tft.setCursor(26, 180);
  tft.setTextFont(4);
  tft.print("P. Atmos: ");
  tft.print(presion, 2);
  tft.print("hPa");
}
void Meteorologico(float temp, float humidity) {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN);
  tft.setCursor(47, 15);       
  tft.setTextFont(4);
  tft.print("TEMPERLEY");
  
  // Temperatura
  tft.setTextColor(TFT_RED);
  tft.setCursor(17, 55);
  tft.setTextFont(7);
  tft.print(temp - 273.15);
  
  // Humedad
  tft.setTextColor(TFT_ORANGE);
  tft.setCursor(26, 150);
  tft.setTextFont(4);
  tft.print("Humedad: ");
  tft.print(humidity);
  tft.print(" %");
}
void obtenerDatosMeteorologicos() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(URL + "q=" + lat + "," + lon + "&appid=" + ApiKey);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String JSON_Data = http.getString();
      if (TESTEOS){
        Serial.println(JSON_Data);
      }

      DynamicJsonDocument doc(2048);
      deserializeJson(doc, JSON_Data);
      JsonObject obj = doc.as<JsonObject>();

      float temp = obj["main"]["temp"].as<float>();
      float humidity = obj["main"]["humidity"].as<float>();

      Meteorologico(temp, humidity);
    }else {
      if (TESTEOS){
        Serial.println("¡Error al obtener datos!");
      }
      
    }
    http.end();
  } else {
    if (TESTEOS){
    Serial.println("WiFi desconectado.");
    }
    
  }
}

void ImagenWifi(uint16_t color) {
  // Coordenadas del símbolo WiFi
  int x = tft.width() - 10;
  int y = 0;

  
  tft.fillRect(x, y, 10, 10, TFT_BLACK);    // Borra el área del símbolo antes de dibujarlo 

  // Dibuja un símbolo de WiFi simple usando líneas y arcos dentro de un área de 10x10
  tft.drawPixel(x + 5, y + 8, color);                  // Punto central (señal)       
  tft.drawLine(x + 3, y + 6, x + 7, y + 6, color);     // Primera línea
  tft.drawLine(x + 2, y + 4, x + 8, y + 4, color);     // Segunda línea
  tft.drawLine(x + 1, y + 2, x + 9, y + 2, color);     // Tercera línea
}
void ReintentarConexionWifi(){
  if (WiFi.status() != WL_CONNECTED) {
    conectarWifi();
  }
}
void loop() {
  Ambiente();
  ReintentarConexionWifi();
  delay(14000);
  obtenerDatosMeteorologicos();
  delay(14000);
}