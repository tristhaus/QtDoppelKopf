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

#ifndef TST_PLAYERINFO_H
#define TST_PLAYERINFO_H

#include <gtest/gtest.h>
#include "../Backend/gameinfo.h"
#include "../Backend/playerinfo.h"

TEST(BackendTest, PlayerInfoAndGameInfoShallProvideCorrectScoresAndCashBalance)
{
    // Arrange
    Backend::GameInfo gameInfo;

    // Act, Assert
    gameInfo.SetPlayers(std::vector<std::wstring>{L"A", L"B", L"C", L"D", L"E"}, L"A", std::set<unsigned int> {});
    std::vector<std::shared_ptr<Backend::PlayerInfo>> playerInfos(gameInfo.PlayerInfos());

    EXPECT_STREQ(L"A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ(L"B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ(L"C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ(L"D", playerInfos[3]->Name().c_str());
    EXPECT_STREQ(L"E", playerInfos[4]->Name().c_str());

    EXPECT_FALSE(playerInfos[0]->ParticipatedInLastDeal());
    EXPECT_FALSE(playerInfos[1]->ParticipatedInLastDeal());
    EXPECT_FALSE(playerInfos[2]->ParticipatedInLastDeal());
    EXPECT_FALSE(playerInfos[3]->ParticipatedInLastDeal());
    EXPECT_FALSE(playerInfos[4]->ParticipatedInLastDeal());

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"B", -2),
                          std::make_pair<std::wstring, int>(L"C", 2),
                          std::make_pair<std::wstring, int>(L"D", -2),
                          std::make_pair<std::wstring, int>(L"E", 2)
                      }, 0u);

    EXPECT_EQ( 0, playerInfos[0]->CurrentScore());
    EXPECT_EQ(-2, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 2, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-2, playerInfos[3]->CurrentScore());
    EXPECT_EQ( 2, playerInfos[4]->CurrentScore());

    EXPECT_EQ( 1, playerInfos[0]->CashCents());
    EXPECT_EQ( 2, playerInfos[1]->CashCents());
    EXPECT_EQ( 0, playerInfos[2]->CashCents());
    EXPECT_EQ( 2, playerInfos[3]->CashCents());
    EXPECT_EQ( 0, playerInfos[4]->CashCents());

    EXPECT_FALSE(playerInfos[0]->ParticipatedInLastDeal());
    EXPECT_TRUE(playerInfos[1]->ParticipatedInLastDeal());
    EXPECT_TRUE(playerInfos[2]->ParticipatedInLastDeal());
    EXPECT_TRUE(playerInfos[3]->ParticipatedInLastDeal());
    EXPECT_TRUE(playerInfos[4]->ParticipatedInLastDeal());

    EXPECT_EQ(-2, playerInfos[1]->ScoreInLastDeal());
    EXPECT_EQ( 2, playerInfos[2]->ScoreInLastDeal());
    EXPECT_EQ(-2, playerInfos[3]->ScoreInLastDeal());
    EXPECT_EQ( 2, playerInfos[4]->ScoreInLastDeal());

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"A", -3),
                          std::make_pair<std::wstring, int>(L"C", 1),
                          std::make_pair<std::wstring, int>(L"D", 1),
                          std::make_pair<std::wstring, int>(L"E", 1)
                      }, 0u);

    EXPECT_EQ(-3, playerInfos[0]->CurrentScore());
    EXPECT_EQ(-2, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 3, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[3]->CurrentScore());
    EXPECT_EQ( 3, playerInfos[4]->CurrentScore());

    EXPECT_EQ( 3, playerInfos[0]->CashCents());
    EXPECT_EQ( 2, playerInfos[1]->CashCents());
    EXPECT_EQ( 0, playerInfos[2]->CashCents());
    EXPECT_EQ( 2, playerInfos[3]->CashCents());
    EXPECT_EQ( 0, playerInfos[4]->CashCents());

    EXPECT_TRUE(playerInfos[0]->ParticipatedInLastDeal());
    EXPECT_FALSE(playerInfos[1]->ParticipatedInLastDeal());
    EXPECT_TRUE(playerInfos[2]->ParticipatedInLastDeal());
    EXPECT_TRUE(playerInfos[3]->ParticipatedInLastDeal());
    EXPECT_TRUE(playerInfos[4]->ParticipatedInLastDeal());

    EXPECT_EQ(-3, playerInfos[0]->ScoreInLastDeal());
    EXPECT_EQ( 1, playerInfos[2]->ScoreInLastDeal());
    EXPECT_EQ( 1, playerInfos[3]->ScoreInLastDeal());
    EXPECT_EQ( 1, playerInfos[4]->ScoreInLastDeal());

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"A", -2),
                          std::make_pair<std::wstring, int>(L"B", -2),
                          std::make_pair<std::wstring, int>(L"D", 6),
                          std::make_pair<std::wstring, int>(L"E", -2)
                      }, 0u);

    EXPECT_EQ(-5, playerInfos[0]->CurrentScore());
    EXPECT_EQ(-4, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 3, playerInfos[2]->CurrentScore());
    EXPECT_EQ( 5, playerInfos[3]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[4]->CurrentScore());

    EXPECT_EQ( 5, playerInfos[0]->CashCents());
    EXPECT_EQ( 4, playerInfos[1]->CashCents());
    EXPECT_EQ( 1, playerInfos[2]->CashCents());
    EXPECT_EQ( 0, playerInfos[3]->CashCents());
    EXPECT_EQ( 2, playerInfos[4]->CashCents());

    EXPECT_TRUE(playerInfos[0]->ParticipatedInLastDeal());
    EXPECT_TRUE(playerInfos[1]->ParticipatedInLastDeal());
    EXPECT_FALSE(playerInfos[2]->ParticipatedInLastDeal());
    EXPECT_TRUE(playerInfos[3]->ParticipatedInLastDeal());
    EXPECT_TRUE(playerInfos[4]->ParticipatedInLastDeal());

    EXPECT_EQ(-2, playerInfos[0]->ScoreInLastDeal());
    EXPECT_EQ(-2, playerInfos[1]->ScoreInLastDeal());
    EXPECT_EQ( 6, playerInfos[3]->ScoreInLastDeal());
    EXPECT_EQ(-2, playerInfos[4]->ScoreInLastDeal());
}

