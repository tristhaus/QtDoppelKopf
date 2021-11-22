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
#include "eventinfo.h"
#include <string>
#include <vector>

#ifndef DEAL_H
#define DEAL_H

namespace Backend
{
    /*!
     * \brief The Deal class represents a completed deal
     *        and its results.
     */
    class Deal final : public Entry
    {
    private:
        std::vector<std::pair<std::string, int>> changes;
        NumberOfEvents numberOfEvents;
        Players players;

    public:
        /*!
         * \brief Initializes a new instance.
         * \param changes The unmultiplied score changes from this deal.
         * \param numberOfEvents The number of multiplier-relevant events from this deal.
         * \param players The number of players present at this deal.
         */
        Deal(std::vector<std::pair<std::string, int>> changes,
             NumberOfEvents numberOfEvents,
             Players presentPlayers);

        /*!
         * \reimp
         */
        virtual enum Entry::Kind Kind() const;

        /*!
         * \brief Gets the unmultiplied score changes from this deal.
         * \return The unmultiplied score changes from this deal.
         */
        std::vector<std::pair<std::string, int>> Changes() const;

        /*!
         * \brief Gets the number of multiplier-relevant events from this deal.
         * \return The number of multiplier-relevant events from this deal.
         */
        NumberOfEvents NumberOfEvents() const;

        /*!
         * \brief Gets the number of players present at this deal.
         * \return The number of players present at this deal.
         */
        Players Players() const;
    };
}

#endif // DEAL_H
