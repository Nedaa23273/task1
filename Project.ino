#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>
SoftwareSerial bluetooth(2, 3);  // Create a SoftwareSerial object. Define the TX and RX pins.


//**********************************Moisture Sensor******************************
int val = 0; //value for storing moisture value 
int soilPin = A0;//Declare a variable for the soil moisture sensor 
int soilPower = 7;//Variable for Soil moisture Power
int Pump =8;
float temperature =0 ; 
int Led=9;
int fan=11;

//**********************************Moisture Sensor******************************
#define DHTPIN 10    // what pin we're connected to
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);
float hum;  //Stores humidity value
float temp;
//_____________________________________________________________________________________
void setup() 
{
  Serial.begin(9600);                  // open serial over USB

  dht.begin();
  bluetooth.begin(9600);  // Serial communication with the HC-05 module

  pinMode(soilPower, OUTPUT);
  pinMode(Led, OUTPUT);
  pinMode(fan, OUTPUT);
  digitalWrite(soilPower, LOW);      //Set to LOW so no power is flowing through the sensor
  digitalWrite(fan, LOW);      
  pinMode(Pump, OUTPUT);
  digitalWrite(Pump, LOW);



}
void loop() 
{

  //___________________________________Temperature________________________
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");

        if(temp > 20.0 )
          {digitalWrite(fan , HIGH);}
       else
          {digitalWrite(fan , LOW);}







  //____________________________________Soil Moisture___________________________________
    Serial.print("Soil Moisture = ");
    int Soil = readSoil();
    Serial.println(Soil);
    if(readSoil()<=400)
    {
    digitalWrite(Pump,HIGH);
    }
    else
    {
    digitalWrite(Pump,LOW);
    }











  //____________________________________bluetooth___________________________________ 

  if (bluetooth.available()) {
    char data = bluetooth.read();
    Serial.print("Received from Bluetooth: ");
    Serial.println(data);

    if(data=='f')
    {
   digitalWrite(Led, HIGH);

    }

   else if (data=='x')
    {
    digitalWrite(Led, LOW);
    digitalWrite(Pump,LOW);
    }

    }
       bluetooth.print("Soil Moisture = ");
    bluetooth.print(Soil);
    bluetooth.print("\n");
 bluetooth.print("   Temperature: ");
  bluetooth.print(temp);
   bluetooth.print("\n");


 //_______________________________________________________________________

 delay(1000);//take a reading every second







}






//____________________________Functions_________________________//
int readSoil()
{

    digitalWrite(soilPower, HIGH);//turn D7 "On"
    delay(10);//wait 10 milliseconds 
    val = analogRead(soilPin);//Read the SIG value form sensor 
    digitalWrite(soilPower, LOW);//turn D7 "Off"
    return val;//send current moisture value
}
