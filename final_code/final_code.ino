#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int greenDelay = 3000; // Default delay for the green light
unsigned long previousMillis = 0;
const long interval = 1000; // Check for new delay every 1 second
unsigned long previousDelayCheckMillis = 0;
const long delayCheckInterval = 1000; // Check for new delay every 1 second

unsigned long redCountdownStartMillis = 0;
const long redCountdownDuration = 3000; // Red light countdown duration in milliseconds

bool receivedInput = false; // Flag to track if input was received

// Initialize the LCD with the I2C address
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Adjust the address and size as needed

void setup() {
  pinMode(2, OUTPUT);  // Red LED
  pinMode(3, OUTPUT);  // Yellow LED
  pinMode(4, OUTPUT);  // Green LED

  pinMode(5, OUTPUT);  // Red LED
  pinMode(6, OUTPUT);  // Yellow LED
  pinMode(7, OUTPUT);  // Green LED

  // Initialize serial communication
  Serial.begin(9600);

  // Initialize the LCD
  lcd.init();
  lcd.backlight();

  // Display the welcome message and team name on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome to");
  lcd.setCursor(0, 1);
  lcd.print("Your Traffic Light");
  delay(2000); // Display the message for 2 seconds

  // Display the team name
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Team Name:");
  lcd.setCursor(0, 1);
  lcd.print("Warriors Of Innovation");
  delay(2000); // Display the team name for 2 seconds

  // Set the initial state of the green light to the default value
  unsigned long currentMillis = millis();
  redCountdownStartMillis = currentMillis;
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
}

void loop() {
  unsigned long currentMillis = millis();

  // Check for new delay input
  if (currentMillis - previousDelayCheckMillis >= delayCheckInterval) {
    previousDelayCheckMillis = currentMillis;

    if (Serial.available() > 0) {
      greenDelay = Serial.parseInt(); // Read the delay for the green light in milliseconds
      receivedInput = true; // Set the flag to indicate input was received
    }
  }

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // If no new input has been received within a certain time, use the default value for the green LED
    if (!receivedInput) {
      greenDelay = 3000; // Set to the default value
    }
    
    // Reset the flag for the next cycle
    receivedInput = false;

    // Red light countdown
    redCountdownStartMillis = currentMillis;
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);

    while (currentMillis - redCountdownStartMillis < redCountdownDuration) {
      int remainingRedTime = (redCountdownDuration - (currentMillis - redCountdownStartMillis)) / 1000;

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Red Lane 1: ");
      lcd.print(remainingRedTime);

      delay(950);  // Update the display every 1 second

      currentMillis = millis();
    }

    // Red light
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    delay(3000);  // Red light stays on for 3 seconds

    // Yellow light
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);

    delay(1000);  // Yellow light stays on for 1 second

    // Green light
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);

    // Countdown Timer
    int remainingTime = greenDelay / 1000;
    for (int i = 0; i < remainingTime; i++) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Green Lane 1: ");
      lcd.print(remainingTime - i);
      lcd.print(" sec");
      delay(1000);
    }

    // Reset the LCD after the countdown
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Green Lane 1: 0 sec");

    // FOR FIRST LANE TRANSITION YELLOW LIGHT
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);

    delay(1000);
  }
}
