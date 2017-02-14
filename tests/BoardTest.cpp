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

#include "chess/Board.hpp"

using namespace cgc;

//--------------------------------------------------------------------------------------------
TEST_GROUP(BoardTest)
{
  TEST_SETUP()
  {
  }

  TEST_TEARDOWN()
  {
  }
};

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whitePawnOnH2)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(H, TWO);

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(PAWN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whitePawnOnG2)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(G, TWO);

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(PAWN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whitePawnOnF2)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(F, TWO);

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(PAWN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whitePawnOnE2)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(E, TWO);

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(PAWN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whitePawnOnD2)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(D, TWO);

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(PAWN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whitePawnOnC2)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(C, TWO);

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(PAWN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whitePawnOnB2)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(B, TWO);

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(PAWN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whitePawnOnA2)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(A, TWO);

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(PAWN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whiteRookOnH1)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(H, ONE);

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(ROOK, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whiteKnightOnG1)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(G, ONE);

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(KNIGHT, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whiteBishopOnF1)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(F, ONE);

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(BISHOP, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whiteKingOnE1)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(E, ONE);

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(KING, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whiteQueenOnD1)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(D, ONE);

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(QUEEN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whiteBishopOnC1)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(C, ONE);

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(BISHOP, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whiteKnightOnB1)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(B, ONE);

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(KNIGHT, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whiteRookOnA1)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(A, ONE);

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(ROOK, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, DefaultConstructor)
{
  Board b;
}
