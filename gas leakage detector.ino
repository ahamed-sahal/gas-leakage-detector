#define BLYNK_TEMPLATE_ID "TMPLXXXX"
#define BLYNK_TEMPLATE_NAME "GasDetector"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// WiFi credentials
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// LCD (change address to 0x3F if not working)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin definitions
#define MQ2_PIN D5
#define GREEN_LED D3
#define YELLOW_LED D4
#define RED_LED D2
#define BUZZER D8
#define RELAY D0

bool alertSent = false;

void setup() {
  Serial.begin(9600);

  // Pin setup
  pinMode(MQ2_PIN, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(RELAY, OUTPUT);

  // Initial OFF state
  digitalWrite(BUZZER, LOW);
  digitalWrite(RELAY, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);

  // LCD init
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("System Starting");

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  delay(2000);
}

void loop() {
  Blynk.run();

  int gas = digitalRead(MQ2_PIN);
  Serial.println(gas);   // debug

  lcd.clear();

  // ⚠️ NOTE: MQ2 logic may be reversed — this version assumes HIGH = GAS
  if (gas == HIGH) {
    
    // 🔴 Gas Leak Condition
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);

    digitalWrite(BUZZER, HIGH);
    digitalWrite(RELAY, HIGH);   // Fan ON

    lcd.setCursor(0, 0);
    lcd.print("GAS LEAK!");
    lcd.setCursor(0, 1);
    lcd.print("Danger!");

    if (!alertSent) {
      Blynk.logEvent("gas_alert", "LPG Gas Leak Detected!");
      alertSent = true;
    }

  } else {

    // 🟢 Safe Condition
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);

    digitalWrite(BUZZER, LOW);
    digitalWrite(RELAY, LOW);   // Fan OFF

    lcd.setCursor(0, 0);
    lcd.print("System Safe");

    alertSent = false;
  }

  delay(500);
}
