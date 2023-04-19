#include <Wire.h>
#include <String.h>
#include <LiquidCrystal_PCF8574.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>

#include "DHT.h"
#define DHTPIN 6
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
// DS1302接線指示: 可依需求修改
// DS1302 CLK/SCLK --> 10
// DS1302 DAT/IO --> 9
// DS1302 RST/CE --> 8
// DS1302 VCC --> 3.3v - 5v
// DS1302 GND --> GND

ThreeWire myWire(9, 10, 8); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

LiquidCrystal_PCF8574 lcd(0x27); // 設定i2c位址，一般情況就是0x27和0x3F兩種

byte col, row, nb = 0, bc = 0;                            // general
//int bb[8];  // 若編譯出現錯誤，請用這行
byte bb[8];  

void setup ()
{
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);  //16x2的LCD
  //lcd.begin(20, 4); //20x4的LCD
  lcd.setBacklight(255); //背光設到最大
  lcd.clear(); //清除畫面
  Serial.print("compiled: ");
  Serial.print(__DATE__);
  Serial.println(__TIME__);

  Rtc.Begin();
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  printDateTime(compiled);
  Serial.println();
  
  if (!Rtc.IsDateTimeValid())
  {
    Serial.println("RTC lost confidence in the DateTime!");
    Rtc.SetDateTime(compiled);
  }

  if (Rtc.GetIsWriteProtected())
  {
    Serial.println("RTC was write protected, enabling writing now");
    Rtc.SetIsWriteProtected(false);
  }

  if (!Rtc.GetIsRunning())
  {
    Serial.println("RTC was not actively running, starting now");
    Rtc.SetIsRunning(true);
  }
  RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled)
  {
    Serial.println("RTC is older than compile time!  (Updating DateTime)");

    Rtc.SetDateTime(compiled);
  }
  else if (now > compiled)
  {
    Serial.println("RTC is newer than compile time. (this is expected)");
    Rtc.SetDateTime(compiled);
  }
  else if (now == compiled)
  {
    Serial.println("RTC is the same as compile time! (not expected but all is fine)");
  }
}

void loop ()
{
  RtcDateTime now = Rtc.GetDateTime();

  printDateTime(now);
  Serial.println();

  if (!now.IsValid())
  {
    Serial.println("RTC lost confidence in the DateTime!");
   
  }

  lcd.clear(); 

  if(now.Hour()>11){
    lcd.setCursor(2, 0);
    lcd.print("P");
    lcd.setCursor(3, 0);
    lcd.print("M");
  }else{
    lcd.setCursor(2, 0);
    lcd.print("A");
    lcd.setCursor(3, 0);
    lcd.print("M");
  }
 
  lcd.setCursor(10, 0);
  lcd.print(now.Hour());
  lcd.print(":");
  lcd.print(now.Minute());

  float h = dht.readHumidity();   //取得濕度
  float t = dht.readTemperature();  //取得溫度C

  lcd.setCursor(1, 1); 
  lcd.print(h);
  lcd.setCursor(5, 1);
  lcd.print("%");


  lcd.setCursor(9, 1);  
  lcd.print(t);
  lcd.setCursor(13, 1);
  lcd.print((char)223); 
  lcd.setCursor(14, 1);
  lcd.print("C");
  delay(10000); // 10秒更新一次
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
  char datestring[20];

  snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
             dt.Month(),
             dt.Day(),
             dt.Year(),
             dt.Hour(),
             dt.Minute(),
             dt.Second() );
  Serial.print(datestring);
}


int freeRam(void) {
  extern int  __bss_end, *__brkval;
  int free_memory;
  if ((int)__brkval == 0) {
    free_memory = ((int)&free_memory) - ((int)&__bss_end);
  }
  else {
    free_memory = ((int)&free_memory) - ((int)__brkval);
  }
  return free_memory;
}
