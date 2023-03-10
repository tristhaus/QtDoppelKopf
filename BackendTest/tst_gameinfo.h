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

#include "../Backend/gameinfo.h"
#include "../TestHelper/memoryrepository.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <regex>

TEST(BackendTest, GameInfoShallReportPlayersIncludingPresenceAndPlayingAfterSetting) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    Backend::GameInfo gameInfo(std::make_shared<MemoryRepository>());
    std::set<unsigned int> sitOutScheme;

    // Act, Assert
    gameInfo.SetPlayers(std::vector<std::string>{"A", "B", "C", "D"}, "A", sitOutScheme);
    std::vector<std::shared_ptr<Backend::PlayerInfo>> one(gameInfo.PlayerInfos());

    ASSERT_EQ(4, one.size());
    EXPECT_STREQ("A", one[0]->Name().c_str());
    EXPECT_STREQ("B", one[1]->Name().c_str());
    EXPECT_STREQ("C", one[2]->Name().c_str());
    EXPECT_STREQ("D", one[3]->Name().c_str());
    EXPECT_TRUE(one[0]->IsPresent());
    EXPECT_TRUE(one[1]->IsPresent());
    EXPECT_TRUE(one[2]->IsPresent());
    EXPECT_TRUE(one[3]->IsPresent());
    EXPECT_TRUE(one[0]->IsPlaying());
    EXPECT_TRUE(one[1]->IsPlaying());
    EXPECT_TRUE(one[2]->IsPlaying());
    EXPECT_TRUE(one[3]->IsPlaying());
    EXPECT_EQ(Backend::GameInfo::PoppableEntry::None, gameInfo.LastPoppableEntry());

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("A", 0),
                          std::make_pair<std::string, int>("B", 0),
                          std::make_pair<std::string, int>("C", 0),
                          std::make_pair<std::string, int>("D", 0)
                      }, 0U);

    EXPECT_EQ(Backend::GameInfo::PoppableEntry::Deal, gameInfo.LastPoppableEntry());

    gameInfo.SetPlayers(std::vector<std::string>{"A", "B", "E", "C", "D"}, "B", sitOutScheme);
    std::vector<std::shared_ptr<Backend::PlayerInfo>> two(gameInfo.PlayerInfos());

    ASSERT_EQ(5, two.size());
    EXPECT_STREQ("A", two[0]->Name().c_str());
    EXPECT_STREQ("B", two[1]->Name().c_str());
    EXPECT_STREQ("E", two[2]->Name().c_str());
    EXPECT_STREQ("C", two[3]->Name().c_str());
    EXPECT_STREQ("D", two[4]->Name().c_str());
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
    EXPECT_EQ(Backend::GameInfo::PoppableEntry::PlayersSet, gameInfo.LastPoppableEntry());

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("E", 0),
                          std::make_pair<std::string, int>("C", 0),
                          std::make_pair<std::string, int>("D", 0),
                          std::make_pair<std::string, int>("A", 0)
                      }, 0U);

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("C", 0),
                          std::make_pair<std::string, int>("D", 0),
                          std::make_pair<std::string, int>("A", 0),
                          std::make_pair<std::string, int>("B", 0)
                      }, 0U);

    EXPECT_EQ(Backend::GameInfo::PoppableEntry::Deal, gameInfo.LastPoppableEntry());

    gameInfo.SetPlayers(std::vector<std::string>{"A", "E", "C", "D"}, "E", sitOutScheme);
    std::vector<std::shared_ptr<Backend::PlayerInfo>> three(gameInfo.PlayerInfos());

    ASSERT_EQ(5, three.size());
    EXPECT_STREQ("A", three[0]->Name().c_str());
    EXPECT_STREQ("E", three[1]->Name().c_str());
    EXPECT_STREQ("C", three[2]->Name().c_str());
    EXPECT_STREQ("D", three[3]->Name().c_str());
    EXPECT_STREQ("B", three[4]->Name().c_str());
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
    EXPECT_EQ(Backend::GameInfo::PoppableEntry::PlayersSet, gameInfo.LastPoppableEntry());

    gameInfo.SetPlayers(std::vector<std::string>{"A", "E", "F", "C"}, "F", sitOutScheme);
    std::vector<std::shared_ptr<Backend::PlayerInfo>> four(gameInfo.PlayerInfos());

    ASSERT_EQ(6, four.size());
    EXPECT_STREQ("A", four[0]->Name().c_str());
    EXPECT_STREQ("E", four[1]->Name().c_str());
    EXPECT_STREQ("F", four[2]->Name().c_str());
    EXPECT_STREQ("C", four[3]->Name().c_str());
    EXPECT_TRUE(std::strcmp("B", four[4]->Name().c_str()) == 0 || std::strcmp("B", four[5]->Name().c_str()) == 0);
    EXPECT_TRUE(std::strcmp("D", four[4]->Name().c_str()) == 0 || std::strcmp("D", four[5]->Name().c_str()) == 0);
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
    EXPECT_EQ(Backend::GameInfo::PoppableEntry::PlayersSet, gameInfo.LastPoppableEntry());
}

TEST(BackendTest, GameInfoShallThrowOnSettingBadPlayerNames) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    Backend::GameInfo gameInfo(std::make_shared<MemoryRepository>());
    std::set<unsigned int> emptySitOutScheme;

    // Act, Assert
    gameInfo.SetPlayers({"A", "B", "C", "D", "E", "F", "G"}, "A", std::set<unsigned int> { 3U, 5U });

    EXPECT_THROW( //NOLINT(cppcoreguidelines-avoid-goto, hicpp-avoid-goto)
    {
        try
        {
            gameInfo.SetPlayers({"A", "B", "C"}, "A", emptySitOutScheme);
        }
        catch( const std::exception& e )
        {
            EXPECT_STREQ("not enough players", e.what());
            throw;
        }
    }, std::exception);

    EXPECT_THROW( //NOLINT(cppcoreguidelines-avoid-goto, hicpp-avoid-goto)
    {
        try
        {
            gameInfo.SetPlayers({"A", "B", "A", "D"}, "A", emptySitOutScheme);
        }
        catch( const std::exception& e )
        {
            EXPECT_STREQ("names must be unique, offender: \"A\"", e.what());
            throw;
        }
    }, std::exception );

    EXPECT_THROW( //NOLINT(cppcoreguidelines-avoid-goto, hicpp-avoid-goto)
    {
        try
        {
            gameInfo.SetPlayers({"A", "B", "C", "D"}, "Z", emptySitOutScheme);
        }
        catch( const std::exception& e )
        {
            EXPECT_STREQ("name of dealer must be among the players", e.what());
            throw;
        }
    }, std::exception );

    gameInfo.SetPlayers({"A", "B", "C", "D", "E"}, "A", emptySitOutScheme);

    EXPECT_THROW( //NOLINT(cppcoreguidelines-avoid-goto, hicpp-avoid-goto)
    {
        try
        {
            gameInfo.SetPlayers({"A", "B", "C", "D", "E", "F", "G"}, "A", std::set<unsigned int> { 3U });
        }
        catch( const std::exception& e )
        {
            EXPECT_STREQ("incorrect size of the sit out scheme", e.what());
            throw;
        }
    }, std::exception );
}

