#include <LedControl.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

const byte RS = 9;
const byte enable = 8;
const byte buzzerPin = 3;
const byte lcdControlPin = 5;


const byte d4 = 7;
const byte d5 = 6;
const byte d6 = 13;
const byte d7 = 4;

LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

const byte dinPin = 12;
const byte clockPin = 11;
const byte loadPin = 10;

const byte xPin = A0;
const byte yPin = A1;
const byte swPin = 2;

const byte minRow = 0;
const byte maxRow = 8;
const byte minCol = 0;
const byte maxCol = 8;

const unsigned long blinkDuration = 300;
const unsigned long resetTime = 3000;
unsigned long lastBlinkTime = 0;
unsigned long score = 0;
unsigned long highscore = 0;
unsigned long maximumScore = 3;
unsigned long last = 0;
unsigned long lastFinishGameTime = 0;
byte setting = 0;
byte audioOn;

byte inMenu = 1;

const short int buzzerTone = 1000;
const short int buzzerTimeMenu = 500;
const short int blinkStartTime = 500;
const short int buzzerDuration = 200;
unsigned long buzzerStart = 0;
unsigned long blinkStart = 0;
unsigned short int lcdValueMapped;
unsigned short int matrixValue;
unsigned short int chrPos;

unsigned short int speed;
unsigned short int damage;


LedControl lc = LedControl(dinPin, clockPin, loadPin, 1);

byte matrixBrightness = 2;

byte xPos = 0;
byte yPos = 7;

byte xLastPos = 0;
byte yLastPos = 0;

byte newFoodPosX = -1;
byte newFoodPosY = -1;
byte needFood = true;

const int minThreshold = 200;
const int maxThreshold = 600;

const byte moveInterval = 100;
unsigned long long lastMoved = 0;

unsigned long startGameTime = 0;
unsigned long finishGameTime = 0;
unsigned long time = 0;
unsigned long currentGameTime = 0;

const byte matrixSize = 8;
bool matrixChanged = true;
bool goToAction = false;
uint16_t characterCursor = 0;
int chrOption = 65;
int diffOption = 1;



byte matrixByte[matrixSize] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

byte highscoreIcon[matrixSize] = {
  B01111110,
  B01111110,
  B01111110,
  B00111100,
  B00011000,
  B00011000,
  B00111100,
  B00111100,
};

byte playIcon[matrixSize] = {
  B00100000,
  B00110000,
  B00111000,
  B00111100,
  B00111000,
  B00110000,
  B00100000,
  B00000000
};

byte aboutIcon[matrixSize] = {
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
};

byte settingsIcon[matrixSize] = {
  B00011000,
  B11011011,
  B11111111,
  B01100110,
  B01100110,
  B11111111,
  B11011011,
  B00011000
};

byte howIcon[matrixSize] = {
  B00111100,
  B01100110,
  B01100110,
  B00001100,
  B00011000,
  B00011000,
  B00000000,
  B00011000
};



unsigned long long greetDuration = 3000;
bool cleared = 0;

const byte upArrow = 0;
const byte downArrow = 1;
const short int leftArrow = 3;
const short int rightArrow = 4;
const short int heart = 5;



const short int cat = 2;


int xValue = 0;
int yValue = 0;
bool joyMoved = false;
bool joyMovedName = false;


unsigned long lastJoyDebounceTime = 0;
const unsigned long debounceJoyDelay = 100;
bool lastJoyMoved = false;
bool transitioned = false;
bool shouldTransition = false;

short int direction = 0;
const short int up = -1;
const short int down = 1;

short int directionName = 0;
const short int right = 2;
const short int left = 3;

const unsigned long debounceDelay = 100;
bool buttonPressed = false;
bool shortPress = false;

int buttonState;
int lastButtonState = HIGH;

unsigned long lastDebounceTime = 0;
unsigned long start = 0;
byte readingPress = LOW;
unsigned long pressedDebounceTime = 0;
unsigned long releasedDebounceTime = 0;

