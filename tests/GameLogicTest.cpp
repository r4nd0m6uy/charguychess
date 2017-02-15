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
#include <CppUTestExt/MockSupport.h>

#include "mocks/IBoardObserverMock.hpp"
#include "chess/GameLogic.hpp"
#include "chess/Move.hpp"

using namespace cgc;
using namespace tests;

//--------------------------------------------------------------------------------------------
TEST_GROUP(GameLogicTest)
{
  TEST_SETUP()
  {
  }

  TEST_TEARDOWN()
  {
    mock().clear();
  }
};

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, blackCapturedPiecesClearedAfterNew)
{
  Square to(D, THREE);
  Move m(Square(E, TWO), to);
  Board b;
  GameLogic gl;

  b.setPiece(PlayerPiece(BLACK, QUEEN), to);
  gl.setBoard(b);

  CHECK(gl.applyMove(m));
  gl.newGame();
  CHECK_EQUAL(0, gl.getCapturedBlackPieces().size());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, whiteCapturedPiecesClearedAfterNew)
{
  Square to(D, SIX);
  Move m(Square(C, SEVEN), to);
  Board b;
  GameLogic gl;

  b.setPiece(PlayerPiece(WHITE, KNIGHT), to);
  gl.setBoard(b);
  gl.setTurn(BLACK);

  CHECK(gl.applyMove(m));
  gl.newGame();
  CHECK_EQUAL(0, gl.getCapturedWhitePieces().size());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, getCaputredBlackPawnTakesQueen)
{
  Square to(D, SIX);
  Move m(Square(C, SEVEN), to);
  Board b;
  GameLogic gl;

  b.setPiece(PlayerPiece(WHITE, KNIGHT), to);
  gl.setBoard(b);
  gl.setTurn(BLACK);

  CHECK(gl.applyMove(m));
  CHECK_EQUAL(1, gl.getCapturedWhitePieces().size());
  CHECK_EQUAL(KNIGHT,  gl.getCapturedWhitePieces().front().getType());
  CHECK_EQUAL(0, gl.getCapturedBlackPieces().size());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, getCaputredWhitePawnTakesQueen)
{
  Square to(D, THREE);
  Move m(Square(E, TWO), to);
  Board b;
  GameLogic gl;

  b.setPiece(PlayerPiece(BLACK, QUEEN), to);
  gl.setBoard(b);

  CHECK(gl.applyMove(m));
  CHECK_EQUAL(0, gl.getCapturedWhitePieces().size());
  CHECK_EQUAL(1, gl.getCapturedBlackPieces().size());
  CHECK_EQUAL(QUEEN,  gl.getCapturedBlackPieces().front().getType());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, getCaputredPiecesNoPiecesTaken)
{
  GameLogic gl;

  CHECK_EQUAL(0, gl.getCapturedWhitePieces().size());
  CHECK_EQUAL(0, gl.getCapturedBlackPieces().size());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, newGameRaiseObserverEvent)
{
  GameLogic gl;
  IBoardObserverMock observer;

  gl.registerBoardObserver(observer);

  mock().expectOneCall("boardChanged").onObject(&observer).
      withParameter("playerTurn", WHITE).
      withParameter("newStatus", &gl.getBoard());

  gl.newGame();

  mock().checkExpectations();
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, newGame)
{
  std::list<Square> lm;
  Square from(E, TWO);
  Square to(E, FOUR);
  Move m(from, to);
  GameLogic gl;

  gl.applyMove(m);
  gl.newGame();

  CHECK_EQUAL(WHITE, gl.getTurn());
  CHECK(gl.getBoard().isEmpty(to));
  CHECK(!gl.getBoard().isEmpty(from));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, legalMoveObserverCallback)
{
  GameLogic gl;
  Square from(A, TWO);
  Square to(A, THREE);
  Move m(from, to);
  IBoardObserverMock observer;

  gl.registerBoardObserver(observer);

  mock().expectOneCall("boardChanged").onObject(&observer).
      withParameter("playerTurn", BLACK).
      withParameter("newStatus", &gl.getBoard());

  CHECK(gl.applyMove(m));

  mock().checkExpectations();
}

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
  CHECK_EQUAL(NO_PIECE, pieceFrom.getType());

  const PlayerPiece& pieceTo = gl.getBoard().getPiece(to);
  CHECK_EQUAL(WHITE, pieceTo.getColor());
  CHECK_EQUAL(PAWN, pieceTo.getType());

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
  CHECK_EQUAL(PAWN, pieceFrom.getType());

  const PlayerPiece& pieceTo = gl.getBoard().getPiece(to);
  CHECK_EQUAL(NO_COLOR, pieceTo.getColor());
  CHECK_EQUAL(NO_PIECE, pieceTo.getType());

  CHECK_EQUAL(WHITE, gl.getTurn());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, legalMovesCleared)
{
  LegalSquares ls(Square(E, SEVEN));
  GameLogic gl;

  gl.setTurn(BLACK);
  ls.addLegalSquare(Square(G, TWO));

  gl.getLegalSquares(ls);

  CHECK_EQUAL(2, ls.getLegalSquaresCount());
  CHECK(ls.contains(Square(E, SIX)));
  CHECK(ls.contains(Square(E, FIVE)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, blackPawnStartLegalMoves)
{
  LegalSquares ls(Square(E, SEVEN));
  GameLogic gl;

  gl.setTurn(BLACK);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(2, ls.getLegalSquaresCount());
  CHECK(ls.contains(Square(E, SIX)));
  CHECK(ls.contains(Square(E, FIVE)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, noLegalMoveOnWrongPlayer)
{
  LegalSquares ls(Square(E, SEVEN));
  GameLogic gl;

  gl.getLegalSquares(ls);

  CHECK_EQUAL(0, ls.getLegalSquaresCount());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, whitePawnLegalMovesAFile)
{
  LegalSquares ls(Square(A, TWO));
  GameLogic gl;

  gl.getLegalSquares(ls);

  CHECK_EQUAL(2, ls.getLegalSquaresCount());
  CHECK(ls.contains(Square(A, THREE)));
  CHECK(ls.contains(Square(A, FOUR)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, whitePawnLegalMovesHFile)
{
  LegalSquares ls(Square(H, TWO));
  GameLogic gl;

  gl.getLegalSquares(ls);

  CHECK_EQUAL(2, ls.getLegalSquaresCount());
  CHECK(ls.contains(Square(H, THREE)));
  CHECK(ls.contains(Square(H, FOUR)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, whitePawnLegalMovesRightLeftCapture)
{
  LegalSquares ls(Square(E, TWO));
  Board b;
  GameLogic gl;

  b.setPiece(PlayerPiece(BLACK, PAWN), Square(F, THREE));
  b.setPiece(PlayerPiece(BLACK, PAWN), Square(D, THREE));
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(4, ls.getLegalSquaresCount());
  CHECK(ls.contains(Square(E, THREE)));
  CHECK(ls.contains(Square(E, FOUR)));
  CHECK(ls.contains(Square(F, THREE)));
  CHECK(ls.contains(Square(D, THREE)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, whitePawnLegalMoves)
{
  LegalSquares ls(Square(E, FOUR));
  Board b;
  GameLogic gl;

  b.setPiece(PlayerPiece(WHITE, PAWN), Square(E, FOUR));
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(1, ls.getLegalSquaresCount());
  CHECK(ls.contains(Square(E, FIVE)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, whitePawnStartLegalMovesWithPieceInTwoFront)
{
  LegalSquares ls(Square(E, FOUR));
  Board b;
  GameLogic gl;

  b.setPiece(PlayerPiece(WHITE, PAWN), Square(E, FOUR));
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(1, ls.getLegalSquaresCount());
  CHECK(ls.contains(Square(E, FIVE)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, whitePawnStartLegalMovesWithPieceInFront)
{
  LegalSquares ls(Square(E, TWO));
  Board b;
  GameLogic gl;

  b.setPiece(PlayerPiece(WHITE, PAWN), Square(E, THREE));
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(0, ls.getLegalSquaresCount());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, whitePawnStartLegalMoves)
{
  LegalSquares ls(Square(E, TWO));
  GameLogic gl;

  gl.getLegalSquares(ls);

  CHECK_EQUAL(2, ls.getLegalSquaresCount());
  CHECK(ls.contains(Square(E, THREE)));
  CHECK(ls.contains(Square(E, FOUR)));
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
