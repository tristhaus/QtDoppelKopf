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

#ifndef GAMEINFO_H
#define GAMEINFO_H

#include "deal.h"
#include "diskrepository.h"
#include "entry.h"
#include "mandatorysolotrigger.h"
#include "multiplierinfo.h"
#include "playerinfo.h"
#include "playersset.h"
#include "repository.h"
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

namespace Backend
{
    /*!
     * \brief The GameInfo class represents the current state of the game
     *        and provides access to information concerning each player.
     */
    class GameInfo
    {
    public:
        /*!
         * \brief The MandatorySoloRound enum lists possible states
         *        of the mandatory solo system:
         *        Unable to trigger because it is the first deal,
         *        Ready to initiate a round,
         *        A round is active.
         */
        enum class MandatorySolo
        {
            CannotTrigger,
            Ready,
            Active
        };

        /*!
         * \brief The PoppableEntry enum lists possible states
         *        of the pop entry functionality:
         *        No popping possible,
         *        popping of players being set,
         *        of a deal,
         *        of the trigger of a mandatory solo round, respectively.
         */
        enum class PoppableEntry
        {
            None,
            PlayersSet,
            Deal,
            MandatorySoloTrigger,
        };

    private:
        class PlayerInfoInternal;
        const unsigned int MaxPlayers;
        std::vector<std::shared_ptr<PlayerInfoInternal>> playerInfos;
        std::map<std::string, std::shared_ptr<PlayerInfoInternal>> nameToPlayerInfo;
        unsigned int numberOfPresentPlayers{};
        unsigned int initialDealerIndex{};
        unsigned int currentDealerIndex{};
        std::set<unsigned int> sitOutScheme;
        MultiplierInfo multiplierInfo;

        std::shared_ptr<Repository> repository;
        std::vector<std::shared_ptr<Entry>> entries;

    public:
        /*!
         * \brief Initializes a new instance.
         * \param repository The repository to be used for permanent storage.
         * \param maxPlayers The maximum number of players that will be kept in this instance.
         */
        explicit GameInfo(std::shared_ptr<Repository> repository = std::make_shared<DiskRepository>(),
                 const unsigned int maxPlayers = 8U); //NOLINT(readability-avoid-const-params-in-decls)

        /*!
         * \brief Provides access to the player information.
         * \return The player information.
         */
        [[nodiscard]] std::vector<std::shared_ptr<PlayerInfo>> PlayerInfos() const;

        /*!
         * \brief Indicates the current dealer, if set.
         * \return A player info about the current dealer or nullptr.
         */
        [[nodiscard]] std::shared_ptr<PlayerInfo> Dealer() const;

        /*!
         * \brief Gets the indices of players that are sitting out.
         * \return The indices of players that are sitting out.
         */
        [[nodiscard]] std::set<unsigned int> SitOutScheme() const;

        /*!
         * \brief Set the name of the current players.
         * \param players The names of the current players, which must be unique.
         * \param dealer The name of the current dealer.
         * \param sitOutScheme The positions of players sitting out, necessary for 6 players or more.
         *                     Zero is the dealer, which is always implied.
         */
        void SetPlayers(const std::vector<std::string>& players,
                        const std::string& dealer,
                        const std::set<unsigned int>& sitOutScheme);

        /*!
         * \brief Pushes a game.
         * \param changes Collection of player names and (positive/negative) points awarded.
         * \param events The number of multiplier events in the deal.
         */
        void PushDeal(const std::vector<std::pair<std::string, int>>& changes, unsigned int numberOfEvents);

        /*!
         * \brief Begins a round of mandatory solo, which suspends the multiplier.
         */
        void TriggerMandatorySolo();

        /*!
         * \brief Gets whether and what can be popped from the entries.
         * \return A value indicating whether and what can be popped from the entries.
         */
        [[nodiscard]] PoppableEntry LastPoppableEntry() const;

        /*!
         * \brief Removes the last entry from the collection of deals.
         */
        void PopLastEntry();

        /*!
         * \brief Saves the state to the ID, which should be a filename.
         * \param id The identifier to save to.
         */
        void SaveTo(const std::u8string& id) const;

        /*!
         * \brief Load the persisted state from the ID, which should be a filename.
         * \param id The identifier to load from.
         */
        void LoadFrom(const std::u8string& id);

