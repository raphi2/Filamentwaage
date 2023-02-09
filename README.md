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

![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/Steckbrett_1.jpg?raw=true)

![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/HX711.jpg?raw=true)

![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/ESP32.jpg?raw=true)


##### Kalibrierfaktor bestimmen
Für eine aussagekräftige Gewichtsaussage muss zuerst der Kalibrierfaktor mittels Normgewicht (100g) ermittelt werden.
Kalibrierfaktor = angezeigter Wert 48466 / 100g 

-> in Programmcode ergänzen mittels Funktion scale.set_scale


###### Überprüfung Kalibrierfaktor
leere & volle Filamentrolle wird mittels Präzisionswaage gewogen und mit Wert der Filamentwaage verglichen


##### Web Server Anwendung

-> Netzwerk Anmeldecode (SSID + Passwort) im Code ergänzen

-> Aufruf der ausgegebenen IP-Adresse

![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/3D_Konzept.jpg?raw=true)

![Aufbau am Ender 3 Pro](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/Foto_1.jpg?raw=true)


