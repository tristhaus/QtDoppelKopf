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

#ifndef CASHCALCULATION_H
#define CASHCALCULATION_H

namespace Backend
{
    /*!
     * \brief Calculates the due balance in Euro cents based on the given point difference.
     * \param pointDifference The point difference to convert.
     * \return The due balance in Euro cents.
     */
    unsigned int CalculateCashCents(unsigned int pointDifference);
}

#endif // CASHCALCULATION_H
