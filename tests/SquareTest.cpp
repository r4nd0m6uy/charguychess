/**
 * Charguy chess: A DIY chess hardware
 *
 * Copyright (C) 2017 R4nd0m6uy <r4nd0m6uy@r4nd0m6uy.ch>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <CppUTest/TestHarness.h>

#include "chess/Square.hpp"

using namespace cgc;

//--------------------------------------------------------------------------------------------
TEST_GROUP(SquareTest)
{
  TEST_SETUP()
  {
  }

  TEST_TEARDOWN()
  {
  }
};

//--------------------------------------------------------------------------------------------
TEST(SquareTest, sameRankAndFileEqual)
{
  Square s1(A, ONE);
  Square s2(A, ONE);

  CHECK(s1 == s2);
}

//--------------------------------------------------------------------------------------------
TEST(SquareTest, constructorWithValidString)
{
  Square s("b4");

  CHECK(s.isValid());
  CHECK_EQUAL(B, s.getFile());
  CHECK_EQUAL(FOUR, s.getRank());
}

//--------------------------------------------------------------------------------------------
TEST(SquareTest, constructorWithValidParameters)
{
  Square s(A, ONE);

  CHECK(s.isValid());
}

//--------------------------------------------------------------------------------------------
TEST(SquareTest, defaultConstructor)
{
  Square s;

  CHECK_FALSE(s.isValid());
}
