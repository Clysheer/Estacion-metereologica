#include <DHT.h>      //Librerias del sensor DHT11
#include <DHT_U.h>    //*

#define PIN_DHT  35          //Pin del esp32 utilizado para la transmision de datos
#define DHTTYPE    DHT11    //Declaracion del tipo de sensor, DHT11 o DHT22

float temperatura;
float humedad;

DHT dht(PIN_DHT, DHTTYPE);   //Creacion del objeto dht
 
void setup(){
  Serial.begin(9600);
  dht.begin();           //inicializacion del sensor DHT11
}

void loop(){
  temperatura = dht.readTemperature();  //Funcion medidora de temperatura
  humedad = dht.readHumidity();         //Funcion medidora de humedad
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" Humedad: ");
  Serial.println(humedad);
  delay(1000);
}