TEST(BackendTest, GameInfoShallCorrectlyReportIfPlayersWereSet) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    Backend::GameInfo gameInfo(std::make_shared<MemoryRepository>());
    std::set<unsigned int> sitOutScheme;

    // Act, Assert
    EXPECT_FALSE(gameInfo.HasPlayersSet());

    gameInfo.SetPlayers(std::vector<std::string>{"A", "B", "C", "D"}, "A", sitOutScheme);

    EXPECT_TRUE(gameInfo.HasPlayersSet());
    EXPECT_EQ(Backend::GameInfo::PoppableEntry::None, gameInfo.LastPoppableEntry());
}

TEST(BackendTest, GameInfoShallAdvanceDealerWhenPushingChanges) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    Backend::GameInfo gameInfo(std::make_shared<MemoryRepository>());

    // Act, Assert
    gameInfo.SetPlayers(std::vector<std::string>{"A", "B", "C", "D", "E", "F"}, "A", std::set<unsigned int> { 3 });
    std::vector<std::shared_ptr<Backend::PlayerInfo>> one(gameInfo.PlayerInfos());

    ASSERT_EQ(6, one.size());
    EXPECT_STREQ("A", one[0]->Name().c_str());
    EXPECT_STREQ("B", one[1]->Name().c_str());
    EXPECT_STREQ("C", one[2]->Name().c_str());
    EXPECT_STREQ("D", one[3]->Name().c_str());
    EXPECT_STREQ("E", one[4]->Name().c_str());
    EXPECT_STREQ("F", one[5]->Name().c_str());
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
    EXPECT_EQ(Backend::GameInfo::PoppableEntry::None, gameInfo.LastPoppableEntry());

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("B", 0),
                          std::make_pair<std::string, int>("C", 0),
                          std::make_pair<std::string, int>("E", 0),
                          std::make_pair<std::string, int>("F", 0)
                      }, 0U);

    std::vector<std::shared_ptr<Backend::PlayerInfo>> two(gameInfo.PlayerInfos());

    ASSERT_EQ(6, two.size());
    EXPECT_STREQ("A", two[0]->Name().c_str());
    EXPECT_STREQ("B", two[1]->Name().c_str());
    EXPECT_STREQ("C", two[2]->Name().c_str());
    EXPECT_STREQ("D", two[3]->Name().c_str());
    EXPECT_STREQ("E", two[4]->Name().c_str());
    EXPECT_STREQ("F", two[5]->Name().c_str());
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
    EXPECT_EQ(Backend::GameInfo::PoppableEntry::Deal, gameInfo.LastPoppableEntry());

    gameInfo.SetPlayers(std::vector<std::string>{"A", "C", "D", "E", "F"}, "F", std::set<unsigned int> {});
    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("A", 0),
                          std::make_pair<std::string, int>("C", 0),
                          std::make_pair<std::string, int>("D", 0),
                          std::make_pair<std::string, int>("E", 0)
                      }, 0U);

    std::vector<std::shared_ptr<Backend::PlayerInfo>> three(gameInfo.PlayerInfos());

    ASSERT_EQ(6, three.size());
    EXPECT_STREQ("A", three[0]->Name().c_str());
    EXPECT_STREQ("C", three[1]->Name().c_str());
    EXPECT_STREQ("D", three[2]->Name().c_str());
    EXPECT_STREQ("E", three[3]->Name().c_str());
    EXPECT_STREQ("F", three[4]->Name().c_str());
    EXPECT_STREQ("B", three[5]->Name().c_str());
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
    EXPECT_EQ(Backend::GameInfo::PoppableEntry::Deal, gameInfo.LastPoppableEntry());

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("C", 0),
                          std::make_pair<std::string, int>("D", 0),
                          std::make_pair<std::string, int>("E", 0),
                          std::make_pair<std::string, int>("F", 0)
                      }, 0U);

    std::vector<std::shared_ptr<Backend::PlayerInfo>> four(gameInfo.PlayerInfos());

    ASSERT_EQ(6, four.size());
    EXPECT_STREQ("A", four[0]->Name().c_str());
    EXPECT_STREQ("C", four[1]->Name().c_str());
    EXPECT_STREQ("D", four[2]->Name().c_str());
    EXPECT_STREQ("E", four[3]->Name().c_str());
    EXPECT_STREQ("F", four[4]->Name().c_str());
    EXPECT_STREQ("B", four[5]->Name().c_str());
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
    EXPECT_EQ(Backend::GameInfo::PoppableEntry::Deal, gameInfo.LastPoppableEntry());
}

TEST(BackendTest, GameInfoShallThrowOnPushingBadChanges) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    Backend::GameInfo gameInfo(std::make_shared<MemoryRepository>());
    std::set<unsigned int> emptySitOutScheme;
    gameInfo.SetPlayers({"A", "B", "C", "D"}, "A", emptySitOutScheme);

    // Act, Assert
    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("A", 0),
                          std::make_pair<std::string, int>("B", 0),
                          std::make_pair<std::string, int>("C", 0),
                          std::make_pair<std::string, int>("D", 0)
                      }, 0U);

    EXPECT_THROW( //NOLINT(cppcoreguidelines-avoid-goto, hicpp-avoid-goto)
    { gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
      {
          std::make_pair<std::string, int>("A", 0),
          std::make_pair<std::string, int>("B", 0),
          std::make_pair<std::string, int>("C", 0),
          std::make_pair<std::string, int>("Z", 0)
      }, 0U);
    }, std::exception);

    gameInfo.SetPlayers({"A", "B", "C", "D", "E"}, "A", emptySitOutScheme);

    EXPECT_THROW( //NOLINT(cppcoreguidelines-avoid-goto, hicpp-avoid-goto)
    {
        try
        {
            gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                         {
                             std::make_pair<std::string, int>("A", 0),
                             std::make_pair<std::string, int>("B", 0),
                             std::make_pair<std::string, int>("C", 0),
                             std::make_pair<std::string, int>("E", 0)
                         }, 0U);
        }
        catch( const std::exception& e )
        {
            EXPECT_STREQ("found change for player not playing: \"A\"", e.what());
            throw;
        }
    }, std::exception);

    gameInfo.SetPlayers({"A", "B", "C", "D", "E"}, "E", emptySitOutScheme);

    EXPECT_THROW( //NOLINT(cppcoreguidelines-avoid-goto, hicpp-avoid-goto)
    {
        try
        {
            gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                         {
                             std::make_pair<std::string, int>("A", 3),
                             std::make_pair<std::string, int>("B", 3),
                             std::make_pair<std::string, int>("C", 0),
                             std::make_pair<std::string, int>("D", -3)
                         }, 0U);
        }
        catch( const std::exception& e )
        {
            EXPECT_STREQ("changes must sum to zero", e.what());
            throw;
        }
    }, std::exception);
}

