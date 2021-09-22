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
#include <numeric>
#include "gameinfo.h"
#include "eventinfo.h"

namespace Backend
{
    GameInfo::GameInfo()
        : dealsRecorded(0u),
          poppableGames(0u)
    {
    }

    const std::vector<std::shared_ptr<PlayerInfo>> GameInfo::PlayerInfos() const
    {
        return std::vector<std::shared_ptr<PlayerInfo>>(this->playerInfos.begin(), this->playerInfos.end());
    }

    const std::shared_ptr<PlayerInfo> GameInfo::Dealer() const
    {
        return this->playerInfos[this->currentDealerIndex];
    }

    const std::set<unsigned int> GameInfo::SitOutScheme() const
    {
        return this->sitOutScheme;
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
        this->poppableGames = 0u;

        this->SetDealer(dealer);

        this->SetAndApplyScheme(sitOutScheme);
    }

    void GameInfo::PushDeal(std::vector<std::pair<std::wstring, int>> changes,
                            unsigned int numberOfEvents)
    {
        auto actualChanges = this->AutoCompleteDeal(changes);

        auto changesIt = actualChanges.begin();
        auto changesEnd = actualChanges.end();
        for(; changesIt != changesEnd; ++changesIt)
        {
            auto player = nameToPlayerInfo.at(changesIt->first);

            if(!player->IsPlaying())
            {
                throw std::exception("found change for player not playing");
            }

            player->PushDealResult(changesIt->second);
            player->SetParticipatedInDeal(true);

            player->SetHasPlayed(true);

            auto relevantChange = std::find_if(changes.begin(), changes.end(), [&](std::pair<std::wstring, int> change){ return change.first == player->Name(); });
            if(relevantChange != changes.end())
            {
                player->SetInputInDeal(std::to_wstring(relevantChange->second));
            }
            else
            {
                player->SetInputInDeal(std::wstring(L""));
            }
        }

        auto playerInfosIt = this->playerInfos.begin();
        auto playerInfosEnd = this->playerInfos.end();
        for(; playerInfosIt != playerInfosEnd; ++playerInfosIt)
        {
            if(!(*playerInfosIt)->IsPlaying())
            {
                (*playerInfosIt)->PushDealResult(0);
                (*playerInfosIt)->SetParticipatedInDeal(false);
                (*playerInfosIt)->SetInputInDeal(std::wstring(L""));
            }
        }

        this->currentDealerIndex = (this->currentDealerIndex + 1) % this->numberOfPresentPlayers;
        this->events.push_back( { NumberOfEvents(numberOfEvents), Players(numberOfPresentPlayers) } );
        this->multiplierInfo.PushDeal(this->events.back());

        this->ApplyScheme();

        ++(this->poppableGames);
    }

    bool GameInfo::CanPopLastDeal()
    {
        return poppableGames > 0;
    }

    void GameInfo::PopLastDeal()
    {
        if(!this->CanPopLastDeal())
        {
            return;
        }

        --(this->poppableGames);

        auto playerInfosIt = this->playerInfos.begin();
        auto playerInfosEnd = this->playerInfos.end();
        for(; playerInfosIt != playerInfosEnd; ++playerInfosIt)
        {
            (*playerInfosIt)->PopLastDealResult();
        }

        this->currentDealerIndex = (this->currentDealerIndex - 1 + this->numberOfPresentPlayers) % this->numberOfPresentPlayers;

        this->events.pop_back();
        this->multiplierInfo.ResetTo(this->events);

        this->ApplyScheme();
    }

    std::vector<unsigned int> GameInfo::MultiplierPreview() const
    {
        return this->multiplierInfo.GetPreview();
    }

    unsigned int GameInfo::LastNumberOfEvents() const
    {
        return !this->events.empty() ? this->events.back().number.Value() : 0u;
    }

    void GameInfo::SortAndSetPlayerInfos(std::vector<std::wstring> players)
    {
        this->numberOfPresentPlayers = static_cast<unsigned int>(players.size());

        std::vector<std::shared_ptr<PlayerInfoInternal>> newInfos;

        auto playersIt = players.begin();
        auto playersEnd = players.end();
        for(; playersIt != playersEnd; ++playersIt)
        {
            if(nameToPlayerInfo.count(*playersIt) == 0)
            {
                auto newPlayerInfo = std::make_shared<PlayerInfoInternal>(*playersIt, [&](unsigned int index){ return this->multiplierInfo.GetMultiplier(index); });
                while(newPlayerInfo->NumberOfRecordedDeals() < this->dealsRecorded)
                {
                    newPlayerInfo->PushDealResult(0);
                    newPlayerInfo->SetParticipatedInDeal(false);
                }

                nameToPlayerInfo[*playersIt] = newPlayerInfo;
            }

            auto currentPlayerInfo = nameToPlayerInfo[*playersIt];
            currentPlayerInfo->SetIsPresent(true);
            newInfos.push_back(currentPlayerInfo);
        }

        auto playerInfosIt = playerInfos.begin();
        auto playerInfosEnd = playerInfos.end();
        for(; playerInfosIt != playerInfosEnd; ++playerInfosIt)
        {

            auto playerIt = std::find_if(
                        players.begin(),
                        players.end(),
                        [&](std::wstring player){ return player == (*playerInfosIt)->Name(); });

            if(playerIt == players.end() && (*playerInfosIt)->HasPlayed())
            {
                (*playerInfosIt)->SetIsPresent(false);
                (*playerInfosIt)->SetIsPlaying(false);
                newInfos.push_back(*playerInfosIt);
            }

            (*playerInfosIt)->DropPreviousDealInformation();
        }

        this->playerInfos = newInfos;
    }

