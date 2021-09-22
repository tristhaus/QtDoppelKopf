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
#include <numeric>

namespace Backend
{
    PlayerInfo::PlayerInfo(std::wstring name, std::function<unsigned short(unsigned int)> multiplierAccessor)
        : name(name),
          hasPlayed(false),
          isPresent(false),
          isPlaying(false),
          participatedInLastDeal(false),
          multiplierAccessor(multiplierAccessor)
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
            retval += dealResults[index] * this->multiplierAccessor(index);
        }

        return retval;
    }

    bool PlayerInfo::ParticipatedInLastDeal() const
    {
        return this->participatedInLastDeal;
    }

    int PlayerInfo::ScoreInLastDeal() const
    {
        return this->dealResults.back() * this->multiplierAccessor(static_cast<unsigned int>(this->dealResults.size()) - 1);
    }

    std::wstring PlayerInfo::InputInLastDeal() const
    {
        return !this->dealInput.empty() ? this->dealInput.back() : std::wstring(L"");
    }
}
