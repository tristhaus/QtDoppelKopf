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

#include "playerinfo.h"
#include "cashcalculation.h"
#include <algorithm>
#include <numeric>
#include <utility>

namespace Backend
{
    PlayerInfo::PlayerInfo(std::string name,
                           std::function<unsigned short(unsigned int)> multiplierAccessor, //NOLINT(google-runtime-int)
                           std::function<int()> maxCurrentScoreAccessor)
        : name(std::move(name)),
          hasPlayed(false),
          isPresent(false),
          isPlaying(false),
          multiplierAccessor(std::move(multiplierAccessor)),
          maxCurrentScoreAccessor(std::move(maxCurrentScoreAccessor))
    {
    }

    std::string PlayerInfo::Name() const
    {
        return this->name;
    }

    bool PlayerInfo::HasPlayed() const
    {
        return this->hasPlayed;
    }

    bool PlayerInfo::IsPresent() const
    {
        return this->isPresent;
    }

    bool PlayerInfo::IsPlaying() const
    {
        return this->isPlaying;
    }

    int PlayerInfo::CurrentScore() const
    {
        return this->accumulatedMultipliedResults.empty() ? 0 : this->accumulatedMultipliedResults.back();
    }

    bool PlayerInfo::ParticipatedInLastDeal() const
    {
        return !this->dealResults.empty() ? this->dealResults.back().HasPlayedInDeal : false;
    }

    int PlayerInfo::ScoreInLastDeal() const
    {
        return this->multipliedResults.back();
    }

    std::string PlayerInfo::InputInLastDeal() const
    {
        return !this->dealInput.empty() ? this->dealInput.back() : std::string(u8"");
    }

    unsigned int PlayerInfo::CashCents() const
    {
        return CalculateCashCents(this->maxCurrentScoreAccessor() - this->CurrentScore());
    }

    unsigned int PlayerInfo::NumberGamesWon() const
    {
        return static_cast<unsigned int>(std::count_if(this->dealResults.begin(), this->dealResults.end(), [](DealResult item){ return item.HasPlayedInDeal && item.UnmultipliedScore > 0; }));
    }

    unsigned int PlayerInfo::NumberGamesLost() const
    {
        return static_cast<unsigned int>(std::count_if(this->dealResults.begin(), this->dealResults.end(), [](DealResult item){ return item.HasPlayedInDeal && item.UnmultipliedScore < 0; }));
    }

    unsigned int PlayerInfo::NumberGames() const
    {
        return static_cast<unsigned int>(std::count_if(this->dealResults.begin(), this->dealResults.end(), [](DealResult item){ return item.HasPlayedInDeal; }));
    }

    unsigned int PlayerInfo::SolosWon() const
    {
        return static_cast<unsigned int>(std::count_if(this->dealResults.begin(),
                                                       this->dealResults.end(),
                                                       [](DealResult item)
                                                       {
                                                          return item.HasPlayedInDeal && item.PlayedSolo && item.UnmultipliedScore > 0;
                                                       }));
    }

    unsigned int PlayerInfo::SolosLost() const
    {
        return static_cast<unsigned int>(std::count_if(this->dealResults.begin(),
                                                       this->dealResults.end(),
                                                       [](DealResult item)
                                                       {
                                                          return item.HasPlayedInDeal && item.PlayedSolo && item.UnmultipliedScore < 0;
                                                       }));
    }

    int PlayerInfo::TotalSoloPoints() const
    {
        int sum = 0;

        for (unsigned int index = 0; index < this->dealResults.size(); ++index)
        {
            if(this->dealResults[index].PlayedSolo)
            {
                sum += this->multipliedResults[index];
            }
        }

        return sum;
    }

    int PlayerInfo::MaxSingleWin() const
    {
        if(this->multipliedResults.empty())
        {
            return 0;
        }

        return std::max(0, *std::max_element(this->multipliedResults.begin(), this->multipliedResults.end()));
    }

    int PlayerInfo::MaxSingleLoss() const
    {
        if(this->multipliedResults.empty())
        {
            return 0;
        }

        return std::min(0, *std::min_element(this->multipliedResults.begin(), this->multipliedResults.end()));
    }

    int PlayerInfo::UnmultipliedScore() const
    {
        int sum = 0;

        std::for_each(this->dealResults.begin(),
                      this->dealResults.end(),
                      [&sum](DealResult item) { sum += item.UnmultipliedScore; } );

        return sum;
    }

    std::vector<int> PlayerInfo::ScoreHistory() const
    {
        return this->accumulatedMultipliedResults;
    }
}
