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
    this->effective.emplace_back(0U, false);
}

void Backend::MultiplierInfo::PushDeal(const Backend::EventInfo & eventInfo)
{
    auto GrowEffective = [this](unsigned int minIndex)
    {
        while(minIndex >= this->effective.size())
        {
            this->effective.emplace_back(0U, false);
        }
    };

    unsigned int effectiveIndex = this->dealIndex + 1;

    GrowEffective(effectiveIndex);

    if(eventInfo.mandatorySolo)
    {
        for(unsigned int iter = 0; iter < eventInfo.players.Value(); ++iter)
        {
            this->effective.insert(this->effective.begin() + effectiveIndex, std::make_pair(0U, true));
            ++effectiveIndex;
        }
    }

    unsigned int baseIndex = effectiveIndex;

    for(unsigned int event = 0; event < eventInfo.number.Value(); ++event)
    {
        effectiveIndex = baseIndex;

        GrowEffective(effectiveIndex);

        while(this->effective[effectiveIndex].first == 3U)
        {
            ++effectiveIndex;

            GrowEffective(effectiveIndex);
        }

        for(unsigned int iter = 0; iter < eventInfo.players.Value(); ++iter)
        {
            GrowEffective(effectiveIndex);

            this->effective[effectiveIndex++].first++;
        }
    }

    ++(this->dealIndex);
}

void Backend::MultiplierInfo::ResetTo(const std::vector<EventInfo> & events)
{
    this->effective.clear();
    this->dealIndex = 0;
    this->effective.emplace_back(0U, false);

    for (const auto & event : events)
    {
        this->PushDeal(event);
    }

    this->dealIndex = static_cast<unsigned int>(events.size());
}

unsigned short Backend::MultiplierInfo::GetMultiplier(const unsigned int & index) const //NOLINT(google-runtime-int)
{
    if(this->effective.size() <= index)
    {
        throw std::exception((std::string("attempt to get multiplier for game ") + std::to_string(index) + std::string(" which does not exist")).c_str());
    }

    switch (this->effective[index].first)
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
        throw std::exception((std::string("not supported bock of ") + std::to_string(static_cast<unsigned int>(this->effective[index].first))).c_str());
    }
}

bool Backend::MultiplierInfo::GetIsMandatorySolo(const unsigned int & index) const
{
    if(this->effective.size() <= index)
    {
        throw std::exception((std::string("attempt to get mandatory solo for game ") + std::to_string(index) + std::string(" which does not exist")).c_str());
    }

    return this->effective[index].second;
}

std::vector<unsigned int> Backend::MultiplierInfo::GetPreview() const
{
    return std::vector<unsigned int>
    {
        static_cast<unsigned int>(std::count(this->effective.begin() + this->dealIndex, this->effective.end(), std::pair<unsigned short, bool>(1U, false))), //NOLINT(google-runtime-int)
        static_cast<unsigned int>(std::count(this->effective.begin() + this->dealIndex, this->effective.end(), std::pair<unsigned short, bool>(2U, false))), //NOLINT(google-runtime-int)
        static_cast<unsigned int>(std::count(this->effective.begin() + this->dealIndex, this->effective.end(), std::pair<unsigned short, bool>(3U, false)))  //NOLINT(google-runtime-int)
    };
}
