#include <Wire.h>
//const int buttonStart = 7; 
int buttonState = 0; 

const int button1 = 2;     // the number of the pushbutton pin
const int button2 = 3; 
const int button3 = 4;     // the number of the pushbutton pin
const int button4 = 5;
const int button5 = 6;     // the number of the pushbutton pin
const int button6 = A0; 
const int button7 = A1; 

const int ledPin =  13;        // the number of the LED pin
const int LED1 = 8;            //What set pins the LED are using
const int LED2 = 9;
const int LED3 = 10;
const int LED4 = 11;
const int LED5 = 12;
const int LED6 = 13;
const int LED7 = 7;
 
int LEDcounter = 0; 

int temp1 = 0; 
int buttonStateUp = 0;         // variable for reading the pushbutton status
int buttonStateDown = 0;
int buttonStateUp2 = 0;         // variable for reading the pushbutton status
int buttonStateDown2 = 0;
int buttonStateUp3 = 0;         // variable for reading the pushbutton status
int buttonStateDown3 = 0;
int buttonStateUp4 = 0;

int pressesCounterUp  = 0 ;          // helped to know when the button is being released.  
int pressesCounterDown = 0;  
int pressesCounterUp2  = 0 ;          // helped to know when the button is being released.  
int pressesCounterDown2 = 0;  
int pressesCounterUp3  = 0 ;          // helped to know when the button is being released.  
int pressesCounterDown3 = 0; 
int pressesCounterUp4  = 0 ; 

int ledArray[7] = {7,8,9,10,11,12,13};

int order[7] =  {7,8,9,10,11,12,13};



//-----------------------------------------functions
void randomarray(int *array1){
    for (int i=0; i < 7; i++) {
      int n = random(0, 7); 
      int temp = array1[n];
      array1[n] =  array1[i];
      array1[i] = temp;
    } 
}        

//------------------------------------------blinking()
void blinking(){
  
  Wire.beginTransmission(1);
  Wire.write('K');
  Wire.endTransmission();


   for (int i=0; i < 3; i++) {
      digitalWrite(7, LOW);  
      digitalWrite(8, LOW); 
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      delay(425); 
      digitalWrite(8, HIGH);  
      digitalWrite(9, HIGH); 
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);
      digitalWrite(7, HIGH);
      delay(425); 
   }
}

//---------------------------------------------- Reset to start a new game
void restGame(){
    blinking(); 

     
    digitalWrite(13, LOW);
    delay(375);  
    digitalWrite(12, LOW);
    delay(375); 
    digitalWrite(11, LOW);
    delay(375); 
    digitalWrite(10, LOW);
    delay(375);
    digitalWrite(9, LOW);
    delay(375);
    digitalWrite(8, LOW);
    delay(375); 
    digitalWrite(7, LOW);
    randomarray(ledArray);
    randomarray(ledArray);

    
     Wire.beginTransmission(2);
     Wire.write('V');
     Wire.endTransmission(); 
//     delay(2000); 
//
//     Wire.beginTransmission(2);
//     Wire.write('I');
//     Wire.endTransmission();
      
}

//-----------------------------------------------------Reset back to beginning of game
void startReset(){
  Wire.beginTransmission(1);
  Wire.write('R');
  Wire.endTransmission();
 
  Wire.beginTransmission(1);
  Wire.write('W');
  Wire.endTransmission();




  
  delay(550); 
  Wire.beginTransmission(1);
  Wire.write('F');
  Wire.endTransmission();
  
  for (int i=0; i < 7; i++) {
         digitalWrite(ledArray[i], LOW); 
  }
  Serial.print("Reseting back to beginning\n"); 
  temp1 = 0; 
  LEDcounter = 0; 
     
}

//------------------------------------------------------- Check 
void orderCheck(int LEDcounter1, int LED){
  int ledC = order[LEDcounter1]; 
  if (ledC != LED){
     Serial.print("They do not match\n");
     //delay(200); 
     Wire.beginTransmission(2);
     Wire.write('D');
     Wire.endTransmission();
      
     startReset();}
  else{
    Serial.print("They match!!\n");
     Wire.beginTransmission(2);
     Wire.write('R');
     Wire.endTransmission();
     Wire.beginTransmission(1);
     Wire.write('G');
     Wire.endTransmission(); 
         // delay(1000);
    LEDcounter = LEDcounter + 1; }
}

//--------------------------
void winChecker(){
 int LED1state = digitalRead(LED1);
 int LED2state = digitalRead(LED2);
 int LED3state = digitalRead(LED3);
 int LED4state = digitalRead(LED4);
 int LED5state = digitalRead(LED5);
 int LED6state = digitalRead(LED6);
 int LED7state = digitalRead(LED7);

 if (LED1state == HIGH && LED2state == HIGH && LED3state == HIGH && LED4state == HIGH && LED5state == HIGH && LED6state == HIGH && LED7state == HIGH)  {
      Serial.print("Player has won the game\n\n"); 

     Wire.beginTransmission(1);
     Wire.write('V');
     Wire.endTransmission(); 
     delay(2000); 

     Wire.beginTransmission(1);
     Wire.write('I');
     Wire.endTransmission();
      Serial.print("The Game will now Reset"); 
      delay(700); 
      restGame(); 
 }
}  







