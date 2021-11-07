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

#include "entry.h"
#include <vector>
#include <set>
#include <string>

#ifndef PLAYERSSET_H
#define PLAYERSSET_H

namespace Backend
{
    /*!
     * \brief The PlayersSet class represents a change in the players
     *        present at the table.
     */
    class PlayersSet final : public Entry
    {
    private:
        std::vector<std::wstring> players;
        std::wstring dealer;
        std::set<unsigned int> sitOutScheme;
        std::wstring previousDealer;

    public:
        /*!
         * \brief Initializes a new instance.
         * \param players The names of the players.
         * \param dealer The name of the current dealer.
         * \param sitOutScheme The sit out scheme.
         */
        PlayersSet(std::vector<std::wstring> players,
                   std::wstring dealer,
                   std::set<unsigned int> sitOutScheme,
                   std::wstring previousDealer);

        /*!
         * \reimp
         */
        virtual enum Entry::Kind Kind() const;

        /*!
         * \brief Gets the names of the players.
         * \return The names of the players.
         */
        std::vector<std::wstring> Players() const;

        /*!
         * \brief Gets the name of the current dealer.
         * \return The name of the current dealer.
         */
        std::wstring Dealer() const;

        /*!
         * \brief Gets the sit out scheme.
         * \return The sit out scheme.
         */
        std::set<unsigned int> SitOutScheme() const;

        /*!
         * \brief Gets the name of the last current dealer before this set.
         * \return The name of the last current dealer before this set.
         */
        std::wstring PreviousDealer() const;
    };
}

#endif // PLAYERSSET_H
