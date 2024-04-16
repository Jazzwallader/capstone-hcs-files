import processing.serial.*;
import java.awt.event.KeyEvent; // imports library for reading the data from the serial port
import java.io.IOException;
import processing.video.*;


String buffer = "";
int minutes = 0;
int seconds = 0;
String chgState;



Serial myPort;        // The serial port
float voltage = 0;    // For storing the voltage value
float soc = 0;

// Battery voltage range
float minVoltage = 0.0;
float maxVoltage = 4.2;

void setup() {
  size(800, 400);         // Set the window size
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
  rect(50, 50, 300, 100, 5);
  
  // Draw the SOC bar
  noStroke();
  fill(0, 155, 10); // Green color
  float fillWidth = soc * 300; // Calculate fill width based on SOC
  rect(51, 51, fillWidth-1, 99, 5);

  // hehe battery graphic
  noStroke();
  fill(50, 50, 50);
  rect(350, 77, 10, 50, 3);
  
  try {
    // DISPLAYED TEXT
    fill(0);
    textSize(16);
    text("Voltage: " + voltage + "V", 70, 170);
    text("SOC: " + int(soc * 100) + "%", 250, 170);
    text("Time Elapsed: " + minutes + "m" + seconds + "s", 130, 30);
    textSize(24);
    text(chgState, 140, 105);
  } catch (NullPointerException e) {
    System.out.println("Caught a NullPointerException!");
  }
}

void serialEvent(Serial myPort) {
  // Read incoming data into the buffer
  buffer = myPort.readStringUntil('$');
  if (buffer == null) {
    return; // No data received, exit the function
  }
  buffer = buffer.trim(); // Remove any trailing whitespace
  buffer = buffer.substring(0, buffer.length() - 1);
  
  // Split the complete message into its parts
  String[] parts = split(buffer, ',');
  int[] numbers = new int[parts.length];

  for (int i = 2; i < parts.length - 1; i++) {
    try {
        numbers[i] = Integer.parseInt(parts[i]); // Convert and store
    } catch (NumberFormatException e) {
        System.out.println("Error parsing '" + parts[i] + "' to an integer.");
        // Handle the error or initialize the array element with a default value
    }
  }
  
  if (parts.length >= 4) { // Check if all parts are present
    try {
      // Parse each part of the received data
      voltage = Float.parseFloat(parts[0]);
      soc = Float.parseFloat(parts[1]);
      minutes = numbers[2];
      seconds = numbers[3];
      chgState = parts[4]; 
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