    void GameInfo::SetDealer(std::wstring dealer)
    {
        auto dealerIt = std::find_if(
                    this->playerInfos.begin(),
                    this->playerInfos.end(),
                    [&](std::shared_ptr<PlayerInfoInternal> pi){ return pi->Name() == dealer; });

        if(dealerIt == this->playerInfos.end())
        {
            throw std::exception("logic error: dealer must be among the players");
        }

        this->currentDealerIndex = static_cast<unsigned int>(dealerIt - this->playerInfos.begin());
    }

    void GameInfo::SetAndApplyScheme(std::set<unsigned int> newScheme)
    {
        this->sitOutScheme = newScheme;

        if(numberOfPresentPlayers > 4)
        {
            this->sitOutScheme.insert(0u);
        }

        this->ApplyScheme();
    }

    void GameInfo::ApplyScheme()
    {
        for(unsigned int i = currentDealerIndex; i < currentDealerIndex + numberOfPresentPlayers; ++i)
        {
            bool isPlaying = this->sitOutScheme.count(i - currentDealerIndex) == 0;

            this->playerInfos[i % this->numberOfPresentPlayers]->SetIsPlaying(isPlaying);
        }
    }

    std::vector<std::pair<std::wstring, int>> GameInfo::AutoCompleteDeal(std::vector<std::pair<std::wstring, int>> inputChanges)
    {
        auto changesIt = inputChanges.begin();
        auto changesEnd = inputChanges.end();
        if(inputChanges.size() == 4)
        {
            int checksum = std::accumulate(changesIt,
                                           changesEnd,
                                           0,
                                           [](int s, std::pair<std::wstring, int> c){ s += c.second; return s; });
            if(checksum != 0)
            {
                throw std::exception("changes must sum to zero");
            }

            return inputChanges;
        }
        else if(inputChanges.size() > 4 || inputChanges.size() == 0)
        {
            throw std::exception("there can never be more than 4 or zero changes");
        }

        std::vector<std::pair<std::wstring, int>> newChanges;
        int found = 0;
        int instances = 0;

        for(; changesIt != changesEnd; ++changesIt)
        {
            if(instances == 0)
            {
                found = changesIt->second;
                ++instances;
            }
            else if(found == changesIt->second)
            {
                ++instances;
            }
            else
            {
                throw std::exception("unable to complete the changes from the information given");
            }

            newChanges.push_back(*changesIt);
        }

        int valueToSet = - (instances * found) / (4 - static_cast<int>(inputChanges.size()));

        auto playersIt = this->playerInfos.begin();
        auto playersEnd = this->playerInfos.end();
        for(; playersIt != playersEnd; ++playersIt)
        {
            if(!(*playersIt)->IsPlaying())
            {
                continue;
            }

            auto changeIt = std::find_if(inputChanges.begin(),
                                         changesEnd,
                                         [&](std::pair<std::wstring, int> change){ return change.first == (*playersIt)->Name(); });
            if(changeIt != changesEnd)
            {
                continue;
            }

            newChanges.emplace_back(std::pair<std::wstring, int>((*playersIt)->Name(), valueToSet));
        }

        return newChanges;
    }

    GameInfo::PlayerInfoInternal::PlayerInfoInternal(std::wstring name, std::function<unsigned short(unsigned int)> multiplierAccessor)
        : PlayerInfo(name, multiplierAccessor)
    {
    }

    void GameInfo::PlayerInfoInternal::SetHasPlayed(bool hasPlayed)
    {
        this->hasPlayed = hasPlayed;
    }

    void GameInfo::PlayerInfoInternal::SetIsPresent(bool isPresent)
    {
        this->isPresent = isPresent;
    }

    void GameInfo::PlayerInfoInternal::SetIsPlaying(bool isPlaying)
    {
        this->isPlaying = isPlaying;
    }

    void GameInfo::PlayerInfoInternal::PushDealResult(int dealResult)
    {
        this->dealResults.push_back(dealResult);
    }

    void GameInfo::PlayerInfoInternal::PopLastDealResult()
    {
        this->dealResults.pop_back();
        this->dealInput.pop_back();

        this->SetParticipatedInDeal((!this->dealResults.empty() && this->dealResults.back() != 0) || !(this)->InputInLastDeal().empty());
    }

    void GameInfo::PlayerInfoInternal::DropPreviousDealInformation()
    {
        this->dealInput.clear();
    }

    void GameInfo::PlayerInfoInternal::SetParticipatedInDeal(bool participated)
    {
        this->participatedInLastDeal = participated;
    }

    void GameInfo::PlayerInfoInternal::SetInputInDeal(std::wstring input)
    {
        this->dealInput.push_back(input);
    }

    size_t GameInfo::PlayerInfoInternal::NumberOfRecordedDeals() const
    {
        return this->dealResults.size();
    }
}
