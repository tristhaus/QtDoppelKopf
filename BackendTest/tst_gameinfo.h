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

#ifndef TST_GAMEINFO_H
#define TST_GAMEINFO_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../Backend/gameinfo.h"
#include <memory>

TEST(BackendTest, GameInfoShallReportPlayersIncludingPresenceAndPlayingAfterSetting)
{
    // Arrange
    Backend::GameInfo gameInfo;
    std::set<unsigned int> sitOutScheme;

    // Act, Assert
    gameInfo.SetPlayers(std::vector<std::wstring>{L"A", L"B", L"C", L"D"}, L"A", sitOutScheme);
    std::vector<std::shared_ptr<Backend::PlayerInfo>> one(gameInfo.PlayerInfos());

    EXPECT_STREQ(L"A", one[0]->Name().c_str());
    EXPECT_STREQ(L"B", one[1]->Name().c_str());
    EXPECT_STREQ(L"C", one[2]->Name().c_str());
    EXPECT_STREQ(L"D", one[3]->Name().c_str());
    EXPECT_TRUE(one[0]->IsPresent());
    EXPECT_TRUE(one[1]->IsPresent());
    EXPECT_TRUE(one[2]->IsPresent());
    EXPECT_TRUE(one[3]->IsPresent());
    EXPECT_TRUE(one[0]->IsPlaying());
    EXPECT_TRUE(one[1]->IsPlaying());
    EXPECT_TRUE(one[2]->IsPlaying());
    EXPECT_TRUE(one[3]->IsPlaying());
    EXPECT_FALSE(gameInfo.CanPopLastEntry());

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"A", 0),
                          std::make_pair<std::wstring, int>(L"B", 0),
                          std::make_pair<std::wstring, int>(L"C", 0),
                          std::make_pair<std::wstring, int>(L"D", 0)
                      }, 0u);

    EXPECT_TRUE(gameInfo.CanPopLastEntry());

    gameInfo.SetPlayers(std::vector<std::wstring>{L"A", L"B", L"E", L"C", L"D"}, L"B", sitOutScheme);
    std::vector<std::shared_ptr<Backend::PlayerInfo>> two(gameInfo.PlayerInfos());

    EXPECT_STREQ(L"A", two[0]->Name().c_str());
    EXPECT_STREQ(L"B", two[1]->Name().c_str());
    EXPECT_STREQ(L"E", two[2]->Name().c_str());
    EXPECT_STREQ(L"C", two[3]->Name().c_str());
    EXPECT_STREQ(L"D", two[4]->Name().c_str());
    EXPECT_TRUE(two[0]->IsPresent());
    EXPECT_TRUE(two[1]->IsPresent());
    EXPECT_TRUE(two[2]->IsPresent());
    EXPECT_TRUE(two[3]->IsPresent());
    EXPECT_TRUE(two[4]->IsPresent());
    EXPECT_TRUE(two[0]->IsPlaying());
    EXPECT_FALSE(two[1]->IsPlaying());
    EXPECT_TRUE(two[2]->IsPlaying());
    EXPECT_TRUE(two[3]->IsPlaying());
    EXPECT_TRUE(two[4]->IsPlaying());
    EXPECT_FALSE(gameInfo.CanPopLastEntry());

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"E", 0),
                          std::make_pair<std::wstring, int>(L"C", 0),
                          std::make_pair<std::wstring, int>(L"D", 0),
                          std::make_pair<std::wstring, int>(L"A", 0)
                      }, 0u);

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"C", 0),
                          std::make_pair<std::wstring, int>(L"D", 0),
                          std::make_pair<std::wstring, int>(L"A", 0),
                          std::make_pair<std::wstring, int>(L"B", 0)
                      }, 0u);

    EXPECT_TRUE(gameInfo.CanPopLastEntry());

    gameInfo.SetPlayers(std::vector<std::wstring>{L"A", L"E", L"C", L"D"}, L"E", sitOutScheme);
    std::vector<std::shared_ptr<Backend::PlayerInfo>> three(gameInfo.PlayerInfos());

    EXPECT_STREQ(L"A", three[0]->Name().c_str());
    EXPECT_STREQ(L"E", three[1]->Name().c_str());
    EXPECT_STREQ(L"C", three[2]->Name().c_str());
    EXPECT_STREQ(L"D", three[3]->Name().c_str());
    EXPECT_STREQ(L"B", three[4]->Name().c_str());
    EXPECT_TRUE(three[0]->IsPresent());
    EXPECT_TRUE(three[1]->IsPresent());
    EXPECT_TRUE(three[2]->IsPresent());
    EXPECT_TRUE(three[3]->IsPresent());
    EXPECT_FALSE(three[4]->IsPresent());
    EXPECT_TRUE(three[0]->IsPlaying());
    EXPECT_TRUE(three[1]->IsPlaying());
    EXPECT_TRUE(three[2]->IsPlaying());
    EXPECT_TRUE(three[3]->IsPlaying());
    EXPECT_FALSE(three[4]->IsPlaying());
    EXPECT_FALSE(gameInfo.CanPopLastEntry());

    gameInfo.SetPlayers(std::vector<std::wstring>{L"A", L"E", L"F", L"C"}, L"F", sitOutScheme);
    std::vector<std::shared_ptr<Backend::PlayerInfo>> four(gameInfo.PlayerInfos());

    EXPECT_STREQ(L"A", four[0]->Name().c_str());
    EXPECT_STREQ(L"E", four[1]->Name().c_str());
    EXPECT_STREQ(L"F", four[2]->Name().c_str());
    EXPECT_STREQ(L"C", four[3]->Name().c_str());
    EXPECT_TRUE(std::wcscmp(L"B", four[4]->Name().c_str()) == 0 || std::wcscmp(L"B", four[5]->Name().c_str()) == 0);
    EXPECT_TRUE(std::wcscmp(L"D", four[4]->Name().c_str()) == 0 || std::wcscmp(L"D", four[5]->Name().c_str()) == 0);
    EXPECT_TRUE(four[0]->IsPresent());
    EXPECT_TRUE(four[1]->IsPresent());
    EXPECT_TRUE(four[2]->IsPresent());
    EXPECT_TRUE(four[3]->IsPresent());
    EXPECT_FALSE(four[4]->IsPresent());
    EXPECT_FALSE(four[5]->IsPresent());
    EXPECT_TRUE(four[0]->IsPlaying());
    EXPECT_TRUE(four[1]->IsPlaying());
    EXPECT_TRUE(four[2]->IsPlaying());
    EXPECT_TRUE(four[3]->IsPlaying());
    EXPECT_FALSE(four[4]->IsPlaying());
    EXPECT_FALSE(four[5]->IsPlaying());
    EXPECT_FALSE(gameInfo.CanPopLastEntry());
}

