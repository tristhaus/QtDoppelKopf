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

#ifndef EVENTINFO_H
#define EVENTINFO_H

namespace Backend
{
    /*!
     * Helper template to create named arguments.
     */
    template<typename T>
    class NamedNumber
    {
        const T value;
    public:
        NamedNumber(T value)
            : value(value)
        {
        }

        T Value() const
        {
            return value;
        }
    };

    typedef NamedNumber<unsigned int> NumberOfEvents;
    typedef NamedNumber<unsigned int> Players;

    /*!
     * \brief The EventInfo struct collects information regarding
     *        the number of multiplier-relevant events
     *        and the number of present players.
     */
    struct EventInfo
    {
        NumberOfEvents number;
        Players players;
    };
}

#endif // EVENTINFO_H
