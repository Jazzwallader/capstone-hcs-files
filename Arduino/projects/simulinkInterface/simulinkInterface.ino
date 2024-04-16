#include <SoftwareSerial.h>

// SoftwareSerial RX and TX pins
// Connect these pins to TX and RX on the Nano, respectively
int rxPin = 10; // Example pin for SoftwareSerial RX (connect to Nano's TX)
int txPin = 11; // Example pin for SoftwareSerial TX (connect to Nano's RX)

// Initialize SoftwareSerial for communication with the Nano
SoftwareSerial nanoSerial(rxPin, txPin);

void setup() {
  // Start the hardware serial communication at 9600 baud to communicate with Simulink
  Serial.begin(9600);
  
  // Start the software serial communication at 9600 baud for the Nano
  nanoSerial.begin(9600);

  // Simple setup message
  Serial.println("Uno is ready to relay data to Nano...");
}

void loop() {
  // Check if data is available to read from Simulink
  if (Serial.available() > 0) {
    // Read the incoming byte from Simulink
    char receivedChar = Serial.read();

    // Forward the received byte to the Nano
    nanoSerial.write(receivedChar);
  }

  // Optional: Check if there is data coming back from the Nano and relay it back to Simulink
  if (nanoSerial.available() > 0) {
    char receivedCharFromNano = nanoSerial.read();
    Serial.write(receivedCharFromNano);
  }
}