TEST(BackendTest, GameInfoShallThrowOnSettingBadPlayerNames)
{
    // Arrange
    Backend::GameInfo gameInfo;
    std::set<unsigned int> emptySitOutScheme;

    // Act, Assert
    gameInfo.SetPlayers({L"A", L"B", L"C", L"D", L"E", L"F", L"G"}, L"A", std::set<unsigned int> { 3u, 5u });

    EXPECT_THROW({
        try
        {
            gameInfo.SetPlayers({L"A", L"B", L"C"}, L"A", emptySitOutScheme);
        }
        catch( const std::exception& e )
        {
            EXPECT_STREQ("not enough players", e.what());
            throw;
        }
    }, std::exception);

    EXPECT_THROW({
        try
        {
            gameInfo.SetPlayers({L"A", L"B", L"A", L"D"}, L"A", emptySitOutScheme);
        }
        catch( const std::exception& e )
        {
            EXPECT_STREQ("names must be unique", e.what());
            throw;
        }
    }, std::exception );

    EXPECT_THROW({
        try
        {
            gameInfo.SetPlayers({L"A", L"B", L"C", L"D"}, L"Z", emptySitOutScheme);
        }
        catch( const std::exception& e )
        {
            EXPECT_STREQ("name of dealer must be among the players", e.what());
            throw;
        }
    }, std::exception );

    gameInfo.SetPlayers({L"A", L"B", L"C", L"D", L"E"}, L"A", emptySitOutScheme);

    EXPECT_THROW({
        try
        {
            gameInfo.SetPlayers({L"A", L"B", L"C", L"D", L"E", L"F", L"G"}, L"A", std::set<unsigned int> { 3u });
        }
        catch( const std::exception& e )
        {
            EXPECT_STREQ("incorrect size of the sit out scheme", e.what());
            throw;
        }
    }, std::exception );
}

TEST(BackendTest, GameInfoShallAdvanceDealerWhenPushingChanges)
{
    // Arrange
    Backend::GameInfo gameInfo;

    // Act, Assert
    gameInfo.SetPlayers(std::vector<std::wstring>{L"A", L"B", L"C", L"D", L"E", L"F"}, L"A", std::set<unsigned int> { 3 });
    std::vector<std::shared_ptr<Backend::PlayerInfo>> one(gameInfo.PlayerInfos());

    EXPECT_STREQ(L"A", one[0]->Name().c_str());
    EXPECT_STREQ(L"B", one[1]->Name().c_str());
    EXPECT_STREQ(L"C", one[2]->Name().c_str());
    EXPECT_STREQ(L"D", one[3]->Name().c_str());
    EXPECT_STREQ(L"E", one[4]->Name().c_str());
    EXPECT_STREQ(L"F", one[5]->Name().c_str());
    EXPECT_TRUE(one[0]->IsPresent());
    EXPECT_TRUE(one[1]->IsPresent());
    EXPECT_TRUE(one[2]->IsPresent());
    EXPECT_TRUE(one[3]->IsPresent());
    EXPECT_TRUE(one[4]->IsPresent());
    EXPECT_TRUE(one[5]->IsPresent());
    EXPECT_FALSE(one[0]->IsPlaying());
    EXPECT_TRUE(one[1]->IsPlaying());
    EXPECT_TRUE(one[2]->IsPlaying());
    EXPECT_FALSE(one[3]->IsPlaying());
    EXPECT_TRUE(one[4]->IsPlaying());
    EXPECT_TRUE(one[5]->IsPlaying());
    EXPECT_FALSE(gameInfo.CanPopLastEntry());

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"B", 0),
                          std::make_pair<std::wstring, int>(L"C", 0),
                          std::make_pair<std::wstring, int>(L"E", 0),
                          std::make_pair<std::wstring, int>(L"F", 0)
                      }, 0u);

    std::vector<std::shared_ptr<Backend::PlayerInfo>> two(gameInfo.PlayerInfos());

    EXPECT_STREQ(L"A", two[0]->Name().c_str());
    EXPECT_STREQ(L"B", two[1]->Name().c_str());
    EXPECT_STREQ(L"C", two[2]->Name().c_str());
    EXPECT_STREQ(L"D", two[3]->Name().c_str());
    EXPECT_STREQ(L"E", two[4]->Name().c_str());
    EXPECT_STREQ(L"F", two[5]->Name().c_str());
    EXPECT_TRUE(two[0]->IsPresent());
    EXPECT_TRUE(two[1]->IsPresent());
    EXPECT_TRUE(two[2]->IsPresent());
    EXPECT_TRUE(two[3]->IsPresent());
    EXPECT_TRUE(two[4]->IsPresent());
    EXPECT_TRUE(two[5]->IsPresent());
    EXPECT_TRUE(two[0]->IsPlaying());
    EXPECT_FALSE(two[1]->IsPlaying());
    EXPECT_TRUE(two[2]->IsPlaying());
    EXPECT_TRUE(two[3]->IsPlaying());
    EXPECT_FALSE(two[4]->IsPlaying());
    EXPECT_TRUE(two[5]->IsPlaying());
    EXPECT_TRUE(gameInfo.CanPopLastEntry());

    gameInfo.SetPlayers(std::vector<std::wstring>{L"A", L"C", L"D", L"E", L"F"}, L"F", std::set<unsigned int> {});
    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"A", 0),
                          std::make_pair<std::wstring, int>(L"C", 0),
                          std::make_pair<std::wstring, int>(L"D", 0),
                          std::make_pair<std::wstring, int>(L"E", 0)
                      }, 0u);

    std::vector<std::shared_ptr<Backend::PlayerInfo>> three(gameInfo.PlayerInfos());

    EXPECT_STREQ(L"A", three[0]->Name().c_str());
    EXPECT_STREQ(L"C", three[1]->Name().c_str());
    EXPECT_STREQ(L"D", three[2]->Name().c_str());
    EXPECT_STREQ(L"E", three[3]->Name().c_str());
    EXPECT_STREQ(L"F", three[4]->Name().c_str());
    EXPECT_STREQ(L"B", three[5]->Name().c_str());
    EXPECT_TRUE(three[0]->IsPresent());
    EXPECT_TRUE(three[1]->IsPresent());
    EXPECT_TRUE(three[2]->IsPresent());
    EXPECT_TRUE(three[3]->IsPresent());
    EXPECT_TRUE(three[4]->IsPresent());
    EXPECT_FALSE(three[5]->IsPresent());
    EXPECT_FALSE(three[0]->IsPlaying());
    EXPECT_TRUE(three[1]->IsPlaying());
    EXPECT_TRUE(three[2]->IsPlaying());
    EXPECT_TRUE(three[3]->IsPlaying());
    EXPECT_TRUE(three[4]->IsPlaying());
    EXPECT_FALSE(three[5]->IsPlaying());
    EXPECT_TRUE(gameInfo.CanPopLastEntry());

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"C", 0),
                          std::make_pair<std::wstring, int>(L"D", 0),
                          std::make_pair<std::wstring, int>(L"E", 0),
                          std::make_pair<std::wstring, int>(L"F", 0)
                      }, 0u);

    std::vector<std::shared_ptr<Backend::PlayerInfo>> four(gameInfo.PlayerInfos());

    EXPECT_STREQ(L"A", four[0]->Name().c_str());
    EXPECT_STREQ(L"C", four[1]->Name().c_str());
    EXPECT_STREQ(L"D", four[2]->Name().c_str());
    EXPECT_STREQ(L"E", four[3]->Name().c_str());
    EXPECT_STREQ(L"F", four[4]->Name().c_str());
    EXPECT_STREQ(L"B", four[5]->Name().c_str());
    EXPECT_TRUE(four[0]->IsPresent());
    EXPECT_TRUE(four[1]->IsPresent());
    EXPECT_TRUE(four[2]->IsPresent());
    EXPECT_TRUE(four[3]->IsPresent());
    EXPECT_TRUE(four[4]->IsPresent());
    EXPECT_FALSE(four[5]->IsPresent());
    EXPECT_TRUE(four[0]->IsPlaying());
    EXPECT_FALSE(four[1]->IsPlaying());
    EXPECT_TRUE(four[2]->IsPlaying());
    EXPECT_TRUE(four[3]->IsPlaying());
    EXPECT_TRUE(four[4]->IsPlaying());
    EXPECT_FALSE(four[5]->IsPlaying());
    EXPECT_TRUE(gameInfo.CanPopLastEntry());
}

