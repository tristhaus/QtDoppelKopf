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

#include "cashcalculation.h"
#include "eventinfo.h"
#include "gameinfo.h"
#include <algorithm>
#include <numeric>
#include <utility>

namespace Backend
{
    GameInfo::GameInfo(std::shared_ptr<Repository> repository, const unsigned int maxPlayers)
        : MaxPlayers(maxPlayers),
          repository(std::move(repository))
    {
    }

    std::vector<std::shared_ptr<PlayerInfo>> GameInfo::PlayerInfos() const
    {
        return std::vector<std::shared_ptr<PlayerInfo>>(this->playerInfos.begin(), this->playerInfos.end());
    }

    std::shared_ptr<PlayerInfo> GameInfo::Dealer() const
    {
        return !this->playerInfos.empty() ? this->playerInfos[this->currentDealerIndex] : nullptr;
    }

    std::set<unsigned int> GameInfo::SitOutScheme() const
    {
        return this->sitOutScheme;
    }

    void GameInfo::SetPlayers(const std::vector<std::string>& players,
                              const std::string& dealer,
                              const std::set<unsigned int>& sitOutScheme)
    {
        std::string previousDealer = this->Dealer() != nullptr ? this->Dealer()->Name() : "";
        auto entry = std::make_shared<PlayersSet>(players, dealer, sitOutScheme, previousDealer);

        this->SetPlayersInternal(entry);

        // first entry must be PlayersSet and is thus replaced
        if(this->entries.size() == 1)
        {
            this->entries.pop_back();
        }

        this->entries.push_back(entry);
    }

    void GameInfo::PushDeal(const std::vector<std::pair<std::string, int>>& changes,
                            unsigned int numberOfEvents)
    {

        auto entry = std::make_shared<Deal>(changes, NumberOfEvents(numberOfEvents), Players(this->numberOfPresentPlayers));

        this->PushDealInternal(entry);

        this->entries.push_back(entry);
    }

    void GameInfo::TriggerMandatorySolo()
    {
        if(this->MandatorySolo() != MandatorySolo::Ready)
        {
            throw std::exception("cannot trigger mandatory solo at this point");
        }

        this->entries.emplace_back(std::make_shared<MandatorySoloTrigger>());

        this->ReconstructEventsForMultiplierInfo();
    }

    GameInfo::PoppableEntry GameInfo::LastPoppableEntry()
    {
        if(this->entries.size() < 2)
        {
            return GameInfo::PoppableEntry::None;
        }

        switch(this->entries.back()->Kind())
        {
        case Backend::Entry::Kind::PlayersSet:
            return GameInfo::PoppableEntry::PlayersSet;
        case Backend::Entry::Kind::Deal:
            return GameInfo::PoppableEntry::Deal;
        case Backend::Entry::Kind::MandatorySoloTrigger:
            return GameInfo::PoppableEntry::MandatorySoloTrigger;
        default:
            throw std::exception("value of Entry::Kind not handled");
        }
    }

