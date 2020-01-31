#include <IOXhop_FirebaseESP32.h>
#include <WiFi.h>
#include <PubSubClient.h>

//WebServer Server;

long lastReconnectAttempt = 0;

#define LED1 18
#define LED2 5
#define LED3 23
#define LED4 22
#define LED5 16
#define LED6 17
#define LED7 19
#define LED8 21
#define LED9 34

#define Touch1 T0   //4
#define Touch2 T3   //15
#define Touch3 T4   //13
#define Touch4 T5   //12
#define Touch5 T6   //14
#define Touch6 T7   //27
#define Touch7 T9   //33
#define Touch8 T8   //32
#define Touch9 T9   //32

int touch1, touch2, touch3, touch4, touch5, touch6, touch7, touch8, touch9;
boolean a = true;
boolean b = true;
boolean c = true;
boolean d = true;
boolean e = true;
boolean f = true;
boolean g = true;
boolean h = true;
boolean j = true;

const char* ssid = "BANG-LAW WALA";
const char* password = "home@home";

//Enter your mqtt server configurations
const char* mqttServer = "soldier.cloudmqtt.com";    //Enter Your mqttServer address
const int mqttPort =   18166;       //Port number
const char* mqttUser = "dtsghhrn"; //User
const char* mqttPassword = "ycDpcGIFTmK4"; //Password

#define FIREBASE_HOST "status-22e54.firebaseio.com"                     //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "j1VnVtCV7pUbTT40EjgxO4PqMdI9kO1ErfSckhlb"       //Your Firebase Database Secret goes here

WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
  Serial.begin(115200);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);
  pinMode(LED9, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Connecting to WiFi..");
    dloop();
  }
  Serial.print("Connected to WiFi :");
  Serial.println(WiFi.SSID());

  client.setServer(mqttServer, mqttPort);
  client.setCallback(MQTTcallback);

  lastReconnectAttempt = 0;

  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
}

void firebasereconnect()
{
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
  Serial.println("Trying to reconnect");
  ESP.restart(); 
  delay(1000);
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

  if (message == "#relay1on")
  {
    Serial.println("Relay 1 on from Web Socket");
    digitalWrite(LED1, 0);
    a=true;
  }
  if (message == "#relay1off")
  {
    Serial.println("Relay 1 off from Web Socket");
    digitalWrite(LED1, 1);
    a=false;
  }

  if (message == "#relay2on")
  {
    Serial.println("Relay 2 on from Web Socket");
    digitalWrite(LED2, 0);
    b=true;
  }
  if (message == "#relay2off")
  {
    Serial.println("Relay 2 off from Web Socket");
    digitalWrite(LED2, 1);
    b=false;
  }

  if (message == "#relay3on")
  {
    Serial.println("Relay 3 on from Web Socket");
    digitalWrite(LED3, 0);
    c=true;
  }
  if (message == "#relay3off")
  {
    Serial.println("Relay 3 off from Web Socket");
    digitalWrite(LED3, 1);
    c=false;
  }

  if (message == "#relay4on")
  {
    Serial.println("Relay 4 on from Web Socket");
    digitalWrite(LED4, 0);
    d=true;
  }
  if (message == "#relay4off")
  {
    Serial.println("Relay 4 off from Web Socket");
    digitalWrite(LED4, 1);
    d=false;
  }

  if (message == "#relay5on")
  {
    Serial.println("Relay 5 on from Web Socket");
    digitalWrite(LED5, 0);
    e=true;
  }
  if (message == "#relay5off")
  {
    Serial.println("Relay 5 off from Web Socket");
    digitalWrite(LED5, 1);
    e=false;
  }

  if (message == "#relay6on")
  {
    Serial.println("Relay 6 on from Web Socket");
    digitalWrite(LED6, 0);
    f=true;
  }
  if (message == "#relay6off")
  {
    Serial.println("Relay 6 off from Web Socket");
    digitalWrite(LED6, 1);
    f=false;
  }

  if (message == "#relay7on")
  {
    Serial.println("Relay 7 on from Web Socket");
    digitalWrite(LED7, 0);
    g=true;
  }
  if (message == "#relay7off")
  {
    Serial.println("Relay 7 off from Web Socket");
    digitalWrite(LED7, 1);
    g=false;
  }

  if (message == "#relay8on")
  {
    Serial.println("Relay 8 on from Web Socket");
    digitalWrite(LED8, 0);
    h=true;
  }
  if (message == "#relay8off")
  {
    Serial.println("Relay 8 off from Web Socket");
    digitalWrite(LED8, 1);
    h=false;
  }

  Serial.println();
  Serial.println("-----------------------");
}

boolean reconnect()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Connecting to WiFi..");
    dloop();
  }
  Serial.println("Reconnecting to mqtt");
  if (client.connect("ckekwtxs", mqttUser, mqttPassword ))
  {
    // Once connected, publish an announcement...
    client.publish("esp/test", "Hello From Wemos D1");
    client.subscribe("esp/test");
  }
  return client.connected();
}

void loop()
{
  if (!client.connected())
  {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
      Serial.println("Connecting to WiFi..");
      dloop();
    }
   
    Serial.println("mqtt NOT connected");
    long now = millis();
    if (now - lastReconnectAttempt > 1000)
    {
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (reconnect())
      {
        lastReconnectAttempt = 0;
      }
    }
  }
  else
  {
    // Client connected
    client.loop();
  }
 
  dloop();
}

