#include <LCD_I2C.h>
LCD_I2C lcd(0x3F); 
#include<SoftwareSerial.h>
SoftwareSerial mySerial(D3, D4);
#include <ThingSpeak.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <EveryTimer.h>
#define PERIOD_MS 1000
EveryTimer timer;
bool active = true;
char thingSpeakAddress[] = "api.thingspeak.com";
unsigned long channelID = *******;
char* readAPIKey = "****************";
char* writeAPIKey = "****************";
unsigned int dataFieldOne = 1;
const char* ssid     = "IOT";
const char* password = "123456789";

#define BLYNK_TEMPLATE_ID "*************"
#define BLYNK_TEMPLATE_NAME "ATTENANCE SYSTEM IOT"
#define BLYNK_AUTH_TOKEN "YUtFvvpZgMUGaT-3FHoz0XexwgNQdokO"
int count = 0;
char input[12];
char reader1[] = "4D0098F0BA9F";
char reader2[] = "4D00990117C2";
char reader3[] = "4D009920887C";
char reader4[] = "4D0098A6592A";
char auth[] = BLYNK_AUTH_TOKEN;
int i;
int pureval;
unsigned int m = 0, act = 0, val, val1, val2, val3, val4, val5;
String inputString = "";
unsigned char a[200];
String predict = "";
unsigned long lastConnectionTime = 0;
long lastUpdateTime = 0;
WiFiClient client;
int gasstate, sec, act1;

String s1 = "717822e221 - Kevin Anand Raj-ENTRY ";
String s2 = "717822e231 - Naresh Kannan-ENTRY ";
String s3 = "717822e236 - Prithive-ENTRY ";
String s4 = "717822e248 - Sriram-ENTRY ";
String s11 = "717822e221 - Kevin Anand Raj-EXIT ";
String s22 = "717822e231 - Naresh Kannan-EXIT ";
String s33 = "717822e236 - Prithive-EXIT ";
String s44 = "717822e248 - Sriram-EXIT ";
int rfid;
int stdid, id1state = 0, id2state = 0, id3state = 0;
void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("SETUP");
  lcd.begin();
  lcd.backlight();
  timer.Every(PERIOD_MS, action);
  lcd.print("    SMART "); 
  lcd.setCursor(5, 1); 
  lcd.print("ATTENANCE");
  Blynk.begin(auth, ssid, password, "blynk.cloud", 80);
  Serial.println("BNlynk Completed");
  ThingSpeak.begin( client );
  delay(3000);
  lcd.clear();
}
void loop()
{
  rfidread();
  delay(100);
  delay(100);
  Blynk.run();
}
int write2TSData( long TSChannel, unsigned int TSField1, String field1Data)
{
  ThingSpeak.setField( TSField1, field1Data );
  int writeSuccess = ThingSpeak.writeFields( TSChannel, writeAPIKey );
  return writeSuccess;
}
void action()
{
  sec++;
}
void rfidread()
{
  if (mySerial.available())
  {
    count = 0;
    while (mySerial.available() && count < 12
    {
      input[count] = mySerial.read();
      count++;
      delay(5);
      Serial.print(input[count]);
    }
    Serial.print(input);                             
  }
  if (strncmp(input, reader1, 12) == 0 && id1state == 0)
  {
    write2TSData(
      channelID,
      dataFieldOne, s1

    );
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("KEVIN");
    lcd.print(",717822e221");
    lcd.setCursor(0, 1);
    lcd.print("ENTRY ");
    Blynk.virtualWrite(V0, "KEVIN  ID:717822e221, ENTRY");
    input[0] = '1';
    delay(3000);
    lcd.clear();
    Blynk.virtualWrite(V0, "                  ");
    sec = 0;
    id1state = 1;
  }
  if (strncmp(input, reader1, 12) == 0 && id1state == 1)
  {
    write2TSData(
      channelID,
      dataFieldOne, s11
    );
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("KEVIN");
    lcd.print(",717822e221");
    lcd.setCursor(0, 1);
    lcd.print("EXIT ");
    Blynk.virtualWrite(V0, "KEVIN  ID:717822e221, EXIT");
    input[0] = '1';
    delay(3000);
    lcd.clear();
    Blynk.virtualWrite(V0, "                  ");
    sec = 0;
    id1state = 0;
  }
  if (strncmp(input, reader2, 12) == 0 && id2state == 0)
  {
    write2TSData(
      channelID,
      dataFieldOne, s2
    );
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("NARESH");
    lcd.print(",717822e231 ");
    lcd.setCursor(0, 1);
    lcd.print("ENTRY ");
    Blynk.virtualWrite(V0, "NARESH  ID:717822e231, ENTRY");
    Serial.print("Card 2 ");
    input[0] = '1';
    delay(3000);
    lcd.clear();
    Blynk.virtualWrite(V0, "                  ");
    sec = 0;
    id2state = 1;
  }
  if (strncmp(input, reader2, 12) == 0 && id2state == 1)
  {
    write2TSData(
      channelID,
      dataFieldOne, s22
    );

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("NARESH");
    lcd.print(",717822e231");
    lcd.setCursor(0, 1);
    lcd.print("EXIT ");
    Blynk.virtualWrite(V0, "NARESH  ID:717822e231, EXIT");
    Serial.print("Card 2 ");
    input[0] = '1';
    delay(3000);
    lcd.clear();
    Blynk.virtualWrite(V0, "                  ");
    sec = 0;
    id2state = 0;
  }
