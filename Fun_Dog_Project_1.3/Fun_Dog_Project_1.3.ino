#include <Servo.h>
Servo Servo1;

int angle=90;
int x = 0;              
int state = 0;          
unsigned long previousMillis = 0;
unsigned long ServoMillis = 0;   
const long interval = 1000; 
const long ServoDuration = 3000; 
bool countdownActive = false;  
bool ServoOn = false;            

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, INPUT_PULLUP);    
  pinMode(10, INPUT_PULLUP);   
  pinMode(11, INPUT_PULLUP);   
  Servo1.attach(12);         

  Servo1.write(0);       

  
  Serial.begin(9600);
}

void loop() {
  
  if (!countdownActive) {
    handleButtons();   
  }

  
  if (digitalRead(11) == LOW && !countdownActive) { 
    countdownActive = true;         
    previousMillis = millis();      
    Serial.println("Countdown started!");  
  }

  
  if (countdownActive) {
    unsigned long currentMillis = millis();

    
    if (x == 0) {
      countdownActive = false;  
      Servo1.write(angle);   
      ServoOn = true;             
      ServoMillis = millis();     
      Serial.println("Countdown finished, Servo ON!");  
    } 
    else if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;  
      if (x > 0) {
        x--;  
        displayDigit(x);  
        Serial.print("Countdown running, x = ");
        Serial.println(x);  
      }
    }
  }

  
  if (ServoOn) {
    unsigned long currentMillis = millis();
    if (currentMillis - ServoMillis >= ServoDuration) {
      Servo1.write(0);  
      ServoOn = false;          
      Serial.println("Servo turned off!");  
    }
  }
}


void handleButtons() {
  
  if (digitalRead(9) == LOW && digitalRead(10) == HIGH && !state) {
    x++;
    if (x > 9) x = 0;   
    state = 1;
    displayDigit(x);    
    Serial.print("Incremented to: ");
    Serial.println(x);  
  }

  
  if (digitalRead(9) == HIGH && digitalRead(10) == LOW && !state) {
    x--;
    if (x < 0) x = 9;   
    state = 1;
    displayDigit(x);    
    Serial.print("Decremented to: ");
    Serial.println(x);  
  }

  
  if (digitalRead(9) == HIGH && digitalRead(10) == HIGH) {
    state = 0;
  }
}


void displayDigit(int num) {
  switch (num) {
    case 0:
      digitalWrite(8, LOW);
      digitalWrite(7, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(2, HIGH);
      break;

    case 1:
      digitalWrite(8, LOW);
      digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(2, LOW);
      break;

    case 2:
      digitalWrite(8, HIGH);
      digitalWrite(7, LOW);
      digitalWrite(6, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(2, HIGH);
      break;

    case 3:
      digitalWrite(8, HIGH);
      digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(2, HIGH);
      break;

    case 4:
      digitalWrite(8, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(2, LOW);
      break;

    case 5:
      digitalWrite(8, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(2, HIGH);
      break;

    case 6:
      digitalWrite(8, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(2, HIGH);
      break;

    case 7:
      digitalWrite(8, LOW);
      digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(2, HIGH);
      break;

    case 8:
      digitalWrite(8, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(2, HIGH);
      break;

    case 9:
      digitalWrite(8, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(2, HIGH);
      break;
  }
}
