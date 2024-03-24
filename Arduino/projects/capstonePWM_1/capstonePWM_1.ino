const int pwmOutPin = 9; // Select a PWM capable pin
const int inputPin = A0; // Use an analog input pin
unsigned long pwmDetectedTime = 0;
bool pwmSignalDetected = false;
int pwmDutyCycle = 191; // Start with a 75% duty cycle

void setup() {
  Serial.begin(9600);
  pinMode(pwmOutPin, OUTPUT);
  analogWrite(pwmOutPin, pwmDutyCycle); // Set initial duty cycle
}

void loop() {
  // Read the input value
  int inputValue = analogRead(inputPin);
  unsigned long currentMillis = millis();

  // Check for PWM signal within a specific range or low value indicating OFF
  if ((inputValue > 450 && inputValue < 600) || inputValue < 25) { 
    // ON range (450, 600) due to fluxuations in voltage @ MOSFET source terminal
    // Boolean OR used to detect 25% OFF cycle
    if (!pwmSignalDetected) {
      pwmSignalDetected = true;
      pwmDetectedTime = currentMillis;
    }
  } else {
    pwmSignalDetected = false;
    pwmDutyCycle = 191; // Reset duty cycle to 75% when no signal is detected
    analogWrite(pwmOutPin, pwmDutyCycle);
  }

  // After detecting PWM, wait 5 seconds and change duty cycle
  if (pwmSignalDetected && (currentMillis - pwmDetectedTime > 5000)) {
    pwmDutyCycle = 64; // Change to 25% duty cycle
    analogWrite(pwmOutPin, pwmDutyCycle);
    pwmSignalDetected = false; // Reset the detection flag
  }
  
  // Serial output for debugging
  Serial.print("Voltage @ A0: ");
  Serial.println(inputValue);
  //Serial.print(", PWM Duty Cycle: ");
  //Serial.println(pwmDutyCycle);

  delay(100); // Small delay to reduce reading frequency
}
