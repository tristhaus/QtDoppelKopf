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

#include "deserializer.h"
#include "rapidjson/writer.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/istreamwrapper.h"

#define DATAVERSION u8"2"

Backend::DeSerializer::DeSerializer()
{
}

void Backend::DeSerializer::Serialize(std::vector<std::shared_ptr<Backend::Entry>> entries, std::ostream & os)
{
    rapidjson::GenericDocument<rapidjson::UTF8<char>> document;
    document.SetObject();
    auto & allocator = document.GetAllocator();

    rapidjson::GenericValue<rapidjson::UTF8<char>> key, value;

    key.SetString(KeyDataVersion, static_cast<rapidjson::SizeType>(strlen(KeyDataVersion)), allocator);
    value.SetString(DATAVERSION);
    document.AddMember(key, value, allocator);

    rapidjson::GenericValue<rapidjson::UTF8<char>> array;
    array.SetArray();

    for (auto & entry : entries)
    {
        this->SerializeEntry(entry, value, allocator);

        array.PushBack(value, allocator);
    }

    key.SetString(KeyData, static_cast<rapidjson::SizeType>(strlen(KeyData)), allocator);
    document.AddMember(key, array, allocator);

    rapidjson::OStreamWrapper osw(os);

    rapidjson::Writer<rapidjson::OStreamWrapper, rapidjson::UTF8<char>, rapidjson::ASCII<char>> writer(osw);
    document.Accept(writer);
}

std::vector<std::shared_ptr<Backend::Entry>> Backend::DeSerializer::Deserialize(std::istream & is)
{
    rapidjson::IStreamWrapper isw(is);

    rapidjson::GenericDocument<rapidjson::UTF8<char>> document;
    document.ParseStream(isw);

    if(!(document.IsObject()))
    {
        throw std::exception(u8"did not parse to object");
    }

    if(!(document.HasMember(KeyDataVersion) && document[KeyDataVersion].IsString() && std::strcmp(document[KeyDataVersion].GetString(), DATAVERSION) == 0))
    {
        throw std::exception(u8"no valid data version found");
    }

    if(!(document.HasMember(KeyData) && document[KeyData].IsArray()))
    {
        throw std::exception(u8"no valid data member found");
    }

    std::vector<std::shared_ptr<Backend::Entry>> entries;

    auto & datas = document[KeyData];
    auto datasIt = datas.Begin();
    auto datasEnd = datas.End();

    for(; datasIt != datasEnd; ++datasIt)
    {
        if(!datasIt->IsObject())
        {
            throw std::exception(u8"entry is not object");
        }

        if(!datasIt->HasMember(KeyKind))
        {
            throw std::exception(u8"missing kind in entry");
        }

        if(!(*datasIt)[KeyKind].IsString())
        {
            throw std::exception(u8"kind is not string");
        }

        auto kind = (*datasIt)[KeyKind].GetString();
        if(std::strcmp(kind, ValuePlayersSet) == 0)
        {
            auto entry = this->DeserializePlayersSet(datasIt);
            entries.push_back(entry);
        }
        else if(std::strcmp(kind, ValueDeal) == 0)
        {
            auto entry = this->DeserializeDeal(datasIt);
            entries.push_back(entry);
        }
        else if(std::strcmp(kind, ValueMandatorySoloTrigger) == 0)
        {
            entries.push_back(std::make_shared<MandatorySoloTrigger>());
        }
        else
        {
            throw std::exception((std::string(u8"unknown kind value in data: \"") + kind + std::string("\"")).c_str());
        }
    }

    return entries;
}

void Backend::DeSerializer::SerializeEntry(std::shared_ptr<Entry> entry,
                                           rapidjson::GenericValue<rapidjson::UTF8<char>> & serializedEntry,
                                           rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator)
{
    switch(entry->Kind())
    {
    case Entry::Kind::PlayersSet:
        this->SerializePlayersSet(std::static_pointer_cast<PlayersSet>(entry), serializedEntry, allocator);
        break;
    case Entry::Kind::Deal:
        this->SerializeDeal(std::static_pointer_cast<Deal>(entry), serializedEntry, allocator);
        break;
    case Entry::Kind::MandatorySoloTrigger:
        this->SerializeMandatorySoloTrigger(serializedEntry, allocator);
        break;
    default:
        throw std::exception(u8"value of Entry::Kind not handled");
    }
}

