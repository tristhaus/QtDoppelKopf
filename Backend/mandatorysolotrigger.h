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

#ifndef MANDATORYSOLOTRIGGER_H
#define MANDATORYSOLOTRIGGER_H

namespace Backend
{
    /*!
     * \brief The MandatorySoloTrigger class represents
     *        the beginning of a mandatory solo round,
     *        suspending the multiplier.
     */
    class MandatorySoloTrigger final : public Entry
    {
    public:
        /*!
         * \brief Initializes a new instance.
         */
        MandatorySoloTrigger();

        /*!
         * \reimp
         */
        virtual enum Entry::Kind Kind() const;
    };
}

#endif // MANDATORYSOLOTRIGGER_H
