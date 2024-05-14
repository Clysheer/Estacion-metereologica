# Estacion-metereologica
La  Estación  Meteorológica  es  un  dispositivo  que  tiene  la  capacidad  de  medir  la temperatura  ambiente,  humedad  y  presión  atmosférica  del  lugar  específico  en  el  que  se encuentre  el  dispositivo  y  también  puede  visualizar  la  temperatura  de  una  zona geográfica  predeterminada  (ej:  Lomas  de  Zamora).  Todo  esto  utilizando  la  pantalla
ST7789 de 240*240 pixeles que al ser oled mostrará al usuario los datos extraídos de manera fácil y sencilla. Todo esto utilizando como cerebro al microcontrolador ESP32que  utilizando  su  conexión  Wifi  logre  interactuar  con  la  utilización  de  una  API,  la  cual recibirá  los  datos  de  la  zona  geográfica  y  los  mostrará  por  la  pantalla,  y  además, utilizando  los  sensores  de  Presión  Atmosférica  BPM  280  y  el    DHT11  de  temperatura  y humedad  calcule  la  temperatura  del  ambiente  y  la  presión  atmosférica.
En  definitiva,  es  un  dispositivo  compuesto  por  un  microcontrolador  ESP32,  una  pantalla oled  y  unos  sensores  de  temperatura,  humedad  y  presión  atmosférica.
Al  tamaño  de  la  pantalla  ser  relativamente  pequeña,  los  datos  extraídos  del  sensor DHT11  y  de  la  API  se  irán  mostrando  por  la  pantalla  ST7789  en  manera  de  turnos, cada  15  segundo  pasará  de  mostrar  la  temperatura  ambiente  a  mostrar  la  meteorología y  así  sucesivamente.
Todo esto será alimentado sin la utilización de baterías, si no que será alimentado mediante un cargador de 240v con una salida de 5v (cargador de celular) que ira conectado a la placa del dispositivo
El  proyecto  está  planteado  como  un  proyecto  de  inicio,  el  costo  económico  no  es  muy alto  y  sirve  como  inicio  a  la  utilización  del  microcontrolador  ESP32  y  su  conectividad wifi.
![image](https://github.com/Clysheer/Estacion-metereologica/assets/112779501/a632e171-3ac4-46bb-ba8a-081e93e5fa85)
*Diagrama  en  bloques:*
![image](https://github.com/Clysheer/Estacion-metereologica/assets/112779501/56cff24d-81c1-47f1-8f01-ad6f3b75ed04)
*Materiales :*
1-Pantalla DISPLAY TFT
ST7789  240*240
2-ESP  WROOM  32  DEVKIT  V1
3-DHT11  Sensor
4-Placa  PCB  Simple  Faz  10x10
5-Sensor Presion Atmosferica
Bmp280
*Diseño 3D :*
![image](https://github.com/Clysheer/Estacion-metereologica/assets/112779501/e3d9f9ba-7208-4bc2-9df9-08e691eb176b)
![image](https://github.com/Clysheer/Estacion-metereologica/assets/112779501/6ba13a63-bb2c-414e-a53b-e9fcee4ba187)
![image](https://github.com/Clysheer/Estacion-metereologica/assets/112779501/b6efeacd-a39a-4d09-b9ca-1d85ac8d8a1c)