    void GameInfo::PopLastEntry()
    {
        if(this->LastPoppableEntry() == GameInfo::PoppableEntry::None)
        {
            return;
        }

        auto entry = this->entries.back();
        this->entries.pop_back();

        if(entry->Kind() == Entry::Kind::PlayersSet)
        {
            auto lastPlayerSetEntry = std::find_if(
                        this->entries.rbegin(),
                        this->entries.rend(),
                        [](const std::shared_ptr<Backend::Entry>& entry){ return  entry->Kind() == Backend::Entry::Kind::PlayersSet; });

            if(lastPlayerSetEntry == this->entries.rend())
            {
                throw std::exception("must never happen 1");
            }

            this->SetPlayersInternal(std::static_pointer_cast<Backend::PlayersSet>(*lastPlayerSetEntry));

            this->SetDealer(std::static_pointer_cast<Backend::PlayersSet>(entry)->PreviousDealer());

            auto relevantPlayerSetEntry = std::find_if(
                        this->entries.rbegin(),
                        this->entries.rend(),
                        [](const std::shared_ptr<Backend::Entry>& entry){ return  entry->Kind() == Backend::Entry::Kind::PlayersSet; });
            if(relevantPlayerSetEntry == this->entries.rend())
            {
                throw std::exception("must never happen 2");
            }

            auto relevantInitialDealerName = std::static_pointer_cast<Backend::PlayersSet>(*relevantPlayerSetEntry)->Dealer();
            auto relevantInitialDealerInfo = std::find_if(this->playerInfos.begin(), this->playerInfos.end(), [&relevantInitialDealerName](const std::shared_ptr<PlayerInfoInternal>& playerInfo) { return playerInfo->Name() == relevantInitialDealerName; });
            if(relevantInitialDealerInfo == this->playerInfos.end())
            {
                throw std::exception("must never happen 3");
            }

            this->initialDealerIndex = static_cast<unsigned int>(relevantInitialDealerInfo - this->playerInfos.begin());
        }
        else if(entry->Kind() == Entry::Kind::Deal)
        {
            auto playerInfosIt = this->playerInfos.begin();
            auto playerInfosEnd = this->playerInfos.end();
            for(; playerInfosIt != playerInfosEnd; ++playerInfosIt)
            {
                (*playerInfosIt)->PopLastDealResult();
            }

            this->currentDealerIndex = (this->currentDealerIndex - 1 + this->numberOfPresentPlayers) % this->numberOfPresentPlayers;

            this->ApplyScheme();

            this->ReconstructEventsForMultiplierInfo();
        }
        else if(entry->Kind() == Entry::Kind::MandatorySoloTrigger)
        {
            this->ReconstructEventsForMultiplierInfo();
        }
    }

    void GameInfo::SaveTo(const std::u8string& id) const
    {
        this->repository->Save(this->entries, id);
    }

    void GameInfo::LoadFrom(const std::u8string& id)
    {
        auto applyEntries = [&](const std::vector<std::shared_ptr<Entry>>& entries)
        {
            for (const auto & entry : entries)
            {
                switch(entry->Kind())
                {
                case Entry::Kind::PlayersSet:
                {
                    this->SetPlayersInternal(std::static_pointer_cast<PlayersSet>(entry));

                    // first entry must be PlayersSet and is thus replaced
                    if(this->entries.size() == 1)
                    {
                        this->entries.pop_back();
                    }

                    this->entries.push_back(entry);
                    break;
                }
                case Entry::Kind::Deal:
                {
                    this->PushDealInternal(std::static_pointer_cast<Deal>(entry));

                    this->entries.push_back(entry);
                    break;
                }
                case Entry::Kind::MandatorySoloTrigger:
                {
                    this->TriggerMandatorySolo();
                    break;
                }
                default:
                    throw std::exception("value of Entry::Kind not handled");
                }
            }
        };

        auto oldEntries = this->entries;

        auto newEntries = this->repository->Load(id);

        try
        {
            this->entries.clear();
            applyEntries(newEntries);
        }
        catch (...)
        {
            this->entries.clear();
            applyEntries(oldEntries);
            throw;
        }
    }

    bool GameInfo::HasPlayersSet() const
    {
        return std::find_if(
                    this->entries.begin(),
                    this->entries.end(),
                    [](const std::shared_ptr<Entry>& entry) { return entry->Kind() == Entry::Kind::PlayersSet; }) != this->entries.end();
    }

    std::vector<unsigned int> GameInfo::MultiplierPreview() const
    {
        return this->multiplierInfo.GetPreview();
    }

    unsigned int GameInfo::LastNumberOfEvents() const
    {
        auto lastDeal = std::find_if(
                    this->entries.rbegin(),
                    this->entries.rend(),
                    [](const std::shared_ptr<Entry>& entry) { return entry->Kind() == Entry::Kind::Deal; });

        if(lastDeal == this->entries.rend())
        {
            return 0U;
        }

        return std::static_pointer_cast<Deal>(*lastDeal)->NumberOfEvents().Value();
    }

    unsigned int GameInfo::TotalCashCents() const
    {
        auto sum = std::accumulate(this->playerInfos.begin(),
                                  this->playerInfos.end(),
                                  0,
                                  [](unsigned int total, const std::shared_ptr<PlayerInfoInternal>& player){ total += player->CashCents(); return total; });
        sum += (MaxPlayers - static_cast<int>(this->playerInfos.size())) * this->AbsentPlayerCashCents();
        return sum;
    }

