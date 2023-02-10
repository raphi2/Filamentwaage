/**
Filamentwaage für 3D Drucker
Idee und Umsetzung: Bader Raphael, Brockschmidt Sophia, Moser Anna
Wurde im Zuge der SPS Winterchallenge 2022/23 an der FH Kufstein erarbeitet
**/

//import of libraries
#include <Arduino.h>
#include <HX711.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <AsyncTCP.h>

//InfluxDB library and definitions
#define DEVICE "ESP32"
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#include <InfluxDbClient.h>

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 33;
const int LOADCELL_SCK_PIN = 32;

// Replace with your network credentials
const char* ssid = "FH_MEDIEN";
const char* password = "P##96bCqXYuuF*e";

// InfluxDB URL
#define INFLUXDB_URL "http://217.160.37.170:8086"
// InfluxDB Name
#define INFLUXDB_DB_NAME "dbSPS22"
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_DB_NAME);

// Data point in InfluxDB
Point sensor("Wägezelle Ender 3 Pro");

// Set InfluxDB 1 authentication parameter
#define INFLUXDB_USER "SPS22"
#define INFLUXDB_PASSWORD "@home2learn"

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

//Definition of scale variable
HX711 scale;

// Code for HTML Webseite
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .gewicht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
    button {
      background-color: #034078;
      border: none;
      padding: 14px 20px;
      text-align: center;
      font-size: 20px;
      border-radius: 4px;
      transition-duration: 0.4s;
      color: white;
      cursor: pointer;
    }
    button:hover {
      background-color: #1282A2;
    }
  </style>
</head>

<body>
  <h2>Filamentwaage</h2>
  <p>
    <span class="gewicht-labels">Gewicht</span>
    <span id="gewicht">%GEWICHT%</span>
    <span class="gewicht-labels">g</span>
  </p>
  <button onclick="reverseDirection()">TARA</button>


</body>
<script>

function reverseDirection(){
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/button?value=", true);
  xhr.send();
}

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("gewicht").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/gewicht", true);
  xhttp.send();
}, 10000 ) ;

</script>
</html>)rawliteral";

// Replaces placeholder with weight values
String processor(const String& var){
  //Serial.println(var);
  if(var == "GEWICHT"){
    return "Bitte warten";
  }
  return String();
}

void setup() {

  Serial.begin(115200);

  // InfluxDB connection
  // Connect WiFi - Influx DB
  Serial.println("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(ssid, password);
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();

  // Set InfluxDB 1 authentication params
  client.setConnectionParamsV1(INFLUXDB_URL, INFLUXDB_DB_NAME, INFLUXDB_USER, INFLUXDB_PASSWORD);

  // Add constant tags - only once
  sensor.addTag("device", DEVICE);
  sensor.addTag("SSID", WiFi.SSID());

  // Check server connection
  if (client.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/gewicht", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(scale.get_units()).c_str());
  });

  // Send a GET request to Tare Button - Scale Tare
  server.on("/button", HTTP_GET, [](AsyncWebServerRequest *request){
    scale.tare();               // reset the scale to 0
    });

  // Start server
  server.begin();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! I am ESP32.");
  });

  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");

  Serial.println("Initializing the scale");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());      // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));   // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided
            // by the SCALE parameter (not set yet)
           
  scale.set_scale(48466/100); // this value is obtained by calibrating the scale with known weights; see the README for details                  
  scale.tare();               // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
            // by the SCALE parameter set with set_scale

  Serial.println("Readings:");
}

void loop() {

  // Sensor data Output to console
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10), 5);

  // Store measured value into point
  sensor.clearFields();
  sensor.addField("Gewicht", scale.get_units()); //store measurement of 1 reading into Database
  sensor.addField("Mittelwelt", scale.get_units(10)); //store the average of 10 readings into Database

  // Print what are we exactly writing
  Serial.print("Writing: ");
  Serial.println(client.pointToLineProtocol(sensor));

  // If no Wifi signal, try to reconnect it
  if (wifiMulti.run() != WL_CONNECTED) {
    Serial.println("Wifi connection lost");
  }
  // Write point
  if (!client.writePoint(sensor)) {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }
  
  delay(5000);
}

