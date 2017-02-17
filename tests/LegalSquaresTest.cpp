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

#include "chess/LegalSquares.hpp"

#include <CppUTest/TestHarness.h>


using namespace cgc;

//--------------------------------------------------------------------------------------------
TEST_GROUP(LegalMovesTest)
{
  TEST_SETUP()
  {
  }

  TEST_TEARDOWN()
  {
  }
};

//--------------------------------------------------------------------------------------------
TEST(LegalMovesTest, doesntContainAfterClear)
{
  LegalSquares lm(Square(A, ONE));
  Square ls(A, TWO);

  lm.add(ls);
  lm.clear();
  CHECK_FALSE(lm.contains(ls));
}

//--------------------------------------------------------------------------------------------
TEST(LegalMovesTest, containsAfterAdd)
{
  LegalSquares lm(Square(A, ONE));
  Square ls(A, TWO);

  lm.add(ls);
  CHECK(lm.contains(ls));
}

//--------------------------------------------------------------------------------------------
TEST(LegalMovesTest, defaultConstructor)
{
  Square from(A, ONE);
  LegalSquares lm(from);

  CHECK(from == lm.getFrom());
}
