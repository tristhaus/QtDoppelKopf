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
#include "playerselection_ui.h"

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
    const QString FileFilter = "Spiele (*.qdk)";
    const QString ResetButtonLabelNone = "Zurücksetzen";
    const QString ResetButtonLabelPlayersSet  = "Spielerwahl zurücksetzen";
    const QString ResetButtonLabelDeal = "Spiel zurücksetzen";
    const QString ResetButtonLabelMandatorySoloTrigger = "Pflichtsolo zurücksetzen";
    const unsigned int MaxPlayers;
    std::vector<QColor> htmlColors;
    Ui::MainWindow *ui;
    std::unique_ptr<Ui::PlayerSelection> playerSelection;
    std::unique_ptr<QMessageBox> aboutMessageBox;
    Backend::GameInfo gameInfo;
    unsigned int dealerIndex;

    /*!
     * \brief presetFilename allows to set a filename and
     *        thus circumvent the file dialog, e.g. for testing.
     */
    QString presetFilename;

public:
    MainWindow(unsigned int maxPlayers,
               std::shared_ptr<Backend::Repository> repository = std::make_shared<Backend::DiskRepository>(),
               bool showPlayerSelection = true,
               QWidget *parent = nullptr);
    ~MainWindow();

private:
    void UpdateDisplay();
    void ShowPlayerSelection();
    std::vector<std::pair<QString, bool>> GetDefaultPlayers();
    std::map<QString, std::pair<std::vector<int>,std::vector<int>>> GetHistoricData();
    void RedrawPlayerHistory();
    void ShowAboutDialog();
    void DetermineAndSetMultiplierLabels();
    QString GetFolderForFileDialog();

private slots:
    void OnChangePlayerPressed();
    void OnLoadGamePressed();
    void OnSaveGamePressed();
    void OnMandatorySoloPressed();
    void OnCommitPressed();
    void OnResetPressed();
    void OnHistoryPlayerSelected();
    void OnAboutPressed();

private:
    /*!
     * \brief The Resetter class executes the contained action on destruction.
     *        The usual application is to reset something.
     */
    class Resetter
    {
    private:
        std::function<void()> action;

    public:
        /*!
         * \brief Initializes a new instance holding the supplied action.
         * \param action The action to store and execute on destruction.
         */
        Resetter(std::function<void()> action) : action(action)
        {
        }
        ~Resetter()
        {
            this->action();
        }
        Resetter(const Resetter&) = delete;
        Resetter(Resetter&&) = delete;
        Resetter& operator=(const Resetter&) = delete;
        Resetter& operator=(Resetter&&) = delete;
    };
};
#endif // MAINWINDOW_H
