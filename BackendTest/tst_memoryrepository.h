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

#include <regex>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../TestHelper/memoryrepository.h"

#ifndef TST_MEMORYREPOSITORY_H
#define TST_MEMORYREPOSITORY_H

TEST(BackendTest, MemoryRepositoryShallCorrectlyStoreEntries)
{
    // Arrange
    std::vector<std::shared_ptr<Backend::Entry>> entries;

    entries.push_back(std::make_shared<Backend::PlayersSet>(
                          std::vector<std::string>
                          {
                              u8"A",
                              u8"B",
                              u8"C",
                              u8"D",
                              u8"E",
                              u8"F",
                              u8"文字",
                          },
                          u8"C",
                          std::set<unsigned int> { 2, 4 },
                          u8"Z"));
    entries.push_back(std::make_shared<Backend::Deal>(
                          std::vector<std::pair<std::string, int>>
                          {
                              std::make_pair<std::string, int>(u8"A", 1),
                              std::make_pair<std::string, int>(u8"B", 1),
                              std::make_pair<std::string, int>(u8"C", -1),
                              std::make_pair<std::string, int>(u8"D", -1)
                          },
                          Backend::NumberOfEvents(2),
                          Backend::Players(7)));
    entries.push_back(std::make_shared<Backend::MandatorySoloTrigger>());

    MemoryRepository repo;
    std::string id = u8"someId";

    // Act
    repo.Save(entries, id);

    // Assert
    std::string persisted;
    bool found = repo.TryGetByIdentifier(id, persisted);

    ASSERT_TRUE(found);

    ASSERT_TRUE(persisted.length() > 0);
    std::regex dataVersionRegex(u8R"foo("dataVersion":"[0-9]+")foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, dataVersionRegex));

    std::regex playersSetKindRegex(u8R"foo("kind":"playersSet")foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, playersSetKindRegex));
    std::regex playerNamesRegex(u8R"foo("playerNames":\["A","B","C","D","E","F","\\u6587\\u5B57"\])foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, playerNamesRegex));
    std::regex dealerNameRegex(u8R"foo("dealerName":"C")foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, dealerNameRegex));
    std::regex sitOutSchemeRegex(u8R"foo("sitOutScheme":\[2,4\])foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, sitOutSchemeRegex));
    std::regex previousDealerNameRegex(u8R"foo("previousDealerName":"Z")foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, previousDealerNameRegex));

    std::regex dealKindRegex(u8R"foo("kind":"deal")foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, dealKindRegex));
    std::regex playersRegex(u8R"foo("players":7)foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, playersRegex));
    std::regex numberOfEventsRegex(u8R"foo("numberOfEvents":2)foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, numberOfEventsRegex));
    std::regex changesRegex(u8R"foo("changes":\[\{)foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, sitOutSchemeRegex));
    std::regex objectARegex(u8R"foo(\{"name":"A","diff":1\})foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, objectARegex));
    std::regex objectBRegex(u8R"foo(\{"name":"B","diff":1\})foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, objectBRegex));
    std::regex objectCRegex(u8R"foo(\{"name":"C","diff":-1\})foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, objectCRegex));
    std::regex objectDRegex(u8R"foo(\{"name":"D","diff":-1\})foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, objectDRegex));

    std::regex mandatorySoloTriggerKindRegex(u8R"foo("kind":"mandatorySoloTrigger")foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(persisted, mandatorySoloTriggerKindRegex));
}

TEST(BackendTest, MemoryRepositoryShallCorrectlyLoadEntries)
{
    std::string content(u8R"foo({
    "dataVersion": "2",
    "data": [
        {
            "kind": "playersSet",
            "playerNames": [
                "A",
                "B",
                "C",
                "D",
                "E",
                "F",
                "G"
            ],
            "dealerName": "C",
            "sitOutScheme": [
                2,
                4
            ],
            "previousDealerName": "B"
        },
        {
            "kind": "deal",
            "players": 7,
            "numberOfEvents": 2,
            "changes": [
                {
                    "name": "A",
                    "diff": 1
                },
                {
                    "name": "B",
                    "diff": 1
                },
                {
                    "name": "C",
                    "diff": -1
                },
                {
                    "name": "D",
                    "diff": -1
                }
            ]
        },
        {
            "kind": "mandatorySoloTrigger"
        }
    ]
})foo");

    MemoryRepository repo;
    std::string id = u8"someId";
    repo.SetByIdentifier(id, content);

    // Act
    auto result = repo.Load(id);

    // Assert
    ASSERT_EQ(3, result.size());

    auto playersSet = std::static_pointer_cast<Backend::PlayersSet>(result[0]);
    EXPECT_THAT(playersSet->Players(), ::testing::ElementsAre(std::string(u8"A"), std::string(u8"B"), std::string(u8"C"), std::string(u8"D"), std::string(u8"E"), std::string(u8"F"), std::string(u8"G")));
    EXPECT_STREQ(u8"C", playersSet->Dealer().c_str());
    EXPECT_THAT(playersSet->SitOutScheme(), ::testing::ElementsAre(2, 4));
    EXPECT_STREQ(u8"B", playersSet->PreviousDealer().c_str());

    auto deal = std::static_pointer_cast<Backend::Deal>(result[1]);
    EXPECT_EQ(7, deal->Players().Value());
    EXPECT_EQ(2, deal->NumberOfEvents().Value());
    auto changes = deal->Changes();
    EXPECT_STREQ(u8"A", changes[0].first.c_str());
    EXPECT_STREQ(u8"B", changes[1].first.c_str());
    EXPECT_STREQ(u8"C", changes[2].first.c_str());
    EXPECT_STREQ(u8"D", changes[3].first.c_str());
    EXPECT_EQ( 1, changes[0].second);
    EXPECT_EQ( 1, changes[1].second);
    EXPECT_EQ(-1, changes[2].second);
    EXPECT_EQ(-1, changes[3].second);

    auto mandatorySoloTrigger = result[2];
    EXPECT_EQ(Backend::Entry::Kind::MandatorySoloTrigger, mandatorySoloTrigger->Kind());
}

TEST(BackendTest, MemoryRepositoryRoundtripShallWorkCorrectly)
{
    // Arrange
    std::vector<std::shared_ptr<Backend::Entry>> entries;

    entries.push_back(std::make_shared<Backend::PlayersSet>(
                          std::vector<std::string>
                          {
                              u8"A",
                              u8"B",
                              u8"C",
                              u8"D",
                              u8"E",
                              u8"F",
                              u8"文字",
                          },
                          u8"C",
                          std::set<unsigned int> { 2, 4 },
                          u8"Z"));
    entries.push_back(std::make_shared<Backend::Deal>(
                          std::vector<std::pair<std::string, int>>
                          {
                              std::make_pair<std::string, int>(u8"A", 1),
                              std::make_pair<std::string, int>(u8"B", 1),
                              std::make_pair<std::string, int>(u8"C", -1),
                              std::make_pair<std::string, int>(u8"D", -1)
                          },
                          Backend::NumberOfEvents(2),
                          Backend::Players(7)));
    entries.push_back(std::make_shared<Backend::MandatorySoloTrigger>());

    MemoryRepository repo;
    std::string id = u8"someId";

    // Act
    repo.Save(entries, id);
    auto result = repo.Load(id);

    // Assert
    ASSERT_EQ(3, entries.size());

    auto playersSet = std::static_pointer_cast<Backend::PlayersSet>(result[0]);
    EXPECT_THAT(playersSet->Players(), ::testing::ElementsAre(std::string(u8"A"), std::string(u8"B"), std::string(u8"C"), std::string(u8"D"), std::string(u8"E"), std::string(u8"F"), std::string(u8"文字")));
    EXPECT_STREQ(u8"C", playersSet->Dealer().c_str());
    EXPECT_THAT(playersSet->SitOutScheme(), ::testing::ElementsAre(2, 4));
    EXPECT_STREQ(u8"Z", playersSet->PreviousDealer().c_str());

    auto deal = std::static_pointer_cast<Backend::Deal>(result[1]);
    EXPECT_EQ(7, deal->Players().Value());
    EXPECT_EQ(2, deal->NumberOfEvents().Value());
    auto changes = deal->Changes();
    EXPECT_STREQ(u8"A", changes[0].first.c_str());
    EXPECT_STREQ(u8"B", changes[1].first.c_str());
    EXPECT_STREQ(u8"C", changes[2].first.c_str());
    EXPECT_STREQ(u8"D", changes[3].first.c_str());
    EXPECT_EQ( 1, changes[0].second);
    EXPECT_EQ( 1, changes[1].second);
    EXPECT_EQ(-1, changes[2].second);
    EXPECT_EQ(-1, changes[3].second);

    auto mandatorySoloTrigger = result[2];
    EXPECT_EQ(Backend::Entry::Kind::MandatorySoloTrigger, mandatorySoloTrigger->Kind());
}

TEST(BackendTest, MemoryRepositoryShallThrowIfNoContentFound)
{
    MemoryRepository repo;
    std::string id = u8"someId ä 文字";

    // Act, Assert
    EXPECT_THROW({
        try
        {
            auto result = repo.Load(id);
        }
        catch( const std::exception& e )
        {
            EXPECT_STREQ(u8"content not found by identifier: \"someId ä 文字\"", e.what());
            throw;
        }
    }, std::exception);
}

#endif // TST_MEMORYREPOSITORY_H
