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
#include <QtWidgets/QMenuBar>

#include "../Frontend/playerselection_ui.h"

class FrontendTest : public QObject
{
    Q_OBJECT

public:
    FrontendTest();
    ~FrontendTest();

private slots:
    void ConstructionShallWorkCompletely();
    void ConstructionShallThrowOnBadDealer1();
    void ConstructionShallThrowOnBadDealer2();
#ifdef _USE_LONG_TEST
    void InputDataWithoutActionShallBeReturned();
    void AfterLoweringPlayerCountCorrectDataShallBeReturned();
    void AfterRaisingPlayerCountAndInteractingCorrectDataShallBeReturned();
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
    // Arrange
    std::vector<std::pair<QString, bool>> players
    {
        std::pair<QString, bool>(QString("A"), true),
        std::pair<QString, bool>(QString("B"), true),
        std::pair<QString, bool>(QString("C"), true),
        std::pair<QString, bool>(QString("E"), true),
        std::pair<QString, bool>(QString("F"), true),
        std::pair<QString, bool>(QString("G"), true),
        std::pair<QString, bool>(QString("D"), false)
    };

    QString dealer("C");
    std::set<unsigned int> sitOutScheme
    {
        0,
        3
    };

    try
    {
        // Act
        Ui::PlayerSelection ps(8u, players, dealer, sitOutScheme, nullptr);

        // Assert
        QVERIFY2(ps.verticalDialogLayout, "main layout not created");
        QVERIFY2(ps.topLayout, "top layout not created");
        QVERIFY2(ps.playerNamesGridLayout, "player names grid layout not created");
        QVERIFY2(ps.dialogNumberOfPresentPlayers, "spinbox for players not created");
        QVERIFY2(ps.dialogAnzahlSpielerLabel, "anzahl spieler label not created");

        QVERIFY2(ps.dialogNames.size() > 0, "there must be name inputs");
        QVERIFY2(ps.dialogNames.size() == ps.dealerButtons.size(), "size of names unequal to size of radio buttons");

        for(size_t i = 0; i < ps.dialogNames.size(); ++i)
        {
            QVERIFY2(ps.dialogNames[i], "name input not created");
            QVERIFY2(ps.dealerButtons[i], "dealer radio button not created");
        }

        QVERIFY2(ps.dialogSpacer, "spacer not created");
        QVERIFY2(ps.bottomLayout, "bottom layout not created");
        QVERIFY2(ps.dialogAussitzenLabel, "dialog aussitzen not created");
        QVERIFY2(ps.dialogAcceptButton, "accept button not created");

        QVERIFY2(ps.dialogSittingOuts.size() > 0, "there must be inputs for the sitting out scheme");

        for(size_t i = 0; i < ps.dialogSittingOuts.size(); ++i)
        {
            QVERIFY2(ps.dialogSittingOuts[i], "sitting out scheme input not created");
        }
    }
    catch (std::exception & ex)
    {
        QFAIL(ex.what());
    }
}

void FrontendTest::ConstructionShallThrowOnBadDealer1()
{
    std::vector<std::pair<QString, bool>> players
    {
        std::pair<QString, bool>(QString("A"), true),
        std::pair<QString, bool>(QString("B"), true),
        std::pair<QString, bool>(QString("C"), true),
        std::pair<QString, bool>(QString("E"), true),
        std::pair<QString, bool>(QString("F"), true),
        std::pair<QString, bool>(QString("G"), true),
        std::pair<QString, bool>(QString("D"), false)
    };

    QString dealer("D");
    std::set<unsigned int> sitOutScheme
    {
        0,
        3
    };

    QVERIFY_EXCEPTION_THROWN(
        try
        {
            Ui::PlayerSelection ps(8u, players, dealer, sitOutScheme, nullptr);
        }
        catch( const std::exception& e )
        {
            QCOMPARE("dealer not among players or not active", e.what());
            throw;
        }
    , std::exception);
}

void FrontendTest::ConstructionShallThrowOnBadDealer2()
{
    std::vector<std::pair<QString, bool>> players
    {
        std::pair<QString, bool>(QString("A"), true),
        std::pair<QString, bool>(QString("B"), true),
        std::pair<QString, bool>(QString("C"), true),
        std::pair<QString, bool>(QString("E"), true),
        std::pair<QString, bool>(QString("F"), true),
        std::pair<QString, bool>(QString("G"), true),
        std::pair<QString, bool>(QString("D"), false)
    };

    QString dealer("unknown");
    std::set<unsigned int> sitOutScheme
    {
        0,
        3
    };

    QVERIFY_EXCEPTION_THROWN(
        try
        {
            Ui::PlayerSelection ps(8u, players, dealer, sitOutScheme, nullptr);
        }
        catch( const std::exception& e )
        {
            QCOMPARE("dealer not among players or not active", e.what());
            throw;
        }
    , std::exception);
}

