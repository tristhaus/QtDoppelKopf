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

#include <algorithm>
#include "gameinfo.h"

namespace Backend
{
    GameInfo::GameInfo()
    {
    }

    const std::vector<PlayerInfo> & GameInfo::PlayerInfos() const
    {
        return this->playerInfos;
    }

    void GameInfo::SetPlayers(std::vector<std::wstring> players)
    {
        // todo : ensure uniqueness of names

        std::vector<PlayerInfo> newInfos;

        auto playersIt = players.begin();
        auto playersEnd = players.end();
        for(; playersIt != playersEnd; ++playersIt)
        {
            auto playerInfoIt = std::find_if(
                        this->playerInfos.begin(),
                        this->playerInfos.end(),
                        [&](PlayerInfo pi){ return pi.Name() == *playersIt; });

            if(playerInfoIt != this->playerInfos.end())
            {
                newInfos.push_back(*playerInfoIt);
            }
            else
            {
                newInfos.emplace_back(PlayerInfo(*playersIt));
            }
        }

        this->playerInfos = newInfos;
    }
}
