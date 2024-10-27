// Lab 7 - Interrupts
// This code is supposed to show my name and under it my favorite quote which will scroll through the LCD screen.
// Youtube link - https://youtu.be/oZjMqd3BUNg

#include <LiquidCrystal.h>

// time
long Time;

// initializing 2 buttons
int Button1 = 8;
int Button2 = 9;

// initializing variables to read buttons
int read1 = 0;
int read2 = 0;

//int ButtonValue = 0;

// initializing the LCD
int rs = 12;
int en = 11;
int d4 = 5;
int d5 = 4;
int d6 = 3;
int d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char * msg1 = "Interrupt received! Press button 2 to continue. ";
char * msg2 =  "We have been waiting for X seconds. ";

// line number to show string
int lineNum = 1;
int temp = 0;
int timeCounter = 0;

void setup() {
  // start the LCD screen
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(msg1);
  lcd.scrollDisplayLeft();
  delay(500);
  
  // inputs
  pinMode(Button1, INPUT_PULLUP);
  pinMode(Button2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(8), msg1Line, CHANGE);
  attachInterrupt(digitalPinToInterrupt(9), msg2Line, CHANGE);
  Serial.begin(9600);
}

void loop() {
  // checks for buttons pressed
  read1 = digitalRead(Button1);
  read2 = digitalRead(Button2);

//  Time = millis();

  lcd.setCursor(0,0);
//  msg1Line();
  
  if(read1 == LOW) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.autoscroll();
    lcd.print("Interrupt received! Press button 2 to continue");
  }
  
  if(read2 == LOW) {
    lcd.clear();
    Time = millis();
    timeCounter++;
//      attachInterrupt(2, timer, LOW);
    delay(1000);
  }
  
  if(timeCounter == 1) {
    lcd.setCursor(0,1);
    lcd.print((millis() - Time) / 1000);
  }

  if(timeCounter > 1) {
    timeCounter = 0;
    lcd.clear();
    lcd.print("start");
  }
}

void timer(){
  lcd.print("Interrupt received! Press button 2 to continue");
  lcd.scrollDisplayLeft();
  delay(400);
  attachInterrupt(3, loop, read2);
  read1 = digitalRead(Button1);
  
}

void msg1Line() {
  int len = strlen(msg1);
  if (temp == (len - 1)) {
    temp = 0;
  }
  lcd.setCursor(0, lineNum);
  if (temp < lineNum - 16) {
    for (int i = temp; i < temp + 16; i++) {
      lcd.print(msg1[i]);
    }
  }
  else {
    for (int i = temp; i < (len - 1); i++) {
      lcd.print(msg1[i]);
    }
    for (int i = 0; i <= 16 - (len - temp); i++) {
      lcd.print(msg1[i]);
    }
  }
  temp++;
}

void msg2Line() {
  int len = strlen(msg2);
  if (temp == (len - 1)) {
    temp = 0;
  }
  lcd.setCursor(0, lineNum);
  if (temp < lineNum - 16) {
    for (int i = temp; i < temp + 16; i++) {
      lcd.print(msg2[i]);
    }
  }
  else {
    for (int i = temp; i < (len - 1); i++) {
      lcd.print(msg2[i]);
    }
    for (int i = 0; i <= 16 - (len - temp); i++) {
      lcd.print(msg2[i]);
    }
  }
  temp++;
}