void dloop()
{
  touch9 = touchRead(Touch9);  // dummy loop start
  Serial.println(touch9);
  if (touch9 < 40)
  {
    if (j == false)
    {
      digitalWrite(LED9, HIGH);
      Serial.println("light 9 OFF from touch sensor");
      client.publish("esp/testStatus", "#relay9on");
      j = true;
      delay(300);
    }
    else if (j == true)
    {
      digitalWrite(LED9, LOW);
      Serial.println("light 9 ON from touch sensor");
      client.publish("esp/testStatus", "#relay9off");
      j = false;
      delay(300);
    }
  }                          // dummy loop end
   
  touch1 = touchRead(Touch1);
  Serial.println(touch1);

  if (touch1 < 40)
  {
    if (a == false)
    {
      digitalWrite(LED1, LOW);
      Serial.println("light 1 OFF from touch sensor");
      client.publish("esp/testStatus", "#relay1on");
      Firebase.setString("Member/D1Status","D1 On");
      a = true;
      delay(300);
    }
    else if (a == true)
    {
      digitalWrite(LED1, HIGH);
      Serial.println("light 1 ON from touch sensor");
      client.publish("esp/testStatus", "#relay1off");
      Firebase.setString("Member/D1Status","D1 Off");
      a = false;
      delay(300);
    }
  }

  touch2 = touchRead(Touch2);
  Serial.println(touch2);

  if (touch2 < 40)
  {
    if (b == false)
    {
      digitalWrite(LED2, LOW);
      Serial.println("light 2 OFF from touch sensor");
      client.publish("esp/testStatus", "#relay2on");
      Firebase.setString("Member/D2Status","D2 On");
      b = true;
      delay(300);
    }
    else if (b == true)
    {
      digitalWrite(LED2, HIGH);
      Serial.println("light 2 ON from touch sensor");
      client.publish("esp/testStatus", "#relay2off");
      Firebase.setString("Member/D2Status","D2 Off");
      b = false;
      delay(300);
    }
  }

  touch3 = touchRead(Touch3);
  Serial.println(touch3);

  if (touch3 < 40)
  {
    if ( c == false)
    {
      digitalWrite(LED3, LOW);
      Serial.println("light 3 OFF from touch sensor");
      client.publish("esp/testStatus", "#relay3on");
      Firebase.setString("Member/D3Status","D3 On");
      c = true;
      delay(300);
    }
    else if (c == true)
    {
      digitalWrite(LED3, HIGH);
      Serial.println("light 3 ON from touch sensor");
      client.publish("esp/testStatus", "#relay3off");
      Firebase.setString("Member/D3Status","D3 Off");
      c = false;
      delay(300);
    }
  }

  touch4 = touchRead(Touch4);
  Serial.println(touch4);

  if (touch4 < 40)
  {
    if (d == false)
    {
      digitalWrite(LED4, LOW);
      Serial.println("light 4 OFF from touch sensor");
      client.publish("esp/testStatus", "#relay4on");
      Firebase.setString("Member/D4Status","D4 On");
      d = true;
      delay(300);
    }
    else if (d == true)
    {
      digitalWrite(LED4, HIGH);
      Serial.println("light 4 ON from touch sensor");
      client.publish("esp/testStatus", "#relay4off");
      Firebase.setString("Member/D4Status","D4 Off");
      d = false;
      delay(300);
    }
  }

  touch5 = touchRead(Touch5);
  Serial.println(touch5);

  if (touch5 < 40)
  {
    if (e == false)
    {
      digitalWrite(LED5, LOW);
      Serial.println("light 5 OFF from touch sensor");
      client.publish("esp/testStatus", "#relay5on");
      Firebase.setString("Member/D5Status","D5 On");
      e = true;
      delay(300);
    }
    else if (e == true)
    {
      digitalWrite(LED5, HIGH);
      Serial.println("light 5 ON from touch sensor");
      client.publish("esp/testStatus", "#relay5off");
      Firebase.setString("Member/D5Status","D5 Off");
      e = false;
      delay(300);
    }
  }

  touch6 = touchRead(Touch6);
  Serial.println(touch6);

  if (touch6 < 40)
  {
    if ( f == false)
    {
      digitalWrite(LED6, LOW);
      Serial.println("light 6 OFF from touch sensor");
      client.publish("esp/testStatus", "#relay6on");
      Firebase.setString("Member/D6Status","D6 On");
      f = true;
      delay(300);
    }
    else if (f == true)
    {
      digitalWrite(LED6, HIGH);
      Serial.println("light 6 ON from touch sensor");
      client.publish("esp/testStatus", "#relay6off");
      Firebase.setString("Member/D6Status","D6 Off");
      f = false;
      delay(300);
    }
  }

  touch7 = touchRead(Touch7);
  Serial.println(touch7);

  if (touch7 < 40)
  {
    if (g == false)
    {
      digitalWrite(LED7, LOW);
      Serial.println("light 7 OFF from touch sensor");
      client.publish("esp/testStatus", "#relay7on");
      Firebase.setString("Member/D7Status","D7 On");
      g = true;
      delay(300);
    }
    else if (g == true)
    {
      digitalWrite(LED7, HIGH);
      Serial.println("light 7 ON from touch sensor");
      client.publish("esp/testStatus", "#relay7off");
      Firebase.setString("Member/D7Status","D7 Off");
      g = false;
      delay(300);
    }
  }

  touch8 = touchRead(Touch8);
  Serial.println(touch8);

  if (touch8 < 40)
  {
    if (h == false)
    {
      digitalWrite(LED8, LOW);
      Serial.println("light 8 OFF from touch sensor");
      client.publish("esp/testStatus", "#relay8on");
      Firebase.setString("Member/D8Status","D8 On");
      h = true;
      delay(300);
    }
    else if (h == true)
    {
      digitalWrite(LED8, HIGH);
      Serial.println("light 8 ON from touch sensor");
      client.publish("esp/testStatus", "#relay8off");
      Firebase.setString("Member/D8Status","D8 Off");
      h = false;
      delay(300);
    }
  }
}
