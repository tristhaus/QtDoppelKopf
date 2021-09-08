/*
 * This file is part of QtDoppelKopf.
 *
 * QtDoppelKopf is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QtDoppelKopf is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QtDoppelKopf.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Backend/gameinfo.h"
#include "../Backend/playerinfo.h"

class FrontendTest;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend FrontendTest;

private:
    Ui::MainWindow *ui;
    Backend::GameInfo gameInfo;
    unsigned int dealerIndex;
public:
    MainWindow(bool showPlayerSelection = true, QWidget *parent = nullptr);
    ~MainWindow();

private:
    void UpdateDisplay();
    void ShowPlayerSelection(bool calledOnStartup);
    std::vector<std::pair<QString, bool>> GetDefaultPlayers();
    void ShowNotImplementedMessageBox();

private slots:
    void OnChangePlayerPressed();
    void OnLoadGamePressed();
    void OnSaveGamePressed();
    void OnMandatorySoloPressed();
    void OnCommitPressed();
    void OnResetPressed();
};
#endif // MAINWINDOW_H
