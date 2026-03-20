#define BLYNK_TEMPLATE_ID "TMPL342cTvHkW"
#define BLYNK_TEMPLATE_NAME "Smart Robot"
#define BLYNK_AUTH_TOKEN "wuioa8RuhApp8K_C-bycAkT2PILtJLRc"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <HardwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ==== WiFi ====
char ssid[] = "Redmi8";
char pass[] = "Qwerty098";

// ==== Motor Pins ====
#define IN1 26
#define IN2 27
#define IN3 14
#define IN4 12
#define ENA 25
#define ENB 13

// ==== IR Sensor and Button ====
#define IR_SENSOR 33
#define BUTTON_PIN 32  // physical button pin

// ==== DFPlayer ====
HardwareSerial mySerial(2);
DFRobotDFPlayerMini myDFPlayer;

// ==== LCD ====
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ==== Latched States ====
bool objectDetected = false;  // IR sensor latch
bool buttonPressed = false;   // Button latch

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600, SERIAL_8N1, 16, 17);  // RX=16, TX=17

  // Pins
  pinMode(IR_SENSOR, INPUT_PULLUP);       // IR open-collector, stabilize with pull-up
  pinMode(BUTTON_PIN, INPUT_PULLUP);     // Button active LOW

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connecting WiFi");
  Serial.println("Connecting to WiFi...");

  // WiFi + Blynk
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  lcd.clear();
  lcd.print("WiFi Connected");
  delay(1000);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("Blynk Connected!");

  // DFPlayer
  Serial.println("Initializing DFPlayer...");
  if (!myDFPlayer.begin(mySerial)) {
    Serial.println("DFPlayer not found!");
    lcd.clear();
    lcd.print("DFPlayer Error!");
  } else {
    myDFPlayer.volume(25);
  }
  lcd.clear();
  lcd.print("System Ready!");
  Serial.println("System Ready!");
}

// ==== Movement Functions ====
void moveForward()  { digitalWrite(IN1,HIGH); digitalWrite(IN2,LOW); digitalWrite(IN3,HIGH); digitalWrite(IN4,LOW); Serial.println("Moving Forward"); }
void moveBackward() { digitalWrite(IN1,LOW); digitalWrite(IN2,HIGH); digitalWrite(IN3,LOW); digitalWrite(IN4,HIGH); Serial.println("Moving Backward"); }
void turnLeft()     { digitalWrite(IN1,LOW); digitalWrite(IN2,HIGH); digitalWrite(IN3,HIGH); digitalWrite(IN4,LOW); Serial.println("Turning Left"); }
void turnRight()    { digitalWrite(IN1,HIGH); digitalWrite(IN2,LOW); digitalWrite(IN3,LOW); digitalWrite(IN4,HIGH); Serial.println("Turning Right"); }
void stopCar()      { digitalWrite(IN1,LOW); digitalWrite(IN2,LOW); digitalWrite(IN3,LOW); digitalWrite(IN4,LOW); Serial.println("Stopping Car"); }

// ==== Blynk Controls ====
BLYNK_WRITE(V0){ moveForward(); }
BLYNK_WRITE(V1){ moveBackward(); }
BLYNK_WRITE(V2){ turnLeft(); }
BLYNK_WRITE(V3){ turnRight(); }
BLYNK_WRITE(V4){ stopCar(); }

BLYNK_WRITE(V5){ myDFPlayer.play(1); Serial.println("Playing Audio 1"); }
BLYNK_WRITE(V6){ myDFPlayer.play(2); Serial.println("Playing Audio 2"); }
BLYNK_WRITE(V7){ myDFPlayer.play(3); Serial.println("Playing Audio 3"); }
BLYNK_WRITE(V8){ myDFPlayer.play(4); Serial.println("Playing Audio 4"); }
BLYNK_WRITE(V9){ myDFPlayer.play(5); Serial.println("Playing Audio 5"); }

// ==== Optional Reset Button in Blynk (V12) ====
BLYNK_WRITE(V12){  // Reset latched states remotely
    if(param.asInt() == 1){
        objectDetected = false;
        buttonPressed = false;
        Blynk.virtualWrite(V10, 0); // IR button OFF
        delay(50);
        Blynk.virtualWrite(V11, 0); // Button OFF
        delay(50);
        Serial.println("Latches Reset");
    }
}

void loop() {
  // Ensure Blynk stays connected
  if (Blynk.connected()) {
      Blynk.run();
  } else {
      Blynk.connect();  // reconnect if disconnected
  }

  // --- IR Sensor (Latched, active LOW) ---
  int irValue = digitalRead(IR_SENSOR);
  if (irValue == LOW && !objectDetected) {  // LOW = object detected
      objectDetected = true;                 // latch
      Serial.println("IR Sensor: Object Detected! (Latched)");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Welcome Sambhav Jain");
      myDFPlayer.play(1);
      Blynk.virtualWrite(V10, 1);           // turn ON IR switch
      delay(50);                             // ensure Blynk receives the update
  }

  // --- Button (Latched, active LOW) ---
  int btnValue = digitalRead(BUTTON_PIN);
  if (btnValue == LOW && !buttonPressed) {  // pressed
      buttonPressed = true;                  // latch
      Serial.println("Button Pressed! (Latched)");
      Blynk.virtualWrite(V11, 1);            // turn ON Button switch
      delay(50);                             // ensure Blynk receives the update
  }
}
