/*
  SendDataToGoogleSpreadsheet

  Demonstrates appending a row of data to a Google spreadsheet from the Arduino Yun 
  using the Temboo Arduino Yun SDK.  

  This example code is in the public domain.
*/

#include <Bridge.h>
#include <Temboo.h>
#include "TembooAccount.h" // contains Temboo account information

/*** SUBSTITUTE YOUR VALUES BELOW: ***/

// Note that for additional security and reusability, you could
// use #define statements to specify these values in a .h file.

const String GOOGLE_CLIENT_ID = "216186659341-1qeo38ffful8eiocv2aft1sqv0l1hss8.apps.googleusercontent.com";
const String GOOGLE_CLIENT_SECRET = "z3HRsuUjYhOnRJKaRx5wPOYi";
const String GOOGLE_REFRESH_TOKEN = "1//0dJTounCgbQ82CgYIARAAGA0SNwF-L9IrMn7WaN-XNYD45jeomV07ANBrzlY4wLaR4lUF2hoI-X4vEIJYC4nNlhRxzccMSt1O9dE";
const int MOTION_SENSOR = 2;
const int SENSOR_50 = 3;
const int SENSOR_100 = 4;

// The ID of the spreadsheet you want to send data to
// which can be found in the URL when viewing your spreadsheet at Google. For example, 
// the ID in the URL below is: "1tvFW2n-xFFJCE1q5j0HTetOsDhhgw7_998_K4sFtk"
// Sample URL: https://docs.google.com/spreadsheets/d/1SBkVYVsW4rjIVRC-3v-TVYP002WAhGfs3IrOZAImqwM/edit
const String SPREADSHEET_ID = "1o7Myyf2URCXKUwdFFud3vSdyO_oSAdBZpprtNg2UsBw";

int numRuns = 1;   // execution count, so this doesn't run forever
int maxRuns = 5;   // the max number of times the Google Spreadsheet Choreo should run

void setup() {
  
  // for debugging, wait until a serial console is connected
  Serial.begin(9600);
  delay(4000);
  while(!Serial);

  Serial.print("Initializing the bridge... ");
  Bridge.begin();
  Serial.println("Done!\n");
}

void loop()
{

  // while we haven't reached the max number of runs...
  if (numRuns <= maxRuns) {

    Serial.println("Running AppendValues - Run #" + String(numRuns++));

    // get the number of milliseconds this sketch has been running
    unsigned long now = millis();
    
    Serial.println("Getting sensor value...");

    // get the value we want to append to our spreadsheet
    unsigned int halfSensor = digitalRead(SENSOR_50);
    unsigned int fullSensor = digitalRead(SENSOR_100);

    Serial.println("Appending value to spreadsheet...");

    // we need a Process object to send a Choreo request to Temboo
    TembooChoreo AppendValuesChoreo;

    // invoke the Temboo client
    // NOTE that the client must be reinvoked and repopulated with
    // appropriate arguments each time its run() method is called.
    AppendValuesChoreo.begin();
    
    // set Temboo account credentials
    AppendValuesChoreo.setAccountName(TEMBOO_ACCOUNT);
    AppendValuesChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    AppendValuesChoreo.setAppKey(TEMBOO_APP_KEY);
    
    // identify the Temboo Library choreo to run (Google > Sheets > AppendValues)
    AppendValuesChoreo.setChoreo("/Library/Google/Sheets/AppendValues");
    
    // set the required Choreo inputs
    // see https://www.temboo.com/library/Library/Google/Sheets/AppendValues/ 
    // for complete details about the inputs for this Choreo
    AppendValuesChoreo.addInput("RefreshToken", "1//0dJTounCgbQ82CgYIARAAGA0SNwF-L9IrMn7WaN-XNYD45jeomV07ANBrzlY4wLaR4lUF2hoI-X4vEIJYC4nNlhRxzccMSt1O9dE");
    AppendValuesChoreo.addInput("ClientSecret", "z3HRsuUjYhOnRJKaRx5wPOYi");
    AppendValuesChoreo.addInput("Values", "[[1,1,1]]");
    AppendValuesChoreo.addInput("ClientID", "216186659341-1qeo38ffful8eiocv2aft1sqv0l1hss8.apps.googleusercontent.com");
    AppendValuesChoreo.addInput("SpreadsheetID", "1o7Myyf2URCXKUwdFFud3vSdyO_oSAdBZpprtNg2UsBw");
    

    // convert the time and sensor values to a json array
    String rowData = "[[\"" + String(now) + "\", \"" + String(halfSensor) + "\", \"" + String(fullSensor) + "\"]]";

    // add the RowData input item
    AppendValuesChoreo.addInput("Values", rowData);

    // run the Choreo and wait for the results
    // The return code (returnCode) will indicate success or failure 
    unsigned int returnCode = AppendValuesChoreo.run();

    // return code of zero (0) means success
    if (returnCode == 0) {
      Serial.println("Success! Appended " + rowData);
      Serial.println("");
    } else {
      // return code of anything other than zero means failure  
      // read and display any error messages
      while (AppendValuesChoreo.available()) {
        char c = AppendValuesChoreo.read();
        Serial.print(c);
      }
    }

    AppendValuesChoreo.close();
  }

  Serial.println("Waiting...");
  delay(5000); // wait 5 seconds between AppendValues calls
}
