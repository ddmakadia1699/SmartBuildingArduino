#include <WiFi.h>
#include <FirebaseArduino.h>

const int trigPin = 1;
const int echoPin = 2;
const int trigPin2 = 3;
const int echoPin2 = 4;
const int trigPin3 = 5;
const int echoPin3 = 6;
const int trigPin4 = 7;
const int echoPin4 = 8;
const int trigPin5 = 9;
const int echoPin5 = 10;
const int trigPin6 = 11;
const int echoPin6 = 12;

// defines variables
long duration,duration2,duration3,duration4,duration5,duration6;
int distance,distance2,distance3,distance4,distance5,distance6;

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
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin3, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin3, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin4, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin4, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin5, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin5, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin6, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin6, INPUT); // Sets the echoPin as an Input

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
  if(distance < 10)
  {
    Firebase.setString("Parking/P1", "0");  
  }
  else
  {
    Firebase.setString("Parking/P1", "1");   
  }

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance2);
  
  // set value
  if(distance2 < 10)
  {
    Firebase.setString("Parking/P2", "0");  
  }
  else
  {
    Firebase.setString("Parking/P2", "1");   
  }

  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = duration3*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance3);
  
  // set value
  if(distance3 < 10)
  {
    Firebase.setString("Parking/P3", "0");  
  }
  else
  {
    Firebase.setString("Parking/P3", "1");   
  } 

  digitalWrite(trigPin4, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin4, LOW);
  duration4 = pulseIn(echoPin4, HIGH);
  distance4 = duration4*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance4);
  
  // set value
  if(distance4 < 10)
  {
    Firebase.setString("Parking/P4", "0");  
  }
  else
  {
    Firebase.setString("Parking/P4", "1");   
  }  

  digitalWrite(trigPin5, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin5, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin5, LOW);
  duration5 = pulseIn(echoPin5, HIGH);
  distance5 = duration5*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance5);
  
  // set value
  if(distance5 < 10)
  {
    Firebase.setString("Parking/P5", "0");  
  }
  else
  {
    Firebase.setString("Parking/P5", "1");   
  }

  digitalWrite(trigPin6, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin6, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin6, LOW);
  duration6 = pulseIn(echoPin6, HIGH);
  distance6 = duration6*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance6);
  
  // set value
  if(distance6 < 10)
  {
    Firebase.setString("Parking/P6", "0");  
  }
  else
  {
    Firebase.setString("Parking/P6", "1");   
  }
  
  // handle error
  if (Firebase.failed()) 
  {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      firebasereconnect();
      return;
  }
  delay(100);
}
