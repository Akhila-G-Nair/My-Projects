#include<LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);   //defining LCD pins

#define interruptPin 2                    //defining interrupt pin

int rpm = 0, No_of_Pulse = 0, count = 0, rpm_avg = 0;
unsigned long oldtime = 0, time_ms = 0, AVG = 0;

void blink()
{
  detachInterrupt(digitalPinToInterrupt(interruptPin)); // disable interrupt
  if (digitalRead (interruptPin) == HIGH)         //checking whether the interruptPin high
  {
    while (digitalRead (interruptPin) == HIGH);   //wait till the interruptPin high
    No_of_Pulse++;
//    Serial.println (No_of_Pulse);
  }
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, HIGH); // enable interrupt
}

void setup()
{
  Serial.begin (9600);
  lcd.begin(16, 2);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), blink, HIGH); // enable interrupt
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("___TACHOMETER___");
}

void loop()
{
  time_ms = millis() - oldtime;                 //finds the time
  rpm = (No_of_Pulse * 60000) / time_ms ;       //calculates rpm
  oldtime = millis();                           //saves the current time
  No_of_Pulse = 0;
  AVG = AVG + rpm;                              //adding rpm to find average
  count++;
//  Serial.println ("Count: " + String (count) + " RPM: " + String (rpm));
  if (count == 6) 
  {
    rpm_avg = AVG / 6;                         // taking average of 6 values
    lcd.setCursor(0, 1);
    lcd.print("RPM -->         ");
    lcd.setCursor(8, 1);
    lcd.print (String(rpm_avg));             //printing result
    AVG = 0;
    count = 0;
  }
  delay (1000);
}
