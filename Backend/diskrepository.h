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

#include "../Backend/repository.h"

#ifndef DISKREPOSITORY_H
#define DISKREPOSITORY_H

namespace Backend
{
    class DiskRepository final : public Repository
    {
    private:
        Backend::DeSerializer deserializer;

    public:
        /*!
         * \brief Initializes a new instance.
         */
        DiskRepository();

        /*!
         * \reimp
         */
        virtual void Save(const std::vector<std::shared_ptr<Backend::Entry>> & entries, const std::string & identifier);

        /*!
         * \reimp
         */
        virtual std::vector<std::shared_ptr<Backend::Entry>> Load(const std::string & identifier);
    };
}

#endif // DISKREPOSITORY_H
