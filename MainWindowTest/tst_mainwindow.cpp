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

#include <QtTest>
#include <QTest>

#include "../Frontend/mainwindow.h"
#include "../Frontend/mainwindow_ui.h"

class FrontendTest : public QObject
{
    Q_OBJECT

private:
    const QString ExpectedStandardNamesStyleSheet = "QLabel { }";
    const QString ExpectedDealerNamesStyleSheet = "QLabel { border: 3px solid orange ; border-radius : 6px }";

public:
    FrontendTest();
    ~FrontendTest();

private slots:
    void ConstructionShallWorkCompletely();
#ifdef _USE_LONG_TEST
    void SetDataShallBeDisplayed();
    void OneCommittedGameShallBeDisplayed();
    void TwoCommittedGamesShallBeDisplayed();
    void TwoCommittedAndTwoPoppedGameShallBeDisplayed();
    void AllLevelsOfMultipliersShallCorrectlyBeDisplayed();
    void StatisticsShallCorrectlyBeDisplayed();
    void ScoreHistoryPlotShallWorkCorrectly();
    void AboutButtonShallTriggerDialogAndOKShallClose();
    void MandatorySoloButtonShallBeEnabledAndTrigger();
#endif
};

FrontendTest::FrontendTest()
{
}

FrontendTest::~FrontendTest()
{
}

void FrontendTest::ConstructionShallWorkCompletely()
{
    try
    {
        // Act
        MainWindow mw(8u, false);

        // Assert
        QVERIFY2(mw.ui->centralwidget, "not created central widget");
        QVERIFY2(mw.ui->leftVerticalLayout, "not created vertical layout");

        QVERIFY2(mw.ui->topMenu, "not created top menu");
        QVERIFY2(mw.ui->topMenuLayout, "not created top menu layout");
        QVERIFY2(mw.ui->changePlayersButton, "not created change players button");
        QVERIFY2(mw.ui->loadButton, "not created load button");
        QVERIFY2(mw.ui->saveButton, "not created save button");
        QVERIFY2(mw.ui->mandatorySoloButton, "not created mandatory solo button");
        QVERIFY2(mw.ui->aboutButton, "not created about button");
        QVERIFY2(mw.ui->topMenuSpacer, "not created top menu spacer");

        QVERIFY2(mw.ui->namesLayout, "not created names layout");
        QVERIFY2(mw.ui->namenLabel, "not created namen label");
        QVERIFY2(mw.ui->names.size() > 0, "there must be name labels");
        for(size_t i = 0; i < mw.ui->names.size(); ++i)
        {
            QVERIFY2(mw.ui->names[i], "name label not created");
        }

        QVERIFY2(mw.ui->letztesLabel, "not created letztes label");
        QVERIFY2(mw.ui->lastGames.size() > 0, "there must be last games labels");
        QVERIFY2(mw.ui->lastGames.size() == mw.ui->names.size(), "sizes do not match: lastGames, names");
        for(size_t i = 0; i < mw.ui->lastGames.size(); ++i)
        {
            QVERIFY2(mw.ui->lastGames[i], "last game label not created");
        }

        QVERIFY2(mw.ui->aktuellesLabel, "not created aktuelles label");
        QVERIFY2(mw.ui->actuals.size() > 0, "there must be actuals inputs");
        QVERIFY2(mw.ui->actuals.size() == mw.ui->names.size(), "sizes do not match: actuals, names");
        for(size_t i = 0; i < mw.ui->actuals.size(); ++i)
        {
            QVERIFY2(mw.ui->actuals[i], "actual input not created");
        }

        QVERIFY2(mw.ui->controlWidget, "not created control widget");
        QVERIFY2(mw.ui->horizontalLayout, "not created horizontal layout");
        QVERIFY2(mw.ui->bockereignisseLabel, "not created bockereignisse label");
        QVERIFY2(mw.ui->spinBox, "not created spin box");
        QVERIFY2(mw.ui->commitButton, "not created commit button");
        QVERIFY2(mw.ui->resetButton, "not created reset button");
        QVERIFY2(mw.ui->controlSpacer0, "not created control spacer 0");
        QVERIFY2(mw.ui->controlSpacer1, "not created control spacer 1");

        QVERIFY2(mw.ui->spielstandLabel, "not created spielstand label");
        QVERIFY2(mw.ui->scores.size() > 0, "there must be scores labels");
        QVERIFY2(mw.ui->scores.size() == mw.ui->names.size(), "sizes do not match: scores, names");
        for(size_t i = 0; i < mw.ui->scores.size(); ++i)
        {
            QVERIFY2(mw.ui->scores[i], "score label not created");
        }

        QVERIFY2(mw.ui->zuZahlenLabel, "not created zu zahlen label");
        QVERIFY2(mw.ui->cashs.size() > 0, "there must be scores labels");
        QVERIFY2(mw.ui->cashs.size() == mw.ui->names.size(), "sizes do not match: cashs, names");
        for(size_t i = 0; i < mw.ui->cashs.size(); ++i)
        {
            QVERIFY2(mw.ui->cashs[i], "cash label not created");
        }

        QVERIFY2(mw.ui->kassenstandLabel, "not created kassenstand label");
        QVERIFY2(mw.ui->totalCash, "not created total cash label");

        QVERIFY2(mw.ui->statisticsBox, "not created statistics box");
        QVERIFY2(mw.ui->statisticsGridLayout, "not created grid layout");

        QVERIFY2(mw.ui->gewonnenLabel, "not created gewonnen label");
        QVERIFY2(mw.ui->verlorenLabel, "not created verloren label");
        QVERIFY2(mw.ui->anzahlSpieleLabel, "not created anzahl spiele label");
        QVERIFY2(mw.ui->soloGewonnenLabel, "not created solo gewonnen label");
        QVERIFY2(mw.ui->soloVerlorenLabel, "not created solo verloren label");
        QVERIFY2(mw.ui->soloPunkteLabel, "not created punkte label");
        QVERIFY2(mw.ui->groessterGewinnLabel, "not created groesster gewinn label");
        QVERIFY2(mw.ui->groessterVerlustLabel, "not created groesster verlust label");
        QVERIFY2(mw.ui->ohneBockLabel, "not created ohne bock label");

        QVERIFY2(mw.ui->statisticNames.size() > 0, "there must be statisticNames labels");
        QVERIFY2(mw.ui->statisticNames.size() == mw.ui->names.size(), "sizes do not match: statisticNames, names");
        for(size_t i = 0; i < mw.ui->statisticNames.size(); ++i)
        {
            QVERIFY2(mw.ui->statisticNames[i], "statistic name label not created");
        }

        QVERIFY2(mw.ui->numberWons.size() > 0, "there must be numberWons labels");
        QVERIFY2(mw.ui->numberWons.size() == mw.ui->names.size(), "sizes do not match: numberWons, names");
        for(size_t i = 0; i < mw.ui->numberWons.size(); ++i)
        {
            QVERIFY2(mw.ui->numberWons[i], "number won label not created");
        }

        QVERIFY2(mw.ui->numberLosts.size() > 0, "there must be numberLosts labels");
        QVERIFY2(mw.ui->numberLosts.size() == mw.ui->names.size(), "sizes do not match: numberLosts, names");
        for(size_t i = 0; i < mw.ui->numberLosts.size(); ++i)
        {
            QVERIFY2(mw.ui->numberLosts[i], "number lost label not created");
        }

        QVERIFY2(mw.ui->numberPlayeds.size() > 0, "there must be numberPlayeds labels");
        QVERIFY2(mw.ui->numberPlayeds.size() == mw.ui->names.size(), "sizes do not match: numberPlayeds, names");
        for(size_t i = 0; i < mw.ui->numberPlayeds.size(); ++i)
        {
            QVERIFY2(mw.ui->numberPlayeds[i], "number playeds label not created");
        }

        QVERIFY2(mw.ui->numberSoloWons.size() > 0, "there must be numberSoloWons labels");
        QVERIFY2(mw.ui->numberSoloWons.size() == mw.ui->names.size(), "sizes do not match: numberSoloWons, names");
        for(size_t i = 0; i < mw.ui->numberSoloWons.size(); ++i)
        {
            QVERIFY2(mw.ui->numberSoloWons[i], "solo wons label not created");
        }

        QVERIFY2(mw.ui->numberSoloLosts.size() > 0, "there must be numberSoloLosts labels");
        QVERIFY2(mw.ui->numberSoloLosts.size() == mw.ui->names.size(), "sizes do not match: numberSoloLosts, names");
        for(size_t i = 0; i < mw.ui->numberSoloLosts.size(); ++i)
        {
            QVERIFY2(mw.ui->numberSoloLosts[i], "solo losts label not created");
        }

        QVERIFY2(mw.ui->pointsSolos.size() > 0, "there must be pointsSolos labels");
        QVERIFY2(mw.ui->pointsSolos.size() == mw.ui->names.size(), "sizes do not match: pointsSolos, names");
        for(size_t i = 0; i < mw.ui->pointsSolos.size(); ++i)
        {
            QVERIFY2(mw.ui->pointsSolos[i], "points solos label not created");
        }

        QVERIFY2(mw.ui->maxSingleWins.size() > 0, "there must be maxSingleWins labels");
        QVERIFY2(mw.ui->maxSingleWins.size() == mw.ui->names.size(), "sizes do not match: maxSingleWins, names");
        for(size_t i = 0; i < mw.ui->maxSingleWins.size(); ++i)
        {
            QVERIFY2(mw.ui->maxSingleWins[i], "max single wins label not created");
        }

        QVERIFY2(mw.ui->maxSingleLosss.size() > 0, "there must be maxSingleLosss labels");
        QVERIFY2(mw.ui->maxSingleLosss.size() == mw.ui->names.size(), "sizes do not match: maxSingleLosss, names");
        for(size_t i = 0; i < mw.ui->maxSingleLosss.size(); ++i)
        {
            QVERIFY2(mw.ui->maxSingleLosss[i], "max single losss label not created");
        }

        QVERIFY2(mw.ui->unmultipliedScores.size() > 0, "there must be unmultipliedScores labels");
        QVERIFY2(mw.ui->unmultipliedScores.size() == mw.ui->names.size(), "sizes do not match: unmultipliedScores, names");
        for(size_t i = 0; i < mw.ui->unmultipliedScores.size(); ++i)
        {
            QVERIFY2(mw.ui->unmultipliedScores[i], "unmultiplied scores label not created");
        }

        QVERIFY2(mw.ui->currentGameMultiplier, "current game multiplier not created");
        QVERIFY2(mw.ui->multiplierPreviewWidget, "multiplier preview widget not created");
        QVERIFY2(mw.ui->multiplierPreviewGridLayout, "multiplier preview grid layout not created");
        QVERIFY2(mw.ui->dreifachbockLabel, "dreifachbock label not created");
        QVERIFY2(mw.ui->doppelbockLabel, "doppelbock label not created");
        QVERIFY2(mw.ui->einfachbockLabel, "einfachbock label not created");
        QVERIFY2(mw.ui->tripleMultiplier, "triple multiplier not created");
        QVERIFY2(mw.ui->doubleMultiplier, "double multiplier not created");
        QVERIFY2(mw.ui->singleMultiplier, "single multiplier not created");

        QVERIFY2(mw.ui->playerHistorySelectionWidget, "not created player history selection widget");
        QVERIFY2(mw.ui->playerHistoryGridLayout, "not created player history grid layout");

        QVERIFY2(mw.ui->playerHistorySelectionLayouts.size() > 0, "there must be playerHistorySelectionLayouts labels");
        QVERIFY2(mw.ui->playerHistorySelectionLayouts.size() == mw.ui->names.size(), "sizes do not match: playerHistorySelectionLayouts, names");
        for(size_t i = 0; i < mw.ui->playerHistorySelectionLayouts.size(); ++i)
        {
            QVERIFY2(mw.ui->playerHistorySelectionLayouts[i], "player history selection layout not created");
        }

        QVERIFY2(mw.ui->playerHistorySelectionCheckboxes.size() > 0, "there must be playerHistorySelectionCheckboxes labels");
        QVERIFY2(mw.ui->playerHistorySelectionCheckboxes.size() == mw.ui->names.size(), "sizes do not match: playerHistorySelectionCheckboxes, names");
        for(size_t i = 0; i < mw.ui->playerHistorySelectionCheckboxes.size(); ++i)
        {
            QVERIFY2(mw.ui->playerHistorySelectionCheckboxes[i], "player history selection checkbox not created");
        }

        QVERIFY2(mw.ui->playerHistorySelectionLabels.size() > 0, "there must be playerHistorySelectionLabels labels");
        QVERIFY2(mw.ui->playerHistorySelectionLabels.size() == mw.ui->names.size(), "sizes do not match: playerHistorySelectionLabels, names");
        for(size_t i = 0; i < mw.ui->playerHistorySelectionLabels.size(); ++i)
        {
            QVERIFY2(mw.ui->playerHistorySelectionLabels[i], "player history selection label not created");
        }

        QVERIFY2(mw.ui->plotPlayerHistory, "not created player history plot");

        QVERIFY2(mw.StandardNamesStylesheet.compare(ExpectedStandardNamesStyleSheet) == 0, "unexpected content of standard names style sheet");
        QVERIFY2(mw.DealerNamesStylesheet.compare(ExpectedDealerNamesStyleSheet) == 0, "unexpected content of dealer names style sheet");
    }
    catch (std::exception & ex)
    {
        QFAIL(ex.what());
    }
    catch (...)
    {
        QFAIL("unknown exception");
    }
}

