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

Backend::PlayersSet::PlayersSet(std::vector<std::wstring> players,
                                std::wstring dealer,
                                std::set<unsigned int> sitOutScheme,
                                std::wstring previousDealer)
    : players(players),
      dealer(dealer),
      sitOutScheme(sitOutScheme),
      previousDealer(previousDealer)
{
}

enum Backend::Entry::Kind Backend::PlayersSet::Kind() const
{
    return Backend::Entry::Kind::PlayersSet;
}

std::set<unsigned int> Backend::PlayersSet::SitOutScheme() const
{
    return sitOutScheme;
}

std::wstring Backend::PlayersSet::Dealer() const
{
    return dealer;
}

std::vector<std::wstring> Backend::PlayersSet::Players() const
{
    return players;
}

std::wstring Backend::PlayersSet::PreviousDealer() const
{
    return previousDealer;
}
