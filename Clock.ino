const int DISCO = 0;
const int NUMBERS = 1;
const int COUNTDOWN = 2;

int pin = 0;
int digit = 10;
int value = 0;
int counter = 0;
int mode = true;
int countdown = 1234;

void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  switch(mode) {
    case DISCO: {
      discoLooping();
      break;
    }
    case NUMBERS: {
      numberLooping();
      break;
    }
    default: {
      countdownLooping();
      break;
    }
  }
}

void discoLooping() {
  for(int digit = 10; digit < 14; digit++) {
    digitalWrite(digit, HIGH);
    for(int value = 0; value < 10; value++) {
      digitalWrite(value, HIGH);
      delay(100);
      digitalWrite(value, LOW);
    }
    digitalWrite(digit, LOW);
  }
  mode = NUMBERS;
}

void numberLooping() {
  setDigitValue(digit, value);

  digit++;

  if (digit >= 14) {
    digit = 10;
    counter++;
    if(counter >= 15){
      value++;
      counter = 0;
    }
          
    if (value >= 10) {
      value = 0;
      mode = COUNTDOWN;
    }
  }
}

void countdownLooping() {

  int currentValue = countdown / 1000;
  setDigitValue(10, currentValue);

  currentValue = countdown % 1000;
  setDigitValue(11, currentValue / 100);

  currentValue = currentValue % 100;
  setDigitValue(12, currentValue / 10);

  currentValue = countdown % 10;
  setDigitValue(13, currentValue);

  countdown--;
  if (countdown <= 0) {
    countdown = 1234;
    mode = DISCO;
  }
}

void setDigitValue(int digit, int value) {
  digitalWrite(digit, HIGH);
  digitalWrite(value, HIGH);

  delay(2);

  digitalWrite(digit, LOW);
  digitalWrite(value, LOW);
}

