---
description: 'RFID: Verarbeitung'
---

# Verarbeitung

## Verarbeitung in unser Projekt

{% hint style="success" %}
Die Verbindung über Drähte war äußerst einfach. Jedoch war das Programm das größte Problem.
{% endhint %}

### Code - Beispiel:

Zusehen ist die Einbindung des RFID Moduls. Dafür gab es folgende Voraussetzungen:

* [ ] Einbindung der SPI - Library
* [ ] Einbindung der MFRC522 Library
* [ ] setzen des MIFARE Keys
* [ ] MFRC552 Instanz erstellen und initialisieren
* [ ] nach Prsäsenz der Karte und der UID Fragen mit Funktion readRFID ab Zeile80



{% @github-files/github-code-block url="https://github.com/lucas-developments/Arduino_RFID/blob/main/Projekt_Programm_RFID.ino" fullWidth="true" %}
