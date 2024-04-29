#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Put your WiFi Credentials here
const char* ssid = "Vllamada";
const char* password = "Vllamada_2021";

// URL Endpoint for the API
String URL = "http://api.openweathermap.org/data/2.5/weather?";
String ApiKey = "44d3a7d9ae8f99c1cdc98166cf3bb5f8";
// Replace with your location Credentials
String lat = "Temperley";
String lon = "Argentina";

void setup() {
  Serial.begin(9600);
  // We start by connecting to a WiFi network
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
  // wait for WiFi connection
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    // Set HTTP Request Final URL with Location and API key information
    http.begin(URL + "q=" + lat + "," + lon + "&appid=" + ApiKey);
    // start connection and send HTTP Request
    int httpCode = http.GET();
    // httpCode will be negative on error
    if (httpCode > 0) {
      // Read Data as a JSON string
      String JSON_Data = http.getString();
      Serial.println(JSON_Data);
      // Retrieve some information about the weather from the JSON format
      DynamicJsonDocument doc(2048);
      deserializeJson(doc, JSON_Data);
      JsonObject obj = doc.as<JsonObject>();
      // Display the Current Weather Info on Serial Monitor
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
  // Wait for 30 seconds
  delay(10000);
}
