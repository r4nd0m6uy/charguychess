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
#include <algorithm>

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
TEST(GameLogicTest, legalMoveApplied)
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
TEST(GameLogicTest, illegalMoveNotApplied)
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
TEST(GameLogicTest, blackPawnStartLegalMoves)
{
  std::list<Square> lm;
  GameLogic gl;

  gl.getLegalMoves(Square(E, SEVEN), lm);

  CHECK_EQUAL(2, lm.size());
  CHECK(std::find(lm.begin(), lm.end(), Square(E, SIX)) != lm.end());
  CHECK(std::find(lm.begin(), lm.end(), Square(E, FIVE)) != lm.end());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, whitePawnLegalMovesAFile)
{
  std::list<Square> lm;
  GameLogic gl;

  gl.getLegalMoves(Square(A, TWO), lm);

  CHECK_EQUAL(2, lm.size());
  CHECK(std::find(lm.begin(), lm.end(), Square(A, THREE)) != lm.end());
  CHECK(std::find(lm.begin(), lm.end(), Square(A, FOUR)) != lm.end());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, whitePawnLegalMovesHFile)
{
  std::list<Square> lm;
  GameLogic gl;

  gl.getLegalMoves(Square(H, TWO), lm);

  CHECK_EQUAL(2, lm.size());
  CHECK(std::find(lm.begin(), lm.end(), Square(H, THREE)) != lm.end());
  CHECK(std::find(lm.begin(), lm.end(), Square(H, FOUR)) != lm.end());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, whitePawnLegalMovesRightLeftCapture)
{
  std::list<Square> lm;
  Board b;
  GameLogic gl;

  b.setPiece(PlayerPiece(BLACK, PAWN), Square(F, THREE));
  b.setPiece(PlayerPiece(BLACK, PAWN), Square(D, THREE));
  gl.setBoard(b);
  gl.getLegalMoves(Square(E, TWO), lm);

  CHECK_EQUAL(4, lm.size());
  CHECK(std::find(lm.begin(), lm.end(), Square(E, THREE)) != lm.end());
  CHECK(std::find(lm.begin(), lm.end(), Square(E, FOUR)) != lm.end());
  CHECK(std::find(lm.begin(), lm.end(), Square(F, THREE)) != lm.end());
  CHECK(std::find(lm.begin(), lm.end(), Square(D, THREE)) != lm.end());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, whitePawnLegalMovesRightCapture)
{
  std::list<Square> lm;
  Board b;
  GameLogic gl;

  b.setPiece(PlayerPiece(BLACK, PAWN), Square(F, THREE));
  gl.setBoard(b);
  gl.getLegalMoves(Square(E, TWO), lm);

  CHECK_EQUAL(3, lm.size());
  CHECK(std::find(lm.begin(), lm.end(), Square(E, THREE)) != lm.end());
  CHECK(std::find(lm.begin(), lm.end(), Square(E, FOUR)) != lm.end());
  CHECK(std::find(lm.begin(), lm.end(), Square(F, THREE)) != lm.end());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, whitePawnLegalMoves)
{
  std::list<Square> lm;
  Board b;
  GameLogic gl;

  b.setPiece(PlayerPiece(WHITE, PAWN), Square(E, FOUR));
  gl.setBoard(b);

  gl.getLegalMoves(Square(E, FOUR), lm);

  CHECK_EQUAL(1, lm.size());
  CHECK(std::find(lm.begin(), lm.end(), Square(E, FIVE)) != lm.end());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, whitePawnStartLegalMovesWithPieceInTwoFront)
{
  std::list<Square> lm;
  Board b;
  GameLogic gl;

  b.setPiece(PlayerPiece(WHITE, PAWN), Square(E, FOUR));
  gl.setBoard(b);

  gl.getLegalMoves(Square(E, TWO), lm);

  CHECK_EQUAL(1, lm.size());
  CHECK(std::find(lm.begin(), lm.end(), Square(E, THREE)) != lm.end());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, whitePawnStartLegalMovesWithPieceInFront)
{
  std::list<Square> lm;
  Board b;
  GameLogic gl;

  b.setPiece(PlayerPiece(WHITE, PAWN), Square(E, THREE));
  gl.setBoard(b);

  gl.getLegalMoves(Square(E, TWO), lm);

  CHECK_EQUAL(0, lm.size());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, whitePawnStartLegalMoves)
{
  std::list<Square> lm;
  GameLogic gl;

  gl.getLegalMoves(Square(E, TWO), lm);

  CHECK_EQUAL(2, lm.size());
  CHECK(std::find(lm.begin(), lm.end(), Square(E, THREE)) != lm.end());
  CHECK(std::find(lm.begin(), lm.end(), Square(E, FOUR)) != lm.end());
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
