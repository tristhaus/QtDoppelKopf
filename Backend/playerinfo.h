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

#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include <string>
#include <vector>
#include <functional>

namespace Backend
{
    /*!
     * \brief The PlayerInfo class collects information
     *        regarding a player identified by name.
     */
    class PlayerInfo
    {
    protected:
        class DealResult
        {
        public:
            DealResult(bool hasPlayedInDeal, int unmultipliedScore, bool playedSolo)
                : HasPlayedInDeal(hasPlayedInDeal),
                  UnmultipliedScore(unmultipliedScore),
                  PlayedSolo(playedSolo)
            {
            }

            const bool HasPlayedInDeal;
            const int UnmultipliedScore;
            const bool PlayedSolo;
        };

        std::wstring name;
        bool hasPlayed;
        bool isPresent;
        bool isPlaying;
        std::vector<DealResult> dealResults;
        std::vector<int> multipliedResults;
        std::vector<std::wstring> dealInput;
        std::function<unsigned short(unsigned int)> multiplierAccessor;
        std::function<int()> maxCurrentScoreAccessor;

    public:
        /*!
         * \brief Initializes a new instance from the given name.
         * \param name The unique name of the player.
         * \param multiplierAccessor A function to obtain the multiplier for the indexed game.
         * \param maxCurrentScoreAccessor A function to obtain the maximum current score among the players.
         */
        PlayerInfo(std::wstring name,
                   std::function<unsigned short(unsigned int)> multiplierAccessor,
                   std::function<int()> maxCurrentScoreAccessor);

        /*!
         * \brief Gets the name of the player.
         * \return The name of the player.
         */
        std::wstring Name() const;

        /*!
         * \brief Gets a value indicating whether the player has participated in any deal.
         * \return A value indicating whether the player has participated in any deal.
         */
        bool HasPlayed() const;

        /*!
         * \brief Gets a value indicating whether the player is present at the table.
         * \return A value indicating whether the player is present at the table.
         */
        bool IsPresent() const;

        /*!
         * \brief Gets a value indicating whether the player is playing during the next deal.
         * \return A value indicating whether the player is playing during the next deal.
         */
        bool IsPlaying() const;

        /*!
         * \brief Gets the current score of the player.
         * \return A number indicating the current score of the player.
         */
        int CurrentScore() const;

        /*!
         * \brief Gets a value indicating whether the player played in the last persisted deal.
         * \return A value indicating whether the player played in the last persisted deal.
         */
        bool ParticipatedInLastDeal() const;

        /*!
         * \brief Gets the total change in points in the last deal.
         * \return The total change in points in the last deal.
         */
        int ScoreInLastDeal() const;

        /*!
         * \brief Gets the input in the last deal, if any.
         * \return The input in the last deal, if any.
         */
        std::wstring InputInLastDeal() const;

        /*!
         * \brief Gets the due balance in Euro cent.
         * \return The due balance in Euro cent.
         */
        unsigned int CashCents() const;

        /*!
         * \brief Gets the number of won games.
         * \return The number of won games.
         */
        unsigned int NumberGamesWon() const;

        /*!
         * \brief Gets the number of lost games.
         * \return The number of lost games.
         */
        unsigned int NumberGamesLost() const;

        /*!
         * \brief Gets the number of games.
         * \return The number of games.
         */
        unsigned int NumberGames() const;

        /*!
         * \brief Gets the number of solos won.
         * \return The number of solos won.
         */
        unsigned int SolosWon() const;

        /*!
         * \brief Gets the number of solos lost.
         * \return The number of solos lost.
         */
        unsigned int SolosLost() const;

        /*!
         * \brief Gets the sum of points collected from played solos.
         * \return The sum of points collected from played solos.
         */
        int TotalSoloPoints() const;

        /*!
         * \brief Gets the points of the maximal single win.
         * \return The points of the maximal single win.
         */
        int MaxSingleWin() const;

        /*!
         * \brief Gets the points of the maximal single loss.
         * \return The points of the maximal single loss.
         */
        int MaxSingleLoss() const;

        /*!
         * \brief Gets the score without applying the multiplier.
         * \return The score without applying the multiplier.
         */
        int UnmultipliedScore() const;
    };
}

#endif // PLAYERINFO_H
