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
int moveDuration = 300;
unsigned long lastMove = 0;


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

unsigned long lastJoyMove = 0;
unsigned long joyDebounce = 10;

byte inMenu = 1;

const short int buzzerTone = 1000;
const short int buzzerTimeMenu = 500;
const short int blinkStartTime = 500;
const short int buzzerDuration = 200;
unsigned long buzzerStart = 0;
unsigned long blinkStart = 0;
unsigned short int lcdValueMapped = 40;
unsigned short int matrixValue;
unsigned short int chrPos;

unsigned short int speed;
unsigned short int level;


unsigned long lastSpeedChange = 0;
int speedChangeDuration = 3000;

float maxSpeed = 200.0;

float speedFactor = 15.0;


LedControl lc = LedControl(dinPin, clockPin, loadPin, 1);

byte matrixBrightness = 2;

byte xPos = 0;
byte yPos = 0;

byte xLastPos = 0;
byte yLastPos = 0;

byte newFoodPosX = -1;
byte newFoodPosY = -1;
byte needFood = true;
byte foodBlinkStatus = 1;

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

bool isGameOver = false;
bool isWin = false;

int changedName = false;

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

const char* instructions = "Use the joystick to move. Eat the blinking dot. Do not hit yourself.";
const char* about1 = "GAME NAME: A Dabloon Story";
const char* about2 = "AUTHOR: Madalina-Elena Kopacz";
const char* about3 = "GITHUB: https://github.com/MadalinaKopacz/";
int maximumLength = 15;

unsigned short int menuOption = 1;
unsigned short int aboutOption = 1;
unsigned short int soundOption = 1;
unsigned short int highScoreOption = 1;
unsigned short int settingsOption = 1;
byte initialSnakeDirection = 3;
byte snakeDirection = initialSnakeDirection;
float snakeSpeed = 0.0;

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
const unsigned short int levelAddress = 288;

const int initialSnakeRow = 5;
const int initialSnakeCol = 7;
struct Snake {
  short int headRow = initialSnakeRow;
  short int headCol = initialSnakeCol;
};
Snake snake;
int matrix[matrixSize][matrixSize] = {};
struct playerHighScore {
  char name[6] = "N/A";
  unsigned short int score = 0;
};
int initialSnakeLength = 2;
short int lastSnakeDirection = right;

int gameState = 1;
int snakeLength;

char currentName[6] = "     ";
unsigned long startDisplay1Time = millis();
unsigned short int difficulty = 1;

void setup() {
  Serial.begin(9600);

  lc.shutdown(0, false);
  lc.setIntensity(0, matrixBrightness);
  lc.clearDisplay(0);

  randomSeed(analogRead(0));

  lcd.begin(16, 2);

  lcd.createChar(upArrow, customUpArrow);
  lcd.home();
  lcd.createChar(leftArrow, customLeftArrow);
  lcd.home();
  lcd.createChar(rightArrow, customRightArrow);
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
  EEPROM.get(levelAddress, level);

  snakeLength = initialSnakeLength;
  snakeDirection = initialSnakeDirection;
  lastSnakeDirection = snakeDirection;
  snakeSpeed = 0;

  resetMatrix();

  lc.shutdown(0, false);
  lc.clearDisplay(0);

  randomSeed(analogRead(0));

  matrix[snake.headRow][snake.headCol] = snakeLength;
}

void resetMatrix() {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      matrix[row][col] = 0;
    }
  }
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
  if (millis() - lastJoyMove <= joyDebounce) {
    return;
  }

  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);

  xLastPos = xPos;
  yLastPos = yPos;
  if (xValue < minThreshold) {
    snakeDirection = 2;
  }
  if (xValue > maxThreshold) {
    snakeDirection = 0;
  }

  if (yValue > maxThreshold) {
    snakeDirection = 1;
  }

  if (yValue < minThreshold) {
    snakeDirection = 3;
  }
}

void blink() {
  if (millis() - lastBlinkTime > blinkDuration) {
    lastBlinkTime = millis();
    foodBlinkStatus = !foodBlinkStatus;
    lc.setLed(0, newFoodPosX, newFoodPosY, foodBlinkStatus);
  }
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
      snakeLength = initialSnakeLength;
      gameCanRun = true;
      isWin = false;
      isGameOver = false;
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
    for (int col = 0; col < matrixSize; col++) {
      matrix[row][col] = 0;
    }
  }
}

