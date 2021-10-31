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

#include <fstream>
#include <filesystem>
#include "diskrepository.h"

Backend::DiskRepository::DiskRepository()
{
}

void Backend::DiskRepository::Save(const std::vector<std::shared_ptr<Backend::Entry>> & entries, const std::wstring & identifier)
{
    std::wofstream wofs(identifier);

    if(!(wofs.is_open() && wofs.good()))
    {
        throw std::exception("unable to open stream for writing");
    }

    deserializer.Serialize(entries, wofs);

    if(!(wofs.is_open() && wofs.good()))
    {
        throw std::exception("bad stream after writing");
    }

    wofs.close();
}

std::vector<std::shared_ptr<Backend::Entry>> Backend::DiskRepository::Load(const std::wstring & identifier)
{
    try
    {
        std::filesystem::path path(identifier);
        if(!std::filesystem::exists(path))
        {
            throw std::exception("file does not exist");
        }
    }
    catch (const std::exception&)
    {
        throw std::exception("exception when opening");
    }

    std::wifstream wifs(identifier);

    if(!(wifs.is_open() && wifs.good()))
    {
        throw std::exception("unable to open stream for reading");
    }

    auto entries = deserializer.Deserialize(wifs);

    wifs.close();

    return entries;
}