void setup()
{

  Wire.begin(); 
  Serial.begin(9600);
//  pinMode(buttonStart, INPUT);
//  Serial.print("start");
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(button5, INPUT);
  pinMode(button6, INPUT);
  pinMode(button7, INPUT);
    Serial.print("setup");

       pinMode(ledPin, OUTPUT);
   pinMode(LED1, OUTPUT);    //For LED that represents 1
   pinMode(LED2, OUTPUT);    //For LED that represents 2
   pinMode(LED3, OUTPUT);    //For LED that represents 4
   pinMode(LED4, OUTPUT);    //For LED that represents 4
   pinMode(LED5, OUTPUT);    //For LED that represents 4
   pinMode(LED6, OUTPUT);    //For LED that represents 4
   pinMode(LED7, OUTPUT);    //For LED that represents 4
   
  for(int i = 0; i < 7; i++){
    Serial.println(ledArray[i]);
  }

  randomarray(ledArray);
  randomarray(ledArray);
  randomarray(ledArray);
  randomarray(ledArray);
  Serial.println("\n");

  for(int i = 0; i < 7; i++) {
    Serial.println(ledArray[i]);
  }
}

void loop()
{

  buttonStateUp = digitalRead(button1);
  buttonStateDown = digitalRead(button2);
  buttonStateUp2 = digitalRead(button3);
  buttonStateDown2 = digitalRead(button4);
  buttonStateUp3 = digitalRead(button5);
  buttonStateDown3 = digitalRead(button6);
  buttonStateUp4 = digitalRead(button7);


//-----------------------------------Button 1
if( pressesCounterUp !=  buttonStateUp){        //if the counter and the button isnt pressed
  if (buttonStateUp == HIGH) {  // if they are the same it means that button is being held    
      digitalWrite(ledArray[0], HIGH);
      temp1 = ledArray[0];
      orderCheck(LEDcounter, temp1); 
      Serial.print("Button 1 has been pressed\n"); 
      }
}

//-----------------------------------Button 2
if( pressesCounterDown !=  buttonStateDown){    //if the counter and the button isnt pressed  
  if (buttonStateDown == HIGH) {                // if they are the same it means that button is being held/
      digitalWrite(ledArray[1], HIGH);
      temp1 = ledArray[1];
      orderCheck(LEDcounter, temp1);
      Serial.print("Button 2 has been pressed\n");
      }
}

//-----------------------------------Button 3
if( pressesCounterUp2 !=  buttonStateUp2){        //if the counter and the button isnt pressed
  if (buttonStateUp2 == HIGH) {                  // if they are the same it means that button is being held    
      digitalWrite(ledArray[2], HIGH);
      temp1 = ledArray[2];
      orderCheck(LEDcounter, temp1); 
      Serial.print("Button 3 has been pressed\n");  
      }
}

//-----------------------------------Button 4
if( pressesCounterDown2 !=  buttonStateDown2){    //if the counter and the button isnt pressed  
  if (buttonStateDown2 == HIGH) {                // if they are the same it means that button is being held
          digitalWrite(ledArray[3], HIGH);
      temp1 = ledArray[3];
      orderCheck(LEDcounter, temp1); 
      Serial.print("Button 4 has been pressed\n");  
    }
}

//-----------------------------------Button 5
if( pressesCounterUp3 !=  buttonStateUp3){        //if the counter and the button isnt pressed
  if (buttonStateUp3 == HIGH) {                  // if they are the same it means that button is being held   
     digitalWrite(ledArray[4], HIGH); 
      temp1 = ledArray[4];
      orderCheck(LEDcounter, temp1); 
      Serial.print("Button 5 has been pressed\n");   
   }
}

//-----------------------------------Button 6
if( pressesCounterDown3 !=  buttonStateDown3){    //if the counter and the button isnt pressed  
  if (buttonStateDown3 == HIGH) {                // if they are the same it means that button is being held
      digitalWrite(ledArray[5], HIGH);
      temp1 = ledArray[5];
      orderCheck(LEDcounter, temp1);   
      Serial.print("Button 6 has been pressed\n"); 
    }
}


//----------------------------------Button 7
if( pressesCounterUp4 !=  buttonStateUp4){        //if the counter and the button isnt pressed
  if (buttonStateUp4 == HIGH) {
     digitalWrite(ledArray[6], HIGH);
     temp1 = ledArray[6];
     orderCheck(LEDcounter, temp1);   
     Serial.print("Button 7 has been pressed\n"); 
   }
}
   
   pressesCounterUp = buttonStateUp;          //if the button held that will stay 1 and it will not go throught the other if statement 
   pressesCounterDown = buttonStateDown;
   pressesCounterUp2 = buttonStateUp2;          //if the button held that will stay 1 and it will not go throught the other if statement 
   pressesCounterDown2 = buttonStateDown2;
   pressesCounterUp3 = buttonStateUp3;          //if the button held that will stay 1 and it will not go throught the other if statement 
   pressesCounterDown3 = buttonStateDown3;
   pressesCounterUp4 = buttonStateUp4; 

//========================================================================
//          
  Wire.beginTransmission(1);
  Wire.write('H');
  Wire.endTransmission();
 
  delay(50);
  
  Wire.beginTransmission(1);
  Wire.write('L');
  Wire.endTransmission();
 
  delay(50);
  
  Wire.beginTransmission(2);
  Wire.write('H');
  Wire.endTransmission();
 
  delay(50);
  
  Wire.beginTransmission(2);
  Wire.write('L');
  Wire.endTransmission();
  delay(50);

    winChecker();
}