const char* instructions = "Use the joystick to move. Eat the blinking dot. Press the joystick to go back.";
const char* about1 = "GAME NAME: A Dabloon Story";
const char* about2 = "AUTHOR: Madalina-Elena Kopacz";
const char* about3 = "GITHUB: https://github.com/MadalinaKopacz/";


unsigned short int menuOption = 1;
unsigned short int aboutOption = 1;
unsigned short int soundOption = 1;
unsigned short int highScoreOption = 1;
unsigned short int settingsOption = 1;


bool shouldDisplayFinish1 = false;

bool gameCanRun = true;

const byte customDownArrow[] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};

const byte customUpArrow[] = {
  B00000,
  B00000,
  B00100,
  B01110,
  B11111,
  B00000,
  B00000,
  B00000
};

const byte customRightArrow[] = {
  B00000,
  B00100,
  B00110,
  B00111,
  B00110,
  B00100,
  B00000,
  B00000
};

const byte customHeart[] = {
  B00000,
  B01010,
  B10101,
  B10001,
  B10001,
  B01010,
  B00100,
  B00000
};

const byte customLeftArrow[] = {
  B00000,
  B00100,
  B01100,
  B11100,
  B01100,
  B00100,
  B00000,
  B00000
};

const byte customCat[] = {
  B11011,
  B10001,
  B00000,
  B01010,
  B00000,
  B10101,
  B01110,
  B00000
};

const unsigned short int hsAddress[] = { 0, 32, 64, 96, 128 };
const unsigned short int buzzerAddress = 160;
const unsigned short int lcdValueAddress = 192;
const unsigned short int matrixValueAddress = 224;
const unsigned short int speedAddress = 256;
const unsigned short int damageAddress = 288;


struct playerHighScore {
  char name[6] = "N/A";
  unsigned short int score = 0;
};

char currentName[6] = "AAAAA";
unsigned long startDisplay1Time = millis();
unsigned short int difficulty = 1;

void setup() {
  Serial.begin(9600);

  lc.shutdown(0, false);
  lc.setIntensity(0, matrixBrightness);
  lc.clearDisplay(0);

  randomSeed(analogRead(0));

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  lcd.createChar(upArrow, customUpArrow);
  lcd.home();
  lcd.createChar(leftArrow, customLeftArrow);
  lcd.home();
  lcd.createChar(rightArrow, customRightArrow);
  lcd.home();
  lcd.createChar(heart, customHeart);
  lcd.home();
  lcd.createChar(downArrow, customDownArrow);
  lcd.home();
  lcd.createChar(cat, customCat);
  lcd.home();

  pinMode(swPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(lcdControlPin, OUTPUT);

  EEPROM.get(buzzerAddress, audioOn);
  EEPROM.get(lcdValueAddress, lcdValueMapped);
  EEPROM.get(matrixValueAddress, matrixValue);
  lc.setIntensity(0, matrixValue);  
  EEPROM.get(speedAddress, speed);
  EEPROM.get(damageAddress, damage);
}

void loop() {
  analogWrite(lcdControlPin, lcdValueMapped);
  greet();
}

void updateByteMatrix(const byte matrix[]) {
  for (int row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, matrix[row]);
  }
}

void updatePositions() {
  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);

  xLastPos = xPos;
  yLastPos = yPos;
  if (xValue < minThreshold) {
    if (xPos < matrixSize - 1) {
      xPos++;
    } else {
      xPos = 0;
    }
  }
  if (xValue > maxThreshold) {
    if (xPos > 0) {
      xPos--;
    } else {
      xPos = matrixSize - 1;
    }
  }

  if (yValue > maxThreshold) {
    if (yPos > 0) {
      yPos--;
    } else {
      yPos = matrixSize - 1;
    }
  }

  if (yValue < minThreshold) {

    if (yPos < matrixSize - 1) {
      yPos++;
    } else {
      yPos = 0;
    }
  }
  if (xPos != xLastPos || yPos != yLastPos) {
    matrixChanged = true;
    matrixByte[xLastPos] &= (0 << yLastPos);
    matrixByte[xPos] |= (1 << yPos);
  }
}