TEST(BackendTest, GameInfoShallCorrectlyUseMultiplier) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    Backend::GameInfo gameInfo(std::make_shared<MemoryRepository>());
    std::set<unsigned int> emptySitOutScheme;
    gameInfo.SetPlayers({"A", "B", "C", "D"}, "A", emptySitOutScheme);

    // Act, Assert
    ASSERT_EQ(Backend::GameInfo::PoppableEntry::None, gameInfo.LastPoppableEntry());
    ASSERT_EQ(Backend::GameInfo::MandatorySolo::CannotTrigger, gameInfo.MandatorySolo());

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("A", 1),
                          std::make_pair<std::string, int>("B", 1),
                      }, 1U);

    auto playerInfos = gameInfo.PlayerInfos();

    EXPECT_STREQ("A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ("B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ("C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ("D", playerInfos[3]->Name().c_str());

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

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("A", 3),
                          std::make_pair<std::string, int>("C", 3),
                      }, 2U);

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

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("C", 2),
                          std::make_pair<std::string, int>("D", 2),
                      }, 0U);

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

TEST(BackendTest, GameInfoShallCorrectlyReportMultiplier) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    Backend::GameInfo gameInfo(std::make_shared<MemoryRepository>());
    std::set<unsigned int> emptySitOutScheme;
    gameInfo.SetPlayers({"A", "B", "C", "D"}, "A", emptySitOutScheme);

    // Act, Assert
    ASSERT_EQ(Backend::GameInfo::PoppableEntry::None, gameInfo.LastPoppableEntry());
    ASSERT_EQ(Backend::GameInfo::MandatorySolo::CannotTrigger, gameInfo.MandatorySolo());

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("A", 1),
                          std::make_pair<std::string, int>("B", 1),
                      }, 1U);

    auto playerInfos = gameInfo.PlayerInfos();

    EXPECT_STREQ("A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ("B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ("C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ("D", playerInfos[3]->Name().c_str());

    EXPECT_EQ( 1, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[1]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[3]->CurrentScore());

    EXPECT_STREQ("1", playerInfos[0]->InputInLastDeal().c_str());
    EXPECT_STREQ("1", playerInfos[1]->InputInLastDeal().c_str());
    EXPECT_STREQ( "", playerInfos[2]->InputInLastDeal().c_str());
    EXPECT_STREQ( "", playerInfos[3]->InputInLastDeal().c_str());

    ASSERT_EQ(Backend::GameInfo::PoppableEntry::Deal, gameInfo.LastPoppableEntry());

    auto preview1 = gameInfo.MultiplierPreview();

    EXPECT_EQ(4, preview1[0]);
    EXPECT_EQ(0, preview1[1]);
    EXPECT_EQ(0, preview1[2]);

    EXPECT_EQ(1, gameInfo.LastNumberOfEvents());

    ASSERT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("A", 3),
                          std::make_pair<std::string, int>("C", 3),
                      }, 2U);

    EXPECT_EQ( 7, playerInfos[0]->CurrentScore());
    EXPECT_EQ(-5, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 5, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-7, playerInfos[3]->CurrentScore());

    EXPECT_STREQ("3", playerInfos[0]->InputInLastDeal().c_str());
    EXPECT_STREQ( "", playerInfos[1]->InputInLastDeal().c_str());
    EXPECT_STREQ("3", playerInfos[2]->InputInLastDeal().c_str());
    EXPECT_STREQ( "", playerInfos[3]->InputInLastDeal().c_str());

    ASSERT_EQ(Backend::GameInfo::PoppableEntry::Deal, gameInfo.LastPoppableEntry());

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

    EXPECT_STREQ("1", playerInfos[0]->InputInLastDeal().c_str());
    EXPECT_STREQ("1", playerInfos[1]->InputInLastDeal().c_str());
    EXPECT_STREQ( "", playerInfos[2]->InputInLastDeal().c_str());
    EXPECT_STREQ( "", playerInfos[3]->InputInLastDeal().c_str());

    auto preview3 = gameInfo.MultiplierPreview();

    EXPECT_EQ(4, preview3[0]);
    EXPECT_EQ(0, preview3[1]);
    EXPECT_EQ(0, preview3[2]);

    EXPECT_EQ(1, gameInfo.LastNumberOfEvents());

    ASSERT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());
}

TEST(BackendTest, GameInfoShallCorrectlyPopDeal) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    Backend::GameInfo gameInfo(std::make_shared<MemoryRepository>());
    std::set<unsigned int> emptySitOutScheme;
    gameInfo.SetPlayers({"A", "B", "C", "D"}, "A", emptySitOutScheme);

    // Act, Assert
    ASSERT_EQ(Backend::GameInfo::PoppableEntry::None, gameInfo.LastPoppableEntry());
    ASSERT_EQ(Backend::GameInfo::MandatorySolo::CannotTrigger, gameInfo.MandatorySolo());

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("A", 1),
                          std::make_pair<std::string, int>("B", 1),
                      }, 0U);

    auto playerInfos = gameInfo.PlayerInfos();

    EXPECT_STREQ("A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ("B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ("C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ("D", playerInfos[3]->Name().c_str());

    EXPECT_EQ( 1, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[1]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[3]->CurrentScore());

    EXPECT_STREQ("1", playerInfos[0]->InputInLastDeal().c_str());
    EXPECT_STREQ("1", playerInfos[1]->InputInLastDeal().c_str());
    EXPECT_STREQ( "", playerInfos[2]->InputInLastDeal().c_str());
    EXPECT_STREQ( "", playerInfos[3]->InputInLastDeal().c_str());

    ASSERT_EQ(Backend::GameInfo::PoppableEntry::Deal, gameInfo.LastPoppableEntry());
    ASSERT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("A", 3),
                          std::make_pair<std::string, int>("C", 3),
                      }, 0U);

    EXPECT_EQ( 4, playerInfos[0]->CurrentScore());
    EXPECT_EQ(-2, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 2, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-4, playerInfos[3]->CurrentScore());

    EXPECT_STREQ("3", playerInfos[0]->InputInLastDeal().c_str());
    EXPECT_STREQ( "", playerInfos[1]->InputInLastDeal().c_str());
    EXPECT_STREQ("3", playerInfos[2]->InputInLastDeal().c_str());
    EXPECT_STREQ( "", playerInfos[3]->InputInLastDeal().c_str());

    ASSERT_EQ(Backend::GameInfo::PoppableEntry::Deal, gameInfo.LastPoppableEntry());
    ASSERT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());

    gameInfo.PopLastEntry();

    EXPECT_EQ( 1, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[1]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[3]->CurrentScore());

    EXPECT_STREQ("1", playerInfos[0]->InputInLastDeal().c_str());
    EXPECT_STREQ("1", playerInfos[1]->InputInLastDeal().c_str());
    EXPECT_STREQ( "", playerInfos[2]->InputInLastDeal().c_str());
    EXPECT_STREQ( "", playerInfos[3]->InputInLastDeal().c_str());

    ASSERT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());
}

