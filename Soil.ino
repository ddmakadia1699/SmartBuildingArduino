#include <WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "example.firebaseio.com"
#define FIREBASE_AUTH "token_or_secret"
#define WIFI_SSID "Makadia`s"
#define WIFI_PASSWORD "kidd123456789"

int sensorPin = A0; 
int sensorPin2 = A1; 
int sensorPin3 = A2; 
int sensorPin4 = A3; 

int sensorValue,sensorValue2,sensorValue3,sensorValue4;  
int limit = 300; 

void firebasereconnect()
{
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
  Serial.println("Trying to reconnect");
  ESP.restart(); 
  delay(1000);
} 


void setup() 
{
 Serial.begin(9600);
 WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {

 sensorValue = analogRead(sensorPin); 
 sensorValue2 = analogRead(sensorPin2); 
 sensorValue3 = analogRead(sensorPin3); 
 sensorValue4 = analogRead(sensorPin4);
  
 Serial.println(sensorValue);
 Serial.println(sensorValue2);
 Serial.println(sensorValue3);
 Serial.println(sensorValue4);
 
 Firebase.setString("Soil/Block_A", sensorValue);
 Firebase.setString("Soil/Block_B", sensorValue2);
 Firebase.setString("Soil/Block_C", sensorValue3);
 Firebase.setString("Soil/Block_D", sensorValue4);
 
 delay(1000); 
}