        /*!
         * \brief Gets a value indicating whether any players are set in this instance.
         * \return A value indicating whether any players are set in this instance.
         */
        [[nodiscard]] bool HasPlayersSet() const;

        /*!
         * \brief Gets the future levels of multiplication (which are the indices of the vector returned).
         * \return A vector containing counts for single, double ... etc. level of multiplication.
         */
        [[nodiscard]] std::vector<unsigned int> MultiplierPreview() const;

        /*!
         * \brief Gets the number of events in the last deal.
         * \return The number of events in the last deal.
         */
        [[nodiscard]] unsigned int LastNumberOfEvents() const;

        /*!
         * \brief Gets the total cash from all players who played in Euro cents.
         * \return The total cash from all players who played in Euro cents.
         */
        [[nodiscard]] unsigned int TotalCashCents() const;

        /*!
         * \brief Gets the cash for an absent player in Euro cents;
         * \return The cash for an absent player in Euro cents;
         */
        [[nodiscard]] unsigned int AbsentPlayerCashCents() const;

        /*!
         * \brief Gets the state of the mandatory solo round.
         * \return The state of the mandatory solo round.
         */
        [[nodiscard]] enum MandatorySolo MandatorySolo() const;

        /*!
         * \brief Gets the number games remaining in the current round.
         * \return The number games remaining in the current round.
         */
        [[nodiscard]] unsigned int RemainingGamesInRound() const;

    private:
        void SetPlayersInternal(const std::shared_ptr<PlayersSet>& playersSet);
        void SortAndSetPlayerInfos(const std::vector<std::string>& players);
        void SetDealer(const std::string& dealer);
        void SetAndApplyScheme(const std::set<unsigned int>& newScheme);
        void ApplyScheme();
        void PushDealInternal(const std::shared_ptr<Deal>& deal);
        std::vector<std::pair<std::string, int>> AutoCompleteDeal(std::vector<std::pair<std::string, int>> inputChanges);
        [[nodiscard]] static std::string FindSoloPlayer(const std::vector<std::pair<std::string, int>>& changes);
        [[nodiscard]] int MaximumCurrentScore() const;
        void ReconstructEventsForMultiplierInfo();
        [[nodiscard]] unsigned int DealsRecorded() const;

    private:
        class PlayerInfoInternal : public PlayerInfo
        {
        public:
            /*!
             * \brief Initializes a new instance from the given name.
             * \param The unique name of the player.
             * \param multiplierAccessor A function to obtain the multiplier for the indexed game.
             * \param maxCurrentScoreAccessor A function to obtain the maximum current score among the players.
             */
            PlayerInfoInternal(std::string name,
                               std::function<unsigned short(unsigned int)> multiplierAccessor, //NOLINT(google-runtime-int)
                               std::function<int()> maxCurrentScoreAccessor);

            /*!
             * \brief Sets a value indicating whether the player has participated in any deal.
             * \param hasPlayed A value indicating whether the player has participated in any deal.
             */
            void SetHasPlayed(bool hasPlayed);

            /*!
             * \brief Sets a value indicating whether the player is present at the table.
             * \param isPresent A value indicating whether the player is present at the table.
             */
            void SetIsPresent(bool isPresent);

            /*!
             * \brief Sets a value indicating whether the player is playing during the next deal.
             * \param isPlaying A value indicating whether the player is playing during the next deal.
             */
            void SetIsPlaying(bool isPlaying);

            /*!
             * \brief Adds a result of a deal to the player.
             * \param hasPlayedInDeal Value indicating whether the player played in the deal.
             * \param unmultipliedScore The change in score to push.
             * \param playedSolo Value indicating whether the player played solo.
             */
            void PushDealResult(bool hasPlayedInDeal, int unmultipliedScore, bool playedSolo);

            /*!
             * \brief Removes the last deal result from the collection.
             */
            void PopLastDealResult();

            /*!
             * \brief Sets the input in the last deal, if any.
             * \param input The input in the last deal, if any.
             */
            void SetInputInDeal(const std::string& input);

            /*!
             * \brief Gets the number of recorded deals for this player.
             * \return The number of records.
             */
            [[nodiscard]] size_t NumberOfRecordedDeals() const;
        };
    };
}

#endif // GAMEINFO_H