TEST(BackendTest, GameInfoShallThrowOnPushingBadChanges)
{
    // Arrange
    Backend::GameInfo gameInfo;
    std::set<unsigned int> emptySitOutScheme;
    gameInfo.SetPlayers({L"A", L"B", L"C", L"D"}, L"A", emptySitOutScheme);

    // Act, Assert
    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"A", 0),
                          std::make_pair<std::wstring, int>(L"B", 0),
                          std::make_pair<std::wstring, int>(L"C", 0),
                          std::make_pair<std::wstring, int>(L"D", 0)
                      }, 0u);

    EXPECT_THROW({ gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                   {
                       std::make_pair<std::wstring, int>(L"A", 0),
                       std::make_pair<std::wstring, int>(L"B", 0),
                       std::make_pair<std::wstring, int>(L"C", 0),
                       std::make_pair<std::wstring, int>(L"Z", 0)
                   }, 0u);
                 }, std::exception);

    gameInfo.SetPlayers({L"A", L"B", L"C", L"D", L"E"}, L"A", emptySitOutScheme);

    EXPECT_THROW({
        try
        {
            gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                         {
                             std::make_pair<std::wstring, int>(L"A", 0),
                             std::make_pair<std::wstring, int>(L"B", 0),
                             std::make_pair<std::wstring, int>(L"C", 0),
                             std::make_pair<std::wstring, int>(L"E", 0)
                         }, 0u);
        }
        catch( const std::exception& e )
        {
            EXPECT_STREQ("found change for player not playing", e.what());
            throw;
        }
    }, std::exception);

    gameInfo.SetPlayers({L"A", L"B", L"C", L"D", L"E"}, L"E", emptySitOutScheme);

    EXPECT_THROW({
        try
        {
            gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                         {
                             std::make_pair<std::wstring, int>(L"A", 3),
                             std::make_pair<std::wstring, int>(L"B", 3),
                             std::make_pair<std::wstring, int>(L"C", 0),
                             std::make_pair<std::wstring, int>(L"D", -3)
                         }, 0u);
        }
        catch( const std::exception& e )
        {
            EXPECT_STREQ("changes must sum to zero", e.what());
            throw;
        }
    }, std::exception);
}

