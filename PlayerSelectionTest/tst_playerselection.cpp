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
#include <QtWidgets/QMenuBar>

#include "../Frontend/playerselection_ui.h"

class FrontendTest : public QObject
{
    Q_OBJECT

private:
    const int SingleShotInterval = 200;
    const int WaitingInterval = 300;
    const unsigned int MaxPlayers = 8U;
    const unsigned int DefaultPlayers = 8U;

public:
    FrontendTest();

private slots:
    void ConstructionShallWorkCompletely() const;
    void ConstructionShallThrowOnBadDealer1() const;
    void ConstructionShallThrowOnBadDealer2() const;
#ifdef _USE_LONG_TEST
    void InputDataWithoutActionShallBeReturned();
    void AfterLoweringPlayerCountCorrectDataShallBeReturned();
    void AfterRaisingPlayerCountAndInteractingCorrectDataShallBeReturned();
#endif
};

FrontendTest::FrontendTest()
= default;

void FrontendTest::ConstructionShallWorkCompletely() const
{
    // Arrange
    std::vector<std::pair<QString, bool>> players
    {
        std::pair<QString, bool>(QString::fromUtf8("A"), true),
        std::pair<QString, bool>(QString::fromUtf8("B"), true),
        std::pair<QString, bool>(QString::fromUtf8("C"), true),
        std::pair<QString, bool>(QString::fromUtf8("E"), true),
        std::pair<QString, bool>(QString::fromUtf8("F"), true),
        std::pair<QString, bool>(QString::fromUtf8("G"), true),
        std::pair<QString, bool>(QString::fromUtf8("D"), false)
    };

    QString dealer = QString::fromUtf8("C");
    std::set<unsigned int> sitOutScheme
    {
        0,
        3
    };

    try
    {
        // Act
        Ui::PlayerSelection ps(MaxPlayers, players, dealer, sitOutScheme, nullptr);

        // Assert
        QVERIFY2(ps.verticalDialogLayout, qPrintable(QString::fromUtf8("main layout not created")));
        QVERIFY2(ps.topLayout, qPrintable(QString::fromUtf8("top layout not created")));
        QVERIFY2(ps.playerNamesGridLayout, qPrintable(QString::fromUtf8("player names grid layout not created")));
        QVERIFY2(ps.dialogNumberOfPresentPlayers, qPrintable(QString::fromUtf8("spinbox for players not created")));
        QVERIFY2(ps.dialogAnzahlSpielerLabel, qPrintable(QString::fromUtf8("anzahl spieler label not created")));

        QVERIFY2(!ps.dialogNames.empty(), qPrintable(QString::fromUtf8("there must be name inputs")));
        QVERIFY2(ps.dialogNames.size() == ps.dealerButtons.size(), qPrintable(QString::fromUtf8("size of names unequal to size of radio buttons")));

        for(size_t i = 0; i < ps.dialogNames.size(); ++i)
        {
            QVERIFY2(ps.dialogNames[i], qPrintable(QString::fromUtf8("name input not created")));
            QVERIFY2(ps.dealerButtons[i], qPrintable(QString::fromUtf8("dealer radio button not created")));
        }

        QVERIFY2(ps.dialogSpacer, qPrintable(QString::fromUtf8("spacer not created")));
        QVERIFY2(ps.bottomLayout, qPrintable(QString::fromUtf8("bottom layout not created")));
        QVERIFY2(ps.dialogAussitzenLabel, qPrintable(QString::fromUtf8("dialog aussitzen not created")));
        QVERIFY2(ps.dialogAcceptButton, qPrintable(QString::fromUtf8("accept button not created")));

        QVERIFY2(!ps.dialogSittingOuts.empty(), qPrintable(QString::fromUtf8("there must be inputs for the sitting out scheme")));

        for(auto & dialogSittingOut : ps.dialogSittingOuts)
        {
            QVERIFY2(dialogSittingOut, qPrintable(QString::fromUtf8("sitting out scheme input not created")));
        }
    }
    catch (std::exception & ex)
    {
        QFAIL(ex.what());
    }
}

void FrontendTest::ConstructionShallThrowOnBadDealer1() const
{
    std::vector<std::pair<QString, bool>> players
    {
        std::pair<QString, bool>(QString::fromUtf8("A"), true),
        std::pair<QString, bool>(QString::fromUtf8("B"), true),
        std::pair<QString, bool>(QString::fromUtf8("C"), true),
        std::pair<QString, bool>(QString::fromUtf8("E"), true),
        std::pair<QString, bool>(QString::fromUtf8("F"), true),
        std::pair<QString, bool>(QString::fromUtf8("G"), true),
        std::pair<QString, bool>(QString::fromUtf8("D"), false)
    };

    QString dealer = QString::fromUtf8("D");
    std::set<unsigned int> sitOutScheme
    {
        0,
        3
    };

    QVERIFY_EXCEPTION_THROWN(
        try
        {
            Ui::PlayerSelection ps(MaxPlayers, players, dealer, sitOutScheme, nullptr);
        }
        catch( const std::exception& e )
        {
            QString expected = QString::fromUtf8("dealer \"D\" not among players or not active");
            QString actual = QString::fromUtf8(e.what());
            QVERIFY2(expected.compare(actual) == 0, qPrintable(QString::fromUtf8("exception message does not match")));
            throw;
        }
    , std::exception);
}

