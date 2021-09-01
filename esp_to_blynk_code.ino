
#define BLYNK_PRINT Serial

#include <passwordblynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#include<SoftwareSerial.h>        // Library for Serial communication
SoftwareSerial SUART(4, 5);       // SRX=Dpin-D2; STX-DPin-D1
passwordblynk wifi;

Servo servo;
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "Ov46jhsAI_92u8rCqfcibryZx3G-8hon";
void runidc();
String str;
float temp;
//float tmp=12.45;
//int mp=34;
// Your WiFi credentials.
// Set password to "" for open networks.
const char* ssid = wifi.getssid();
const char* pass = wifi.getpass();
BlynkTimer timer; //announcing the timer
// Use Virtual pin 5 for uptime display
#define PIN_UPTIME V5

// This function tells Arduino what to do if there is a Widget
// which is requesting data for Virtual Pin (5)ee
void runidc()
{
  // This command writes Arduino's uptime in seconds to Virtual Pin (5)
 
  Blynk.virtualWrite(V5, temp);
  
}
BLYNK_WRITE(V3)
{
   servo.write(param.asInt());
}

//BLYNK_WRITE(V4)
//{
 // servo.write(0);
//}
//BLYNK_WRITE(V6)
//{
//  servo.write(90);
//}
void setup(){
  // Debug console
   servo.attach(15); // NodeMCU D8 pin
  SUART.begin(115200);
  Serial.begin(115200);
timer.setInterval(1000L, runidc);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  while (!Serial) {
 // wait for serial port to connect. Needed for native USB port only
}
}


void loop(){
if (SUART.available()) {
SUART.write(SUART.read());
str=SUART.readStringUntil('\n');

temp=str.toFloat();
Serial.println(temp);

 }
  Blynk.run();
  timer.run();

}