TEST(BackendTest, GameInfoShallCorrectlyPushDealAfterPopping) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    Backend::GameInfo gameInfo(std::make_shared<MemoryRepository>());
    std::set<unsigned int> emptySitOutScheme;
    gameInfo.SetPlayers({"A", "B", "C", "D"}, "A", emptySitOutScheme);

    // Act
    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("A", 1),
                          std::make_pair<std::string, int>("B", 1),
                      }, 0U);

    while(gameInfo.LastPoppableEntry() != Backend::GameInfo::PoppableEntry::None)
    {
        gameInfo.PopLastEntry();
    }

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("A", 1),
                          std::make_pair<std::string, int>("C", 1),
                      }, 0U);

    // Assert
    auto playerInfos = gameInfo.PlayerInfos();

    EXPECT_EQ( 1, playerInfos[0]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[3]->CurrentScore());

    EXPECT_EQ(Backend::GameInfo::PoppableEntry::Deal, gameInfo.LastPoppableEntry());
}

TEST(BackendTest, GameInfoShallCorrectlyPopAllKindsOfEntries) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    Backend::GameInfo gameInfo(std::make_shared<MemoryRepository>());
    std::set<unsigned int> sitOutScheme = { 3 };
    gameInfo.SetPlayers({"A", "B", "C", "D", "E", "F"}, "A", sitOutScheme);

    // Act, Assert
    auto playerInfos = gameInfo.PlayerInfos();

    EXPECT_STREQ("A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ("B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ("C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ("D", playerInfos[3]->Name().c_str());
    EXPECT_STREQ("E", playerInfos[4]->Name().c_str());
    EXPECT_STREQ("F", playerInfos[5]->Name().c_str());

    ASSERT_EQ(Backend::GameInfo::PoppableEntry::None, gameInfo.LastPoppableEntry());
    ASSERT_EQ(Backend::GameInfo::MandatorySolo::CannotTrigger, gameInfo.MandatorySolo());

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("B", 2),
                          std::make_pair<std::string, int>("C", 2),
                      }, 0U);

    EXPECT_EQ( 0, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 2, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 2, playerInfos[2]->CurrentScore());
    EXPECT_EQ( 0, playerInfos[3]->CurrentScore());
    EXPECT_EQ(-2, playerInfos[4]->CurrentScore());
    EXPECT_EQ(-2, playerInfos[5]->CurrentScore());

    EXPECT_STREQ( "", playerInfos[0]->InputInLastDeal().c_str());
    EXPECT_STREQ("2", playerInfos[1]->InputInLastDeal().c_str());
    EXPECT_STREQ("2", playerInfos[2]->InputInLastDeal().c_str());
    EXPECT_STREQ( "", playerInfos[3]->InputInLastDeal().c_str());
    EXPECT_STREQ( "", playerInfos[4]->InputInLastDeal().c_str());
    EXPECT_STREQ( "", playerInfos[5]->InputInLastDeal().c_str());

    ASSERT_EQ(Backend::GameInfo::PoppableEntry::Deal, gameInfo.LastPoppableEntry());
    ASSERT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());

    gameInfo.TriggerMandatorySolo();

    ASSERT_EQ(Backend::GameInfo::PoppableEntry::MandatorySoloTrigger, gameInfo.LastPoppableEntry());
    ASSERT_EQ(Backend::GameInfo::MandatorySolo::Active, gameInfo.MandatorySolo());

    gameInfo.SetPlayers({"A", "B", "C", "D", "E", "Z"}, "A", sitOutScheme);
    playerInfos = gameInfo.PlayerInfos();

    EXPECT_STREQ("A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ("B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ("C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ("D", playerInfos[3]->Name().c_str());
    EXPECT_STREQ("E", playerInfos[4]->Name().c_str());
    EXPECT_STREQ("Z", playerInfos[5]->Name().c_str());

    ASSERT_EQ(Backend::GameInfo::PoppableEntry::PlayersSet, gameInfo.LastPoppableEntry());

    gameInfo.PopLastEntry();
    playerInfos = gameInfo.PlayerInfos();

    EXPECT_STREQ("A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ("B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ("C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ("D", playerInfos[3]->Name().c_str());
    EXPECT_STREQ("E", playerInfos[4]->Name().c_str());
    EXPECT_STREQ("F", playerInfos[5]->Name().c_str());

    ASSERT_EQ(Backend::GameInfo::PoppableEntry::MandatorySoloTrigger, gameInfo.LastPoppableEntry());

    gameInfo.PopLastEntry();
    playerInfos = gameInfo.PlayerInfos();

    ASSERT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());

    EXPECT_STREQ( "", playerInfos[0]->InputInLastDeal().c_str());
    EXPECT_STREQ("2", playerInfos[1]->InputInLastDeal().c_str());
    EXPECT_STREQ("2", playerInfos[2]->InputInLastDeal().c_str());
    EXPECT_STREQ( "", playerInfos[3]->InputInLastDeal().c_str());
    EXPECT_STREQ( "", playerInfos[4]->InputInLastDeal().c_str());
    EXPECT_STREQ( "", playerInfos[5]->InputInLastDeal().c_str());

    ASSERT_EQ(Backend::GameInfo::PoppableEntry::Deal, gameInfo.LastPoppableEntry());

    gameInfo.PopLastEntry();
    playerInfos = gameInfo.PlayerInfos();

    ASSERT_EQ(Backend::GameInfo::PoppableEntry::None, gameInfo.LastPoppableEntry());

    EXPECT_EQ(0, playerInfos[0]->CurrentScore());
    EXPECT_EQ(0, playerInfos[1]->CurrentScore());
    EXPECT_EQ(0, playerInfos[2]->CurrentScore());
    EXPECT_EQ(0, playerInfos[3]->CurrentScore());
    EXPECT_EQ(0, playerInfos[4]->CurrentScore());
    EXPECT_EQ(0, playerInfos[5]->CurrentScore());

    EXPECT_EQ(0, playerInfos[0]->NumberGames());
    EXPECT_EQ(0, playerInfos[1]->NumberGames());
    EXPECT_EQ(0, playerInfos[2]->NumberGames());
    EXPECT_EQ(0, playerInfos[3]->NumberGames());
    EXPECT_EQ(0, playerInfos[4]->NumberGames());
    EXPECT_EQ(0, playerInfos[5]->NumberGames());
}

TEST(BackendTest, GameInfoShallHaveCorrectMultiplierAfterPopping) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    Backend::GameInfo gameInfo(std::make_shared<MemoryRepository>());
    std::set<unsigned int> sitOutScheme { 3 };
    gameInfo.SetPlayers({"A", "B", "C", "D", "E", "F"}, "A", sitOutScheme);

    // Act, Assert
    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("B", 1),
                          std::make_pair<std::string, int>("C", 1),
                      }, 1U);

    auto playerInfos = gameInfo.PlayerInfos();

    EXPECT_STREQ("A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ("B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ("C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ("D", playerInfos[3]->Name().c_str());
    EXPECT_STREQ("E", playerInfos[4]->Name().c_str());
    EXPECT_STREQ("F", playerInfos[5]->Name().c_str());

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

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("A", 2),
                          std::make_pair<std::string, int>("C", 2),
                      }, 2U);

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

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("A", 2),
                          std::make_pair<std::string, int>("B", 2),
                      }, 0U);

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

