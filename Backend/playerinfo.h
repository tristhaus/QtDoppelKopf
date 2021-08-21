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

#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include <string>

namespace Backend
{
    /*!
     * \brief The PlayerInfo class collects and maintains information
     *        regarding a player identified by name.
     */
    class PlayerInfo
    {
    private:
        std::wstring name;
        bool hasPlayed;
        bool isPresent;
        bool isPlaying;

    public:
        /*!
         * \brief Initializes a new instance from the given name.
         * \param The unique name of the player.
         */
        PlayerInfo(std::wstring name);

        /*!
         * \brief Gets the name of the player.
         * \return The name of the player.
         */
        std::wstring Name() const;

        /*!
         * \brief Gets a value indicating whether the player has participated in any deal.
         * \return A value indicating whether the player has participated in any deal.
         */
        bool HasPlayed() const;

        /*!
         * \brief Sets a value indicating whether the player has participated in any deal.
         * \param a value indicating whether the player has participated in any deal.
         */
        void SetHasPlayed(bool hasPlayed);

        /*!
         * \brief Gets a value indicating whether the player is present at the table.
         * \return A value indicating whether the player is present at the table.
         */
        bool IsPresent() const;

        /*!
         * \brief Sets a value indicating whether the player is present at the table.
         * \param a value indicating whether the player is present at the table.
         */
        void SetIsPresent(bool isPresent);

        /*!
         * \brief Gets a value indicating whether the player is playing during the next deal.
         * \return A value indicating whether the player is playing during the next deal.
         */
        bool IsPlaying() const;

        /*!
         * \brief Sets a value indicating whether the player is playing during the next deal.
         * \param a value indicating whether the player is playing during the next deal.
         */
        void SetIsPlaying(bool isPlaying);
    };
}

#endif // PLAYERINFO_H