#ifdef _USE_LONG_TEST

void FrontendTest::SetDataShallBeDisplayed()
{
    // Arrange
    std::vector<std::wstring> players
    {
        L"A",
        L"B",
        L"C",
        L"D",
        L"E",
        L"F"
    };

    std::wstring dealer(L"C");
    std::set<unsigned int> sitOutScheme
    {
        3
    };

    MainWindow mw(8u, false);

    // Act
    mw.gameInfo.SetPlayers(players, dealer, sitOutScheme);
    mw.UpdateDisplay();

    // Assert
    QVERIFY2(mw.ui->names[0]->text().compare(QString("A")) == 0, "incorrect player name 0");
    QVERIFY2(mw.ui->names[1]->text().compare(QString("B")) == 0, "incorrect player name 1");
    QVERIFY2(mw.ui->names[2]->text().compare(QString("C")) == 0, "incorrect player name 2");
    QVERIFY2(mw.ui->names[3]->text().compare(QString("D")) == 0, "incorrect player name 3");
    QVERIFY2(mw.ui->names[4]->text().compare(QString("E")) == 0, "incorrect player name 4");
    QVERIFY2(mw.ui->names[5]->text().compare(QString("F")) == 0, "incorrect player name 5");

    QVERIFY2(mw.ui->names[0]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, "incorrect dealer state name 0");
    QVERIFY2(mw.ui->names[1]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, "incorrect dealer state name 1");
    QVERIFY2(mw.ui->names[2]->styleSheet().compare(ExpectedDealerNamesStyleSheet) == 0, "incorrect dealer state name 2");
    QVERIFY2(mw.ui->names[3]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, "incorrect dealer state name 3");
    QVERIFY2(mw.ui->names[4]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, "incorrect dealer state name 4");
    QVERIFY2(mw.ui->names[5]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, "incorrect dealer state name 5");

    QVERIFY2(mw.ui->actuals[0]->isEnabled() == true, "incorrect state actuals 0");
    QVERIFY2(mw.ui->actuals[1]->isEnabled() == true, "incorrect state actuals 1");
    QVERIFY2(mw.ui->actuals[2]->isEnabled() == false, "incorrect state actuals 2");
    QVERIFY2(mw.ui->actuals[3]->isEnabled() == true, "incorrect state actuals 3");
    QVERIFY2(mw.ui->actuals[4]->isEnabled() == true, "incorrect state actuals 4");
    QVERIFY2(mw.ui->actuals[5]->isEnabled() == false, "incorrect state actuals 5");

    QVERIFY2(mw.ui->scores[0]->text().compare(QString("0")) == 0, "incorrect scores 0");
    QVERIFY2(mw.ui->scores[1]->text().compare(QString("0")) == 0, "incorrect scores 1");
    QVERIFY2(mw.ui->scores[2]->text().compare(QString("0")) == 0, "incorrect scores 2");
    QVERIFY2(mw.ui->scores[3]->text().compare(QString("0")) == 0, "incorrect scores 3");
    QVERIFY2(mw.ui->scores[4]->text().compare(QString("0")) == 0, "incorrect scores 4");
    QVERIFY2(mw.ui->scores[5]->text().compare(QString("0")) == 0, "incorrect scores 5");

    QVERIFY2(mw.ui->actuals[0]->text().isEmpty(), "actuals 0 not empty");
    QVERIFY2(mw.ui->actuals[1]->text().isEmpty(), "actuals 1 not empty");
    QVERIFY2(mw.ui->actuals[2]->text().isEmpty(), "actuals 2 not empty");
    QVERIFY2(mw.ui->actuals[3]->text().isEmpty(), "actuals 3 not empty");
    QVERIFY2(mw.ui->actuals[4]->text().isEmpty(), "actuals 4 not empty");
    QVERIFY2(mw.ui->actuals[5]->text().isEmpty(), "actuals 5 not empty");

    QVERIFY2(mw.ui->spinBox->value() == 0, "events spinbox not set to zero");

    QVERIFY2(mw.ui->cashs[0]->text().compare(QString("0,00")) == 0, "incorrect cashs 0");
    QVERIFY2(mw.ui->cashs[1]->text().compare(QString("0,00")) == 0, "incorrect cashs 1");
    QVERIFY2(mw.ui->cashs[2]->text().compare(QString("0,00")) == 0, "incorrect cashs 2");
    QVERIFY2(mw.ui->cashs[3]->text().compare(QString("0,00")) == 0, "incorrect cashs 3");
    QVERIFY2(mw.ui->cashs[4]->text().compare(QString("0,00")) == 0, "incorrect cashs 4");
    QVERIFY2(mw.ui->cashs[5]->text().compare(QString("0,00")) == 0, "incorrect cashs 5");

    QVERIFY2(mw.ui->totalCash->text().compare(QString("0,00 (inkl. 0,00 pro Abwesender)")) == 0, "incorrect totalCash");

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString("Kein Bock")) == 0, "current game multiplier label incorrect");
    QVERIFY2(mw.ui->tripleMultiplier->text().compare(QString("0")) == 0, "triple multiplier label incorrect");
    QVERIFY2(mw.ui->doubleMultiplier->text().compare(QString("0")) == 0, "double multiplier label incorrect");
    QVERIFY2(mw.ui->singleMultiplier->text().compare(QString("0")) == 0, "single multiplier label incorrect");
}