void blink() {
  if (millis() - lastBlinkTime > blinkDuration) {
    lastBlinkTime = millis();
    matrixByte[newFoodPosX] ^= (1 << newFoodPosY);
    lc.setRow(0, newFoodPosX, matrixByte[newFoodPosX]);
  }
}

void collision() {
  if (newFoodPosX == xPos && newFoodPosY == yPos) {
    score++;
    needFood = true;
    matrixChanged = true;
  }

  matrixByte[xPos] |= (1 << yPos);
  lc.setRow(0, newFoodPosX, matrixByte[newFoodPosX]);
}

void generateFood() {
  newFoodPosX = random(minRow, maxRow);
  newFoodPosY = random(minCol, maxCol);

  if (newFoodPosX == xPos && newFoodPosY == yPos) {
    generateFood();
  }

  matrixByte[newFoodPosX] |= (1 << newFoodPosY);
  matrixChanged = true;

  needFood = false;
}

void displayPartialMessage(char* text) {
  uint8_t ind = 0;
  while (ind < 16) {
    if (!text[ind]) {
      break;
    }
    lcd.print((char)text[ind]);
    ind++;
  }
  while (ind < 16) {
    lcd.print(" ");
    ind++;
  }
}

void displayWholeMessage(char* text) {
  if (millis() > last + 500) {
    last = millis();

    if (text[characterCursor]) {
      displayPartialMessage(text + characterCursor);
      characterCursor++;
    } else if (strlen(text) >= characterCursor) {
      displayPartialMessage("");
      characterCursor = 0;
    }
  }
}

void greet() {
  if (millis() <= greetDuration) {
    lcd.setCursor(0, 0);
    lcd.print("HELLO, TRAVELER!");
  } else {
    if (!cleared) {
      lcd.clear();
      cleared = 1;
    }
    if (!goToAction) {
      scrollMenu(1, 5, menuOption);
      menu();
      pressButtonInMenu(true);
    } else {
      actionAfterPress();
      pressButtonInMenu(false);
    }
  }
}

void pressButtonInMenu(const bool givenGoToAction) {
  buttonPress();
  if (buttonPressed) {
    lcd.clear();
    goToAction = givenGoToAction;
    buttonPressed = false;
    if (!givenGoToAction) {
      inMenu = 1;
    } else {
      inMenu = 0;
    }
    if (!givenGoToAction && menuOption == 1) {
      scoreCloseGame();
      closeGame();
    }
    if (givenGoToAction && menuOption == 1) {
      score = 0;
      gameCanRun = true;
      startGameTime = millis();
    }
    if (givenGoToAction && (menuOption == 2 || menuOption == 3 || menuOption == 4 || menuOption == 5)) {
      setting = 0;
      characterCursor = 0;
    }
    if (!givenGoToAction && menuOption == 3) {
      highScoreOption = 1;
    }
    if (!givenGoToAction && menuOption == 5) {
      aboutOption = 1;
    }
    if (!givenGoToAction && menuOption == 2) {
      settingsOption = 1;
    }
  }
}

void restartMatrix() {
  for (int row = 0; row < matrixSize; row++) {
    matrixByte[row] = B00000000;
  }
}

void closeGame() {
  restartMatrix();
  updateByteMatrix(matrixByte);
  xPos = 0;
  yPos = 7;
  needFood = 1;
}

void scoreCloseGame() {
  playerHighScore smallestHighScore;
  EEPROM.get(hsAddress[4], smallestHighScore);
  if (score > smallestHighScore.score) {
    updateHighScores();
  }
}

