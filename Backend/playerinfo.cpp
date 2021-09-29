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
#include <numeric>
#include <algorithm>

namespace Backend
{
    PlayerInfo::PlayerInfo(std::wstring name,
                           std::function<unsigned short(unsigned int)> multiplierAccessor,
                           std::function<int()> maxCurrentScoreAccessor)
        : name(name),
          hasPlayed(false),
          isPresent(false),
          isPlaying(false),
          multiplierAccessor(multiplierAccessor),
          maxCurrentScoreAccessor(maxCurrentScoreAccessor)
    {
    }

    std::wstring PlayerInfo::Name() const
    {
        return name;
    }

    bool PlayerInfo::HasPlayed() const
    {
        return hasPlayed;
    }

    bool PlayerInfo::IsPresent() const
    {
        return isPresent;
    }

    bool PlayerInfo::IsPlaying() const
    {
        return isPlaying;
    }

    int PlayerInfo::CurrentScore() const
    {
        int retval = 0;
        for(unsigned int index = 0; index < this->dealResults.size(); ++index)
        {
            retval += dealResults[index].second * this->multiplierAccessor(index);
        }

        return retval;
    }

    bool PlayerInfo::ParticipatedInLastDeal() const
    {
        return !this->dealResults.empty() ? this->dealResults.back().first : false;
    }

    int PlayerInfo::ScoreInLastDeal() const
    {
        return this->dealResults.back().second * this->multiplierAccessor(static_cast<unsigned int>(this->dealResults.size()) - 1);
    }

    std::wstring PlayerInfo::InputInLastDeal() const
    {
        return !this->dealInput.empty() ? this->dealInput.back() : std::wstring(L"");
    }

    unsigned int PlayerInfo::CashCents() const
    {
        return CalculateCashCents(this->maxCurrentScoreAccessor() - this->CurrentScore());
    }

    unsigned int PlayerInfo::NumberGamesWon() const
    {
        return static_cast<unsigned int>(std::count_if(this->dealResults.begin(), this->dealResults.end(), [](std::pair<bool, int> item){ return item.first && item.second > 0; }));
    }

    unsigned int PlayerInfo::NumberGamesLost() const
    {
        return static_cast<unsigned int>(std::count_if(this->dealResults.begin(), this->dealResults.end(), [](std::pair<bool, int> item){ return item.first && item.second < 0; }));
    }

    unsigned int PlayerInfo::NumberGames() const
    {
        return static_cast<unsigned int>(std::count_if(this->dealResults.begin(), this->dealResults.end(), [](std::pair<bool, int> item){ return item.first; }));
    }

    int PlayerInfo::MaxSingleWin() const
    {
        int retval = 0;
        for(unsigned int index = 0; index < this->dealResults.size(); ++index)
        {
            retval = std::max(retval, dealResults[index].second * this->multiplierAccessor(index));
        }

        return retval;
    }

    int PlayerInfo::MaxSingleLoss() const
    {
        int retval = 0;
        for(unsigned int index = 0; index < this->dealResults.size(); ++index)
        {
            retval = std::min(retval, dealResults[index].second * this->multiplierAccessor(index));
        }

        return retval;
    }

    int PlayerInfo::UnmultipliedScore() const
    {
        int sum = 0;

        std::for_each(this->dealResults.begin(),
                      this->dealResults.end(),
                      [&sum](std::pair<bool, int> item) { sum += item.second; } );

        return sum;
    }
}
