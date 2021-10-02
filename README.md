# QtDoppelKopf

Copyright tristhaus 2021 and later.

![main](/../screenshot/screenshot.png?raw=true)

A program to note down the scores in a game of Doppelkopf following the house rules of a group of friends.

## For Users

Currently, this is an alpha-stage demo of what QtDoppelKopf shall become. A pre-release of the current status has been made available.

## For Developers

I am currently not looking for contributors since this is primarily a custom, private program.

In order to compile the [frontend tests](/MainWindowTest/), you need to define one of two preprocessor constants
 * `_SKIP_LONG_TEST` if you wish to skip the long-running tests
 * `_USE_LONG_TEST` if you wish to execute those tests

The simplest thing in Qt Creator is to add an additional argument to the qmake step like `"DEFINES+=_USE_LONG_TEST"`.

The project is not localized.

## License

All source code licensed under GPL v3 (see LICENSE for terms).

## Attributions

Graphical user interface built using [Qt](https://doc.qt.io/).

Icon (suit symbols and letters) by tristhaus.
