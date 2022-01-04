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

#if defined(_SKIP_LONG_TEST)
#elif defined(_USE_LONG_TEST)
#else
#error "you need to make a choice between using or skipping long tests, -D_USE_LONG_TEST -D_SKIP_LONG_TEST"
#endif

#include <QTest>
#include <QtTest>

#include "../Frontend/mainwindow.h"
#include "../Frontend/mainwindow_ui.h"

#include "../TestHelper/memoryrepository.h"

class FrontendTest : public QObject
{
    Q_OBJECT

private:
    const int SingleShotInterval = 1000;
    const int ShortInterval = 10;
    const unsigned int MaxPlayers = 8U;
    const unsigned int DefaultPlayers = 8U;
    const QString ExpectedStandardNamesStyleSheet = QString::fromUtf8(u8"QLabel { }");
    const QString ExpectedDealerNamesStyleSheet = QString::fromUtf8(u8"QLabel { border: 3px solid orange ; border-radius : 6px }");

public:
    FrontendTest();

private slots:
    void ConstructionShallWorkCompletely() const;
#ifdef _USE_LONG_TEST
    void CancellingInitialPlayerSelectionLeadsToDisabledUI();
    void SetDataShallBeDisplayed();
    void PlayerSelectionButtonShallTriggerDialogAndSetDataShallBeUsed();
    void OneCommittedGameShallBeDisplayed();
    void TwoCommittedGamesShallBeDisplayed();
    void TwoCommittedAndTwoPoppedGameShallBeDisplayed();
    void AllLevelsOfMultipliersShallCorrectlyBeDisplayed() const;
    void StatisticsShallCorrectlyBeDisplayed() const;
    void ScoreHistoryPlotShallWorkCorrectly() const;
    void AboutButtonShallTriggerDialogAndOKShallClose();
    void MandatorySoloButtonShallBeEnabledAndTrigger() const;
    void EveryOptionOfResetButtonShallBeDisplayed();
    void SaveGameShallWorkWithPresetValueAndPersist() const;
    void LoadGameShallWorkWithPresetValueAndDisplayGame();
    void FocusOnActualShallTriggerAutofill() const;
    void ReturnKeyShallCommitGame() const;
#endif // _USE_LONG_TEST
};

FrontendTest::FrontendTest()
= default;

void FrontendTest::ConstructionShallWorkCompletely() const//NOLINT(google-readability-function-size, hicpp-function-size, readability-function-size)
{
    try
    {
        // Act
        MainWindow mw(MaxPlayers, std::make_shared<MemoryRepository>(), false);

        // Assert
        QVERIFY2(mw.ui->centralwidget, qPrintable(QString::fromUtf8(u8"not created central widget")));
        QVERIFY2(mw.ui->leftVerticalLayout, qPrintable(QString::fromUtf8(u8"not created vertical layout")));

        QVERIFY2(mw.ui->topMenu, qPrintable(QString::fromUtf8(u8"not created top menu")));
        QVERIFY2(mw.ui->topMenuLayout, qPrintable(QString::fromUtf8(u8"not created top menu layout")));
        QVERIFY2(mw.ui->changePlayersButton, qPrintable(QString::fromUtf8(u8"not created change players button")));
        QVERIFY2(mw.ui->loadButton, qPrintable(QString::fromUtf8(u8"not created load button")));
        QVERIFY2(mw.ui->saveButton, qPrintable(QString::fromUtf8(u8"not created save button")));
        QVERIFY2(mw.ui->mandatorySoloButton, qPrintable(QString::fromUtf8(u8"not created mandatory solo button")));
        QVERIFY2(mw.ui->aboutButton, qPrintable(QString::fromUtf8(u8"not created about button")));
        QVERIFY2(mw.ui->topMenuSpacer, qPrintable(QString::fromUtf8(u8"not created top menu spacer")));

        QVERIFY2(mw.ui->namesLayout, qPrintable(QString::fromUtf8(u8"not created names layout")));
        QVERIFY2(mw.ui->namenLabel, qPrintable(QString::fromUtf8(u8"not created namen label")));
        QVERIFY2(!mw.ui->names.empty(), qPrintable(QString::fromUtf8(u8"there must be name labels")));
        for(auto & name : mw.ui->names)
        {
            QVERIFY2(name, qPrintable(QString::fromUtf8(u8"name label not created")));
        }

        QVERIFY2(mw.ui->letztesLabel, qPrintable(QString::fromUtf8(u8"not created letztes label")));
        QVERIFY2(!mw.ui->lastGames.empty(), qPrintable(QString::fromUtf8(u8"there must be last games labels")));
        QVERIFY2(mw.ui->lastGames.size() == mw.ui->names.size(), qPrintable(QString::fromUtf8(u8"sizes do not match: lastGames, names")));
        for(auto & lastGame : mw.ui->lastGames)
        {
            QVERIFY2(lastGame, qPrintable(QString::fromUtf8(u8"last game label not created")));
        }

        QVERIFY2(mw.ui->aktuellesLabel, qPrintable(QString::fromUtf8(u8"not created aktuelles label")));
        QVERIFY2(!mw.ui->actuals.empty(), qPrintable(QString::fromUtf8(u8"there must be actuals inputs")));
        QVERIFY2(mw.ui->actuals.size() == mw.ui->names.size(), qPrintable(QString::fromUtf8(u8"sizes do not match: actuals, names")));
        for(auto & actual : mw.ui->actuals)
        {
            QVERIFY2(actual, qPrintable(QString::fromUtf8(u8"actual input not created")));
        }

        QVERIFY2(mw.ui->controlWidget, qPrintable(QString::fromUtf8(u8"not created control widget")));
        QVERIFY2(mw.ui->horizontalLayout, qPrintable(QString::fromUtf8(u8"not created horizontal layout")));
        QVERIFY2(mw.ui->bockereignisseLabel, qPrintable(QString::fromUtf8(u8"not created bockereignisse label")));
        QVERIFY2(mw.ui->spinBox, qPrintable(QString::fromUtf8(u8"not created spin box")));
        QVERIFY2(mw.ui->controlSpacer0, qPrintable(QString::fromUtf8(u8"not created control spacer 0")));
        QVERIFY2(mw.ui->remainingGamesInRound, qPrintable(QString::fromUtf8(u8"not created remaining games in round")));
        QVERIFY2(mw.ui->controlSpacer1, qPrintable(QString::fromUtf8(u8"not created control spacer 1")));
        QVERIFY2(mw.ui->commitButton, qPrintable(QString::fromUtf8(u8"not created commit button")));
        QVERIFY2(mw.ui->controlSpacer2, qPrintable(QString::fromUtf8(u8"not created control spacer 2")));
        QVERIFY2(mw.ui->resetButton, qPrintable(QString::fromUtf8(u8"not created reset button")));

        QVERIFY2(mw.ui->spielstandLabel, qPrintable(QString::fromUtf8(u8"not created spielstand label")));
        QVERIFY2(!mw.ui->scores.empty(), qPrintable(QString::fromUtf8(u8"there must be scores labels")));
        QVERIFY2(mw.ui->scores.size() == mw.ui->names.size(), qPrintable(QString::fromUtf8(u8"sizes do not match: scores, names")));
        for(auto & score : mw.ui->scores)
        {
            QVERIFY2(score, qPrintable(QString::fromUtf8(u8"score label not created")));
        }

        QVERIFY2(mw.ui->zuZahlenLabel, qPrintable(QString::fromUtf8(u8"not created zu zahlen label")));
        QVERIFY2(!mw.ui->cashs.empty(), qPrintable(QString::fromUtf8(u8"there must be scores labels")));
        QVERIFY2(mw.ui->cashs.size() == mw.ui->names.size(), qPrintable(QString::fromUtf8(u8"sizes do not match: cashs, names")));
        for(auto & cash : mw.ui->cashs)
        {
            QVERIFY2(cash, qPrintable(QString::fromUtf8(u8"cash label not created")));
        }

        QVERIFY2(mw.ui->kassenstandLabel, qPrintable(QString::fromUtf8(u8"not created kassenstand label")));
        QVERIFY2(mw.ui->totalCash, qPrintable(QString::fromUtf8(u8"not created total cash label")));

        QVERIFY2(mw.ui->statisticsBox, qPrintable(QString::fromUtf8(u8"not created statistics box")));
        QVERIFY2(mw.ui->statisticsGridLayout, qPrintable(QString::fromUtf8(u8"not created grid layout")));

        QVERIFY2(mw.ui->gewonnenLabel, qPrintable(QString::fromUtf8(u8"not created gewonnen label")));
        QVERIFY2(mw.ui->verlorenLabel, qPrintable(QString::fromUtf8(u8"not created verloren label")));
        QVERIFY2(mw.ui->anzahlSpieleLabel, qPrintable(QString::fromUtf8(u8"not created anzahl spiele label")));
        QVERIFY2(mw.ui->soloGewonnenLabel, qPrintable(QString::fromUtf8(u8"not created solo gewonnen label")));
        QVERIFY2(mw.ui->soloVerlorenLabel, qPrintable(QString::fromUtf8(u8"not created solo verloren label")));
        QVERIFY2(mw.ui->soloPunkteLabel, qPrintable(QString::fromUtf8(u8"not created punkte label")));
        QVERIFY2(mw.ui->groessterGewinnLabel, qPrintable(QString::fromUtf8(u8"not created groesster gewinn label")));
        QVERIFY2(mw.ui->groessterVerlustLabel, qPrintable(QString::fromUtf8(u8"not created groesster verlust label")));
        QVERIFY2(mw.ui->ohneBockLabel, qPrintable(QString::fromUtf8(u8"not created ohne bock label")));

        QVERIFY2(!mw.ui->statisticNames.empty(), qPrintable(QString::fromUtf8(u8"there must be statisticNames labels")));
        QVERIFY2(mw.ui->statisticNames.size() == mw.ui->names.size(), qPrintable(QString::fromUtf8(u8"sizes do not match: statisticNames, names")));
        for(auto & statisticName : mw.ui->statisticNames)
        {
            QVERIFY2(statisticName, qPrintable(QString::fromUtf8(u8"statistic name label not created")));
        }

        QVERIFY2(!mw.ui->numberWons.empty(), qPrintable(QString::fromUtf8(u8"there must be numberWons labels")));
        QVERIFY2(mw.ui->numberWons.size() == mw.ui->names.size(), qPrintable(QString::fromUtf8(u8"sizes do not match: numberWons, names")));
        for(auto & numberWon : mw.ui->numberWons)
        {
            QVERIFY2(numberWon, qPrintable(QString::fromUtf8(u8"number won label not created")));
        }

        QVERIFY2(!mw.ui->numberLosts.empty(), qPrintable(QString::fromUtf8(u8"there must be numberLosts labels")));
        QVERIFY2(mw.ui->numberLosts.size() == mw.ui->names.size(), qPrintable(QString::fromUtf8(u8"sizes do not match: numberLosts, names")));
        for(auto & numberLost : mw.ui->numberLosts)
        {
            QVERIFY2(numberLost, qPrintable(QString::fromUtf8(u8"number lost label not created")));
        }

        QVERIFY2(!mw.ui->numberPlayeds.empty(), qPrintable(QString::fromUtf8(u8"there must be numberPlayeds labels")));
        QVERIFY2(mw.ui->numberPlayeds.size() == mw.ui->names.size(), qPrintable(QString::fromUtf8(u8"sizes do not match: numberPlayeds, names")));
        for(auto & numberPlayed : mw.ui->numberPlayeds)
        {
            QVERIFY2(numberPlayed, qPrintable(QString::fromUtf8(u8"number playeds label not created")));
        }

        QVERIFY2(!mw.ui->numberSoloWons.empty(), qPrintable(QString::fromUtf8(u8"there must be numberSoloWons labels")));
        QVERIFY2(mw.ui->numberSoloWons.size() == mw.ui->names.size(), qPrintable(QString::fromUtf8(u8"sizes do not match: numberSoloWons, names")));
        for(auto & numberSoloWon : mw.ui->numberSoloWons)
        {
            QVERIFY2(numberSoloWon, qPrintable(QString::fromUtf8(u8"solo wons label not created")));
        }

        QVERIFY2(!mw.ui->numberSoloLosts.empty(), qPrintable(QString::fromUtf8(u8"there must be numberSoloLosts labels")));
        QVERIFY2(mw.ui->numberSoloLosts.size() == mw.ui->names.size(), qPrintable(QString::fromUtf8(u8"sizes do not match: numberSoloLosts, names")));
        for(auto & numberSoloLost : mw.ui->numberSoloLosts)
        {
            QVERIFY2(numberSoloLost, qPrintable(QString::fromUtf8(u8"solo losts label not created")));
        }

        QVERIFY2(!mw.ui->pointsSolos.empty(), qPrintable(QString::fromUtf8(u8"there must be pointsSolos labels")));
        QVERIFY2(mw.ui->pointsSolos.size() == mw.ui->names.size(), qPrintable(QString::fromUtf8(u8"sizes do not match: pointsSolos, names")));
        for(auto & pointsSolo : mw.ui->pointsSolos)
        {
            QVERIFY2(pointsSolo, qPrintable(QString::fromUtf8(u8"points solos label not created")));
        }

        QVERIFY2(!mw.ui->maxSingleWins.empty(), qPrintable(QString::fromUtf8(u8"there must be maxSingleWins labels")));
        QVERIFY2(mw.ui->maxSingleWins.size() == mw.ui->names.size(), qPrintable(QString::fromUtf8(u8"sizes do not match: maxSingleWins, names")));
        for(auto & maxSingleWin : mw.ui->maxSingleWins)
        {
            QVERIFY2(maxSingleWin, qPrintable(QString::fromUtf8(u8"max single wins label not created")));
        }

        QVERIFY2(!mw.ui->maxSingleLosss.empty(), qPrintable(QString::fromUtf8(u8"there must be maxSingleLosss labels")));
        QVERIFY2(mw.ui->maxSingleLosss.size() == mw.ui->names.size(), qPrintable(QString::fromUtf8(u8"sizes do not match: maxSingleLosss, names")));
        for(auto & maxSingleLoss : mw.ui->maxSingleLosss)
        {
            QVERIFY2(maxSingleLoss, qPrintable(QString::fromUtf8(u8"max single losss label not created")));
        }

        QVERIFY2(!mw.ui->unmultipliedScores.empty(), qPrintable(QString::fromUtf8(u8"there must be unmultipliedScores labels")));
        QVERIFY2(mw.ui->unmultipliedScores.size() == mw.ui->names.size(), qPrintable(QString::fromUtf8(u8"sizes do not match: unmultipliedScores, names")));
        for(auto & unmultipliedScore : mw.ui->unmultipliedScores)
        {
            QVERIFY2(unmultipliedScore, qPrintable(QString::fromUtf8(u8"unmultiplied scores label not created")));
        }

        QVERIFY2(mw.ui->currentGameMultiplier, qPrintable(QString::fromUtf8(u8"current game multiplier not created")));
        QVERIFY2(mw.ui->multiplierPreviewWidget, qPrintable(QString::fromUtf8(u8"multiplier preview widget not created")));
        QVERIFY2(mw.ui->multiplierPreviewGridLayout, qPrintable(QString::fromUtf8(u8"multiplier preview grid layout not created")));
        QVERIFY2(mw.ui->dreifachbockLabel, qPrintable(QString::fromUtf8(u8"dreifachbock label not created")));
        QVERIFY2(mw.ui->doppelbockLabel, qPrintable(QString::fromUtf8(u8"doppelbock label not created")));
        QVERIFY2(mw.ui->einfachbockLabel, qPrintable(QString::fromUtf8(u8"einfachbock label not created")));
        QVERIFY2(mw.ui->tripleMultiplier, qPrintable(QString::fromUtf8(u8"triple multiplier not created")));
        QVERIFY2(mw.ui->doubleMultiplier, qPrintable(QString::fromUtf8(u8"double multiplier not created")));
        QVERIFY2(mw.ui->singleMultiplier, qPrintable(QString::fromUtf8(u8"single multiplier not created")));

        QVERIFY2(mw.ui->playerHistorySelectionWidget, qPrintable(QString::fromUtf8(u8"not created player history selection widget")));
        QVERIFY2(mw.ui->playerHistoryGridLayout, qPrintable(QString::fromUtf8(u8"not created player history grid layout")));

        QVERIFY2(!mw.ui->playerHistorySelectionLayouts.empty(), qPrintable(QString::fromUtf8(u8"there must be playerHistorySelectionLayouts labels")));
        QVERIFY2(mw.ui->playerHistorySelectionLayouts.size() == mw.ui->names.size(), qPrintable(QString::fromUtf8(u8"sizes do not match: playerHistorySelectionLayouts, names")));
        for(auto & playerHistorySelectionLayout : mw.ui->playerHistorySelectionLayouts)
        {
            QVERIFY2(playerHistorySelectionLayout, qPrintable(QString::fromUtf8(u8"player history selection layout not created")));
        }

        QVERIFY2(!mw.ui->playerHistorySelectionCheckboxes.empty(), qPrintable(QString::fromUtf8(u8"there must be playerHistorySelectionCheckboxes labels")));
        QVERIFY2(mw.ui->playerHistorySelectionCheckboxes.size() == mw.ui->names.size(), qPrintable(QString::fromUtf8(u8"sizes do not match: playerHistorySelectionCheckboxes, names")));
        for(auto & playerHistorySelectionCheckboxe : mw.ui->playerHistorySelectionCheckboxes)
        {
            QVERIFY2(playerHistorySelectionCheckboxe, qPrintable(QString::fromUtf8(u8"player history selection checkbox not created")));
        }

        QVERIFY2(!mw.ui->playerHistorySelectionLabels.empty(), qPrintable(QString::fromUtf8(u8"there must be playerHistorySelectionLabels labels")));
        QVERIFY2(mw.ui->playerHistorySelectionLabels.size() == mw.ui->names.size(), qPrintable(QString::fromUtf8(u8"sizes do not match: playerHistorySelectionLabels, names")));
        for(auto & playerHistorySelectionLabel : mw.ui->playerHistorySelectionLabels)
        {
            QVERIFY2(playerHistorySelectionLabel, qPrintable(QString::fromUtf8(u8"player history selection label not created")));
        }

        QVERIFY2(mw.ui->plotPlayerHistory, qPrintable(QString::fromUtf8(u8"not created player history plot")));

        QVERIFY2(mw.StandardNamesStylesheet.compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"unexpected content of standard names style sheet")));
        QVERIFY2(mw.DealerNamesStylesheet.compare(ExpectedDealerNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"unexpected content of dealer names style sheet")));
    }
    catch (std::exception & ex)
    {
        QFAIL(ex.what());
    }
    catch (...)
    {
        QFAIL(u8"unknown exception");
    }
}