TEST(BackendTest, GameInfoShallCorrectlyUseMultiplier)
{
    // Arrange
    Backend::GameInfo gameInfo;
    std::set<unsigned int> emptySitOutScheme;
    gameInfo.SetPlayers({L"A", L"B", L"C", L"D"}, L"A", emptySitOutScheme);

    // Act, Assert
    ASSERT_FALSE(gameInfo.CanPopLastEntry());
    ASSERT_EQ(Backend::GameInfo::MandatorySolo::CannotTrigger, gameInfo.MandatorySolo());

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"A", 1),
                          std::make_pair<std::wstring, int>(L"B", 1),
                      }, 1u);

    auto playerInfos = gameInfo.PlayerInfos();

    EXPECT_STREQ(L"A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ(L"B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ(L"C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ(L"D", playerInfos[3]->Name().c_str());

    EXPECT_EQ( 1, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[1]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[3]->CurrentScore());

    auto preview1 = gameInfo.MultiplierPreview();

    EXPECT_EQ(4, preview1[0]);
    EXPECT_EQ(0, preview1[1]);
    EXPECT_EQ(0, preview1[2]);

    EXPECT_EQ(1, gameInfo.LastNumberOfEvents());

    EXPECT_EQ(0, playerInfos[0]->CashCents());
    EXPECT_EQ(0, playerInfos[1]->CashCents());
    EXPECT_EQ(1, playerInfos[2]->CashCents());
    EXPECT_EQ(1, playerInfos[3]->CashCents());
    EXPECT_EQ(2, gameInfo.TotalCashCents());

    ASSERT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"A", 3),
                          std::make_pair<std::wstring, int>(L"C", 3),
                      }, 2u);

    EXPECT_EQ( 7, playerInfos[0]->CurrentScore());
    EXPECT_EQ(-5, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 5, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-7, playerInfos[3]->CurrentScore());

    auto preview2 = gameInfo.MultiplierPreview();

    EXPECT_EQ(0, preview2[0]);
    EXPECT_EQ(1, preview2[1]);
    EXPECT_EQ(3, preview2[2]);

    EXPECT_EQ(2, gameInfo.LastNumberOfEvents());

    EXPECT_EQ(0, playerInfos[0]->CashCents());
    EXPECT_EQ(6, playerInfos[1]->CashCents());
    EXPECT_EQ(1, playerInfos[2]->CashCents());
    EXPECT_EQ(7, playerInfos[3]->CashCents());
    EXPECT_EQ(14 + 4*3, gameInfo.TotalCashCents());

    ASSERT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"C", 2),
                          std::make_pair<std::wstring, int>(L"D", 2),
                      }, 0u);

    EXPECT_EQ( -9, playerInfos[0]->CurrentScore());
    EXPECT_EQ(-21, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 21, playerInfos[2]->CurrentScore());
    EXPECT_EQ(  9, playerInfos[3]->CurrentScore());

    auto preview3 = gameInfo.MultiplierPreview();

    EXPECT_EQ(0, preview3[0]);
    EXPECT_EQ(1, preview3[1]);
    EXPECT_EQ(2, preview3[2]);

    EXPECT_EQ(0, gameInfo.LastNumberOfEvents());

    EXPECT_EQ(15, playerInfos[0]->CashCents());
    EXPECT_EQ(21, playerInfos[1]->CashCents());
    EXPECT_EQ( 0, playerInfos[2]->CashCents());
    EXPECT_EQ( 6, playerInfos[3]->CashCents());
    EXPECT_EQ(42 + 4*10, gameInfo.TotalCashCents());

    ASSERT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());
}

TEST(BackendTest, GameInfoShallCorrectlyReportMultiplier)
{
    // Arrange
    Backend::GameInfo gameInfo;
    std::set<unsigned int> emptySitOutScheme;
    gameInfo.SetPlayers({L"A", L"B", L"C", L"D"}, L"A", emptySitOutScheme);

    // Act, Assert
    ASSERT_FALSE(gameInfo.CanPopLastEntry());
    ASSERT_EQ(Backend::GameInfo::MandatorySolo::CannotTrigger, gameInfo.MandatorySolo());

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"A", 1),
                          std::make_pair<std::wstring, int>(L"B", 1),
                      }, 1u);

    auto playerInfos = gameInfo.PlayerInfos();

    EXPECT_STREQ(L"A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ(L"B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ(L"C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ(L"D", playerInfos[3]->Name().c_str());

    EXPECT_EQ( 1, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[1]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[3]->CurrentScore());

    EXPECT_STREQ(L"1", playerInfos[0]->InputInLastDeal().c_str());
    EXPECT_STREQ(L"1", playerInfos[1]->InputInLastDeal().c_str());
    EXPECT_STREQ( L"", playerInfos[2]->InputInLastDeal().c_str());
    EXPECT_STREQ( L"", playerInfos[3]->InputInLastDeal().c_str());

    ASSERT_TRUE(gameInfo.CanPopLastEntry());

    auto preview1 = gameInfo.MultiplierPreview();

    EXPECT_EQ(4, preview1[0]);
    EXPECT_EQ(0, preview1[1]);
    EXPECT_EQ(0, preview1[2]);

    EXPECT_EQ(1, gameInfo.LastNumberOfEvents());

    ASSERT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"A", 3),
                          std::make_pair<std::wstring, int>(L"C", 3),
                      }, 2u);

    EXPECT_EQ( 7, playerInfos[0]->CurrentScore());
    EXPECT_EQ(-5, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 5, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-7, playerInfos[3]->CurrentScore());

    EXPECT_STREQ(L"3", playerInfos[0]->InputInLastDeal().c_str());
    EXPECT_STREQ( L"", playerInfos[1]->InputInLastDeal().c_str());
    EXPECT_STREQ(L"3", playerInfos[2]->InputInLastDeal().c_str());
    EXPECT_STREQ( L"", playerInfos[3]->InputInLastDeal().c_str());

    ASSERT_TRUE(gameInfo.CanPopLastEntry());

    auto preview2 = gameInfo.MultiplierPreview();

    EXPECT_EQ(0, preview2[0]);
    EXPECT_EQ(1, preview2[1]);
    EXPECT_EQ(3, preview2[2]);

    EXPECT_EQ(2, gameInfo.LastNumberOfEvents());

    ASSERT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());

    gameInfo.PopLastEntry();

    EXPECT_EQ( 1, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[1]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[3]->CurrentScore());

    EXPECT_STREQ(L"1", playerInfos[0]->InputInLastDeal().c_str());
    EXPECT_STREQ(L"1", playerInfos[1]->InputInLastDeal().c_str());
    EXPECT_STREQ( L"", playerInfos[2]->InputInLastDeal().c_str());
    EXPECT_STREQ( L"", playerInfos[3]->InputInLastDeal().c_str());

    auto preview3 = gameInfo.MultiplierPreview();

    EXPECT_EQ(4, preview3[0]);
    EXPECT_EQ(0, preview3[1]);
    EXPECT_EQ(0, preview3[2]);

    EXPECT_EQ(1, gameInfo.LastNumberOfEvents());

    ASSERT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());
}

