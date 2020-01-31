#include <WiFi.h>
#include <PubSubClient.h>
#include<FirebaseArduino.h>
#include <IRsend.h>
#define IR D7

const uint16_t kIrLed = D7;  
IRsend irsend(kIrLed);

#define FIREBASE_HOST "smartswitch1.firebaseio.com"                     //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "dQyG9jeXv5XQHfHmY7V59h8aQT7rZIcvVmSK8RXE"       //Your Firebase Database Secret goes here

int hallTemp, b1Temp,b2Temp,b3Temp,kitchenTemp;
int hallT = A0;
int b1T = A1;
int b2T = A2;
int b3T = A3;
int kitchenT = A4;

WebServer Server;

const char* ssid = "BANG-LAW WALA";
const char* password =  "home@home";

//Enter your mqtt server configurations
const char* mqttServer = "soldier.cloudmqtt.com";    //Enter Your mqttServer address
const int mqttPort =   18166;       //Port number
const char* mqttUser = "dtsghhrn"; //User
const char* mqttPassword = "ycDpcGIFTmK4"; //Password

WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
  Serial.begin(115200);
  
  irsend.begin();
  pinMode(IR,OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.print("Connected to WiFi :");
  Serial.println(WiFi.SSID());

  client.setServer(mqttServer, mqttPort);
  client.setCallback(MQTTcallback);

  while (!client.connected()) 
  {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP8266", mqttUser, mqttPassword )) 
    {
      Serial.println("connected");  
    } 
    else 
    {
      Serial.print("failed with state ");
      Serial.println(client.state());  //If you get state 5: mismatch in configuration
      setup();
      delay(2000);
    }
  }
  client.publish("esp/test", "Hello From Micro-controller");
  client.subscribe("esp/test");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void MQTTcallback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  Serial.print("Message:");

  String message;
  for (int i = 0; i < length; i++)
  {
    message = message + (char)payload[i];  //Conver *byte to String
  }

  Serial.print(message);

  if (message == "#gtp")
  {
    uint16_t d1[67] = {9040, 4524,  550, 560,  550, 1696,  548, 560,  550, 560,  548, 560,  550, 560,  550, 560,  550, 560,  550, 1696,  550, 560,  550, 1696,  550, 1696,  548, 1696,  550, 1696,  548, 1696,  550, 1696,  548, 560,  548, 560,  550, 560,  550, 1694,  550, 560,  550, 560,  550, 1696,  548, 560,  550, 1696,  548, 1696,  548, 1696,  550, 560,  550, 1696,  550, 1696,  550, 560,  550, 1696,  550};  // NEC 40BF12ED
    irsend.sendRaw(d1, 67, 38);  // Send a raw data capture at 38kHz.
    Serial.println("Ground Floor Temp One Plus");
    delay(1);
  }
  if (message == "#gtm")
  {
    uint16_t d2[67] = {9052, 4524,  550, 560,  550, 1696,  552, 560,  550, 560,  550, 560,  550, 560,  550, 560,  552, 560,  550, 1696,  552, 560, 560,  550, 560,  550, 1696,  550, 560,  550, 1696,  550, 1696,  548, 1696,  550, 1696,  548, 1696,  550, 1696,  548, 560,  548, 560,  550, 560,  550, 1694,  550, 560,  550, 560,  550, 1696,  548, 560,  550, 1696,  548, 1696,  548, 1696,  550, 560,  550, 1696,  550, 1696,  550, 560,  550, 1696,  550};  // NEC 40BF12ED
    irsend.sendRaw(d1, 67, 38);  // Send a raw data capture at 38kHz.
    Serial.println("Ground Floor Temp One Minus");
    delay(1);
  }

  if (message == "#ffp")
  {
    uint16_t d1[67] = {9040, 4524,  550, 560,  550, 1696,  548, 560,  550, 560,  548, 560,  550, 560,  550, 560,  550, 560,  550, 1696,  550, 560,  550, 1696,  550, 1696,  548, 1696,  550, 1696,  548, 1696,  550, 1696,  548, 560,  548, 560,  550, 560,  550, 1694,  550, 560,  550, 560,  550, 1696,  548, 560,  550, 1696,  548, 1696,  548, 1696,  550, 560,  550, 1696,  550, 1696,  550, 560,  550, 1696,  550};  // NEC 40BF12ED
    irsend.sendRaw(d1, 67, 38);  // Send a raw data capture at 38kHz.
    Serial.println("First Floor Temp One Plus");
    delay(1);
  }
  if (message == "#ffm")
  {
    uint16_t d2[67] = {9052, 4524,  550, 560,  550, 1696,  552, 560,  550, 560,  550, 560,  550, 560,  550, 560,  552, 560,  550, 1696,  552, 560, 560,  550, 560,  550, 1696,  550, 560,  550, 1696,  550, 1696,  548, 1696,  550, 1696,  548, 1696,  550, 1696,  548, 560,  548, 560,  550, 560,  550, 1694,  550, 560,  550, 560,  550, 1696,  548, 560,  550, 1696,  548, 1696,  548, 1696,  550, 560,  550, 1696,  550, 1696,  550, 560,  550, 1696,  550};  // NEC 40BF12ED
    irsend.sendRaw(d1, 67, 38);  // Send a raw data capture at 38kHz.
    Serial.println("First Floor Temp One Minus");
    delay(1);
  }

  if (message == "#sfp")
  {
    uint16_t d1[67] = {9040, 4524,  550, 560,  550, 1696,  548, 560,  550, 560,  548, 560,  550, 560,  550, 560,  550, 560,  550, 1696,  550, 560,  550, 1696,  550, 1696,  548, 1696,  550, 1696,  548, 1696,  550, 1696,  548, 560,  548, 560,  550, 560,  550, 1694,  550, 560,  550, 560,  550, 1696,  548, 560,  550, 1696,  548, 1696,  548, 1696,  550, 560,  550, 1696,  550, 1696,  550, 560,  550, 1696,  550};  // NEC 40BF12ED
    irsend.sendRaw(d1, 67, 38);  // Send a raw data capture at 38kHz.
    Serial.println("Second Floor Temp One Plus");
    delay(1);
  }
  if (message == "#sfm")
  {
    uint16_t d2[67] = {9052, 4524,  550, 560,  550, 1696,  552, 560,  550, 560,  550, 560,  550, 560,  550, 560,  552, 560,  550, 1696,  552, 560, 560,  550, 560,  550, 1696,  550, 560,  550, 1696,  550, 1696,  548, 1696,  550, 1696,  548, 1696,  550, 1696,  548, 560,  548, 560,  550, 560,  550, 1694,  550, 560,  550, 560,  550, 1696,  548, 560,  550, 1696,  548, 1696,  548, 1696,  550, 560,  550, 1696,  550, 1696,  550, 560,  550, 1696,  550};  // NEC 40BF12ED
    irsend.sendRaw(d1, 67, 38);  // Send a raw data capture at 38kHz.
    Serial.println("Second Floor Temp One Minus");
    delay(1);
  }

  if (message == "#tfp")
  {
    uint16_t d1[67] = {9040, 4524,  550, 560,  550, 1696,  548, 560,  550, 560,  548, 560,  550, 560,  550, 560,  550, 560,  550, 1696,  550, 560,  550, 1696,  550, 1696,  548, 1696,  550, 1696,  548, 1696,  550, 1696,  548, 560,  548, 560,  550, 560,  550, 1694,  550, 560,  550, 560,  550, 1696,  548, 560,  550, 1696,  548, 1696,  548, 1696,  550, 560,  550, 1696,  550, 1696,  550, 560,  550, 1696,  550};  // NEC 40BF12ED
    irsend.sendRaw(d1, 67, 38);  // Send a raw data capture at 38kHz.
    Serial.println("Third Floor Temp One Plus");
    delay(1);
  }
  if (message == "#tfm")
  {
    uint16_t d2[67] = {9052, 4524,  550, 560,  550, 1696,  552, 560,  550, 560,  550, 560,  550, 560,  550, 560,  552, 560,  550, 1696,  552, 560, 560,  550, 560,  550, 1696,  550, 560,  550, 1696,  550, 1696,  548, 1696,  550, 1696,  548, 1696,  550, 1696,  548, 560,  548, 560,  550, 560,  550, 1694,  550, 560,  550, 560,  550, 1696,  548, 560,  550, 1696,  548, 1696,  548, 1696,  550, 560,  550, 1696,  550, 1696,  550, 560,  550, 1696,  550};  // NEC 40BF12ED
    irsend.sendRaw(d1, 67, 38);  // Send a raw data capture at 38kHz.
    Serial.println("Third Floor Temp One Minus");
    delay(1);
  }

  if (message == "#pp")
  {
    uint16_t d1[67] = {9040, 4524,  550, 560,  550, 1696,  548, 560,  550, 560,  548, 560,  550, 560,  550, 560,  550, 560,  550, 1696,  550, 560,  550, 1696,  550, 1696,  548, 1696,  550, 1696,  548, 1696,  550, 1696,  548, 560,  548, 560,  550, 560,  550, 1694,  550, 560,  550, 560,  550, 1696,  548, 560,  550, 1696,  548, 1696,  548, 1696,  550, 560,  550, 1696,  550, 1696,  550, 560,  550, 1696,  550};  // NEC 40BF12ED
    irsend.sendRaw(d1, 67, 38);  // Send a raw data capture at 38kHz.
    Serial.println("Parking Temp One Plus");
    delay(1);
  }
  if (message == "#pm")
  {
    uint16_t d2[67] = {9052, 4524,  550, 560,  550, 1696,  552, 560,  550, 560,  550, 560,  550, 560,  550, 560,  552, 560,  550, 1696,  552, 560, 560,  550, 560,  550, 1696,  550, 560,  550, 1696,  550, 1696,  548, 1696,  550, 1696,  548, 1696,  550, 1696,  548, 560,  548, 560,  550, 560,  550, 1694,  550, 560,  550, 560,  550, 1696,  548, 560,  550, 1696,  548, 1696,  548, 1696,  550, 560,  550, 1696,  550, 1696,  550, 560,  550, 1696,  550};  // NEC 40BF12ED
    irsend.sendRaw(d1, 67, 38);  // Send a raw data capture at 38kHz.
    Serial.println("Parking Temp One Minus");
    delay(1);
  }
  
  Serial.println();
  Serial.println("-----------------------");
}

