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

#ifndef MULTIPLIERINFO_H
#define MULTIPLIERINFO_H

#include "eventinfo.h"
#include <vector>

namespace Backend
{
    /*!
     * \brief The MultiplierInfo class represents logic regarding
     *        the calculation of the current and future multipliers.
     */
    class MultiplierInfo
    {
    private:
        template<typename T>
        class SparseVector{
        private:
            std::vector<T> data;

        public:
            T& at(const unsigned int index)
            {
                this->ensureSizeOfAtLeast(index + 1);

                return this->data.at(index);
            }

            [[nodiscard]] const T at(const unsigned int index) const
            {
                return index < data.size()
                        ? this->data.at(index)
                        : T{};
            }

            void insert(const unsigned int index, const unsigned int count, const T & value)
            {
                this->ensureSizeOfAtLeast(index + 1);

                this->data.insert(data.begin() + index, count, value);
            }

            void clear()
            {
                this->data.clear();
            }

            unsigned int countAfter(const unsigned int index, const T & value) const
            {
                return index < data.size()
                        ? static_cast<unsigned int>(std::count(this->data.begin() + index, this->data.end(), value))
                        : 0U;
            }

        private:
            void ensureSizeOfAtLeast(const unsigned int targetSize)
            {
                const auto oldSize = this->data.size();
                if(oldSize <= targetSize)
                {
                    this->data.insert(this->data.end(), targetSize - oldSize, T{});
                }
            }
        };

        unsigned int dealIndex;
        SparseVector<std::pair<unsigned short, bool>> effective; //NOLINT(google-runtime-int)

    public:
        /*!
         * \brief Initializes a new instance.
         */
        MultiplierInfo();

        /*!
         * \brief Pushes the result of a deal.
         * \param eventInfo Collection of the information regarding a deal.
         */
        void PushDeal(const EventInfo & eventInfo);

        /*!
         * \brief Reinitializes the contained data based on the provided events.
         *        Typically used after the events were rewritten in some fashion.
         * \param events The new collection of events to consider.
         */
        void ResetTo(const std::vector<EventInfo> & events);

        /*!
         * \brief Gets the final multiplier for some indexed deal.
         * \param index The index of the deal in question.
         * \return The final multiplier to be applied to the deal results.
         */
        [[nodiscard]] unsigned short GetMultiplier(const unsigned int & index) const; //NOLINT(google-runtime-int)

        /*!
         * \brief Gets a value indicating whether the deal is a mandatory solo.
         * \param index The index of the deal in question.
         * \return A value indicating whether the deal is a mandatory solo.
         */
        [[nodiscard]] bool GetIsMandatorySolo(const unsigned int & index) const;

        /*!
         * \brief Gets the future levels of multiplication (which are the indices of the vector returned).
         * \return A vector containing counts for single, double ... etc. level of multiplication.
         */
        [[nodiscard]] std::vector<unsigned int> GetPreview() const;
    };
}

#endif // MULTIPLIERINFO_H