void FrontendTest::OneCommittedGameShallBeDisplayed()
{
    // Arrange
    std::vector<std::wstring> players
    {
        L"A",
        L"B",
        L"C",
        L"D",
        L"E",
        L"F"
    };

    std::wstring dealer(L"C");
    std::set<unsigned int> sitOutScheme
    {
        3
    };

    MainWindow mw(8u, false);

    QSignalSpy commitButtonSpy(mw.ui->commitButton, &QPushButton::clicked);

    mw.gameInfo.SetPlayers(players, dealer, sitOutScheme);
    mw.UpdateDisplay();

    // Act
    mw.ui->actuals[0]->setText(QString("2"));
    mw.ui->actuals[3]->setText(QString("2"));
    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    // Assert
    QVERIFY2(mw.ui->names[0]->text().compare(QString("A")) == 0, "incorrect player name 0");
    QVERIFY2(mw.ui->names[1]->text().compare(QString("B")) == 0, "incorrect player name 1");
    QVERIFY2(mw.ui->names[2]->text().compare(QString("C")) == 0, "incorrect player name 2");
    QVERIFY2(mw.ui->names[3]->text().compare(QString("D")) == 0, "incorrect player name 3");
    QVERIFY2(mw.ui->names[4]->text().compare(QString("E")) == 0, "incorrect player name 4");
    QVERIFY2(mw.ui->names[5]->text().compare(QString("F")) == 0, "incorrect player name 5");

    QVERIFY2(mw.ui->names[0]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, "incorrect dealer state name 0");
    QVERIFY2(mw.ui->names[1]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, "incorrect dealer state name 1");
    QVERIFY2(mw.ui->names[2]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, "incorrect dealer state name 2");
    QVERIFY2(mw.ui->names[3]->styleSheet().compare(ExpectedDealerNamesStyleSheet) == 0, "incorrect dealer state name 3");
    QVERIFY2(mw.ui->names[4]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, "incorrect dealer state name 4");
    QVERIFY2(mw.ui->names[5]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, "incorrect dealer state name 5");

    QVERIFY2(mw.ui->actuals[0]->isEnabled() == false, "incorrect state actuals 0");
    QVERIFY2(mw.ui->actuals[1]->isEnabled() == true, "incorrect state actuals 1");
    QVERIFY2(mw.ui->actuals[2]->isEnabled() == true, "incorrect state actuals 2");
    QVERIFY2(mw.ui->actuals[3]->isEnabled() == false, "incorrect state actuals 3");
    QVERIFY2(mw.ui->actuals[4]->isEnabled() == true, "incorrect state actuals 4");
    QVERIFY2(mw.ui->actuals[5]->isEnabled() == true, "incorrect state actuals 5");

    QVERIFY2(mw.ui->scores[0]->text().compare(QString("2")) == 0, "incorrect scores 0");
    QVERIFY2(mw.ui->scores[1]->text().compare(QString("-2")) == 0, "incorrect scores 1");
    QVERIFY2(mw.ui->scores[2]->text().compare(QString("0")) == 0, "incorrect scores 2");
    QVERIFY2(mw.ui->scores[3]->text().compare(QString("2")) == 0, "incorrect scores 3");
    QVERIFY2(mw.ui->scores[4]->text().compare(QString("-2")) == 0, "incorrect scores 4");
    QVERIFY2(mw.ui->scores[5]->text().compare(QString("0")) == 0, "incorrect scores 5");

    QVERIFY2(mw.ui->lastGames[0]->text().compare(QString("2")) == 0, "incorrect last games 0");
    QVERIFY2(mw.ui->lastGames[1]->text().compare(QString("-2")) == 0, "incorrect last games 1");
    QVERIFY2(mw.ui->lastGames[2]->text().compare(QString("")) == 0, "incorrect last games 2");
    QVERIFY2(mw.ui->lastGames[3]->text().compare(QString("2")) == 0, "incorrect last games 3");
    QVERIFY2(mw.ui->lastGames[4]->text().compare(QString("-2")) == 0, "incorrect last games 4");
    QVERIFY2(mw.ui->lastGames[5]->text().compare(QString("")) == 0, "incorrect last games 5");

    QVERIFY2(mw.ui->actuals[0]->text().isEmpty(), "actuals 0 not empty");
    QVERIFY2(mw.ui->actuals[1]->text().isEmpty(), "actuals 1 not empty");
    QVERIFY2(mw.ui->actuals[2]->text().isEmpty(), "actuals 2 not empty");
    QVERIFY2(mw.ui->actuals[3]->text().isEmpty(), "actuals 3 not empty");
    QVERIFY2(mw.ui->actuals[4]->text().isEmpty(), "actuals 4 not empty");
    QVERIFY2(mw.ui->actuals[5]->text().isEmpty(), "actuals 5 not empty");

    QVERIFY2(mw.ui->spinBox->value() == 0, "events spinbox not set to zero");

    QVERIFY2(mw.ui->cashs[0]->text().compare(QString("0,00")) == 0, "incorrect cashs 0");
    QVERIFY2(mw.ui->cashs[1]->text().compare(QString("0,02")) == 0, "incorrect cashs 1");
    QVERIFY2(mw.ui->cashs[2]->text().compare(QString("0,01")) == 0, "incorrect cashs 2");
    QVERIFY2(mw.ui->cashs[3]->text().compare(QString("0,00")) == 0, "incorrect cashs 3");
    QVERIFY2(mw.ui->cashs[4]->text().compare(QString("0,02")) == 0, "incorrect cashs 4");
    QVERIFY2(mw.ui->cashs[5]->text().compare(QString("0,01")) == 0, "incorrect cashs 5");

    QVERIFY2(mw.ui->totalCash->text().compare(QString("0,08 (inkl. 0,01 pro Abwesender)")) == 0, "incorrect totalCash");

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString("Kein Bock")) == 0, "current game multiplier label incorrect");
    QVERIFY2(mw.ui->tripleMultiplier->text().compare(QString("0")) == 0, "triple multiplier label incorrect");
    QVERIFY2(mw.ui->doubleMultiplier->text().compare(QString("0")) == 0, "double multiplier label incorrect");
    QVERIFY2(mw.ui->singleMultiplier->text().compare(QString("0")) == 0, "single multiplier label incorrect");
}

