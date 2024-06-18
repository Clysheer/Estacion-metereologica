#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

  // Reemplazar con tu conexion wifi
const char* ssid[] = { "Vllamada",};        
const char* password[] = {"Vllamada_2021"};


String URL = "http://api.openweathermap.org/data/2.5/weather?"; // URL para la API
String ApiKey = "44d3a7d9ae8f99c1cdc98166cf3bb5f8";             //Clave de la URL

// Reemplazar con la ubicacion deseada
String lat = "Temperley";               
String lon = "Argentina";

void setup() {
  Serial.begin(9600);
  // Iniciamos la conexion Wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Espera por la conexion wifi
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    // Establecer la URL final de la solicitud HTTP con la ubicación y la información de la clave de API
    http.begin(URL + "q=" + lat + "," + lon + "&appid=" + ApiKey);
    // iniciar la conexión y enviar la solicitud HTTP
    int httpCode = http.GET();
    // httpCode será negativo en caso de error
    if (httpCode > 0) {
      // Leer datos como una cadena JSON
      String JSON_Data = http.getString();
      Serial.println(JSON_Data);
      // Recuperar información sobre el tiempo desde el formato JSON
      DynamicJsonDocument doc(2048);
      deserializeJson(doc, JSON_Data);
      JsonObject obj = doc.as<JsonObject>();
      // Mostrar la información meteorológica actual en el monitor serie
      const char* description = obj["weather"][0]["description"].as<const char*>();
      const float temp = obj["main"]["temp"].as<float>();
      const float humidity = obj["main"]["humidity"].as<float>();
      Serial.print("Description: ");
      Serial.println(description);
      Serial.print("Temperature: ");
      Serial.print(temp- 273.15);
      Serial.println(" C");
      Serial.print("Humidity: ");
      Serial.print(humidity);
      Serial.println(" %");
    } else {
      Serial.println("Error!");
    }
    http.end();
  }
  // Espera por 30 segundos
  delay(10000);
}