TEST(BackendTest, GameInfoShallUseMultiplierAfterSettingPlayers) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    Backend::GameInfo gameInfo(std::make_shared<MemoryRepository>());
    std::set<unsigned int> sitOutScheme { };
    gameInfo.SetPlayers({"A", "B", "C", "D"}, "A", sitOutScheme);

    // Act, Assert
    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("B", 1),
                          std::make_pair<std::string, int>("C", 1),
                      }, 0U);

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("A", 1),
                          std::make_pair<std::string, int>("C", 1),
                      }, 0U);

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("C", 1),
                          std::make_pair<std::string, int>("D", 1),
                      }, 1U);


    auto playerInfos = gameInfo.PlayerInfos();

    EXPECT_STREQ("A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ("B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ("C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ("D", playerInfos[3]->Name().c_str());

    EXPECT_EQ(-1, playerInfos[0]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 3, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[3]->CurrentScore());

    gameInfo.SetPlayers({"A", "B", "C", "D", "E"}, "D", sitOutScheme);

    playerInfos = gameInfo.PlayerInfos();

    EXPECT_STREQ("A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ("B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ("C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ("D", playerInfos[3]->Name().c_str());
    EXPECT_STREQ("E", playerInfos[4]->Name().c_str());

    EXPECT_EQ(-1, playerInfos[0]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 3, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[3]->CurrentScore());
    EXPECT_EQ( 0, playerInfos[4]->CurrentScore());

    EXPECT_EQ(4, gameInfo.MultiplierPreview()[0]);
    EXPECT_EQ(0, gameInfo.MultiplierPreview()[1]);
    EXPECT_EQ(0, gameInfo.MultiplierPreview()[2]);

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("C", 1),
                          std::make_pair<std::string, int>("E", 1),
                      }, 0U);

    EXPECT_EQ(-3, playerInfos[0]->CurrentScore());
    EXPECT_EQ(-3, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 5, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[3]->CurrentScore());
    EXPECT_EQ( 2, playerInfos[4]->CurrentScore());
}

TEST(BackendTest, GameInfoShallProvideCorrectStatistics) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    Backend::GameInfo gameInfo(std::make_shared<MemoryRepository>());
    std::set<unsigned int> sitOutScheme {};
    gameInfo.SetPlayers({"A", "B", "C", "D", "E"}, "A", sitOutScheme);

    // Act
    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          /* A */
                          std::make_pair<std::string, int>("B", -1),
                          std::make_pair<std::string, int>("C", -1),
                          std::make_pair<std::string, int>("D",  1),
                          std::make_pair<std::string, int>("E",  1)
                      }, 0U);

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("A",  3),
                          /* B */
                          std::make_pair<std::string, int>("C", -1),
                          std::make_pair<std::string, int>("D", -1),
                          std::make_pair<std::string, int>("E", -1)
                      }, 1U);

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("A",  2),
                          std::make_pair<std::string, int>("B",  2),
                          /* C */
                          std::make_pair<std::string, int>("D",  2),
                          std::make_pair<std::string, int>("E", -6)
                      }, 0U);

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("A",  3),
                          std::make_pair<std::string, int>("B", -3),
                          std::make_pair<std::string, int>("C",  3),
                          /* D */
                          std::make_pair<std::string, int>("E", -3)
                      }, 0U);

    // Assert
    auto playerInfos = gameInfo.PlayerInfos();

    EXPECT_STREQ("A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ("B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ("C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ("D", playerInfos[3]->Name().c_str());
    EXPECT_STREQ("E", playerInfos[4]->Name().c_str());

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

TEST(BackendTest, GameInfoShallSuspendMultiplierForMandatorySolo) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    Backend::GameInfo gameInfo(std::make_shared<MemoryRepository>());
    std::set<unsigned int> sitOutScheme { };
    gameInfo.SetPlayers({"A", "B", "C", "D"}, "A", sitOutScheme);

    // Act, Assert
    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("B", 1),
                          std::make_pair<std::string, int>("C", 1),
                      }, 1U);

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());

    gameInfo.TriggerMandatorySolo();

    auto playerInfos = gameInfo.PlayerInfos();

    EXPECT_STREQ("A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ("B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ("C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ("D", playerInfos[3]->Name().c_str());

    EXPECT_EQ(-1, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[3]->CurrentScore());

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Active, gameInfo.MandatorySolo());

    auto preview1 = gameInfo.MultiplierPreview();
    EXPECT_EQ(4, preview1[0]);
    EXPECT_EQ(0, preview1[1]);
    EXPECT_EQ(0, preview1[2]);

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("B", 6),
                      }, 0U);

    EXPECT_EQ(-3, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 7, playerInfos[1]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-3, playerInfos[3]->CurrentScore());

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Active, gameInfo.MandatorySolo());

    auto preview2 = gameInfo.MultiplierPreview();
    EXPECT_EQ(4, preview2[0]);
    EXPECT_EQ(0, preview2[1]);
    EXPECT_EQ(0, preview2[2]);

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("C", -3),
                      }, 0U);

    EXPECT_EQ(-2, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 8, playerInfos[1]->CurrentScore());
    EXPECT_EQ(-4, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-2, playerInfos[3]->CurrentScore());

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Active, gameInfo.MandatorySolo());

    auto preview3 = gameInfo.MultiplierPreview();
    EXPECT_EQ(4, preview3[0]);
    EXPECT_EQ(0, preview3[1]);
    EXPECT_EQ(0, preview3[2]);

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("D", 3),
                      }, 0U);

    EXPECT_EQ(-3, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 7, playerInfos[1]->CurrentScore());
    EXPECT_EQ(-5, playerInfos[2]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[3]->CurrentScore());

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Active, gameInfo.MandatorySolo());

    auto preview4 = gameInfo.MultiplierPreview();
    EXPECT_EQ(4, preview4[0]);
    EXPECT_EQ(0, preview4[1]);
    EXPECT_EQ(0, preview4[2]);

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("A", -9),
                      }, 0U);

    EXPECT_EQ(-12, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 10, playerInfos[1]->CurrentScore());
    EXPECT_EQ( -2, playerInfos[2]->CurrentScore());
    EXPECT_EQ(  4, playerInfos[3]->CurrentScore());

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());

    auto preview5 = gameInfo.MultiplierPreview();
    EXPECT_EQ(4, preview5[0]);
    EXPECT_EQ(0, preview5[1]);
    EXPECT_EQ(0, preview5[2]);

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("B", 5),
                          std::make_pair<std::string, int>("C", 5),
                      }, 0U);

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

