  
/*
Derived from Yún HTTP Client Sketch
and https://github.com/marloft/PushingBoxGoogleSpreadsheet/blob/master/PushingBoxGoogleSpreadsheet.ino
 */


#include <Bridge.h>
#include <HttpClient.h>
#include <Process.h>

const int MOTION_SENSOR = 2;  // Sensor to check when someone puts item int bin
const byte ULTRASONIC_SENSOR_1 = A0; 
const byte ULTRASONIC_SENSOR_2 = A1; 
const byte ULTRASONIC_SENSOR_3 = A2; 
const byte ULTRASONIC_SENSOR_4 = A3; 

const int BIN_DEPTH = 3;

char devid[] = "v8C89B8298357893";         // DEVICE ID for PushingBox
char serverName[] = "api.pushingbox.com";  // PushingBox API url
boolean DEBUG = true;


Process date;
int hours, minutes, seconds; 
int lastSecond = -1;


String GetDate()
{
  date.begin("/bin/date");
  date.addParameter("+%d/%m/%Y %T");
  date.run();

  while (date.available() > 0)
  {
    String timeString = date.readString();
    return timeString;
  }
}


void setup() {
  // Blink light setting up bridge
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);

  Serial.begin(9600);
  while (!Serial); // wait for a serial connection
}

void loop() {
  
  HttpClient client;

  if (digitalRead(MOTION_SENSOR) == 1)
  {
    delay(10000);
    double result1 = analogRead(ULTRASONIC_SENSOR_1);
    double result2 = analogRead(ULTRASONIC_SENSOR_2);
    double result3 = analogRead(ULTRASONIC_SENSOR_3);
    double result4 = analogRead(ULTRASONIC_SENSOR_4);

    double binFullness = (result1 + result2 + result3 + result4) / (4 * BIN_DEPTH);
    
    String currentTime = GetDate();
    
    // Make a HTTP request:  
    String APIRequest;
    APIRequest = String(serverName) + "/pushingbox?devid=" + String(devid) + "&TimeStamp=50&fullness=" + binFullness;
    client.get (APIRequest);
    
    // if there are incoming bytes available
    // from the server, read them and print them:
    while (client.available())
    {
      char c = client.read();
    }
    
    Serial.println(currentTime);
    Serial.println("Sent values: ");
    Serial.println("fullness: " + String(binFullness) + "\nPercentage full: " + String(binFullness * 100));
  }
}
