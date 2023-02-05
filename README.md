# Filamentwaage

Created by: Bader Raphael, Brockschmidt Sophia, Moser Anna

### Verwendete Hardware: 

- Microcontoller: ESP32 Vroom
- Sensor: Wägezelle 5kg ([Amazon Link](https://www.amazon.de/dp/B073GWX6J4?ref=ppx_yo2ov_dt_b_product_details&th=1))
- A/D Wandler: HX711
- Schrauben: 2x M5x20mm / 2x M4x20mm


### Verwendete Bibliotheken:
- [HX711] (https://github.com/bogde/HX711)


### Vorbereitung
[Link zu Tutorial](https://user-images.githubusercontent.com/124445731/216824439-50896850-175e-45c3-b1ba-71407113d498.png)

#### Hardware

##### Pinbelegung ESP32

Änderungen:
GPIO 16 -> GPIO 33

GPIO 4  -> GPIO 32
! [alt text](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2022/03/ESP32-load-cell-diagram_bb.png?resize=1024%2C472&quality=100&strip=all&ssl=1)

![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/3D_Konzept.jpg?raw=true)

![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/Steckbrett.jpg?raw=true)

![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/Foto_1.jpg?raw=true)

#### Software
##### Libraries installieren
[HX711](https://github.com/bogde/HX711) Ver 0.7.5

##### platformio.ini ergänzen
lib_deps = bogde/HX711@^0.7.5

monitor_speed = 115200!

##### Code einfügen 
-> Pinbelegung anpassen

##### Kalibrierfaktor bestimmen
Für eine aussagekräftige Gewichtsaussage muss zuerst der Kalibrierfaktor mittels Normgewicht (100g) ermittelt werden.
Kalibrierfaktor = angezeigter Wert 48466 / 100g 

-> in Programmcode ergänzen (Zeile 44) 

###### Überprüfung Kalibrierfaktor
leere & volle Filamentrolle wird mittels Präzisionswaage gewogen und mit Wert der Filamentwaage verglichen

##### Web Server Anwendung
[Anleitung](https://randomnerdtutorials.com/esp32-dht11-dht22-temperature-humidity-web-server-arduino-ide/)
1. Libraries installieren

2. Platform.io ergänzen

ottowinter/ESPAsyncWebServer-esphome@^3.0.0![image](https://user-images.githubusercontent.com/124445731/216825539-7a01ff40-6a96-4703-b9e1-7058dc8aca42.png)

3. Network configurations im Code ändern

4. Einheiten ändern

5. [10.0.9.47](http://10.0.9.47/) Anzeige Filamentwaage 


