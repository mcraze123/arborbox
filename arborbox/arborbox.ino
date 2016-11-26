#include "SPI.h"
#include "Ethernet.h"
#include "WebServer.h"
#include "DHT.h"
#include <DS1307RTC.h>
#include <Time.h>
#include <TimeAlarms.h>
#include <Wire.h>
#include <ambi101.h>
#include <moistureSensor.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <dtwrapper.h>
#include <LiquidCrystal.h>

// Pin setup
#define RELAY1_PIN 28
#define RELAY2_PIN 26
#define LIGHT_SENSOR_PIN 9
#define MOISTURE_SENSOR_PIN 8
#define SOIL_TEMP_SENSOR_PIN 24
#define DHTPIN 22

#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
DTWrapperClass soilTempSensor;
tmElements_t tm;

LiquidCrystal lcd(30, 32, 34, 36, 38, 40);

#define PREFIX ""
static uint8_t mac[6] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
static uint8_t ip[4] = { 192, 168, 1, 100 };
WebServer webserver(PREFIX, 80);

void defaultCmd(WebServer &server, WebServer::ConnectionType type, char *, bool){
  // TO TEST:
  // curl --data "r1=1&r2=1" http://192.168.1.100
  if (type == WebServer::POST){
    bool repeat;
    char name[16], value[16];
    do{
      repeat = server.readPOSTparam(name, 16, value, 16);
      if (strcmp(name, "r1") == 0){
        relay_set(RELAY1_PIN,atoi(value));
      }
      else if(strcmp(name,"r2") == 0){
        relay_set(RELAY2_PIN,atoi(value));
      }
    } while (repeat);
    
    server.httpSeeOther(PREFIX);
    return;
  }

  server.httpSuccess();

  if (type == WebServer::GET){    
    P(html_begin) = "<!DOCTYPE html><html><head><title>Arborbox</title></head><body>";
    P(line_break) = "<br />";
    P(html_end) = "</body></html>";

    server.printP(html_begin);
    
    server.print(ms.read(MOISTURE_SENSOR_PIN));
    server.printP(line_break);
    server.print(lightSensor.read(LIGHT_SENSOR_PIN));
    server.printP(line_break);
    server.print(soilTempSensor.getTempC(SOIL_TEMP_SENSOR_PIN));
    server.printP(line_break);
    server.print(dht.readTemperature());
    server.printP(line_break);
    server.print(dht.readHumidity());
    if (RTC.read(tm)) {
      server.printP(line_break);
      if(tm.Hour >= 0 && tm.Hour < 10){
        server.print("0");
      }
      server.print(tm.Hour);
      server.print(":");
      if(tm.Minute >= 0 && tm.Minute < 10){
        server.print("0");
      }
      server.print(tm.Minute);
      server.print(":");
      if(tm.Second >= 0 && tm.Second < 10){
        server.print("0");
      }
      server.print(tm.Second);
      server.printP(line_break);
      server.print(tm.Day);
      server.print("/");
      server.print(tm.Month);
      server.print("/");
      server.print(tmYearToCalendar(tm.Year));
    }
    server.printP(html_end);
  }
}

void relay_set(int pin, int value){
  if(value == 1){
    digitalWrite(RELAY1_PIN, LOW);
  }
  else{
    digitalWrite(pin, HIGH);
  }
}

void relay_begin(int pin){
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
}

void Repeats2(){
  Serial.println("light cycle off");
  digitalWrite(RELAY1_PIN,HIGH);
}

void Repeats(){
  Serial.println("light cycle on");
  digitalWrite(RELAY1_PIN,LOW);
}

void LightCycleOn(){
  Serial.println("light cycle on");
  digitalWrite(RELAY1_PIN,LOW);
}

void LightCycleOff(){
  Serial.println("light cycle off");
  digitalWrite(RELAY1_PIN,HIGH);
}

void printDigits(int digits){
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println();
}

void setup(){
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Welcome to Arborbox!");
  Ethernet.begin(mac, ip);
  webserver.setDefaultCommand(&defaultCmd);
  webserver.begin();
  dht.begin();
  relay_begin(RELAY1_PIN);
  relay_begin(RELAY2_PIN);
  Wire.begin();
  setSyncProvider(RTC.get);
  if(timeStatus()!=timeSet){
    Serial.println("Unable to sync with the RTC");
  }
  else{
    Serial.println("RTC has set the system time");
  }
  Alarm.alarmRepeat(22,15,0,LightCycleOn);
  Alarm.alarmRepeat(10,15,0,LightCycleOff);
  Alarm.timerRepeat(15,Repeats);
  Alarm.timerRepeat(20,Repeats2);
}

void loop(){
  webserver.processConnection();
  
  digitalClockDisplay();
  Alarm.delay(1000);
  
  lcd.setCursor(0,0);
  if (RTC.read(tm)) {
    if(tm.Hour >= 0 && tm.Hour < 10){
      lcd.print("0");
    }
    lcd.print(tm.Hour);
    lcd.print(":");
    if(tm.Minute >= 0 && tm.Minute < 10){
      lcd.print("0");
    }
    lcd.print(tm.Minute);
    lcd.print(":");
    if(tm.Second >= 0 && tm.Second < 10){
      lcd.print("0");
    }
    lcd.print(tm.Second);
    lcd.print("  ");
    lcd.print(tm.Day);
    lcd.print("/");
    lcd.print(tm.Month);
  }
  lcd.setCursor(0,1);
  lcd.print("SoilWater: ");
  lcd.print(ms.read(MOISTURE_SENSOR_PIN));
  lcd.setCursor(0,1);
  lcd.print("Light: ");
  lcd.print(lightSensor.read(LIGHT_SENSOR_PIN));
  lcd.setCursor(0,1);
  lcd.print("SoilTemp: ");
  lcd.print(soilTempSensor.getTempC(SOIL_TEMP_SENSOR_PIN));
  lcd.setCursor(0,1);
  lcd.print("Temp: ");
  lcd.print(dht.readTemperature());
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(dht.readHumidity());
}
