#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <Keypad.h>
#include <SoftwareSerial.h>

#define RST_PIN   9     // Configurable, see typical pin layout above
#define SS_PIN    10    // Configurable, see typical pin layout above

// Pins für Dioden

int redPin = 13;
int greenPin = 12;

SoftwareSerial mySerial(14,15);

// Pin für Summer

int SummerPin = 11;

// Versuche der Eingabe über das Pinfeld für die Sperrung

int currentTrys = 0;
int AllWrongs = 0;

// Sperrzeit in Millisekunden
int unsigned long lockTime = 3000;
int unsigned long LockEndTime = 0;

// LCD Initialisierung
LiquidCrystal lcd(3, 4, 5, 6, 7, 8);
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

MFRC522::MIFARE_Key key;

const byte ROWS = 4; // Vier Reihen
const byte COLS = 4; // Vier Zeilen

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {A0, A1, A2, A3}; // Pins für Reihen
byte colPins[COLS] = {A4, A5, A6, A7}; // Pins für Zeilen

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.begin(16, 2);

  // Rote Diode
  pinMode(redPin, OUTPUT);

  // Grüne Diode
  pinMode(greenPin, OUTPUT);

  // Summer konfigurieren
  pinMode(SummerPin, OUTPUT);
  lcd.clear();
  mySerial.begin(9600);
}

// Funktionsdeklarierungen
void correct();
void wrong();
void lockTimeMaths();
void write_RFID();
void readRFID();
String uid = "";

// Variable, ob ein RFID Code gelesen wird
bool isRFIDRead = false;

void readRFID() 
{
  unsigned long lastCardTime = millis(); // Variable, um die Zeit des letzten Kartenauftretens zu verfolgen
  const unsigned long CARD_TIMEOUT = 15000; // Timeout-Dauer in Millisekunden (15 Sekunden)
    
  while((millis() - lastCardTime) < CARD_TIMEOUT) {
    if (mfrc522.PICC_IsNewCardPresent()) {
      if (mfrc522.PICC_ReadCardSerial()) {
        uid = "";
        for (byte i = 0; i < mfrc522.uid.size; i++) {
          uid += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
          uid += String(mfrc522.uid.uidByte[i], HEX);
        }
        Serial.println("RFID Code: " + uid);
        write_RFID();
        break;
      }
    }
  }

  // halt the PICC (Proximity Integrated Circuit Card)
  mfrc522.PICC_HaltA();
  // stop communication with the PICC
  mfrc522.PCD_StopCrypto1();

  if (uid.length() == 0) {
    Serial.println("Timeout abgelaufen, RFID-Modul freigegeben");
  }
}


void write_RFID() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RFID Code:");
  lcd.setCursor(0, 1);
  lcd.print(uid);
  Serial.println("CHIP RFID CODE: " + uid);
  delay(5000);
  Tastenfeld();
}

void loop() {
  readRFID();
  // Tastenfeld();
  // if (currentTrys == 3) {
  //   wrong();
  // }
 
}

void Tastenfeld() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Code eingeben");
  if(mySerial.available())
   {
     char c = mySerial.read();
     Serial.print("RX: ");
     Serial.print(c);
     Serial.println(" ");
   }
}

void correct() {
  Serial.println("Der Code wurde besätigt, die grüne Diode wird eingeschaltet");
  digitalWrite(greenPin, HIGH);
  delay(10000);
  digitalWrite(greenPin, LOW);
  acceptFunctions();
}

void wrong() {
  Serial.println("Der Code war falsch, die rote Diode wird eingeschaltet");
  digitalWrite(redPin, HIGH);
  delay(10000);
  digitalWrite(redPin, LOW);
  AllWrongs = AllWrongs + 1;
  lockSystem();
}

void lockTimeMaths() {
  if (currentTrys == 3) {
    lockTime = 30000;
  }

  if (AllWrongs == 1) {
    if (currentTrys == 3) {
      lockTime = 60000;
    }
  }

  if (AllWrongs == 2) {
    if (currentTrys == 3) {
      lockTime = 90000;
    }
  }
  
  if (AllWrongs == 3) {
    lockTime = 150000;
  }
}

void lockSystem() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gesperrt für " + lockTime);
  currentTrys = 0;
  Serial.println("Aktuelle Versuche: " + AllWrongs);
}

void acceptFunctions() {
  Serial.println("Funktionsfreigabe, da die Pin bestätigt wurde");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("Freigegeben");
  digitalWrite(greenPin, HIGH);
  digitalWrite(SummerPin, HIGH);
  delay(25000);
  lcd.clear();
  digitalWrite(greenPin, LOW);
  digitalWrite(SummerPin, LOW);
  delay (10000);
}

void declineFunctions() {
  Serial.println("Der Code war Falsch. Versuch: " + currentTrys);

}
