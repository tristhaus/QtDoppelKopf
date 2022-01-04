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

#include <functional>
#include <string>
#include <vector>

namespace Backend
{
    /*!
     * \brief The PlayerInfo class collects information
     *        regarding a player identified by name.
     */
    class PlayerInfo
    {
    protected:
        struct DealResult
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

        std::string name;
        bool hasPlayed;
        bool isPresent;
        bool isPlaying;
        std::vector<DealResult> dealResults;
        std::vector<int> multipliedResults;
        std::vector<int> accumulatedMultipliedResults;
        std::vector<std::string> dealInput;
        std::function<unsigned short(unsigned int)> multiplierAccessor; //NOLINT(google-runtime-int)
        std::function<int()> maxCurrentScoreAccessor;

    public:
        /*!
         * \brief Initializes a new instance from the given name.
         * \param name The unique name of the player.
         * \param multiplierAccessor A function to obtain the multiplier for the indexed game.
         * \param maxCurrentScoreAccessor A function to obtain the maximum current score among the players.
         */
        PlayerInfo(std::string name,
                   std::function<unsigned short(unsigned int)> multiplierAccessor, //NOLINT(google-runtime-int)
                   std::function<int()> maxCurrentScoreAccessor);

        /*!
         * \brief Gets the name of the player.
         * \return The name of the player.
         */
        [[nodiscard]] std::string Name() const;

        /*!
         * \brief Gets a value indicating whether the player has participated in any deal.
         * \return A value indicating whether the player has participated in any deal.
         */
        [[nodiscard]] bool HasPlayed() const;

        /*!
         * \brief Gets a value indicating whether the player is present at the table.
         * \return A value indicating whether the player is present at the table.
         */
        [[nodiscard]] bool IsPresent() const;

        /*!
         * \brief Gets a value indicating whether the player is playing during the next deal.
         * \return A value indicating whether the player is playing during the next deal.
         */
        [[nodiscard]] bool IsPlaying() const;

        /*!
         * \brief Gets the current score of the player.
         * \return A number indicating the current score of the player.
         */
        [[nodiscard]] int CurrentScore() const;

        /*!
         * \brief Gets a value indicating whether the player played in the last persisted deal.
         * \return A value indicating whether the player played in the last persisted deal.
         */
        [[nodiscard]] bool ParticipatedInLastDeal() const;

        /*!
         * \brief Gets the total change in points in the last deal.
         * \return The total change in points in the last deal.
         */
        [[nodiscard]] int ScoreInLastDeal() const;

        /*!
         * \brief Gets the input in the last deal, if any.
         * \return The input in the last deal, if any.
         */
        [[nodiscard]] std::string InputInLastDeal() const;

        /*!
         * \brief Gets the due balance in Euro cent.
         * \return The due balance in Euro cent.
         */
        [[nodiscard]] unsigned int CashCents() const;

        /*!
         * \brief Gets the number of won games.
         * \return The number of won games.
         */
        [[nodiscard]] unsigned int NumberGamesWon() const;

        /*!
         * \brief Gets the number of lost games.
         * \return The number of lost games.
         */
        [[nodiscard]] unsigned int NumberGamesLost() const;

        /*!
         * \brief Gets the number of games.
         * \return The number of games.
         */
        [[nodiscard]] unsigned int NumberGames() const;

        /*!
         * \brief Gets the number of solos won.
         * \return The number of solos won.
         */
        [[nodiscard]] unsigned int SolosWon() const;

        /*!
         * \brief Gets the number of solos lost.
         * \return The number of solos lost.
         */
        [[nodiscard]] unsigned int SolosLost() const;

        /*!
         * \brief Gets the sum of points collected from played solos.
         * \return The sum of points collected from played solos.
         */
        [[nodiscard]] int TotalSoloPoints() const;

        /*!
         * \brief Gets the points of the maximal single win.
         * \return The points of the maximal single win.
         */
        [[nodiscard]] int MaxSingleWin() const;

        /*!
         * \brief Gets the points of the maximal single loss.
         * \return The points of the maximal single loss.
         */
        [[nodiscard]] int MaxSingleLoss() const;

        /*!
         * \brief Gets the score without applying the multiplier.
         * \return The score without applying the multiplier.
         */
        [[nodiscard]] int UnmultipliedScore() const;

        /*!
         * \brief Gets the entire history of scores.
         * \return The entire history of scores.
         */
        [[nodiscard]] std::vector<int> ScoreHistory() const;
    };
}

#endif // PLAYERINFO_H
