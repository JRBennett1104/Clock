#include <Wire.h>
#include <RTClib.h>

const int DISCO = 0;
const int NUMBERS = 1;
const int COUNTDOWN = 2;

int pin = 0;
int digit = 10;
int value = 0;
int counter = 0;
int mode = true;
int countdown = 1234;

RTC_DS3231 rtc;

void setup() {
  for(int pin = 0; pin < 14; pin++) {
    pinMode(pin, OUTPUT);
  }

  initialiseRtc();
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

void initialiseRtc() {
  #ifndef ESP8266
    while (!Serial); // for Leonardo/Micro/Zero
  #endif  

  Serial.begin(9600);

  delay(3000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}
