#
# This file is part of QtDoppelKopf.
#
# QtDoppelKopf is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# QtDoppelKopf is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with QtDoppelKopf.  If not, see <http://www.gnu.org/licenses/>.
#
#

QT += testlib core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += qt warn_on depend_includepath testcase c++20

TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../Frontend/Frontend.pri)

include(../Backend/Backend.pri)

SOURCES +=  tst_playerselection.cpp
