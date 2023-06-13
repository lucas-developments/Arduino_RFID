---
description: 'RFID: Ziel'
---

# Ziel

## Unser Ziel

{% hint style="success" %}
**Unser Ziel:**\
\
Funktionsfreigabe durch das Auslesen eines RFID Chips. Dieses hat später sogar geklappt!
{% endhint %}

Das Programm, welches in [vision.md](vision.md "mention")gezeigt wird, liest den RFID-Chip aus, indem es kontinuierlich überprüft, ob eine neue Karte erkannt wird. Wenn eine Karte erkannt wird, wird der eindeutige Code des Chips gelesen und als "uid" gespeichert. Anschließend wird die Funktion `write_RFID()` aufgerufen, um den RFID-Code weiterzuverarbeiten.

Falls innerhalb des definierten Zeitlimits von 15 Sekunden kein RFID-Chip erkannt wird, wird die Meldung "Timeout abgelaufen, RFID-Modul freigegeben" auf der seriellen Konsole ausgegeben. Dies bedeutet, dass das RFID-Modul ohne gültigen Chip erkannt wurde und somit die Freigabe erteilt wird.

Dank der erfolgreichen Implementierung dieses Codes können RFID-Chips nun zur Funktionsfreigabe verwendet werden.\
\
Die Funktion `write_RFID()` wird aufgerufen, wenn ein neuer RFID-Chip erkannt und erfolgreich ausgelesen wurde. Sie dient dazu, den erkannten RFID-Code auf einem LCD-Display anzuzeigen und ihn über die serielle Schnittstelle auszugeben. Anschließend wird eine Verzögerung von 5 Sekunden eingefügt, bevor die Funktion `Tastenfeld()` aufgerufen wird.
