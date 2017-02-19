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

#include "chess/SquaresList.hpp"

#include <CppUTest/TestHarness.h>


using namespace cgc;

//--------------------------------------------------------------------------------------------
TEST_GROUP(SquaresListTest)
{
  TEST_SETUP()
  {
  }

  TEST_TEARDOWN()
  {
  }
};

//--------------------------------------------------------------------------------------------
TEST(SquaresListTest, addTwiceTheSame)
{
  SquaresList sl;
  Square s(A, TWO);

  sl.add(s);
  sl.add(s);

  CHECK_EQUAL(1, sl.count());
  CHECK(sl.contains(s));
}

//--------------------------------------------------------------------------------------------
TEST(SquaresListTest, append)
{
  SquaresList sl1;
  SquaresList sl2;
  Square s1(A, ONE);
  Square s2(A, TWO);

  sl1.add(s1);
  sl2.add(s2);
  sl1.append(sl2);

  CHECK_EQUAL(2, sl1.count());
  CHECK(sl1.contains(s1));
  CHECK(sl1.contains(s2));
}

//--------------------------------------------------------------------------------------------
TEST(SquaresListTest, doesntContainAfterClear)
{
  SquaresList sl;
  Square s(A, TWO);

  sl.add(s);
  sl.clear();

  CHECK_EQUAL(0, sl.count());
  CHECK_FALSE(sl.contains(s));
}

//--------------------------------------------------------------------------------------------
TEST(SquaresListTest, containsAfterAdd)
{
  SquaresList sl;
  Square s(A, TWO);

  sl.add(s);

  CHECK_EQUAL(1, sl.count());
  CHECK(sl.contains(s));
}

//--------------------------------------------------------------------------------------------
TEST(SquaresListTest, defaultConstructor)
{
  SquaresList sl;

  CHECK_EQUAL(0, sl.count());
}
