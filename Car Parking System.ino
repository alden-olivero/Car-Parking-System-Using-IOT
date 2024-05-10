#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize a 16x2 LCD with I2C address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo myservo;

// Define IR sensor pins
#define ir_enter 7
#define ir_back 11
#define ir_car1 5
#define ir_car2 6

#define ir_car3 2


// Slot and flag variables
int S1 = 0, S2 = 0, S3 = 0;
int flag1 = 0, flag2 = 0;
int slot = 300; // Initialize with the total number of slots

byte Heart[] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};

byte smiley[8] = { B00000, B10001, B00000, B00000, B10001, B01110, B00000, };
void setup() {
  Serial.begin(9600);

  // Set pin modes for IR sensors
  pinMode(ir_car1, INPUT);
  pinMode(ir_car2, INPUT);
  pinMode(ir_car3, INPUT);

  pinMode(ir_enter, INPUT);
  pinMode(ir_back, INPUT);

  // Attach the servo
  myservo.attach(9);
  myservo.write(90);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, Heart);
   lcd.createChar(1, smiley);
  // Welcome message
  lcd.setCursor(0, 0);
  lcd.print("Welcome");
  lcd.setCursor(0, 1);
  lcd.print("Sneha MAM ");
  //lcd.write(byte(0));
  //lcd.print(" ");
  lcd.write(byte(1));
  delay(5000);


  // Project title
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Car Parking");
  lcd.setCursor(0, 1);
  lcd.print("System");
  delay(5000);

  lcd.clear();
  Read_Sensor();

  int total = S1 + S2 + S3;
  slot -= total; // Update slot count based on sensor readings
}

void loop() {
  Read_Sensor();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Slots: ");
  lcd.print(slot); // Display the available slots

  lcd.setCursor(0, 1);
  lcd.print(S1 ? "S1:F " : "S1:E ");
  lcd.print(S2 ? "S2:F " : "S2:E ");
  lcd.print(S3 ? "S3:F " : "S3:E ");

  // Check if a car is entering
  if (digitalRead(ir_enter) == 0 && flag1 == 0) {
    if (slot > 0) {
      flag1 = 1;
      if (flag2 == 0) {
        myservo.write(180); // Open the gate
        slot--; // Decrement the available slot count
      }
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Parking Full");
      delay(1500);
    }
  }

  // Check if a car is leaving
  if (digitalRead(ir_back) == 0 && flag2 == 0) {
    flag2 = 1;
    if (flag1 == 0) {
      myservo.write(180); // Open the gate
      slot++; // Increment the available slot count
    }
  }

  // Reset flags and servo position
  if (flag1 == 1 && flag2 == 1) {
    delay(1000); // Wait for the gate to open/close
    myservo.write(90); // Reset the gate
    flag1 = 0;
    flag2 = 0;
  }

  delay(1); // Small delay to avoid rapid re-triggering
}

void Read_Sensor() {
  static int lastS1 = -1, lastS2 = -1, lastS3 = -1;

  // Current sensor states
  int currentS1 = digitalRead(ir_car1) == 0 ? 1 : 0;
  int currentS2 = digitalRead(ir_car2) == 0 ? 1 : 0;
  int currentS3 = digitalRead(ir_car3) == 0 ? 1 : 0;

  // Debouncing logic for S3
  if (currentS3 != lastS3) { // If there's a change in state
    delay(50); // Debounce delay
    if (digitalRead(ir_car3) == (currentS3 == 1 ? LOW : HIGH)) { // Confirm change
      S3 = currentS3;
    }
  }

  S1 = currentS1;
  S2 = currentS2;
  lastS1 = currentS1;
  lastS2 = currentS2;
  lastS3 = currentS3;
}

