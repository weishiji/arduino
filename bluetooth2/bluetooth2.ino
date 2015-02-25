#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10,11); // RX | TX


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int led = 8;
int level = 1;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  Serial.println("Enter AT commands");
  BTSerial.begin(9600);
  pinMode(led,OUTPUT);
  
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  if(BTSerial.available()){
    Serial.write(BTSerial.read());
  }
  //keeping reading form arduino Serial and send to HC-06
  if(Serial.available()){
    BTSerial.write(Serial.read());
  }
  serialEvent();                                                           
  // print the string when a newline arrives:
  if (stringComplete) {
    level = inputString.toInt();
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  
  analogWrite(led,level);
  
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (BTSerial.available()) {
    // get the new byte:
    char inChar = (char)BTSerial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}
