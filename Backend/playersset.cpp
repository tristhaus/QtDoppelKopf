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

#include "playersset.h"

#include <utility>

Backend::PlayersSet::PlayersSet(std::vector<std::string> players,
                                std::string dealer,
                                std::set<unsigned int> sitOutScheme,
                                std::string previousDealer)
    : players(std::move(players)),
      dealer(std::move(dealer)),
      sitOutScheme(std::move(sitOutScheme)),
      previousDealer(std::move(previousDealer))
{
}

enum Backend::Entry::Kind Backend::PlayersSet::Kind() const
{
    return Backend::Entry::Kind::PlayersSet;
}

std::set<unsigned int> Backend::PlayersSet::SitOutScheme() const
{
    return this->sitOutScheme;
}

std::string Backend::PlayersSet::Dealer() const
{
    return this->dealer;
}

std::vector<std::string> Backend::PlayersSet::Players() const
{
    return this->players;
}

std::string Backend::PlayersSet::PreviousDealer() const
{
    return this->previousDealer;
}
