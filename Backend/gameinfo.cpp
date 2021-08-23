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

    const PlayerInfo& GameInfo::Dealer() const
    {
        return this->playerInfos[this->currentDealerIndex];
    }

    void GameInfo::SetPlayers(std::vector<std::wstring> players,
                              std::wstring dealer,
                              std::set<unsigned int> sitOutScheme)
    {
        bool dealerFound = false;
        const auto playersSize = players.size();

        if(playersSize < 4u)
        {
            throw std::exception("not enough players");
        }

        for(size_t i = 0; i < playersSize; ++i)
        {
            if(dealer == players[i])
            {
                dealerFound = true;
            }

            for(size_t j = i + 1; j < playersSize; ++j)
            {
                if(players[i] == players[j])
                {
                    throw std::exception("names must be unique");
                }
            }
        }

        if(!dealerFound)
        {
            throw std::exception("name of dealer must be among the players");
        }

        if(playersSize > 5u && sitOutScheme.size() + 5u != playersSize)
        {
            throw std::exception("incorrect size of the sit out scheme");
        }

        this->SortAndSetPlayerInfos(players);

        this->SetDealer(dealer);

        this->SetAndApplyScheme(sitOutScheme);
    }

    void GameInfo::PushDeal(std::vector<std::pair<std::wstring, int>> changes)
    {
        if(changes.size() != 4)
        {
            throw std::exception("changes must have size 4");
        }

        auto changesIt = changes.begin();
        auto changesEnd = changes.end();
        for(; changesIt != changesEnd; ++changesIt)
        {
            // todo also persist score
            auto playerIt = std::find_if(this->playerInfos.begin(),
                                      this->playerInfos.end(),
                                      [&](PlayerInfo pi){ return pi.Name() == changesIt->first; });

            if(playerIt == this->playerInfos.end())
            {
                throw std::exception("found change for unknown player");
            }

            if(!playerIt->IsPlaying())
            {
                throw std::exception("found change for player not playing");
            }

            playerIt->SetHasPlayed(true);
        }

        this->currentDealerIndex = (this->currentDealerIndex + 1) % this->numberOfPresentPlayers;

        this->ApplyScheme();
    }

    void Backend::GameInfo::SortAndSetPlayerInfos(std::vector<std::wstring> players)
    {
        this->numberOfPresentPlayers = static_cast<unsigned int>(players.size());

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
                playerInfoIt->SetIsPresent(true);
                newInfos.push_back(*playerInfoIt);
            }
            else
            {
                PlayerInfo newPlayer(*playersIt);
                newPlayer.SetIsPresent(true);
                newInfos.emplace_back(newPlayer);
            }
        }

        auto playerInfosIt = playerInfos.begin();
        auto playerInfosEnd = playerInfos.end();
        for(; playerInfosIt != playerInfosEnd; ++playerInfosIt)
        {

            auto playerIt = std::find_if(
                        players.begin(),
                        players.end(),
                        [&](std::wstring player){ return player == playerInfosIt->Name(); });

            if( playerIt == players.end() && playerInfosIt->HasPlayed())
            {
                playerInfosIt->SetIsPresent(false);
                playerInfosIt->SetIsPlaying(false);
                newInfos.push_back(*playerInfosIt);
            }
        }

        this->playerInfos = newInfos;
    }

    void Backend::GameInfo::SetDealer(std::wstring dealer)
    {
        auto dealerIt = std::find_if(
                    this->playerInfos.begin(),
                    this->playerInfos.end(),
                    [&](PlayerInfo pi){ return pi.Name() == dealer; });

        if(dealerIt == this->playerInfos.end())
        {
            throw std::exception("logic error: dealer must be among the players");
        }

        this->currentDealerIndex = static_cast<unsigned int>(dealerIt - this->playerInfos.begin());
    }

    void Backend::GameInfo::SetAndApplyScheme(std::set<unsigned int> newScheme)
    {
        this->sitOutScheme = newScheme;

        if(numberOfPresentPlayers > 4)
        {
            this->sitOutScheme.insert(0u);
        }

        this->ApplyScheme();
    }

    void Backend::GameInfo::ApplyScheme()
    {
        for(unsigned int i = currentDealerIndex; i < currentDealerIndex + numberOfPresentPlayers; ++i)
        {
            bool isPlaying = this->sitOutScheme.count(i - currentDealerIndex) == 0;

            this->playerInfos[i % this->numberOfPresentPlayers].SetIsPlaying(isPlaying);
        }
    }
}