void closeGame() {
  restartMatrix();
  xPos = 0;
  yPos = 0;
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
void setDifficulty() {
  if (speed == 1) {
    speedFactor = 12;
  }
  if (speed == 2) {
    speedFactor = 15;
  }
  if (speed == 3) {
    speedFactor = 17;
  }
  if (level == 1) {
    maximumLength = 9;
  }
  if (level == 2) {
    maximumLength = 12;
  }
  if (level == 3) {
    maximumLength = 15;
  }
}
void game() {
  setDifficulty();
  if (gameCanRun) {

    if (needFood) {
      generateFood();
    }
    updatePositions();
    changeSpeed();
    if (millis() - lastMoved > moveInterval - snakeSpeed) {
      lastMoved = millis();
      showSnake();
    }

    if (isGameOver || isWin) {
      shouldDisplayFinish1 = true;
      gameCanRun = false;
      endGameSounds();
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
  if (!changedName) {
    lcd.setCursor(0, 0);
    lcd.print("Hi!");
  } else {
    char message0[15] = "Hi, ";
    strcat(message0, currentName);
    lcd.setCursor(0, 0);
    lcd.print(message0);
  }


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
  if (chrOption == ' ') {
    chrOption = 65;
  }
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
      if (chrOption == 65) {
        chrOption = 90;
      } else {
        chrOption--;
      }
    } else {

      if (chrOption == 90) {
        chrOption = 65;
      } else {
        chrOption++;
      }
    }
    currentName[chrPos] = chrOption;
    changedName = true;

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
    currentName[chrPos] = chrOption;

  } else if (!settingsDirection && shouldTransition && !transitioned) {
    option += direction;
    if (inMenu) {
      activateBuzzer();
    }
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
      if (lcdValueMapped <= 40) {
        lcdValueMapped = 40;
      }

      EEPROM.put(lcdValueAddress, lcdValueMapped);
      lcd.setCursor(11, 0);
      lcd.print("     ");

    } else if (setting && settingsOption == 2 && settingsDirection == up && diffOption == 1) {
      speed += 1;
      speed = (speed % 3);
      EEPROM.put(speedAddress, speed);

    } else if (setting && settingsOption == 2 && settingsDirection == up && diffOption == 2) {
      level += 1;
      level = (level % 3);
      EEPROM.put(speedAddress, level);

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
          if (!changedName) {
            displayWholeMessage("Hello! Choose username (max. 5 characters)");
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
          lcd.print(speed + 1);
          lcd.setCursor(0, 1);
          lcd.print("Level: ");
          lcd.setCursor(9, 1);
          lcd.print(level + 1);
          lcd.setCursor(14, 0);

          if (diffOption == 1) {
            lcd.write(downArrow);
          } else {
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
          lcd.print(lcdValueMapped - 40);
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

void endGameSounds() {

  if (audioOn) {
    if (isGameOver) {
      if (audioOn) {
        sadSound();
      }
    }

    if (isWin) {
      if (audioOn) {

        happySound();
      }
    }
  }

  removeSnake();
  gameState = 0;
}


void sadSound() {
  tone(buzzerPin, 1000, 200);
  delay(200);
  tone(buzzerPin, 800, 200);
  delay(200);
  tone(buzzerPin, 600, 200);
}

void happySound() {
  tone(buzzerPin, 500, 200);
  delay(200);
  tone(buzzerPin, 500, 200);
  delay(200);
  tone(buzzerPin, 1000, 500);
}

void removeSnake() {
  lc.setLed(0, newFoodPosX, newFoodPosX, 0);

  for (int i = snakeLength; i >= 1; i--) {
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        if (matrix[row][col] == i) {
          lc.setLed(0, row, col, 0);
          delay(100);
        }
      }
    }
  }
}


void showSnake() {
  if (snakeDirection == lastSnakeDirection - 2 || snakeDirection == lastSnakeDirection + 2) {
    snakeDirection = lastSnakeDirection;
  }

  switch (snakeDirection) {
    case 0:  //up
      snake.headRow--;
      if (snake.headRow < 0) snake.headRow = 7;
      lc.setLed(0, snake.headRow, snake.headCol, HIGH);
      break;

    case 2:  //down
      snake.headRow++;
      if (snake.headRow > 7) snake.headRow = 0;
      lc.setLed(0, snake.headRow, snake.headCol, HIGH);
      break;

    case 1:  //right
      snake.headCol++;
      if (snake.headCol > 7) snake.headCol = 0;
      lc.setLed(0, snake.headRow, snake.headCol, HIGH);
      break;

    case 3:  //left
      snake.headCol--;
      if (snake.headCol < 0) snake.headCol = 7;
      lc.setLed(0, snake.headRow, snake.headCol, HIGH);
      break;
  }

  lastSnakeDirection = snakeDirection;

  if (matrix[snake.headRow][snake.headCol] > 1) {
    isGameOver = true;
    return;
  }

  if (snake.headRow == newFoodPosX && snake.headCol == newFoodPosY) {
    lc.setLed(0, newFoodPosX, newFoodPosY, HIGH);

    if (audioOn == true) {
      tone(buzzerPin, 1000, 250);
    }
    needFood = true;

    snakeLength++;

    for (int row = 0; row < matrixSize; row++) {
      for (int col = 0; col < matrixSize; col++) {
        if (matrix[row][col] > 0) {
          matrix[row][col]++;
        }
      }
    }
  }

  matrix[snake.headRow][snake.headCol] = snakeLength + 1;

  for (int row = 0; row < matrixSize; row++) {
    for (int col = 0; col < matrixSize; col++) {
      if (matrix[row][col] > 0) {
        matrix[row][col]--;
      }
      lc.setLed(0, row, col, matrix[row][col] == 0 ? 0 : 1);
    }
  }
  blink();

  score = snakeLength - initialSnakeLength;
}

void changeSpeed() {
  if (millis() - lastSpeedChange > speedChangeDuration) {
    lastSpeedChange = millis();

    if (snakeSpeed <= maxSpeed - speedFactor) {
      snakeSpeed += speedFactor;
    }
  }
}
void generateFood() {
  if (snakeLength == maximumLength) {
    isWin = true;
  }
  do {
    newFoodPosX = random(0, matrixSize);
    newFoodPosY = random(0, matrixSize);
  } while (matrix[newFoodPosX][newFoodPosY] > 0);

  needFood = false;
}