void FrontendTest::TwoCommittedGamesShallBeDisplayed()
{
    // Arrange
    std::vector<std::wstring> players
    {
        L"A",
        L"B",
        L"C",
        L"D",
        L"E",
        L"F"
    };

    std::wstring dealer(L"C");
    std::set<unsigned int> sitOutScheme
    {
        3
    };

    MainWindow mw(8u, false);

    QSignalSpy commitButtonSpy(mw.ui->commitButton, &QPushButton::clicked);

    mw.gameInfo.SetPlayers(players, dealer, sitOutScheme);
    mw.UpdateDisplay();

    // Act
    mw.ui->actuals[0]->setText(QString("2"));
    mw.ui->actuals[3]->setText(QString("2"));
    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    mw.ui->actuals[2]->setText(QString("-3"));
    mw.ui->actuals[4]->setText(QString("-3"));
    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    // Assert
    QVERIFY2(mw.ui->names[0]->text().compare(QString("A")) == 0, "incorrect player name 0");
    QVERIFY2(mw.ui->names[1]->text().compare(QString("B")) == 0, "incorrect player name 1");
    QVERIFY2(mw.ui->names[2]->text().compare(QString("C")) == 0, "incorrect player name 2");
    QVERIFY2(mw.ui->names[3]->text().compare(QString("D")) == 0, "incorrect player name 3");
    QVERIFY2(mw.ui->names[4]->text().compare(QString("E")) == 0, "incorrect player name 4");
    QVERIFY2(mw.ui->names[5]->text().compare(QString("F")) == 0, "incorrect player name 5");

    QVERIFY2(mw.ui->names[0]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, "incorrect dealer state name 0");
    QVERIFY2(mw.ui->names[1]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, "incorrect dealer state name 1");
    QVERIFY2(mw.ui->names[2]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, "incorrect dealer state name 2");
    QVERIFY2(mw.ui->names[3]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, "incorrect dealer state name 3");
    QVERIFY2(mw.ui->names[4]->styleSheet().compare(ExpectedDealerNamesStyleSheet) == 0, "incorrect dealer state name 4");
    QVERIFY2(mw.ui->names[5]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, "incorrect dealer state name 5");

    QVERIFY2(mw.ui->actuals[0]->isEnabled() == true, "incorrect state actuals 0");
    QVERIFY2(mw.ui->actuals[1]->isEnabled() == false, "incorrect state actuals 1");
    QVERIFY2(mw.ui->actuals[2]->isEnabled() == true, "incorrect state actuals 2");
    QVERIFY2(mw.ui->actuals[3]->isEnabled() == true, "incorrect state actuals 3");
    QVERIFY2(mw.ui->actuals[4]->isEnabled() == false, "incorrect state actuals 4");
    QVERIFY2(mw.ui->actuals[5]->isEnabled() == true, "incorrect state actuals 5");

    QVERIFY2(mw.ui->scores[0]->text().compare(QString("2")) == 0, "incorrect scores 0");
    QVERIFY2(mw.ui->scores[1]->text().compare(QString("1")) == 0, "incorrect scores 1");
    QVERIFY2(mw.ui->scores[2]->text().compare(QString("-3")) == 0, "incorrect scores 2");
    QVERIFY2(mw.ui->scores[3]->text().compare(QString("2")) == 0, "incorrect scores 3");
    QVERIFY2(mw.ui->scores[4]->text().compare(QString("-5")) == 0, "incorrect scores 4");
    QVERIFY2(mw.ui->scores[5]->text().compare(QString("3")) == 0, "incorrect scores 5");

    QVERIFY2(mw.ui->lastGames[0]->text().compare(QString("")) == 0, "incorrect last games 0");
    QVERIFY2(mw.ui->lastGames[1]->text().compare(QString("3")) == 0, "incorrect last games 1");
    QVERIFY2(mw.ui->lastGames[2]->text().compare(QString("-3")) == 0, "incorrect last games 2");
    QVERIFY2(mw.ui->lastGames[3]->text().compare(QString("")) == 0, "incorrect last games 3");
    QVERIFY2(mw.ui->lastGames[4]->text().compare(QString("-3")) == 0, "incorrect last games 4");
    QVERIFY2(mw.ui->lastGames[5]->text().compare(QString("3")) == 0, "incorrect last games 5");

    QVERIFY2(mw.ui->actuals[0]->text().isEmpty(), "actuals 0 not empty");
    QVERIFY2(mw.ui->actuals[1]->text().isEmpty(), "actuals 1 not empty");
    QVERIFY2(mw.ui->actuals[2]->text().isEmpty(), "actuals 2 not empty");
    QVERIFY2(mw.ui->actuals[3]->text().isEmpty(), "actuals 3 not empty");
    QVERIFY2(mw.ui->actuals[4]->text().isEmpty(), "actuals 4 not empty");
    QVERIFY2(mw.ui->actuals[5]->text().isEmpty(), "actuals 5 not empty");

    QVERIFY2(mw.ui->spinBox->value() == 0, "events spinbox not set to zero");

    QVERIFY2(mw.ui->cashs[0]->text().compare(QString("0,00")) == 0, "incorrect cashs 0");
    QVERIFY2(mw.ui->cashs[1]->text().compare(QString("0,01")) == 0, "incorrect cashs 1");
    QVERIFY2(mw.ui->cashs[2]->text().compare(QString("0,03")) == 0, "incorrect cashs 2");
    QVERIFY2(mw.ui->cashs[3]->text().compare(QString("0,00")) == 0, "incorrect cashs 3");
    QVERIFY2(mw.ui->cashs[4]->text().compare(QString("0,04")) == 0, "incorrect cashs 4");
    QVERIFY2(mw.ui->cashs[5]->text().compare(QString("0,00")) == 0, "incorrect cashs 5");

    QVERIFY2(mw.ui->totalCash->text().compare(QString("0,10 (inkl. 0,01 pro Abwesender)")) == 0, "incorrect totalCash");

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString("Kein Bock")) == 0, "current game multiplier label incorrect");
    QVERIFY2(mw.ui->tripleMultiplier->text().compare(QString("0")) == 0, "triple multiplier label incorrect");
    QVERIFY2(mw.ui->doubleMultiplier->text().compare(QString("0")) == 0, "double multiplier label incorrect");
    QVERIFY2(mw.ui->singleMultiplier->text().compare(QString("0")) == 0, "single multiplier label incorrect");
}

