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

#include "../Backend/diskrepository.h"
#include <filesystem>
#include <fstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#ifndef TST_DISKREPOSITORY_H
#define TST_DISKREPOSITORY_H

#if defined(_USE_LONG_TEST)
TEST(BackendTest, DiskRepositoryShallCorrectlyRoundtripGame) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    auto tempFile = std::filesystem::temp_directory_path() / std::filesystem::path(u8"qtdoppelkopf.testing.文字.temp.file");
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
                          "Z"));
    entries.push_back(std::make_shared<Backend::Deal>(
                          std::vector<std::pair<std::string, int>>
                          {
                              std::make_pair<std::string, int>("A", 1),
                              std::make_pair<std::string, int>("B", 1),
                              std::make_pair<std::string, int>("C", -1),
                              std::make_pair<std::string, int>("D", -1)
                          },
                          Backend::NumberOfEvents(2),
                          Backend::Players(7)));
    entries.push_back(std::make_shared<Backend::MandatorySoloTrigger>());

    Backend::DiskRepository repo;
    auto id = tempFile.u8string();

    // Act
    repo.Save(entries, id);
    auto result = repo.Load(id);

    // Assert
    ASSERT_EQ(3, entries.size());

    auto playersSet = std::static_pointer_cast<Backend::PlayersSet>(result[0]);
    EXPECT_THAT(playersSet->Players(), ::testing::ElementsAre(std::string("A"), std::string("B"), std::string("C"), std::string("D"), std::string("E"), std::string("F"), std::string("文字")));
    EXPECT_STREQ("C", playersSet->Dealer().c_str());
    EXPECT_THAT(playersSet->SitOutScheme(), ::testing::ElementsAre(2, 4));
    EXPECT_STREQ("Z", playersSet->PreviousDealer().c_str());

    auto deal = std::static_pointer_cast<Backend::Deal>(result[1]);
    EXPECT_EQ(7, deal->Players().Value());
    EXPECT_EQ(2, deal->NumberOfEvents().Value());
    auto changes = deal->Changes();
    EXPECT_STREQ("A", changes[0].first.c_str());
    EXPECT_STREQ("B", changes[1].first.c_str());
    EXPECT_STREQ("C", changes[2].first.c_str());
    EXPECT_STREQ("D", changes[3].first.c_str());
    EXPECT_EQ( 1, changes[0].second);
    EXPECT_EQ( 1, changes[1].second);
    EXPECT_EQ(-1, changes[2].second);
    EXPECT_EQ(-1, changes[3].second);

    auto mandatorySoloTrigger = result[2];
    EXPECT_EQ(Backend::Entry::Kind::MandatorySoloTrigger, mandatorySoloTrigger->Kind());

    if(std::filesystem::exists(tempFile) && !std::filesystem::is_directory(tempFile))
    {
        std::filesystem::remove(tempFile);
    }
}
#endif // _USE_LONG_TEST

#endif // TST_DISKREPOSITORY_H