TEST(BackendTest, GameInfoShallPopMandatorySolo) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    Backend::GameInfo gameInfo(std::make_shared<MemoryRepository>());
    std::set<unsigned int> sitOutScheme { };
    gameInfo.SetPlayers({"A", "B", "C", "D"}, "A", sitOutScheme);

    // Act, Assert
    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("B", 1),
                          std::make_pair<std::string, int>("C", 1),
                      }, 1U);

    auto playerInfos = gameInfo.PlayerInfos();

    EXPECT_STREQ("A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ("B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ("C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ("D", playerInfos[3]->Name().c_str());

    EXPECT_EQ(-1, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[3]->CurrentScore());

    EXPECT_EQ(Backend::GameInfo::PoppableEntry::Deal, gameInfo.LastPoppableEntry());

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("B", 1),
                          std::make_pair<std::string, int>("C", 1),
                      }, 0U);

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());

    EXPECT_EQ(-3, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 3, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 3, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-3, playerInfos[3]->CurrentScore());

    EXPECT_EQ(Backend::GameInfo::PoppableEntry::Deal, gameInfo.LastPoppableEntry());

    gameInfo.TriggerMandatorySolo();

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Active, gameInfo.MandatorySolo());

    auto preview1 = gameInfo.MultiplierPreview();
    EXPECT_EQ(3, preview1[0]);
    EXPECT_EQ(0, preview1[1]);
    EXPECT_EQ(0, preview1[2]);

    EXPECT_EQ(Backend::GameInfo::PoppableEntry::MandatorySoloTrigger, gameInfo.LastPoppableEntry());

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("B", 6),
                      }, 0U);

    EXPECT_EQ(-5, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 9, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-5, playerInfos[3]->CurrentScore());

    EXPECT_EQ(Backend::GameInfo::PoppableEntry::Deal, gameInfo.LastPoppableEntry());

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

    EXPECT_EQ(Backend::GameInfo::PoppableEntry::MandatorySoloTrigger, gameInfo.LastPoppableEntry());

    gameInfo.PopLastEntry();

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());

    auto preview4 = gameInfo.MultiplierPreview();
    EXPECT_EQ(3, preview4[0]);
    EXPECT_EQ(0, preview4[1]);
    EXPECT_EQ(0, preview4[2]);

    EXPECT_EQ(Backend::GameInfo::PoppableEntry::Deal, gameInfo.LastPoppableEntry());

    gameInfo.PopLastEntry();

    auto preview5 = gameInfo.MultiplierPreview();
    EXPECT_EQ(4, preview5[0]);
    EXPECT_EQ(0, preview5[1]);
    EXPECT_EQ(0, preview5[2]);

    EXPECT_EQ(Backend::GameInfo::PoppableEntry::Deal, gameInfo.LastPoppableEntry());

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("A", 3),
                          std::make_pair<std::string, int>("C", 3),
                      }, 0U);

    EXPECT_EQ( 5, playerInfos[0]->CurrentScore());
    EXPECT_EQ(-5, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 7, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-7, playerInfos[3]->CurrentScore());

    auto preview6 = gameInfo.MultiplierPreview();
    EXPECT_EQ(3, preview6[0]);
    EXPECT_EQ(0, preview6[1]);
    EXPECT_EQ(0, preview6[2]);

    EXPECT_EQ(Backend::GameInfo::PoppableEntry::Deal, gameInfo.LastPoppableEntry());
}

TEST(BackendTest, GameInfoShallAllowMandatorySoloAfterPlayerSet) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    Backend::GameInfo gameInfo(std::make_shared<MemoryRepository>());
    std::set<unsigned int> sitOutScheme { };
    gameInfo.SetPlayers({"A", "B", "C", "D"}, "A", sitOutScheme);

    // Act, Assert
    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("B", 1),
                          std::make_pair<std::string, int>("C", 1),
                      }, 0U);

    auto playerInfos = gameInfo.PlayerInfos();

    EXPECT_STREQ("A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ("B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ("C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ("D", playerInfos[3]->Name().c_str());

    EXPECT_EQ(-1, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[3]->CurrentScore());

    EXPECT_EQ(Backend::GameInfo::PoppableEntry::Deal, gameInfo.LastPoppableEntry());

    gameInfo.SetPlayers({"A", "B", "C", "D", "E"}, "B", sitOutScheme);

    playerInfos = gameInfo.PlayerInfos();

    EXPECT_STREQ("A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ("B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ("C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ("D", playerInfos[3]->Name().c_str());
    EXPECT_STREQ("E", playerInfos[4]->Name().c_str());

    EXPECT_EQ(-1, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[3]->CurrentScore());
    EXPECT_EQ( 0, playerInfos[4]->CurrentScore());

    gameInfo.TriggerMandatorySolo();

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Active, gameInfo.MandatorySolo());
    EXPECT_EQ(Backend::GameInfo::PoppableEntry::MandatorySoloTrigger, gameInfo.LastPoppableEntry());

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("C", 1),
                          std::make_pair<std::string, int>("D", 1),
                      }, 0U);

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Active, gameInfo.MandatorySolo());

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("D", 1),
                          std::make_pair<std::string, int>("E", 1),
                      }, 0U);

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Active, gameInfo.MandatorySolo());

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("E", 1),
                          std::make_pair<std::string, int>("A", 1),
                      }, 0U);

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Active, gameInfo.MandatorySolo());

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("A", 1),
                          std::make_pair<std::string, int>("B", 1),
                      }, 0U);

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Active, gameInfo.MandatorySolo());

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("B", 1),
                          std::make_pair<std::string, int>("C", 1),
                      }, 0U);

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Ready, gameInfo.MandatorySolo());
}