TEST(BackendTest, GameInfoShallCorrectlyPopDeal)
{
    // Arrange
    Backend::GameInfo gameInfo;
    std::set<unsigned int> emptySitOutScheme;
    gameInfo.SetPlayers({L"A", L"B", L"C", L"D"}, L"A", emptySitOutScheme);

    // Act, Assert
    ASSERT_FALSE(gameInfo.CanPopLastEntry());
    ASSERT_EQ(Backend::GameInfo::MandatorySolo::CannotTrigger, gameInfo.MandatorySolo());

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"A", 1),
                          std::make_pair<std::wstring, int>(L"B", 1),
                      }, 0u);

    auto playerInfos = gameInfo.PlayerInfos();

    EXPECT_STREQ(L"A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ(L"B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ(L"C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ(L"D", playerInfos[3]->Name().c_str());

    EXPECT_EQ( 1, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[1]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[3]->CurrentScore());

    EXPECT_STREQ(L"1", playerInfos[0]->InputInLastDeal().c_str());
    EXPECT_STREQ(L"1", playerInfos[1]->InputInLastDeal().c_str());
    EXPECT_STREQ( L"", playerInfos[2]->InputInLastDeal().c_str());
    EXPECT_STREQ( L"", playerInfos[3]->InputInLastDeal().c_str());

    ASSERT_TRUE(gameInfo.CanPopLastEntry());
    ASSERT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"A", 3),
                          std::make_pair<std::wstring, int>(L"C", 3),
                      }, 0u);

    EXPECT_EQ( 4, playerInfos[0]->CurrentScore());
    EXPECT_EQ(-2, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 2, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-4, playerInfos[3]->CurrentScore());

    EXPECT_STREQ(L"3", playerInfos[0]->InputInLastDeal().c_str());
    EXPECT_STREQ( L"", playerInfos[1]->InputInLastDeal().c_str());
    EXPECT_STREQ(L"3", playerInfos[2]->InputInLastDeal().c_str());
    EXPECT_STREQ( L"", playerInfos[3]->InputInLastDeal().c_str());

    ASSERT_TRUE(gameInfo.CanPopLastEntry());
    ASSERT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());

    gameInfo.PopLastEntry();

    EXPECT_EQ( 1, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[1]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[3]->CurrentScore());

    EXPECT_STREQ(L"1", playerInfos[0]->InputInLastDeal().c_str());
    EXPECT_STREQ(L"1", playerInfos[1]->InputInLastDeal().c_str());
    EXPECT_STREQ( L"", playerInfos[2]->InputInLastDeal().c_str());
    EXPECT_STREQ( L"", playerInfos[3]->InputInLastDeal().c_str());

    ASSERT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());
}

TEST(BackendTest, GameInfoShallHaveCorrectMultiplierAfterPopping)
{
    // Arrange
    Backend::GameInfo gameInfo;
    std::set<unsigned int> sitOutScheme { 3 };
    gameInfo.SetPlayers({L"A", L"B", L"C", L"D", L"E", L"F"}, L"A", sitOutScheme);

    // Act, Assert
    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"B", 1),
                          std::make_pair<std::wstring, int>(L"C", 1),
                      }, 1u);

    auto playerInfos = gameInfo.PlayerInfos();

    EXPECT_STREQ(L"A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ(L"B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ(L"C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ(L"D", playerInfos[3]->Name().c_str());
    EXPECT_STREQ(L"E", playerInfos[4]->Name().c_str());
    EXPECT_STREQ(L"F", playerInfos[5]->Name().c_str());

    EXPECT_EQ( 0, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[2]->CurrentScore());
    EXPECT_EQ( 0, playerInfos[3]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[4]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[5]->CurrentScore());

    auto preview1 = gameInfo.MultiplierPreview();
    EXPECT_EQ(6, preview1[0]);
    EXPECT_EQ(0, preview1[1]);
    EXPECT_EQ(0, preview1[2]);

    EXPECT_EQ( 0, playerInfos[0]->CashCents());
    EXPECT_EQ( 0, playerInfos[1]->CashCents());
    EXPECT_EQ( 0, playerInfos[2]->CashCents());
    EXPECT_EQ( 0, playerInfos[3]->CashCents());
    EXPECT_EQ( 1, playerInfos[4]->CashCents());
    EXPECT_EQ( 1, playerInfos[5]->CashCents());
    EXPECT_EQ( 2, gameInfo.TotalCashCents());

    ASSERT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"A", 2),
                          std::make_pair<std::wstring, int>(L"C", 2),
                      }, 2u);

    EXPECT_EQ( 4, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 5, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-4, playerInfos[3]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[4]->CurrentScore());
    EXPECT_EQ(-5, playerInfos[5]->CurrentScore());

    auto preview2 = gameInfo.MultiplierPreview();
    EXPECT_EQ(0, preview2[0]);
    EXPECT_EQ(1, preview2[1]);
    EXPECT_EQ(5, preview2[2]);

    EXPECT_EQ( 0, playerInfos[0]->CashCents());
    EXPECT_EQ( 2, playerInfos[1]->CashCents());
    EXPECT_EQ( 0, playerInfos[2]->CashCents());
    EXPECT_EQ( 4, playerInfos[3]->CashCents());
    EXPECT_EQ( 3, playerInfos[4]->CashCents());
    EXPECT_EQ( 5, playerInfos[5]->CashCents());
    EXPECT_EQ(14 + 2*2, gameInfo.TotalCashCents());

    ASSERT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"A", 2),
                          std::make_pair<std::wstring, int>(L"B", 2),
                      }, 0u);

    EXPECT_EQ( 20, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 17, playerInfos[1]->CurrentScore());
    EXPECT_EQ(  5, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-20, playerInfos[3]->CurrentScore());
    EXPECT_EQ(-17, playerInfos[4]->CurrentScore());
    EXPECT_EQ( -5, playerInfos[5]->CurrentScore());

    auto preview3 = gameInfo.MultiplierPreview();
    EXPECT_EQ(0, preview3[0]);
    EXPECT_EQ(1, preview3[1]);
    EXPECT_EQ(4, preview3[2]);

    EXPECT_EQ( 0, playerInfos[0]->CashCents());
    EXPECT_EQ( 1, playerInfos[1]->CashCents());
    EXPECT_EQ( 7, playerInfos[2]->CashCents());
    EXPECT_EQ(20, playerInfos[3]->CashCents());
    EXPECT_EQ(18, playerInfos[4]->CashCents());
    EXPECT_EQ(12, playerInfos[5]->CashCents());
    EXPECT_EQ(58 + 2*10, gameInfo.TotalCashCents());

    EXPECT_THAT(playerInfos[0]->ScoreHistory(), ::testing::ElementsAre( 0,  4,  20));
    EXPECT_THAT(playerInfos[1]->ScoreHistory(), ::testing::ElementsAre( 1,  1,  17));
    EXPECT_THAT(playerInfos[2]->ScoreHistory(), ::testing::ElementsAre( 1,  5,   5));
    EXPECT_THAT(playerInfos[3]->ScoreHistory(), ::testing::ElementsAre( 0, -4, -20));
    EXPECT_THAT(playerInfos[4]->ScoreHistory(), ::testing::ElementsAre(-1, -1, -17));
    EXPECT_THAT(playerInfos[5]->ScoreHistory(), ::testing::ElementsAre(-1, -5,  -5));

    gameInfo.PopLastEntry();

    EXPECT_EQ( 4, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 5, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-4, playerInfos[3]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[4]->CurrentScore());
    EXPECT_EQ(-5, playerInfos[5]->CurrentScore());

    auto preview4 = gameInfo.MultiplierPreview();
    EXPECT_EQ(0, preview4[0]);
    EXPECT_EQ(1, preview4[1]);
    EXPECT_EQ(5, preview4[2]);

    EXPECT_EQ( 0, playerInfos[0]->CashCents());
    EXPECT_EQ( 2, playerInfos[1]->CashCents());
    EXPECT_EQ( 0, playerInfos[2]->CashCents());
    EXPECT_EQ( 4, playerInfos[3]->CashCents());
    EXPECT_EQ( 3, playerInfos[4]->CashCents());
    EXPECT_EQ( 5, playerInfos[5]->CashCents());
    EXPECT_EQ(14 + 2*2, gameInfo.TotalCashCents());

    EXPECT_THAT(playerInfos[0]->ScoreHistory(), ::testing::ElementsAre( 0,  4));
    EXPECT_THAT(playerInfos[1]->ScoreHistory(), ::testing::ElementsAre( 1,  1));
    EXPECT_THAT(playerInfos[2]->ScoreHistory(), ::testing::ElementsAre( 1,  5));
    EXPECT_THAT(playerInfos[3]->ScoreHistory(), ::testing::ElementsAre( 0, -4));
    EXPECT_THAT(playerInfos[4]->ScoreHistory(), ::testing::ElementsAre(-1, -1));
    EXPECT_THAT(playerInfos[5]->ScoreHistory(), ::testing::ElementsAre(-1, -5));

    ASSERT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());
}

