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

#include "mainwindow.h"
#include "mainwindow_ui.h"
#include "playerselection_ui.h"

#include <QMessageBox>

MainWindow::MainWindow(bool showPlayerSelection, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this->ui->changePlayersButton, &QAbstractButton::pressed, this, &MainWindow::OnChangePlayerPressed);
    connect(this->ui->loadButton, &QAbstractButton::pressed, this, &MainWindow::OnLoadGamePressed);
    connect(this->ui->saveButton, &QAbstractButton::pressed, this, &MainWindow::OnSaveGamePressed);
    connect(this->ui->mandatorySoloButton, &QAbstractButton::pressed, this, &MainWindow::OnMandatorySoloPressed);
    connect(this->ui->commitButton, &QAbstractButton::pressed, this, &MainWindow::OnCommitPressed);
    connect(this->ui->resetButton, &QAbstractButton::pressed, this, &MainWindow::OnResetPressed);

    if(showPlayerSelection)
    {
        this->ShowPlayerSelection(true);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateDisplay()
{
    auto playerInfos = this->gameInfo.PlayerInfos();

    // set visibility
    for(unsigned int index = 0; index < ui->maxNumberOfPlayers; ++index)
    {
        bool visible = false;

        if(index < playerInfos.size())
        {
            auto playerInfo = playerInfos[index];
            visible = playerInfo->IsPresent() || playerInfo->HasPlayed();
        }

        ui->names[index]->setVisible(visible);
        ui->lastGames[index]->setVisible(visible);
        ui->actuals[index]->setVisible(visible);
        ui->scores[index]->setVisible(visible);
        ui->cashs[index]->setVisible(visible);

        ui->statisticNames[index]->setVisible(visible);
        ui->numberWons[index]->setVisible(visible);
        ui->numberLosts[index]->setVisible(visible);
        ui->numberPlayeds[index]->setVisible(visible);
        ui->numberSoloWons[index]->setVisible(visible);
        ui->numberSoloLosts[index]->setVisible(visible);
        ui->pointsSolos[index]->setVisible(visible);
        ui->maxSingleWins[index]->setVisible(visible);
        ui->maxSingleLosss[index]->setVisible(visible);
        ui->unmultipliedScores[index]->setVisible(visible);
    }

    // set data
    for(unsigned int index = 0; index < playerInfos.size(); ++index)
    {
        auto playerInfo = playerInfos[index];

        QString name = QString::fromStdWString(playerInfo->Name());
        ui->names[index]->setText(name);
        ui->statisticNames[index]->setText(name);

        ui->scores[index]->setText(QString().setNum(playerInfo->CurrentScore()));
        ui->actuals[index]->setEnabled(playerInfo->IsPlaying());
        ui->actuals[index]->clear();
    }
}

void MainWindow::ShowPlayerSelection(bool calledOnStartup)
{
    std::vector<std::pair<QString, bool>> currentPlayers;
    QString currentDealer;
    std::set<unsigned int> currentSitOutScheme;

    if(gameInfo.PlayerInfos().size() > 0)
    {
        const std::vector<std::shared_ptr<Backend::PlayerInfo>> playerInfos = gameInfo.PlayerInfos();

        for(auto playerInfosIt = playerInfos.begin(); playerInfosIt != playerInfos.end(); ++playerInfosIt)
        {
            currentPlayers.emplace_back(std::pair<QString, bool>(QString::fromStdWString((*playerInfosIt)->Name()), (*playerInfosIt)->IsPresent()));
        }

        std::wstring dealerName = gameInfo.Dealer()->Name();
        auto dealerIt = std::find_if(playerInfos.cbegin(), playerInfos.cend(), [&](std::shared_ptr<Backend::PlayerInfo> left){ return left->Name().compare(dealerName) == 0; });
        this->dealerIndex = dealerIt - playerInfos.cbegin();

        currentSitOutScheme = gameInfo.SitOutScheme();
    }
    else
    {
        this->dealerIndex = 0;
        currentPlayers = GetDefaultPlayers();
    }

    currentDealer = currentPlayers[this->dealerIndex].first;

    Ui::PlayerSelection ps(ui->maxNumberOfPlayers, currentPlayers, currentDealer, currentSitOutScheme, this);
    ps.setModal(true);
    ps.show();
    int dialogCode = ps.exec();

    if(dialogCode == QDialog::Rejected)
    {
        if(calledOnStartup)
        {
            exit(EXIT_FAILURE);
        }

        return;
    }

    auto result = ps.GetResults();

    std::vector<std::wstring> players;

    std::transform(std::get<0>(result).begin(),
                   std::get<0>(result).end(),
                   std::back_inserter(players),
                   [](QString qs) { return qs.toStdWString(); });

    auto dealer = std::get<1>(result).toStdWString();

    auto sitOutScheme = std::get<2>(result);

    gameInfo.SetPlayers(players, dealer, sitOutScheme);

    this->UpdateDisplay();
}

std::vector<std::pair<QString, bool>> MainWindow::GetDefaultPlayers()
{
#define PASTE(x, y) x##y
#define MAKEWIDE(x) PASTE(L,x)
    return std::vector<std::pair<QString, bool>>
    {
#ifdef MY_PLAYER_A
        std::pair<QString, bool>(QString::fromStdWString(MAKEWIDE(MY_PLAYER_A)), true),
#else
        std::pair<QString, bool>(QString::fromStdWString(L"Spieler A"), true),
#endif
#ifdef MY_PLAYER_B
        std::pair<QString, bool>(QString::fromStdWString(MAKEWIDE(MY_PLAYER_B)), true),
#else
        std::pair<QString, bool>(QString::fromStdWString(L"Spieler B"), true),
#endif
#ifdef MY_PLAYER_C
        std::pair<QString, bool>(QString::fromStdWString(MAKEWIDE(MY_PLAYER_C)), true),
#else
        std::pair<QString, bool>(QString::fromStdWString(L"Spieler C"), true),
#endif
#ifdef MY_PLAYER_D
        std::pair<QString, bool>(QString::fromStdWString(MAKEWIDE(MY_PLAYER_D)), true),
#else
        std::pair<QString, bool>(QString::fromStdWString(L"Spieler D"), true),
#endif
#ifdef MY_PLAYER_E
        std::pair<QString, bool>(QString::fromStdWString(MAKEWIDE(MY_PLAYER_E)), true),
#else
        std::pair<QString, bool>(QString::fromStdWString(L"Spieler E"), true),
#endif
#ifdef MY_PLAYER_F
        std::pair<QString, bool>(QString::fromStdWString(MAKEWIDE(MY_PLAYER_F)), true),
#else
        std::pair<QString, bool>(QString::fromStdWString(L"Spieler F"), true),
#endif
#ifdef MY_PLAYER_G
        std::pair<QString, bool>(QString::fromStdWString(MAKEWIDE(MY_PLAYER_G)), true),
#else
        std::pair<QString, bool>(QString::fromStdWString(L"Spieler G"), true),
#endif
#ifdef MY_PLAYER_H
        std::pair<QString, bool>(QString::fromStdWString(MAKEWIDE(MY_PLAYER_H)), true),
#else
        std::pair<QString, bool>(QString::fromStdWString(L"Spieler H"), true),
#endif
    };
#undef PASTE
#undef MAKEWIDE
}

void MainWindow::ShowNotImplementedMessageBox()
{
    auto messageBoxTitle = QString("Nicht implementiert");
    auto messageBoxText = QString("Diese Funktion ist noch nicht implementiert.");
    auto errorBox = std::make_unique<QMessageBox>(
                    QMessageBox::Icon::Warning,
                    messageBoxTitle,
                    messageBoxText);

    errorBox->exec();
}

QString MainWindow::DetermineMultiplierText() const
{
    auto preview = this->gameInfo.MultiplierPreview();

    if(preview[2] > 0)
    {
        return QString("Dreifachbock (%1:%2:%3)").arg(preview[2]).arg(preview[1]).arg(preview[0]);
    }
    else if(preview[1] > 0)
    {
        return QString("Doppelbock (%1:%2)").arg(preview[1]).arg(preview[0]);
    }
    else if(preview[0] > 0)
    {
        return QString("Bock (%1)").arg(preview[0]);
    }
    else
    {
        return QString("Normalspiel");
    }
>>>>>>> 415e674 (i hate strings and the c preproc)
=======
>>>>>>> be4fbf6 (Add "not implemented" message boxes to all main window buttons)
}

void MainWindow::OnChangePlayerPressed()
{
    this->ShowPlayerSelection(false);
}

void MainWindow::OnLoadGamePressed()
{
    this->ShowNotImplementedMessageBox();
}

void MainWindow::OnSaveGamePressed()
{
    this->ShowNotImplementedMessageBox();
}

void MainWindow::OnMandatorySoloPressed()
{
    this->ShowNotImplementedMessageBox();
}

void MainWindow::OnCommitPressed()
{
    std::vector<std::pair<std::wstring, int>> changes;

    for (unsigned int index = 0; index < ui->maxNumberOfPlayers; ++index)
    {
        auto & actual = ui->actuals[index];

        if(actual->isEnabled() && !actual->text().isEmpty())
        {
            bool intConversionOK = true;
            int value = actual->text().toInt(&intConversionOK);
            if(!intConversionOK)
            {
                return;
            }

            std::wstring name = ui->names[index]->text().toStdWString();
            changes.emplace_back(std::make_pair(name, value));
        }
    }

    if(changes.size() == 0)
    {
        return;
    }

    this->gameInfo.PushDeal(changes);

    this->UpdateDisplay();
}

void MainWindow::OnResetPressed()
{
    this->ShowNotImplementedMessageBox();
}
