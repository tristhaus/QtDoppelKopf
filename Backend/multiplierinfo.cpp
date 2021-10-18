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

#include <string>
#include <algorithm>

Backend::MultiplierInfo::MultiplierInfo()
    : dealIndex(0)
{
    this->effective.push_back(std::make_pair(0u, false));
}

void Backend::MultiplierInfo::PushDeal(const Backend::EventInfo eventInfo)
{
    auto GrowEffective = [this](unsigned int minIndex)
    {
        while(minIndex >= this->effective.size())
        {
            this->effective.push_back(std::make_pair(0u, false));
        }
    };

    unsigned int effectiveIndex = dealIndex + 1;

    GrowEffective(effectiveIndex);

    if(eventInfo.mandatorySolo)
    {
        for(unsigned int iter = 0; iter < eventInfo.players.Value(); ++iter)
        {
            this->effective.insert(effective.begin() + effectiveIndex, std::make_pair(0u, true));
            ++effectiveIndex;
        }
    }

    unsigned int baseIndex = effectiveIndex;

    for(unsigned int event = 0; event < eventInfo.number.Value(); ++event)
    {
        effectiveIndex = baseIndex;

        GrowEffective(effectiveIndex);

        while(this->effective[effectiveIndex].first == 3u)
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

    ++dealIndex;
}

void Backend::MultiplierInfo::ResetTo(const std::vector<EventInfo> events)
{
    this->effective.clear();
    dealIndex = 0;

    for (auto event : events) {
        this->PushDeal(event);
    }

    dealIndex = static_cast<unsigned int>(events.size());
}

unsigned short Backend::MultiplierInfo::GetMultiplier(const unsigned int index) const
{
    if(this->effective.size() <= index)
    {
        throw std::exception("attempt to get multiplier for game that does not exist");
    }

    switch (this->effective[index].first)
    {
    case 3:
        return 8u;
    case 2:
        return 4u;
    case 1:
        return 2u;
    case 0:
        return 1u;
    default:
        throw std::exception((std::string("not supported bock of") + std::to_string(static_cast<unsigned int>(this->effective[index].first))).c_str());
    }
}

bool Backend::MultiplierInfo::GetIsMandatorySolo(const unsigned int index) const
{
    if(this->effective.size() <= index)
    {
        throw std::exception("attempt to get mandatory solo for game that does not exist");
    }

    return this->effective[index].second;
}

std::vector<unsigned int> Backend::MultiplierInfo::GetPreview() const
{
    return std::vector<unsigned int>
    {
        static_cast<unsigned int>(std::count(effective.begin() + dealIndex, effective.end(), std::pair<unsigned short, bool>(1u, false))),
        static_cast<unsigned int>(std::count(effective.begin() + dealIndex, effective.end(), std::pair<unsigned short, bool>(2u, false))),
        static_cast<unsigned int>(std::count(effective.begin() + dealIndex, effective.end(), std::pair<unsigned short, bool>(3u, false)))
    };
}