void FrontendTest::ConstructionShallThrowOnBadDealer2() const
{
    std::vector<std::pair<QString, bool>> players
    {
        std::pair<QString, bool>(QString::fromUtf8("A"), true),
        std::pair<QString, bool>(QString::fromUtf8("B"), true),
        std::pair<QString, bool>(QString::fromUtf8("C"), true),
        std::pair<QString, bool>(QString::fromUtf8("E"), true),
        std::pair<QString, bool>(QString::fromUtf8("F"), true),
        std::pair<QString, bool>(QString::fromUtf8("G"), true),
        std::pair<QString, bool>(QString::fromUtf8("D"), false)
    };

    QString dealer = QString::fromUtf8("unknown");
    std::set<unsigned int> sitOutScheme
    {
        0,
        3
    };

    QVERIFY_EXCEPTION_THROWN(
        try
        {
            Ui::PlayerSelection ps(MaxPlayers, players, dealer, sitOutScheme, nullptr);
        }
        catch( const std::exception& e )
        {
            QString expected = QString::fromUtf8("dealer \"unknown\" not among players or not active");
            QString actual = QString::fromUtf8(e.what());
            QVERIFY2(expected.compare(actual) == 0, qPrintable(QString::fromUtf8("exception message does not match")));
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
        std::pair<QString, bool>(QString::fromUtf8("A"), true),
        std::pair<QString, bool>(QString::fromUtf8("B"), true),
        std::pair<QString, bool>(QString::fromUtf8("C"), true),
        std::pair<QString, bool>(QString::fromUtf8("E"), true),
        std::pair<QString, bool>(QString::fromUtf8("F"), true),
        std::pair<QString, bool>(QString::fromUtf8("G"), true),
        std::pair<QString, bool>(QString::fromUtf8("D"), false)
    };

    QString dealer = QString::fromUtf8("C");
    std::set<unsigned int> sitOutScheme
    {
        0,
        3
    };

    Ui::PlayerSelection ps(this->DefaultPlayers, players, dealer, sitOutScheme, nullptr);
    ps.setModal(true);
    ps.show();

    QSignalSpy acceptButtonSpy(ps.dialogAcceptButton, &QPushButton::clicked);

    // Act
    QTimer::singleShot(this->SingleShotInterval, this, [&]()
    {
        QTest::mouseClick(ps.dialogAcceptButton, Qt::LeftButton);
    });

    int dialogCode = ps.exec();

    acceptButtonSpy.wait(this->WaitingInterval);

    auto result = ps.GetResults();

    // Assert
    QVERIFY2(acceptButtonSpy.count() == 1, qPrintable(QString::fromUtf8("accept button spy did not register signal")));
    QVERIFY2(dialogCode == QDialog::Accepted, qPrintable(QString::fromUtf8("dialog does not report accepted")));

    auto resultPlayers = std::get<0>(result);
    auto resultDealer = std::get<1>(result);
    auto resultSitOutScheme = std::get<2>(result);

    QVERIFY2(resultPlayers.size() == 6, qPrintable(QString::fromUtf8("incorrect result players size")));
    QVERIFY2(resultPlayers[0].compare(QString::fromUtf8("A")) == 0, qPrintable(QString::fromUtf8("wrong player 0")));
    QVERIFY2(resultPlayers[1].compare(QString::fromUtf8("B")) == 0, qPrintable(QString::fromUtf8("wrong player 1")));
    QVERIFY2(resultPlayers[2].compare(QString::fromUtf8("C")) == 0, qPrintable(QString::fromUtf8("wrong player 2")));
    QVERIFY2(resultPlayers[3].compare(QString::fromUtf8("E")) == 0, qPrintable(QString::fromUtf8("wrong player 3")));
    QVERIFY2(resultPlayers[4].compare(QString::fromUtf8("F")) == 0, qPrintable(QString::fromUtf8("wrong player 4")));
    QVERIFY2(resultPlayers[5].compare(QString::fromUtf8("G")) == 0, qPrintable(QString::fromUtf8("wrong player 5")));

    QVERIFY2(resultDealer.compare(QString::fromUtf8("C")) == 0, qPrintable(QString::fromUtf8("wrong dealer")));

    QVERIFY2(resultSitOutScheme.size() == 1, qPrintable(QString::fromUtf8("wrong size of sit out scheme")));
    QVERIFY2(resultSitOutScheme.count(3) == 1, qPrintable(QString::fromUtf8("wrong concent of sit out scheme")));
}

void FrontendTest::AfterLoweringPlayerCountCorrectDataShallBeReturned()
{
    // Arrange
    std::vector<std::pair<QString, bool>> players
    {
        std::pair<QString, bool>(QString::fromUtf8("A"), true),
        std::pair<QString, bool>(QString::fromUtf8("B"), true),
        std::pair<QString, bool>(QString::fromUtf8("C"), true),
        std::pair<QString, bool>(QString::fromUtf8("E"), true),
        std::pair<QString, bool>(QString::fromUtf8("F"), true),
        std::pair<QString, bool>(QString::fromUtf8("G"), true),
        std::pair<QString, bool>(QString::fromUtf8("D"), false)
    };

    QString dealer = QString::fromUtf8("C");
    std::set<unsigned int> sitOutScheme
    {
        0,
        3
    };

    Ui::PlayerSelection ps(this->DefaultPlayers, players, dealer, sitOutScheme, nullptr);
    ps.setModal(true);
    ps.show();

    QSignalSpy acceptButtonSpy(ps.dialogAcceptButton, &QPushButton::clicked);

    bool playerNameInput5visible = true;
    bool dealerInput5visible = true;

    // Act
    QTimer::singleShot(this->SingleShotInterval, this, [&]()
    {
        ps.dialogNumberOfPresentPlayers->clear();
        QTest::keyClicks(ps.dialogNumberOfPresentPlayers, QString::fromUtf8("5"));
        playerNameInput5visible = ps.dialogNames[5]->isVisible();
        dealerInput5visible = ps.dealerButtons[5]->isVisible();
        QTest::mouseClick(ps.dialogAcceptButton, Qt::LeftButton);
    });

    int dialogCode = ps.exec();

    acceptButtonSpy.wait(this->WaitingInterval);

    auto result = ps.GetResults();

    // Assert
    QVERIFY2(acceptButtonSpy.count() == 1, qPrintable(QString::fromUtf8("accept button spy did not register signal")));
    QVERIFY2(dialogCode == QDialog::Accepted, qPrintable(QString::fromUtf8("dialog does not report accepted")));

    auto resultPlayers = std::get<0>(result);
    auto resultDealer = std::get<1>(result);
    auto resultSitOutScheme = std::get<2>(result);

    QVERIFY2(resultPlayers.size() == 5, qPrintable(QString::fromUtf8("incorrect result players size")));
    QVERIFY2(resultPlayers[0].compare(QString::fromUtf8("A")) == 0, qPrintable(QString::fromUtf8("wrong player 0")));
    QVERIFY2(resultPlayers[1].compare(QString::fromUtf8("B")) == 0, qPrintable(QString::fromUtf8("wrong player 1")));
    QVERIFY2(resultPlayers[2].compare(QString::fromUtf8("C")) == 0, qPrintable(QString::fromUtf8("wrong player 2")));
    QVERIFY2(resultPlayers[3].compare(QString::fromUtf8("E")) == 0, qPrintable(QString::fromUtf8("wrong player 3")));
    QVERIFY2(resultPlayers[4].compare(QString::fromUtf8("F")) == 0, qPrintable(QString::fromUtf8("wrong player 4")));

    QVERIFY2(resultDealer.compare(QString::fromUtf8("C")) == 0, qPrintable(QString::fromUtf8("wrong dealer")));

    QVERIFY2(resultSitOutScheme.empty(), qPrintable(QString::fromUtf8("wrong size of sit out scheme")));

    QVERIFY2(!playerNameInput5visible, qPrintable(QString::fromUtf8("player name input incorrectly visible")));
    QVERIFY2(!dealerInput5visible, qPrintable(QString::fromUtf8("dealer input incorrectly visible")));
}

void FrontendTest::AfterRaisingPlayerCountAndInteractingCorrectDataShallBeReturned()
{
    // Arrange
    std::vector<std::pair<QString, bool>> players
    {
        std::pair<QString, bool>(QString::fromUtf8("A"), true),
        std::pair<QString, bool>(QString::fromUtf8("B"), true),
        std::pair<QString, bool>(QString::fromUtf8("C"), true),
        std::pair<QString, bool>(QString::fromUtf8("E"), true),
        std::pair<QString, bool>(QString::fromUtf8("F"), true),
        std::pair<QString, bool>(QString::fromUtf8("G"), true),
        std::pair<QString, bool>(QString::fromUtf8("D"), false)
    };

    QString dealer = QString::fromUtf8("C");
    std::set<unsigned int> sitOutScheme
    {
        0,
        3
    };

    Ui::PlayerSelection ps(this->DefaultPlayers, players, dealer, sitOutScheme, nullptr);
    ps.setModal(true);
    ps.show();

    QSignalSpy acceptButtonSpy(ps.dialogAcceptButton, &QPushButton::clicked);

    bool playerNameInput6visible = false;
    bool dealerInput6visible = false;

    // Act
    QTimer::singleShot(this->SingleShotInterval, this, [&]()
    {
        ps.dialogNumberOfPresentPlayers->clear();
        QTest::keyClicks(ps.dialogNumberOfPresentPlayers, QString::fromUtf8("7"));
        playerNameInput6visible = ps.dialogNames[6]->isVisible();
        dealerInput6visible = ps.dealerButtons[6]->isVisible();

        ps.dialogNames[0]->clear();
        ps.dialogNames[1]->clear();
        ps.dialogNames[2]->clear();
        ps.dialogNames[3]->clear();
        ps.dialogNames[4]->clear();
        ps.dialogNames[5]->clear();
        ps.dialogNames[6]->clear();
        QTest::keyClicks(ps.dialogNames[0], QString::fromUtf8("J"));
        QTest::keyClicks(ps.dialogNames[1], QString::fromUtf8("K"));
        QTest::keyClicks(ps.dialogNames[2], QString::fromUtf8("L"));
        QTest::keyClicks(ps.dialogNames[3], QString::fromUtf8("M"));
        QTest::keyClicks(ps.dialogNames[4], QString::fromUtf8("N"));
        QTest::keyClicks(ps.dialogNames[5], QString::fromUtf8("O"));
        QTest::keyClicks(ps.dialogNames[6], QString::fromUtf8("P"));

        QTest::mouseClick(ps.dealerButtons[2], Qt::LeftButton);

        QTest::mouseClick(ps.dialogAcceptButton, Qt::LeftButton);
    });

    int dialogCode = ps.exec();

    acceptButtonSpy.wait(this->WaitingInterval);

    auto result = ps.GetResults();

    // Assert
    QVERIFY2(acceptButtonSpy.count() == 1, qPrintable(QString::fromUtf8("accept button spy did not register signal")));
    QVERIFY2(dialogCode == QDialog::Accepted, qPrintable(QString::fromUtf8("dialog does not report accepted")));

    auto resultPlayers = std::get<0>(result);
    auto resultDealer = std::get<1>(result);
    auto resultSitOutScheme = std::get<2>(result);

    QVERIFY2(resultPlayers.size() == 7, qPrintable(QString::fromUtf8("incorrect result players size")));
    QVERIFY2(resultPlayers[0].compare(QString::fromUtf8("J")) == 0, qPrintable(QString::fromUtf8("wrong player 0")));
    QVERIFY2(resultPlayers[1].compare(QString::fromUtf8("K")) == 0, qPrintable(QString::fromUtf8("wrong player 1")));
    QVERIFY2(resultPlayers[2].compare(QString::fromUtf8("L")) == 0, qPrintable(QString::fromUtf8("wrong player 2")));
    QVERIFY2(resultPlayers[3].compare(QString::fromUtf8("M")) == 0, qPrintable(QString::fromUtf8("wrong player 3")));
    QVERIFY2(resultPlayers[4].compare(QString::fromUtf8("N")) == 0, qPrintable(QString::fromUtf8("wrong player 4")));
    QVERIFY2(resultPlayers[5].compare(QString::fromUtf8("O")) == 0, qPrintable(QString::fromUtf8("wrong player 5")));
    QVERIFY2(resultPlayers[6].compare(QString::fromUtf8("P")) == 0, qPrintable(QString::fromUtf8("wrong player 6")));

    QVERIFY2(resultDealer.compare(QString::fromUtf8("L")) == 0, qPrintable(QString::fromUtf8("wrong dealer")));

    QVERIFY2(resultSitOutScheme.size() == 2, qPrintable(QString::fromUtf8("wrong size of sit out scheme")));
    QVERIFY2(resultSitOutScheme.count(3) == 1, qPrintable(QString::fromUtf8("wrong concent of sit out scheme")));
    QVERIFY2(resultSitOutScheme.count(4) == 1, qPrintable(QString::fromUtf8("wrong concent of sit out scheme")));

    QVERIFY2(playerNameInput6visible, qPrintable(QString::fromUtf8("player name input incorrectly invisible")));
    QVERIFY2(dealerInput6visible, qPrintable(QString::fromUtf8("dealer input incorrectly invisible")));
}

#endif // _USE_LONG_TEST

QTEST_MAIN(FrontendTest)

#include "tst_playerselection.moc"
