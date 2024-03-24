import processing.serial.*;
import java.awt.event.KeyEvent; // imports library for reading the data from the serial port
import java.io.IOException;


String buffer = "";
int minutes = 0;
int seconds = 0;


Serial myPort;        // The serial port
float voltage = 0;    // For storing the voltage value
float soc = 0;

// Battery voltage range
float minVoltage = 0.0;
float maxVoltage = 4.2;

void setup() {
  size(400, 200);         // Set the window size
  println(Serial.list()); // Print available serial ports
  
  // Initialize the serial port - replace 0 with the correct index for your system
  myPort = new Serial(this, "COM3", 9600);
  myPort.bufferUntil('$'); // Read until newline

}


void draw() {
  
  background(230); // Set the background to a light gray
  
  // Calculate SOC based on the current voltage
  //float soc = map(voltage, minVoltage, maxVoltage, 0, 1);
  soc = constrain(soc, 0, 1); // Ensure SOC is within 0 to 1
  
  // Draw the battery outline
  stroke(0);
  fill(255);
  rect(50, 50, 300, 100, 15);
  
  // Draw the SOC bar
  noStroke();
  fill(0, 255, 0); // Green color
  float fillWidth = soc * 300; // Calculate fill width based on SOC
  rect(50, 50, fillWidth, 100, 15);
  
  // Display the voltage and SOC
  fill(0);
  textSize(16);
  text("Voltage: " + voltage + "V", 70, 170);
  text("SOC: " + int(soc * 100) + "%", 250, 170);
}

void serialEvent(Serial myPort) {
  // Read incoming data into the buffer
  buffer = myPort.readStringUntil('$');
  if (buffer == null) {
    return; // No data received, exit the function
  }
  buffer = buffer.trim(); // Remove any trailing whitespace
  
  // Split the complete message into its parts
  String[] parts = split(buffer, ',');
  
  if (parts.length == 4) { // Check if all parts are present
    try {
      // Parse each part of the received data
      voltage = Float.parseFloat(parts[0]);
      soc = Float.parseFloat(parts[1]);
      minutes = Integer.parseInt(parts[2]);
      seconds = Integer.parseInt(parts[3]);
      System.out.println("Parsed data successfully.");
    } catch (NumberFormatException e) {
      System.out.println("Error parsing numbers from the received data.");
    }
  } else {
    System.out.println("Incomplete data received.");
  }
  
  // Clear the buffer after processing
  buffer = "";
}
