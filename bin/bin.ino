  
/*
Derived from Yún HTTP Client Sketch
and https://github.com/marloft/PushingBoxGoogleSpreadsheet/blob/master/PushingBoxGoogleSpreadsheet.ino
 */


#include <Bridge.h>
#include <HttpClient.h>
#include <Process.h>

const int MOTION_SENSOR = 2;  // Sensor to check when someone puts item int bin
const int SENSOR_50 = 3;      // Sensor for bin being 50% full 
const int SENSOR_100 = 4;     // Sensor for bin being 100% full

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
    int half = digitalRead(SENSOR_50);
    int full = digitalRead(SENSOR_100);
    String currentTime = GetDate();
    
    // Make a HTTP request:  
    String APIRequest;
    APIRequest = String(serverName) + "/pushingbox?devid=" + String(devid) + "&TimeStamp=50&half=" + half + "&full=" + full ;
    client.get (APIRequest);
    
    // if there are incoming bytes available
    // from the server, read them and print them:
    while (client.available())
    {
      char c = client.read();
    }
    
    Serial.println(currentTime);
    Serial.println("Sent values: ");
    Serial.println("half full: " + String(digitalRead(SENSOR_50)) + "\nfull: " + String(digitalRead(SENSOR_100)));
  }
}
