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

#include <iostream>
#include <vector>
#include "rapidjson/document.h"
#include "entry.h"
#include "playersset.h"
#include "deal.h"
#include "mandatorysolotrigger.h"

#ifndef DESERIALIZER_H
#define DESERIALIZER_H

namespace Backend
{
    /*!
     * \brief The DeSerializer class provides de/serialization of entries.
     */
    class DeSerializer
    {
    private:
        constexpr static const wchar_t * const KeyDataVersion = L"dataVersion";
        constexpr static const wchar_t * const KeyData = L"data";

        constexpr static const wchar_t * const KeyKind = L"kind";
        constexpr static const wchar_t * const ValuePlayersSet = L"playersSet";
        constexpr static const wchar_t * const ValueDeal = L"deal";
        constexpr static const wchar_t * const ValueMandatorySoloTrigger = L"mandatorySoloTrigger";

        constexpr static const wchar_t * const KeyPlayerNames = L"playerNames";
        constexpr static const wchar_t * const KeyDealerName = L"dealerName";
        constexpr static const wchar_t * const KeySitOutScheme = L"sitOutScheme";

        constexpr static const wchar_t * const KeyPlayers = L"players";
        constexpr static const wchar_t * const KeyNumberOfEvents = L"numberOfEvents";

        constexpr static const wchar_t * const KeyChanges = L"changes";
        constexpr static const wchar_t * const KeyChangeName = L"name";
        constexpr static const wchar_t * const KeyChangeDiff = L"diff";

    public:
        /*!
         * \brief Initializes a new instance.
         */
        DeSerializer();

        /*!
         * \brief Serialize the entries into the stream as JSON.
         * \param entries The entries to serialize.
         * \param wos The stream to serialize into.
         */
        void Serialize(std::vector<std::shared_ptr<Entry>> entries, std::wostream & wos);

        /*!
         * \brief Deserialize from the stream into the return value.
         * \param wis The stream to deserialize from.
         * \return The deserialized entries.
         */
        std::vector<std::shared_ptr<Entry>> Deserialize(std::wistream & wis);

    private:
        void SerializeEntry(std::shared_ptr<Entry> entry,
                            rapidjson::GenericValue<rapidjson::UTF16<wchar_t>> & serializedEntry,
                            rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator);
        void SerializePlayersSet(std::shared_ptr<Backend::PlayersSet> playersSet,
                                 rapidjson::GenericValue<rapidjson::UTF16<wchar_t>> & serializedEntry,
                                 rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator);
        void SerializeDeal(std::shared_ptr<Backend::Deal> deal,
                           rapidjson::GenericValue<rapidjson::UTF16<wchar_t>> & serializedEntry,
                           rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator);
        void SerializeMandatorySoloTrigger(rapidjson::GenericValue<rapidjson::UTF16<wchar_t>> & serializedEntry,
                                           rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator);

        std::shared_ptr<Entry> DeserializePlayersSet(rapidjson::GenericValue<rapidjson::UTF16<wchar_t>> * data);
        std::shared_ptr<Entry> DeserializeDeal(rapidjson::GenericValue<rapidjson::UTF16<wchar_t>> * data);
    };
}

#endif // DESERIALIZER_H
