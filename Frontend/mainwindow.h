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
#include <QMessageBox>
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
    const QString StandardNamesStylesheet = "QLabel { }";
    const QString DealerNamesStylesheet = "QLabel { border: 3px solid orange ; border-radius : 6px }";
    const unsigned int MaxPlayers;
    std::vector<QColor> htmlColors;
    Ui::MainWindow *ui;
    std::unique_ptr<QMessageBox> aboutMessageBox;
    Backend::GameInfo gameInfo = Backend::GameInfo(this->MaxPlayers);
    unsigned int dealerIndex;
public:
    MainWindow(unsigned int maxPlayers, bool showPlayerSelection = true, QWidget *parent = nullptr);
    ~MainWindow();

private:
    void DisableNotImplementedButtons();
    void UpdateDisplay();
    void ShowPlayerSelection(bool calledOnStartup);
    std::vector<std::pair<QString, bool>> GetDefaultPlayers();
    void ShowNotImplementedMessageBox();
    std::map<QString, std::pair<std::vector<int>,std::vector<int>>> GetHistoricData();
    void RedrawPlayerHistory();
    void ShowAboutDialog();
    void DetermineAndSetMultiplierLabels();

private slots:
    void OnChangePlayerPressed();
    void OnLoadGamePressed();
    void OnSaveGamePressed();
    void OnMandatorySoloPressed();
    void OnCommitPressed();
    void OnResetPressed();
    void OnHistoryPlayerSelected();
    void OnAboutPressed();
};
#endif // MAINWINDOW_H
