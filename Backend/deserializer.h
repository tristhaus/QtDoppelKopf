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

#include "deal.h"
#include "entry.h"
#include "mandatorysolotrigger.h"
#include "playersset.h"
#include "rapidjson/document.h"
#include <iostream>
#include <vector>

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
        constexpr static const char * const KeyDataVersion = "dataVersion";
        constexpr static const char * const KeyData = "data";

        constexpr static const char * const KeyKind = "kind";
        constexpr static const char * const ValuePlayersSet = "playersSet";
        constexpr static const char * const ValueDeal = "deal";
        constexpr static const char * const ValueMandatorySoloTrigger = "mandatorySoloTrigger";

        constexpr static const char * const KeyPlayerNames = "playerNames";
        constexpr static const char * const KeyDealerName = "dealerName";
        constexpr static const char * const KeySitOutScheme = "sitOutScheme";
        constexpr static const char * const KeyPreviousDealerName = "previousDealerName";

        constexpr static const char * const KeyPlayers = "players";
        constexpr static const char * const KeyNumberOfEvents = "numberOfEvents";

        constexpr static const char * const KeyChanges = "changes";
        constexpr static const char * const KeyChangeName = "name";
        constexpr static const char * const KeyChangeDiff = "diff";

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
        void Serialize(const std::vector<std::shared_ptr<Entry>> & entries, std::ostream & os);

        /*!
         * \brief Deserialize from the stream into the return value.
         * \param wis The stream to deserialize from.
         * \return The deserialized entries.
         */
        std::vector<std::shared_ptr<Entry>> Deserialize(std::istream & is);

    private:
        static void SerializeEntry(const std::shared_ptr<Entry> & entry,
                            rapidjson::GenericValue<rapidjson::UTF8<char>> & serializedEntry, //NOLINT (google-runtime-references)
                            rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator); //NOLINT (google-runtime-references)
        static void SerializePlayersSet(const std::shared_ptr<Backend::PlayersSet> & playersSet,
                                 rapidjson::GenericValue<rapidjson::UTF8<char>> & serializedEntry, //NOLINT (google-runtime-references)
                                 rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator); //NOLINT (google-runtime-references)
        static void SerializeDeal(const std::shared_ptr<Backend::Deal>& deal,
                           rapidjson::GenericValue<rapidjson::UTF8<char>> & serializedEntry, //NOLINT (google-runtime-references)
                           rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator); //NOLINT (google-runtime-references)
        static void SerializeMandatorySoloTrigger(rapidjson::GenericValue<rapidjson::UTF8<char>> & serializedEntry, //NOLINT (google-runtime-references)
                                           rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator); //NOLINT (google-runtime-references)

        static std::shared_ptr<Entry> DeserializePlayersSet(const rapidjson::GenericValue<rapidjson::UTF8<char>> & data);
        static std::shared_ptr<Entry> DeserializeDeal(const rapidjson::GenericValue<rapidjson::UTF8<char>> & data);
    };
}

#endif // DESERIALIZER_H
