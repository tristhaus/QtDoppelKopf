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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    }
}
