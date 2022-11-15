#define LED_NUM 4
#define BlueLed   6
#define GreenLed  9
#define YellowLed 10
#define RedLed    11

int Leds[LED_NUM] = { BlueLed ,GreenLed ,YellowLed ,RedLed };
unsigned long LastChangeTime[LED_NUM];

int LedRate[LED_NUM] = { 0,0,0,0 };

int rNum;
int score;
bool wasOn;
//
unsigned long startMillis;  
unsigned long currentMillis;
const unsigned long period = 5000;  
unsigned long startGameInMs;
unsigned long time_now;

// Joystick variables
int LR = A3;     
int UD = A1;     
int LeftRight;          
int UpDown;        
int xState;
int yState;

#define WAIT_4_START  1
#define START_GAME    4
#define GAME_ON       2
#define GAME_FINISHED 3
int currState;

int startJoy = 0;    
int endJoy = 0;   
int holdTime = 0;       
int idleTime = 0;    
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A5));
  wasOn = false;
  for (int k = 0; k < LED_NUM; k++) {
    pinMode(Leds[k], OUTPUT);
    LastChangeTime[k] = millis();
    LedRate[k] = ChooseRandomValueInSmartRange();
}
  pinMode(LR, INPUT);
  pinMode(UD, INPUT);
  score = 0;
  currState = WAIT_4_START;
}

