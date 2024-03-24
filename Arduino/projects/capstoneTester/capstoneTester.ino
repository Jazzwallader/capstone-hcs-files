#include "SevSeg.h"
SevSeg sevseg; //Initiate a seven segment controller object

unsigned long startTime;
bool chgState;

void setup() {
  // Initialize Serial communication at a baud rate of 9600:
  Serial.begin(9600);

  // Initialize digital pin 9 as an output.
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);

  // Initially, set digital pin 9 to LOW (OFF)
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);

  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = false; // False = resistors on digit pins, True = resistors on segment pins
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);

  startTime = millis(); // Store the start time
}

void loop() {
  unsigned long elapsedTime = (millis() - startTime) / 1000; // Calculate elapsed time in seconds
  int minutes = elapsedTime / 60;
  int seconds = elapsedTime % 60;


  // Read the value from the analog pin A0
  int sensorValue = analogRead(A0);
  int a5 = analogRead(A5);
  int a4 = analogRead(A4);
  float battVoltage = sensorValue * (5.0 / 1023.0);
  // Assuming a direct mapping, let's convert the sensor value to a percentage
  // This example assumes the analog value ranges linearly with SOC
  // Adjust the 'minVoltage' and 'maxVoltage' according to your battery's characteristics and the BMS output
  float minVoltage = 2.4; // Assuming 3.0V as 0% SOC
  float maxVoltage = 4.2; // Assuming 4.2V as 100% SOC
  float voltage = a5 * (5 / 1023.0);
  //float soc = (voltage) / (maxVoltage);
  float soc = a4 / 1023.0;


  // Conditions for turning pin 9 ON or OFF
  // if (voltage < 1.2) {
  //   chgState = LOW;
  //   digitalWrite(9, LOW); // Charging ON
  // } else if (voltage > 1.9) {
  //   chgState = HIGH;
  //   digitalWrite(9, HIGH); // Charging OFF
  // } else {
  //   chgState = chgState;
  //   digitalWrite(9, chgState);
  // }

String serialCSV = String(voltage) + "," + String(soc) + "," + String(minutes) + "," + String(seconds) + "$";
  // Print the SOC to the Serial Monitor
  //Serial.print("Voltage: ");
  Serial.print(serialCSV);
  //Serial.println(" = Int: ");
  //Serial.println(sensorValue);

  // Wait for a bit to avoid spamming the Serial Monitor
  delay(1000);
}