void Backend::DeSerializer::SerializePlayersSet(std::shared_ptr<PlayersSet> playersSet,
                                                rapidjson::GenericValue<rapidjson::UTF8<char>> & serializedEntry,
                                                rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator)
{
    serializedEntry.SetObject();

    rapidjson::GenericValue<rapidjson::UTF8<char>> key, value, helper;

    key.SetString(KeyKind, static_cast<rapidjson::SizeType>(strlen(KeyKind)), allocator);
    value.SetString(ValuePlayersSet, static_cast<rapidjson::SizeType>(strlen(ValuePlayersSet)), allocator);
    serializedEntry.AddMember(key, value, allocator);

    key.SetString(KeyPlayerNames, static_cast<rapidjson::SizeType>(strlen(KeyPlayerNames)), allocator);
    value.SetArray();
    for (auto & playerName : playersSet->Players())
    {
        helper.SetString(playerName.c_str(), static_cast<rapidjson::SizeType>(strlen(playerName.c_str())), allocator);
        value.PushBack(helper, allocator);
    }
    serializedEntry.AddMember(key, value, allocator);

    key.SetString(KeyDealerName, static_cast<rapidjson::SizeType>(strlen(KeyDealerName)), allocator);
    value.SetString(playersSet->Dealer().c_str(), static_cast<rapidjson::SizeType>(strlen(playersSet->Dealer().c_str())), allocator);
    serializedEntry.AddMember(key, value, allocator);

    key.SetString(KeySitOutScheme, static_cast<rapidjson::SizeType>(strlen(KeySitOutScheme)), allocator);
    value.SetArray();
    for (auto & sitOutItem : playersSet->SitOutScheme())
    {
        helper.SetInt(sitOutItem);
        value.PushBack(helper, allocator);
    }

    serializedEntry.AddMember(key, value, allocator);

    key.SetString(KeyPreviousDealerName, static_cast<rapidjson::SizeType>(strlen(KeyPreviousDealerName)), allocator);
    value.SetString(playersSet->PreviousDealer().c_str(), static_cast<rapidjson::SizeType>(strlen(playersSet->PreviousDealer().c_str())), allocator);
    serializedEntry.AddMember(key, value, allocator);
}

void Backend::DeSerializer::SerializeDeal(std::shared_ptr<Deal> deal,
                                          rapidjson::GenericValue<rapidjson::UTF8<char>> & serializedEntry,
                                          rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator)
{
    serializedEntry.SetObject();

    rapidjson::GenericValue<rapidjson::UTF8<char>> key, value, changeObject, changeKey, changeValue;

    key.SetString(KeyKind, static_cast<rapidjson::SizeType>(strlen(KeyKind)), allocator);
    value.SetString(ValueDeal, static_cast<rapidjson::SizeType>(strlen(ValueDeal)), allocator);
    serializedEntry.AddMember(key, value, allocator);

    key.SetString(KeyPlayers, static_cast<rapidjson::SizeType>(strlen(KeyPlayers)), allocator);
    value.SetInt(deal->Players().Value());
    serializedEntry.AddMember(key, value, allocator);

    key.SetString(KeyNumberOfEvents, static_cast<rapidjson::SizeType>(strlen(KeyNumberOfEvents)), allocator);
    value.SetInt(deal->NumberOfEvents().Value());
    serializedEntry.AddMember(key, value, allocator);

    key.SetString(KeyChanges, static_cast<rapidjson::SizeType>(strlen(KeyChanges)), allocator);
    value.SetArray();
    for (auto & change : deal->Changes())
    {
        changeObject.SetObject();

        changeKey.SetString(KeyChangeName, static_cast<rapidjson::SizeType>(strlen(KeyChangeName)), allocator);
        changeValue.SetString(change.first.c_str(), static_cast<rapidjson::SizeType>(strlen(change.first.c_str())), allocator);
        changeObject.AddMember(changeKey, changeValue, allocator);

        changeKey.SetString(KeyChangeDiff, static_cast<rapidjson::SizeType>(strlen(KeyChangeDiff)), allocator);
        changeValue.SetInt(change.second);
        changeObject.AddMember(changeKey, changeValue, allocator);

        value.PushBack(changeObject, allocator);
    }

    serializedEntry.AddMember(key, value, allocator);
}

void Backend::DeSerializer::SerializeMandatorySoloTrigger(rapidjson::GenericValue<rapidjson::UTF8<char>> & serializedEntry,
                                                          rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator)
{
    serializedEntry.SetObject();

    rapidjson::GenericValue<rapidjson::UTF8<char>> key, value;

    key.SetString(KeyKind, static_cast<rapidjson::SizeType>(strlen(KeyKind)), allocator);
    value.SetString(ValueMandatorySoloTrigger, static_cast<rapidjson::SizeType>(strlen(ValueMandatorySoloTrigger)), allocator);
    serializedEntry.AddMember(key, value, allocator);
}

