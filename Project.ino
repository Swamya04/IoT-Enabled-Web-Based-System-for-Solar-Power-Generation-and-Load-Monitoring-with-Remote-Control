#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Major Project 2026"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <WebServer.h>
#include <WebSocketsServer.h>

// WiFi details
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// Pin connections
#define CURRENT_PIN 34
#define VOLTAGE_PIN 35
#define RELAY_PIN 5

WebServer server(80);
WebSocketsServer webSocket(81);

BlynkTimer timer;

// Stores total energy consumed
float totalEnergy = 0;

// Used for energy calculation timing
unsigned long lastTime = 0;

// Current sensor offset value
float offset = 0;

// Reads voltage from voltage sensor
float readVoltage()
{
  int adc = analogRead(VOLTAGE_PIN);

  float voltage = adc * (3.3 / 4095.0) * 4.5;

  return voltage;
}

// Reads current from ACS712 sensor
float readCurrent()
{
  float raw = analogRead(CURRENT_PIN);

  float voltage = raw * (3.3 / 4095.0);

  float offsetVoltage = offset * (3.3 / 4095.0);

  float current_A = (voltage - offsetVoltage) / 0.066;

  float current_mA = current_A * 1000.0;

  return current_mA;
}

// Controls relay from Blynk app
BLYNK_WRITE(V3)
{
  digitalWrite(RELAY_PIN, param.asInt());
}

// Sends data to website and Blynk
void sendData()
{
  float voltage = readVoltage();

  float current_mA = readCurrent();

  float current_A = current_mA / 1000.0;

  float power = voltage * current_A;

  // Calculates energy usage
  unsigned long now = millis();

  totalEnergy += power * (now - lastTime) / 3600000.0;

  lastTime = now;

  // Displays values in Serial Monitor
  Serial.print("Voltage: ");
  Serial.println(voltage);

  Serial.print("Current: ");
  Serial.print(current_mA);
  Serial.println(" mA");

  Serial.print("Power: ");
  Serial.println(power);

  Serial.println("----------------");

  // Sends data to Blynk
  Blynk.virtualWrite(V0, voltage);
  Blynk.virtualWrite(V1, current_mA);
  Blynk.virtualWrite(V2, power);

  // Sends data to web dashboard
  String json = "{";

  json += "\"v\":" + String(voltage,2) + ",";
  json += "\"c\":" + String(current_mA,2) + ",";
  json += "\"p\":" + String(power,2) + ",";
  json += "\"e\":" + String(totalEnergy,2) + ",";
  json += "\"r\":" + String(digitalRead(RELAY_PIN));

  json += "}";

  webSocket.broadcastTXT(json);
}

// Toggles relay from website
void handleToggle()
{
  int state = !digitalRead(RELAY_PIN);

  digitalWrite(RELAY_PIN, state);

  Blynk.virtualWrite(V3, state);

  server.send(200, "text/plain", "OK");
}

// Main webpage
void handleRoot()
{
  String html = R"rawliteral(

<!DOCTYPE html>
<html>

<head>

<meta name="viewport" content="width=device-width, initial-scale=1">

<style>

body{
font-family:Arial;
background:white;
text-align:center;
margin:0;
}

.card{
margin:20px;
padding:20px;
}

.toggle{
width:100px;
height:100px;
border-radius:50%;
font-size:20px;
color:white;
border:none;
}

</style>

</head>

<body>

<h2>Major Project 2026</h2>

<div class="card">

<div id="v">Voltage</div>

<div id="c">Current</div>

<div id="p">Power</div>

<div id="e">Energy</div>

<button id="btn" class="toggle">--</button>

</div>

<script>

let ws = new WebSocket("ws://"+location.hostname+":81/");

ws.onmessage = function(e){

let d = JSON.parse(e.data);

document.getElementById("v").innerText = "Voltage: " + d.v + " V";

document.getElementById("c").innerText = "Current: " + d.c + " mA";

document.getElementById("p").innerText = "Power: " + d.p + " W";

document.getElementById("e").innerText = "Energy: " + d.e + " Wh";

let btn = document.getElementById("btn");

if(d.r == 1)
{
  btn.innerText = "ON";
  btn.style.background = "green";
}
else
{
  btn.innerText = "OFF";
  btn.style.background = "red";
}

};

document.getElementById("btn").onclick = function(){

fetch('/toggle');

};

</script>

</body>
</html>

)rawliteral";

  server.send(200,"text/html",html);
}

// Initial setup
void setup()
{
  Serial.begin(9600);

  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, LOW);

  analogReadResolution(12);

  analogSetAttenuation(ADC_11db);

  // Finds sensor offset value
  for(int i = 0; i < 500; i++)
  {
    offset += analogRead(CURRENT_PIN);

    delay(2);
  }

  offset /= 500;

  Serial.print("Offset Value: ");

  Serial.println(offset);

  // Connects ESP32 to WiFi
  WiFi.begin(ssid, pass);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);

    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");

  // Connects to Blynk server
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Webpage routes
  server.on("/", handleRoot);

  server.on("/toggle", handleToggle);

  server.begin();

  // Starts WebSocket communication
  webSocket.begin();

  lastTime = millis();

  // Sends data every 2 seconds
  timer.setInterval(2000L, sendData);
}

// Main loop
void loop()
{
  Blynk.run();

  timer.run();

  server.handleClient();

  webSocket.loop();
}