void menu() {
  switch (menuOption) {
    case 1:
      {
        updateByteMatrix(playIcon);
        lcd.setCursor(0, 0);
        lcd.print("A Dabloon Story");
        lcd.setCursor(15, 0);
        lcd.write(cat);
        lcd.setCursor(0, 1);
        lcd.print("> Start Game");

        lcd.setCursor(15, 1);
        lcd.write(downArrow);
        break;
      }
    case 2:
      {
        updateByteMatrix(settingsIcon);
        lcd.setCursor(0, 0);
        lcd.print("> Settings");
        lcd.setCursor(2, 1);
        lcd.print("Highscore");

        lcd.setCursor(15, 0);
        lcd.write(upArrow);
        lcd.setCursor(15, 1);
        lcd.write(downArrow);
        break;
      }
    case 3:
      {

        updateByteMatrix(highscoreIcon);
        lcd.setCursor(0, 0);
        lcd.print("> Highscore");
        lcd.setCursor(2, 1);
        lcd.print("How to play");

        lcd.setCursor(15, 0);
        lcd.write(upArrow);
        lcd.setCursor(15, 1);
        lcd.write(downArrow);
        break;
      }
    case 4:
      {

        updateByteMatrix(howIcon);
        lcd.setCursor(0, 0);
        lcd.print("> How to play");
        lcd.setCursor(2, 1);
        lcd.print("About");

        lcd.setCursor(15, 0);
        lcd.write(upArrow);
        lcd.setCursor(15, 1);
        lcd.write(downArrow);
        break;
      }
    case 5:
      {

        updateByteMatrix(aboutIcon);
        lcd.setCursor(2, 0);
        lcd.print("How to play");
        lcd.setCursor(0, 1);
        lcd.print("> About");

        lcd.setCursor(15, 0);
        lcd.write(upArrow);
        break;
      }
  }
}

void game() {
  if (gameCanRun) {

    updateByteMatrix(matrixByte);
    if (needFood) {
      generateFood();
    }
    if (millis() - lastMoved > moveInterval) {
      updatePositions();
      lastMoved = millis();
    }
    if (matrixChanged == true) {
      updateByteMatrix(matrixByte);
      matrixChanged = false;
    }
    blink();
    collision();
    if (score >= maximumScore) {
      shouldDisplayFinish1 = true;
      gameCanRun = false;
      closeGame();
    }
    currentGameTime = millis();
    displayPlayingGame();
  } else {
    displayFinishScreens();
  }
}

void displayFinishScreen1() {
  if (!cleared) {
    lcd.clear();
    cleared = 1;
  }
  char buffer[7];
  itoa(score, buffer, 10);
  char message[50] = "Congratulations on reaching score ";
  strcat(message, buffer);
  displayWholeMessage(message);

  lcd.setCursor(0, 1);

  if (millis() >= currentGameTime + 13000) {
    lastFinishGameTime = millis();
    shouldDisplayFinish1 = false;
    cleared = false;
    characterCursor = 0;
  }
}

void displayFinishScreen2() {
  if (!cleared) {
    lcd.clear();
    cleared = 1;
  }
  char buffer[7] = "";
  itoa(score, buffer, 10);
  char message1[10] = "Score:";
  strcat(message1, buffer);

  playerHighScore smallestHighScore;
  EEPROM.get(hsAddress[4], smallestHighScore);
  if (score > smallestHighScore.score) {
    strcat(message1, " NEW HIGHSCORE!");
    displayWholeMessage(message1);
  } else {
    lcd.setCursor(0, 0);
    lcd.print(message1);
  }

  time = (currentGameTime - startGameTime) / 1000;

  itoa(time, buffer, 10);
  char message2[15] = "Time:";
  strcat(message2, buffer);

  lcd.setCursor(0, 1);
  lcd.print(message2);
}

void displayPlayingGame() {
  if (!cleared) {
    lcd.clear();
    cleared = 1;
  }

  char message0[15] = "Hi, ";
  strcat(message0, currentName);
  lcd.setCursor(0, 0);
  lcd.print(message0);

  lcd.setCursor(15, 0);
  lcd.write(heart);
  lcd.setCursor(14, 0);
  lcd.print("3");



  char buffer[7] = "";
  itoa(score, buffer, 10);
  char message1[15] = "D:";
  strcat(message1, buffer);
  lcd.setCursor(0, 1);
  lcd.print(message1);


  time = (currentGameTime - startGameTime) / 1000;
  itoa(time, buffer, 10);
  char message2[20] = "T:";
  strcat(message2, buffer);
  lcd.setCursor(8, 1);
  lcd.print(message2);
}

