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

MainWindow::MainWindow(const unsigned int maxPlayers, std::shared_ptr<Backend::Repository> repository, bool showPlayerSelection, QWidget *parent)
    : QMainWindow(parent),
      MaxPlayers(maxPlayers),
      ui(new Ui::MainWindow(MaxPlayers)),
      gameInfo(Backend::GameInfo(repository, maxPlayers))
{
    assert(maxPlayers <= 8);
    this->htmlColors = std::vector<QColor>
    {
        QColor(0x7b, 0x1f, 0xa2),
        QColor(0x00, 0x00, 0x00),
        QColor(0xfb, 0x8c, 0x00),
        QColor(0x00, 0x89, 0x7b),
        QColor(0x39, 0x49, 0xab),
        QColor(0xe5, 0x39, 0x35),
        QColor(0x79, 0x55, 0x48),
        QColor(0x21, 0x96, 0xf3)
    };

    ui->setupUi(this);

    connect(this->ui->changePlayersButton, &QAbstractButton::pressed, this, &MainWindow::OnChangePlayerPressed);
    connect(this->ui->loadButton, &QAbstractButton::pressed, this, &MainWindow::OnLoadGamePressed);
    connect(this->ui->saveButton, &QAbstractButton::pressed, this, &MainWindow::OnSaveGamePressed);
    connect(this->ui->mandatorySoloButton, &QAbstractButton::pressed, this, &MainWindow::OnMandatorySoloPressed);
    connect(this->ui->commitButton, &QAbstractButton::pressed, this, &MainWindow::OnCommitPressed);
    connect(this->ui->resetButton, &QAbstractButton::pressed, this, &MainWindow::OnResetPressed);
    connect(this->ui->aboutButton, &QAbstractButton::pressed, this, &MainWindow::OnAboutPressed);

    for(unsigned int i = 0; i < MaxPlayers; ++i)
    {
        connect(this->ui->playerHistorySelectionCheckboxes[i], &QCheckBox::stateChanged, this, &MainWindow::OnHistoryPlayerSelected);
    }

    if(showPlayerSelection)
    {
        this->ShowPlayerSelection();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateDisplay()
{
    auto playerInfos = this->gameInfo.PlayerInfos();
    auto dealer = this->gameInfo.Dealer();

    // set visibility
    for(unsigned int index = 0; index < this->MaxPlayers; ++index)
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

        ui->playerHistorySelectionCheckboxes[index]->setVisible(visible);
        ui->playerHistorySelectionLabels[index]->setVisible(visible);
    }

    // set data
    for(unsigned int index = 0; index < playerInfos.size(); ++index)
    {
        auto playerInfo = playerInfos[index];

        QString name = QString::fromUtf8(playerInfo->Name());
        ui->names[index]->setText(name);
        if(dealer && playerInfo->Name().compare(dealer->Name()) == 0)
        {
            ui->names[index]->setStyleSheet(this->DealerNamesStylesheet);
        }
        else
        {
            ui->names[index]->setStyleSheet(this->StandardNamesStylesheet);
        }

        ui->statisticNames[index]->setText(name);

        ui->scores[index]->setText(QString().setNum(playerInfo->CurrentScore()));
        ui->actuals[index]->setEnabled(playerInfo->IsPlaying());
        ui->actuals[index]->clear();

        ui->lastGames[index]->setText(playerInfo->ParticipatedInLastDeal() ? QString(u8"%1").arg(playerInfo->ScoreInLastDeal()) : QString(u8""));

        ui->cashs[index]->setText(QString(u8"%1,%2").arg(playerInfo->CashCents()/100).arg(playerInfo->CashCents()%100, 2, 10, QLatin1Char('0')));

        ui->numberWons[index]->setText(QString().setNum(playerInfo->NumberGamesWon()));
        ui->numberLosts[index]->setText(QString().setNum(playerInfo->NumberGamesLost()));
        ui->numberPlayeds[index]->setText(QString().setNum(playerInfo->NumberGames()));
        ui->numberSoloWons[index]->setText(QString().setNum(playerInfo->SolosWon()));
        ui->numberSoloLosts[index]->setText(QString().setNum(playerInfo->SolosLost()));
        ui->pointsSolos[index]->setText(QString().setNum(playerInfo->TotalSoloPoints()));
        ui->maxSingleWins[index]->setText(QString().setNum(playerInfo->MaxSingleWin()));
        ui->maxSingleLosss[index]->setText(QString().setNum(playerInfo->MaxSingleLoss()));
        ui->unmultipliedScores[index]->setText(QString().setNum(playerInfo->UnmultipliedScore()));

        ui->playerHistorySelectionLabels[index]->setText(QString::asprintf(u8"<font color=\"#%02x%02x%02x\">■</font> %s",
                                                                           this->htmlColors[index].red(),
                                                                           this->htmlColors[index].green(),
                                                                           this->htmlColors[index].blue(),
                                                                           name.toStdString().c_str()));
    }

    ui->spinBox->setValue(0);

    ui->totalCash->setText(QString(u8"%1,%2 (inkl. %3,%4 pro Abwesender)")
                           .arg(gameInfo.TotalCashCents()/100)
                           .arg(gameInfo.TotalCashCents()%100, 2, 10, QLatin1Char('0'))
                           .arg(gameInfo.AbsentPlayerCashCents()/100)
                           .arg(gameInfo.AbsentPlayerCashCents()%100, 2, 10, QLatin1Char('0')));

    ui->resetButton->setEnabled(this->gameInfo.LastPoppableEntry() != Backend::GameInfo::PoppableEntry::None);
    switch(this->gameInfo.LastPoppableEntry())
    {
    case Backend::GameInfo::PoppableEntry::None:
    {
        ui->resetButton->setText(this->ResetButtonLabelNone);
        break;
    }

    case Backend::GameInfo::PoppableEntry::PlayersSet:
    {
        ui->resetButton->setText(this->ResetButtonLabelPlayersSet);
        break;
    }

    case Backend::GameInfo::PoppableEntry::Deal:
    {
        ui->resetButton->setText(this->ResetButtonLabelDeal);
        break;
    }

    case Backend::GameInfo::PoppableEntry::MandatorySoloTrigger:
    {
        ui->resetButton->setText(this->ResetButtonLabelMandatorySoloTrigger);
        break;
    }

    default:
        throw std::exception(u8"value of Backend::GameInfo::PoppableEntry not handled");
    }

    ui->saveButton->setEnabled(this->gameInfo.HasPlayersSet());
    ui->commitButton->setEnabled(this->gameInfo.HasPlayersSet());

    this->DetermineAndSetMultiplierLabels();
    ui->mandatorySoloButton->setEnabled(this->gameInfo.MandatorySolo() == Backend::GameInfo::MandatorySolo::Ready);

    this->RedrawPlayerHistory();
}

void MainWindow::ShowPlayerSelection()
{
    std::vector<std::pair<QString, bool>> currentPlayers;
    QString currentDealer;
    std::set<unsigned int> currentSitOutScheme;

    if(gameInfo.PlayerInfos().size() > 0)
    {
        const std::vector<std::shared_ptr<Backend::PlayerInfo>> playerInfos = gameInfo.PlayerInfos();

        for(auto playerInfosIt = playerInfos.begin(); playerInfosIt != playerInfos.end(); ++playerInfosIt)
        {
            currentPlayers.emplace_back(std::pair<QString, bool>(QString::fromUtf8((*playerInfosIt)->Name()), (*playerInfosIt)->IsPresent()));
        }

        std::string dealerName = gameInfo.Dealer()->Name();
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

    this->playerSelection = std::make_unique<Ui::PlayerSelection>(this->MaxPlayers, currentPlayers, currentDealer, currentSitOutScheme, this);
    this->playerSelection->setModal(true);
    this->playerSelection->show();
    int dialogCode = this->playerSelection->exec();

    if(dialogCode == QDialog::Rejected)
    {
        this->UpdateDisplay();
        return;
    }

    auto result = this->playerSelection->GetResults();
    this->playerSelection.reset();

    std::vector<std::string> players;

    std::transform(std::get<0>(result).begin(),
                   std::get<0>(result).end(),
                   std::back_inserter(players),
                   [](QString qs) { auto bytes = qs.toUtf8(); return std::string(bytes.constData(), bytes.length()); });

    auto dealerBytes = std::get<1>(result).toUtf8();
    std::string dealer(dealerBytes.constData(), dealerBytes.length());

    auto sitOutScheme = std::get<2>(result);

    gameInfo.SetPlayers(players, dealer, sitOutScheme);

    this->UpdateDisplay();
}

std::vector<std::pair<QString, bool>> MainWindow::GetDefaultPlayers()
{
    return std::vector<std::pair<QString, bool>>
    {
#ifdef MY_PLAYER_A
        std::pair<QString, bool>(QString::fromUtf8(MY_PLAYER_A), true),
#else
        std::pair<QString, bool>(QString::fromUtf8(u8"Spieler A"), true),
#endif
#ifdef MY_PLAYER_B
        std::pair<QString, bool>(QString::fromUtf8((MY_PLAYER_B)), true),
#else
        std::pair<QString, bool>(QString::fromUtf8(u8"Spieler B"), true),
#endif
#ifdef MY_PLAYER_C
        std::pair<QString, bool>(QString::fromUtf8((MY_PLAYER_C)), true),
#else
        std::pair<QString, bool>(QString::fromUtf8(u8"Spieler C"), true),
#endif
#ifdef MY_PLAYER_D
        std::pair<QString, bool>(QString::fromUtf8((MY_PLAYER_D)), true),
#else
        std::pair<QString, bool>(QString::fromUtf8(u8"Spieler D"), true),
#endif
#ifdef MY_PLAYER_E
        std::pair<QString, bool>(QString::fromUtf8((MY_PLAYER_E)), true),
#else
        std::pair<QString, bool>(QString::fromUtf8(u8"Spieler E"), true),
#endif
#ifdef MY_PLAYER_F
        std::pair<QString, bool>(QString::fromUtf8((MY_PLAYER_F)), true),
#else
        std::pair<QString, bool>(QString::fromUtf8(u8"Spieler F"), true),
#endif
#ifdef MY_PLAYER_G
        std::pair<QString, bool>(QString::fromUtf8((MY_PLAYER_G)), true),
#else
        std::pair<QString, bool>(QString::fromUtf8(u8"Spieler G"), true),
#endif
#ifdef MY_PLAYER_H
        std::pair<QString, bool>(QString::fromUtf8((MY_PLAYER_H)), true),
#else
        std::pair<QString, bool>(QString::fromUtf8(u8"Spieler H"), true),
#endif
    };
}

void MainWindow::RedrawPlayerHistory()
{
    ui->plotPlayerHistory->clearGraphs();

    if(!gameInfo.HasPlayersSet())
    {
        ui->plotPlayerHistory->replot();
        return;
    }

    auto players = this->gameInfo.PlayerInfos();
    auto map = this->GetHistoricData();

    for(unsigned int i = 0; i < players.size(); ++i)
    {
        if(ui->playerHistorySelectionCheckboxes[i]->isChecked())
        {
            auto name = QString::fromUtf8(players[i]->Name());
            auto data = map[name];

            QVector<double> dataX(data.first.begin(), data.first.end());
            QVector<double> dataY(data.second.begin(), data.second.end());

            dataX.insert(dataX.cbegin(), 0.0);
            dataY.insert(dataY.cbegin(), 0.0);

            auto * qcpGraph = ui->plotPlayerHistory->addGraph();
            qcpGraph->addData(dataX, dataY, true);

            auto pen = QPen(this->htmlColors[i]);
            pen.setWidth(3);
            qcpGraph->setPen(pen);
        }
    }

    auto x = static_cast<unsigned int>(map.begin()->second.first.size());
    x = std::max(x, 50u);
    ui->plotPlayerHistory->xAxis->setRange(x - 50u, x);
    ui->plotPlayerHistory->yAxis->rescale();

    ui->plotPlayerHistory->replot();
}

std::map<QString, std::pair<std::vector<int>, std::vector<int>>> MainWindow::GetHistoricData()
{
    std::map<QString, std::pair<std::vector<int>, std::vector<int>>> map;

    auto players = this->gameInfo.PlayerInfos();

    std::vector<int> x(players[0]->ScoreHistory().size());
    std::iota(x.begin(), x.end(), 1);

    for (auto & player : players)
    {
        map[QString::fromUtf8(player->Name())] = std::make_pair(x, player->ScoreHistory());
    }

    return map;
}

void MainWindow::ShowAboutDialog()
{
    QString messageBoxTitle = QString::fromUtf8(u8"Über QtDoppelKopf");

    QString messageBoxText = QString::fromUtf8(u8"Ein Programm zum Nachhalten des Spielstandes beim Doppelkopf nach den Hausregeln von Freunden.<br /><br />QtDoppelKopf Copyright (C) 2021 und später, tristhaus<br />Für dieses Programm besteht KEINERLEI GARANTIE.<br />Dies ist freie Software, die Sie unter bestimmten Bedingungen weitergeben dürfen. Siehe beigefügte LICENSE Datei für Details.<br /><br />Graphische Nutzeroberfläche mit <a href=\"https://doc.qt.io/\">Qt</a> gebaut.<br />Icon (Farbsymbole und Buchstaben) von tristhaus.<br /><a href=\"https://www.qcustomplot.com/\">QCustomPlot</a> Bibliothek (Version 2.1.0) von Emanuel Eichhammer benutzt unter der <a href=\"https://www.gnu.org/licenses/gpl-3.0.html\">GPL v3</a> Lizenz.<br />JSON De/Serialisierung via <a href=\"https://rapidjson.org/\">rapidjson</a> bereitgestellt von THL A29 Limited, eine Tencent Firma, und Milo Yip benutzt unter der <a href=\"http://opensource.org/licenses/MIT\">MIT Lizenz</a>.");

    this->aboutMessageBox = std::make_unique<QMessageBox>(
                    QMessageBox::Icon::NoIcon,
                    messageBoxTitle,
                    messageBoxText);

    this->aboutMessageBox->setTextFormat(Qt::RichText);
    this->aboutMessageBox->setTextInteractionFlags(Qt::TextBrowserInteraction);

    this->aboutMessageBox->exec();

    this->aboutMessageBox.reset();
}

void MainWindow::DetermineAndSetMultiplierLabels()
{
    auto preview = this->gameInfo.MultiplierPreview();

    if(this->gameInfo.MandatorySolo() == Backend::GameInfo::MandatorySolo::Active)
    {
        ui->currentGameMultiplier->setText(QString(u8"Pflichtsolorunde"));
    }
    else if(preview[2] > 0)
    {
        ui->currentGameMultiplier->setText(QString(u8"Dreifachbock"));
    }
    else if(preview[1] > 0)
    {
        ui->currentGameMultiplier->setText(QString(u8"Doppelbock"));
    }
    else if(preview[0] > 0)
    {
        ui->currentGameMultiplier->setText(QString(u8"Einfachbock"));
    }
    else
    {
        ui->currentGameMultiplier->setText(QString(u8"Kein Bock"));
    }

    ui->tripleMultiplier->setText(QString().number(preview[2]));
    ui->doubleMultiplier->setText(QString().number(preview[1]));
    ui->singleMultiplier->setText(QString().number(preview[0]));
}

void MainWindow::OnChangePlayerPressed()
{
    this->ShowPlayerSelection();
}

void MainWindow::OnLoadGamePressed()
{
    Resetter resetter([&](){ this->presetFilename.clear(); });

    auto folder = this->GetFolderForFileDialog();
    QString fileName = !this->presetFilename.isEmpty() ? this->presetFilename : QFileDialog::getOpenFileName(this, u8"", folder, FileFilter, nullptr, QFileDialog::Options());

    if(fileName.isEmpty())
    {
        return;
    }

    try
    {
        auto filenameBytes = fileName.toUtf8();
        std::string filename(filenameBytes.constData(), filenameBytes.length());
        this->gameInfo.LoadFrom(filename);
    }
    catch(std::exception & exception)
    {
        QString messageBoxTitle = QString::fromUtf8(u8"Fehler");

        QString messageBoxTextTemplate = QString::fromUtf8(u8"Beim Ladeversuch aufgetretener Fehler: %1");
        QString errorMesssage = QString::fromUtf8(exception.what());
        QString messageBoxText = messageBoxTextTemplate.arg(errorMesssage);

        auto errorBox = std::make_unique<QMessageBox>(
                    QMessageBox::Icon::Critical,
                    messageBoxTitle,
                    messageBoxText);

        errorBox->exec();

        errorBox.reset();
    }

    this->UpdateDisplay();
}

void MainWindow::OnSaveGamePressed()
{
    Resetter resetter([&](){ this->presetFilename.clear(); });

    auto folder = this->GetFolderForFileDialog();
    QString fileName = !this->presetFilename.isEmpty() ? this->presetFilename : QFileDialog::getSaveFileName(this, u8"", folder, this->FileFilter, nullptr, QFileDialog::Options());

    if(fileName.isEmpty())
    {
        return;
    }

    try
    {
        auto filenameBytes = fileName.toUtf8();
        std::string filename(filenameBytes.constData(), filenameBytes.length());
        this->gameInfo.SaveTo(filename);
    }
    catch(std::exception & exception)
    {
        QString messageBoxTitle = QString::fromUtf8(u8"Fehler");

        QString messageBoxTextTemplate = QString::fromUtf8(u8"Beim Speicherversuch aufgetretener Fehler: %1");
        QString errorMesssage = QString::fromUtf8(exception.what());
        QString messageBoxText = messageBoxTextTemplate.arg(errorMesssage);

        auto errorBox = std::make_unique<QMessageBox>(
                    QMessageBox::Icon::Critical,
                    messageBoxTitle,
                    messageBoxText);

        errorBox->exec();

        errorBox.reset();
    }
}

QString MainWindow::GetFolderForFileDialog()
{
    auto list = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    return QString(list.first());
}

void MainWindow::OnMandatorySoloPressed()
{
    this->gameInfo.TriggerMandatorySolo();

    this->UpdateDisplay();
}

void MainWindow::OnCommitPressed()
{
    std::vector<std::pair<std::string, int>> changes;

    for (unsigned int index = 0; index < this->MaxPlayers; ++index)
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

            auto nameBytes = ui->names[index]->text().toUtf8();
            std::string name(nameBytes.constData(), nameBytes.length());
            changes.emplace_back(std::make_pair(name, value));
        }
    }

    if(changes.size() == 0)
    {
        return;
    }

    auto numberOfEvents = static_cast<unsigned int>(ui->spinBox->value());

    this->gameInfo.PushDeal(changes, numberOfEvents);

    this->UpdateDisplay();
}

void MainWindow::OnResetPressed()
{
    auto playerInfos = this->gameInfo.PlayerInfos();

    std::vector<std::string> resetActuals;
    std::transform(playerInfos.begin(),
                   playerInfos.end(),
                   std::back_inserter(resetActuals),
                   [](std::shared_ptr<Backend::PlayerInfo> info){ return info->InputInLastDeal(); });

    auto numberOfEvents = this->gameInfo.LastNumberOfEvents();

    bool wasDeal = this->gameInfo.LastPoppableEntry() == Backend::GameInfo::PoppableEntry::Deal;
    this->gameInfo.PopLastEntry();

    this->UpdateDisplay();

    if(wasDeal)
    {
        for (unsigned int index = 0; index < resetActuals.size(); ++index)
        {
            this->ui->actuals[index]->setText(QString::fromUtf8(resetActuals[index]));
        }

        this->ui->spinBox->setValue(static_cast<int>(numberOfEvents));
    }
}

void MainWindow::OnHistoryPlayerSelected()
{
    this->RedrawPlayerHistory();
}

void MainWindow::OnAboutPressed()
{
    this->ShowAboutDialog();
}
