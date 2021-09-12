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

namespace Backend
{
    /*!
     * \brief The PlayerInfo class collects information
     *        regarding a player identified by name.
     */
    class PlayerInfo
    {
    protected:
        std::wstring name;
        bool hasPlayed;
        bool isPresent;
        bool isPlaying;
        bool participatedInLastDeal;
        std::vector<int> dealResults;
        std::vector<std::wstring> dealInput;

    public:
        /*!
         * \brief Initializes a new instance from the given name.
         * \param The unique name of the player.
         */
        PlayerInfo(std::wstring name);

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
    };
}

#endif // PLAYERINFO_H
