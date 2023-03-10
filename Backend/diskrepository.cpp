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

#include "diskrepository.h"
#include <filesystem>
#include <fstream>

Backend::DiskRepository::DiskRepository()
= default;

void Backend::DiskRepository::Save(const std::vector<std::shared_ptr<Backend::Entry>> & entries, const std::u8string & identifier)
{
    std::filesystem::path path = std::filesystem::path(identifier);
    std::ofstream ofs(path);

    if(!(ofs.is_open() && ofs.good()))
    {
        throw std::exception((std::string("unable to open stream for writing \"") + path.string() + std::string("\"")).c_str());
    }

    deserializer.Serialize(entries, ofs);

    if(!(ofs.is_open() && ofs.good()))
    {
        throw std::exception((std::string("bad stream after writing \"") + path.string() + std::string("\"")).c_str());
    }

    ofs.close();
}

std::vector<std::shared_ptr<Backend::Entry>> Backend::DiskRepository::Load(const std::u8string & identifier)
{
    std::filesystem::path path = std::filesystem::path(identifier);
    if(!std::filesystem::exists(path))
    {
        throw std::exception((std::string("file \"") + path.string() + std::string("\" does not exist")).c_str());
    }

    std::ifstream ifs;

    try
    {
        ifs.open(path);
    }
    catch (const std::exception& exception)
    {
        throw std::exception((std::string("when opening \"") + path.string() + std::string("\" exception: \"") + exception.what() + std::string("\"")).c_str());
    }

    if(!(ifs.is_open() && ifs.good()))
    {
        throw std::exception((std::string("unable to open stream \"") + path.string() + std::string("\" for reading")).c_str());
    }

    auto entries = deserializer.Deserialize(ifs);

    ifs.close();

    return entries;
}
