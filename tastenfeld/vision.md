# Verarbeitung

## Verarbeitung in unser Projekt

{% hint style="success" %}
Die Verbindung über Drähte war sehr einfach. Jedoch war das größte Problem das Programm, da das Tastenfeld über einen 2. Arduino lief, welcher über serielle Kommunikation den eingegeben Code auf den Arduino Uno R3 übertragen musste.
{% endhint %}

### Code - Beispiel:

Zusehen ist die Einbindung des Tastenfeld Moduls. Dafür gab es folgende Voraussetzungen:

* [ ] Einbindung der KeyPad- Library
* [ ] Einbindung der Software Serial Library
* [ ] Zeilen und Spalten definieren
* [ ] Initialisierung auf den eingesteckten Steckplätzen \[s. Zeile 14 + 15]
* [ ] KeyMap auf PINs, Reihen und Spalten einstellen
* [ ] globale Variable für die Übertragung erstellen
* [ ] Serielle Übertragung starten
* [ ] Tastenfeldabfrage starten und per serieller Kommunikation an den Arduino Uno R3 senden

{% @github-files/github-code-block url="https://github.com/lucas-developments/Arduino_RFID/blob/main/tastenfeld.ino" %}
