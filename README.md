# Filamentwaage

([Link zum Grafan Dashboard](http://217.160.37.170:3000/d/aa0QPgJ4z/wagezelle-ender-3-pro?from=1676030184659&to=1676051784659&viewPanel=2&orgId=1&theme=dark))


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

y-Achse = Gewicht in g

x-Achse = Zeitverlauf hh:minmin:ss

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

- mittels Aufruf der ausgegebenen IP-Adresse/update kann die Firmware des Microcontrollers OTA aktualisiert werden




![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/3D_Konzept.jpg?raw=true)

![Aufbau am Ender 3 Pro](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/Foto_1.jpg?raw=true)

Folgende Website visualisiert das Filamentgewicht auf 0,01g genau und aktualisiert sich alle 5 Sekunden. 
Mittels Tara Button kann der aktuelle Gewichtswert tariert werden. Dies ist nur notwendig, wenn eine neue Filamentspule mit einer neuen Rolle verwendet wird.

![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/Website.JPG?raw=true)



### Fazit

Theoretisch ist die Filamentwaage in der Lage auf 0,01g genau zu gemessen. In der Praxis sind Schwankungen von mind. 0,2g zu beobachten. Für die oben beschriebene Anwendung ist dies jedoch vernachlässigbar. 

Um eine aussagekräftige Gewichtsmessung zu erhalten, muss die Wägezelle vor Inbetriebnahme auf Raumtemperatur gebracht werden. 

Im folgenden Graph sind zwei Linien zu erkennen:

Die grüne Linie visualisiert eine Messung, während die gelbe Linie den Mittelwert aus 10 Messungen ergibt. 

![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/Mittelwert.JPG?raw=true)


Probedruck eines ca. 1,5g schweren Deckels. Dabei entstand eine Zunahme des angezeigten Gewichtswerts um ca. 4g. Mögliche Ursachen:
- entstandene Zugkraft an der Filamentspule (mögliche Lösung: andere Zuführung des Filaments, ggf Umlenkung)
- zu geringe Gerichtabnahme des Filaments -> zur Klärung schwereres Druckobjekt zur Überprüfung der These


#### Verbesserungen

- andere Zuführung des Filaments, ggf Umlenkung
- widerstandsarme Lagerung der Filamentspult, durch bspw. Kugellager






