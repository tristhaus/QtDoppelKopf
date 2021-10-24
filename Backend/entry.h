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

#ifndef ENTRY_H
#define ENTRY_H

namespace Backend
{
    /*!
     * \brief The Entry class represents a common base
     *        for entries in the game info.
     */
    class Entry
    {
    public:
        /*!
         * \brief The Kind enumeration represents
         *        the type of the entry.
         */
        enum class Kind
        {
            PlayersSet,
            Deal,
            MandatorySoloTrigger,
        };

    public:
        /*!
         * \brief Gets the kind of the entry.
         * \return The kind of the entry.
         */
        virtual enum Kind Kind() const = 0;
    };
}

#endif // ENTRY_H
