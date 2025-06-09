#include <Adafruit_CircuitPlayground.h>



// global var 
int score = 0;
unsigned long delayTime = 1000; 
bool hardMode = false;
int targetLED;
bool showRed; // this for red and false for blue



void setup() {
  CircuitPlayground.begin();
  pinMode(7, INPUT_PULLUP); // switch

  // switch
  if (digitalRead(7) == LOW) {

    // right switch = hard mode
    hardMode = true;
    delayTime = 200; // 1.5x speed maybe 2x 
  }

  flashStart();
}




// scoring
void loop() {
  while (score < 5) {
    playRound();

    if (checkButton()) {
      correctFeedback();
      score++;
      delayTime *= 0.7; // speed up
    } else {
      gameOver();
      return;
    }

    delay(1000);
  }


  youWin();
}


// start
void flashStart() {
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 150, 150, 0); // yellow
  }
  delay(500);
  CircuitPlayground.clearPixels();
}


// main loop
void playRound() {
  targetLED = random(0, 10);
  showRed = random(0, 2); 
  // randomly pick red or blue

  CircuitPlayground.clearPixels();
  if (showRed) {
    CircuitPlayground.setPixelColor(targetLED, 255, 0, 0); // red
    CircuitPlayground.playTone(220, 200);
  } else {
    CircuitPlayground.setPixelColor(targetLED, 0, 0, 255); // blue
    CircuitPlayground.playTone(440, 200);
  }
  delay(delayTime);
  CircuitPlayground.clearPixels();
}


// buttons
bool checkButton() {
  unsigned long start = millis();
  while (millis() - start < delayTime) {
    if (CircuitPlayground.leftButton()) {
      return showRed; // correct for red was shown
    }
    if (CircuitPlayground.rightButton()) {
      return !showRed; // correct for blue was shown
    }
  }
  return false;
}



// good feed back
void correctFeedback() {
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 0, 255, 0); // green
  }
  delay(300);
  CircuitPlayground.clearPixels();
}



// game over = red all + sound
void gameOver() {
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 255, 0, 0); // red
  }
  CircuitPlayground.playTone(220, 500);
  delay(1000);
  CircuitPlayground.clearPixels();
}



// win = green all + good sound
void youWin() {
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 0, 255, 0); // green
  }
  CircuitPlayground.playTone(880, 500);
  delay(1500);
  CircuitPlayground.clearPixels();
}