#ifdef _USE_LONG_TEST

void FrontendTest::CancellingInitialPlayerSelectionLeadsToDisabledUI()
{
    // Arrange
    MainWindow mw(this->DefaultPlayers, std::make_shared<MemoryRepository>(), false);

    // Act
    // spy needed such that events actually happen
    QSignalSpy spyChangePlayersButton(mw.ui->changePlayersButton, &QAbstractButton::pressed);

    // Act
    QTimer::singleShot(this->SingleShotInterval, this, [&]()
    {
        mw.playerSelection->reject();
    });

    QTest::mouseClick(mw.ui->changePlayersButton, Qt::LeftButton);

    // Assert
    QVERIFY2(mw.ui->changePlayersButton->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state changePlayersButton")));
    QVERIFY2(mw.ui->loadButton->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state loadButton")));
    QVERIFY2(mw.ui->saveButton->isEnabled() == false, qPrintable(QString::fromUtf8(u8"incorrect state saveButton")));
    QVERIFY2(mw.ui->mandatorySoloButton->isEnabled() == false, qPrintable(QString::fromUtf8(u8"incorrect state mandatorySoloButton")));
    QVERIFY2(mw.ui->aboutButton->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state aboutButton")));

    QVERIFY2(mw.ui->actuals[0]->isVisible() == false, qPrintable(QString::fromUtf8(u8"incorrect state actuals 0")));
    QVERIFY2(mw.ui->actuals[1]->isVisible() == false, qPrintable(QString::fromUtf8(u8"incorrect state actuals 1")));
    QVERIFY2(mw.ui->actuals[2]->isVisible() == false, qPrintable(QString::fromUtf8(u8"incorrect state actuals 2")));
    QVERIFY2(mw.ui->actuals[3]->isVisible() == false, qPrintable(QString::fromUtf8(u8"incorrect state actuals 3")));
    QVERIFY2(mw.ui->actuals[4]->isVisible() == false, qPrintable(QString::fromUtf8(u8"incorrect state actuals 4")));
    QVERIFY2(mw.ui->actuals[5]->isVisible() == false, qPrintable(QString::fromUtf8(u8"incorrect state actuals 5")));
    QVERIFY2(mw.ui->actuals[6]->isVisible() == false, qPrintable(QString::fromUtf8(u8"incorrect state actuals 6")));
    QVERIFY2(mw.ui->actuals[7]->isVisible() == false, qPrintable(QString::fromUtf8(u8"incorrect state actuals 7")));

    QVERIFY2(mw.ui->remainingGamesInRound->text().compare(QString::fromUtf8(u8"Neue Runde")) == 0, qPrintable(QString::fromUtf8(u8"incorrect remaining games in round")));

    QVERIFY2(mw.ui->spinBox->isEnabled() == false, qPrintable(QString::fromUtf8(u8"events spinbox incorrect state")));
    QVERIFY2(mw.ui->commitButton->isEnabled() == false, qPrintable(QString::fromUtf8(u8"commitButton incorrect state")));
    QVERIFY2(mw.ui->resetButton->isEnabled() == false, qPrintable(QString::fromUtf8(u8"resetButton incorrect state")));
}

void FrontendTest::SetDataShallBeDisplayed()
{
    // Arrange
    std::vector<std::string> players
    {
        u8"A",
        u8"B",
        u8"C",
        u8"D",
        u8"E",
        u8"F"
    };

    std::string dealer(u8"C");
    std::set<unsigned int> sitOutScheme
    {
        3
    };

    MainWindow mw(this->DefaultPlayers, std::make_shared<MemoryRepository>(), false);

    // Act
    mw.gameInfo.SetPlayers(players, dealer, sitOutScheme);
    mw.UpdateDisplay();

    // Assert
    QVERIFY2(mw.ui->names[0]->text().compare(QString::fromUtf8(u8"A")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 0")));
    QVERIFY2(mw.ui->names[1]->text().compare(QString::fromUtf8(u8"B")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 1")));
    QVERIFY2(mw.ui->names[2]->text().compare(QString::fromUtf8(u8"C")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 2")));
    QVERIFY2(mw.ui->names[3]->text().compare(QString::fromUtf8(u8"D")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 3")));
    QVERIFY2(mw.ui->names[4]->text().compare(QString::fromUtf8(u8"E")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 4")));
    QVERIFY2(mw.ui->names[5]->text().compare(QString::fromUtf8(u8"F")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 5")));

    QVERIFY2(mw.ui->names[0]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 0")));
    QVERIFY2(mw.ui->names[1]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 1")));
    QVERIFY2(mw.ui->names[2]->styleSheet().compare(ExpectedDealerNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 2")));
    QVERIFY2(mw.ui->names[3]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 3")));
    QVERIFY2(mw.ui->names[4]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 4")));
    QVERIFY2(mw.ui->names[5]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 5")));

    QVERIFY2(mw.ui->actuals[0]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 0")));
    QVERIFY2(mw.ui->actuals[1]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 1")));
    QVERIFY2(mw.ui->actuals[2]->isEnabled() == false, qPrintable(QString::fromUtf8(u8"incorrect state actuals 2")));
    QVERIFY2(mw.ui->actuals[3]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 3")));
    QVERIFY2(mw.ui->actuals[4]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 4")));
    QVERIFY2(mw.ui->actuals[5]->isEnabled() == false, qPrintable(QString::fromUtf8(u8"incorrect state actuals 5")));

    QVERIFY2(mw.ui->remainingGamesInRound->text().compare(QString::fromUtf8(u8"Neue Runde")) == 0, qPrintable(QString::fromUtf8(u8"incorrect remaining games in round")));

    QVERIFY2(mw.ui->scores[0]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 0")));
    QVERIFY2(mw.ui->scores[1]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 1")));
    QVERIFY2(mw.ui->scores[2]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 2")));
    QVERIFY2(mw.ui->scores[3]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 3")));
    QVERIFY2(mw.ui->scores[4]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 4")));
    QVERIFY2(mw.ui->scores[5]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 5")));

    QVERIFY2(mw.ui->actuals[0]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 0 not empty")));
    QVERIFY2(mw.ui->actuals[1]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 1 not empty")));
    QVERIFY2(mw.ui->actuals[2]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 2 not empty")));
    QVERIFY2(mw.ui->actuals[3]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 3 not empty")));
    QVERIFY2(mw.ui->actuals[4]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 4 not empty")));
    QVERIFY2(mw.ui->actuals[5]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 5 not empty")));

    QVERIFY2(mw.ui->spinBox->value() == 0, qPrintable(QString::fromUtf8(u8"events spinbox not set to zero")));

    QVERIFY2(mw.ui->cashs[0]->text().compare(QString::fromUtf8(u8"0,00")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 0")));
    QVERIFY2(mw.ui->cashs[1]->text().compare(QString::fromUtf8(u8"0,00")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 1")));
    QVERIFY2(mw.ui->cashs[2]->text().compare(QString::fromUtf8(u8"0,00")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 2")));
    QVERIFY2(mw.ui->cashs[3]->text().compare(QString::fromUtf8(u8"0,00")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 3")));
    QVERIFY2(mw.ui->cashs[4]->text().compare(QString::fromUtf8(u8"0,00")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 4")));
    QVERIFY2(mw.ui->cashs[5]->text().compare(QString::fromUtf8(u8"0,00")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 5")));

    QVERIFY2(mw.ui->totalCash->text().compare(QString::fromUtf8(u8"0,00 (inkl. 0,00 pro Abwesender)")) == 0, qPrintable(QString::fromUtf8(u8"incorrect totalCash")));

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString::fromUtf8(u8"Kein Bock")) == 0, qPrintable(QString::fromUtf8(u8"current game multiplier label incorrect")));
    QVERIFY2(mw.ui->tripleMultiplier->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"triple multiplier label incorrect")));
    QVERIFY2(mw.ui->doubleMultiplier->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"double multiplier label incorrect")));
    QVERIFY2(mw.ui->singleMultiplier->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"single multiplier label incorrect")));
}

void FrontendTest::PlayerSelectionButtonShallTriggerDialogAndSetDataShallBeUsed()
{
    // Arrange
    MainWindow mw(this->DefaultPlayers, std::make_shared<MemoryRepository>(), false);

    // spy needed such that events actually happen
    QSignalSpy spyChangePlayersButton(mw.ui->changePlayersButton, &QAbstractButton::pressed);

    // Act
    bool changePlayersDialogFound = false;
    QTimer::singleShot(this->SingleShotInterval, this, [&]()
    {
        changePlayersDialogFound = mw.playerSelection != nullptr;
        mw.playerSelection->dialogNames[1]->setText(QString::fromUtf8(u8"NewPlayer"));
        if(changePlayersDialogFound)
        {
            QTest::mouseClick(mw.playerSelection->dialogAcceptButton, Qt::LeftButton);
        }
    });

    QTest::mouseClick(mw.ui->changePlayersButton, Qt::LeftButton);

    // Assert
    QVERIFY2(changePlayersDialogFound, qPrintable(QString::fromUtf8(u8"changePlayersDialog not found")));

    QVERIFY2(mw.playerSelection == nullptr, qPrintable(QString::fromUtf8(u8"playerSelection still reachable")));

    QVERIFY2(mw.ui->names[1]->text().compare(QString::fromUtf8(u8"NewPlayer")) == 0, qPrintable(QString::fromUtf8(u8"incorrect name")));
}

void FrontendTest::OneCommittedGameShallBeDisplayed()
{
    // Arrange
    std::vector<std::string> players
    {
        u8"A",
        u8"B",
        u8"C",
        u8"D",
        u8"E",
        u8"F"
    };

    std::string dealer(u8"C");
    std::set<unsigned int> sitOutScheme
    {
        3
    };

    MainWindow mw(this->DefaultPlayers, std::make_shared<MemoryRepository>(), false);

    QSignalSpy commitButtonSpy(mw.ui->commitButton, &QPushButton::clicked);

    mw.gameInfo.SetPlayers(players, dealer, sitOutScheme);
    mw.UpdateDisplay();

    // Act
    mw.ui->actuals[0]->setText(QString::fromUtf8(u8"2"));
    mw.ui->actuals[3]->setText(QString::fromUtf8(u8"2"));
    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    // Assert
    QVERIFY2(mw.ui->names[0]->text().compare(QString::fromUtf8(u8"A")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 0")));
    QVERIFY2(mw.ui->names[1]->text().compare(QString::fromUtf8(u8"B")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 1")));
    QVERIFY2(mw.ui->names[2]->text().compare(QString::fromUtf8(u8"C")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 2")));
    QVERIFY2(mw.ui->names[3]->text().compare(QString::fromUtf8(u8"D")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 3")));
    QVERIFY2(mw.ui->names[4]->text().compare(QString::fromUtf8(u8"E")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 4")));
    QVERIFY2(mw.ui->names[5]->text().compare(QString::fromUtf8(u8"F")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 5")));

    QVERIFY2(mw.ui->names[0]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 0")));
    QVERIFY2(mw.ui->names[1]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 1")));
    QVERIFY2(mw.ui->names[2]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 2")));
    QVERIFY2(mw.ui->names[3]->styleSheet().compare(ExpectedDealerNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 3")));
    QVERIFY2(mw.ui->names[4]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 4")));
    QVERIFY2(mw.ui->names[5]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 5")));

    QVERIFY2(mw.ui->actuals[0]->isEnabled() == false, qPrintable(QString::fromUtf8(u8"incorrect state actuals 0")));
    QVERIFY2(mw.ui->actuals[1]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 1")));
    QVERIFY2(mw.ui->actuals[2]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 2")));
    QVERIFY2(mw.ui->actuals[3]->isEnabled() == false, qPrintable(QString::fromUtf8(u8"incorrect state actuals 3")));
    QVERIFY2(mw.ui->actuals[4]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 4")));
    QVERIFY2(mw.ui->actuals[5]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 5")));

    QVERIFY2(mw.ui->remainingGamesInRound->text().compare(QString::fromUtf8(u8"5 Spiele in Runde")) == 0, qPrintable(QString::fromUtf8(u8"incorrect remaining games in round")));

    QVERIFY2(mw.ui->scores[0]->text().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 0")));
    QVERIFY2(mw.ui->scores[1]->text().compare(QString::fromUtf8(u8"-2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 1")));
    QVERIFY2(mw.ui->scores[2]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 2")));
    QVERIFY2(mw.ui->scores[3]->text().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 3")));
    QVERIFY2(mw.ui->scores[4]->text().compare(QString::fromUtf8(u8"-2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 4")));
    QVERIFY2(mw.ui->scores[5]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 5")));

    QVERIFY2(mw.ui->lastGames[0]->text().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 0")));
    QVERIFY2(mw.ui->lastGames[1]->text().compare(QString::fromUtf8(u8"-2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 1")));
    QVERIFY2(mw.ui->lastGames[2]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 2")));
    QVERIFY2(mw.ui->lastGames[3]->text().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 3")));
    QVERIFY2(mw.ui->lastGames[4]->text().compare(QString::fromUtf8(u8"-2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 4")));
    QVERIFY2(mw.ui->lastGames[5]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 5")));

    QVERIFY2(mw.ui->actuals[0]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 0 not empty")));
    QVERIFY2(mw.ui->actuals[1]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 1 not empty")));
    QVERIFY2(mw.ui->actuals[2]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 2 not empty")));
    QVERIFY2(mw.ui->actuals[3]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 3 not empty")));
    QVERIFY2(mw.ui->actuals[4]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 4 not empty")));
    QVERIFY2(mw.ui->actuals[5]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 5 not empty")));

    QVERIFY2(mw.ui->spinBox->value() == 0, qPrintable(QString::fromUtf8(u8"events spinbox not set to zero")));

    QVERIFY2(mw.ui->cashs[0]->text().compare(QString::fromUtf8(u8"0,00")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 0")));
    QVERIFY2(mw.ui->cashs[1]->text().compare(QString::fromUtf8(u8"0,02")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 1")));
    QVERIFY2(mw.ui->cashs[2]->text().compare(QString::fromUtf8(u8"0,01")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 2")));
    QVERIFY2(mw.ui->cashs[3]->text().compare(QString::fromUtf8(u8"0,00")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 3")));
    QVERIFY2(mw.ui->cashs[4]->text().compare(QString::fromUtf8(u8"0,02")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 4")));
    QVERIFY2(mw.ui->cashs[5]->text().compare(QString::fromUtf8(u8"0,01")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 5")));

    QVERIFY2(mw.ui->totalCash->text().compare(QString::fromUtf8(u8"0,08 (inkl. 0,01 pro Abwesender)")) == 0, qPrintable(QString::fromUtf8(u8"incorrect totalCash")));

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString::fromUtf8(u8"Kein Bock")) == 0, qPrintable(QString::fromUtf8(u8"current game multiplier label incorrect")));
    QVERIFY2(mw.ui->tripleMultiplier->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"triple multiplier label incorrect")));
    QVERIFY2(mw.ui->doubleMultiplier->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"double multiplier label incorrect")));
    QVERIFY2(mw.ui->singleMultiplier->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"single multiplier label incorrect")));
}

void FrontendTest::TwoCommittedGamesShallBeDisplayed()
{
    // Arrange
    std::vector<std::string> players
    {
        u8"A",
        u8"B",
        u8"C",
        u8"D",
        u8"E",
        u8"F"
    };

    std::string dealer(u8"C");
    std::set<unsigned int> sitOutScheme
    {
        3
    };

    MainWindow mw(this->DefaultPlayers, std::make_shared<MemoryRepository>(), false);

    QSignalSpy commitButtonSpy(mw.ui->commitButton, &QPushButton::clicked);

    mw.gameInfo.SetPlayers(players, dealer, sitOutScheme);
    mw.UpdateDisplay();

    // Act
    mw.ui->actuals[0]->setText(QString::fromUtf8(u8"2"));
    mw.ui->actuals[3]->setText(QString::fromUtf8(u8"2"));
    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    mw.ui->actuals[2]->setText(QString::fromUtf8(u8"-3"));
    mw.ui->actuals[4]->setText(QString::fromUtf8(u8"-3"));
    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    // Assert
    QVERIFY2(mw.ui->names[0]->text().compare(QString::fromUtf8(u8"A")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 0")));
    QVERIFY2(mw.ui->names[1]->text().compare(QString::fromUtf8(u8"B")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 1")));
    QVERIFY2(mw.ui->names[2]->text().compare(QString::fromUtf8(u8"C")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 2")));
    QVERIFY2(mw.ui->names[3]->text().compare(QString::fromUtf8(u8"D")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 3")));
    QVERIFY2(mw.ui->names[4]->text().compare(QString::fromUtf8(u8"E")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 4")));
    QVERIFY2(mw.ui->names[5]->text().compare(QString::fromUtf8(u8"F")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 5")));

    QVERIFY2(mw.ui->names[0]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 0")));
    QVERIFY2(mw.ui->names[1]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 1")));
    QVERIFY2(mw.ui->names[2]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 2")));
    QVERIFY2(mw.ui->names[3]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 3")));
    QVERIFY2(mw.ui->names[4]->styleSheet().compare(ExpectedDealerNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 4")));
    QVERIFY2(mw.ui->names[5]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 5")));

    QVERIFY2(mw.ui->actuals[0]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 0")));
    QVERIFY2(mw.ui->actuals[1]->isEnabled() == false, qPrintable(QString::fromUtf8(u8"incorrect state actuals 1")));
    QVERIFY2(mw.ui->actuals[2]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 2")));
    QVERIFY2(mw.ui->actuals[3]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 3")));
    QVERIFY2(mw.ui->actuals[4]->isEnabled() == false, qPrintable(QString::fromUtf8(u8"incorrect state actuals 4")));
    QVERIFY2(mw.ui->actuals[5]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 5")));

    QVERIFY2(mw.ui->remainingGamesInRound->text().compare(QString::fromUtf8(u8"4 Spiele in Runde")) == 0, qPrintable(QString::fromUtf8(u8"incorrect remaining games in round")));

    QVERIFY2(mw.ui->scores[0]->text().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 0")));
    QVERIFY2(mw.ui->scores[1]->text().compare(QString::fromUtf8(u8"1")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 1")));
    QVERIFY2(mw.ui->scores[2]->text().compare(QString::fromUtf8(u8"-3")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 2")));
    QVERIFY2(mw.ui->scores[3]->text().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 3")));
    QVERIFY2(mw.ui->scores[4]->text().compare(QString::fromUtf8(u8"-5")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 4")));
    QVERIFY2(mw.ui->scores[5]->text().compare(QString::fromUtf8(u8"3")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 5")));

    QVERIFY2(mw.ui->lastGames[0]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 0")));
    QVERIFY2(mw.ui->lastGames[1]->text().compare(QString::fromUtf8(u8"3")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 1")));
    QVERIFY2(mw.ui->lastGames[2]->text().compare(QString::fromUtf8(u8"-3")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 2")));
    QVERIFY2(mw.ui->lastGames[3]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 3")));
    QVERIFY2(mw.ui->lastGames[4]->text().compare(QString::fromUtf8(u8"-3")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 4")));
    QVERIFY2(mw.ui->lastGames[5]->text().compare(QString::fromUtf8(u8"3")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 5")));

    QVERIFY2(mw.ui->actuals[0]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 0 not empty")));
    QVERIFY2(mw.ui->actuals[1]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 1 not empty")));
    QVERIFY2(mw.ui->actuals[2]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 2 not empty")));
    QVERIFY2(mw.ui->actuals[3]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 3 not empty")));
    QVERIFY2(mw.ui->actuals[4]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 4 not empty")));
    QVERIFY2(mw.ui->actuals[5]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 5 not empty")));

    QVERIFY2(mw.ui->spinBox->value() == 0, qPrintable(QString::fromUtf8(u8"events spinbox not set to zero")));

    QVERIFY2(mw.ui->cashs[0]->text().compare(QString::fromUtf8(u8"0,00")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 0")));
    QVERIFY2(mw.ui->cashs[1]->text().compare(QString::fromUtf8(u8"0,01")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 1")));
    QVERIFY2(mw.ui->cashs[2]->text().compare(QString::fromUtf8(u8"0,03")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 2")));
    QVERIFY2(mw.ui->cashs[3]->text().compare(QString::fromUtf8(u8"0,00")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 3")));
    QVERIFY2(mw.ui->cashs[4]->text().compare(QString::fromUtf8(u8"0,04")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 4")));
    QVERIFY2(mw.ui->cashs[5]->text().compare(QString::fromUtf8(u8"0,00")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 5")));

    QVERIFY2(mw.ui->totalCash->text().compare(QString::fromUtf8(u8"0,10 (inkl. 0,01 pro Abwesender)")) == 0, qPrintable(QString::fromUtf8(u8"incorrect totalCash")));

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString::fromUtf8(u8"Kein Bock")) == 0, qPrintable(QString::fromUtf8(u8"current game multiplier label incorrect")));
    QVERIFY2(mw.ui->tripleMultiplier->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"triple multiplier label incorrect")));
    QVERIFY2(mw.ui->doubleMultiplier->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"double multiplier label incorrect")));
    QVERIFY2(mw.ui->singleMultiplier->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"single multiplier label incorrect")));
}

void FrontendTest::TwoCommittedAndTwoPoppedGameShallBeDisplayed() //NOLINT(google-readability-function-size, hicpp-function-size, readability-function-size)
{
    // Arrange
    std::vector<std::string> players
    {
        u8"A",
        u8"B",
        u8"C",
        u8"D",
        u8"E",
        u8"F"
    };

    std::string dealer(u8"C");
    std::set<unsigned int> sitOutScheme
    {
        3
    };

    MainWindow mw(this->DefaultPlayers, std::make_shared<MemoryRepository>(), false);

    QSignalSpy commitButtonSpy(mw.ui->commitButton, &QPushButton::clicked);
    QSignalSpy resetButtonSpy(mw.ui->resetButton, &QPushButton::clicked);

    mw.gameInfo.SetPlayers(players, dealer, sitOutScheme);
    mw.UpdateDisplay();

    // Act, Assert
    bool isEnabled1 = mw.ui->resetButton->isEnabled();

    mw.ui->actuals[0]->setText(QString::fromUtf8(u8"2"));
    mw.ui->actuals[3]->setText(QString::fromUtf8(u8"2"));
    mw.ui->spinBox->setValue(1);

    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    bool isEnabled2 = mw.ui->resetButton->isEnabled();

    mw.ui->actuals[2]->setText(QString::fromUtf8(u8"-3"));
    mw.ui->actuals[4]->setText(QString::fromUtf8(u8"-3"));
    mw.ui->spinBox->setValue(2);

    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    bool isEnabled3 = mw.ui->resetButton->isEnabled();

    QVERIFY2(mw.ui->names[0]->text().compare(QString::fromUtf8(u8"A")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 0")));
    QVERIFY2(mw.ui->names[1]->text().compare(QString::fromUtf8(u8"B")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 1")));
    QVERIFY2(mw.ui->names[2]->text().compare(QString::fromUtf8(u8"C")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 2")));
    QVERIFY2(mw.ui->names[3]->text().compare(QString::fromUtf8(u8"D")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 3")));
    QVERIFY2(mw.ui->names[4]->text().compare(QString::fromUtf8(u8"E")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 4")));
    QVERIFY2(mw.ui->names[5]->text().compare(QString::fromUtf8(u8"F")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 5")));

    QVERIFY2(mw.ui->actuals[0]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 0")));
    QVERIFY2(mw.ui->actuals[1]->isEnabled() == false, qPrintable(QString::fromUtf8(u8"incorrect state actuals 1")));
    QVERIFY2(mw.ui->actuals[2]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 2")));
    QVERIFY2(mw.ui->actuals[3]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 3")));
    QVERIFY2(mw.ui->actuals[4]->isEnabled() == false, qPrintable(QString::fromUtf8(u8"incorrect state actuals 4")));
    QVERIFY2(mw.ui->actuals[5]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 5")));

    QVERIFY2(mw.ui->remainingGamesInRound->text().compare(QString::fromUtf8(u8"4 Spiele in Runde")) == 0, qPrintable(QString::fromUtf8(u8"incorrect remaining games in round")));

    QVERIFY2(mw.ui->scores[0]->text().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 0")));
    QVERIFY2(mw.ui->scores[1]->text().compare(QString::fromUtf8(u8"4")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 1")));
    QVERIFY2(mw.ui->scores[2]->text().compare(QString::fromUtf8(u8"-6")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 2")));
    QVERIFY2(mw.ui->scores[3]->text().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 3")));
    QVERIFY2(mw.ui->scores[4]->text().compare(QString::fromUtf8(u8"-8")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 4")));
    QVERIFY2(mw.ui->scores[5]->text().compare(QString::fromUtf8(u8"6")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 5")));

    QVERIFY2(mw.ui->lastGames[0]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 0")));
    QVERIFY2(mw.ui->lastGames[1]->text().compare(QString::fromUtf8(u8"6")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 1")));
    QVERIFY2(mw.ui->lastGames[2]->text().compare(QString::fromUtf8(u8"-6")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 2")));
    QVERIFY2(mw.ui->lastGames[3]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 3")));
    QVERIFY2(mw.ui->lastGames[4]->text().compare(QString::fromUtf8(u8"-6")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 4")));
    QVERIFY2(mw.ui->lastGames[5]->text().compare(QString::fromUtf8(u8"6")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 5")));

    QVERIFY2(mw.ui->actuals[0]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 0 not empty")));
    QVERIFY2(mw.ui->actuals[1]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 1 not empty")));
    QVERIFY2(mw.ui->actuals[2]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 2 not empty")));
    QVERIFY2(mw.ui->actuals[3]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 3 not empty")));
    QVERIFY2(mw.ui->actuals[4]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 4 not empty")));
    QVERIFY2(mw.ui->actuals[5]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 5 not empty")));

    QVERIFY2(mw.ui->spinBox->value() == 0, qPrintable(QString::fromUtf8(u8"events spinbox not set to zero")));

    QVERIFY2(mw.ui->cashs[0]->text().compare(QString::fromUtf8(u8"0,02")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 0")));
    QVERIFY2(mw.ui->cashs[1]->text().compare(QString::fromUtf8(u8"0,01")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 1")));
    QVERIFY2(mw.ui->cashs[2]->text().compare(QString::fromUtf8(u8"0,06")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 2")));
    QVERIFY2(mw.ui->cashs[3]->text().compare(QString::fromUtf8(u8"0,02")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 3")));
    QVERIFY2(mw.ui->cashs[4]->text().compare(QString::fromUtf8(u8"0,07")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 4")));
    QVERIFY2(mw.ui->cashs[5]->text().compare(QString::fromUtf8(u8"0,00")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 5")));

    QVERIFY2(mw.ui->totalCash->text().compare(QString::fromUtf8(u8"0,24 (inkl. 0,03 pro Abwesender)")) == 0, qPrintable(QString::fromUtf8(u8"incorrect totalCash")));

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString::fromUtf8(u8"Dreifachbock")) == 0, qPrintable(QString::fromUtf8(u8"current game multiplier label incorrect")));
    QVERIFY2(mw.ui->tripleMultiplier->text().compare(QString::fromUtf8(u8"5")) == 0, qPrintable(QString::fromUtf8(u8"triple multiplier label incorrect")));
    QVERIFY2(mw.ui->doubleMultiplier->text().compare(QString::fromUtf8(u8"1")) == 0, qPrintable(QString::fromUtf8(u8"double multiplier label incorrect")));
    QVERIFY2(mw.ui->singleMultiplier->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"single multiplier label incorrect")));

    QVERIFY2(isEnabled1 == false, qPrintable(QString::fromUtf8(u8"reset button wrong enabled state")));
    QVERIFY2(isEnabled2, qPrintable(QString::fromUtf8(u8"reset button wrong enabled state")));
    QVERIFY2(isEnabled3, qPrintable(QString::fromUtf8(u8"reset button wrong enabled state")));

    QTest::mouseClick(mw.ui->resetButton, Qt::LeftButton);
    bool isEnabled4 = mw.ui->resetButton->isEnabled();

    QVERIFY2(mw.ui->names[0]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 0")));
    QVERIFY2(mw.ui->names[1]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 1")));
    QVERIFY2(mw.ui->names[2]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 2")));
    QVERIFY2(mw.ui->names[3]->styleSheet().compare(ExpectedDealerNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 3")));
    QVERIFY2(mw.ui->names[4]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 4")));
    QVERIFY2(mw.ui->names[5]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 5")));

    QVERIFY2(mw.ui->actuals[0]->isEnabled() == false, qPrintable(QString::fromUtf8(u8"incorrect state actuals 0")));
    QVERIFY2(mw.ui->actuals[1]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 1")));
    QVERIFY2(mw.ui->actuals[2]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 2")));
    QVERIFY2(mw.ui->actuals[3]->isEnabled() == false, qPrintable(QString::fromUtf8(u8"incorrect state actuals 3")));
    QVERIFY2(mw.ui->actuals[4]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 4")));
    QVERIFY2(mw.ui->actuals[5]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 5")));

    QVERIFY2(mw.ui->remainingGamesInRound->text().compare(QString::fromUtf8(u8"5 Spiele in Runde")) == 0, qPrintable(QString::fromUtf8(u8"incorrect remaining games in round")));

    QVERIFY2(mw.ui->scores[0]->text().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 0")));
    QVERIFY2(mw.ui->scores[1]->text().compare(QString::fromUtf8(u8"-2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 1")));
    QVERIFY2(mw.ui->scores[2]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 2")));
    QVERIFY2(mw.ui->scores[3]->text().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 3")));
    QVERIFY2(mw.ui->scores[4]->text().compare(QString::fromUtf8(u8"-2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 4")));
    QVERIFY2(mw.ui->scores[5]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 5")));

    QVERIFY2(mw.ui->lastGames[0]->text().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 0")));
    QVERIFY2(mw.ui->lastGames[1]->text().compare(QString::fromUtf8(u8"-2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 1")));
    QVERIFY2(mw.ui->lastGames[2]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 2")));
    QVERIFY2(mw.ui->lastGames[3]->text().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 3")));
    QVERIFY2(mw.ui->lastGames[4]->text().compare(QString::fromUtf8(u8"-2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 4")));
    QVERIFY2(mw.ui->lastGames[5]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 5")));

    QVERIFY2(mw.ui->actuals[0]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 0 not empty")));
    QVERIFY2(mw.ui->actuals[1]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 1 not empty")));
    QVERIFY2(mw.ui->actuals[4]->text().compare(QString::fromUtf8(u8"-3")) == 0, qPrintable(QString::fromUtf8(u8"actuals 2 wrong content")));
    QVERIFY2(mw.ui->actuals[3]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 3 not empty")));
    QVERIFY2(mw.ui->actuals[4]->text().compare(QString::fromUtf8(u8"-3")) == 0, qPrintable(QString::fromUtf8(u8"actuals 4 wrong content")));
    QVERIFY2(mw.ui->actuals[5]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 5 not empty")));

    QVERIFY2(mw.ui->spinBox->value() == 2, qPrintable(QString::fromUtf8(u8"events spinbox not set to correct value")));

    QVERIFY2(mw.ui->cashs[0]->text().compare(QString::fromUtf8(u8"0,00")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 0")));
    QVERIFY2(mw.ui->cashs[1]->text().compare(QString::fromUtf8(u8"0,02")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 1")));
    QVERIFY2(mw.ui->cashs[2]->text().compare(QString::fromUtf8(u8"0,01")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 2")));
    QVERIFY2(mw.ui->cashs[3]->text().compare(QString::fromUtf8(u8"0,00")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 3")));
    QVERIFY2(mw.ui->cashs[4]->text().compare(QString::fromUtf8(u8"0,02")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 4")));
    QVERIFY2(mw.ui->cashs[5]->text().compare(QString::fromUtf8(u8"0,01")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 5")));

    QVERIFY2(mw.ui->totalCash->text().compare(QString::fromUtf8(u8"0,08 (inkl. 0,01 pro Abwesender)")) == 0, qPrintable(QString::fromUtf8(u8"incorrect totalCash")));

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString::fromUtf8(u8"Einfachbock")) == 0, qPrintable(QString::fromUtf8(u8"current game multiplier label incorrect")));
    QVERIFY2(mw.ui->tripleMultiplier->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"triple multiplier label incorrect")));
    QVERIFY2(mw.ui->doubleMultiplier->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"double multiplier label incorrect")));
    QVERIFY2(mw.ui->singleMultiplier->text().compare(QString::fromUtf8(u8"6")) == 0, qPrintable(QString::fromUtf8(u8"single multiplier label incorrect")));

    QVERIFY2(isEnabled4, qPrintable(QString::fromUtf8(u8"reset button wrong enabled state")));

    QTest::mouseClick(mw.ui->resetButton, Qt::LeftButton);
    bool isEnabled5 = mw.ui->resetButton->isEnabled();

    QVERIFY2(mw.ui->names[0]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 0")));
    QVERIFY2(mw.ui->names[1]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 1")));
    QVERIFY2(mw.ui->names[2]->styleSheet().compare(ExpectedDealerNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 2")));
    QVERIFY2(mw.ui->names[3]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 3")));
    QVERIFY2(mw.ui->names[4]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 4")));
    QVERIFY2(mw.ui->names[5]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 5")));

    QVERIFY2(mw.ui->actuals[0]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 0")));
    QVERIFY2(mw.ui->actuals[1]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 1")));
    QVERIFY2(mw.ui->actuals[2]->isEnabled() == false, qPrintable(QString::fromUtf8(u8"incorrect state actuals 2")));
    QVERIFY2(mw.ui->actuals[3]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 3")));
    QVERIFY2(mw.ui->actuals[4]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 4")));
    QVERIFY2(mw.ui->actuals[5]->isEnabled() == false, qPrintable(QString::fromUtf8(u8"incorrect state actuals 5")));

    QVERIFY2(mw.ui->remainingGamesInRound->text().compare(QString::fromUtf8(u8"Neue Runde")) == 0, qPrintable(QString::fromUtf8(u8"incorrect remaining games in round")));

    QVERIFY2(mw.ui->scores[0]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 0")));
    QVERIFY2(mw.ui->scores[1]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 1")));
    QVERIFY2(mw.ui->scores[2]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 2")));
    QVERIFY2(mw.ui->scores[3]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 3")));
    QVERIFY2(mw.ui->scores[4]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 4")));
    QVERIFY2(mw.ui->scores[5]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 5")));

    QVERIFY2(mw.ui->lastGames[0]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 0")));
    QVERIFY2(mw.ui->lastGames[1]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 1")));
    QVERIFY2(mw.ui->lastGames[2]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 2")));
    QVERIFY2(mw.ui->lastGames[3]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 3")));
    QVERIFY2(mw.ui->lastGames[4]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 4")));
    QVERIFY2(mw.ui->lastGames[5]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 5")));

    QVERIFY2(mw.ui->actuals[0]->text().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"actuals 0 wrong content")));
    QVERIFY2(mw.ui->actuals[1]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 1 not empty")));
    QVERIFY2(mw.ui->actuals[2]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 2 not empty")));
    QVERIFY2(mw.ui->actuals[3]->text().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"actuals 3 wrong content")));
    QVERIFY2(mw.ui->actuals[4]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 4 not empty")));
    QVERIFY2(mw.ui->actuals[5]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 5 not empty")));

    QVERIFY2(mw.ui->spinBox->value() == 1, qPrintable(QString::fromUtf8(u8"events spinbox not set to correct value")));

    QVERIFY2(mw.ui->cashs[0]->text().compare(QString::fromUtf8(u8"0,00")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 0")));
    QVERIFY2(mw.ui->cashs[1]->text().compare(QString::fromUtf8(u8"0,00")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 1")));
    QVERIFY2(mw.ui->cashs[2]->text().compare(QString::fromUtf8(u8"0,00")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 2")));
    QVERIFY2(mw.ui->cashs[3]->text().compare(QString::fromUtf8(u8"0,00")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 3")));
    QVERIFY2(mw.ui->cashs[4]->text().compare(QString::fromUtf8(u8"0,00")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 4")));
    QVERIFY2(mw.ui->cashs[5]->text().compare(QString::fromUtf8(u8"0,00")) == 0, qPrintable(QString::fromUtf8(u8"incorrect cashs 5")));

    QVERIFY2(mw.ui->totalCash->text().compare(QString::fromUtf8(u8"0,00 (inkl. 0,00 pro Abwesender)")) == 0, qPrintable(QString::fromUtf8(u8"incorrect totalCash")));

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString::fromUtf8(u8"Kein Bock")) == 0, qPrintable(QString::fromUtf8(u8"current game multiplier label incorrect")));
    QVERIFY2(mw.ui->tripleMultiplier->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"triple multiplier label incorrect")));
    QVERIFY2(mw.ui->doubleMultiplier->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"double multiplier label incorrect")));
    QVERIFY2(mw.ui->singleMultiplier->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"single multiplier label incorrect")));

    QVERIFY2(isEnabled5 == false, qPrintable(QString::fromUtf8(u8"reset button wrong enabled state")));
}

void FrontendTest::AllLevelsOfMultipliersShallCorrectlyBeDisplayed() const
{
    // Arrange
    std::vector<std::string> players
    {
        u8"A",
        u8"B",
        u8"C",
        u8"D",
        u8"E"
    };

    std::string dealer(u8"C");
    std::set<unsigned int> sitOutScheme;

    MainWindow mw(this->DefaultPlayers, std::make_shared<MemoryRepository>(), false);

    QSignalSpy commitButtonSpy(mw.ui->commitButton, &QPushButton::clicked);

    mw.gameInfo.SetPlayers(players, dealer, sitOutScheme);
    mw.UpdateDisplay();

    // Act, Assert

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString::fromUtf8(u8"Kein Bock")) == 0, qPrintable(QString::fromUtf8(u8"current game multiplier label incorrect")));
    QVERIFY2(mw.ui->tripleMultiplier->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"triple multiplier label incorrect")));
    QVERIFY2(mw.ui->doubleMultiplier->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"double multiplier label incorrect")));
    QVERIFY2(mw.ui->singleMultiplier->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"single multiplier label incorrect")));

    mw.ui->actuals[0]->setText(QString::fromUtf8(u8"2"));
    mw.ui->actuals[3]->setText(QString::fromUtf8(u8"2"));
    mw.ui->spinBox->setValue(1);

    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString::fromUtf8(u8"Einfachbock")) == 0, qPrintable(QString::fromUtf8(u8"current game multiplier label incorrect")));
    QVERIFY2(mw.ui->tripleMultiplier->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"triple multiplier label incorrect")));
    QVERIFY2(mw.ui->doubleMultiplier->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"double multiplier label incorrect")));
    QVERIFY2(mw.ui->singleMultiplier->text().compare(QString::fromUtf8(u8"5")) == 0, qPrintable(QString::fromUtf8(u8"single multiplier label incorrect")));

    mw.ui->actuals[2]->setText(QString::fromUtf8(u8"-3"));
    mw.ui->actuals[4]->setText(QString::fromUtf8(u8"-3"));
    mw.ui->spinBox->setValue(1);

    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString::fromUtf8(u8"Doppelbock")) == 0, qPrintable(QString::fromUtf8(u8"current game multiplier label incorrect")));
    QVERIFY2(mw.ui->tripleMultiplier->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"triple multiplier label incorrect")));
    QVERIFY2(mw.ui->doubleMultiplier->text().compare(QString::fromUtf8(u8"4")) == 0, qPrintable(QString::fromUtf8(u8"double multiplier label incorrect")));
    QVERIFY2(mw.ui->singleMultiplier->text().compare(QString::fromUtf8(u8"1")) == 0, qPrintable(QString::fromUtf8(u8"single multiplier label incorrect")));

    mw.ui->actuals[2]->setText(QString::fromUtf8(u8"-3"));
    mw.ui->actuals[4]->setText(QString::fromUtf8(u8"-3"));
    mw.ui->spinBox->setValue(1);

    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString::fromUtf8(u8"Dreifachbock")) == 0, qPrintable(QString::fromUtf8(u8"current game multiplier label incorrect")));
    QVERIFY2(mw.ui->tripleMultiplier->text().compare(QString::fromUtf8(u8"3")) == 0, qPrintable(QString::fromUtf8(u8"triple multiplier label incorrect")));
    QVERIFY2(mw.ui->doubleMultiplier->text().compare(QString::fromUtf8(u8"1")) == 0, qPrintable(QString::fromUtf8(u8"double multiplier label incorrect")));
    QVERIFY2(mw.ui->singleMultiplier->text().compare(QString::fromUtf8(u8"1")) == 0, qPrintable(QString::fromUtf8(u8"single multiplier label incorrect")));
}

void FrontendTest::StatisticsShallCorrectlyBeDisplayed() const
{
    // Arrange
    std::vector<std::string> players
    {
        u8"A",
        u8"B",
        u8"C",
        u8"D",
        u8"E"
    };

    std::string dealer(u8"A");
    std::set<unsigned int> sitOutScheme {};

    MainWindow mw(this->DefaultPlayers, std::make_shared<MemoryRepository>(), false);

    QSignalSpy commitButtonSpy(mw.ui->commitButton, &QPushButton::clicked);

    mw.gameInfo.SetPlayers(players, dealer, sitOutScheme);
    mw.UpdateDisplay();

    // Act
    mw.ui->actuals[1]->setText(QString::fromUtf8(u8"-1"));
    mw.ui->actuals[2]->setText(QString::fromUtf8(u8"-1"));
    mw.ui->actuals[3]->setText(QString::fromUtf8(u8"1"));
    mw.ui->actuals[4]->setText(QString::fromUtf8(u8"1"));
    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    mw.ui->actuals[0]->setText(QString::fromUtf8(u8"3"));
    mw.ui->actuals[2]->setText(QString::fromUtf8(u8"-1"));
    mw.ui->actuals[3]->setText(QString::fromUtf8(u8"-1"));
    mw.ui->actuals[4]->setText(QString::fromUtf8(u8"-1"));
    mw.ui->spinBox->setValue(1);
    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    mw.ui->actuals[0]->setText(QString::fromUtf8(u8"2"));
    mw.ui->actuals[1]->setText(QString::fromUtf8(u8"2"));
    mw.ui->actuals[3]->setText(QString::fromUtf8(u8"2"));
    mw.ui->actuals[4]->setText(QString::fromUtf8(u8"-6"));
    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    mw.ui->actuals[0]->setText(QString::fromUtf8(u8"3"));
    mw.ui->actuals[1]->setText(QString::fromUtf8(u8"-3"));
    mw.ui->actuals[2]->setText(QString::fromUtf8(u8"3"));
    mw.ui->actuals[4]->setText(QString::fromUtf8(u8"-3"));
    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    // Assert
    QVERIFY2(mw.ui->names[0]->text().compare(QString::fromUtf8(u8"A")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 0")));
    QVERIFY2(mw.ui->names[1]->text().compare(QString::fromUtf8(u8"B")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 1")));
    QVERIFY2(mw.ui->names[2]->text().compare(QString::fromUtf8(u8"C")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 2")));
    QVERIFY2(mw.ui->names[3]->text().compare(QString::fromUtf8(u8"D")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 3")));
    QVERIFY2(mw.ui->names[4]->text().compare(QString::fromUtf8(u8"E")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 4")));

    QVERIFY2(mw.ui->remainingGamesInRound->text().compare(QString::fromUtf8(u8"1 Spiel in Runde")) == 0, qPrintable(QString::fromUtf8(u8"incorrect remaining games in round")));

    QVERIFY2(mw.ui->scores[0]->text().compare(QString::fromUtf8(u8"13")) == 0, qPrintable(QString::fromUtf8(u8"incorrect score 0")));
    QVERIFY2(mw.ui->scores[1]->text().compare(QString::fromUtf8(u8"-3")) == 0, qPrintable(QString::fromUtf8(u8"incorrect score 1")));
    QVERIFY2(mw.ui->scores[2]->text().compare(QString::fromUtf8(u8"4")) == 0, qPrintable(QString::fromUtf8(u8"incorrect score 2")));
    QVERIFY2(mw.ui->scores[3]->text().compare(QString::fromUtf8(u8"4")) == 0, qPrintable(QString::fromUtf8(u8"incorrect score 3")));
    QVERIFY2(mw.ui->scores[4]->text().compare(QString::fromUtf8(u8"-18")) == 0, qPrintable(QString::fromUtf8(u8"incorrect score 4")));

    QVERIFY2(mw.ui->numberWons[0]->text().compare(QString::fromUtf8(u8"3")) == 0, qPrintable(QString::fromUtf8(u8"incorrect number wons 0")));
    QVERIFY2(mw.ui->numberWons[1]->text().compare(QString::fromUtf8(u8"1")) == 0, qPrintable(QString::fromUtf8(u8"incorrect number wons 1")));
    QVERIFY2(mw.ui->numberWons[2]->text().compare(QString::fromUtf8(u8"1")) == 0, qPrintable(QString::fromUtf8(u8"incorrect number wons 2")));
    QVERIFY2(mw.ui->numberWons[3]->text().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect number wons 3")));
    QVERIFY2(mw.ui->numberWons[4]->text().compare(QString::fromUtf8(u8"1")) == 0, qPrintable(QString::fromUtf8(u8"incorrect number wons 4")));

    QVERIFY2(mw.ui->numberLosts[0]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect number losts 0")));
    QVERIFY2(mw.ui->numberLosts[1]->text().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect number losts 1")));
    QVERIFY2(mw.ui->numberLosts[2]->text().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect number losts 2")));
    QVERIFY2(mw.ui->numberLosts[3]->text().compare(QString::fromUtf8(u8"1")) == 0, qPrintable(QString::fromUtf8(u8"incorrect number losts 3")));
    QVERIFY2(mw.ui->numberLosts[4]->text().compare(QString::fromUtf8(u8"3")) == 0, qPrintable(QString::fromUtf8(u8"incorrect number losts 4")));

    QVERIFY2(mw.ui->numberPlayeds[0]->text().compare(QString::fromUtf8(u8"3")) == 0, qPrintable(QString::fromUtf8(u8"incorrect number playeds 0")));
    QVERIFY2(mw.ui->numberPlayeds[1]->text().compare(QString::fromUtf8(u8"3")) == 0, qPrintable(QString::fromUtf8(u8"incorrect number playeds 1")));
    QVERIFY2(mw.ui->numberPlayeds[2]->text().compare(QString::fromUtf8(u8"3")) == 0, qPrintable(QString::fromUtf8(u8"incorrect number playeds 2")));
    QVERIFY2(mw.ui->numberPlayeds[3]->text().compare(QString::fromUtf8(u8"3")) == 0, qPrintable(QString::fromUtf8(u8"incorrect number playeds 3")));
    QVERIFY2(mw.ui->numberPlayeds[4]->text().compare(QString::fromUtf8(u8"4")) == 0, qPrintable(QString::fromUtf8(u8"incorrect number playeds 4")));

    QVERIFY2(mw.ui->numberSoloWons[0]->text().compare(QString::fromUtf8(u8"1")) == 0, qPrintable(QString::fromUtf8(u8"incorrect number solo wons 0")));
    QVERIFY2(mw.ui->numberSoloWons[1]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect number solo wons 1")));
    QVERIFY2(mw.ui->numberSoloWons[2]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect number solo wons 2")));
    QVERIFY2(mw.ui->numberSoloWons[3]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect number solo wons 3")));
    QVERIFY2(mw.ui->numberSoloWons[4]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect number solo wons 4")));

    QVERIFY2(mw.ui->numberSoloLosts[0]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect number solo losts 0")));
    QVERIFY2(mw.ui->numberSoloLosts[1]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect number solo losts 1")));
    QVERIFY2(mw.ui->numberSoloLosts[2]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect number solo losts 2")));
    QVERIFY2(mw.ui->numberSoloLosts[3]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect number solo losts 3")));
    QVERIFY2(mw.ui->numberSoloLosts[4]->text().compare(QString::fromUtf8(u8"1")) == 0, qPrintable(QString::fromUtf8(u8"incorrect number solo losts 4")));

    QVERIFY2(mw.ui->pointsSolos[0]->text().compare(QString::fromUtf8(u8"3")) == 0, qPrintable(QString::fromUtf8(u8"incorrect points solos 0")));
    QVERIFY2(mw.ui->pointsSolos[1]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect points solos 1")));
    QVERIFY2(mw.ui->pointsSolos[2]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect points solos 2")));
    QVERIFY2(mw.ui->pointsSolos[3]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect points solos 3")));
    QVERIFY2(mw.ui->pointsSolos[4]->text().compare(QString::fromUtf8(u8"-12")) == 0, qPrintable(QString::fromUtf8(u8"incorrect points solos 4")));

    QVERIFY2(mw.ui->maxSingleWins[0]->text().compare(QString::fromUtf8(u8"6")) == 0, qPrintable(QString::fromUtf8(u8"incorrect max single win 0")));
    QVERIFY2(mw.ui->maxSingleWins[1]->text().compare(QString::fromUtf8(u8"4")) == 0, qPrintable(QString::fromUtf8(u8"incorrect max single win 1")));
    QVERIFY2(mw.ui->maxSingleWins[2]->text().compare(QString::fromUtf8(u8"6")) == 0, qPrintable(QString::fromUtf8(u8"incorrect max single win 2")));
    QVERIFY2(mw.ui->maxSingleWins[3]->text().compare(QString::fromUtf8(u8"4")) == 0, qPrintable(QString::fromUtf8(u8"incorrect max single win 3")));
    QVERIFY2(mw.ui->maxSingleWins[4]->text().compare(QString::fromUtf8(u8"1")) == 0, qPrintable(QString::fromUtf8(u8"incorrect max single win 4")));

    QVERIFY2(mw.ui->maxSingleLosss[0]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect max single loss 0")));
    QVERIFY2(mw.ui->maxSingleLosss[1]->text().compare(QString::fromUtf8(u8"-6")) == 0, qPrintable(QString::fromUtf8(u8"incorrect max single loss 1")));
    QVERIFY2(mw.ui->maxSingleLosss[2]->text().compare(QString::fromUtf8(u8"-1")) == 0, qPrintable(QString::fromUtf8(u8"incorrect max single loss 2")));
    QVERIFY2(mw.ui->maxSingleLosss[3]->text().compare(QString::fromUtf8(u8"-1")) == 0, qPrintable(QString::fromUtf8(u8"incorrect max single loss 3")));
    QVERIFY2(mw.ui->maxSingleLosss[4]->text().compare(QString::fromUtf8(u8"-12")) == 0, qPrintable(QString::fromUtf8(u8"incorrect max single loss 4")));

    QVERIFY2(mw.ui->unmultipliedScores[0]->text().compare(QString::fromUtf8(u8"8")) == 0, qPrintable(QString::fromUtf8(u8"incorrect unmultiplied scores 0")));
    QVERIFY2(mw.ui->unmultipliedScores[1]->text().compare(QString::fromUtf8(u8"-2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect unmultiplied scores 1")));
    QVERIFY2(mw.ui->unmultipliedScores[2]->text().compare(QString::fromUtf8(u8"1")) == 0, qPrintable(QString::fromUtf8(u8"incorrect unmultiplied scores 2")));
    QVERIFY2(mw.ui->unmultipliedScores[3]->text().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect unmultiplied scores 3")));
    QVERIFY2(mw.ui->unmultipliedScores[4]->text().compare(QString::fromUtf8(u8"-9")) == 0, qPrintable(QString::fromUtf8(u8"incorrect unmultiplied scores 4")));
}

void FrontendTest::ScoreHistoryPlotShallWorkCorrectly() const
{
    // Arrange
    std::vector<std::string> players
    {
        u8"A",
        u8"B",
        u8"C",
        u8"D",
        u8"E"
    };

    std::string dealer(u8"A");
    std::set<unsigned int> sitOutScheme {};

    MainWindow mw(this->DefaultPlayers, std::make_shared<MemoryRepository>(), false);

    QSignalSpy commitButtonSpy(mw.ui->commitButton, &QPushButton::clicked);

    mw.gameInfo.SetPlayers(players, dealer, sitOutScheme);
    mw.UpdateDisplay();

    // Act
    mw.ui->actuals[1]->setText(QString::fromUtf8(u8"-1"));
    mw.ui->actuals[2]->setText(QString::fromUtf8(u8"-1"));
    mw.ui->actuals[3]->setText(QString::fromUtf8(u8"1"));
    mw.ui->actuals[4]->setText(QString::fromUtf8(u8"1"));
    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    mw.ui->actuals[0]->setText(QString::fromUtf8(u8"3"));
    mw.ui->actuals[2]->setText(QString::fromUtf8(u8"-1"));
    mw.ui->actuals[3]->setText(QString::fromUtf8(u8"-1"));
    mw.ui->actuals[4]->setText(QString::fromUtf8(u8"-1"));
    mw.ui->spinBox->setValue(1);
    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    // Act, Assert
    QVERIFY2(mw.ui->plotPlayerHistory->graphCount() == 5, qPrintable(QString::fromUtf8(u8"incorrect graph count A")));

    mw.ui->playerHistorySelectionCheckboxes[2]->setChecked(false);

    QVERIFY2(mw.ui->plotPlayerHistory->graphCount() == 4, qPrintable(QString::fromUtf8(u8"incorrect graph count B")));

    mw.ui->playerHistorySelectionCheckboxes[2]->setChecked(true);
    mw.ui->playerHistorySelectionCheckboxes[0]->setChecked(false);
    mw.ui->playerHistorySelectionCheckboxes[1]->setChecked(false);

    QVERIFY2(mw.ui->plotPlayerHistory->graphCount() == 3, qPrintable(QString::fromUtf8(u8"incorrect graph count C")));

    mw.ui->playerHistorySelectionCheckboxes[0]->setChecked(true);
    mw.ui->playerHistorySelectionCheckboxes[1]->setChecked(true);

    QVERIFY2(mw.ui->plotPlayerHistory->graphCount() == 5, qPrintable(QString::fromUtf8(u8"incorrect graph count D")));
}

void FrontendTest::AboutButtonShallTriggerDialogAndOKShallClose()
{
    // Arrange
    MainWindow mw(this->DefaultPlayers, std::make_shared<MemoryRepository>(), false);

    // spy needed such that events actually happen
    QSignalSpy spyAboutButton(mw.ui->aboutButton, &QAbstractButton::pressed);

    // Act
    bool aboutMessageBoxFound = false;
    bool aboutMessageBoxHasOneButton = false;
    QTimer::singleShot(this->SingleShotInterval, this, [&]()
    {
        aboutMessageBoxFound = mw.aboutMessageBox != nullptr;
        aboutMessageBoxHasOneButton = mw.aboutMessageBox->buttons().count() == 1 && mw.aboutMessageBox->buttons().first() != nullptr;
        if(aboutMessageBoxFound && aboutMessageBoxHasOneButton)
        {
            QTest::mouseClick(mw.aboutMessageBox->buttons().first(), Qt::LeftButton);
        }
    });

    QTest::mouseClick(mw.ui->aboutButton, Qt::LeftButton);

    // Assert
    QVERIFY2(aboutMessageBoxFound, qPrintable(QString::fromUtf8(u8"aboutMessageBox not found")));
    QVERIFY2(aboutMessageBoxHasOneButton, qPrintable(QString::fromUtf8(u8"aboutMessageBox does not have exactly one button")));

    QVERIFY2(mw.aboutMessageBox == nullptr, qPrintable(QString::fromUtf8(u8"aboutMessageBox still reachable")));
}

void FrontendTest::MandatorySoloButtonShallBeEnabledAndTrigger() const
{
    // Arrange
    std::vector<std::string> players
    {
        u8"A",
        u8"B",
        u8"C",
        u8"D"
    };

    std::string dealer(u8"A");
    std::set<unsigned int> sitOutScheme {};

    MainWindow mw(this->DefaultPlayers, std::make_shared<MemoryRepository>(), false);

    QSignalSpy mandatorySoloButtonSpy(mw.ui->mandatorySoloButton, &QPushButton::clicked);
    QSignalSpy commitButtonSpy(mw.ui->commitButton, &QPushButton::clicked);
    QSignalSpy resetButtonSpy(mw.ui->resetButton, &QPushButton::clicked);

    mw.gameInfo.SetPlayers(players, dealer, sitOutScheme);
    mw.UpdateDisplay();

    // Act, Assert
    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString::fromUtf8(u8"Kein Bock")) == 0, qPrintable(QString::fromUtf8(u8"incorrect multiplier label at beginning")));
    QVERIFY2(mw.ui->mandatorySoloButton->isEnabled() == false, qPrintable(QString::fromUtf8(u8"wrong enabled state at beginning")));

    mw.ui->actuals[0]->setText(QString::fromUtf8(u8"-1"));
    mw.ui->actuals[1]->setText(QString::fromUtf8(u8"-1"));
    mw.ui->actuals[2]->setText(QString::fromUtf8(u8"1"));
    mw.ui->actuals[3]->setText(QString::fromUtf8(u8"1"));
    mw.ui->spinBox->setValue(1);
    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    mw.ui->actuals[0]->setText(QString::fromUtf8(u8"-1"));
    mw.ui->actuals[1]->setText(QString::fromUtf8(u8"-1"));
    mw.ui->actuals[2]->setText(QString::fromUtf8(u8"1"));
    mw.ui->actuals[3]->setText(QString::fromUtf8(u8"1"));
    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString::fromUtf8(u8"Einfachbock")) == 0, qPrintable(QString::fromUtf8(u8"incorrect multiplier label after first game")));
    QVERIFY2(mw.ui->mandatorySoloButton->isEnabled() == true, qPrintable(QString::fromUtf8(u8"wrong enabled state after first game")));

    QTest::mouseClick(mw.ui->mandatorySoloButton, Qt::LeftButton);

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString::fromUtf8(u8"Pflichtsolorunde")) == 0, qPrintable(QString::fromUtf8(u8"incorrect multiplier label after trigger")));
    QVERIFY2(mw.ui->mandatorySoloButton->isEnabled() == false, qPrintable(QString::fromUtf8(u8"wrong enabled state after trigger")));

    mw.ui->actuals[0]->setText(QString::fromUtf8(u8"1"));
    mw.ui->actuals[1]->setText(QString::fromUtf8(u8"1"));
    mw.ui->actuals[2]->setText(QString::fromUtf8(u8"-3"));
    mw.ui->actuals[3]->setText(QString::fromUtf8(u8"1"));
    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    QVERIFY2(mw.ui->scores[0]->text().compare(QString::fromUtf8(u8"-2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect score 0")));
    QVERIFY2(mw.ui->scores[1]->text().compare(QString::fromUtf8(u8"-2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect score 1")));
    QVERIFY2(mw.ui->scores[2]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect score 2")));
    QVERIFY2(mw.ui->scores[3]->text().compare(QString::fromUtf8(u8"4")) == 0, qPrintable(QString::fromUtf8(u8"incorrect score 3")));

    QTest::mouseClick(mw.ui->resetButton, Qt::LeftButton);
    QTest::mouseClick(mw.ui->resetButton, Qt::LeftButton);

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString::fromUtf8(u8"Einfachbock")) == 0, qPrintable(QString::fromUtf8(u8"incorrect multiplier label after reset")));
    QVERIFY2(mw.ui->mandatorySoloButton->isEnabled() == true, qPrintable(QString::fromUtf8(u8"wrong enabled state after reset")));
}

void FrontendTest::EveryOptionOfResetButtonShallBeDisplayed()
{
    // Arrange
    MainWindow mw(this->DefaultPlayers, std::make_shared<MemoryRepository>(), false);

    std::vector<std::string> players
    {
        u8"A",
        u8"B",
        u8"C",
        u8"D"
    };

    std::string dealer(u8"A");
    std::set<unsigned int> sitOutScheme { };

    mw.gameInfo.SetPlayers(players, dealer, sitOutScheme);
    mw.UpdateDisplay();

    // spy needed such that events actually happen
    QSignalSpy spyChangePlayersButton(mw.ui->changePlayersButton, &QAbstractButton::pressed);
    QSignalSpy spyCommitButton(mw.ui->commitButton, &QAbstractButton::pressed);
    QSignalSpy spyMandatorySoloButton(mw.ui->mandatorySoloButton, &QAbstractButton::pressed);

    // Act, Assert
    QVERIFY2(!mw.ui->resetButton->isEnabled(), qPrintable(QString::fromUtf8(u8"incorrect reset button state: none")));
    QVERIFY2(mw.ui->resetButton->text().compare(QString::fromUtf8(u8"Zurücksetzen")) == 0, qPrintable(QString::fromUtf8(u8"incorrect reset button label: none")));

    mw.ui->actuals[0]->setText(QString::fromUtf8(u8"2"));
    mw.ui->actuals[1]->setText(QString::fromUtf8(u8"2"));
    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    QVERIFY2(mw.ui->resetButton->isEnabled(), qPrintable(QString::fromUtf8(u8"incorrect reset button state: deal")));
    QVERIFY2(mw.ui->resetButton->text().compare(QString::fromUtf8(u8"Spiel zurücksetzen")) == 0, qPrintable(QString::fromUtf8(u8"incorrect reset button label: deal")));

    bool changePlayersDialogFound = false;
    QTimer::singleShot(this->SingleShotInterval, this, [&]()
    {
        changePlayersDialogFound = mw.playerSelection != nullptr;
        mw.playerSelection->dialogNames[1]->setText(QString::fromUtf8(u8"NewPlayer"));
        if(changePlayersDialogFound)
        {
            QTest::mouseClick(mw.playerSelection->dialogAcceptButton, Qt::LeftButton);
        }
    });

    QTest::mouseClick(mw.ui->changePlayersButton, Qt::LeftButton);

    QVERIFY2(changePlayersDialogFound, qPrintable(QString::fromUtf8(u8"changePlayersDialog not found")));

    QVERIFY2(mw.playerSelection == nullptr, qPrintable(QString::fromUtf8(u8"playerSelection still reachable")));

    QVERIFY2(mw.ui->names[1]->text().compare(QString::fromUtf8(u8"NewPlayer")) == 0, qPrintable(QString::fromUtf8(u8"incorrect name")));

    QVERIFY2(mw.ui->resetButton->isEnabled(), qPrintable(QString::fromUtf8(u8"incorrect reset button state: player choice")));
    QVERIFY2(mw.ui->resetButton->text().compare(QString::fromUtf8(u8"Spielerwahl zurücksetzen")) == 0, qPrintable(QString::fromUtf8(u8"incorrect reset button label: player choice")));

    QTest::mouseClick(mw.ui->mandatorySoloButton, Qt::LeftButton);

    QVERIFY2(mw.ui->resetButton->isEnabled(), qPrintable(QString::fromUtf8(u8"incorrect reset button state: mandatory solo")));
    QVERIFY2(mw.ui->resetButton->text().compare(QString::fromUtf8(u8"Pflichtsolo zurücksetzen")) == 0, qPrintable(QString::fromUtf8(u8"incorrect reset button label: mandatory solo")));
    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString::fromUtf8(u8"Pflichtsolorunde")) == 0, qPrintable(QString::fromUtf8(u8"incorrect multiplier label after trigger")));
}

void FrontendTest::SaveGameShallWorkWithPresetValueAndPersist() const
{
    // Arrange
    std::shared_ptr<MemoryRepository> memoryRepository = std::make_shared<MemoryRepository>();
    MainWindow mw(this->DefaultPlayers, memoryRepository, false);

    std::string identifier = u8"something";
    std::string dummy;

    mw.presetFilename = QString::fromUtf8(identifier);

    // spy needed such that events actually happen
    QSignalSpy spySaveAction(mw.ui->saveButton, &QAbstractButton::pressed);

    // Act
    QTest::mouseClick(mw.ui->saveButton, Qt::LeftButton);

    // Assert
    QVERIFY2(memoryRepository->TryGetByIdentifier(identifier, dummy), qPrintable(QString::fromUtf8(u8"no persisted data found")));
    QVERIFY2(mw.presetFilename.isEmpty(), qPrintable(QString::fromUtf8(u8"preset file name not cleared after logic has executed")));
}

void FrontendTest::LoadGameShallWorkWithPresetValueAndDisplayGame()
{
    // Arrange
    std::shared_ptr<MemoryRepository> memoryRepository = std::make_shared<MemoryRepository>();
    std::string identifier = u8"something";
    std::string content = u8R"foo({
    "dataVersion": "2",
    "data": [
        {
            "kind": "playersSet",
            "playerNames": [
                "A",
                "B",
                "C",
                "D"
            ],
            "dealerName": "A",
            "sitOutScheme": [],
            "previousDealerName": ""
        },
        {
            "kind": "deal",
            "players": 4,
            "numberOfEvents": 1,
            "changes": [
                {
                    "name": "A",
                    "diff": 1
                },
                {
                    "name": "B",
                    "diff": 1
                }
            ]
        },
        {
            "kind": "deal",
            "players": 4,
            "numberOfEvents": 2,
            "changes": [
                {
                    "name": "A",
                    "diff": 3
                },
                {
                    "name": "C",
                    "diff": 3
                }
            ]
        },
        {
            "kind": "deal",
            "players": 4,
            "numberOfEvents": 0,
            "changes": [
                {
                    "name": "C",
                    "diff": 2
                },
                {
                    "name": "D",
                    "diff": 2
                }
            ]
        }
    ]
})foo";
    memoryRepository->SetByIdentifier(identifier, content);

    MainWindow mw(this->DefaultPlayers, memoryRepository, false);

    mw.presetFilename = QString::fromUtf8(identifier);

    // spy needed such that events actually happen
    QSignalSpy spyLoadAction(mw.ui->loadButton, &QAbstractButton::pressed);

    // Act
    QTest::mouseClick(mw.ui->loadButton, Qt::LeftButton);

    // Assert
    QVERIFY2(mw.presetFilename.isEmpty(), qPrintable(QString::fromUtf8(u8"preset file name not cleared after logic has executed")));

    QVERIFY2(mw.ui->names[0]->text().compare(QString::fromUtf8(u8"A")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 0")));
    QVERIFY2(mw.ui->names[1]->text().compare(QString::fromUtf8(u8"B")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 1")));
    QVERIFY2(mw.ui->names[2]->text().compare(QString::fromUtf8(u8"C")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 2")));
    QVERIFY2(mw.ui->names[3]->text().compare(QString::fromUtf8(u8"D")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 3")));

    QVERIFY2(mw.ui->names[0]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 0")));
    QVERIFY2(mw.ui->names[1]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 1")));
    QVERIFY2(mw.ui->names[2]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 2")));
    QVERIFY2(mw.ui->names[3]->styleSheet().compare(ExpectedDealerNamesStyleSheet) == 0, qPrintable(QString::fromUtf8(u8"incorrect dealer state name 4")));

    QVERIFY2(mw.ui->actuals[0]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 0")));
    QVERIFY2(mw.ui->actuals[1]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 1")));
    QVERIFY2(mw.ui->actuals[2]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 2")));
    QVERIFY2(mw.ui->actuals[3]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 3")));

    QVERIFY2(mw.ui->scores[0]->text().compare(QString::fromUtf8(u8"-9")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 0")));
    QVERIFY2(mw.ui->scores[1]->text().compare(QString::fromUtf8(u8"-21")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 1")));
    QVERIFY2(mw.ui->scores[2]->text().compare(QString::fromUtf8(u8"21")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 2")));
    QVERIFY2(mw.ui->scores[3]->text().compare(QString::fromUtf8(u8"9")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 3")));

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString::fromUtf8(u8"Dreifachbock")) == 0, qPrintable(QString::fromUtf8(u8"current game multiplier label incorrect")));
    QVERIFY2(mw.ui->tripleMultiplier->text().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"triple multiplier label incorrect")));
    QVERIFY2(mw.ui->doubleMultiplier->text().compare(QString::fromUtf8(u8"1")) == 0, qPrintable(QString::fromUtf8(u8"double multiplier label incorrect")));
    QVERIFY2(mw.ui->singleMultiplier->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"single multiplier label incorrect")));
}

void FrontendTest::FocusOnActualShallTriggerAutofill() const
{
    // Arrange
    std::vector<std::string> players
    {
        u8"A",
        u8"B",
        u8"C",
        u8"D",
        u8"E",
        u8"F"
    };

    std::string dealer(u8"C");
    std::set<unsigned int> sitOutScheme
    {
        3
    };

    MainWindow mw(this->DefaultPlayers, std::make_shared<MemoryRepository>(), false);
    mw.gameInfo.SetPlayers(players, dealer, sitOutScheme);
    mw.UpdateDisplay();

    QApplication::setActiveWindow(&mw);

    // Act 1
    mw.ui->actuals[0]->setText(QString::fromUtf8(u8"2"));
    QTest::mouseClick(mw.ui->actuals[3], Qt::LeftButton);
    QTest::qWait(this->ShortInterval);

    // Assert 1
    QVERIFY2(mw.ui->actuals[0]->selectedText().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect selected text actuals 0")));
    QVERIFY2(mw.ui->actuals[3]->selectedText().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect selected text actuals 3")));

    QVERIFY2(mw.ui->actuals[0]->text().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect text actuals 0")));
    QVERIFY2(mw.ui->actuals[1]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect text actuals 1")));
    QVERIFY2(mw.ui->actuals[2]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect text actuals 2")));
    QVERIFY2(mw.ui->actuals[3]->text().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect text actuals 3")));
    QVERIFY2(mw.ui->actuals[4]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect text actuals 4")));
    QVERIFY2(mw.ui->actuals[5]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect text actuals 5")));

    // Reset
    for(unsigned int i = 0; i < players.size(); ++i)
    {
        mw.ui->actuals[i]->clear();
    }
    mw.ui->actuals[0]->setFocus();

    // Act 2
    mw.ui->actuals[0]->setText(QString::fromUtf8(u8"3"));
    QTest::mouseClick(mw.ui->actuals[3], Qt::LeftButton);
    QTest::mouseClick(mw.ui->actuals[4], Qt::LeftButton);

    // Assert 2
    QVERIFY2(mw.ui->actuals[0]->text().compare(QString::fromUtf8(u8"3")) == 0, qPrintable(QString::fromUtf8(u8"incorrect text actuals 0")));
    QVERIFY2(mw.ui->actuals[1]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect text actuals 1")));
    QVERIFY2(mw.ui->actuals[2]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect text actuals 2")));
    QVERIFY2(mw.ui->actuals[3]->text().compare(QString::fromUtf8(u8"3")) == 0, qPrintable(QString::fromUtf8(u8"incorrect text actuals 3")));
    QVERIFY2(mw.ui->actuals[4]->text().compare(QString::fromUtf8(u8"3")) == 0, qPrintable(QString::fromUtf8(u8"incorrect text actuals 4")));
    QVERIFY2(mw.ui->actuals[5]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect text actuals 5")));

    // Reset
    for(unsigned int i = 0; i < players.size(); ++i)
    {
        mw.ui->actuals[i]->clear();
    }
    mw.ui->actuals[0]->setFocus();

    // Act 3
    mw.ui->actuals[0]->setText(QString::fromUtf8(u8"4"));
    mw.ui->actuals[4]->setText(QString::fromUtf8(u8"5"));
    QTest::mouseClick(mw.ui->actuals[1], Qt::LeftButton);

    // Assert 3
    QVERIFY2(mw.ui->actuals[0]->text().compare(QString::fromUtf8(u8"4")) == 0, qPrintable(QString::fromUtf8(u8"incorrect text actuals 0")));
    QVERIFY2(mw.ui->actuals[1]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect text actuals 1")));
    QVERIFY2(mw.ui->actuals[2]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect text actuals 2")));
    QVERIFY2(mw.ui->actuals[3]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect text actuals 3")));
    QVERIFY2(mw.ui->actuals[4]->text().compare(QString::fromUtf8(u8"5")) == 0, qPrintable(QString::fromUtf8(u8"incorrect text actuals 4")));
    QVERIFY2(mw.ui->actuals[5]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect text actuals 5")));

    // Reset
    for(unsigned int i = 0; i < players.size(); ++i)
    {
        mw.ui->actuals[i]->clear();
    }
    mw.ui->actuals[0]->setFocus();

    // Act 4
    mw.ui->actuals[0]->setText(QString::fromUtf8(u8"6"));
    QTest::keyClick(&mw, Qt::Key_Tab);

    // Assert 4
    QVERIFY2(mw.ui->actuals[1]->hasFocus(), qPrintable(QString::fromUtf8(u8"actuals 1 does not have focus")));

    QVERIFY2(mw.ui->actuals[0]->text().compare(QString::fromUtf8(u8"6")) == 0, qPrintable(QString::fromUtf8(u8"incorrect text actuals 0")));
    QVERIFY2(mw.ui->actuals[1]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect text actuals 1")));
    QVERIFY2(mw.ui->actuals[2]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect text actuals 2")));
    QVERIFY2(mw.ui->actuals[3]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect text actuals 3")));
    QVERIFY2(mw.ui->actuals[4]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect text actuals 4")));
    QVERIFY2(mw.ui->actuals[5]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect text actuals 5")));
}

void FrontendTest::ReturnKeyShallCommitGame() const
{
    // Arrange
    std::vector<std::string> players
    {
        u8"A",
        u8"B",
        u8"C",
        u8"D",
        u8"E",
        u8"F"
    };

    std::string dealer(u8"C");
    std::set<unsigned int> sitOutScheme
    {
        3
    };

    MainWindow mw(this->DefaultPlayers, std::make_shared<MemoryRepository>(), false);

    QSignalSpy commitButtonSpy(mw.ui->commitButton, &QPushButton::clicked);

    mw.gameInfo.SetPlayers(players, dealer, sitOutScheme);
    mw.UpdateDisplay();

    // Act
    mw.ui->actuals[0]->setText(QString::fromUtf8(u8"2"));
    mw.ui->actuals[3]->setText(QString::fromUtf8(u8"2"));
    QTest::keyClick(mw.ui->actuals[3], Qt::Key_Return);

    // Assert
    QVERIFY2(mw.ui->names[0]->text().compare(QString::fromUtf8(u8"A")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 0")));
    QVERIFY2(mw.ui->names[1]->text().compare(QString::fromUtf8(u8"B")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 1")));
    QVERIFY2(mw.ui->names[2]->text().compare(QString::fromUtf8(u8"C")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 2")));
    QVERIFY2(mw.ui->names[3]->text().compare(QString::fromUtf8(u8"D")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 3")));
    QVERIFY2(mw.ui->names[4]->text().compare(QString::fromUtf8(u8"E")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 4")));
    QVERIFY2(mw.ui->names[5]->text().compare(QString::fromUtf8(u8"F")) == 0, qPrintable(QString::fromUtf8(u8"incorrect player name 5")));

    QVERIFY2(mw.ui->actuals[0]->isEnabled() == false, qPrintable(QString::fromUtf8(u8"incorrect state actuals 0")));
    QVERIFY2(mw.ui->actuals[1]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 1")));
    QVERIFY2(mw.ui->actuals[2]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 2")));
    QVERIFY2(mw.ui->actuals[3]->isEnabled() == false, qPrintable(QString::fromUtf8(u8"incorrect state actuals 3")));
    QVERIFY2(mw.ui->actuals[4]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 4")));
    QVERIFY2(mw.ui->actuals[5]->isEnabled() == true, qPrintable(QString::fromUtf8(u8"incorrect state actuals 5")));

    QVERIFY2(mw.ui->scores[0]->text().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 0")));
    QVERIFY2(mw.ui->scores[1]->text().compare(QString::fromUtf8(u8"-2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 1")));
    QVERIFY2(mw.ui->scores[2]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 2")));
    QVERIFY2(mw.ui->scores[3]->text().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 3")));
    QVERIFY2(mw.ui->scores[4]->text().compare(QString::fromUtf8(u8"-2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 4")));
    QVERIFY2(mw.ui->scores[5]->text().compare(QString::fromUtf8(u8"0")) == 0, qPrintable(QString::fromUtf8(u8"incorrect scores 5")));

    QVERIFY2(mw.ui->lastGames[0]->text().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 0")));
    QVERIFY2(mw.ui->lastGames[1]->text().compare(QString::fromUtf8(u8"-2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 1")));
    QVERIFY2(mw.ui->lastGames[2]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 2")));
    QVERIFY2(mw.ui->lastGames[3]->text().compare(QString::fromUtf8(u8"2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 3")));
    QVERIFY2(mw.ui->lastGames[4]->text().compare(QString::fromUtf8(u8"-2")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 4")));
    QVERIFY2(mw.ui->lastGames[5]->text().compare(QString::fromUtf8(u8"")) == 0, qPrintable(QString::fromUtf8(u8"incorrect last games 5")));

    QVERIFY2(mw.ui->actuals[0]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 0 not empty")));
    QVERIFY2(mw.ui->actuals[1]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 1 not empty")));
    QVERIFY2(mw.ui->actuals[2]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 2 not empty")));
    QVERIFY2(mw.ui->actuals[3]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 3 not empty")));
    QVERIFY2(mw.ui->actuals[4]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 4 not empty")));
    QVERIFY2(mw.ui->actuals[5]->text().isEmpty(), qPrintable(QString::fromUtf8(u8"actuals 5 not empty")));
}

#endif // _USE_LONG_TEST

QTEST_MAIN(FrontendTest)

#include "tst_mainwindow.moc"