void FrontendTest::TwoCommittedAndTwoPoppedGameShallBeDisplayed()
{
    // Arrange
    std::vector<std::wstring> players
    {
        L"A",
        L"B",
        L"C",
        L"D",
        L"E",
        L"F"
    };

    std::wstring dealer(L"C");
    std::set<unsigned int> sitOutScheme
    {
        3
    };

    MainWindow mw(8u, false);

    QSignalSpy commitButtonSpy(mw.ui->commitButton, &QPushButton::clicked);
    QSignalSpy resetButtonSpy(mw.ui->resetButton, &QPushButton::clicked);

    mw.gameInfo.SetPlayers(players, dealer, sitOutScheme);
    mw.UpdateDisplay();

    // Act, Assert
    bool isEnabled1 = mw.ui->resetButton->isEnabled();

    mw.ui->actuals[0]->setText(QString("2"));
    mw.ui->actuals[3]->setText(QString("2"));
    mw.ui->spinBox->setValue(1);

    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    bool isEnabled2 = mw.ui->resetButton->isEnabled();

    mw.ui->actuals[2]->setText(QString("-3"));
    mw.ui->actuals[4]->setText(QString("-3"));
    mw.ui->spinBox->setValue(2);

    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    bool isEnabled3 = mw.ui->resetButton->isEnabled();

    QVERIFY2(mw.ui->names[0]->text().compare(QString("A")) == 0, "incorrect player name 0");
    QVERIFY2(mw.ui->names[1]->text().compare(QString("B")) == 0, "incorrect player name 1");
    QVERIFY2(mw.ui->names[2]->text().compare(QString("C")) == 0, "incorrect player name 2");
    QVERIFY2(mw.ui->names[3]->text().compare(QString("D")) == 0, "incorrect player name 3");
    QVERIFY2(mw.ui->names[4]->text().compare(QString("E")) == 0, "incorrect player name 4");
    QVERIFY2(mw.ui->names[5]->text().compare(QString("F")) == 0, "incorrect player name 5");

    QVERIFY2(mw.ui->actuals[0]->isEnabled() == true, "incorrect state actuals 0");
    QVERIFY2(mw.ui->actuals[1]->isEnabled() == false, "incorrect state actuals 1");
    QVERIFY2(mw.ui->actuals[2]->isEnabled() == true, "incorrect state actuals 2");
    QVERIFY2(mw.ui->actuals[3]->isEnabled() == true, "incorrect state actuals 3");
    QVERIFY2(mw.ui->actuals[4]->isEnabled() == false, "incorrect state actuals 4");
    QVERIFY2(mw.ui->actuals[5]->isEnabled() == true, "incorrect state actuals 5");

    QVERIFY2(mw.ui->scores[0]->text().compare(QString("2")) == 0, "incorrect scores 0");
    QVERIFY2(mw.ui->scores[1]->text().compare(QString("4")) == 0, "incorrect scores 1");
    QVERIFY2(mw.ui->scores[2]->text().compare(QString("-6")) == 0, "incorrect scores 2");
    QVERIFY2(mw.ui->scores[3]->text().compare(QString("2")) == 0, "incorrect scores 3");
    QVERIFY2(mw.ui->scores[4]->text().compare(QString("-8")) == 0, "incorrect scores 4");
    QVERIFY2(mw.ui->scores[5]->text().compare(QString("6")) == 0, "incorrect scores 5");

    QVERIFY2(mw.ui->lastGames[0]->text().compare(QString("")) == 0, "incorrect last games 0");
    QVERIFY2(mw.ui->lastGames[1]->text().compare(QString("6")) == 0, "incorrect last games 1");
    QVERIFY2(mw.ui->lastGames[2]->text().compare(QString("-6")) == 0, "incorrect last games 2");
    QVERIFY2(mw.ui->lastGames[3]->text().compare(QString("")) == 0, "incorrect last games 3");
    QVERIFY2(mw.ui->lastGames[4]->text().compare(QString("-6")) == 0, "incorrect last games 4");
    QVERIFY2(mw.ui->lastGames[5]->text().compare(QString("6")) == 0, "incorrect last games 5");

    QVERIFY2(mw.ui->actuals[0]->text().isEmpty(), "actuals 0 not empty");
    QVERIFY2(mw.ui->actuals[1]->text().isEmpty(), "actuals 1 not empty");
    QVERIFY2(mw.ui->actuals[2]->text().isEmpty(), "actuals 2 not empty");
    QVERIFY2(mw.ui->actuals[3]->text().isEmpty(), "actuals 3 not empty");
    QVERIFY2(mw.ui->actuals[4]->text().isEmpty(), "actuals 4 not empty");
    QVERIFY2(mw.ui->actuals[5]->text().isEmpty(), "actuals 5 not empty");

    QVERIFY2(mw.ui->spinBox->value() == 0, "events spinbox not set to zero");

    QVERIFY2(mw.ui->cashs[0]->text().compare(QString("0,02")) == 0, "incorrect cashs 0");
    QVERIFY2(mw.ui->cashs[1]->text().compare(QString("0,01")) == 0, "incorrect cashs 1");
    QVERIFY2(mw.ui->cashs[2]->text().compare(QString("0,06")) == 0, "incorrect cashs 2");
    QVERIFY2(mw.ui->cashs[3]->text().compare(QString("0,02")) == 0, "incorrect cashs 3");
    QVERIFY2(mw.ui->cashs[4]->text().compare(QString("0,07")) == 0, "incorrect cashs 4");
    QVERIFY2(mw.ui->cashs[5]->text().compare(QString("0,00")) == 0, "incorrect cashs 5");

    QVERIFY2(mw.ui->totalCash->text().compare(QString("0,24 (inkl. 0,03 pro Abwesender)")) == 0, "incorrect totalCash");

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString("Dreifachbock")) == 0, "current game multiplier label incorrect");
    QVERIFY2(mw.ui->tripleMultiplier->text().compare(QString("5")) == 0, "triple multiplier label incorrect");
    QVERIFY2(mw.ui->doubleMultiplier->text().compare(QString("1")) == 0, "double multiplier label incorrect");
    QVERIFY2(mw.ui->singleMultiplier->text().compare(QString("0")) == 0, "single multiplier label incorrect");

    QVERIFY2(isEnabled1 == false, "reset button wrong enabled state");
    QVERIFY2(isEnabled2, "reset button wrong enabled state");
    QVERIFY2(isEnabled3, "reset button wrong enabled state");

    QTest::mouseClick(mw.ui->resetButton, Qt::LeftButton);
    bool isEnabled4 = mw.ui->resetButton->isEnabled();

    QVERIFY2(mw.ui->names[0]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, "incorrect dealer state name 0");
    QVERIFY2(mw.ui->names[1]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, "incorrect dealer state name 1");
    QVERIFY2(mw.ui->names[2]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, "incorrect dealer state name 2");
    QVERIFY2(mw.ui->names[3]->styleSheet().compare(ExpectedDealerNamesStyleSheet) == 0, "incorrect dealer state name 3");
    QVERIFY2(mw.ui->names[4]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, "incorrect dealer state name 4");
    QVERIFY2(mw.ui->names[5]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, "incorrect dealer state name 5");

    QVERIFY2(mw.ui->actuals[0]->isEnabled() == false, "incorrect state actuals 0");
    QVERIFY2(mw.ui->actuals[1]->isEnabled() == true, "incorrect state actuals 1");
    QVERIFY2(mw.ui->actuals[2]->isEnabled() == true, "incorrect state actuals 2");
    QVERIFY2(mw.ui->actuals[3]->isEnabled() == false, "incorrect state actuals 3");
    QVERIFY2(mw.ui->actuals[4]->isEnabled() == true, "incorrect state actuals 4");
    QVERIFY2(mw.ui->actuals[5]->isEnabled() == true, "incorrect state actuals 5");

    QVERIFY2(mw.ui->scores[0]->text().compare(QString("2")) == 0, "incorrect scores 0");
    QVERIFY2(mw.ui->scores[1]->text().compare(QString("-2")) == 0, "incorrect scores 1");
    QVERIFY2(mw.ui->scores[2]->text().compare(QString("0")) == 0, "incorrect scores 2");
    QVERIFY2(mw.ui->scores[3]->text().compare(QString("2")) == 0, "incorrect scores 3");
    QVERIFY2(mw.ui->scores[4]->text().compare(QString("-2")) == 0, "incorrect scores 4");
    QVERIFY2(mw.ui->scores[5]->text().compare(QString("0")) == 0, "incorrect scores 5");

    QVERIFY2(mw.ui->lastGames[0]->text().compare(QString("2")) == 0, "incorrect last games 0");
    QVERIFY2(mw.ui->lastGames[1]->text().compare(QString("-2")) == 0, "incorrect last games 1");
    QVERIFY2(mw.ui->lastGames[2]->text().compare(QString("")) == 0, "incorrect last games 2");
    QVERIFY2(mw.ui->lastGames[3]->text().compare(QString("2")) == 0, "incorrect last games 3");
    QVERIFY2(mw.ui->lastGames[4]->text().compare(QString("-2")) == 0, "incorrect last games 4");
    QVERIFY2(mw.ui->lastGames[5]->text().compare(QString("")) == 0, "incorrect last games 5");

    QVERIFY2(mw.ui->actuals[0]->text().isEmpty(), "actuals 0 not empty");
    QVERIFY2(mw.ui->actuals[1]->text().isEmpty(), "actuals 1 not empty");
    QVERIFY2(mw.ui->actuals[4]->text().compare(QString("-3")) == 0, "actuals 2 wrong content");
    QVERIFY2(mw.ui->actuals[3]->text().isEmpty(), "actuals 3 not empty");
    QVERIFY2(mw.ui->actuals[4]->text().compare(QString("-3")) == 0, "actuals 4 wrong content");
    QVERIFY2(mw.ui->actuals[5]->text().isEmpty(), "actuals 5 not empty");

    QVERIFY2(mw.ui->spinBox->value() == 2, "events spinbox not set to correct value");

    QVERIFY2(mw.ui->cashs[0]->text().compare(QString("0,00")) == 0, "incorrect cashs 0");
    QVERIFY2(mw.ui->cashs[1]->text().compare(QString("0,02")) == 0, "incorrect cashs 1");
    QVERIFY2(mw.ui->cashs[2]->text().compare(QString("0,01")) == 0, "incorrect cashs 2");
    QVERIFY2(mw.ui->cashs[3]->text().compare(QString("0,00")) == 0, "incorrect cashs 3");
    QVERIFY2(mw.ui->cashs[4]->text().compare(QString("0,02")) == 0, "incorrect cashs 4");
    QVERIFY2(mw.ui->cashs[5]->text().compare(QString("0,01")) == 0, "incorrect cashs 5");

    QVERIFY2(mw.ui->totalCash->text().compare(QString("0,08 (inkl. 0,01 pro Abwesender)")) == 0, "incorrect totalCash");

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString("Einfachbock")) == 0, "current game multiplier label incorrect");
    QVERIFY2(mw.ui->tripleMultiplier->text().compare(QString("0")) == 0, "triple multiplier label incorrect");
    QVERIFY2(mw.ui->doubleMultiplier->text().compare(QString("0")) == 0, "double multiplier label incorrect");
    QVERIFY2(mw.ui->singleMultiplier->text().compare(QString("6")) == 0, "single multiplier label incorrect");

    QVERIFY2(isEnabled4, "reset button wrong enabled state");

    QTest::mouseClick(mw.ui->resetButton, Qt::LeftButton);
    bool isEnabled5 = mw.ui->resetButton->isEnabled();

    QVERIFY2(mw.ui->names[0]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, "incorrect dealer state name 0");
    QVERIFY2(mw.ui->names[1]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, "incorrect dealer state name 1");
    QVERIFY2(mw.ui->names[2]->styleSheet().compare(ExpectedDealerNamesStyleSheet) == 0, "incorrect dealer state name 2");
    QVERIFY2(mw.ui->names[3]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, "incorrect dealer state name 3");
    QVERIFY2(mw.ui->names[4]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, "incorrect dealer state name 4");
    QVERIFY2(mw.ui->names[5]->styleSheet().compare(ExpectedStandardNamesStyleSheet) == 0, "incorrect dealer state name 5");

    QVERIFY2(mw.ui->actuals[0]->isEnabled() == true, "incorrect state actuals 0");
    QVERIFY2(mw.ui->actuals[1]->isEnabled() == true, "incorrect state actuals 1");
    QVERIFY2(mw.ui->actuals[2]->isEnabled() == false, "incorrect state actuals 2");
    QVERIFY2(mw.ui->actuals[3]->isEnabled() == true, "incorrect state actuals 3");
    QVERIFY2(mw.ui->actuals[4]->isEnabled() == true, "incorrect state actuals 4");
    QVERIFY2(mw.ui->actuals[5]->isEnabled() == false, "incorrect state actuals 5");

    QVERIFY2(mw.ui->scores[0]->text().compare(QString("0")) == 0, "incorrect scores 0");
    QVERIFY2(mw.ui->scores[1]->text().compare(QString("0")) == 0, "incorrect scores 1");
    QVERIFY2(mw.ui->scores[2]->text().compare(QString("0")) == 0, "incorrect scores 2");
    QVERIFY2(mw.ui->scores[3]->text().compare(QString("0")) == 0, "incorrect scores 3");
    QVERIFY2(mw.ui->scores[4]->text().compare(QString("0")) == 0, "incorrect scores 4");
    QVERIFY2(mw.ui->scores[5]->text().compare(QString("0")) == 0, "incorrect scores 5");

    QVERIFY2(mw.ui->lastGames[0]->text().compare(QString("")) == 0, "incorrect last games 0");
    QVERIFY2(mw.ui->lastGames[1]->text().compare(QString("")) == 0, "incorrect last games 1");
    QVERIFY2(mw.ui->lastGames[2]->text().compare(QString("")) == 0, "incorrect last games 2");
    QVERIFY2(mw.ui->lastGames[3]->text().compare(QString("")) == 0, "incorrect last games 3");
    QVERIFY2(mw.ui->lastGames[4]->text().compare(QString("")) == 0, "incorrect last games 4");
    QVERIFY2(mw.ui->lastGames[5]->text().compare(QString("")) == 0, "incorrect last games 5");

    QVERIFY2(mw.ui->actuals[0]->text().compare(QString("2")) == 0, "actuals 0 wrong content");
    QVERIFY2(mw.ui->actuals[1]->text().isEmpty(), "actuals 1 not empty");
    QVERIFY2(mw.ui->actuals[2]->text().isEmpty(), "actuals 2 not empty");
    QVERIFY2(mw.ui->actuals[3]->text().compare(QString("2")) == 0, "actuals 3 wrong content");
    QVERIFY2(mw.ui->actuals[4]->text().isEmpty(), "actuals 4 not empty");
    QVERIFY2(mw.ui->actuals[5]->text().isEmpty(), "actuals 5 not empty");

    QVERIFY2(mw.ui->spinBox->value() == 1, "events spinbox not set to correct value");

    QVERIFY2(mw.ui->cashs[0]->text().compare(QString("0,00")) == 0, "incorrect cashs 0");
    QVERIFY2(mw.ui->cashs[1]->text().compare(QString("0,00")) == 0, "incorrect cashs 1");
    QVERIFY2(mw.ui->cashs[2]->text().compare(QString("0,00")) == 0, "incorrect cashs 2");
    QVERIFY2(mw.ui->cashs[3]->text().compare(QString("0,00")) == 0, "incorrect cashs 3");
    QVERIFY2(mw.ui->cashs[4]->text().compare(QString("0,00")) == 0, "incorrect cashs 4");
    QVERIFY2(mw.ui->cashs[5]->text().compare(QString("0,00")) == 0, "incorrect cashs 5");

    QVERIFY2(mw.ui->totalCash->text().compare(QString("0,00 (inkl. 0,00 pro Abwesender)")) == 0, "incorrect totalCash");

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString("Kein Bock")) == 0, "current game multiplier label incorrect");
    QVERIFY2(mw.ui->tripleMultiplier->text().compare(QString("0")) == 0, "triple multiplier label incorrect");
    QVERIFY2(mw.ui->doubleMultiplier->text().compare(QString("0")) == 0, "double multiplier label incorrect");
    QVERIFY2(mw.ui->singleMultiplier->text().compare(QString("0")) == 0, "single multiplier label incorrect");

    QVERIFY2(isEnabled5 == false, "reset button wrong enabled state");
}

