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

void Backend::DiskRepository::Save(const std::vector<std::shared_ptr<Backend::Entry>> & entries, const std::string & identifier)
{
    std::filesystem::path path = std::filesystem::u8path(identifier);
    std::ofstream ofs(path);

    if(!(ofs.is_open() && ofs.good()))
    {
        throw std::exception((std::string(u8"unable to open stream for writing \"") + path.string() + std::string(u8"\"")).c_str());
    }

    deserializer.Serialize(entries, ofs);

    if(!(ofs.is_open() && ofs.good()))
    {
        throw std::exception((std::string(u8"bad stream after writing \"") + path.string() + std::string(u8"\"")).c_str());
    }

    ofs.close();
}

std::vector<std::shared_ptr<Backend::Entry>> Backend::DiskRepository::Load(const std::string & identifier)
{
    std::filesystem::path path = std::filesystem::u8path(identifier);
    if(!std::filesystem::exists(path))
    {
        throw std::exception((std::string(u8"file \"") + path.string() + std::string(u8"\" does not exist")).c_str());
    }

    std::ifstream ifs;

    try
    {
        ifs.open(path);
    }
    catch (const std::exception& exception)
    {
        throw std::exception((std::string(u8"when opening \"") + path.string() + std::string(u8"\" exception: \"") + exception.what() + std::string(u8"\"")).c_str());
    }

    if(!(ifs.is_open() && ifs.good()))
    {
        throw std::exception((std::string(u8"unable to open stream \"") + path.string() + std::string(u8"\" for reading")).c_str());
    }

    auto entries = deserializer.Deserialize(ifs);

    ifs.close();

    return entries;
}
