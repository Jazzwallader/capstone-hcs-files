#include "SevSeg.h"
SevSeg sevseg;

void setup() {
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = false;
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);

  Serial.begin(9600); // Start serial communication
}

void loop() {
  if (Serial.available() > 0) {
    String incomingData = Serial.readStringUntil('$'); // Read the incoming data as a string
    incomingData.trim(); // Clean up any whitespace or newline characters
    
    // Split the incoming data string into an array of substrings based on commas
    int firstCommaIndex = incomingData.indexOf(',');
    int secondCommaIndex = incomingData.indexOf(',', firstCommaIndex + 1);
    int thirdCommaIndex = incomingData.indexOf(',', secondCommaIndex + 1);
    
    // Check if all commas were found
    if (firstCommaIndex != -1 && secondCommaIndex != -1 && thirdCommaIndex != -1) {
      // Parse each part of the data
      float voltage = incomingData.substring(0, firstCommaIndex).toFloat();
      float SoC = incomingData.substring(firstCommaIndex + 1, secondCommaIndex).toFloat();
      int minutes = incomingData.substring(secondCommaIndex + 1, thirdCommaIndex).toInt();
      int seconds = incomingData.substring(thirdCommaIndex + 1).toInt();
      
      // Now you can use the voltage, SoC, minutes, and seconds variables
      // For example, to display minutes and seconds on the 7-segment display
      sevseg.setNumber(minutes * 100 + seconds, 2);
    }
  }
  sevseg.refreshDisplay();
}
