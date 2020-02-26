#include <Bridge.h>
#include <Process.h>

Process p;
IR_SENSOR = 'A3';
MOTION_SENSOR = 3;


// Path
String path = "";

void setup() {
    Bridge.begin();
    Serial.begin(9600);
    SerialUSB.begin(9600);

    while(!SerialUSB);
    SerialUSB.println("Log test");

    SerialUSB.println("Setup test");
    p.runShellCommandAsynchronously("python " + path + "logsetup.py");

    if (p.running() {SerialUSB.println("Python script is running")});
}

void loop() {
    if (digitalRead(MOTION_SENSOR) == 1)
    {
        String vol = analogRead(0, IR_SENSOR);
        p.runShellCommandAsynchronously("python " + path + "arduino_bin.py " + vol);
    }
}