void displayFinishScreens() {
  if (shouldDisplayFinish1) {
    displayFinishScreen1();

  } else {
    displayFinishScreen2();
  }
}


void scrollMenu(const unsigned short int minBoundary, const unsigned short int maxBoundary, unsigned short int& option) {
  xValue = analogRead(xPin);
  yValue = analogRead(yPin);
  joyMoved = 0;
  direction = 0;
  chrOption = currentName[chrPos];
  if (menuOption == 2 && setting && (settingsOption == 1 || settingsOption == 2)) {
    if (xValue < minThreshold) {
      joyMoved = true;
      direction = down;
    }
    if (xValue > maxThreshold) {
      joyMoved = true;
      direction = up;
    }
  } else if (menuOption != 2 || (menuOption == 2 && !setting)) {
    if (xValue < minThreshold) {
      if (option < maxBoundary) {
        joyMoved = true;
        direction = down;
      }
    }
    if (xValue > maxThreshold) {
      if (option > minBoundary) {
        joyMoved = true;
        direction = up;
      }
    }
  }
  int settingsDirection = 0;

  if (menuOption == 2 && !inMenu) {
    if (yValue < minThreshold) {
      joyMoved = true;
      settingsDirection = down;
    }
    if (yValue > maxThreshold) {
      joyMoved = true;
      settingsDirection = up;
    }
  }


  if (joyMoved != lastJoyMoved) {
    lastJoyDebounceTime = millis();
  }
  if ((millis() - lastJoyDebounceTime) > debounceJoyDelay) {
    shouldTransition = joyMoved;
  }
  lastJoyMoved = joyMoved;

  if (!settingsDirection && shouldTransition && !transitioned && menuOption == 2 && setting && settingsOption == 1) {
    if (direction == down) {
      Serial.println("down");

      if (chrOption == 65) {
        chrOption = 90;
      } else {
        chrOption--;
      }
    } else {
      Serial.println("up");

      if (chrOption == 90) {
        chrOption = 65;
      } else {
        chrOption++;
      }
    }
    Serial.println(chrOption);
    currentName[chrPos] = chrOption;

  } else if (!settingsDirection && shouldTransition && !transitioned && menuOption == 2 && setting && settingsOption == 2) {
    if (direction == down) {

      if (diffOption == 1) {
        diffOption = 2;
      } 
    } else {

      if (diffOption == 2) {
        diffOption = 1;
      }
    }
    Serial.println(chrOption);
    currentName[chrPos] = chrOption;

  } else if (!settingsDirection && shouldTransition && !transitioned) {
    option += direction;
    lcd.clear();
    characterCursor = 0;
  } else if (shouldTransition && !transitioned) {
    if (setting && settingsOption == 5 && settingsDirection == up) {
      audioOn = !audioOn;
      EEPROM.put(buzzerAddress, audioOn);

    } else if (setting && settingsOption == 6 && settingsDirection == up) {
      initializeHighScoreEeprom();

    }

    else if (setting && settingsOption == 3 && settingsDirection == up) {
      lcdValueMapped += 10;
      lcdValueMapped = lcdValueMapped % 256;
      lcdValueMapped = lcdValueMapped / 10 * 10;
      EEPROM.put(lcdValueAddress, lcdValueMapped);
      lcd.setCursor(11, 0);
      lcd.print("     ");

    } else if (setting && settingsOption == 2 && settingsDirection == up && diffOption == 1) {
      speed += 1;
      speed = (speed % 3);
      EEPROM.put(speedAddress, speed);

    } else if (setting && settingsOption == 2 && settingsDirection == up && diffOption == 2) {
      damage += 1;
      damage = (damage % 3);
      EEPROM.put(speedAddress, damage);

    } else if (setting && settingsOption == 4 && settingsDirection == up) {

      matrixValue += 1;
      matrixValue = matrixValue % 16;
      lc.setIntensity(0, matrixValue);
      EEPROM.put(matrixValueAddress, matrixValue);
      lcd.setCursor(11, 0);
      lcd.print("     ");

    } else if (setting && settingsOption == 1 && settingsDirection == up) {

      chrPos += 1;
      chrPos = chrPos % 5;
      lcd.setCursor(chrPos, 1);
      lcd.print(char(chrOption));
    } else if (setting && settingsOption == 1 && settingsDirection == down) {
      chrPos = 0;
      characterCursor = 0;
      setting = 0;
      cleared = 0;
    } else if (!setting && settingsDirection == up) {
      setting = 1;
      cleared = 0;
      characterCursor = 0;

    } else if (setting && settingsDirection == down) {
      characterCursor = 0;
      setting = 0;
      cleared = 0;
    }
  }
  transitioned = shouldTransition;
}