void FrontendTest::AllLevelsOfMultipliersShallCorrectlyBeDisplayed()
{
    // Arrange
    std::vector<std::wstring> players
    {
        L"A",
        L"B",
        L"C",
        L"D",
        L"E"
    };

    std::wstring dealer(L"C");
    std::set<unsigned int> sitOutScheme;

    MainWindow mw(8u, false);

    QSignalSpy commitButtonSpy(mw.ui->commitButton, &QPushButton::clicked);

    mw.gameInfo.SetPlayers(players, dealer, sitOutScheme);
    mw.UpdateDisplay();

    // Act, Assert

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString("Kein Bock")) == 0, "current game multiplier label incorrect");
    QVERIFY2(mw.ui->tripleMultiplier->text().compare(QString("0")) == 0, "triple multiplier label incorrect");
    QVERIFY2(mw.ui->doubleMultiplier->text().compare(QString("0")) == 0, "double multiplier label incorrect");
    QVERIFY2(mw.ui->singleMultiplier->text().compare(QString("0")) == 0, "single multiplier label incorrect");

    mw.ui->actuals[0]->setText(QString("2"));
    mw.ui->actuals[3]->setText(QString("2"));
    mw.ui->spinBox->setValue(1);

    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString("Einfachbock")) == 0, "current game multiplier label incorrect");
    QVERIFY2(mw.ui->tripleMultiplier->text().compare(QString("0")) == 0, "triple multiplier label incorrect");
    QVERIFY2(mw.ui->doubleMultiplier->text().compare(QString("0")) == 0, "double multiplier label incorrect");
    QVERIFY2(mw.ui->singleMultiplier->text().compare(QString("5")) == 0, "single multiplier label incorrect");

    mw.ui->actuals[2]->setText(QString("-3"));
    mw.ui->actuals[4]->setText(QString("-3"));
    mw.ui->spinBox->setValue(1);

    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString("Doppelbock")) == 0, "current game multiplier label incorrect");
    QVERIFY2(mw.ui->tripleMultiplier->text().compare(QString("0")) == 0, "triple multiplier label incorrect");
    QVERIFY2(mw.ui->doubleMultiplier->text().compare(QString("4")) == 0, "double multiplier label incorrect");
    QVERIFY2(mw.ui->singleMultiplier->text().compare(QString("1")) == 0, "single multiplier label incorrect");

    mw.ui->actuals[2]->setText(QString("-3"));
    mw.ui->actuals[4]->setText(QString("-3"));
    mw.ui->spinBox->setValue(1);

    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString("Dreifachbock")) == 0, "current game multiplier label incorrect");
    QVERIFY2(mw.ui->tripleMultiplier->text().compare(QString("3")) == 0, "triple multiplier label incorrect");
    QVERIFY2(mw.ui->doubleMultiplier->text().compare(QString("1")) == 0, "double multiplier label incorrect");
    QVERIFY2(mw.ui->singleMultiplier->text().compare(QString("1")) == 0, "single multiplier label incorrect");
}

