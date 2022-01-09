#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h> 
#include <Servo.h>
#include <TimeLib.h>
#include <WidgetRTC.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);    
WidgetRTC rtc;
Servo servo;

char auth[] = ""; // your auth token
char ssid[] = "";   // your ssid
char pass[] = "";   // your password
int i,j,n,s,d;
BlynkTimer timer;
bool pinValue=0;
#define trig D6
#define echo D5
#define relay D7
long duration, inches, cm;
void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  servo.attach(2); // pin 4  3v3 gnd
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(relay, OUTPUT);
  timer.setInterval(100L,notify); 
  lcd.init();   // initilazing LCD
  lcd.backlight();// 
  rtc.begin();

 /*timer.setInterval(10L,Mlevel); */
  digitalWrite(relay, HIGH);
}
BLYNK_WRITE(V3)
{
  pinValue=param.asInt();
}
void notify()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(4);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long t = pulseIn(echo, HIGH);
  long cm = t / 29 / 2;
  Serial.println(cm);
  long level= 25-cm; // 25 is changing according to depth
  if (level<0)
  level=0;
  Blynk.virtualWrite(V4, level);
}


//  Loop section
  void loop()
{
  Blynk.run();
  lcd.setCursor(0, 0);
  lcd.print("Besleme olcu:");
  lcd.print(n);
  delay(3000);
  lcd.clear(); 
  
  lcd.setCursor(0 ,0 );
  lcd.print("Besleme saati:");
  lcd.setCursor( 0,1 );
  lcd.print(s);
  lcd.print(":");
  lcd.print(d);
  delay(3000);
  lcd.clear();

  timer.run();
}

BLYNK_WRITE(V0)
{
  n=param.asInt();
}

BLYNK_WRITE(V2)
{
  servo.write(180);
  delay(2000);
  servo.write(0);
}
BLYNK_WRITE(V1)
{
  j=param.asInt();
  if(j==1)
  {
    Serial.print(n);
    servo.write(0);
    delay(1000);
  }
  for(int i=1;i<=n;i++)
  {
    Serial.print(i);
    servo.write(180);
    delay(1000);
    servo.write(0);
    delay(1000);
  }
  lcd.clear();
  s=hour();
  Serial.print(s);
  Serial.print(":");
  d=minute();
  Serial.print(d);
  }

 /*void Mlevel()
  {
    if(pinValue==1)
      {
        digitalWrite(relay, LOW);
        lcd.setCursor(0,1);
        lcd.print("motor is on");
        lcd.clear();
      }else if(pinValue==0)
      {
        digitalWrite(relay,HIGH);
        lcd.setCursor(0,1);
        lcd.print("motor is off");
        lcd.clear();
      } 

      digitalWrite(trig, LOW);
      delayMicroseconds(4);
      digitalWrite(trig, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig, LOW);
      long t= pulseIn(echo, HIGH);
      long cm=t/29/2;

     
      
        Blynk.virtualWrite(V4, cm);
      
      Serial.println(cm);
      lcd.setCursor(0 , 1);
     
      lcd.print("Mama seviyesi:");
      lcd.print(cm);
      lcd.print(" ");
      
     
      
      
  } 
  */
  


  
