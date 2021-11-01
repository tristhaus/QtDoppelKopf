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

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <regex>
#include <sstream>
#include "../Backend/deserializer.h"

#ifndef TST_DESERIALIZER_H
#define TST_DESERIALIZER_H

TEST(BackendTest, SerializationOfEntriesShallWorkCorrectly)
{
    // Arrange
    std::wstringstream ss;
    Backend::DeSerializer ds;
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
                              L"G",
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

    // Act
    ds.Serialize(entries, ss);

    entries.clear();

    // Assert
    auto result = ss.str();

    ASSERT_TRUE(result.length() > 0);
    std::wregex dataVersionRegex(LR"foo("dataVersion":"[0-9]+")foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, dataVersionRegex));

    std::wregex playersSetKindRegex(LR"foo("kind":"playersSet")foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, playersSetKindRegex));
    std::wregex playerNamesRegex(LR"foo("playerNames":\["A","B","C","D","E","F","G"\])foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, playerNamesRegex));
    std::wregex dealerNameRegex(LR"foo("dealerName":"C")foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, dealerNameRegex));
    std::wregex sitOutSchemeRegex(LR"foo("sitOutScheme":\[2,4\])foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, sitOutSchemeRegex));

    std::wregex dealKindRegex(LR"foo("kind":"deal")foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, dealKindRegex));
    std::wregex playersRegex(LR"foo("players":7)foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, playersRegex));
    std::wregex numberOfEventsRegex(LR"foo("numberOfEvents":2)foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, numberOfEventsRegex));
    std::wregex changesRegex(LR"foo("changes":\[\{)foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, sitOutSchemeRegex));
    std::wregex objectARegex(LR"foo(\{"name":"A","diff":1\})foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, objectARegex));
    std::wregex objectBRegex(LR"foo(\{"name":"B","diff":1\})foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, objectBRegex));
    std::wregex objectCRegex(LR"foo(\{"name":"C","diff":-1\})foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, objectCRegex));
    std::wregex objectDRegex(LR"foo(\{"name":"D","diff":-1\})foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, objectDRegex));

    std::wregex mandatorySoloTriggerKindRegex(LR"foo("kind":"mandatorySoloTrigger")foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, mandatorySoloTriggerKindRegex));
}

TEST(BackendTest, DeserializationOfEntriesShallWorkCorrectly)
{
    // Arrange
    const wchar_t * json = LR"foo(
{
    "dataVersion": "1",
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
            ]
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
}
)foo";

    std::wstringstream ss;
    ss << json;

    Backend::DeSerializer ds;

    // Act
    auto result = ds.Deserialize(ss);

    // Assert
    ASSERT_EQ(3, result.size());

    auto playersSet = std::static_pointer_cast<Backend::PlayersSet>(result[0]);
    EXPECT_THAT(playersSet->Players(), ::testing::ElementsAre(std::wstring(L"A"), std::wstring(L"B"), std::wstring(L"C"), std::wstring(L"D"), std::wstring(L"E"), std::wstring(L"F"), std::wstring(L"G")));
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

TEST(BackendTest, DeserializationRoundtripShallWorkCorrectly)
{
    // Arrange
    std::wstringstream ss;
    Backend::DeSerializer ds;
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
                              L"G",
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

    // Act
    ds.Serialize(entries, ss);
    auto result = ds.Deserialize(ss);

    entries.clear();

    // Assert
    ASSERT_EQ(3, result.size());

    auto playersSet = std::static_pointer_cast<Backend::PlayersSet>(result[0]);
    EXPECT_THAT(playersSet->Players(), ::testing::ElementsAre(std::wstring(L"A"), std::wstring(L"B"), std::wstring(L"C"), std::wstring(L"D"), std::wstring(L"E"), std::wstring(L"F"), std::wstring(L"G")));
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

struct TestDeserializationErrorResult
{
    std::wstring testname;
    std::wstring json;
    friend std::wostream& operator<<(std::wostream& wos, const TestDeserializationErrorResult& obj)
    {
        return wos
                << L"testname: " << obj.testname
                << L" json: " << obj.json;
    }
};

class DeserializationErrorTest : public testing::TestWithParam<TestDeserializationErrorResult>
{
};

INSTANTIATE_TEST_SUITE_P(BackendTest, DeserializationErrorTest, // clazy:exclude=non-pod-global-static
    testing::Values(
    TestDeserializationErrorResult{L"NotObject", LR"foo([])foo"},
    TestDeserializationErrorResult{L"EmptyObject", LR"foo({})foo"},
    TestDeserializationErrorResult{L"DataVersionNotCorrect1", LR"foo({"dataVersion":0.0})foo"},
    TestDeserializationErrorResult{L"DataVersionNotCorrect2", LR"foo({"dataVersion":"a"})foo"},
    TestDeserializationErrorResult{L"NoDataMember", LR"foo({"dataVersion":"1"})foo"},
    TestDeserializationErrorResult{L"NoKindMember", LR"foo({"dataVersion":"1","data":[false]})foo"},
    TestDeserializationErrorResult{L"NoKindMember", LR"foo({"dataVersion":"1","data":[{"nokind":""}]})foo"},
    TestDeserializationErrorResult{L"InvalidKindMember", LR"foo({"dataVersion":"1","data":[{"kind":{}}]})foo"},
    TestDeserializationErrorResult{L"InvalidKindMember", LR"foo({"dataVersion":"1","data":[{"kind":"invalid"}]})foo"},
    TestDeserializationErrorResult{L"NoPlayerNamesMember", LR"foo({"dataVersion":"1","data":[{"kind":"playersSet","dealerName":"C","sitOutScheme":[2,4]}]})foo"},
    TestDeserializationErrorResult{L"InvalidPlayerNamesMember", LR"foo({"dataVersion":"1","data":[{"kind":"playersSet","playerNames":{},"dealerName":"C","sitOutScheme":[2,4]}]})foo"},
    TestDeserializationErrorResult{L"PlayerNameNotString", LR"foo({"dataVersion":"1","data":[{"kind":"playersSet","playerNames":["A",{},"C","D","E","F","G"],"dealerName":"C","sitOutScheme":[2,4]}]})foo"},
    TestDeserializationErrorResult{L"NoDealerMember", LR"foo({"dataVersion":"1","data":[{"kind":"playersSet","playerNames":["A","B","C","D","E","F","G"],"sitOutScheme":[2,4]}]})foo"},
    TestDeserializationErrorResult{L"InvalidDealerMember", LR"foo({"dataVersion":"1","data":[{"kind":"playersSet","playerNames":["A","B","C","D","E","F","G"],"dealerName":{},"sitOutScheme":[2,4]}]})foo"},
    TestDeserializationErrorResult{L"NoSitOutSchemeMember", LR"foo({"dataVersion":"1","data":[{"kind":"playersSet","playerNames":["A","B","C","D","E","F","G"],"dealerName":"C"}]})foo"},
    TestDeserializationErrorResult{L"InvalidSitOutSchemeMember", LR"foo({"dataVersion":"1","data":[{"kind":"playersSet","playerNames":["A","B","C","D","E","F","G"],"dealerName":"C","sitOutScheme":{}}]})foo"},
    TestDeserializationErrorResult{L"SitOutSchemeItemNotNumber", LR"foo({"dataVersion":"1","data":[{"kind":"playersSet","playerNames":["A","B","C","D","E","F","G"],"dealerName":"C","sitOutScheme":[1,true]}]})foo"},
    TestDeserializationErrorResult{L"SitOutSchemeItemNotInt", LR"foo({"dataVersion":"1","data":[{"kind":"playersSet","playerNames":["A","B","C","D","E","F","G"],"dealerName":"C","sitOutScheme":[1,5.1]}]})foo"},
    TestDeserializationErrorResult{L"NoPlayersMember", LR"foo({"dataVersion":"1","data":[{"kind":"deal","numberOfEvents":2,"changes":[{"name":"A","diff":1},{"name":"B","diff":1},{"name":"C","diff":-1},{"name":"D","diff":-1}]}]})foo"},
    TestDeserializationErrorResult{L"InvalidPlayersMember", LR"foo({"dataVersion":"1","data":[{"kind":"deal","players":{},"numberOfEvents":2,"changes":[{"name":"A","diff":1},{"name":"B","diff":1},{"name":"C","diff":-1},{"name":"D","diff":-1}]}]})foo"},
    TestDeserializationErrorResult{L"NoNumberOfEventsMember", LR"foo({"dataVersion":"1","data":[{"kind":"deal","players":7,"changes":[{"name":"A","diff":1},{"name":"B","diff":1},{"name":"C","diff":-1},{"name":"D","diff":-1}]}]})foo"},
    TestDeserializationErrorResult{L"InvalidNumberOfEventsMember", LR"foo({"dataVersion":"1","data":[{"kind":"deal","players":7,"numberOfEvents":{},"changes":[{"name":"A","diff":1},{"name":"B","diff":1},{"name":"C","diff":-1},{"name":"D","diff":-1}]}]})foo"},
    TestDeserializationErrorResult{L"NoChangesMember", LR"foo({"dataVersion":"1","data":[{"kind":"deal","players":7,"numberOfEvents":2}]})foo"},
    TestDeserializationErrorResult{L"InvalidChangesMember", LR"foo({"dataVersion":"1","data":[{"kind":"deal","players":7,"numberOfEvents":2,"changes":{}}]})foo"},
    TestDeserializationErrorResult{L"ChangesItemNotObject", LR"foo({"dataVersion":"1","data":[{"kind":"deal","players":7,"numberOfEvents":2,"changes":[true,{"name":"B","diff":1},{"name":"C","diff":-1},{"name":"D","diff":-1}]}]})foo"},
    TestDeserializationErrorResult{L"ChangesItemNoName", LR"foo({"dataVersion":"1","data":[{"kind":"deal","players":7,"numberOfEvents":2,"changes":[{"diff":1},{"name":"B","diff":1},{"name":"C","diff":-1},{"name":"D","diff":-1}]}]})foo"},
    TestDeserializationErrorResult{L"ChangesItemNameNotString", LR"foo({"dataVersion":"1","data":[{"kind":"deal","players":7,"numberOfEvents":2,"changes":[{"name":42,"diff":1},{"name":"B","diff":1},{"name":"C","diff":-1},{"name":"D","diff":-1}]}]})foo"},
    TestDeserializationErrorResult{L"ChangesItemNoDiff", LR"foo({"dataVersion":"1","data":[{"kind":"deal","players":7,"numberOfEvents":2,"changes":[{"name":"A"},{"name":"B","diff":1},{"name":"C","diff":-1},{"name":"D","diff":-1}]}]})foo"},
    TestDeserializationErrorResult{L"ChangesItemDiffNotInt", LR"foo({"dataVersion":"1","data":[{"kind":"deal","players":7,"numberOfEvents":2,"changes":[{"name":"A","diff":{}},{"name":"B","diff":1},{"name":"C","diff":-1},{"name":"D","diff":-1}]}]})foo"}
    ));

TEST_P(DeserializationErrorTest, GivenBadJsonDeserializationShallGiveError)
{
    // Arrange
    TestDeserializationErrorResult tder = GetParam();
    std::wstringstream ss;
    ss << tder.json;
    ss.seekg(0, std::ios::beg);

    Backend::DeSerializer ds;

    // Act, Assert
    EXPECT_THROW({ auto result = ds.Deserialize(ss); }, std::exception);
}

#endif // TST_DESERIALIZER_H
