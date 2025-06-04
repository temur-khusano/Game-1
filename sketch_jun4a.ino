#include <Adafruit_CircuitPlayground.h>

int score = 0;
unsigned long delayTime = 1000; // normal speed
bool hardMode = false;
int targetLED;

void setup() {
  CircuitPlayground.begin();
  pinMode(7, INPUT_PULLUP); // Switch pin

  // Check switch
  if (digitalRead(7) == LOW) {
    // Right switch = hard mode
    hardMode = true;
    delayTime = 667; // 1.5x speed (shorter delay)
  }

  flashStart();
}

void loop() {
  while (score < 5) {
    playRound();

    if (checkButton()) {
      correctFeedback();
      score++;
      delayTime *= 0.9; // Speed up
    } else {
      gameOver();
      return;
    }

    delay(1000);
  }

  youWin();
}

void flashStart() {
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 150, 150, 0); // yellow
  }
  delay(500);
  CircuitPlayground.clearPixels();
}

void playRound() {
  targetLED = random(0, 10);
  CircuitPlayground.clearPixels();
  CircuitPlayground.setPixelColor(targetLED, 0, 0, 255); // blue
  CircuitPlayground.playTone(440, 200);
  delay(delayTime);
  CircuitPlayground.clearPixels();
}

bool checkButton() {
  // Wait for user input
  unsigned long start = millis();
  while (millis() - start < delayTime) {
    if (CircuitPlayground.leftButton() || CircuitPlayground.rightButton()) {
      // Simulate user guessing correctly 50% of the time
      return random(0, 2) == 1;
    }
  }
  return false; // Timeout
}

void correctFeedback() {
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 0, 255, 0); // green
  }
  delay(300);
  CircuitPlayground.clearPixels();
}

void gameOver() {
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 255, 0, 0); // red
  }
  CircuitPlayground.playTone(220, 500);
  delay(1000);
  CircuitPlayground.clearPixels();
}

void youWin() {
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 0, 255, 0); // green
  }
  CircuitPlayground.playTone(880, 500);
  delay(1500);
  CircuitPlayground.clearPixels();
}
