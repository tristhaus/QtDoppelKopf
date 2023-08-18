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

#include "multiplierinfo.h"

#include <algorithm>
#include <string>

Backend::MultiplierInfo::MultiplierInfo()
    : dealIndex(0)
{
}

void Backend::MultiplierInfo::PushDeal(const Backend::EventInfo & eventInfo)
{
    unsigned int effectiveIndex = this->dealIndex + 1;

    if(eventInfo.mandatorySolo)
    {
        this->effective.insert(effectiveIndex, eventInfo.players.Value(), std::make_pair(0U, true));
    }

    const unsigned int baseIndex = effectiveIndex;

    for(unsigned int event = 0; event < eventInfo.number.Value(); ++event)
    {
        effectiveIndex = baseIndex;

        while(this->effective.at(effectiveIndex).first == 3U || this->effective.at(effectiveIndex).second)
        {
            ++effectiveIndex;
        }

        for(unsigned int iter = 0; iter < eventInfo.players.Value(); ++iter)
        {
            this->effective.at(effectiveIndex++).first++;
        }
    }

    ++(this->dealIndex);
}

void Backend::MultiplierInfo::ResetTo(const std::vector<EventInfo> & events)
{
    this->effective.clear();
    this->dealIndex = 0;

    for (const auto & event : events)
    {
        this->PushDeal(event);
    }

    this->dealIndex = static_cast<unsigned int>(events.size());
}

unsigned short Backend::MultiplierInfo::GetMultiplier(const unsigned int & index) const //NOLINT(google-runtime-int)
{
    switch (this->effective.at(index).first)
    {
    case 3:
        return 8U; //NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    case 2:
        return 4U; //NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    case 1:
        return 2U; //NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    case 0:
        return 1U; //NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    default:
        throw std::exception((std::string("not supported bock of ") + std::to_string(static_cast<unsigned int>(this->effective.at(index).first))).c_str());
    }
}

bool Backend::MultiplierInfo::GetIsMandatorySolo(const unsigned int & index) const
{
    return this->effective.at(index).second;
}

std::vector<unsigned int> Backend::MultiplierInfo::GetPreview() const
{
    const auto getCount = [&](const unsigned int exponent) -> unsigned int
    {
        return this->effective.countAfter(this->dealIndex, std::pair<unsigned short, bool>(exponent, false)); //NOLINT(google-runtime-int)
    };

    return std::vector<unsigned int>
    {
        getCount(1U),
        getCount(2U),
        getCount(3U)
    };
}
