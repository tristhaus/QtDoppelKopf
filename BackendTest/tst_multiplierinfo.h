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

#include "../Backend/multiplierinfo.h"
#include <gtest/gtest.h>

TEST(BackendTest, MultiplierShallGiveCorrectDataAfterReset1) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    Backend::MultiplierInfo mi;
    std::vector<Backend::EventInfo> events
    {
        { Backend::NumberOfEvents(0U), Backend::Players(4U), Backend::MandatorySolo(false) },
        { Backend::NumberOfEvents(1U), Backend::Players(4U), Backend::MandatorySolo(false) },
        { Backend::NumberOfEvents(0U), Backend::Players(4U), Backend::MandatorySolo(false) },
        { Backend::NumberOfEvents(0U), Backend::Players(4U), Backend::MandatorySolo(false) },
        { Backend::NumberOfEvents(1U), Backend::Players(4U), Backend::MandatorySolo(false) }
    };

    /* // 4 players throughout
     * 0 0U, 0
     * 1 1U, 0
     * 2 0U, 1
     * 3 0U, 1
     * 4 1U  1
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

    EXPECT_EQ(false, mi.GetIsMandatorySolo(0));
    EXPECT_EQ(false, mi.GetIsMandatorySolo(1));
    EXPECT_EQ(false, mi.GetIsMandatorySolo(2));
    EXPECT_EQ(false, mi.GetIsMandatorySolo(3));
    EXPECT_EQ(false, mi.GetIsMandatorySolo(4));
    EXPECT_EQ(false, mi.GetIsMandatorySolo(5));
    EXPECT_EQ(false, mi.GetIsMandatorySolo(6));
    EXPECT_EQ(false, mi.GetIsMandatorySolo(7));
    EXPECT_EQ(false, mi.GetIsMandatorySolo(8));
}

TEST(BackendTest, MultiplierShallGiveCorrectDataAfterReset2) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    Backend::MultiplierInfo mi;
    std::vector<Backend::EventInfo> events
    {
        { Backend::NumberOfEvents(0U), Backend::Players(4U), Backend::MandatorySolo(false) },
        { Backend::NumberOfEvents(2U), Backend::Players(4U), Backend::MandatorySolo(false) },
        { Backend::NumberOfEvents(2U), Backend::Players(4U), Backend::MandatorySolo(false) },
        { Backend::NumberOfEvents(0U), Backend::Players(4U), Backend::MandatorySolo(false) },
        { Backend::NumberOfEvents(1U), Backend::Players(4U), Backend::MandatorySolo(false) }
    };

    /* // 4 players throughout
     * 0 0U, 0
     * 1 2U, 0
     * 2 2U, 2
     * 3 0U, 2 +1
     * 4 1U  2 +1
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

    EXPECT_EQ(false, mi.GetIsMandatorySolo(0));
    EXPECT_EQ(false, mi.GetIsMandatorySolo(1));
    EXPECT_EQ(false, mi.GetIsMandatorySolo(2));
    EXPECT_EQ(false, mi.GetIsMandatorySolo(3));
    EXPECT_EQ(false, mi.GetIsMandatorySolo(4));
    EXPECT_EQ(false, mi.GetIsMandatorySolo(5));
    EXPECT_EQ(false, mi.GetIsMandatorySolo(6));
    EXPECT_EQ(false, mi.GetIsMandatorySolo(7));
    EXPECT_EQ(false, mi.GetIsMandatorySolo(8));
    EXPECT_EQ(false, mi.GetIsMandatorySolo(9));
}

TEST(BackendTest, MultiplierShallGiveCorrectDataAfterReset3) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    Backend::MultiplierInfo mi;
    std::vector<Backend::EventInfo> events
    {
        { Backend::NumberOfEvents(0U), Backend::Players(4U), Backend::MandatorySolo(false) },
        { Backend::NumberOfEvents(2U), Backend::Players(4U), Backend::MandatorySolo(false) },
        { Backend::NumberOfEvents(2U), Backend::Players(5U), Backend::MandatorySolo(false) },
        { Backend::NumberOfEvents(0U), Backend::Players(5U), Backend::MandatorySolo(false) },
        { Backend::NumberOfEvents(1U), Backend::Players(4U), Backend::MandatorySolo(false) }
    };

    /* // 4 (.) or 5 (#) players
     *  0 0U, 0
     *  1 2U, 0
     *  2 2U, . .
     *  3 0U, . . #
     *  4 1U  . . #
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

    EXPECT_EQ(false, mi.GetIsMandatorySolo( 0));
    EXPECT_EQ(false, mi.GetIsMandatorySolo( 1));
    EXPECT_EQ(false, mi.GetIsMandatorySolo( 2));
    EXPECT_EQ(false, mi.GetIsMandatorySolo( 3));
    EXPECT_EQ(false, mi.GetIsMandatorySolo( 4));
    EXPECT_EQ(false, mi.GetIsMandatorySolo( 5));
    EXPECT_EQ(false, mi.GetIsMandatorySolo( 6));
    EXPECT_EQ(false, mi.GetIsMandatorySolo( 7));
    EXPECT_EQ(false, mi.GetIsMandatorySolo( 8));
    EXPECT_EQ(false, mi.GetIsMandatorySolo( 9));
    EXPECT_EQ(false, mi.GetIsMandatorySolo(10));
}

TEST(BackendTest, MultiplierShallGiveCorrectDataAfterResetWithMandatorySolo) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    Backend::MultiplierInfo mi;
    std::vector<Backend::EventInfo> events
    {
        { Backend::NumberOfEvents(0U), Backend::Players(4U), Backend::MandatorySolo(false) },
        { Backend::NumberOfEvents(2U), Backend::Players(4U), Backend::MandatorySolo(false) },
        { Backend::NumberOfEvents(2U), Backend::Players(4U), Backend::MandatorySolo(true) },

        { Backend::NumberOfEvents(0U), Backend::Players(4U), Backend::MandatorySolo(false) },
        { Backend::NumberOfEvents(0U), Backend::Players(4U), Backend::MandatorySolo(false) },
        { Backend::NumberOfEvents(0U), Backend::Players(4U), Backend::MandatorySolo(false) },
        { Backend::NumberOfEvents(0U), Backend::Players(4U), Backend::MandatorySolo(false) },

        { Backend::NumberOfEvents(0U), Backend::Players(4U), Backend::MandatorySolo(false) },
        { Backend::NumberOfEvents(1U), Backend::Players(4U), Backend::MandatorySolo(false) }
    };

    /* // 4 players throughout
     *  0 0U, 0
     *  1 2U, 0
     *  2 2U, 2 - trigger mandatory solo
     *  3 m
     *  4 m
     *  5 m
     *  6 m
     *  7 0U, 2 +1
     *  8 1U  2 +1
     *  9     2 +1
     * 10       +1 +1 +1
     * 11          +1 +1
     * 12          +1 +1
     * 13          +1 +1
     */

    // Act, Assert
    mi.ResetTo(events);

    EXPECT_EQ(1, mi.GetMultiplier(0));
    EXPECT_EQ(1, mi.GetMultiplier(1));
    EXPECT_EQ(4, mi.GetMultiplier(2));

    EXPECT_EQ(1, mi.GetMultiplier(3));
    EXPECT_EQ(1, mi.GetMultiplier(4));
    EXPECT_EQ(1, mi.GetMultiplier(5));
    EXPECT_EQ(1, mi.GetMultiplier(6));

    EXPECT_EQ(8, mi.GetMultiplier( 7));
    EXPECT_EQ(8, mi.GetMultiplier( 8));
    EXPECT_EQ(8, mi.GetMultiplier( 9));
    EXPECT_EQ(8, mi.GetMultiplier(10));
    EXPECT_EQ(4, mi.GetMultiplier(11));
    EXPECT_EQ(4, mi.GetMultiplier(12));
    EXPECT_EQ(4, mi.GetMultiplier(13));

    EXPECT_EQ(0, mi.GetPreview()[0]);
    EXPECT_EQ(3, mi.GetPreview()[1]);
    EXPECT_EQ(2, mi.GetPreview()[2]);

    EXPECT_EQ(false, mi.GetIsMandatorySolo( 0));
    EXPECT_EQ(false, mi.GetIsMandatorySolo( 1));
    EXPECT_EQ(false, mi.GetIsMandatorySolo( 2));

    EXPECT_EQ(true, mi.GetIsMandatorySolo( 3));
    EXPECT_EQ(true, mi.GetIsMandatorySolo( 4));
    EXPECT_EQ(true, mi.GetIsMandatorySolo( 5));
    EXPECT_EQ(true, mi.GetIsMandatorySolo( 6));

    EXPECT_EQ(false, mi.GetIsMandatorySolo( 7));
    EXPECT_EQ(false, mi.GetIsMandatorySolo( 8));
    EXPECT_EQ(false, mi.GetIsMandatorySolo( 9));
    EXPECT_EQ(false, mi.GetIsMandatorySolo(10));
    EXPECT_EQ(false, mi.GetIsMandatorySolo(11));
    EXPECT_EQ(false, mi.GetIsMandatorySolo(12));
    EXPECT_EQ(false, mi.GetIsMandatorySolo(13));
}

#endif // TST_MULTIPLIERINFO_H