TEST(BackendTest, PlayerInfoAndGameInfoShallAutoCompleteChanges)
{
    // Arrange
    Backend::GameInfo gameInfo;

    // Act, Assert
    gameInfo.SetPlayers(std::vector<std::wstring>{L"A", L"B", L"C", L"D", L"E"}, L"A", std::set<unsigned int> {});
    std::vector<std::shared_ptr<Backend::PlayerInfo>> playerInfos(gameInfo.PlayerInfos());

    EXPECT_STREQ(L"A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ(L"B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ(L"C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ(L"D", playerInfos[3]->Name().c_str());
    EXPECT_STREQ(L"E", playerInfos[4]->Name().c_str());

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"B", -2),
                          std::make_pair<std::wstring, int>(L"D", -2),
                      }, 0u);

    EXPECT_EQ( 0, playerInfos[0]->CurrentScore());
    EXPECT_EQ(-2, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 2, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-2, playerInfos[3]->CurrentScore());
    EXPECT_EQ( 2, playerInfos[4]->CurrentScore());

    EXPECT_FALSE(playerInfos[0]->ParticipatedInLastDeal());
    EXPECT_TRUE(playerInfos[1]->ParticipatedInLastDeal());
    EXPECT_TRUE(playerInfos[2]->ParticipatedInLastDeal());
    EXPECT_TRUE(playerInfos[3]->ParticipatedInLastDeal());
    EXPECT_TRUE(playerInfos[4]->ParticipatedInLastDeal());

    EXPECT_EQ(-2, playerInfos[1]->ScoreInLastDeal());
    EXPECT_EQ( 2, playerInfos[2]->ScoreInLastDeal());
    EXPECT_EQ(-2, playerInfos[3]->ScoreInLastDeal());
    EXPECT_EQ( 2, playerInfos[4]->ScoreInLastDeal());

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"C", 1),
                          std::make_pair<std::wstring, int>(L"D", 1),
                          std::make_pair<std::wstring, int>(L"E", 1)
                      }, 0u);

    EXPECT_EQ(-3, playerInfos[0]->CurrentScore());
    EXPECT_EQ(-2, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 3, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[3]->CurrentScore());
    EXPECT_EQ( 3, playerInfos[4]->CurrentScore());

    EXPECT_TRUE(playerInfos[0]->ParticipatedInLastDeal());
    EXPECT_FALSE(playerInfos[1]->ParticipatedInLastDeal());
    EXPECT_TRUE(playerInfos[2]->ParticipatedInLastDeal());
    EXPECT_TRUE(playerInfos[3]->ParticipatedInLastDeal());
    EXPECT_TRUE(playerInfos[4]->ParticipatedInLastDeal());

    EXPECT_EQ(-3, playerInfos[0]->ScoreInLastDeal());
    EXPECT_EQ( 1, playerInfos[2]->ScoreInLastDeal());
    EXPECT_EQ( 1, playerInfos[3]->ScoreInLastDeal());
    EXPECT_EQ( 1, playerInfos[4]->ScoreInLastDeal());

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"D", 6),
                      }, 0u);

    EXPECT_EQ(-5, playerInfos[0]->CurrentScore());
    EXPECT_EQ(-4, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 3, playerInfos[2]->CurrentScore());
    EXPECT_EQ( 5, playerInfos[3]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[4]->CurrentScore());

    EXPECT_TRUE(playerInfos[0]->ParticipatedInLastDeal());
    EXPECT_TRUE(playerInfos[1]->ParticipatedInLastDeal());
    EXPECT_FALSE(playerInfos[2]->ParticipatedInLastDeal());
    EXPECT_TRUE(playerInfos[3]->ParticipatedInLastDeal());
    EXPECT_TRUE(playerInfos[4]->ParticipatedInLastDeal());

    EXPECT_EQ(-2, playerInfos[0]->ScoreInLastDeal());
    EXPECT_EQ(-2, playerInfos[1]->ScoreInLastDeal());
    EXPECT_EQ( 6, playerInfos[3]->ScoreInLastDeal());
    EXPECT_EQ(-2, playerInfos[4]->ScoreInLastDeal());

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"E", -9),
                      }, 0u);

    EXPECT_EQ(-2, playerInfos[0]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 6, playerInfos[2]->CurrentScore());
    EXPECT_EQ( 5, playerInfos[3]->CurrentScore());
    EXPECT_EQ(-8, playerInfos[4]->CurrentScore());

    EXPECT_TRUE(playerInfos[0]->ParticipatedInLastDeal());
    EXPECT_TRUE(playerInfos[1]->ParticipatedInLastDeal());
    EXPECT_TRUE(playerInfos[2]->ParticipatedInLastDeal());
    EXPECT_FALSE(playerInfos[3]->ParticipatedInLastDeal());
    EXPECT_TRUE(playerInfos[4]->ParticipatedInLastDeal());

    EXPECT_EQ( 3, playerInfos[0]->ScoreInLastDeal());
    EXPECT_EQ( 3, playerInfos[1]->ScoreInLastDeal());
    EXPECT_EQ( 3, playerInfos[2]->ScoreInLastDeal());
    EXPECT_EQ(-9, playerInfos[4]->ScoreInLastDeal());
}

