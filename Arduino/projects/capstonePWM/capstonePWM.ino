const int pwmOutPin = 9; // Select a PWM capable pin
void setup() {
  Serial.begin(9600);
  pinMode(pwmOutPin, OUTPUT);
  analogWrite(pwmOutPin, 191); // Start with a 75% duty cycle
}

const int inputPin = A0; // Use an analog input pin
unsigned long pwmDetectedTime = 0;
bool isPWM = false;
bool state = false;

void loop() {
  static unsigned long lastMillis = 0;
  unsigned long currentMillis = millis();

  // Read the input value
  int inputValue = analogRead(inputPin);
  
  // Simplistic detection logic: A fluctuating signal suggests PWM
  if ((inputValue > 500 && inputValue < 600) || inputValue < 25) { // Adjust these based on expected PWM voltage levels
    // Signal detected as PWM
    if (!isPWM) { // Transition from non-PWM to PWM detected
      isPWM = true;
      pwmDetectedTime = currentMillis;
      state = true;
    }
  } else if ((inputValue > 25 && inputValue < 500) && inputValue > 600)  {
    if (!isPWM) {
      isPWM = false;
      pwmDetectedTime = 0;
      state = false;
    }
  } else {
    isPWM = false;
  }

  // After detecting PWM, wait 5 seconds and change duty cycle
  if (isPWM && (currentMillis - pwmDetectedTime > 5000)) {
    analogWrite(pwmOutPin, 64); // Change to 25% duty cycle

    isPWM = false; // Prevent further duty cycle changes
  } else if (!isPWM && (currentMillis - pwmDetectedTime > 5000)){
    analogWrite(pwmOutPin, 191);
  }
  

  Serial.print("Voltage @ A0: ");
  Serial.println(inputValue);
  Serial.print("PWM DUTY CYCLE:");
  Serial.print(state);

  delay(50); // Small delay to reduce reading frequency
}