TEST(BackendTest, GameInfoShallThrowOnTriggerMandatorySoloInWrongStates) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    Backend::GameInfo gameInfo(std::make_shared<MemoryRepository>());
    std::set<unsigned int> emptySitOutScheme;

    // Act, Assert
    gameInfo.SetPlayers({"A", "B", "C", "D" }, "A", emptySitOutScheme);

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::CannotTrigger, gameInfo.MandatorySolo());

    EXPECT_THROW( //NOLINT(cppcoreguidelines-avoid-goto, hicpp-avoid-goto)
    {
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

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("A", 3),
                          std::make_pair<std::string, int>("C", 3),
                      }, 0U);

    gameInfo.TriggerMandatorySolo();

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Active, gameInfo.MandatorySolo());

    EXPECT_THROW( //NOLINT(cppcoreguidelines-avoid-goto, hicpp-avoid-goto)
    {
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

TEST(BackendTest, GameInfoShallCorrectlySaveToRepository) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    auto repository = std::make_shared<MemoryRepository>();
    std::u8string id(u8"some Id");
    Backend::GameInfo gameInfo(repository);
    std::set<unsigned int> sitOutScheme { };
    gameInfo.SetPlayers({"A", "B", "C", "文字"}, "A", sitOutScheme);

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("B", 1),
                          std::make_pair<std::string, int>("C", 1),
                      }, 1U);

    gameInfo.TriggerMandatorySolo();

    // Act
    gameInfo.SaveTo(id);

    // Assert
    std::string persisted;
    bool found = repository->TryGetByIdentifier(id, persisted);

    ASSERT_TRUE(found);

    ASSERT_TRUE(persisted.length() > 0);
    std::regex dataVersionRegex(R"foo("dataVersion":"[0-9]+")foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, dataVersionRegex));

    std::regex playersSetKindRegex(R"foo("kind":"playersSet")foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, playersSetKindRegex));
    std::regex playerNamesRegex(R"foo("playerNames":\["A","B","C","\\u6587\\u5B57"\])foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, playerNamesRegex));
    std::regex dealerNameRegex(R"foo("dealerName":"A")foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, dealerNameRegex));
    std::regex sitOutSchemeRegex(R"foo("sitOutScheme":\[\])foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, sitOutSchemeRegex));

    std::regex dealKindRegex(R"foo("kind":"deal")foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, dealKindRegex));
    std::regex playersRegex(R"foo("players":4)foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, playersRegex));
    std::regex numberOfEventsRegex(R"foo("numberOfEvents":1)foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, numberOfEventsRegex));
    std::regex changesRegex(R"foo("changes":\[\{)foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, sitOutSchemeRegex));
    std::regex objectBRegex(R"foo(\{"name":"B","diff":1\})foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, objectBRegex));
    std::regex objectCRegex(R"foo(\{"name":"C","diff":1\})foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, objectCRegex));

    std::regex mandatorySoloTriggerKindRegex(R"foo("kind":"mandatorySoloTrigger")foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, mandatorySoloTriggerKindRegex));
}

TEST(BackendTest, GameInfoShallCorrectlyLoadFromRepository) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    std::vector<std::shared_ptr<Backend::Entry>> entries;

    entries.push_back(std::make_shared<Backend::PlayersSet>(
                          std::vector<std::string>
                          {
                              "A",
                              "B",
                              "C",
                              "D",
                              "E",
                              "F",
                              "文字",
                          },
                          "C",
                          std::set<unsigned int> { 2, 4 },
                          ""));
    entries.push_back(std::make_shared<Backend::Deal>(
                          std::vector<std::pair<std::string, int>>
                          {
                              std::make_pair<std::string, int>("A", 1),
                              std::make_pair<std::string, int>("B", 1),
                              std::make_pair<std::string, int>("D", -1),
                              std::make_pair<std::string, int>("F", -1)
                          },
                          Backend::NumberOfEvents(2),
                          Backend::Players(7)));
    entries.push_back(std::make_shared<Backend::MandatorySoloTrigger>());

    auto repository = std::make_shared<MemoryRepository>();
    std::u8string id(u8"some Id");
    repository->Save(entries, id);

    Backend::GameInfo gameInfo(repository);

    // Act
    gameInfo.LoadFrom(id);

    // Assert
    auto playerInfos = gameInfo.PlayerInfos();

    EXPECT_STREQ("A", playerInfos[0]->Name().c_str());
    EXPECT_STREQ("B", playerInfos[1]->Name().c_str());
    EXPECT_STREQ("C", playerInfos[2]->Name().c_str());
    EXPECT_STREQ("D", playerInfos[3]->Name().c_str());
    EXPECT_STREQ("E", playerInfos[4]->Name().c_str());
    EXPECT_STREQ("F", playerInfos[5]->Name().c_str());
    EXPECT_STREQ("文字", playerInfos[6]->Name().c_str());

    EXPECT_STREQ("D", gameInfo.Dealer()->Name().c_str());

    EXPECT_EQ(6U, gameInfo.RemainingGamesInRound());

    EXPECT_EQ( 1, playerInfos[0]->CurrentScore());
    EXPECT_EQ( 1, playerInfos[1]->CurrentScore());
    EXPECT_EQ( 0, playerInfos[2]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[3]->CurrentScore());
    EXPECT_EQ( 0, playerInfos[4]->CurrentScore());
    EXPECT_EQ(-1, playerInfos[5]->CurrentScore());
    EXPECT_EQ( 0, playerInfos[6]->CurrentScore());

    auto multiplierPreview = gameInfo.MultiplierPreview();

    EXPECT_EQ(0, multiplierPreview[0]);
    EXPECT_EQ(7, multiplierPreview[1]);
    EXPECT_EQ(0, multiplierPreview[2]);

    auto mandatorySolo = gameInfo.MandatorySolo();

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Active, mandatorySolo);
}

TEST(BackendTest, GameInfoShallCorrectlyRoundtripRepository) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    auto repository = std::make_shared<MemoryRepository>();
    std::u8string id(u8"some Id");
    Backend::GameInfo gameInfo(repository);
    std::set<unsigned int> sitOutScheme { };
    gameInfo.SetPlayers({"A", "B", "C", "D"}, "A", sitOutScheme);

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("B", 1),
                          std::make_pair<std::string, int>("C", 1),
                      }, 1U);

    gameInfo.TriggerMandatorySolo();

    // Act
    gameInfo.SaveTo(id);

    while(gameInfo.LastPoppableEntry() != Backend::GameInfo::PoppableEntry::None)
    {
        gameInfo.PopLastEntry();
    }

    auto playerInfos = gameInfo.PlayerInfos();

    ASSERT_EQ(0, playerInfos[0]->NumberGames());
    ASSERT_EQ(0, playerInfos[1]->NumberGames());
    ASSERT_EQ(0, playerInfos[2]->NumberGames());
    ASSERT_EQ(0, playerInfos[3]->NumberGames());

    gameInfo.LoadFrom(id);

    // Assert
    EXPECT_EQ(3U, gameInfo.RemainingGamesInRound());

    ASSERT_EQ(1, playerInfos[0]->NumberGames());
    ASSERT_EQ(1, playerInfos[1]->NumberGames());
    ASSERT_EQ(1, playerInfos[2]->NumberGames());
    ASSERT_EQ(1, playerInfos[3]->NumberGames());

    ASSERT_EQ(-1, playerInfos[0]->CurrentScore());
    ASSERT_EQ( 1, playerInfos[1]->CurrentScore());
    ASSERT_EQ( 1, playerInfos[2]->CurrentScore());
    ASSERT_EQ(-1, playerInfos[3]->CurrentScore());

    auto multiplierPreview = gameInfo.MultiplierPreview();

    EXPECT_EQ(4, multiplierPreview[0]);
    EXPECT_EQ(0, multiplierPreview[1]);
    EXPECT_EQ(0, multiplierPreview[2]);

    auto mandatorySolo = gameInfo.MandatorySolo();

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Active, mandatorySolo);
}

TEST(BackendTest, GameInfoShallCorrectlyHandleBadLoad) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    auto repository = std::make_shared<MemoryRepository>();
    std::u8string id(u8"some Id");
    std::string content(R"foo({"will not work":"stuff"})foo");
    repository->SetByIdentifier(id, content);

    Backend::GameInfo gameInfo(repository);
    std::set<unsigned int> sitOutScheme { };
    gameInfo.SetPlayers({"A", "B", "C", "D"}, "A", sitOutScheme);

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("B", 1),
                          std::make_pair<std::string, int>("C", 1),
                      }, 1U);

    gameInfo.TriggerMandatorySolo();

    // Act
    bool exceptionCaught = false;

    try
    {
        gameInfo.LoadFrom(id);
    }
    catch (...)
    {
        exceptionCaught = true;
    }

    // Assert
    // there should be no change due to LoadFrom call
    ASSERT_TRUE(exceptionCaught);

    auto playerInfos = gameInfo.PlayerInfos();

    ASSERT_EQ(1, playerInfos[0]->NumberGames());
    ASSERT_EQ(1, playerInfos[1]->NumberGames());
    ASSERT_EQ(1, playerInfos[2]->NumberGames());
    ASSERT_EQ(1, playerInfos[3]->NumberGames());

    ASSERT_EQ(-1, playerInfos[0]->CurrentScore());
    ASSERT_EQ( 1, playerInfos[1]->CurrentScore());
    ASSERT_EQ( 1, playerInfos[2]->CurrentScore());
    ASSERT_EQ(-1, playerInfos[3]->CurrentScore());

    auto multiplierPreview = gameInfo.MultiplierPreview();

    EXPECT_EQ(4, multiplierPreview[0]);
    EXPECT_EQ(0, multiplierPreview[1]);
    EXPECT_EQ(0, multiplierPreview[2]);

    auto mandatorySolo = gameInfo.MandatorySolo();

    EXPECT_EQ(Backend::GameInfo::MandatorySolo::Active, mandatorySolo);
}

TEST(BackendTest, GameInfoShallCorrectlyReportRemainingGamesInRound) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    auto repository = std::make_shared<MemoryRepository>();

    Backend::GameInfo gameInfo(repository);
    std::set<unsigned int> sitOutScheme { };
    gameInfo.SetPlayers({"A", "B", "C", "D"}, "C", sitOutScheme);

    // Act, Assert
    auto remaining1 = gameInfo.RemainingGamesInRound();
    EXPECT_EQ(0U, remaining1);

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("B", 1),
                          std::make_pair<std::string, int>("C", 1),
                      }, 1U);
    auto remaining2 = gameInfo.RemainingGamesInRound();
    EXPECT_EQ(3U, remaining2);

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("B", 1),
                          std::make_pair<std::string, int>("C", 1),
                      }, 1U);
    auto remaining3 = gameInfo.RemainingGamesInRound();
    EXPECT_EQ(2U, remaining3);

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("B", 1),
                          std::make_pair<std::string, int>("C", 1),
                      }, 1U);
    auto remaining4 = gameInfo.RemainingGamesInRound();
    EXPECT_EQ(1U, remaining4);

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("B", 1),
                          std::make_pair<std::string, int>("C", 1),
                      }, 1U);
    auto remaining5 = gameInfo.RemainingGamesInRound();
    EXPECT_EQ(0U, remaining5);

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("B", 1),
                          std::make_pair<std::string, int>("C", 1),
                      }, 1U);
    auto remaining6 = gameInfo.RemainingGamesInRound();
    EXPECT_EQ(3U, remaining6);

    gameInfo.TriggerMandatorySolo();
    auto remaining7 = gameInfo.RemainingGamesInRound();
    EXPECT_EQ(3U, remaining7);

    gameInfo.PopLastEntry();
    auto remaining8 = gameInfo.RemainingGamesInRound();
    EXPECT_EQ(3U, remaining8);

    gameInfo.PopLastEntry();
    auto remaining9 = gameInfo.RemainingGamesInRound();
    EXPECT_EQ(0U, remaining9);

    gameInfo.PopLastEntry();
    auto remaining10 = gameInfo.RemainingGamesInRound();
    EXPECT_EQ(1U, remaining10);
}

