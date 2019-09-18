#include <Wire.h>
#include "pitches.h"
const byte slaveId = 1;
int buzzer = 7;
int flag1 = 0; 

             
const int pin = 8;
int numTurns = 0;
float factor = 0;
unsigned long time;
int times; 

const int red = 11;
const int green = 10;
const int blue = 9;

//--------------------------------------------

// notes in the melody:
int melody[] = {
  NOTE_G3, NOTE_B3, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_B3, NOTE_A3, NOTE_C4,
  NOTE_G3, NOTE_D4, NOTE_C4, NOTE_B3, NOTE_C4, NOTE_D4, NOTE_G3, NOTE_C4,
  NOTE_B3, NOTE_A3
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 8, 8, 8
};

//--------------------------------------------

int timedOutMelody[] = {
  NOTE_G3, NOTE_G3, NOTE_G3, NOTE_G2
};

int timedOutDurations[] = {
  2, 2, 2, 1
};

//--------------------------------------------

int wonMelody[] = {
  NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_B4, NOTE_F4, NOTE_G4, NOTE_F4,
  NOTE_G4
};

int wonDurations[] = {
  8, 8, 8, 4, 4, 4, 8, 8, 2
};

//--------------------------------------------

void playMainMelody() {
  for (int thisNote = 0; thisNote < 18; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
     
     if(flag1 == 1){
      won();
    }
    factor = 1.0 + (numTurns/2.0);
    Serial.println(factor);
    float noteDuration = 1000 / (noteDurations[thisNote] * factor);
    Serial.println(noteDuration);
    tone(pin, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    // stop the tone playing:
    noTone(pin);
  }
  /*++numTurns;
  if (time > 5000) {
    numTurns = 0;
    timedOut();
    delay(1000);
    time = millis();
    return;
  }*/
}

void timedOut() {
  //Turn on LED to be red
  analogWrite(red, 255);
  
  //Play timedOutMelody
  for(int i = 0; i < 4; ++i) {
    float timedOutDuration = 1000 / timedOutDurations[i];
    tone(pin, timedOutMelody[i], timedOutDuration);
    int pauseBetweenNotes = timedOutDuration * 1.30;
    delay(pauseBetweenNotes);
    
    // stop the tone playing:
    noTone(pin);
  }

  //Turn off LED
  analogWrite(red, 0);
}

void wrongButton() {
   //Turn on LED to be red
   analogWrite(red, 255);
   
   tone(pin, NOTE_G2, 1000);
   delay(1000);
   noTone(pin);
   tone(pin, 0, 500);
   delay(500);
   noTone(pin);
   
   //Turn off LED
   analogWrite(red, 0);
   
}


void won() {
  //Turn on LED to be red
  //analogWrite(green, 255);
  
  //Play timedOutMelody
  for(int i = 0; i < 9; ++i) {
   
    float wonDuration = 1000 / wonDurations[i];
    tone(pin, wonMelody[i], wonDuration);
    int pauseBetweenNotes = wonDuration * 1.30;
    delay(pauseBetweenNotes);
    
    // stop the tone playing:
    noTone(pin);
   
  }

  //Turn off LED
  //analogWrite(green, 0);
}

  //Turn off LED
  //analogWrite(green, 0);


void playB(){
   tone(buzzer,2000);
   delay(100);
   Serial.println("tone 1");
   tone(buzzer,500);
   delay(100);
   Serial.println("tone 2");
   tone(buzzer,1000);
   delay(100);
   Serial.println("tone 3");
   tone(buzzer,505); 
   delay(100);
   Serial.println("tone 4");
     }

//-------------------------------------------------

void setup()
{
  Wire.begin(slaveId); 
  Wire.onReceive(receiveEvent);
 // Wire.begin(); 
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW); 
  
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  time = millis();   
  Serial.begin(9600);
}

void loop()
{
//    if(flag1 == 1){
//      won();
//    }
//     
    playMainMelody();


     
}

void receiveEvent(int howMany)
{
  char inChar;
  
  while(Wire.available() > 0)
  {
    inChar = Wire.read();  

     if (inChar == 'B')
    {
      Serial.print("B has been pressed");
     // analogWrite(buzzer,200);
    //playB();
    // playMainMelody();
      //++numTurns;
     Serial.print("after playMainMelody()");
     //delay(3000);
      //  tone(buzzer,0); 
     //playMainMelody();
    }



    else if (inChar == 'J')
    {
     analogWrite(red, 255);
     analogWrite(green, 0);
     analogWrite(blue, 0);
     delay(500000);
     analogWrite(red, 250);
     analogWrite(green, 250);
     analogWrite(blue, 0);
     delay(500000);
     analogWrite(red, 0);
     analogWrite(green, 255);
     analogWrite(blue, 0);
     delay(500000);
     analogWrite(red, 0);
     analogWrite(green, 0);
     analogWrite(blue, 0);
       Wire.beginTransmission(2);
      Wire.write('B');
      Wire.endTransmission();
 
    }


    
    else if (inChar == 'R')
    {
      Serial.println("red");
      analogWrite(red, 255);
      analogWrite(green, 0);
      analogWrite(blue, 0);
      tone(buzzer,1000);
      delay(100000);
      analogWrite(red, 0);
      noTone(buzzer);
    
    }
    else if (inChar == 'Y')
    {
      Serial.println("yellow");
     analogWrite(red, 250);
      analogWrite(green, 250);
      analogWrite(blue, 0);
    }
    else if (inChar == 'G')
    {
      Serial.println("green");
      analogWrite(red, 0);
      analogWrite(green, 255);
      analogWrite(blue, 0);
      delay(110000);
      analogWrite(green, 0);
    }
    else if (inChar == 'O')
    {
      Serial.println("reset");
      analogWrite(red, 0);
      analogWrite(green, 0);
      analogWrite(blue, 0);
    }
    else if (inChar == 'H')
    {
      digitalWrite(13, HIGH);
    }
    else if (inChar == 'L')
    {
      digitalWrite(13, LOW);
    }

    
    else if (inChar == 'K')
    {
      for(int i = 0; i < 10; ++i) {
      analogWrite(red, random(255));
      analogWrite(green, random(255));
      analogWrite(blue, random(255));
      delay(100000); 
      }
      analogWrite(red, 0);
      analogWrite(green, 0);
      analogWrite(blue, 0);
      
    }
    
     else if (inChar == 'V')
    {
        flag1 = 1; 
    }

     else if (inChar == 'I')
    {
        flag1 = 0; 
    }
    
    else if (inChar == 'W')
    {
       wrongButton();  
     //  tone(pin, NOTE_G2, 1000);
       tone(buzzer,600);
      // delay(100000); 
    }

    else if (inChar == 'F')
    {
       noTone(buzzer);
    }
  }
}
