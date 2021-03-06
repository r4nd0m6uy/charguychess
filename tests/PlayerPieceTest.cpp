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

#include "chess/PlayerPiece.hpp"

using namespace cgc;

//--------------------------------------------------------------------------------------------
TEST_GROUP(PlayerPieceTest)
{
  TEST_SETUP()
  {
  }

  TEST_TEARDOWN()
  {
  }
};

//--------------------------------------------------------------------------------------------
TEST(PlayerPieceTest, twoSamePiecesAreEqual)
{
  Color c = WHITE;
  PieceType p = BISHOP;
  PlayerPiece pp1(c, p);
  PlayerPiece pp2(c, p);

  CHECK(pp1 == pp2);
}

//--------------------------------------------------------------------------------------------
TEST(PlayerPieceTest, ConstructorWithArgs)
{
  Color c = WHITE;
  PieceType p = BISHOP;
  PlayerPiece pp(c, p);

  CHECK_EQUAL(c, pp.getColor());
  CHECK_EQUAL(p, pp.getType());
}

//--------------------------------------------------------------------------------------------
TEST(PlayerPieceTest, DefaultConstructor)
{
  PlayerPiece pp;

  CHECK_EQUAL(NO_COLOR, pp.getColor());
  CHECK_EQUAL(NO_PIECE, pp.getType());
}
