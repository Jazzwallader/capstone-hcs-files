#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// Initialize the LiquidCrystal library with the pins for the 1602A display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


unsigned long durationHigh = pulseIn(7, HIGH);
unsigned long durationLow = pulseIn(7, LOW);
unsigned long period = durationHigh + durationLow;
double dutyCycle = (double)durationHigh / (double)period * 100.0;

void setup() {
  // Set up serial communication at a baud rate of 9600
  Serial.begin(9600);
  pinMode(7, INPUT);
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Time of Use: ");
}


void loop() {
  // Move the duty cycle calculation inside the loop to update it on each iteration
  unsigned long durationHigh = pulseIn(7, HIGH);
  unsigned long durationLow = pulseIn(7, LOW);
  unsigned long period = durationHigh + durationLow;
  double dutyCycle = 0;
  
  // Make sure period is not zero to avoid division by zero
  if (period != 0) {
    dutyCycle = (double)durationHigh / (double)period * 100.0;
  }

  // Initialize the tou variable
  String tou = "null"; // Default value is "Null"

  // Use if-else if statements to determine the tou value
  if (dutyCycle >= 9 && dutyCycle <= 18) {
    tou = "Off-peak";
  } else if (dutyCycle >= 23 && dutyCycle <= 40) {
    tou = "Mid-peak Up";
  } else if (dutyCycle >= 45 && dutyCycle <= 55) {
    tou = "Mid-peak Down";
  } else if (dutyCycle >= 65 && dutyCycle <= 75) {
    tou = "On-peak";
  }
  // Other values will default to "Null" as initialized before the if statement

  // Set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  
  
  // Clear the second line before displaying new value
  // This can be done by printing spaces over the previous text
//  for (int i = 0; i < 16; i++) {
//    lcd.print(" ");
//  }

  // Alternatively, you can use lcd.clear() to clear the display, but it will clear both lines.

  // Reset the cursor to column 0, line 1 to print the new value
  // Display the time of use on the LCD
  lcd.clear();
  lcd.home();
  lcd.print("TOU: ");
  lcd.setCursor(0, 1);
  lcd.print(tou);
  delay(100);
}
