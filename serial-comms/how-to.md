---
description: 'Serielle Kommunikation: How - to & Generelles'
cover: >-
  https://images.unsplash.com/photo-1631378297854-185cff6b0986?crop=entropy&cs=srgb&fm=jpg&ixid=M3wxOTcwMjR8MHwxfHNlYXJjaHw1fHxicmVhZGJvYXJkfGVufDB8fHx8MTY4NjY3NTc2Nnww&ixlib=rb-4.0.3&q=85
coverY: 0
---

# 📲 Serielle Kommunikation

Die serielle Kommunikation zwischen dem Arduino Leonardo und dem Arduino Uno R3 kann über die UART-Schnittstellen der beiden Boards erfolgen. Hier ist eine Erläuterung des Kommunikationsprozesses:

1. Hardwareverbindung:&#x20;
   1. Um die beiden Arduinos miteinander zu verbinden, müssen die **TX** (Transmit) und **RX** (Receive)-Pins der beiden Boards verbunden werden. Das **TX-Pin** des einen Boards **muss mit dem RX-Pin des anderen Boards verbunden werden** und umgekehrt. Es ist auch wichtig, die **Masse (GND) der beiden Boards zu verbinden**, um eine gemeinsame Bezugsebene für die Kommunikation zu haben.
2. Baudrate festlegen:&#x20;
   1. Bevor die Kommunikation beginnen kann, müssen beide Arduinos auf die **gleiche Baudrate** eingestellt sein. Die Baudrate legt die Geschwindigkeit der Datenübertragung fest. Sie muss auf beiden Boards identisch sein, damit die Kommunikation ordnungsgemäß funktioniert.
3. Serielle Schnittstelle initialisieren:&#x20;
   1.  In der Arduino-Programmierung wird die serielle Kommunikation über die "Serial" Library verwaltet. **Auf beiden Arduinos müssen Sie die serielle Schnittstelle mit der entsprechenden Baudrate initialisieren**. Zum Beispiel:\


       **Arduino Leonardo:**\


       ```cpp
       void setup() {
         Serial.begin(9600); // Initialisiert die serielle Kommunikation mit 9600 Baud
       }
       ```

       \
       **Arduino Uno R3:**\


       ```cpp
       void setup() {
         Serial.begin(9600); // Initialisiert die serielle Kommunikation mit 9600 Baud
       }
       ```
4.  Daten senden und empfangen: Nach der Initialisierung können Daten zwischen den Arduinos senden und empfangen werden. Der **Arduino Leonardo** kann Daten über die Funktion **`Serial.write()`** senden, während der **Arduino Uno R3** Daten mit der Funktion **`Serial.read()`** empfangen kann. Hier ist ein Beispiel:\


    **Arduino Leonardo:**\


    ```cpp
    void loop() {
      Serial.write("Hello from Leonardo"); // Sendet den Text "Hello from Leonardo"
      delay(1000); // Wartet 1 Sekunde
    }
    ```


5.  **Arduino Uno R3:**\


    ```cpp
    void loop() {
      if (Serial.available()) {
        char receivedData = Serial.read(); // Liest empfangene Daten ein
        Serial.print("Received data: ");
        Serial.println(receivedData); // Gibt die empfangenen Daten aus
      }
    }
    ```


6. In diesem Beispiel sendet der Arduino Leonardo alle 1 Sekunde den Text "Hello from Leonardo". Der **Arduino Uno R3** **wartet auf empfangene Daten** und gibt sie über die serielle Schnittstelle aus.
