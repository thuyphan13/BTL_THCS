//BTL_THCS_Nhom04_Thuy_Duc

#include <WiFi.h>
#include <FirebaseESP32.h>
#include <DHT.h>
#include <math.h>

FirebaseData dulieufirebase;

#define FIREBASE_HOST "https://smarthome2023-60f1a-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "GLjY2qHvoXBEIbDWX6YCNAqeV3EFSUyV0g8YAf0s"
#define WIFI_SSID "NhaTro66-T6"
#define WIFI_PASS "12345678"

const int DHTPIN = 32;
const int DHTTYPE = DHT22;
DHT dht(DHTPIN, DHTTYPE);

const int relay1 = 26;
const int relay2 = 33;
//int dem = 0;

String firestatus1 = "";
String firestatus2 = "";

void ketnoiwifi() {
  Serial.println("Connecting to Wifi...");
  WiFi.begin("NhaTro66-T6", "12345678");
  while(!(WiFi.status() == WL_CONNECTED)){
    delay(1000);
    Serial.print("...");
  }
  Serial.println("");
  Serial.println("Wifi connected");
}

void setup() {
  Serial.begin(115200);
  ketnoiwifi();
  dht.begin();
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.setString(dulieufirebase,"THCS Nhom4 ", "SmartHome2023");
  
  Firebase.setString(dulieufirebase,"RELAY1 : ", "OFF");
  Firebase.setString(dulieufirebase,"RELAY2 : ", "OFF");    
  
}

void loop() {   
  float t = dht.readTemperature();
  float h = dht.readHumidity(); 

  Firebase.setFloat(dulieufirebase,"Tempurature = ",t);
  Firebase.setFloat(dulieufirebase,"Humidity = ",h);
  
  Serial.print(" Tempurature = ");
  Serial.println(t);
  Serial.println("°C");
  Serial.print(" Humidity = ");
  Serial.println(h);
  Serial.println("%");
  delay(2000);
  
  Firebase.getString(dulieufirebase,"RELAY1 : ");
  firestatus1 = dulieufirebase.stringData();
  if (firestatus1 == "ON" || firestatus1 == "on") {    
      Serial.println(" RELAY 1 ON!");
      digitalWrite(relay1, HIGH);
    }
    else if (firestatus1 == "OFF" || firestatus1 == "off") {            
      Serial.println("RELAY 1 OFF!");
      digitalWrite(relay1, LOW);
    }
    else {
      Serial.println("Error!! Try again with ON/OFF");
    }

    Firebase.getString(dulieufirebase,"RELAY2 : ");
    firestatus2 = dulieufirebase.stringData();
    if (firestatus2 == "ON" || firestatus2 == "on") {    
        Serial.println("RELAY 2 ON!");
        digitalWrite(relay2, HIGH);
      }
      else if (firestatus2 == "OFF" || firestatus2 == "off") {            
        Serial.println("RELAY 2 OFF!");
        digitalWrite(relay2, LOW);
      }
      else {
        Serial.println("Error!! Try again with ON/OFF");
      }
} 