TEST(BackendTest, GameInfoShallUseMultiplierAfterSettingPlayers)
{
    // Arrange
    Backend::GameInfo gameInfo;
    std::set<unsigned int> sitOutScheme { };
    gameInfo.SetPlayers({L"A", L"B", L"C", L"D"}, L"A", sitOutScheme);

    // Act, Assert
    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"B", 1),
                          std::make_pair<std::wstring, int>(L"C", 1),
                      }, 0u);

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"A", 1),
                          std::make_pair<std::wstring, int>(L"C", 1),
                      }, 0u);

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"C", 1),
                          std::make_pair<std::wstring, int>(L"D", 1),
                      }, 1u);


    auto playerInfos = gameInfo.PlayerInfos();

    EXPECT_STREQ(L"A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ(L"B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ(L"C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ(L"D", playerInfos[3]->Name().c_str());

    EXPECT_EQ(-1, playerInfos[0]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 3, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[3]->CurrentScore());

    gameInfo.SetPlayers({L"A", L"B", L"C", L"D", L"E"}, L"D", sitOutScheme);

    playerInfos = gameInfo.PlayerInfos();

    EXPECT_STREQ(L"A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ(L"B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ(L"C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ(L"D", playerInfos[3]->Name().c_str());
    EXPECT_STREQ(L"E", playerInfos[4]->Name().c_str());

    EXPECT_EQ(-1, playerInfos[0]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 3, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[3]->CurrentScore());
    EXPECT_EQ( 0, playerInfos[4]->CurrentScore());

    EXPECT_EQ(4, gameInfo.MultiplierPreview()[0]);
    EXPECT_EQ(0, gameInfo.MultiplierPreview()[1]);
    EXPECT_EQ(0, gameInfo.MultiplierPreview()[2]);

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"C", 1),
                          std::make_pair<std::wstring, int>(L"E", 1),
                      }, 0u);

    EXPECT_EQ(-3, playerInfos[0]->CurrentScore());
    EXPECT_EQ(-3, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 5, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[3]->CurrentScore());
    EXPECT_EQ( 2, playerInfos[4]->CurrentScore());
}