void loop()
{
  if (!client.connected())
  {
    client.connect("ESP8266", mqttUser, mqttPassword );
  }
  client.loop();

  // read data from sensor
  hallTemp = analogRead(hallT);
  float mv1 = ( hallTemp/1024.0)*5000;
  float cel1 = mv1/10;
  float farh1 = (cel1*9)/5 + 32;

  b1Temp = analogRead(b1T);
  float mv2 = ( b1Temp/1024.0)*5000;
  float cel2 = mv2/10;
  float farh2 = (cel2*9)/5 + 32;

  b2Temp = analogRead(b2T);
  float mv3 = ( b2Temp/1024.0)*5000;
  float cel3 = mv3/10;
  float farh3 = (cel3*9)/5 + 32;

  b3Temp = analogRead(b3T);
  float mv4 = ( b3Temp/1024.0)*5000;
  float cel4 = mv4/10;
  float farh4 = (cel4*9)/5 + 32;

  kitchenTemp = analogRead(kitchenT);
  float mv5 = ( kitchenTemp/1024.0)*5000;
  float cel5 = mv5/10;
  float farh5 = (cel5*9)/5 + 32; 

  // set value
  Firebase.setFloat("HVAC/hallTemp", cel1);
  Firebase.setFloat("HVAC/b1Temp", cel2);
  Firebase.setFloat("HVAC/b2Temp", cel3);
  Firebase.setFloat("HVAC/b3Temp", cel4);
  Firebase.setFloat("HVAC/kitchenTemp", cel5);
  
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(100);
}
