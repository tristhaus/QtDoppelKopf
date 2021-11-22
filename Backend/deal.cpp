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

#include "deal.h"

Backend::Deal::Deal(std::vector<std::pair<std::string, int>> changes,
                    Backend::NumberOfEvents numberOfEvents,
                    Backend::Players presentPlayers)
    : changes(changes),
      numberOfEvents(numberOfEvents),
      players(presentPlayers)
{
}

enum Backend::Entry::Kind Backend::Deal::Kind() const
{
    return Backend::Entry::Kind::Deal;
}

Backend::NumberOfEvents Backend::Deal::NumberOfEvents() const
{
    return numberOfEvents;
}

Backend::Players Backend::Deal::Players() const
{
    return players;
}

std::vector<std::pair<std::string, int>> Backend::Deal::Changes() const
{
    return changes;
}
