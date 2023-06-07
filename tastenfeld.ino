#include <Keypad.h>
#include <SoftwareSerial.h>

const byte ROWS = 4; // Vier Reihen
const byte COLS = 4; // Vier Zeilen

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; // Pins für Reihen
byte colPins[COLS] = {5, 4, 3, 2}; // Pins für Zeilen

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
SoftwareSerial mySerial(0,1);

 // Variables
String KeyPadInputs;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  KeyPadInputs = "";
}

void loop() {
    char customKey;
    customKey = customKeypad.getKey();
    while (customKey != '#') {
      customKey = customKeypad.getKey();

     if (customKey != NULL) {
      KeyPadInputs = KeyPadInputs+customKey;
     
      Serial.println(customKey);
     }
  }
   KeyPadInputs.replace("#", "");
   KeyPadInputs.toLowerCase();
   Serial.println(KeyPadInputs);
   Serial1.print(KeyPadInputs);
   KeyPadInputs = "";
}
