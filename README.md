# Filamentwaage

Created by: Bader Raphael, Brockschmidt Sophia, Moser Anna

### Zielstellung

Winterchallenge Studiengang Smart Products and Solutions 2022:

Aufgabenstellung: Einbindung der 3D-Filament Drucker im Makers Lab der FH in eine digital factory

Ziele: 
- Vernetzung und Möglichkeit des Remote Betriebs
- Predictive Maintenance durch geeignete Geräteüberwachung, in diesem Fall des Rohstoffs
- Überwachung des verbleibenden Filaments

### Challenges

- Beispielcode des HX711 Wandlers enthält Befehle, welche diesen einerseits regelmäßig in Sleep Mode versetzt, die CPU verlangsamt und das Programm bei Einbindung des Webservers zum Absturz bringt
- Lötstellen mehrfach ausgerissen
- Entfernen der Stützstruktur der additiv gefertigten Halterung
- Mangelnde Genauigkeit der gedruckten Teile machten intensive Nacharbeit notwendig
- Gewichtszunahme am ruhenden Objekt durch größeren Moment: +0,9g nach 23min 28s 
![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/Gewichtszunahme.JPG?raw=true)



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
- ESP8266 Influxdb


##### Pinbelegung ESP32

- GPIO 33 = DT data 
- GPIO 32 = SCK clock

![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/Steckbrett_1.jpg?raw=true)

![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/HX711.jpg?raw=true)

![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/ESP32.jpg?raw=true)


##### Kalibrierfaktor bestimmen
Für eine aussagekräftige Gewichtsausgabe wurde zunächst der Kalibrierfaktor mittels Normgewicht (100g) bestimmt. 
Kalibrierfaktor = angezeigter Wert 48466 / 100g 

-> in Programmcode ergänzen mittels Funktion scale.set_scale


###### Überprüfung Kalibrierfaktor
leere & volle Filamentrolle wird mittels Präzisionswaage gewogen und mit Wert der Filamentwaage verglichen


##### Web Server Anwendung

- Netzwerk Anmeldecode (SSID + Passwort) im Code ergänzen

- Aufruf der ausgegebenen IP-Adresse

### Fazit

Theoretisch ist die Filamentwaage in der Lage auf 0,01g genau zu gemessen. In der Praxis sind Schwankungen von mind. 0,2g zu beobachten. Für die oben beschriebene Anwendung ist dies jedoch vernachlässigbar. 

![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/3D_Konzept.jpg?raw=true)

![Aufbau am Ender 3 Pro](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/Foto_1.jpg?raw=true)

![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/Website.JPG?raw=true)


