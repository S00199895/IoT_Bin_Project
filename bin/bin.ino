#include <Bridge.h>
#include <Temboo.h>
#include <Process.h>
#include "TembooAccount.h" // contains Temboo account information, as described below

int calls = 1;               // Execution count, so this doesn't run forever
int maxCalls = 10;           // Maximum number of times the Choreo should be executed
const int SENSOR_100 = 4;    // Sensor for the bin being 100% full
const int SENSOR_50 = 3;     // Sensor for the bin being 50% full
const int MOTION_SENSOR = 2; // Sensor to check when someone puts something into the bin


Process date;
int hours, minutes, seconds;     // Results
int lastSecond = -1;             //Impossible val for comp

void setup() {
  Bridge.begin();     // init bridge
  Serial.begin(9600); // init serial
  
  while(!Serial);
  Serial.println("Arduino bin");
}

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

void loop() {
  if (calls <= maxCalls)
  {
    if(digitalRead(MOTION_SENSOR) == 1)
    {
      // Invoke the Temboo client
      TembooChoreo SendEmailChoreo; 
      SendEmailChoreo.begin();
  
      // Set Temboo account credentials
      SendEmailChoreo.setAccountName(TEMBOO_ACCOUNT);
      SendEmailChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
      SendEmailChoreo.setAppKey(TEMBOO_APP_KEY);

      // Identify the Choreo to run
      SendEmailChoreo.setChoreo("/Library/Google/Gmail/SendEmail");
      
      // Set Choreo inputs
      SendEmailChoreo.addInput("FromAddress", "binarduinoyun@gmail.com");
      SendEmailChoreo.addInput("Username", "binarduinoyun@gmail.com");
      SendEmailChoreo.addInput("ToAddress", "binarduinoyun@gmail.com");
      SendEmailChoreo.addInput("MessageBody", "Bin warning");
      SendEmailChoreo.addInput("Password", "atpwckugzjrwgakz");

      // Get the current date and time

      delay(10000);
      String currentTime = GetDate();
      
      if(digitalRead(SENSOR_100) == 0)
      {
        SendEmailChoreo.addInput("Subject", "Your bin is currently full.\n" + currentTime);
        Serial.println(currentTime);
        Serial.println("Bin full");
        SendEmailChoreo.run();
      }
      else if (digitalRead(SENSOR_50) == 0)
      {  
        
        SendEmailChoreo.addInput("Subject", "Your bin is currently half full.\n" + currentTime);
        Serial.println(currentTime);
        Serial.println("Bin half full");
        SendEmailChoreo.run();
      }
      else
      {
        Serial.println(currentTime);
        Serial.println("Bin empty");
      }
      
      while(SendEmailChoreo.available()) {
        char c = SendEmailChoreo.read();
        Serial.print(c);
      }
      SendEmailChoreo.close();
    }
  }
  else 
  {
    Serial.println("Max calls given");
  }
  Serial.println("Waiting...");
  delay(10000);
}