void loop() {
switch(currState){
    case WAIT_4_START:
    score = 0;
    Serial.println("Wait 4 Start");
    AllLedsOn();
      if (RightULeftD()) {
        currState = START_GAME;
      }
      break;
    case START_GAME:
      AllLedsOff();
      GameStartIn();
      startGameInMs = millis();
      currState = GAME_ON;
      break;
    case GAME_ON:
      mainGameManager();
      if (millis()- startGameInMs > 20000) {
        currState = GAME_FINISHED;
      }
      break;
    case GAME_FINISHED:
      AllLedsOn();
      delay(5000);
      currState = WAIT_4_START;;
      break;
  }
} // close loop
void mainGameManager() {
  LeftRight = analogRead(LR);
  UpDown = analogRead(UD);
  currentMillis = millis();  

if (currentMillis - startMillis >= ChooseRandomValueInSmartRange()) {
    rNum=random(4);
    if(wasOn){
    score = max(0, score -1);
    wasOn = false;
    }
//BLUE
if (rNum == 0){
     digitalWrite(Leds[0], HIGH);
     digitalWrite(Leds[1], LOW);
     digitalWrite(Leds[2], LOW);
     digitalWrite(Leds[3], LOW);
     wasOn = true;
}
//GREEN
if (rNum == 1){
     digitalWrite(Leds[0], LOW);
     digitalWrite(Leds[1], HIGH);
     digitalWrite(Leds[2], LOW);
     digitalWrite(Leds[3], LOW);
     wasOn = true;
}
//Yellow
if (rNum == 2){
     digitalWrite(Leds[0], LOW);
     digitalWrite(Leds[1], LOW);
     digitalWrite(Leds[2], HIGH);
     digitalWrite(Leds[3], LOW);
     wasOn = true;
}
//RED
if (rNum == 3){
     digitalWrite(Leds[0], LOW);
     digitalWrite(Leds[1], LOW);
     digitalWrite(Leds[2], LOW);
     digitalWrite(Leds[3], HIGH);
     wasOn = true;
}
    startMillis = currentMillis;
    
  }// close if

 if (LeftRight > 768) {
    xState=2; //RIGHT
  } else if (LeftRight < 384) {
    xState=1; //LEFT
  }
  if (UpDown > 768) {
    yState=3; //DOWN
  } else if (UpDown < 384) {
    yState=4; //UP
  }
  if (LeftRight < 768 && LeftRight > 384){
    xState = 0;
  }
   if (UpDown < 768 && UpDown > 384){
    yState = 0;
  }

Serial.print("Your Score is : ");
Serial.println(score);

//blue
if ((yState == 4 )&& (digitalRead(Leds[0]) == HIGH)) {

      if (Leds[0],HIGH) {
        digitalWrite(Leds[0],LOW);
        score++;
        time_now = millis();
        wasOn = false;
      }
}
//red
if ((xState == 2 )&& (digitalRead(Leds[3]) == HIGH)) {
      if (Leds[3],HIGH) {
        digitalWrite(Leds[3],LOW);
        score++;
        time_now = millis();
        wasOn = false;
      }
}
//yellow
if ((yState == 3 )&& (digitalRead(Leds[2]) == HIGH)) {
      if (Leds[2],HIGH) {
        digitalWrite(Leds[2],LOW);
        score++;
        time_now = millis();
        wasOn = false;
      } 
}
//green
if ((xState == 1 )&& (digitalRead(Leds[1]) == HIGH)) {
      if (Leds[1],HIGH) {
        digitalWrite(Leds[1],LOW);
        score++;
        time_now = millis();
        wasOn = false;
      }
  }
  if ((yState == 3 )&& (digitalRead(Leds[2]) == LOW) && millis() - time_now >= 250) {
    if(millis() >= time_now + 500){
        time_now += 1000;
        score = max(0, score -1);
        wasOn = false;
    }       
 }
   if ((yState == 4 )&& (digitalRead(Leds[0]) == LOW) && millis() - time_now >= 250) {
    if(millis() >= time_now + 500){
        time_now += 1000;
        score = max(0, score -1);
        wasOn = false;
    }       
 }
   if ((xState == 2 )&& (digitalRead(Leds[3]) == LOW) && millis() - time_now >= 250) {
    if(millis() >= time_now + 500){
        time_now += 1000;
        score = max(0, score -1);
        wasOn = false;
    }       
 }
   if ((xState == 1 )&& (digitalRead(Leds[1]) == LOW) && millis() - time_now >= 250) {
    if(millis() >= time_now + 500){
        time_now += 1000;
        score = max(0, score -1);
        wasOn = false;
    }       
 }
}
void GameStartIn(){
  for (int i = 5; i > 0; i--){
    Serial.print("Game Start In ");
    Serial.println(i);
    delay(1000);
  }
}
void AllLedsOff() {
  for (int k = 0; k < LED_NUM; k++) {
    digitalWrite(Leds[k],LOW);
  }
}
void AllLedsOn() {
  for (int k = 0; k < LED_NUM; k++) {
    digitalWrite(Leds[k],HIGH);
  }
}
int ChooseRandomValueInSmartRange() {
  int minRangeVal = max(500, 2000 - 500 * score);
  int maxRangeVal = max(1000, 4000 - 500 * score);
  int val = random(minRangeVal, maxRangeVal);

  return val;
}
bool RightULeftD() {
  int cnt = 0;
  Serial.println("To Start Right Side Up Then Left Side Down :)");
  while (cnt != 2){
  int LeftRight = analogRead(LR);
  int UpDown = analogRead(UD);
  if (LeftRight > 768 && UpDown < 384 && cnt != 1) {
           startJoy = millis();
      idleTime = startJoy - endJoy;
      if (idleTime >= 1000) {
          cnt = 1;
          Serial.println("Phase 1 Completed");
      }
    }
  else if(UpDown < 768 && UpDown > 384 && LeftRight < 768 && LeftRight > 384){
      endJoy = millis();
}
 
   if (LeftRight < 384 && UpDown > 768 && cnt == 1){
        startJoy = millis();
      idleTime = startJoy - endJoy;
      if (idleTime >= 1000) {
         cnt = 2;
          Serial.println("Phase 2 Completed");
      }

  } else if(UpDown < 768 && UpDown > 384 && LeftRight < 768 && LeftRight > 384) {
      endJoy = millis();
    }
  }
  if (cnt >= 2) {
    return true;
  } else {
    return false;
  }
}
