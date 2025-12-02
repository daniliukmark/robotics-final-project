#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <EEPROM.h>

#define LDR_PIN A0
#define SERVO_PIN 9
#define EEPROM_ADDR_COIN 0

// LCD: RS=12, E=11, D4=5, D5=4, D6=3, D7=2
LiquidCrystal Lcd(12, 11, 5, 4, 3, 2);
Servo myServo;

// Variables
int ldrValue = 0;
int baseline = 0;
int coinCount = 0;
const float smoothing = 0.9;
const int dropThreshold = 150;

void calibrateSensor();
int readLdr();
void updateBaseline(int currentValue);
bool detectCoin(int currentValue);
void updateDisplay();
void openLid();
void closeLid();
void handleCoinDetection();
void incrementCoinCount();
void loadCoinCount();

void setup()
{
  Serial.begin(9600);
  myServo.attach(SERVO_PIN);
  Lcd.begin(16, 2);

  loadCoinCount();
  updateDisplay();
  closeLid();
  calibrateSensor();
}

void loop()
{
  int currentValue = readLdr();
  updateBaseline(currentValue);

  if (detectCoin(currentValue))
  {
    handleCoinDetection();
  }

  delay(200);
}

void calibrateSensor()
{
  baseline = analogRead(LDR_PIN);
  Serial.println("Calibrating...");
}

int readLdr()
{
  int value = analogRead(LDR_PIN);
  Serial.print("Light: ");
  Serial.print(value);
  Serial.print(" | Baseline: ");
  Serial.println(baseline);
  return value;
}

void updateBaseline(int currentValue)
{
  baseline = (smoothing * baseline) + ((1 - smoothing) * currentValue);
}

bool detectCoin(int currentValue)
{
  return currentValue < baseline - dropThreshold;
}

void updateDisplay()
{
  Lcd.clear();
  Lcd.setCursor(0, 0);
  Lcd.print("Coins: ");
  Lcd.print(coinCount);
}

void openLid()
{
  myServo.write(90);
  delay(1000);
}

void closeLid()
{
  myServo.write(180);
  delay(1000);
}

void incrementCoinCount()
{
  coinCount++;
  EEPROM.put(EEPROM_ADDR_COIN, coinCount);
  Serial.print("Coin saved! Total: ");
  Serial.println(coinCount);
}

void loadCoinCount()
{
  EEPROM.get(EEPROM_ADDR_COIN, coinCount);

  bool isValid = coinCount >= 0 && coinCount <= 10000;

  if (!isValid)
  {
    coinCount = 0;
    EEPROM.put(EEPROM_ADDR_COIN, coinCount);
  }

  Serial.print("Loaded coin count: ");
  Serial.println(coinCount);
}

void handleCoinDetection()
{
  incrementCoinCount();
  updateDisplay();

  openLid();
  closeLid();

  delay(1000);
}
