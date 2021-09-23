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

#ifndef TST_MULTIPLIERINFO_H
#define TST_MULTIPLIERINFO_H

#include <gtest/gtest.h>
#include "../Backend/multiplierinfo.h"

TEST(BackendTest, MultiplierShallGiveCorrectDataAfterReset1)
{
    // Arrange
    Backend::MultiplierInfo mi;
    std::vector<Backend::EventInfo> events
    {
        { Backend::NumberOfEvents(0u), Backend::Players(4u) },
        { Backend::NumberOfEvents(1u), Backend::Players(4u) },
        { Backend::NumberOfEvents(0u), Backend::Players(4u) },
        { Backend::NumberOfEvents(0u), Backend::Players(4u) },
        { Backend::NumberOfEvents(1u), Backend::Players(4u) }
    };

    /* // 4 players throughout
     * 0 0u, 0
     * 1 1u, 0
     * 2 0u, 1
     * 3 0u, 1
     * 4 1u  1
     * 5     1 +1
     * 6        1
     * 7        1
     * 8        1
     */

    // Act, Assert
    mi.ResetTo(events);

    EXPECT_EQ(1, mi.GetMultiplier(0));
    EXPECT_EQ(1, mi.GetMultiplier(1));
    EXPECT_EQ(2, mi.GetMultiplier(2));
    EXPECT_EQ(2, mi.GetMultiplier(3));
    EXPECT_EQ(2, mi.GetMultiplier(4));
    EXPECT_EQ(4, mi.GetMultiplier(5));
    EXPECT_EQ(2, mi.GetMultiplier(6));
    EXPECT_EQ(2, mi.GetMultiplier(7));
    EXPECT_EQ(2, mi.GetMultiplier(8));

    EXPECT_EQ(3, mi.GetPreview()[0]);
    EXPECT_EQ(1, mi.GetPreview()[1]);
    EXPECT_EQ(0, mi.GetPreview()[2]);
}

TEST(BackendTest, MultiplierShallGiveCorrectDataAfterReset2)
{
    // Arrange
    Backend::MultiplierInfo mi;
    std::vector<Backend::EventInfo> events
    {
        { Backend::NumberOfEvents(0u), Backend::Players(4u) },
        { Backend::NumberOfEvents(2u), Backend::Players(4u) },
        { Backend::NumberOfEvents(2u), Backend::Players(4u) },
        { Backend::NumberOfEvents(0u), Backend::Players(4u) },
        { Backend::NumberOfEvents(1u), Backend::Players(4u) }
    };

    /* // 4 players throughout
     * 0 0u, 0
     * 1 2u, 0
     * 2 2u, 2
     * 3 0u, 2 +1
     * 4 1u  2 +1
     * 5     2 +1
     * 6       +1 +1 +1
     * 7          +1 +1
     * 8          +1 +1
     * 9          +1 +1
     */

    // Act, Assert
    mi.ResetTo(events);

    EXPECT_EQ(1, mi.GetMultiplier(0));
    EXPECT_EQ(1, mi.GetMultiplier(1));
    EXPECT_EQ(4, mi.GetMultiplier(2));
    EXPECT_EQ(8, mi.GetMultiplier(3));
    EXPECT_EQ(8, mi.GetMultiplier(4));
    EXPECT_EQ(8, mi.GetMultiplier(5));
    EXPECT_EQ(8, mi.GetMultiplier(6));
    EXPECT_EQ(4, mi.GetMultiplier(7));
    EXPECT_EQ(4, mi.GetMultiplier(8));
    EXPECT_EQ(4, mi.GetMultiplier(9));

    EXPECT_EQ(0, mi.GetPreview()[0]);
    EXPECT_EQ(3, mi.GetPreview()[1]);
    EXPECT_EQ(2, mi.GetPreview()[2]);
}

TEST(BackendTest, MultiplierShallGiveCorrectDataAfterReset3)
{
    // Arrange
    Backend::MultiplierInfo mi;
    std::vector<Backend::EventInfo> events
    {
        { Backend::NumberOfEvents(0u), Backend::Players(4u) },
        { Backend::NumberOfEvents(2u), Backend::Players(4u) },
        { Backend::NumberOfEvents(2u), Backend::Players(5u) },
        { Backend::NumberOfEvents(0u), Backend::Players(5u) },
        { Backend::NumberOfEvents(1u), Backend::Players(4u) }
    };

    /* // 4 (.) or 5 (#) players
     *  0 0u, 0
     *  1 2u, 0
     *  2 2u, . .
     *  3 0u, . . #
     *  4 1u  . . #
     *  5     . . #
     *  6         # # .
     *  7         # # .
     *  8           # .
     *  9           # .
     * 10           #
     */

    // Act, Assert
    mi.ResetTo(events);

    EXPECT_EQ(1, mi.GetMultiplier( 0));
    EXPECT_EQ(1, mi.GetMultiplier( 1));
    EXPECT_EQ(4, mi.GetMultiplier( 2));
    EXPECT_EQ(8, mi.GetMultiplier( 3));
    EXPECT_EQ(8, mi.GetMultiplier( 4));
    EXPECT_EQ(8, mi.GetMultiplier( 5));
    EXPECT_EQ(8, mi.GetMultiplier( 6));
    EXPECT_EQ(8, mi.GetMultiplier( 7));
    EXPECT_EQ(4, mi.GetMultiplier( 8));
    EXPECT_EQ(4, mi.GetMultiplier( 9));
    EXPECT_EQ(2, mi.GetMultiplier(10));

    EXPECT_EQ(1, mi.GetPreview()[0]);
    EXPECT_EQ(2, mi.GetPreview()[1]);
    EXPECT_EQ(3, mi.GetPreview()[2]);
}

#endif // TST_MULTIPLIERINFO_H
