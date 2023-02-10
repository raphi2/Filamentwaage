# Filamentwaage

Konzept und Umsetzung: Bader Raphael, Brockschmidt Sophia, Moser Anna

### Kurzübersicht

[Link zum Grafana Dashboard](http://217.160.37.170:3000/d/aa0QPgJ4z/wagezelle-ender-3-pro?from=1676030184659&to=1676051784659&viewPanel=2&orgId=1&theme=dark)

Lokale Webseite der Waage aufrufbar unter: [10.0.8.146](10.0.8.146)

### Zielstellung

Winterchallenge Studiengang Smart Products and Solutions 2022:

Aufgabenstellung: Einbindung der 3D-Filament Drucker im Makers Lab der FH in eine digital factory

Ziele: 
- Vernetzung und Möglichkeit des Remote Betriebs
- Predictive Maintenance durch geeignete Geräteüberwachung, in diesem Fall des Rohstoffs
- Überwachung des verbleibenden Filaments

### Verwendete Hardware: 

- Microcontoller: ESP32 Vroom
- Sensor: Wägezelle 5kg ([Amazon Link](https://www.amazon.de/dp/B073GWX6J4?ref=ppx_yo2ov_dt_b_product_details&th=1))
- A/D Wandler: HX711
- Schrauben: 2x M5x20mm / 2x M4x20mm
- diverse Jumperkabel
- Steckboard
- additiv gefertigte Halterung für Wägezelle

### Verwendete Bibliotheken:
- HX711  
- ESPAsyncWebServer 
- AsyncElegantOTA
- ESP8266 Influxdb

### Pinbelegung ESP32

- GPIO 33 = DT data 
- GPIO 32 = SCK clock

![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/Steckbrett_1.jpg?raw=true)

![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/HX711.jpg?raw=true)

![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/ESP32.jpg?raw=true)

### Kalibrierfaktor bestimmen
Für eine aussagekräftige Gewichtsausgabe wurde zunächst der Kalibrierfaktor der Wägezelle mittels Normgewicht (100g) bestimmt. 
Kalibrierfaktor = angezeigter Wert 48466 / 100g 

-> der Kalibrierfaktor wurde im Programmcode ergänzt:

```scale.set_scale(48466/100);```

Um die Richtigkeit des Kalibrierungsfaktor zu überprüfen wurde anschließend das Normgewicht mit einer Präzisionswaage und der Wägezelle gemessen und der Wert miteinander verglichen. Der Unterschied zwischen den beiden Messungen war 0,05g.

### Web Server Anwendung

Folgende Website visualisiert das Filamentgewicht auf 0,01g genau und aktualisiert die Messung alle 5 Sekunden. 
Mittels Tara Button kann der aktuelle Gewichtswert tariert werden. Dies ist nur notwendig, wenn eine neue Filamentspule mit einer neuen Rolle verwendet wird. 
Desweiteren kann die Firmware des Microcontoller über Over-the-Air-Update aktualisiert werden [Link](10.0.8.146/update)

Screenshot der Webseite:
![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/Website.JPG?raw=true)

### Halterung der Waage

Die Halterung der Waage wurde durch 3D Druck hergestellt und anschließend mit M5 und M4 Schrauben an der Wägezelle montiert.

([Link zu 3D Daten](3D))

Grün: Halterung / Orange: Auflage Spule
![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/3D_Konzept.jpg?raw=true)

### Challenges

- Beispielcode des HX711 Wandlers enthält Befehle, welche diesen einerseits regelmäßig in Sleep Mode versetzt, die CPU verlangsamt und das Programm bei Einbindung des Webservers zum Absturz bringt
- Lötstellen mehrfach ausgerissen
- Entfernen der Stützstruktur der additiv gefertigten Halterung
- Mangelnde Genauigkeit der gedruckten Teile machten intensive Nacharbeit notwendig
- Gewichtszunahme am ruhenden Objekt durch Wärmeausdehnung: +0,9g nach 23min 28s

![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/Gewichtszunahme_neu.JPG?raw=true)

Bei einem Probedruck eines ca. 1,5g schweren Deckels ist eine eine Zunahme des angezeigten Gewichtswerts sichtbar, wobei nach Ende des Drucks die Gewichtszunahme bei a. 4g war. Der Druck wurde um 18:08 gestartet und endete um 18:28.
![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/Druckversuch.JPG?raw=true)

Mögliche Ursachen für die Zunahme sind möglich:
- Aufgrund des Filamentvorschubs am 3D Drucker entstehen Zugkraft an der Filamentspule 
  - mögliche Lösung: andere Zuführung des Filaments, ggf Umlenkung
- Die Filamentspule ist unwucht, wodurch die großen Sprünge bei der Messung entstehen
- Zu geringe Gewichtsabnahme des Filaments, daher 

### Fazit

Theoretisch ist die Filamentwaage in der Lage auf 0,01g genau zu gemessen. In der Praxis sind Schwankungen bei ruhiggelagerten Objekten von mind. 0,2g zu beobachten. Für die oben beschriebene Anwendung ist dies jedoch vernachlässigbar.

Im folgenden Graph sind zwei Linien zu erkennen: 
Die grüne Linie visualisiert eine Messung, die gelbe Linie den Mittelwert aus 10 Messungen darstellt. Durch die Berechnung des Mittelwertes können große Messabweichungen eleminiert und die Messkurve geglättet werden.

![alt text](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/Mittelwert_neu.JPG?raw=true)

Um eine aussagekräftige Gewichtsmessung zu erhalten, muss die Wägezelle vor Inbetriebnahme auf Raumtemperatur gebracht werden. 

Für ein aussagekräftiges Ergebnis des Projekts muss noch eine Langzeit während eines Drucks gemacht werden.

Aufbau der Filamentwaage am Ender 3 Pro.
![Aufbau am Ender 3 Pro](https://github.com/raphi2/Filamentwaage/blob/master/Fotos/Foto_1.jpg?raw=true)

#### Mögliche Verbesserungen

- andere Zuführung des Filaments, ggf Umlenkung
- widerstandsarme Lagerung der Filamentspult, durch bspw. Kugellager
- Integration eines Grafen auf der Webseite, zur Darstellung des Gewichts über eine bestimmte Zeitperiode
- Algorithmus implementieren, der die Messabweichungen während des Drucks kompensiert
- Algorithmus implementieren, der den nächsten Wechsel der Filamentspule vorrausagt


