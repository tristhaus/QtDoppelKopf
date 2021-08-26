/*
 * This file is part of QtPollyNom.
 *
 * QtPollyNom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QtPollyNom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QtPollyNom.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef TST_GAMEINFO_H
#define TST_GAMEINFO_H

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

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"A", 0),
                          std::make_pair<std::wstring, int>(L"B", 0),
                          std::make_pair<std::wstring, int>(L"C", 0),
                          std::make_pair<std::wstring, int>(L"D", 0)
                      });

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

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"E", 0),
                          std::make_pair<std::wstring, int>(L"C", 0),
                          std::make_pair<std::wstring, int>(L"D", 0),
                          std::make_pair<std::wstring, int>(L"A", 0)
                      });

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"C", 0),
                          std::make_pair<std::wstring, int>(L"D", 0),
                          std::make_pair<std::wstring, int>(L"A", 0),
                          std::make_pair<std::wstring, int>(L"B", 0)
                      });

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

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"B", 0),
                          std::make_pair<std::wstring, int>(L"C", 0),
                          std::make_pair<std::wstring, int>(L"E", 0),
                          std::make_pair<std::wstring, int>(L"F", 0)
                      });

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

    gameInfo.SetPlayers(std::vector<std::wstring>{L"A", L"C", L"D", L"E", L"F"}, L"F", std::set<unsigned int> {});
    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"A", 0),
                          std::make_pair<std::wstring, int>(L"C", 0),
                          std::make_pair<std::wstring, int>(L"D", 0),
                          std::make_pair<std::wstring, int>(L"E", 0)
                      });

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

    gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                      {
                          std::make_pair<std::wstring, int>(L"C", 0),
                          std::make_pair<std::wstring, int>(L"D", 0),
                          std::make_pair<std::wstring, int>(L"E", 0),
                          std::make_pair<std::wstring, int>(L"F", 0)
                      });

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
                      });

    EXPECT_THROW({
        try
        {
            gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                         {
                             std::make_pair<std::wstring, int>(L"A", 0),
                             std::make_pair<std::wstring, int>(L"B", 0),
                             std::make_pair<std::wstring, int>(L"C", 0)
                         });
        }
        catch( const std::exception& e )
        {
            EXPECT_STREQ("changes must have size 4", e.what());
            throw;
        }
    }, std::exception);

    EXPECT_THROW({
        try
        {
            gameInfo.PushDeal(std::vector<std::pair<std::wstring, int>>
                         {
                             std::make_pair<std::wstring, int>(L"A", 0),
                             std::make_pair<std::wstring, int>(L"B", 0),
                             std::make_pair<std::wstring, int>(L"C", 0),
                             std::make_pair<std::wstring, int>(L"Z", 0)
                         });
        }
        catch( const std::exception& e )
        {
            EXPECT_STREQ("found change for unknown player", e.what());
            throw;
        }
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
                         });
        }
        catch( const std::exception& e )
        {
            EXPECT_STREQ("found change for player not playing", e.what());
            throw;
        }
    }, std::exception);
}

#endif // TST_GAMEINFO_H
