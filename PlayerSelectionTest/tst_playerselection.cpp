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
        std::pair<QString, bool>(QString("D"), false),
        std::pair<QString, bool>(QString("E"), true),
        std::pair<QString, bool>(QString("F"), true),
        std::pair<QString, bool>(QString("G"), true)
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

QTEST_MAIN(FrontendTest)

#include "tst_playerselection.moc"
