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
#include "../Backend/entry.h"
#include "../Backend/deserializer.h"
#include <map>

#ifndef MEMORYREPOSITORY_H
#define MEMORYREPOSITORY_H

/*!
 * \class MemoryRepository
 * \brief The MemoryRepository class persists games to memory.
 */
class MemoryRepository final : public Backend::Repository
{
private:
    Backend::DeSerializer deserializer;
    std::map<std::u8string, std::string> storage;

public:
    /*!
     * \brief Initializes a new instance.
     */
    MemoryRepository();

    /*!
     * \reimp
     */
    virtual void Save(const std::vector<std::shared_ptr<Backend::Entry>> & entries, const std::u8string & identifier);

    /*!
     * \reimp
     */
    virtual std::vector<std::shared_ptr<Backend::Entry>> Load(const std::u8string & identifier);

    /*!
     * \brief Attempts to get the string stored under the identifier.
     * \param identifier The identifier to try and get the string for.
     * \param string The stored string, if any.
     * \return true if found.
     */
    bool TryGetByIdentifier(const std::u8string & identifier, std::string & string) const;

    /*!
     * \brief Stores the string under the identifier.
     * \param identifier The identifier to set the string for.
     * \param string The string to be stored.
     */
    void SetByIdentifier(const std::u8string & identifier, const std::string & string);
};

#endif // MEMORYREPOSITORY_H