void buttonPress() {
  readingPress = digitalRead(swPin);
  if (readingPress != lastButtonState) {
    lastDebounceTime = millis();
  }
  if (millis() - lastDebounceTime > debounceDelay) {
    if (readingPress != buttonState) {
      buttonState = readingPress;

      if (buttonState == LOW && !shouldDisplayFinish1 && !setting) {
        buttonPressed = true;
        activateBuzzer();
      }
    }
  }
  lastButtonState = readingPress;
}

void actionAfterPress() {
  switch (menuOption) {
    case 1:
      {
        lcd.setCursor(0, 0);
        game();
        break;
      }
    case 2:
      {
        if (!setting) {
          lcd.setCursor(0, 0);
          lcd.print("Settings");
        }
        scrollMenu(1, 6, settingsOption);
        settings(settingsOption);
        break;
      }
    case 3:
      {
        lcd.setCursor(0, 0);
        lcd.print("HighScores");
        scrollMenu(1, 5, highScoreOption);
        showHighScores();
        break;
      }
    case 4:
      {
        lcd.setCursor(0, 0);
        lcd.print("How to play?");
        lcd.setCursor(0, 1);
        displayWholeMessage(instructions);
        break;
      }
    case 5:
      {
        lcd.setCursor(0, 0);
        lcd.print("About");
        scrollMenu(1, 3, aboutOption);
        aboutOptions(aboutOption);
        break;
      }
  }
}

