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

#include "chess/GameLogic.hpp"
#include "chess/Move.hpp"

using namespace cgc;

//--------------------------------------------------------------------------------------------
TEST_GROUP(GameLogicTest)
{
  TEST_SETUP()
  {
  }

  TEST_TEARDOWN()
  {
  }
};

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, blackPawnMovesBackward)
{
  GameLogic gl;
  Square from(A, FIVE);
  Square to(A, SIX);
  Board b;
  Move m(from, to);

  b.setPiece(PlayerPiece(BLACK, PAWN), from);
  gl.setBoard(b);
  gl.setTurn(BLACK);

  CHECK_FALSE(gl.applyMove(m));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, whitePawnMovesBackward)
{
  GameLogic gl;
  Square from(A, FOUR);
  Square to(A, THREE);
  Board b;
  Move m(from, to);

  b.setPiece(PlayerPiece(WHITE, PAWN), from);
  gl.setBoard(b);

  CHECK_FALSE(gl.applyMove(m));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, pawnCapturesEmptySquare)
{
  GameLogic gl;
  Square from(E, TWO);
  Square to(F, THREE);
  Move m(from, to);

  CHECK_FALSE(gl.applyMove(m));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, pawnCapturesLeftTooFarLeft)
{
  GameLogic gl;
  Square from(E, TWO);
  Square to(G, THREE);
  Board b;
  Move m(from, to);

  b.setPiece(PlayerPiece(BLACK, PAWN), to);
  gl.setBoard(b);

  CHECK_FALSE(gl.applyMove(m));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, pawnCapturesLeftTooFarForward)
{
  GameLogic gl;
  Square from(E, TWO);
  Square to(F, FOUR);
  Board b;
  Move m(from, to);

  b.setPiece(PlayerPiece(BLACK, PAWN), to);
  gl.setBoard(b);

  CHECK_FALSE(gl.applyMove(m));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, pawnCapturesLeft)
{
  GameLogic gl;
  Square from(E, TWO);
  Square to(F, THREE);
  Board b;
  Move m(from, to);

  b.setPiece(PlayerPiece(BLACK, PAWN), to);
  gl.setBoard(b);

  CHECK(gl.applyMove(m));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, blackPawnMovesTwoForward)
{
  GameLogic gl;
  Square from(A, SEVEN);
  Square to(A, FIVE);
  Board b;
  Move m(from, to);

  gl.setTurn(BLACK);

  CHECK(gl.applyMove(m));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, blackPawnMovesForward)
{
  GameLogic gl;
  Square from(A, SEVEN);
  Square to(A, SIX);
  Board b;
  Move m(from, to);

  gl.setTurn(BLACK);

  CHECK(gl.applyMove(m));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, pawnMovesForwardButPiecePresent)
{
  GameLogic gl;
  Square from(A, TWO);
  Square to(A, THREE);
  Board b;
  Move m(from, to);

  b.setPiece(PlayerPiece(WHITE, PAWN), to);
  gl.setBoard(b);

  CHECK_FALSE(gl.applyMove(m));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, pawnMovesTwoForwardButAlreadyMoved)
{
  GameLogic gl;
  Square from(A, THREE);
  Square to(A, FIVE);
  Board b;
  Move m(from, to);

  b.setPiece(PlayerPiece(), Square(A, TWO));
  b.setPiece(PlayerPiece(WHITE, PAWN), from);
  gl.setBoard(b);

  CHECK_FALSE(gl.applyMove(m));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, pawnMovesThreeForward)
{
  GameLogic gl;
  Square from(A, TWO);
  Square to(A, FIVE);
  Move m(from, to);

  CHECK_FALSE(gl.applyMove(m));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, pawnMovesTwoForward)
{
  GameLogic gl;
  Square from(A, TWO);
  Square to(A, FOUR);
  Move m(from, to);

  CHECK(gl.applyMove(m));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, illegalMoveWrongFromColor)
{
  GameLogic gl;
  Square from(A, SEVEN);
  Square to(A, SIX);
  Move m(from, to);

  CHECK_FALSE(gl.applyMove(m));

  // Board doesn't change on illegal move
  const PlayerPiece& pieceFrom = gl.getBoard().getPiece(from);
  CHECK_EQUAL(BLACK, pieceFrom.getColor());
  CHECK_EQUAL(PAWN, pieceFrom.getPiece());

  const PlayerPiece& pieceTo = gl.getBoard().getPiece(to);
  CHECK_EQUAL(NO_COLOR, pieceTo.getColor());
  CHECK_EQUAL(NO_PIECE, pieceTo.getPiece());

  CHECK_EQUAL(WHITE, gl.getTurn());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, pawnMovesOneForward)
{
  GameLogic gl;
  Square from(A, TWO);
  Square to(A, THREE);
  Move m(from, to);

  CHECK(gl.applyMove(m));

  // Board is updated on legal move
  const PlayerPiece& pieceFrom = gl.getBoard().getPiece(from);
  CHECK_EQUAL(NO_COLOR, pieceFrom.getColor());
  CHECK_EQUAL(NO_PIECE, pieceFrom.getPiece());

  const PlayerPiece& pieceTo = gl.getBoard().getPiece(to);
  CHECK_EQUAL(WHITE, pieceTo.getColor());
  CHECK_EQUAL(PAWN, pieceTo.getPiece());

  CHECK_EQUAL(BLACK, gl.getTurn());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, setTurnNoColor)
{
  GameLogic gl;

  gl.setTurn(NO_COLOR);
  CHECK_EQUAL(WHITE, gl.getTurn());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, firstTurnIsWhite)
{
  GameLogic gl;

  CHECK_EQUAL(WHITE, gl.getTurn());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, DefaultConstructor)
{
  GameLogic gl;
}
