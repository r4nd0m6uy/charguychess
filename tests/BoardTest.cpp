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
TEST(BoardTest, isEmptySquare)
{
  Board b;

  CHECK(b.isEmpty(Square(A, THREE)));
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, setPiece)
{
  Board b;
  PlayerPiece p(BLACK, BISHOP);
  Square s(G, FOUR);

  b.setPiece(p, s);
  const PlayerPiece& newPiece = b.getPiece(s);
  CHECK_EQUAL(BLACK, newPiece.getColor());
  CHECK_EQUAL(BISHOP, newPiece.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, blackRookOnH8)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(H, EIGHT));

  CHECK_EQUAL(BLACK, pp.getColor());
  CHECK_EQUAL(ROOK, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, blackKnightOnG8)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(G, EIGHT));

  CHECK_EQUAL(BLACK, pp.getColor());
  CHECK_EQUAL(KNIGHT, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, blackBishopOnF8)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(F, EIGHT));

  CHECK_EQUAL(BLACK, pp.getColor());
  CHECK_EQUAL(BISHOP, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, blackKingOnE8)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(E, EIGHT));

  CHECK_EQUAL(BLACK, pp.getColor());
  CHECK_EQUAL(KING, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, blackQueenOnD8)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(D, EIGHT));

  CHECK_EQUAL(BLACK, pp.getColor());
  CHECK_EQUAL(QUEEN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, blackBishopOnC8)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(C, EIGHT));

  CHECK_EQUAL(BLACK, pp.getColor());
  CHECK_EQUAL(BISHOP, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, blackKnightOnB8)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(B, EIGHT));

  CHECK_EQUAL(BLACK, pp.getColor());
  CHECK_EQUAL(KNIGHT, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, blackRookOnA8)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(A, EIGHT));

  CHECK_EQUAL(BLACK, pp.getColor());
  CHECK_EQUAL(ROOK, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, blackPawnOnH7)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(H, SEVEN));

  CHECK_EQUAL(BLACK, pp.getColor());
  CHECK_EQUAL(PAWN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, blackPawnOnG7)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(G, SEVEN));

  CHECK_EQUAL(BLACK, pp.getColor());
  CHECK_EQUAL(PAWN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, blackPawnOnF7)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(F, SEVEN));

  CHECK_EQUAL(BLACK, pp.getColor());
  CHECK_EQUAL(PAWN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, blackPawnOnE7)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(E, SEVEN));

  CHECK_EQUAL(BLACK, pp.getColor());
  CHECK_EQUAL(PAWN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, blackPawnOnD7)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(D, SEVEN));

  CHECK_EQUAL(BLACK, pp.getColor());
  CHECK_EQUAL(PAWN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, blackPawnOnC7)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(C, SEVEN));

  CHECK_EQUAL(BLACK, pp.getColor());
  CHECK_EQUAL(PAWN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, blackPawnOnB7)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(B, SEVEN));

  CHECK_EQUAL(BLACK, pp.getColor());
  CHECK_EQUAL(PAWN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, blackPawnOnA7)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(A, SEVEN));

  CHECK_EQUAL(BLACK, pp.getColor());
  CHECK_EQUAL(PAWN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whitePawnOnH2)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(H, TWO));

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(PAWN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whitePawnOnG2)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(G, TWO));

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(PAWN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whitePawnOnF2)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(F, TWO));

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(PAWN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whitePawnOnE2)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(E, TWO));

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(PAWN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whitePawnOnD2)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(D, TWO));

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(PAWN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whitePawnOnC2)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(C, TWO));

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(PAWN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whitePawnOnB2)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(B, TWO));

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(PAWN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whitePawnOnA2)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(A, TWO));

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(PAWN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whiteRookOnH1)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(H, ONE));

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(ROOK, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whiteKnightOnG1)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(G, ONE));

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(KNIGHT, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whiteBishopOnF1)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(F, ONE));

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(BISHOP, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whiteKingOnE1)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(E, ONE));

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(KING, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whiteQueenOnD1)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(D, ONE));

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(QUEEN, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whiteBishopOnC1)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(C, ONE));

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(BISHOP, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whiteKnightOnB1)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(B, ONE));

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(KNIGHT, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, whiteRookOnA1)
{
  Board b;
  const PlayerPiece& pp = b.getPiece(Square(A, ONE));

  CHECK_EQUAL(WHITE, pp.getColor());
  CHECK_EQUAL(ROOK, pp.getPiece());
}

//--------------------------------------------------------------------------------------------
TEST(BoardTest, DefaultConstructor)
{
  Board b;
}