TEST(BackendTest, PlayerInfoAndGameInfoShallThrowOnPushingChangesThatCannotBeCompleted)
{
    // Arrange
    Backend::GameInfo gameInfo;
    std::set<unsigned int> emptySitOutScheme;
    gameInfo.SetPlayers({L"A", L"B", L"C", L"D"}, L"A", emptySitOutScheme);

    // Act, Assert
    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"B", 0),
                      }, 0u);

    gameInfo.SetPlayers({L"A", L"B", L"C", L"D"}, L"A", emptySitOutScheme);

    EXPECT_THROW({
        try
        {
            gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                         {
                             std::make_pair<std::wstring, int>(L"B", -2),
                             std::make_pair<std::wstring, int>(L"C", 2)
                         }, 0u);
        }
        catch( const std::exception& e )
        {
            EXPECT_STREQ("unable to complete the changes from the information given", e.what());
            throw;
        }
    }, std::exception);

    EXPECT_THROW({
        try
        {
            gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                         {
                             std::make_pair<std::wstring, int>(L"B", 1),
                             std::make_pair<std::wstring, int>(L"C", 2)
                         }, 0u);
        }
        catch( const std::exception& e )
        {
            EXPECT_STREQ("unable to complete the changes from the information given", e.what());
            throw;
        }
    }, std::exception);

    EXPECT_THROW({
        try
        {
            gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                         {
                             std::make_pair<std::wstring, int>(L"B", -2),
                             std::make_pair<std::wstring, int>(L"C", 2),
                             std::make_pair<std::wstring, int>(L"A", 2),
                             std::make_pair<std::wstring, int>(L"D", 2),
                             std::make_pair<std::wstring, int>(L"E", 2)
                         }, 0u);
        }
        catch( const std::exception& e )
        {
            EXPECT_STREQ("there can never be more than 4 or zero changes", e.what());
            throw;
        }
    }, std::exception);
}

#endif // TST_PLAYERINFO_H
