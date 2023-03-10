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

#include "deserializer.h"
#include "entry.h"

#ifndef REPOSITORY_H
#define REPOSITORY_H

namespace Backend
{
    class Repository
    {
    public:
        /*!
         * \brief Saves entries to the storage.
         * \param game The entries to save.
         * \param identifier The identifier, which may be a file path if the underlying storage is the disk.
         */
        virtual void Save(const std::vector<std::shared_ptr<Entry>> & entries, const std::u8string & identifier) = 0;

        /*!
         * \brief Loads entries from storage.
         * \param identifier The identifier, which may be a file path if the underlying storage is the disk.
         * \return The loaded entries.
         */
        virtual std::vector<std::shared_ptr<Entry>> Load(const std::u8string & identifier) = 0;
    };
}

#endif // REPOSITORY_H
