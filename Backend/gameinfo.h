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

#include <vector>
#include <string>
#include "playerinfo.h"

namespace Backend
{
    /*!
     * \brief The GameInfo class represents the current state of the game
     *        and provides access to information concerning each player.
     */
    class GameInfo
    {
    private:
        std::vector<PlayerInfo> playerInfos;

    public:
        /*!
         * \brief Initializes a new instance.
         */
        GameInfo();

        /*!
         * \brief Provides access to the player information.
         * \return The player information.
         */
        const std::vector<PlayerInfo> & PlayerInfos() const;

        /*!
         * \brief Set the name of the current players.
         * \param players The names of the current players, which must be unique.
         */
        void SetPlayers(std::vector<std::wstring> players);
    };
}

#endif // GAMEINFO_H