    unsigned int GameInfo::AbsentPlayerCashCents() const
    {
        return CalculateCashCents(this->MaximumCurrentScore());
    }

    enum GameInfo::MandatorySolo GameInfo::MandatorySolo() const
    {
        unsigned int count = this->DealsRecorded();

        if(count == 0)
        {
            return MandatorySolo::CannotTrigger;
        }

        return this->multiplierInfo.GetIsMandatorySolo(count) ? MandatorySolo::Active : MandatorySolo::Ready;
    }

    unsigned int GameInfo::RemainingGamesInRound() const
    {
        if(numberOfPresentPlayers == 0)
        {
            return 0;
        }

        return (2 * this->numberOfPresentPlayers + this->initialDealerIndex - this->currentDealerIndex) % this->numberOfPresentPlayers;
    }

    void Backend::GameInfo::SetPlayersInternal(const std::shared_ptr<PlayersSet>& playersSet)
    {
        bool dealerFound = false;
        auto players = playersSet->Players();
        auto dealer = playersSet->Dealer();
        const auto playersSize = players.size();

        if(playersSize < 4U)
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
                    throw std::exception((std::string("names must be unique, offender: \"") + players[i] + std::string("\"")).c_str());
                }
            }
        }

        if(!dealerFound)
        {
            throw std::exception("name of dealer must be among the players");
        }

        const unsigned int playersSetSizeRequiringSitoutScheme = 5U;
        if(playersSize > playersSetSizeRequiringSitoutScheme && playersSet->SitOutScheme().size() + playersSetSizeRequiringSitoutScheme != playersSize)
        {
            throw std::exception("incorrect size of the sit out scheme");
        }

        this->SortAndSetPlayerInfos(playersSet->Players());
        this->SetDealer(playersSet->Dealer());
        this->initialDealerIndex = this->currentDealerIndex;
        this->SetAndApplyScheme(playersSet->SitOutScheme());
    }

    void GameInfo::SortAndSetPlayerInfos(std::vector<std::string> players)
    {
        this->numberOfPresentPlayers = static_cast<unsigned int>(players.size());

        std::vector<std::shared_ptr<PlayerInfoInternal>> newInfos;

        auto playersIt = players.begin();
        auto playersEnd = players.end();
        for(; playersIt != playersEnd; ++playersIt)
        {
            if(this->nameToPlayerInfo.count(*playersIt) == 0)
            {
                auto newPlayerInfo = std::make_shared<PlayerInfoInternal>(*playersIt,
                                                                          [&](unsigned int index){ return this->multiplierInfo.GetMultiplier(index); },
                                                                          [&](){ return this->MaximumCurrentScore(); });
                while(newPlayerInfo->NumberOfRecordedDeals() < this->DealsRecorded())
                {
                    newPlayerInfo->PushDealResult(false, 0, false);
                }

                this->nameToPlayerInfo[*playersIt] = newPlayerInfo;
            }

            auto currentPlayerInfo = this->nameToPlayerInfo[*playersIt];
            currentPlayerInfo->SetIsPresent(true);
            newInfos.push_back(currentPlayerInfo);
        }

        auto playerInfosIt = this->playerInfos.begin();
        auto playerInfosEnd = this->playerInfos.end();
        for(; playerInfosIt != playerInfosEnd; ++playerInfosIt)
        {

            auto playerIt = std::find_if(
                        players.begin(),
                        players.end(),
                        [&](const std::string& player){ return player == (*playerInfosIt)->Name(); });

            if(playerIt == players.end() && (*playerInfosIt)->HasPlayed())
            {
                (*playerInfosIt)->SetIsPresent(false);
                (*playerInfosIt)->SetIsPlaying(false);
                newInfos.push_back(*playerInfosIt);
            }
        }

        this->playerInfos = newInfos;
    }

    void GameInfo::SetDealer(std::string dealer)
    {
        auto dealerIt = std::find_if(
                    this->playerInfos.begin(),
                    this->playerInfos.end(),
                    [&](const std::shared_ptr<PlayerInfoInternal>& pi){ return pi->Name() == dealer; });

        if(dealerIt == this->playerInfos.end())
        {
            throw std::exception("logic error: dealer must be among the players");
        }

        this->currentDealerIndex = static_cast<unsigned int>(dealerIt - this->playerInfos.begin());
    }

    void GameInfo::SetAndApplyScheme(std::set<unsigned int> newScheme)
    {
        this->sitOutScheme = std::move(newScheme);

        if(this->numberOfPresentPlayers > 4)
        {
            this->sitOutScheme.insert(0U);
        }

        this->ApplyScheme();
    }

    void GameInfo::ApplyScheme()
    {
        for(unsigned int i = this->currentDealerIndex; i < this->currentDealerIndex + this->numberOfPresentPlayers; ++i)
        {
            bool isPlaying = this->sitOutScheme.count(i - this->currentDealerIndex) == 0;

            this->playerInfos[i % this->numberOfPresentPlayers]->SetIsPlaying(isPlaying);
        }
    }

    void Backend::GameInfo::PushDealInternal(const std::shared_ptr<Deal>& deal)
    {
        auto changes = deal->Changes();
        auto actualChanges = this->AutoCompleteDeal(changes);

        std::string soloPlayer = GameInfo::FindSoloPlayer(actualChanges);

        auto changesIt = actualChanges.begin();
        auto changesEnd = actualChanges.end();
        for(; changesIt != changesEnd; ++changesIt)
        {
            auto player = this->nameToPlayerInfo.at(changesIt->first);

            if(!player->IsPlaying())
            {
                throw std::exception((std::string("found change for player not playing: \"") + player->Name() + std::string("\"")).c_str());
            }

            player->PushDealResult(true, changesIt->second, player->Name() == soloPlayer);

            player->SetHasPlayed(true);

            auto relevantChange = std::find_if(changes.begin(), changes.end(), [&](const std::pair<std::string, int>& change){ return change.first == player->Name(); });
            if(relevantChange != changes.end())
            {
                player->SetInputInDeal(std::to_string(relevantChange->second));
            }
            else
            {
                player->SetInputInDeal(std::string(""));
            }
        }

        auto playerInfosIt = this->playerInfos.begin();
        auto playerInfosEnd = this->playerInfos.end();
        for(; playerInfosIt != playerInfosEnd; ++playerInfosIt)
        {
            if(!(*playerInfosIt)->IsPlaying())
            {
                (*playerInfosIt)->PushDealResult(false, 0, false);
                (*playerInfosIt)->SetInputInDeal(std::string(""));
            }
        }

        this->currentDealerIndex = (this->currentDealerIndex + 1) % this->numberOfPresentPlayers;

        EventInfo eventInfo { deal->NumberOfEvents(), Players(this->numberOfPresentPlayers), ::Backend::MandatorySolo(false) };
        this->multiplierInfo.PushDeal(eventInfo);

        this->ApplyScheme();
    }

    std::vector<std::pair<std::string, int>> GameInfo::AutoCompleteDeal(std::vector<std::pair<std::string, int>> inputChanges)
    {
        auto changesIt = inputChanges.begin();
        auto changesEnd = inputChanges.end();
        if(inputChanges.size() == 4)
        {
            int checksum = std::accumulate(changesIt,
                                           changesEnd,
                                           0,
                                           [](int s, const std::pair<std::string, int>& c){ s += c.second; return s; });
            if(checksum != 0)
            {
                throw std::exception("changes must sum to zero");
            }

            return inputChanges;
        }
        else if(inputChanges.size() > 4 || inputChanges.empty())
        {
            throw std::exception("there can never be more than 4 or zero changes");
        }

        std::vector<std::pair<std::string, int>> newChanges;
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
                                         [&](const std::pair<std::string, int>& change){ return change.first == (*playersIt)->Name(); });
            if(changeIt != changesEnd)
            {
                continue;
            }

            newChanges.emplace_back(std::pair<std::string, int>((*playersIt)->Name(), valueToSet));
        }

        return newChanges;
    }

    std::string GameInfo::FindSoloPlayer(const std::vector<std::pair<std::string, int>>& changes)
    {
        std::string losingPlayer;
        std::string winningPlayer;

        unsigned int losers = 0;
        unsigned int winners = 0;

        for (const auto & change : changes)
        {
            if(change.second < 0)
            {
                ++losers;
                losingPlayer = change.first;
            }
            else
            {
                ++winners;
                winningPlayer = change.first;
            }
        }

        if(losers == 3 && winners == 1)
        {
            return winningPlayer;
        }
        else if(winners == 3 && losers == 1)
        {
            return losingPlayer;
        }
        else
        {
            return std::string();
        }
    }

    int GameInfo::MaximumCurrentScore() const
    {
        if(this->playerInfos.empty())
        {
            return 0;
        }

        return (*std::max_element(this->playerInfos.begin(),
                                  this->playerInfos.end(),
                                  [](const std::shared_ptr<PlayerInfoInternal>& p1, const std::shared_ptr<PlayerInfoInternal>& p2){ return p1->CurrentScore() < p2->CurrentScore(); }))->CurrentScore();
    }

    void GameInfo::ReconstructEventsForMultiplierInfo()
    {
        std::vector<EventInfo> events;
        unsigned int relevantNumberOfPlayers = 4;

        for (auto & entry : this->entries)
        {
            if(entry->Kind() == Entry::Kind::MandatorySoloTrigger)
            {
                auto numberOfEvents = events.back().number;
                events.pop_back();

                EventInfo event{ numberOfEvents, Players(relevantNumberOfPlayers), Backend::MandatorySolo(true) };
                events.push_back(event);

                continue;
            }
            else if(entry->Kind() == Entry::Kind::PlayersSet)
            {
                auto playersSet = std::static_pointer_cast<PlayersSet>(entry);
                relevantNumberOfPlayers = static_cast<unsigned int>(playersSet->Players().size());
                continue;
            }

            auto deal = std::static_pointer_cast<Deal>(entry);

            EventInfo event{ deal->NumberOfEvents(), Players(relevantNumberOfPlayers), Backend::MandatorySolo(false) };

            events.push_back(event);
        }

        this->multiplierInfo.ResetTo(events);
    }

    unsigned int GameInfo::DealsRecorded() const
    {
        return static_cast<unsigned int>(std::count_if(
                                             this->entries.begin(),
                                             this->entries.end(),
                                             [](const std::shared_ptr<Entry>& entry) { return entry->Kind() == Entry::Kind::Deal; }));
    }

    GameInfo::PlayerInfoInternal::PlayerInfoInternal(std::string name,
                                                     std::function<unsigned short(unsigned int)> multiplierAccessor, //NOLINT(google-runtime-int)
                                                     std::function<int()> maxCurrentScoreAccessor)
        : PlayerInfo(std::move(name), std::move(multiplierAccessor), std::move(maxCurrentScoreAccessor))
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

    void GameInfo::PlayerInfoInternal::PushDealResult(bool hasPlayedInDeal, int unmultipliedScore, bool playedSolo)
    {
        if(!hasPlayedInDeal)
        {
            unmultipliedScore = 0;
        }

        this->multipliedResults.push_back(unmultipliedScore * this->multiplierAccessor(static_cast<unsigned int>(this->dealResults.size())));
        this->accumulatedMultipliedResults.push_back(this->CurrentScore() + this->multipliedResults.back());
        this->dealResults.emplace_back(hasPlayedInDeal, unmultipliedScore, playedSolo);
    }

    void GameInfo::PlayerInfoInternal::PopLastDealResult()
    {
        this->dealResults.pop_back();
        this->multipliedResults.pop_back();
        this->accumulatedMultipliedResults.pop_back();
        this->dealInput.pop_back();
    }

    void GameInfo::PlayerInfoInternal::SetInputInDeal(const std::string& input)
    {
        this->dealInput.push_back(input);
    }

    size_t GameInfo::PlayerInfoInternal::NumberOfRecordedDeals() const
    {
        return this->dealResults.size();
    }
}