#ifdef _USE_LONG_TEST

void FrontendTest::InputDataWithoutActionShallBeReturned()
{
    // Arrange
    std::vector<std::pair<QString, bool>> players
    {
        std::pair<QString, bool>(QString("A"), true),
        std::pair<QString, bool>(QString("B"), true),
        std::pair<QString, bool>(QString("C"), true),
        std::pair<QString, bool>(QString("E"), true),
        std::pair<QString, bool>(QString("F"), true),
        std::pair<QString, bool>(QString("G"), true),
        std::pair<QString, bool>(QString("D"), false)
    };

    QString dealer("C");
    std::set<unsigned int> sitOutScheme
    {
        0,
        3
    };

    Ui::PlayerSelection ps(8u, players, dealer, sitOutScheme, nullptr);
    ps.setModal(true);
    ps.show();

    QSignalSpy acceptButtonSpy(ps.dialogAcceptButton, &QPushButton::clicked);

    // Act
    QTimer::singleShot(200, [&]()
    {
        QTest::mouseClick(ps.dialogAcceptButton, Qt::LeftButton);
    });

    int dialogCode = ps.exec();

    acceptButtonSpy.wait(300);

    auto result = ps.GetResults();

    // Assert
    QVERIFY2(acceptButtonSpy.count() == 1, "accept button spy did not register signal");
    QVERIFY2(dialogCode == QDialog::Accepted, "dialog does not report accepted");

    auto resultPlayers = std::get<0>(result);
    auto resultDealer = std::get<1>(result);
    auto resultSitOutScheme = std::get<2>(result);

    QVERIFY2(resultPlayers.size() == 6, "incorrect result players size");
    QVERIFY2(resultPlayers[0].compare(QString("A")) == 0, "wrong player 0");
    QVERIFY2(resultPlayers[1].compare(QString("B")) == 0, "wrong player 1");
    QVERIFY2(resultPlayers[2].compare(QString("C")) == 0, "wrong player 2");
    QVERIFY2(resultPlayers[3].compare(QString("E")) == 0, "wrong player 3");
    QVERIFY2(resultPlayers[4].compare(QString("F")) == 0, "wrong player 4");
    QVERIFY2(resultPlayers[5].compare(QString("G")) == 0, "wrong player 5");

    QVERIFY2(resultDealer.compare(QString("C")) == 0, "wrong dealer");

    QVERIFY2(resultSitOutScheme.size() == 1, "wrong size of sit out scheme");
    QVERIFY2(resultSitOutScheme.count(3) == 1, "wrong concent of sit out scheme");
}

void FrontendTest::AfterLoweringPlayerCountCorrectDataShallBeReturned()
{
    // Arrange
    std::vector<std::pair<QString, bool>> players
    {
        std::pair<QString, bool>(QString("A"), true),
        std::pair<QString, bool>(QString("B"), true),
        std::pair<QString, bool>(QString("C"), true),
        std::pair<QString, bool>(QString("E"), true),
        std::pair<QString, bool>(QString("F"), true),
        std::pair<QString, bool>(QString("G"), true),
        std::pair<QString, bool>(QString("D"), false)
    };

    QString dealer("C");
    std::set<unsigned int> sitOutScheme
    {
        0,
        3
    };

    Ui::PlayerSelection ps(8u, players, dealer, sitOutScheme, nullptr);
    ps.setModal(true);
    ps.show();

    QSignalSpy acceptButtonSpy(ps.dialogAcceptButton, &QPushButton::clicked);

    bool playerNameInput5visible = true;
    bool dealerInput5visible = true;

    // Act
    QTimer::singleShot(200, [&]()
    {
        ps.dialogNumberOfPresentPlayers->clear();
        QTest::keyClicks(ps.dialogNumberOfPresentPlayers, "5");
        playerNameInput5visible = ps.dialogNames[5]->isVisible();
        dealerInput5visible = ps.dealerButtons[5]->isVisible();
        QTest::mouseClick(ps.dialogAcceptButton, Qt::LeftButton);
    });

    int dialogCode = ps.exec();

    acceptButtonSpy.wait(300);

    auto result = ps.GetResults();

    // Assert
    QVERIFY2(acceptButtonSpy.count() == 1, "accept button spy did not register signal");
    QVERIFY2(dialogCode == QDialog::Accepted, "dialog does not report accepted");

    auto resultPlayers = std::get<0>(result);
    auto resultDealer = std::get<1>(result);
    auto resultSitOutScheme = std::get<2>(result);

    QVERIFY2(resultPlayers.size() == 5, "incorrect result players size");
    QVERIFY2(resultPlayers[0].compare(QString("A")) == 0, "wrong player 0");
    QVERIFY2(resultPlayers[1].compare(QString("B")) == 0, "wrong player 1");
    QVERIFY2(resultPlayers[2].compare(QString("C")) == 0, "wrong player 2");
    QVERIFY2(resultPlayers[3].compare(QString("E")) == 0, "wrong player 3");
    QVERIFY2(resultPlayers[4].compare(QString("F")) == 0, "wrong player 4");

    QVERIFY2(resultDealer.compare(QString("C")) == 0, "wrong dealer");

    QVERIFY2(resultSitOutScheme.size() == 0, "wrong size of sit out scheme");

    QVERIFY2(!playerNameInput5visible, "player name input incorrectly visible");
    QVERIFY2(!dealerInput5visible, "dealer input incorrectly visible");
}