void FrontendTest::StatisticsShallCorrectlyBeDisplayed()
{
    // Arrange
    std::vector<std::wstring> players
    {
        L"A",
        L"B",
        L"C",
        L"D",
        L"E"
    };

    std::wstring dealer(L"A");
    std::set<unsigned int> sitOutScheme {};

    MainWindow mw(8u, false);

    QSignalSpy commitButtonSpy(mw.ui->commitButton, &QPushButton::clicked);

    mw.gameInfo.SetPlayers(players, dealer, sitOutScheme);
    mw.UpdateDisplay();

    // Act
    mw.ui->actuals[1]->setText(QString("-1"));
    mw.ui->actuals[2]->setText(QString("-1"));
    mw.ui->actuals[3]->setText(QString("1"));
    mw.ui->actuals[4]->setText(QString("1"));
    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    mw.ui->actuals[0]->setText(QString("3"));
    mw.ui->actuals[2]->setText(QString("-1"));
    mw.ui->actuals[3]->setText(QString("-1"));
    mw.ui->actuals[4]->setText(QString("-1"));
    mw.ui->spinBox->setValue(1);
    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    mw.ui->actuals[0]->setText(QString("2"));
    mw.ui->actuals[1]->setText(QString("2"));
    mw.ui->actuals[3]->setText(QString("2"));
    mw.ui->actuals[4]->setText(QString("-6"));
    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    mw.ui->actuals[0]->setText(QString("3"));
    mw.ui->actuals[1]->setText(QString("-3"));
    mw.ui->actuals[2]->setText(QString("3"));
    mw.ui->actuals[4]->setText(QString("-3"));
    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    // Assert
    QVERIFY2(mw.ui->names[0]->text().compare(QString("A")) == 0, "incorrect player name 0");
    QVERIFY2(mw.ui->names[1]->text().compare(QString("B")) == 0, "incorrect player name 1");
    QVERIFY2(mw.ui->names[2]->text().compare(QString("C")) == 0, "incorrect player name 2");
    QVERIFY2(mw.ui->names[3]->text().compare(QString("D")) == 0, "incorrect player name 3");
    QVERIFY2(mw.ui->names[4]->text().compare(QString("E")) == 0, "incorrect player name 4");

    QVERIFY2(mw.ui->scores[0]->text().compare(QString("13")) == 0, "incorrect score 0");
    QVERIFY2(mw.ui->scores[1]->text().compare(QString("-3")) == 0, "incorrect score 1");
    QVERIFY2(mw.ui->scores[2]->text().compare(QString("4")) == 0, "incorrect score 2");
    QVERIFY2(mw.ui->scores[3]->text().compare(QString("4")) == 0, "incorrect score 3");
    QVERIFY2(mw.ui->scores[4]->text().compare(QString("-18")) == 0, "incorrect score 4");

    QVERIFY2(mw.ui->numberWons[0]->text().compare(QString("3")) == 0, "incorrect number wons 0");
    QVERIFY2(mw.ui->numberWons[1]->text().compare(QString("1")) == 0, "incorrect number wons 1");
    QVERIFY2(mw.ui->numberWons[2]->text().compare(QString("1")) == 0, "incorrect number wons 2");
    QVERIFY2(mw.ui->numberWons[3]->text().compare(QString("2")) == 0, "incorrect number wons 3");
    QVERIFY2(mw.ui->numberWons[4]->text().compare(QString("1")) == 0, "incorrect number wons 4");

    QVERIFY2(mw.ui->numberLosts[0]->text().compare(QString("0")) == 0, "incorrect number losts 0");
    QVERIFY2(mw.ui->numberLosts[1]->text().compare(QString("2")) == 0, "incorrect number losts 1");
    QVERIFY2(mw.ui->numberLosts[2]->text().compare(QString("2")) == 0, "incorrect number losts 2");
    QVERIFY2(mw.ui->numberLosts[3]->text().compare(QString("1")) == 0, "incorrect number losts 3");
    QVERIFY2(mw.ui->numberLosts[4]->text().compare(QString("3")) == 0, "incorrect number losts 4");

    QVERIFY2(mw.ui->numberPlayeds[0]->text().compare(QString("3")) == 0, "incorrect number playeds 0");
    QVERIFY2(mw.ui->numberPlayeds[1]->text().compare(QString("3")) == 0, "incorrect number playeds 1");
    QVERIFY2(mw.ui->numberPlayeds[2]->text().compare(QString("3")) == 0, "incorrect number playeds 2");
    QVERIFY2(mw.ui->numberPlayeds[3]->text().compare(QString("3")) == 0, "incorrect number playeds 3");
    QVERIFY2(mw.ui->numberPlayeds[4]->text().compare(QString("4")) == 0, "incorrect number playeds 4");

    QVERIFY2(mw.ui->numberSoloWons[0]->text().compare(QString("1")) == 0, "incorrect number solo wons 0");
    QVERIFY2(mw.ui->numberSoloWons[1]->text().compare(QString("0")) == 0, "incorrect number solo wons 1");
    QVERIFY2(mw.ui->numberSoloWons[2]->text().compare(QString("0")) == 0, "incorrect number solo wons 2");
    QVERIFY2(mw.ui->numberSoloWons[3]->text().compare(QString("0")) == 0, "incorrect number solo wons 3");
    QVERIFY2(mw.ui->numberSoloWons[4]->text().compare(QString("0")) == 0, "incorrect number solo wons 4");

    QVERIFY2(mw.ui->numberSoloLosts[0]->text().compare(QString("0")) == 0, "incorrect number solo losts 0");
    QVERIFY2(mw.ui->numberSoloLosts[1]->text().compare(QString("0")) == 0, "incorrect number solo losts 1");
    QVERIFY2(mw.ui->numberSoloLosts[2]->text().compare(QString("0")) == 0, "incorrect number solo losts 2");
    QVERIFY2(mw.ui->numberSoloLosts[3]->text().compare(QString("0")) == 0, "incorrect number solo losts 3");
    QVERIFY2(mw.ui->numberSoloLosts[4]->text().compare(QString("1")) == 0, "incorrect number solo losts 4");

    QVERIFY2(mw.ui->pointsSolos[0]->text().compare(QString("3")) == 0, "incorrect points solos 0");
    QVERIFY2(mw.ui->pointsSolos[1]->text().compare(QString("0")) == 0, "incorrect points solos 1");
    QVERIFY2(mw.ui->pointsSolos[2]->text().compare(QString("0")) == 0, "incorrect points solos 2");
    QVERIFY2(mw.ui->pointsSolos[3]->text().compare(QString("0")) == 0, "incorrect points solos 3");
    QVERIFY2(mw.ui->pointsSolos[4]->text().compare(QString("-12")) == 0, "incorrect points solos 4");

    QVERIFY2(mw.ui->maxSingleWins[0]->text().compare(QString("6")) == 0, "incorrect max single win 0");
    QVERIFY2(mw.ui->maxSingleWins[1]->text().compare(QString("4")) == 0, "incorrect max single win 1");
    QVERIFY2(mw.ui->maxSingleWins[2]->text().compare(QString("6")) == 0, "incorrect max single win 2");
    QVERIFY2(mw.ui->maxSingleWins[3]->text().compare(QString("4")) == 0, "incorrect max single win 3");
    QVERIFY2(mw.ui->maxSingleWins[4]->text().compare(QString("1")) == 0, "incorrect max single win 4");

    QVERIFY2(mw.ui->maxSingleLosss[0]->text().compare(QString("0")) == 0, "incorrect max single loss 0");
    QVERIFY2(mw.ui->maxSingleLosss[1]->text().compare(QString("-6")) == 0, "incorrect max single loss 1");
    QVERIFY2(mw.ui->maxSingleLosss[2]->text().compare(QString("-1")) == 0, "incorrect max single loss 2");
    QVERIFY2(mw.ui->maxSingleLosss[3]->text().compare(QString("-1")) == 0, "incorrect max single loss 3");
    QVERIFY2(mw.ui->maxSingleLosss[4]->text().compare(QString("-12")) == 0, "incorrect max single loss 4");

    QVERIFY2(mw.ui->unmultipliedScores[0]->text().compare(QString("8")) == 0, "incorrect unmultiplied scores 0");
    QVERIFY2(mw.ui->unmultipliedScores[1]->text().compare(QString("-2")) == 0, "incorrect unmultiplied scores 1");
    QVERIFY2(mw.ui->unmultipliedScores[2]->text().compare(QString("1")) == 0, "incorrect unmultiplied scores 2");
    QVERIFY2(mw.ui->unmultipliedScores[3]->text().compare(QString("2")) == 0, "incorrect unmultiplied scores 3");
    QVERIFY2(mw.ui->unmultipliedScores[4]->text().compare(QString("-9")) == 0, "incorrect unmultiplied scores 4");
}

