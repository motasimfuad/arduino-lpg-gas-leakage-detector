/*
 * ============================================================
 * LPG Gas Leakage Detection and Alert System
 * ============================================================
 * Author      : Mohammad Motasim Fuad
 * Institution : Daffodil International University
 * Year        : 2018
 * Platform    : Arduino Pro Mini (ATmega328P, 5V, 16MHz)
 * Sensor      : MQ-Series Gas Sensor (MQ-2 / MQ-6)
 * License     : MIT
 *
 * Description :
 *   Monitors the digital comparator output (DOUT) of an
 *   MQ-series gas sensor module. On HIGH signal (gas detected
 *   above safety threshold), activates a piezoelectric buzzer via
 *   BC547 NPN transistor and displays an alert on a 16x2 LCD.
 *   Displays "safe" state continuously when no leakage detected.
 *
 * Pin Mapping :
 *   A4 (D18) -> MQ Sensor DOUT (comparator output)
 *   D13      -> BC547 Base via 1kΩ resistor -> Buzzer
 *   D7       -> LCD RS
 *   D8       -> LCD EN
 *   D9       -> LCD D4
 *   D10      -> LCD D5
 *   D11      -> LCD D6
 *   D12      -> LCD D7
 * ============================================================
 */

#include <LiquidCrystal.h>

/* --- Pin Definitions --- */
const uint8_t PIN_GAS_SENSOR  = 18;   // A4 used as digital input
const uint8_t PIN_BUZZER      = 13;   // To BC547 base via 1kΩ

/* --- LCD Configuration (RS, EN, D4, D5, D6, D7) --- */
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

/* --- Timing Constants --- */
const uint16_t SENSOR_WARMUP_MS  = 10000;  // 10-sec warm-up
const uint16_t POLL_INTERVAL_MS  = 500;    // Poll every 500ms
const uint16_t BLINK_ON_MS       = 300;    // Buzzer blink ON
const uint16_t BLINK_OFF_MS      = 200;    // Buzzer blink OFF

/* --- State Tracking --- */
bool previousLeakState = false;

/* ========================================================== */
/*  SETUP                                                     */
/* ========================================================== */
void setup() {
  Serial.begin(9600);
  Serial.println(F("LPG Gas Leakage Detector - Initializing..."));

  pinMode(PIN_GAS_SENSOR, INPUT);
  pinMode(PIN_BUZZER,     OUTPUT);
  digitalWrite(PIN_BUZZER, LOW);

  lcd.begin(16, 2);
  lcd.clear();

  /* Sensor warm-up indication */
  lcd.setCursor(0, 0);
  lcd.print(F("  LPG Detector  "));
  lcd.setCursor(0, 1);
  lcd.print(F("  Warming Up... "));

  delay(SENSOR_WARMUP_MS);

  /* Ready screen */
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("  System Ready  "));
  lcd.setCursor(0, 1);
  lcd.print(F(" Monitoring...  "));
  delay(1500);

  Serial.println(F("System ready. Monitoring active."));
}

/* ========================================================== */
/*  HELPERS                                                   */
/* ========================================================== */
void displaySafeState() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("  System Ready  "));
  lcd.setCursor(0, 1);
  lcd.print(F(" No LPG Leakage "));
}

void displayAlertState() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F(" LPG Gas Leakage"));
  lcd.setCursor(0, 1);
  lcd.print(F("     ALERT!     "));
}

void activateBuzzer() {
  digitalWrite(PIN_BUZZER, HIGH);
  delay(BLINK_ON_MS);
  digitalWrite(PIN_BUZZER, LOW);
  delay(BLINK_OFF_MS);
}

/* ========================================================== */
/*  MAIN LOOP                                                 */
/* ========================================================== */
void loop() {
  bool gasDetected = (digitalRead(PIN_GAS_SENSOR) == HIGH);

  if (gasDetected) {
    if (!previousLeakState) {
      displayAlertState();
      Serial.println(F("[ALERT] LPG gas leakage detected!"));
      previousLeakState = true;
    }
    activateBuzzer();
  } else {
    digitalWrite(PIN_BUZZER, LOW);
    if (previousLeakState) {
      displaySafeState();
      Serial.println(F("[SAFE] No gas leakage detected."));
      previousLeakState = false;
    }
    delay(POLL_INTERVAL_MS);
  }
}