void settings(short int settingsOption) {
  if (!setting) {
    switch (settingsOption) {
      case 1:
        {
          lcd.setCursor(14, 0);
          lcd.write(downArrow);
          lcd.setCursor(15, 0);
          lcd.write(rightArrow);
          lcd.setCursor(0, 1);
          if (!strcmp(currentName, "AAAAA")) {
            displayWholeMessage("Choose username (max. 5 characters)");
          } else {
            char usernameText[60] = "Hello, ";
            strcat(usernameText, currentName);
            strcat(usernameText, "! Do you want to change your username?");
            displayWholeMessage(usernameText);
          }
          break;
        }
      case 2:
        {
          lcd.setCursor(13, 0);
          lcd.write(upArrow);
          lcd.setCursor(14, 0);
          lcd.write(downArrow);
          lcd.setCursor(15, 0);
          lcd.write(rightArrow);
          lcd.setCursor(0, 1);
          displayWholeMessage("Choose game difficulty");
          break;
        }
      case 3:
        {
          lcd.setCursor(13, 0);
          lcd.write(upArrow);
          lcd.setCursor(14, 0);
          lcd.write(downArrow);
          lcd.setCursor(15, 0);
          lcd.write(rightArrow);
          lcd.setCursor(0, 1);
          displayWholeMessage("LCD brightness control");
          break;
        }
      case 4:
        {
          lcd.setCursor(13, 0);
          lcd.write(upArrow);
          lcd.setCursor(14, 0);
          lcd.write(downArrow);
          lcd.setCursor(15, 0);
          lcd.write(rightArrow);
          lcd.setCursor(0, 1);
          displayWholeMessage("Matrix brightness control");
          break;
        }
      case 5:
        {
          lcd.setCursor(13, 0);
          lcd.write(upArrow);
          lcd.setCursor(14, 0);
          lcd.write(downArrow);
          lcd.setCursor(15, 0);
          lcd.write(rightArrow);
          lcd.setCursor(0, 1);
          displayWholeMessage("Sound settings");
          break;
        }
      case 6:
        {
          lcd.setCursor(14, 0);
          lcd.write(upArrow);
          lcd.setCursor(15, 0);
          lcd.write(rightArrow);
          lcd.setCursor(0, 1);
          displayWholeMessage("Reset highscores");
          break;
        }
    }
  } else {

    switch (settingsOption) {
      case 1:
        {
          if (!cleared) {
            lcd.clear();
            cleared = 1;
          }
          lcd.setCursor(15, 0);
          lcd.write(rightArrow);
          lcd.setCursor(14, 0);
          lcd.write(leftArrow);
          lcd.setCursor(0, 0);

          enterName();
          break;
        }
      case 2:
        {
          if (!cleared) {
            lcd.clear();
            cleared = 1;
          }
          lcd.setCursor(15, 0);
          lcd.write(rightArrow);
          lcd.setCursor(13, 0);
          lcd.write(leftArrow);
          lcd.setCursor(0, 0);
          lcd.print("Speed: ");
          lcd.setCursor(9, 0);
          lcd.print(speed+1);
          lcd.setCursor(0, 1);
          lcd.print("Damage: ");
          lcd.setCursor(9, 1);
          lcd.print(damage+1);
          lcd.setCursor(14, 0);

          if(diffOption == 1) {
          lcd.write(downArrow);
          }
          else {
            lcd.write(upArrow);
          }

          break;
        }
      case 3:
        {

          if (!cleared) {
            lcd.clear();
            cleared = 1;
          }
          lcd.setCursor(15, 0);
          lcd.write(rightArrow);
          lcd.setCursor(14, 0);
          lcd.write(leftArrow);
          lcd.setCursor(0, 0);
          lcd.print("Brightness:");
          lcd.setCursor(11, 0);
          lcd.print(lcdValueMapped);
          lcd.setCursor(0, 1);
          displayWholeMessage("Scroll right  to change");
          break;
        }
      case 4:
        {
          if (!cleared) {
            lcd.clear();
            cleared = 1;
          }
          lcd.setCursor(15, 0);
          lcd.write(rightArrow);
          lcd.setCursor(14, 0);
          lcd.write(leftArrow);
          lcd.setCursor(0, 0);
          lcd.print("Brightness:");
          lcd.setCursor(11, 0);
          lcd.print(matrixValue);
          lcd.setCursor(0, 1);
          displayWholeMessage("Scroll right  to change");
          break;
        }
      case 5:
        {
          if (!cleared) {
            lcd.clear();
            cleared = 1;
          }
          lcd.setCursor(15, 0);
          lcd.write(rightArrow);
          lcd.setCursor(14, 0);
          lcd.write(leftArrow);
          lcd.setCursor(0, 0);
          lcd.print("Sound: ");
          lcd.setCursor(8, 0);
          if (audioOn) {
            lcd.print("ON ");
          } else {
            lcd.print("OFF");
          }
          lcd.setCursor(0, 1);
          displayWholeMessage("Scroll right  to change");
          break;
        }
      case 6:
        {
          if (!cleared) {
            lcd.clear();
            cleared = 1;
          }
          lcd.setCursor(0, 0);
          lcd.print("Reset Hscore");
          lcd.setCursor(15, 0);
          lcd.write(rightArrow);
          lcd.setCursor(14, 0);
          lcd.write(leftArrow);
          lcd.setCursor(0, 1);
          displayWholeMessage("Scroll right  to change");
          break;
        }
    }
  }
}