void FrontendTest::ScoreHistoryPlotShallWorkCorrectly()
{
    // Arrange
    std::vector<std::wstring> players
    {
        L"A",
        L"B",
        L"C",
        L"D",
        L"E"
    };

    std::wstring dealer(L"A");
    std::set<unsigned int> sitOutScheme {};

    MainWindow mw(8u, false);

    QSignalSpy commitButtonSpy(mw.ui->commitButton, &QPushButton::clicked);

    mw.gameInfo.SetPlayers(players, dealer, sitOutScheme);
    mw.UpdateDisplay();

    // Act
    mw.ui->actuals[1]->setText(QString("-1"));
    mw.ui->actuals[2]->setText(QString("-1"));
    mw.ui->actuals[3]->setText(QString("1"));
    mw.ui->actuals[4]->setText(QString("1"));
    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    mw.ui->actuals[0]->setText(QString("3"));
    mw.ui->actuals[2]->setText(QString("-1"));
    mw.ui->actuals[3]->setText(QString("-1"));
    mw.ui->actuals[4]->setText(QString("-1"));
    mw.ui->spinBox->setValue(1);
    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    // Act, Assert
    QVERIFY2(mw.ui->plotPlayerHistory->graphCount() == 5, "incorrect graph count A");

    mw.ui->playerHistorySelectionCheckboxes[2]->setChecked(false);

    QVERIFY2(mw.ui->plotPlayerHistory->graphCount() == 4, "incorrect graph count B");

    mw.ui->playerHistorySelectionCheckboxes[2]->setChecked(true);
    mw.ui->playerHistorySelectionCheckboxes[0]->setChecked(false);
    mw.ui->playerHistorySelectionCheckboxes[1]->setChecked(false);

    QVERIFY2(mw.ui->plotPlayerHistory->graphCount() == 3, "incorrect graph count C");

    mw.ui->playerHistorySelectionCheckboxes[0]->setChecked(true);
    mw.ui->playerHistorySelectionCheckboxes[1]->setChecked(true);

    QVERIFY2(mw.ui->plotPlayerHistory->graphCount() == 5, "incorrect graph count D");
}

void FrontendTest::AboutButtonShallTriggerDialogAndOKShallClose()
{
    // Arrange
    MainWindow mw(8u, false);
    auto ui = mw.ui;

    // spy needed such that events actually happen
    QSignalSpy spyAboutButton(ui->aboutButton, &QAbstractButton::pressed);

    // Act
    bool aboutMessageBoxFound = false;
    bool aboutMessageBoxHasOneButton = false;
    int interval = 1000;
    QTimer::singleShot(interval, [&]()
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
    QVERIFY2(aboutMessageBoxFound, "aboutMessageBox not found");
    QVERIFY2(aboutMessageBoxHasOneButton, "aboutMessageBox does not have exactly one button");

    QVERIFY2(mw.aboutMessageBox == nullptr, "aboutMessageBox still reachable");
}

void FrontendTest::MandatorySoloButtonShallBeEnabledAndTrigger()
{
    // Arrange
    std::vector<std::wstring> players
    {
        L"A",
        L"B",
        L"C",
        L"D"
    };

    std::wstring dealer(L"A");
    std::set<unsigned int> sitOutScheme {};

    MainWindow mw(8u, false);

    QSignalSpy mandatorySoloButtonSpy(mw.ui->mandatorySoloButton, &QPushButton::clicked);
    QSignalSpy commitButtonSpy(mw.ui->commitButton, &QPushButton::clicked);
    QSignalSpy resetButtonSpy(mw.ui->resetButton, &QPushButton::clicked);

    mw.gameInfo.SetPlayers(players, dealer, sitOutScheme);
    mw.UpdateDisplay();

    // Act, Assert
    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString::fromUtf8("Kein Bock")) == 0, "incorrect multiplier label at beginning");
    QVERIFY2(mw.ui->mandatorySoloButton->isEnabled() == false, "wrong enabled state at beginning");

    mw.ui->actuals[0]->setText(QString("-1"));
    mw.ui->actuals[1]->setText(QString("-1"));
    mw.ui->actuals[2]->setText(QString("1"));
    mw.ui->actuals[3]->setText(QString("1"));
    mw.ui->spinBox->setValue(1);
    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    mw.ui->actuals[0]->setText(QString("-1"));
    mw.ui->actuals[1]->setText(QString("-1"));
    mw.ui->actuals[2]->setText(QString("1"));
    mw.ui->actuals[3]->setText(QString("1"));
    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString::fromUtf8("Einfachbock")) == 0, "incorrect multiplier label after first game");
    QVERIFY2(mw.ui->mandatorySoloButton->isEnabled() == true, "wrong enabled state after first game");

    QTest::mouseClick(mw.ui->mandatorySoloButton, Qt::LeftButton);

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString::fromUtf8("Pflichtsolorunde")) == 0, "incorrect multiplier label after trigger");
    QVERIFY2(mw.ui->mandatorySoloButton->isEnabled() == false, "wrong enabled state after trigger");

    mw.ui->actuals[0]->setText(QString("1"));
    mw.ui->actuals[1]->setText(QString("1"));
    mw.ui->actuals[2]->setText(QString("-3"));
    mw.ui->actuals[3]->setText(QString("1"));
    QTest::mouseClick(mw.ui->commitButton, Qt::LeftButton);

    QVERIFY2(mw.ui->scores[0]->text().compare(QString::fromUtf8("-2")) == 0, "incorrect score 0");
    QVERIFY2(mw.ui->scores[1]->text().compare(QString::fromUtf8("-2")) == 0, "incorrect score 1");
    QVERIFY2(mw.ui->scores[2]->text().compare(QString::fromUtf8("0")) == 0, "incorrect score 2");
    QVERIFY2(mw.ui->scores[3]->text().compare(QString::fromUtf8("4")) == 0, "incorrect score 3");

    QTest::mouseClick(mw.ui->resetButton, Qt::LeftButton);
    QTest::mouseClick(mw.ui->resetButton, Qt::LeftButton);

    QVERIFY2(mw.ui->currentGameMultiplier->text().compare(QString::fromUtf8("Einfachbock")) == 0, "incorrect multiplier label after reset");
    QVERIFY2(mw.ui->mandatorySoloButton->isEnabled() == true, "wrong enabled state after reset");
}

#endif // _USE_LONG_TEST

QTEST_MAIN(FrontendTest)

#include "tst_mainwindow.moc"