TEST(BackendTest, GameInfoShallCorrectlyReportRemainingGamesInRoundAfterPoppingPlayerSet) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    auto repository = std::make_shared<MemoryRepository>();

    Backend::GameInfo gameInfo(repository);
    std::set<unsigned int> sitOutScheme { };
    gameInfo.SetPlayers({"A", "B", "C", "D"}, "C", sitOutScheme);

    // Act, Assert
    auto remaining1 = gameInfo.RemainingGamesInRound();
    EXPECT_EQ(0U, remaining1);

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("B", 1),
                          std::make_pair<std::string, int>("C", 1),
                      }, 1U);
    auto remaining2 = gameInfo.RemainingGamesInRound();
    EXPECT_EQ(3U, remaining2);

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("B", 1),
                          std::make_pair<std::string, int>("C", 1),
                      }, 1U);
    auto remaining3 = gameInfo.RemainingGamesInRound();
    EXPECT_EQ(2U, remaining3);

    gameInfo.SetPlayers({"A", "B", "C", "D", "E"}, "E", sitOutScheme);
    auto remaining4 = gameInfo.RemainingGamesInRound();
    EXPECT_EQ(0U, remaining4);

    gameInfo.PushDeal(std::vector<std::pair<std::string, int>>
                      {
                          std::make_pair<std::string, int>("B", 1),
                          std::make_pair<std::string, int>("C", 1),
                      }, 1U);
    auto remaining5 = gameInfo.RemainingGamesInRound();
    EXPECT_EQ(4U, remaining5);

    gameInfo.PopLastEntry();
    auto remaining6 = gameInfo.RemainingGamesInRound();
    EXPECT_EQ(0U, remaining6);

    gameInfo.PopLastEntry();
    auto remaining7 = gameInfo.RemainingGamesInRound();
    EXPECT_EQ(2U, remaining7);
}

TEST(BackendTest, GameInfoShallHandleNoPlayersSet) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    Backend::GameInfo gameInfo(std::make_shared<MemoryRepository>());

    // Act
    auto playerInfos = gameInfo.PlayerInfos();
    auto dealer = gameInfo.Dealer();
    auto poppableEntry = gameInfo.LastPoppableEntry();
    auto hasPlayersSet = gameInfo.HasPlayersSet();
    auto lastNumberOfEvents = gameInfo.LastNumberOfEvents();
    auto totalCashCents = gameInfo.TotalCashCents();
    auto mandatorySolo = gameInfo.MandatorySolo();
    auto remaingingGamesInRound = gameInfo.RemainingGamesInRound();

    // Assert
    EXPECT_EQ(Backend::GameInfo::PoppableEntry::None, poppableEntry);
    EXPECT_FALSE(hasPlayersSet);
    EXPECT_EQ(0U, lastNumberOfEvents);
    EXPECT_EQ(0U, totalCashCents);
    EXPECT_EQ(Backend::GameInfo::MandatorySolo::CannotTrigger, mandatorySolo);
    EXPECT_EQ(0U, remaingingGamesInRound);
}

#endif // TST_GAMEINFO_H