TEST(BackendTest, GameInfoShallProvideCorrectStatistics)
{
    // Arrange
    Backend::GameInfo gameInfo;
    std::set<unsigned int> sitOutScheme {};
    gameInfo.SetPlayers({L"A", L"B", L"C", L"D", L"E"}, L"A", sitOutScheme);

    // Act
    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          /* A */
                          std::make_pair<std::wstring, int>(L"B", -1),
                          std::make_pair<std::wstring, int>(L"C", -1),
                          std::make_pair<std::wstring, int>(L"D",  1),
                          std::make_pair<std::wstring, int>(L"E",  1)
                      }, 0u);

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"A",  3),
                          /* B */
                          std::make_pair<std::wstring, int>(L"C", -1),
                          std::make_pair<std::wstring, int>(L"D", -1),
                          std::make_pair<std::wstring, int>(L"E", -1)
                      }, 1u);

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"A",  2),
                          std::make_pair<std::wstring, int>(L"B",  2),
                          /* C */
                          std::make_pair<std::wstring, int>(L"D",  2),
                          std::make_pair<std::wstring, int>(L"E", -6)
                      }, 0u);

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"A",  3),
                          std::make_pair<std::wstring, int>(L"B", -3),
                          std::make_pair<std::wstring, int>(L"C",  3),
                          /* D */
                          std::make_pair<std::wstring, int>(L"E", -3)
                      }, 0u);

    // Assert
    auto playerInfos = gameInfo.PlayerInfos();

    EXPECT_STREQ(L"A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ(L"B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ(L"C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ(L"D", playerInfos[3]->Name().c_str());
    EXPECT_STREQ(L"E", playerInfos[4]->Name().c_str());

    EXPECT_EQ( 13, playerInfos[0]->CurrentScore());
    EXPECT_EQ( -3, playerInfos[1]->CurrentScore());
    EXPECT_EQ(  4, playerInfos[2]->CurrentScore());
    EXPECT_EQ(  4, playerInfos[3]->CurrentScore());
    EXPECT_EQ(-18, playerInfos[4]->CurrentScore());

    EXPECT_EQ(3, playerInfos[0]->NumberGamesWon());
    EXPECT_EQ(1, playerInfos[1]->NumberGamesWon());
    EXPECT_EQ(1, playerInfos[2]->NumberGamesWon());
    EXPECT_EQ(2, playerInfos[3]->NumberGamesWon());
    EXPECT_EQ(1, playerInfos[4]->NumberGamesWon());

    EXPECT_EQ(0, playerInfos[0]->NumberGamesLost());
    EXPECT_EQ(2, playerInfos[1]->NumberGamesLost());
    EXPECT_EQ(2, playerInfos[2]->NumberGamesLost());
    EXPECT_EQ(1, playerInfos[3]->NumberGamesLost());
    EXPECT_EQ(3, playerInfos[4]->NumberGamesLost());

    EXPECT_EQ(3, playerInfos[0]->NumberGames());
    EXPECT_EQ(3, playerInfos[1]->NumberGames());
    EXPECT_EQ(3, playerInfos[2]->NumberGames());
    EXPECT_EQ(3, playerInfos[3]->NumberGames());
    EXPECT_EQ(4, playerInfos[4]->NumberGames());

    EXPECT_EQ(1, playerInfos[0]->SolosWon());
    EXPECT_EQ(0, playerInfos[1]->SolosWon());
    EXPECT_EQ(0, playerInfos[2]->SolosWon());
    EXPECT_EQ(0, playerInfos[3]->SolosWon());
    EXPECT_EQ(0, playerInfos[4]->SolosWon());

    EXPECT_EQ(0, playerInfos[0]->SolosLost());
    EXPECT_EQ(0, playerInfos[1]->SolosLost());
    EXPECT_EQ(0, playerInfos[2]->SolosLost());
    EXPECT_EQ(0, playerInfos[3]->SolosLost());
    EXPECT_EQ(1, playerInfos[4]->SolosLost());

    EXPECT_EQ(  3, playerInfos[0]->TotalSoloPoints());
    EXPECT_EQ(  0, playerInfos[1]->TotalSoloPoints());
    EXPECT_EQ(  0, playerInfos[2]->TotalSoloPoints());
    EXPECT_EQ(  0, playerInfos[3]->TotalSoloPoints());
    EXPECT_EQ(-12, playerInfos[4]->TotalSoloPoints());

    EXPECT_EQ(6, playerInfos[0]->MaxSingleWin());
    EXPECT_EQ(4, playerInfos[1]->MaxSingleWin());
    EXPECT_EQ(6, playerInfos[2]->MaxSingleWin());
    EXPECT_EQ(4, playerInfos[3]->MaxSingleWin());
    EXPECT_EQ(1, playerInfos[4]->MaxSingleWin());

    EXPECT_EQ(  0, playerInfos[0]->MaxSingleLoss());
    EXPECT_EQ( -6, playerInfos[1]->MaxSingleLoss());
    EXPECT_EQ( -1, playerInfos[2]->MaxSingleLoss());
    EXPECT_EQ( -1, playerInfos[3]->MaxSingleLoss());
    EXPECT_EQ(-12, playerInfos[4]->MaxSingleLoss());

    EXPECT_EQ( 8, playerInfos[0]->UnmultipliedScore());
    EXPECT_EQ(-2, playerInfos[1]->UnmultipliedScore());
    EXPECT_EQ( 1, playerInfos[2]->UnmultipliedScore());
    EXPECT_EQ( 2, playerInfos[3]->UnmultipliedScore());
    EXPECT_EQ(-9, playerInfos[4]->UnmultipliedScore());

    EXPECT_THAT(playerInfos[0]->ScoreHistory(), ::testing::ElementsAre( 0,  3,   7,  13));
    EXPECT_THAT(playerInfos[1]->ScoreHistory(), ::testing::ElementsAre(-1, -1,   3,  -3));
    EXPECT_THAT(playerInfos[2]->ScoreHistory(), ::testing::ElementsAre(-1, -2,  -2,   4));
    EXPECT_THAT(playerInfos[3]->ScoreHistory(), ::testing::ElementsAre( 1,  0,   4,   4));
    EXPECT_THAT(playerInfos[4]->ScoreHistory(), ::testing::ElementsAre( 1,  0, -12, -18));
}

TEST(BackendTest, GameInfoShallSuspendMultiplierForMandatorySolo)
{
    // Arrange
    Backend::GameInfo gameInfo;
    std::set<unsigned int> sitOutScheme { };
    gameInfo.SetPlayers({L"A", L"B", L"C", L"D"}, L"A", sitOutScheme);

    // Act, Assert
    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"B", 1),
                          std::make_pair<std::wstring, int>(L"C", 1),
                      }, 1u);

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());

    gameInfo.TriggerMandatorySolo();

    auto playerInfos = gameInfo.PlayerInfos();

    EXPECT_STREQ(L"A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ(L"B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ(L"C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ(L"D", playerInfos[3]->Name().c_str());

    EXPECT_EQ(-1, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[3]->CurrentScore());

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Active, gameInfo.MandatorySolo());

    auto preview1 = gameInfo.MultiplierPreview();
    EXPECT_EQ(4, preview1[0]);
    EXPECT_EQ(0, preview1[1]);
    EXPECT_EQ(0, preview1[2]);

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"B", 6),
                      }, 0u);

    EXPECT_EQ(-3, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 7, playerInfos[1]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-3, playerInfos[3]->CurrentScore());

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Active, gameInfo.MandatorySolo());

    auto preview2 = gameInfo.MultiplierPreview();
    EXPECT_EQ(4, preview2[0]);
    EXPECT_EQ(0, preview2[1]);
    EXPECT_EQ(0, preview2[2]);

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"C", -3),
                      }, 0u);

    EXPECT_EQ(-2, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 8, playerInfos[1]->CurrentScore());
    EXPECT_EQ(-4, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-2, playerInfos[3]->CurrentScore());

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Active, gameInfo.MandatorySolo());

    auto preview3 = gameInfo.MultiplierPreview();
    EXPECT_EQ(4, preview3[0]);
    EXPECT_EQ(0, preview3[1]);
    EXPECT_EQ(0, preview3[2]);

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"D", 3),
                      }, 0u);

    EXPECT_EQ(-3, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 7, playerInfos[1]->CurrentScore());
    EXPECT_EQ(-5, playerInfos[2]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[3]->CurrentScore());

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Active, gameInfo.MandatorySolo());

    auto preview4 = gameInfo.MultiplierPreview();
    EXPECT_EQ(4, preview4[0]);
    EXPECT_EQ(0, preview4[1]);
    EXPECT_EQ(0, preview4[2]);

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"A", -9),
                      }, 0u);

    EXPECT_EQ(-12, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 10, playerInfos[1]->CurrentScore());
    EXPECT_EQ( -2, playerInfos[2]->CurrentScore());
    EXPECT_EQ(  4, playerInfos[3]->CurrentScore());

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());

    auto preview5 = gameInfo.MultiplierPreview();
    EXPECT_EQ(4, preview5[0]);
    EXPECT_EQ(0, preview5[1]);
    EXPECT_EQ(0, preview5[2]);

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"B", 5),
                          std::make_pair<std::wstring, int>(L"C", 5),
                      }, 0u);

    EXPECT_EQ(-22, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 20, playerInfos[1]->CurrentScore());
    EXPECT_EQ(  8, playerInfos[2]->CurrentScore());
    EXPECT_EQ( -6, playerInfos[3]->CurrentScore());

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());

    auto preview6 = gameInfo.MultiplierPreview();
    EXPECT_EQ(3, preview6[0]);
    EXPECT_EQ(0, preview6[1]);
    EXPECT_EQ(0, preview6[2]);
}

