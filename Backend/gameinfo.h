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

#include <memory>
#include <vector>
#include <set>
#include <map>
#include <string>
#include "playerinfo.h"
#include "eventinfo.h"
#include "multiplierinfo.h"

namespace Backend
{
    /*!
     * \brief The GameInfo class represents the current state of the game
     *        and provides access to information concerning each player.
     */
    class GameInfo
    {
    private:
        class PlayerInfoInternal;
        const unsigned int MaxPlayers;
        unsigned int dealsRecorded;
        std::vector<std::shared_ptr<PlayerInfoInternal>> playerInfos;
        std::map<std::wstring, std::shared_ptr<PlayerInfoInternal>> nameToPlayerInfo;
        unsigned int numberOfPresentPlayers;
        unsigned int currentDealerIndex;
        std::set<unsigned int> sitOutScheme;
        unsigned int poppableGames;
        std::vector<EventInfo> events;
        MultiplierInfo multiplierInfo;

    public:
        /*!
         * \brief Initializes a new instance.
         */
        GameInfo(const unsigned int maxPlayers = 8u);

        /*!
         * \brief Provides access to the player information.
         * \return The player information.
         */
        const std::vector<std::shared_ptr<PlayerInfo>> PlayerInfos() const;

        /*!
         * \brief Indicates the current dealer.
         * \return A player info about the current dealer.
         */
        const std::shared_ptr<PlayerInfo> Dealer() const;

        /*!
         * \brief Gets the indices of players that are sitting out.
         * \return The indices of players that are sitting out.
         */
        const std::set<unsigned int> SitOutScheme() const;

        /*!
         * \brief Set the name of the current players.
         * \param players The names of the current players, which must be unique.
         * \param dealer The name of the current dealer.
         * \param sitOutScheme The positions of players sitting out, necessary for 6 players or more.
         *                     Zero is the dealer, which is always implied.
         */
        void SetPlayers(std::vector<std::wstring> players,
                        std::wstring dealer,
                        std::set<unsigned int> sitOutScheme);

        /*!
         * \brief Pushes a game.
         * \param changes Collection of player names and (positive/negative) points awarded.
         * \param events The number of multiplier events in the deal.
         */
        void PushDeal(std::vector<std::pair<std::wstring, int>> changes, unsigned int numberOfEvents);

        /*!
         * \brief Gets a value indicating whether the last deal can be popped off.
         * \return A value indicating whether the last deal can be popped off.
         */
        bool CanPopLastDeal();

        /*!
         * \brief Removes the last deal from the collection of deals.
         */
        void PopLastDeal();

        /*!
         * \brief Gets the future levels of multiplication (which are the indices of the vector returned).
         * \return A vector containing counts for single, double ... etc. level of multiplication.
         */
        std::vector<unsigned int> MultiplierPreview() const;

        /*!
         * \brief Gets the number of events in the last deal.
         * \return The number of events in the last deal.
         */
        unsigned int LastNumberOfEvents() const;

        /*!
         * \brief Gets the total cash from all players who played in Euro cents.
         * \return The total cash from all players who played in Euro cents.
         */
        unsigned int TotalCashCents() const;

        /*!
         * \brief Gets the cash for an absent player in Euro cents;
         * \return The cash for an absent player in Euro cents;
         */
        unsigned int AbsentPlayerCashCents() const;

    private:
        void SortAndSetPlayerInfos(std::vector<std::wstring> players);
        void SetDealer(std::wstring dealer);
        void SetAndApplyScheme(std::set<unsigned int> newScheme);
        void ApplyScheme();
        std::vector<std::pair<std::wstring, int>> AutoCompleteDeal(std::vector<std::pair<std::wstring, int>> inputChanges);
        int MaximumCurrentScore() const;

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
            PlayerInfoInternal(std::wstring name,
                               std::function<unsigned short(unsigned int)> multiplierAccessor,
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
             * \param dealResult The change in score to push.
             */
            void PushDealResult(int dealResult);

            /*!
             * \brief Removes the last deal result from the collection.
             */
            void PopLastDealResult();

            /*!
             * \brief Removes information regarding previous deals,
             *        disabling the popping of old results.
             */
            void DropPreviousDealInformation();

            /*!
             * \brief Sets a value indicating whether the player played in the last persisted deal.
             * \param participated A value indicating whether the player played in the last persisted deal.
             */
            void SetParticipatedInDeal(bool participated);

            /*!
             * \brief Sets the input in the last deal, if any.
             * \param input The input in the last deal, if any.
             */
            void SetInputInDeal(std::wstring input);

            /*!
             * \brief Gets the number of recorded deals for this player.
             * \return The number of records.
             */
            size_t NumberOfRecordedDeals() const;
        };
    };
}

#endif // GAMEINFO_H
