# QtDoppelKopf

Copyright tristhaus 2021 und später.

![main](/../screenshot/screenshot.png?raw=true)

Ein Programm zum Nachhalten des Spielstandes beim Doppelkopf nach den Hausregeln von Freunden.

## Für Nutzer

Die Entwicklung ist weitgehend abgeschlossen. Ich bin für Vorschläge bzgl. neuer Features offen.

Nach Auswahl der Spieler:innen muss nur noch das Minimum an Daten pro Spiel eingegeben werden, die fehlenden Punkte werden ergänzt, wenn möglich, tw. schon in der UI.
Bockrunden werden bis zu Dreifachbock unterstützt und es ist möglich die jeweils letzte Aktion (Änderung Spieler, Eintrag Spiel, Start Pflichtsolorunde) zurückzunehmen und geändert wieder zu übernehmen.

## Für Entwickler

Siehe [README.md](README.md).

## Lizenz

Alle Quelldateien lizensiert unter der GPL v3, siehe LICENSE für die Bedingungen, siehe auch [deutschsprachige Hinweise der FSF](https://www.gnu.org/licenses/quick-guide-gplv3).

## Anerkennungen

Graphische Nutzeroberfläche gebaut mit [Qt](https://doc.qt.io/).

Icon (Farbsymbole und Buchstaben) von tristhaus.

[QCustomPlot](https://www.qcustomplot.com/) Bibliothek (Version 2.1.0) von Emanuel Eichhammer genutzt unter der [GPL v3](https://www.gnu.org/licenses/gpl-3.0.html).

JSON De/Serialisierung via [rapidjson](https://rapidjson.org/) bereitgestellt von THL A29 Limited, eine Tencent Firma, und Milo Yip benutzt unter der [MIT Lizenz](http://opensource.org/licenses/MIT).

GoogleTest genutzt unter folgenden Bedingungen:

```
Copyright 2008, Google Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

    * Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
copyright notice, this list of conditions and the following disclaimer
in the documentation and/or other materials provided with the
distribution.
    * Neither the name of Google Inc. nor the names of its
contributors may be used to endorse or promote products derived from
this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
```
