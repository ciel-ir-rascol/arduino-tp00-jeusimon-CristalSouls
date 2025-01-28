const int LEVEL_MAX = 100;

int pinLed[] = {12, 10, 8};
int pinBouton[] = {A0, A2, A4};

int Sequence[LEVEL_MAX] = {0};
int level = 0;

const char* couleurs[] = {"Vert", "Bleu", "Jaune"};

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 3; i++) {
    pinMode(pinLed[i], OUTPUT);
    pinMode(pinBouton[i], INPUT);
  }

  randomSeed(analogRead(A3));
}

void ledAllumer(int ledIndex) {
  digitalWrite(pinLed[ledIndex], HIGH);
  delay(300);
  digitalWrite(pinLed[ledIndex], LOW);
}

void tirageSequence() {
  for (int i = 0; i < level; i++) {
    int currentLed = Sequence[i];
    ledAllumer(currentLed);
    delay(50);
  }
}

int readButtons() {
  while (true) {
    for (int i = 0; i < 3; i++) {
      int buttonPin = pinBouton[i];
      if (digitalRead(buttonPin) == LOW) {
        return i;
      }
    }
    delay(10);
  }
}

void gameOver() {
  Serial.print("Game over! Ton score est de: ");
  Serial.println(level - 1);

  Serial.print("Séquence générée : ");
  for (int i = 0; i < level - 1; i++) {
    Serial.print(couleurs[Sequence[i]]);
    if (i < level - 2) {
      Serial.print(" -> ");
    }
  }
  Serial.println();

  level = 0;
  delay(200);
}

bool checkUserSequence() {
  for (int i = 0; i < level; i++) {
    int expectedButton = Sequence[i];
    int actualButton = readButtons();
    ledAllumer(actualButton);
    if (expectedButton != actualButton) {
      return false;
    }
  }

  return true;
}

void loop() {
  Sequence[level] = random(0, 3);
  level++;
  if (level >= LEVEL_MAX) {
    level = LEVEL_MAX - 1;
  }

  tirageSequence();

  if (!checkUserSequence()) {
    gameOver();
  }

  delay(300);

  if (level > 0) {
    delay(300);
  }
}