TEST(BackendTest, GameInfoShallPopMandatorySolo)
{
    // Arrange
    Backend::GameInfo gameInfo;
    std::set<unsigned int> sitOutScheme { };
    gameInfo.SetPlayers({L"A", L"B", L"C", L"D"}, L"A", sitOutScheme);

    // Act, Assert
    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"B", 1),
                          std::make_pair<std::wstring, int>(L"C", 1),
                      }, 1u);

    auto playerInfos = gameInfo.PlayerInfos();

    EXPECT_STREQ(L"A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ(L"B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ(L"C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ(L"D", playerInfos[3]->Name().c_str());

    EXPECT_EQ(-1, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[3]->CurrentScore());

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"B", 1),
                          std::make_pair<std::wstring, int>(L"C", 1),
                      }, 0u);

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());

    EXPECT_EQ(-3, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 3, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 3, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-3, playerInfos[3]->CurrentScore());

    gameInfo.TriggerMandatorySolo();

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Active, gameInfo.MandatorySolo());

    auto preview1 = gameInfo.MultiplierPreview();
    EXPECT_EQ(3, preview1[0]);
    EXPECT_EQ(0, preview1[1]);
    EXPECT_EQ(0, preview1[2]);

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"B", 6),
                      }, 0u);

    EXPECT_EQ(-5, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 9, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-5, playerInfos[3]->CurrentScore());

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Active, gameInfo.MandatorySolo());

    auto preview2 = gameInfo.MultiplierPreview();
    EXPECT_EQ(3, preview2[0]);
    EXPECT_EQ(0, preview2[1]);
    EXPECT_EQ(0, preview2[2]);

    gameInfo.PopLastEntry();

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Active, gameInfo.MandatorySolo());

    auto preview3 = gameInfo.MultiplierPreview();
    EXPECT_EQ(3, preview3[0]);
    EXPECT_EQ(0, preview3[1]);
    EXPECT_EQ(0, preview3[2]);

    gameInfo.PopLastEntry();

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());

    auto preview4 = gameInfo.MultiplierPreview();
    EXPECT_EQ(4, preview4[0]);
    EXPECT_EQ(0, preview4[1]);
    EXPECT_EQ(0, preview4[2]);

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"A", 3),
                          std::make_pair<std::wstring, int>(L"C", 3),
                      }, 0u);

    EXPECT_EQ( 5, playerInfos[0]->CurrentScore());
    EXPECT_EQ(-5, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 7, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-7, playerInfos[3]->CurrentScore());

    auto preview5 = gameInfo.MultiplierPreview();
    EXPECT_EQ(3, preview5[0]);
    EXPECT_EQ(0, preview5[1]);
    EXPECT_EQ(0, preview5[2]);
}

TEST(BackendTest, GameInfoShallThrowOnTriggerMandatorySoloInWrongStates)
{
    // Arrange
    Backend::GameInfo gameInfo;
    std::set<unsigned int> emptySitOutScheme;

    // Act, Assert
    gameInfo.SetPlayers({L"A", L"B", L"C", L"D" }, L"A", emptySitOutScheme);

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::CannotTrigger, gameInfo.MandatorySolo());

    EXPECT_THROW({
        try
        {
            gameInfo.TriggerMandatorySolo();
        }
        catch( const std::exception& e )
        {
            EXPECT_STREQ("cannot trigger mandatory solo at this point", e.what());
            throw;
        }
    }, std::exception);

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"A", 3),
                          std::make_pair<std::wstring, int>(L"C", 3),
                      }, 0u);

    gameInfo.TriggerMandatorySolo();

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Active, gameInfo.MandatorySolo());

    EXPECT_THROW({
        try
        {
            gameInfo.TriggerMandatorySolo();
        }
        catch( const std::exception& e )
        {
            EXPECT_STREQ("cannot trigger mandatory solo at this point", e.what());
            throw;
        }
    }, std::exception);
}

#endif // TST_GAMEINFO_H
