#include <WiFi.h>
#include <FirebaseArduino.h>

const int trigPin = 1;
const int echoPin = 2;

long duration;
int distance;

// Set these to run example.
#define FIREBASE_HOST "example.firebaseio.com"
#define FIREBASE_AUTH "token_or_secret"

#define WIFI_SSID "Makadia`s"
#define WIFI_PASSWORD "kidd123456789"

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

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  // connect to wifi.
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

void loop() 
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  
  // set value
  if(0 < distance < 20)
  {
    Firebase.setString("Tank Status/Status", "20");  
  }
  if(20 < distance < 30)
  {
    Firebase.setString("Tank Status/Status", "30");  
  }
  if(30 < distance < 50)
  {
    Firebase.setString("Tank Status/Status", "50");  
  }
  if(50 < distance < 60)
  {
    Firebase.setString("Tank Status/Status", "60");  
  }
  if(60 < distance < 80)
  {
    Firebase.setString("Tank Status/Status", "80");  
  }
  if(80 < distance < 90)
  {
    Firebase.setString("Tank Status/Status", "90");  
  }
  if(90 < distance < 100)
  {
    Firebase.setString("Tank Status/Status", "100");  
  }
  else
  {
    Firebase.setString("Tank Status/Status", "E");   
  }
}
