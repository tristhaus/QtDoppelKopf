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

#include "memoryrepository.h"
#include "../Backend/deserializer.h"
#include <sstream>

MemoryRepository::MemoryRepository()
= default;

void MemoryRepository::Save(const std::vector<std::shared_ptr<Backend::Entry>> & entries, const std::string & identifier)
{
    std::stringstream ss;
    deserializer.Serialize(entries, ss);

    std::string content;
    ss >> content;

    storage[identifier] = content;
}

std::vector<std::shared_ptr<Backend::Entry>> MemoryRepository::Load(const std::string & identifier)
{
    std::string content;
    bool found = TryGetByIdentifier(identifier, content);

    if(!found)
    {
        throw std::exception((std::string(u8"content not found by identifier: \"") + identifier + std::string(u8"\"")).c_str());
    }

    std::stringstream ss;
    ss << content;

    return deserializer.Deserialize(ss);
}

bool MemoryRepository::TryGetByIdentifier(const std::string& identifier, std::string& string) const
{
    auto it = storage.find(identifier);

    if(it == storage.end())
    {
        return false;
    }

    string = it->second;
    return true;
}

void MemoryRepository::SetByIdentifier(const std::string& identifier, const std::string& string)
{
    storage[identifier] = string;
}
