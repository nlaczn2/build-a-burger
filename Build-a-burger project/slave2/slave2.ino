#include <Wire.h>
#include <LiquidCrystal.h>
const byte slaveId = 2;

int flag1 = 0; 
const int buttonStart = 7; 
int buttonState = 0; 


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int buttonPin = 8;     // the number of the pushbutton pin

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//DECLARE VARIABLES
String quote= "In the end, everything is a gag.";
    //         0abcdefghijklmnopqrstuvwxyz
const int qLength = quote.length(); // 16 length
const int scrollLength = (qLength +(qLength - 24));

int startFlag = 0;
int timeer = 0;


void start(){
      Serial.print("ur in start\n"); 
  int flagger = 0;
  while(flagger == 0){
      buttonState = digitalRead(buttonStart);
      if(buttonState == HIGH){
         Serial.print("start button was pressed"); 
        flagger = 1;
         Wire.beginTransmission(1);
         Wire.write('J');
         Wire.endTransmission();
         delay(4000); 
        timeer = 0; 
   
      }
      Serial.print("in the while\n"); 
  }
}




void setup()
{
  Wire.begin(slaveId); 
  Wire.onReceive(receiveEvent);
  Wire.begin(); 
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);    
  lcd.begin(16, 2);    
  Serial.begin(9600);
  lcd.clear();
        Serial.print("hello\n");
}

void loop()
{
     lcd.setCursor(0,0);
     lcd.print(timeer);
     lcd.setCursor(0,1);
     delay(1000); 
     lcd.clear();
     timeer++; 


      if(flag1 == 1){
          flag1 = 0; 
          Serial.print("ur in the if\n"); 
        start(); 
      }


//     if(timmer >5){
//     Wire.beginTransmission(1);
//     Wire.write('D');
//     Wire.endTransmission();
//     }
     
}

void receiveEvent(int howMany)
{
  char inChar;
  
  while(Wire.available() > 0)
  {
    inChar = Wire.read();  



  
    if (inChar == 'D')
    {
       lcd.setCursor(0,0);
       lcd.print("WRONG!");
       lcd.setCursor(0,1);
       delay(150000); 
        lcd.clear();
    }

  if (inChar == 'R')
    {
       lcd.setCursor(0,0);
       lcd.print("NICE! YOU WERE");
       lcd.setCursor(0,1);
       lcd.print("RIGHT!");
       delay(200000); 
       lcd.clear();
    }
  
    if (inChar == 'T')
    {
      digitalWrite(13, HIGH);
    }

    else if (inChar == 'V')
    {
        flag1 = 1; 
    }

     else if (inChar == 'I')
    {
        flag1 = 0; 
    }
    
      else if (inChar == 'B')
    {
      timeer  = 0; 
    }

    
    if (inChar == 'H')
    {
      digitalWrite(13, HIGH);
    }
    else if (inChar == 'L')
    {
      digitalWrite(13, LOW);
    }
  }
}
