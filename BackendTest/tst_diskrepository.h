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

#include <filesystem>
#include <fstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../Backend/diskrepository.h"

#ifndef TST_DISKREPOSITORY_H
#define TST_DISKREPOSITORY_H

#if defined(_USE_LONG_TEST)
TEST(BackendTest, DiskRepositoryShallCorrectlyRoundtripGame)
{
    // Arrange
    auto tempFile = std::filesystem::temp_directory_path() / std::filesystem::path(L"qtdoppelkopf.testing.文字.temp.file");
    std::vector<std::shared_ptr<Backend::Entry>> entries;

    entries.push_back(std::make_shared<Backend::PlayersSet>(
                          std::vector<std::wstring>
                          {
                              L"A",
                              L"B",
                              L"C",
                              L"D",
                              L"E",
                              L"F",
                              L"文字",
                          },
                          L"C",
                          std::set<unsigned int> { 2, 4 }));
    entries.push_back(std::make_shared<Backend::Deal>(
                          std::vector<std::pair<std::wstring, int>>
                          {
                              std::make_pair<std::wstring, int>(L"A", 1),
                              std::make_pair<std::wstring, int>(L"B", 1),
                              std::make_pair<std::wstring, int>(L"C", -1),
                              std::make_pair<std::wstring, int>(L"D", -1)
                          },
                          Backend::NumberOfEvents(2),
                          Backend::Players(7)));
    entries.push_back(std::make_shared<Backend::MandatorySoloTrigger>());

    Backend::DiskRepository repo;
    std::wstring id = L"someId";

    // Act
    repo.Save(entries, id);
    auto result = repo.Load(id);

    // Assert
    ASSERT_EQ(3, entries.size());

    auto playersSet = std::static_pointer_cast<Backend::PlayersSet>(result[0]);
    EXPECT_THAT(playersSet->Players(), ::testing::ElementsAre(std::wstring(L"A"), std::wstring(L"B"), std::wstring(L"C"), std::wstring(L"D"), std::wstring(L"E"), std::wstring(L"F"), std::wstring(L"文字")));
    EXPECT_STREQ(L"C", playersSet->Dealer().c_str());
    EXPECT_THAT(playersSet->SitOutScheme(), ::testing::ElementsAre(2, 4));

    auto deal = std::static_pointer_cast<Backend::Deal>(result[1]);
    EXPECT_EQ(7, deal->Players().Value());
    EXPECT_EQ(2, deal->NumberOfEvents().Value());
    auto changes = deal->Changes();
    EXPECT_STREQ(L"A", changes[0].first.c_str());
    EXPECT_STREQ(L"B", changes[1].first.c_str());
    EXPECT_STREQ(L"C", changes[2].first.c_str());
    EXPECT_STREQ(L"D", changes[3].first.c_str());
    EXPECT_EQ( 1, changes[0].second);
    EXPECT_EQ( 1, changes[1].second);
    EXPECT_EQ(-1, changes[2].second);
    EXPECT_EQ(-1, changes[3].second);

    auto mandatorySoloTrigger = result[2];
    EXPECT_EQ(Backend::Entry::Kind::MandatorySoloTrigger, mandatorySoloTrigger->Kind());
}
#endif // _USE_LONG_TEST

#endif // TST_DISKREPOSITORY_H