void FrontendTest::AfterRaisingPlayerCountAndInteractingCorrectDataShallBeReturned()
{
    // Arrange
    std::vector<std::pair<QString, bool>> players
    {
        std::pair<QString, bool>(QString("A"), true),
        std::pair<QString, bool>(QString("B"), true),
        std::pair<QString, bool>(QString("C"), true),
        std::pair<QString, bool>(QString("E"), true),
        std::pair<QString, bool>(QString("F"), true),
        std::pair<QString, bool>(QString("G"), true),
        std::pair<QString, bool>(QString("D"), false)
    };

    QString dealer("C");
    std::set<unsigned int> sitOutScheme
    {
        0,
        3
    };

    Ui::PlayerSelection ps(8u, players, dealer, sitOutScheme, nullptr);
    ps.setModal(true);
    ps.show();

    QSignalSpy acceptButtonSpy(ps.dialogAcceptButton, &QPushButton::clicked);

    bool playerNameInput6visible = false;
    bool dealerInput6visible = false;

    // Act
    QTimer::singleShot(200, [&]()
    {
        ps.dialogNumberOfPresentPlayers->clear();
        QTest::keyClicks(ps.dialogNumberOfPresentPlayers, "7");
        playerNameInput6visible = ps.dialogNames[6]->isVisible();
        dealerInput6visible = ps.dealerButtons[6]->isVisible();

        ps.dialogNames[0]->clear();
        ps.dialogNames[1]->clear();
        ps.dialogNames[2]->clear();
        ps.dialogNames[3]->clear();
        ps.dialogNames[4]->clear();
        ps.dialogNames[5]->clear();
        ps.dialogNames[6]->clear();
        QTest::keyClicks(ps.dialogNames[0], "J");
        QTest::keyClicks(ps.dialogNames[1], "K");
        QTest::keyClicks(ps.dialogNames[2], "L");
        QTest::keyClicks(ps.dialogNames[3], "M");
        QTest::keyClicks(ps.dialogNames[4], "N");
        QTest::keyClicks(ps.dialogNames[5], "O");
        QTest::keyClicks(ps.dialogNames[6], "P");

        QTest::mouseClick(ps.dealerButtons[2], Qt::LeftButton);

        QTest::mouseClick(ps.dialogAcceptButton, Qt::LeftButton);
    });

    int dialogCode = ps.exec();

    acceptButtonSpy.wait(300);

    auto result = ps.GetResults();

    // Assert
    QVERIFY2(acceptButtonSpy.count() == 1, "accept button spy did not register signal");
    QVERIFY2(dialogCode == QDialog::Accepted, "dialog does not report accepted");

    auto resultPlayers = std::get<0>(result);
    auto resultDealer = std::get<1>(result);
    auto resultSitOutScheme = std::get<2>(result);

    QVERIFY2(resultPlayers.size() == 7, "incorrect result players size");
    QVERIFY2(resultPlayers[0].compare(QString("J")) == 0, "wrong player 0");
    QVERIFY2(resultPlayers[1].compare(QString("K")) == 0, "wrong player 1");
    QVERIFY2(resultPlayers[2].compare(QString("L")) == 0, "wrong player 2");
    QVERIFY2(resultPlayers[3].compare(QString("M")) == 0, "wrong player 3");
    QVERIFY2(resultPlayers[4].compare(QString("N")) == 0, "wrong player 4");
    QVERIFY2(resultPlayers[5].compare(QString("O")) == 0, "wrong player 5");
    QVERIFY2(resultPlayers[6].compare(QString("P")) == 0, "wrong player 6");

    QVERIFY2(resultDealer.compare(QString("L")) == 0, "wrong dealer");

    QVERIFY2(resultSitOutScheme.size() == 2, "wrong size of sit out scheme");
    QVERIFY2(resultSitOutScheme.count(3) == 1, "wrong concent of sit out scheme");
    QVERIFY2(resultSitOutScheme.count(4) == 1, "wrong concent of sit out scheme");

    QVERIFY2(playerNameInput6visible, "player name input incorrectly invisible");
    QVERIFY2(dealerInput6visible, "dealer input incorrectly invisible");
}

#endif // _USE_LONG_TEST

QTEST_MAIN(FrontendTest)

#include "tst_playerselection.moc"