void aboutOptions(short int aboutOption) {
  switch (aboutOption) {
    case 1:
      {
        lcd.setCursor(15, 0);
        lcd.write(downArrow);
        lcd.setCursor(0, 1);
        displayWholeMessage(about1);
        break;
      }
    case 2:
      {
        lcd.setCursor(14, 0);
        lcd.write(upArrow);
        lcd.setCursor(15, 0);
        lcd.write(downArrow);
        lcd.setCursor(0, 1);
        displayWholeMessage(about2);
        break;
      }
    case 3:
      {
        lcd.setCursor(15, 0);
        lcd.write(upArrow);
        lcd.setCursor(0, 1);
        displayWholeMessage(about3);
        break;
      }
  }
}


void enterName() {
  lcd.setCursor(0, 0);
  lcd.print("Enter name");
  lcd.setCursor(0, 1);
  lcd.print(currentName);
}


void initializeHighScoreEeprom() {
  playerHighScore highScores[5];
  for (int i = 0; i < 5; i++) {
    EEPROM.put(hsAddress[i], highScores[i]);
  }
}

void updateHighScores() {
  playerHighScore highScores[5];
  Serial.println("Update");
  for (int i = 0; i < 5; i++) {
    EEPROM.get(hsAddress[i], highScores[i]);
  }
  short int position;
  playerHighScore currentHighScore;
  strcpy(currentHighScore.name, currentName);
  currentHighScore.score = score;

  for (int i = 0; i < 5; i++) {
    if (score > highScores[i].score) {
      position = i;
      break;
    }
  }
  for (int i = 4; i > position; i--) {
    EEPROM.put(hsAddress[i], highScores[i - 1]);
  }
  EEPROM.put(hsAddress[position], currentHighScore);
}

void showHighScores() {
  playerHighScore highScores[5];
  for (int i = 0; i < 5; i++) {
    EEPROM.get(hsAddress[i], highScores[i]);
  }
  switch (highScoreOption) {
    case 1:
      {
        lcd.setCursor(15, 0);
        lcd.write(downArrow);
        lcd.setCursor(0, 1);
        lcd.print("1.");
        lcd.setCursor(3, 1);
        lcd.print(highScores[highScoreOption - 1].score);
        lcd.setCursor(10, 1);
        lcd.print(highScores[highScoreOption - 1].name);
        break;
      }
    case 2:
      {
        lcd.setCursor(14, 0);
        lcd.write(upArrow);
        lcd.setCursor(15, 0);
        lcd.write(downArrow);
        lcd.setCursor(0, 1);
        lcd.print("2.");
        lcd.setCursor(3, 1);
        lcd.print(highScores[highScoreOption - 1].score);
        lcd.setCursor(10, 1);
        lcd.print(highScores[highScoreOption - 1].name);
        break;
      }
    case 3:
      {
        lcd.setCursor(14, 0);
        lcd.write(upArrow);
        lcd.setCursor(15, 0);
        lcd.write(downArrow);
        lcd.setCursor(0, 1);
        lcd.print("3.");
        lcd.setCursor(3, 1);
        lcd.print(highScores[highScoreOption - 1].score);
        lcd.setCursor(10, 1);
        lcd.print(highScores[highScoreOption - 1].name);
        break;
      }
    case 4:
      {
        lcd.setCursor(14, 0);
        lcd.write(upArrow);
        lcd.setCursor(15, 0);
        lcd.write(downArrow);
        lcd.setCursor(0, 1);
        lcd.print("4.");
        lcd.setCursor(3, 1);
        lcd.print(highScores[highScoreOption - 1].score);
        lcd.setCursor(10, 1);
        lcd.print(highScores[highScoreOption - 1].name);
        break;
      }
    case 5:
      {
        lcd.setCursor(15, 0);
        lcd.write(upArrow);
        lcd.setCursor(0, 1);
        lcd.print("5.");
        lcd.setCursor(3, 1);
        lcd.print(highScores[highScoreOption - 1].score);
        lcd.setCursor(10, 1);
        lcd.print(highScores[highScoreOption - 1].name);
        break;
      }
  }
}

void activateBuzzer() {
  if (audioOn) {
    if (millis() - buzzerStart >= buzzerTimeMenu) {
      tone(buzzerPin, buzzerTone, buzzerDuration);
      buzzerStart = millis();
    }
  }
}