std::shared_ptr<Backend::Entry> Backend::DeSerializer::DeserializePlayersSet(rapidjson::GenericValue<rapidjson::UTF8<char>> * data)
{
    if(!data->HasMember(KeyPlayerNames))
    {
        throw std::exception(u8"no member playerNames");
    }

    if(!(*data)[KeyPlayerNames].IsArray())
    {
        throw std::exception(u8"playerNames is not array");
    }

    auto & playerNames = (*data)[KeyPlayerNames];
    auto playerNamesIt = playerNames.Begin();
    auto playerNamesEnd = playerNames.End();

    std::vector<std::string> players;

    for(; playerNamesIt != playerNamesEnd; ++playerNamesIt)
    {
        if(!playerNamesIt->IsString())
        {
            throw std::exception(u8"player name is not a string");
        }

        players.push_back(playerNamesIt->GetString());
    }

    if(!data->HasMember(KeyDealerName))
    {
        throw std::exception(u8"no member dealerName");
    }

    if(!(*data)[KeyDealerName].IsString())
    {
        throw std::exception(u8"dealerName is not string");
    }

    auto dealer = (*data)[KeyDealerName].GetString();

    if(!data->HasMember(KeySitOutScheme))
    {
        throw std::exception(u8"no member sitOutScheme");
    }

    if(!(*data)[KeySitOutScheme].IsArray())
    {
        throw std::exception(u8"sitOutScheme is not array");
    }

    auto & scheme = (*data)[KeySitOutScheme];
    auto schemeIt = scheme.Begin();
    auto schemeEnd = scheme.End();

    std::set<unsigned int> sitOutScheme;

    for(; schemeIt != schemeEnd; ++schemeIt)
    {
        if(!schemeIt->IsInt())
        {
            throw std::exception(u8"sit out scheme item is not an int");
        }

        sitOutScheme.emplace(schemeIt->GetInt());
    }

    if(!data->HasMember(KeyPreviousDealerName))
    {
        throw std::exception(u8"no member previousDealerName");
    }

    if(!(*data)[KeyPreviousDealerName].IsString())
    {
        throw std::exception(u8"previousDealerName is not string");
    }

    auto previousDealer = (*data)[KeyPreviousDealerName].GetString();

    return std::make_shared<PlayersSet>(players, dealer, sitOutScheme, previousDealer);
}

std::shared_ptr<Backend::Entry> Backend::DeSerializer::DeserializeDeal(rapidjson::GenericValue<rapidjson::UTF8<char>> * data)
{
    if(!data->HasMember(KeyPlayers))
    {
        throw std::exception(u8"no member players");
    }

    if(!(*data)[KeyPlayers].IsInt())
    {
        throw std::exception(u8"players is not int");
    }

    unsigned int players = (*data)[KeyPlayers].GetInt();

    if(!data->HasMember(KeyNumberOfEvents))
    {
        throw std::exception(u8"no member numberOfEvents");
    }

    if(!(*data)[KeyNumberOfEvents].IsInt())
    {
        throw std::exception(u8"numberOfEvents is not int");
    }

    unsigned int numberOfEvents = (*data)[KeyNumberOfEvents].GetInt();

    if(!data->HasMember(KeyChanges))
    {
        throw std::exception(u8"no member changes");
    }

    if(!(*data)[KeyChanges].IsArray())
    {
        throw std::exception(u8"changes is not array");
    }

    auto & list = (*data)[KeyChanges];
    auto changesIt = list.Begin();
    auto changesEnd = list.End();

    std::vector<std::pair<std::string, int>> changes;

    for(; changesIt != changesEnd; ++changesIt)
    {
        if(!changesIt->IsObject())
        {
            throw std::exception(u8"changes item is not an object");
        }

        if(!changesIt->HasMember(KeyChangeName))
        {
            throw std::exception(u8"changes item does not have a name member");
        }

        if(!(*changesIt)[KeyChangeName].IsString())
        {
            throw std::exception(u8"change member name is not a string");
        }

        std::string name = (*changesIt)[KeyChangeName].GetString();

        if(!changesIt->HasMember(KeyChangeDiff))
        {
            throw std::exception(u8"changes item does not have a diff member");
        }

        if(!(*changesIt)[KeyChangeDiff].IsInt())
        {
            throw std::exception(u8"change member diff is not an int");
        }

        int diff = (*changesIt)[KeyChangeDiff].GetInt();

        changes.emplace_back(std::pair<std::string, int>(name, diff));
    }

    return std::make_shared<Deal>(changes, NumberOfEvents(numberOfEvents), Players(players));
}

#undef DATAVERSION
