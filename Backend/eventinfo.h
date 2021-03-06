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
        /*!
         * \brief Initializes a new instance.
         * \param The value to contain.
         */
        explicit NamedNumber(T value)
            : value(value)
        {
        }

        /*!
         * \brief Get the contained value.
         * \return The contained value.
         */
        [[nodiscard]] T Value() const
        {
            return value;
        }
    };

    using NumberOfEvents = NamedNumber<unsigned int>;
    using Players = NamedNumber<unsigned int>;
    using MandatorySolo = bool;

    /*!
     * \brief The EventInfo struct collects information regarding
     *        the number of multiplier-relevant events
     *        the number of present players,
     *        and whether a round of mandatory solo (suspending the multiplier)
     *        was triggered.
     */
    struct EventInfo
    {
        NumberOfEvents number;
        Players players;
        MandatorySolo mandatorySolo;
    };
}

#endif // EVENTINFO_H
