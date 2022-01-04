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

#include "../Backend/deserializer.h"
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include <regex>
#include <sstream>

#ifndef TST_DESERIALIZER_H
#define TST_DESERIALIZER_H

TEST(BackendTest, SerializationOfEntriesShallWorkCorrectly) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    std::stringstream ss;
    Backend::DeSerializer ds;
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
                              u8"G",
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

    // Act
    ds.Serialize(entries, ss);

    entries.clear();

    // Assert
    auto result = ss.str();

    ASSERT_TRUE(result.length() > 0);
    std::regex dataVersionRegex(u8R"foo("dataVersion":"[0-9]+")foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, dataVersionRegex));

    std::regex playersSetKindRegex(u8R"foo("kind":"playersSet")foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, playersSetKindRegex));
    std::regex playerNamesRegex(u8R"foo("playerNames":\["A","B","C","D","E","F","G"\])foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, playerNamesRegex));
    std::regex dealerNameRegex(u8R"foo("dealerName":"C")foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, dealerNameRegex));
    std::regex sitOutSchemeRegex(u8R"foo("sitOutScheme":\[2,4\])foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, sitOutSchemeRegex));
    std::regex previousDealerNameRegex(u8R"foo("previousDealerName":"Z")foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, previousDealerNameRegex));

    std::regex dealKindRegex(u8R"foo("kind":"deal")foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, dealKindRegex));
    std::regex playersRegex(u8R"foo("players":7)foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, playersRegex));
    std::regex numberOfEventsRegex(u8R"foo("numberOfEvents":2)foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, numberOfEventsRegex));
    std::regex changesRegex(u8R"foo("changes":\[\{)foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, sitOutSchemeRegex));
    std::regex objectARegex(u8R"foo(\{"name":"A","diff":1\})foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, objectARegex));
    std::regex objectBRegex(u8R"foo(\{"name":"B","diff":1\})foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, objectBRegex));
    std::regex objectCRegex(u8R"foo(\{"name":"C","diff":-1\})foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, objectCRegex));
    std::regex objectDRegex(u8R"foo(\{"name":"D","diff":-1\})foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, objectDRegex));

    std::regex mandatorySoloTriggerKindRegex(u8R"foo("kind":"mandatorySoloTrigger")foo", std::regex_constants::ECMAScript);
    EXPECT_TRUE(std::regex_search(result, mandatorySoloTriggerKindRegex));
}

TEST(BackendTest, DeserializationOfEntriesShallWorkCorrectly) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    const char * json = u8R"foo(
{
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
}
)foo";

    std::stringstream ss;
    ss << json;

    Backend::DeSerializer ds;

    // Act
    auto result = ds.Deserialize(ss);

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

TEST(BackendTest, DeserializationRoundtripShallWorkCorrectly) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    std::stringstream ss;
    Backend::DeSerializer ds;
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
                              u8"G",
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

    // Act
    ds.Serialize(entries, ss);
    auto result = ds.Deserialize(ss);

    entries.clear();

    // Assert
    ASSERT_EQ(3, result.size());

    auto playersSet = std::static_pointer_cast<Backend::PlayersSet>(result[0]);
    EXPECT_THAT(playersSet->Players(), ::testing::ElementsAre(std::string(u8"A"), std::string(u8"B"), std::string(u8"C"), std::string(u8"D"), std::string(u8"E"), std::string(u8"F"), std::string(u8"G")));
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

struct TestDeserializationErrorResult
{
    std::string testname;
    std::string json;
    friend std::ostream& operator<<(std::ostream& wos, const TestDeserializationErrorResult& obj)
    {
        return wos
                << u8"testname: " << obj.testname
                << u8" json: " << obj.json;
    }
};

class DeserializationErrorTest : public testing::TestWithParam<TestDeserializationErrorResult>
{
};

INSTANTIATE_TEST_SUITE_P(BackendTest, DeserializationErrorTest, // clazy:exclude=non-pod-global-static //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, fuchsia-statically-constructed-objects)
    testing::Values(
    TestDeserializationErrorResult{u8"NotObject", u8R"foo([])foo"},
    TestDeserializationErrorResult{u8"EmptyObject", u8R"foo({})foo"},
    TestDeserializationErrorResult{u8"DataVersionNotCorrect1", u8R"foo({"dataVersion":0.0})foo"},
    TestDeserializationErrorResult{u8"DataVersionNotCorrect2", u8R"foo({"dataVersion":"a"})foo"},
    TestDeserializationErrorResult{u8"NoDataMember", u8R"foo({"dataVersion":"1"})foo"},
    TestDeserializationErrorResult{u8"NoKindMember", u8R"foo({"dataVersion":"1","data":[false]})foo"},
    TestDeserializationErrorResult{u8"NoKindMember", u8R"foo({"dataVersion":"1","data":[{"nokind":""}]})foo"},
    TestDeserializationErrorResult{u8"InvalidKindMember", u8R"foo({"dataVersion":"1","data":[{"kind":{}}]})foo"},
    TestDeserializationErrorResult{u8"InvalidKindMember", u8R"foo({"dataVersion":"1","data":[{"kind":"invalid"}]})foo"},
    TestDeserializationErrorResult{u8"NoPlayerNamesMember", u8R"foo({"dataVersion":"1","data":[{"kind":"playersSet","dealerName":"C","sitOutScheme":[2,4]}]})foo"},
    TestDeserializationErrorResult{u8"InvalidPlayerNamesMember", u8R"foo({"dataVersion":"1","data":[{"kind":"playersSet","playerNames":{},"dealerName":"C","sitOutScheme":[2,4]}]})foo"},
    TestDeserializationErrorResult{u8"PlayerNameNotString", u8R"foo({"dataVersion":"1","data":[{"kind":"playersSet","playerNames":["A",{},"C","D","E","F","G"],"dealerName":"C","sitOutScheme":[2,4]}]})foo"},
    TestDeserializationErrorResult{u8"NoDealerMember", u8R"foo({"dataVersion":"1","data":[{"kind":"playersSet","playerNames":["A","B","C","D","E","F","G"],"sitOutScheme":[2,4]}]})foo"},
    TestDeserializationErrorResult{u8"InvalidDealerMember", u8R"foo({"dataVersion":"1","data":[{"kind":"playersSet","playerNames":["A","B","C","D","E","F","G"],"dealerName":{},"sitOutScheme":[2,4]}]})foo"},
    TestDeserializationErrorResult{u8"NoSitOutSchemeMember", u8R"foo({"dataVersion":"1","data":[{"kind":"playersSet","playerNames":["A","B","C","D","E","F","G"],"dealerName":"C"}]})foo"},
    TestDeserializationErrorResult{u8"InvalidSitOutSchemeMember", u8R"foo({"dataVersion":"1","data":[{"kind":"playersSet","playerNames":["A","B","C","D","E","F","G"],"dealerName":"C","sitOutScheme":{}}]})foo"},
    TestDeserializationErrorResult{u8"SitOutSchemeItemNotNumber", u8R"foo({"dataVersion":"1","data":[{"kind":"playersSet","playerNames":["A","B","C","D","E","F","G"],"dealerName":"C","sitOutScheme":[1,true]}]})foo"},
    TestDeserializationErrorResult{u8"SitOutSchemeItemNotInt", u8R"foo({"dataVersion":"1","data":[{"kind":"playersSet","playerNames":["A","B","C","D","E","F","G"],"dealerName":"C","sitOutScheme":[1,5.1]}]})foo"},
    TestDeserializationErrorResult{u8"NoPreviousDealerMember", u8R"foo({"dataVersion":"1","data":[{"kind":"playersSet","playerNames":["A","B","C","D","E","F","G"],"dealerName":"C","sitOutScheme":[1,3]}]})foo"},
    TestDeserializationErrorResult{u8"InvalidPreviousDealerMember", u8R"foo({"dataVersion":"1","data":[{"kind":"playersSet","playerNames":["A","B","C","D","E","F","G"],"dealerName":"C","sitOutScheme":[1,3],"previousDealer":{}}]})foo"},
    TestDeserializationErrorResult{u8"NoPlayersMember", u8R"foo({"dataVersion":"1","data":[{"kind":"deal","numberOfEvents":2,"changes":[{"name":"A","diff":1},{"name":"B","diff":1},{"name":"C","diff":-1},{"name":"D","diff":-1}]}]})foo"},
    TestDeserializationErrorResult{u8"InvalidPlayersMember", u8R"foo({"dataVersion":"1","data":[{"kind":"deal","players":{},"numberOfEvents":2,"changes":[{"name":"A","diff":1},{"name":"B","diff":1},{"name":"C","diff":-1},{"name":"D","diff":-1}]}]})foo"},
    TestDeserializationErrorResult{u8"NoNumberOfEventsMember", u8R"foo({"dataVersion":"1","data":[{"kind":"deal","players":7,"changes":[{"name":"A","diff":1},{"name":"B","diff":1},{"name":"C","diff":-1},{"name":"D","diff":-1}]}]})foo"},
    TestDeserializationErrorResult{u8"InvalidNumberOfEventsMember", u8R"foo({"dataVersion":"1","data":[{"kind":"deal","players":7,"numberOfEvents":{},"changes":[{"name":"A","diff":1},{"name":"B","diff":1},{"name":"C","diff":-1},{"name":"D","diff":-1}]}]})foo"},
    TestDeserializationErrorResult{u8"NoChangesMember", u8R"foo({"dataVersion":"1","data":[{"kind":"deal","players":7,"numberOfEvents":2}]})foo"},
    TestDeserializationErrorResult{u8"InvalidChangesMember", u8R"foo({"dataVersion":"1","data":[{"kind":"deal","players":7,"numberOfEvents":2,"changes":{}}]})foo"},
    TestDeserializationErrorResult{u8"ChangesItemNotObject", u8R"foo({"dataVersion":"1","data":[{"kind":"deal","players":7,"numberOfEvents":2,"changes":[true,{"name":"B","diff":1},{"name":"C","diff":-1},{"name":"D","diff":-1}]}]})foo"},
    TestDeserializationErrorResult{u8"ChangesItemNoName", u8R"foo({"dataVersion":"1","data":[{"kind":"deal","players":7,"numberOfEvents":2,"changes":[{"diff":1},{"name":"B","diff":1},{"name":"C","diff":-1},{"name":"D","diff":-1}]}]})foo"},
    TestDeserializationErrorResult{u8"ChangesItemNameNotString", u8R"foo({"dataVersion":"1","data":[{"kind":"deal","players":7,"numberOfEvents":2,"changes":[{"name":42,"diff":1},{"name":"B","diff":1},{"name":"C","diff":-1},{"name":"D","diff":-1}]}]})foo"},
    TestDeserializationErrorResult{u8"ChangesItemNoDiff", u8R"foo({"dataVersion":"1","data":[{"kind":"deal","players":7,"numberOfEvents":2,"changes":[{"name":"A"},{"name":"B","diff":1},{"name":"C","diff":-1},{"name":"D","diff":-1}]}]})foo"},
    TestDeserializationErrorResult{u8"ChangesItemDiffNotInt", u8R"foo({"dataVersion":"1","data":[{"kind":"deal","players":7,"numberOfEvents":2,"changes":[{"name":"A","diff":{}},{"name":"B","diff":1},{"name":"C","diff":-1},{"name":"D","diff":-1}]}]})foo"}
    ));

TEST_P(DeserializationErrorTest, GivenBadJsonDeserializationShallGiveError) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    TestDeserializationErrorResult tder = GetParam();
    std::stringstream ss;
    ss << tder.json;
    ss.seekg(0, std::ios::beg);

    Backend::DeSerializer ds;

    // Act, Assert
    EXPECT_THROW({ auto result = ds.Deserialize(ss); }, std::exception); //NOLINT(cppcoreguidelines-avoid-goto, hicpp-avoid-goto)
}

#endif // TST_DESERIALIZER_H
