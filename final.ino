#include <WiFi.h>

#include "ThingSpeak.h"

#include <DHT.h> 



const char* ssid = "Vamsi";     

const char* password = "vamsipersonal";  



WiFiClient  client;



unsigned long Channel_ID = 1967322;

const char * API_Key = "KUEVVFAHZEMQGLZZ "; 



unsigned long last_time = 0;

unsigned long Delay = 10000;



// Variables to store sensor readings

float temperature;

float temperaturef;

float humidity;

#define DHTPIN 4         

DHT dht(DHTPIN, DHT11);

 void initBME(){

    if (isnan(temperature) || isnan(humidity))  {

   Serial.println("Failed to read from DHT sensor!");

    while (1);

  }

}



void setup() {

  Serial.begin(115200);  

       dht.begin();

  

  WiFi.mode(WIFI_STA);   

  

  ThingSpeak.begin(client); 

}



void loop() {

  if ((millis() - last_time) > Delay) {

    

    // Connect or reconnect to WiFi

    if(WiFi.status() != WL_CONNECTED){

      Serial.print("Connecting...");

      while(WiFi.status() != WL_CONNECTED){

        WiFi.begin(ssid, password); 

        delay(5000);     

      } 

      Serial.println("\nConnected.");

    }



    // Obtaining a new sensor reading for all fields

    temperature = dht.readTemperature();

    Serial.print("Temperature (ºC): ");

    Serial.println(temperature);

    humidity = dht.readHumidity();

    Serial.print("Humidity (%): ");

    Serial.println(humidity);

  

    

    ThingSpeak.setField(1, temperature);

    ThingSpeak.setField(2,humidity );

    

   int Data = ThingSpeak.writeFields(Channel_ID, API_Key);



    if(Data == 200){

      Serial.println("Channel updated successfully!");

    }

    else{

      Serial.println("Problem updating channel. HTTP error code " + String(Data));

    }
    if (temperature>25){
    Serial.println("Temperature is more");}
    last_time = millis();
    

  }
  
  

}
