# Filamentwaage

Created by: Bader Raphael, Brockschmidt Sophia, Moser Anna

### Verwendete Hardware: 

- Microcontoller: ESP32 Vroom
- Sensor: Wägezelle 5kg ([Amazon Link](https://www.amazon.de/dp/B073GWX6J4?ref=ppx_yo2ov_dt_b_product_details&th=1))
- A/D Wandler: HX711
- Schrauben: 2x M5x20mm / 2x M4x20mm
- diverse Jumperkabel
- Steckboard
- additiv gefertigte Halterung für Wägezelle (siehe Ordner 3D)


### Verwendete Bibliotheken:
- HX711  
- ESPAsyncWebServer 
- AsyncElegantOTA


##### Pinbelegung ESP32

GPIO 33 = DT data 

GPIO 32 = SCK clock





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

![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/3D_Konzept.jpg?raw=true)

![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/Foto_1.jpg?raw=true)

### Mögliche Verbesserungen:
