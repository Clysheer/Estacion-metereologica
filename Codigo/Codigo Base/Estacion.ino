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
#define PRUEBA 1
DHT dht(PIN_DHT, DHTTYPE);
TFT_eSPI tft = TFT_eSPI();
Adafruit_BMP085 bmp;

  // Reemplazar con tu conexion wifi
const char* ssid = "Taller_Electronica_5GHz";       
const char* password = "robotica";
//const char* ssid = "Maestros";
//const char* password = "Maestros_2021";
//const char* ssid = "Estudiantes";       
//const char* password = "educar_2018";
//const char* ssid = "Vllamada";       
//const char* password = "Vllamada_2021";

String URL = "http://api.openweathermap.org/data/2.5/weather?"; // URL para la API
String ApiKey = "44d3a7d9ae8f99c1cdc98166cf3bb5f8";             //Clave de la URL

// Reemplazar con la ubicacion deseada
String lat = "Temperley";               
String lon = "Argentina";

void setup() {
  // Iniciamos la conexion Wifi
  WiFi.begin(ssid, password);
  if (PRUEBA){
   Serial.begin(9600);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".conectando.");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  }
}
void Atmosferico(const float tempat, const float humat){
  if(PRUEBA){
    Serial.print("Atmosferico");
  }
  tft.setTextColor(TFT_GREEN);
  tft.setCursor(47, 15);       
  tft.setTextFont(4);
  tft.print("TEMPERLEY");

   //Temperatura
  tft.setTextColor(TFT_RED);
  tft.setCursor(17, 55);
  tft.setTextFont(7);
  tft.print(tempat - 273.15);

    //Humedad
  tft.setTextColor(TFT_ORANGE);
  tft.setCursor(26, 150);
  tft.setTextFont(4);
  tft.print("Humedad: ");
  tft.print(humat);
  tft.print(" %");
}

void ImagenWifi(uint16_t color) {
  if (PRUEBA){
    Serial.println("icono wifi");
  }
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

void TemAmbiente(){
  if (PRUEBA){
    Serial.print("Ambiente");
  }
  float tempdht;
  float humedad;
  float presion;
  tempdht = dht.readTemperature();
  humedad = dht.readHumidity();
  presion = bmp.readPressure() / 100.00;
  tft.setTextColor(TFT_RED);
  tft.setCursor(26, 55);
  tft.setTextFont(7);
  tft.print(tempdht);

  tft.setTextColor(TFT_ORANGE);
  tft.setCursor(26, 150);
  tft.setTextFont(4);
  tft.print("Hum: ");
  tft.print(humedad);
  tft.println("%");

  tft.setTextColor(TFT_VIOLET);
  tft.setCursor(26, 180);
  tft.setTextFont(4);
  tft.print("Pa: ");
  tft.print(presion, 2);
  tft.println("hPa");
}
void Redes(){
  if (WiFi.status() == WL_CONNECTED) {
    ImagenWifi(TFT_GREEN);
    HTTPClient http;
    // Establecer la URL final de la solicitud HTTP con la ubicación y la información de la clave de API
    http.begin(URL + "q=" + lat + "," + lon + "&appid=" + ApiKey);
    // iniciar la conexión y enviar la solicitud HTTP
    int httpCode = http.GET();
    // httpCode será negativo en caso de error
    if (httpCode > 0) {
      // Leer datos como una cadena JSON
      String JSON_Data = http.getString();
     // Serial.println(JSON_Data);
      // Recuperar información sobre el tiempo desde el formato JSON
      DynamicJsonDocument doc(2048);
      deserializeJson(doc, JSON_Data);
      JsonObject obj = doc.as<JsonObject>();
      // Mostrar la información meteorológica actual en el monitor serie
    
      const float tempat = obj["main"]["temp"].as<float>();
      const float humat = obj["main"]["humidity"].as<float>();
      Atmosferico(tempat, humat);
      
      
    } else {
      ImagenWifi(TFT_BLACK);
    }
    http.end();
  }
  delay(10000);
}
void loop() {
  Redes();
  
  TemAmbiente();
  delay(10000);
}
