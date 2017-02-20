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
IGNORE_TEST(GameLogicTest, getControlledSquareStartPos)
{
  Board b;
  GameLogic gl;
  SquaresList ctrlBlack;
  SquaresList ctrlWhite;

  gl.setBoard(b);

  gl.getControlledSquares(WHITE, ctrlWhite);
  gl.getControlledSquares(BLACK, ctrlBlack);

  CHECK_EQUAL(8, ctrlWhite.count());
  CHECK(ctrlWhite.contains(Square(A, THREE)));
  CHECK(ctrlWhite.contains(Square(B, THREE)));
  CHECK(ctrlWhite.contains(Square(C, THREE)));
  CHECK(ctrlWhite.contains(Square(D, THREE)));
  CHECK(ctrlWhite.contains(Square(E, THREE)));
  CHECK(ctrlWhite.contains(Square(F, THREE)));
  CHECK(ctrlWhite.contains(Square(G, THREE)));
  CHECK(ctrlWhite.contains(Square(H, THREE)));

  CHECK_EQUAL(8, ctrlBlack.count());
  CHECK(ctrlBlack.contains(Square(A, SIX)));
  CHECK(ctrlBlack.contains(Square(B, SIX)));
  CHECK(ctrlBlack.contains(Square(C, SIX)));
  CHECK(ctrlBlack.contains(Square(D, SIX)));
  CHECK(ctrlBlack.contains(Square(E, SIX)));
  CHECK(ctrlBlack.contains(Square(F, SIX)));
  CHECK(ctrlBlack.contains(Square(G, SIX)));
  CHECK(ctrlBlack.contains(Square(H, SIX)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, queenOnE4ControlledSquares)
{
  Square from(E, FOUR);
  Board b;
  LegalSquares ls(from);
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, QUEEN), from);
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(27, ls.count());
  CHECK(ls.contains(Square(A, FOUR)));
  CHECK(ls.contains(Square(B, FOUR)));
  CHECK(ls.contains(Square(C, FOUR)));
  CHECK(ls.contains(Square(D, FOUR)));
  CHECK(ls.contains(Square(F, FOUR)));
  CHECK(ls.contains(Square(G, FOUR)));
  CHECK(ls.contains(Square(H, FOUR)));
  CHECK(ls.contains(Square(E, ONE)));
  CHECK(ls.contains(Square(E, TWO)));
  CHECK(ls.contains(Square(E, THREE)));
  CHECK(ls.contains(Square(E, FIVE)));
  CHECK(ls.contains(Square(E, SIX)));
  CHECK(ls.contains(Square(E, SEVEN)));
  CHECK(ls.contains(Square(E, EIGHT)));
  CHECK(ls.contains(Square(A, EIGHT)));
  CHECK(ls.contains(Square(B, SEVEN)));
  CHECK(ls.contains(Square(C, SIX)));
  CHECK(ls.contains(Square(D, FIVE)));
  CHECK(ls.contains(Square(F, THREE)));
  CHECK(ls.contains(Square(G, TWO)));
  CHECK(ls.contains(Square(H, ONE)));
  CHECK(ls.contains(Square(B, ONE)));
  CHECK(ls.contains(Square(C, TWO)));
  CHECK(ls.contains(Square(D, THREE)));
  CHECK(ls.contains(Square(F, FIVE)));
  CHECK(ls.contains(Square(G, SIX)));
  CHECK(ls.contains(Square(H, SEVEN)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, queenOnE4LegalSquares)
{
  Square from(E, FOUR);
  Board b;
  SquaresList whiteSquares;
  SquaresList blackSquares;
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, QUEEN), from);
  gl.setBoard(b);

  gl.getControlledSquares(WHITE, whiteSquares);
  gl.getControlledSquares(BLACK, blackSquares);

  CHECK_EQUAL(27, whiteSquares.count());
  CHECK(whiteSquares.contains(Square(A, FOUR)));
  CHECK(whiteSquares.contains(Square(B, FOUR)));
  CHECK(whiteSquares.contains(Square(C, FOUR)));
  CHECK(whiteSquares.contains(Square(D, FOUR)));
  CHECK(whiteSquares.contains(Square(F, FOUR)));
  CHECK(whiteSquares.contains(Square(G, FOUR)));
  CHECK(whiteSquares.contains(Square(H, FOUR)));
  CHECK(whiteSquares.contains(Square(E, ONE)));
  CHECK(whiteSquares.contains(Square(E, TWO)));
  CHECK(whiteSquares.contains(Square(E, THREE)));
  CHECK(whiteSquares.contains(Square(E, FIVE)));
  CHECK(whiteSquares.contains(Square(E, SIX)));
  CHECK(whiteSquares.contains(Square(E, SEVEN)));
  CHECK(whiteSquares.contains(Square(E, EIGHT)));
  CHECK(whiteSquares.contains(Square(A, EIGHT)));
  CHECK(whiteSquares.contains(Square(B, SEVEN)));
  CHECK(whiteSquares.contains(Square(C, SIX)));
  CHECK(whiteSquares.contains(Square(D, FIVE)));
  CHECK(whiteSquares.contains(Square(F, THREE)));
  CHECK(whiteSquares.contains(Square(G, TWO)));
  CHECK(whiteSquares.contains(Square(H, ONE)));
  CHECK(whiteSquares.contains(Square(B, ONE)));
  CHECK(whiteSquares.contains(Square(C, TWO)));
  CHECK(whiteSquares.contains(Square(D, THREE)));
  CHECK(whiteSquares.contains(Square(F, FIVE)));
  CHECK(whiteSquares.contains(Square(G, SIX)));
  CHECK(whiteSquares.contains(Square(H, SEVEN)));
  CHECK_EQUAL(0, blackSquares.count());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, controlledSquareWROnA1)
{
  Board b;
  SquaresList whiteSquares;
  SquaresList blackSquares;
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, ROOK), Square(A, ONE));
  gl.setBoard(b);

  gl.getControlledSquares(WHITE, whiteSquares);
  gl.getControlledSquares(BLACK, blackSquares);

  CHECK_EQUAL(14, whiteSquares.count());
  CHECK(whiteSquares.contains(Square(A, TWO)));
  CHECK(whiteSquares.contains(Square(A, THREE)));
  CHECK(whiteSquares.contains(Square(A, FOUR)));
  CHECK(whiteSquares.contains(Square(A, FIVE)));
  CHECK(whiteSquares.contains(Square(A, SIX)));
  CHECK(whiteSquares.contains(Square(A, SEVEN)));
  CHECK(whiteSquares.contains(Square(A, EIGHT)));
  CHECK(whiteSquares.contains(Square(B, ONE)));
  CHECK(whiteSquares.contains(Square(C, ONE)));
  CHECK(whiteSquares.contains(Square(D, ONE)));
  CHECK(whiteSquares.contains(Square(E, ONE)));
  CHECK(whiteSquares.contains(Square(F, ONE)));
  CHECK(whiteSquares.contains(Square(G, ONE)));
  CHECK(whiteSquares.contains(Square(H, ONE)));
  CHECK_EQUAL(0, blackSquares.count());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, rookOnE4BlackWhiteOnG4LegalSquares)
{
  Square from(E, FOUR);
  Board b;
  LegalSquares ls(from);
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, ROOK), from);
  b.setPiece(PlayerPiece(WHITE, PAWN), Square(G, FOUR));
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(12, ls.count());
  CHECK(ls.contains(Square(A, FOUR)));
  CHECK(ls.contains(Square(B, FOUR)));
  CHECK(ls.contains(Square(C, FOUR)));
  CHECK(ls.contains(Square(D, FOUR)));
  CHECK(ls.contains(Square(F, FOUR)));
  CHECK(ls.contains(Square(E, ONE)));
  CHECK(ls.contains(Square(E, TWO)));
  CHECK(ls.contains(Square(E, THREE)));
  CHECK(ls.contains(Square(E, FIVE)));
  CHECK(ls.contains(Square(E, SIX)));
  CHECK(ls.contains(Square(E, SEVEN)));
  CHECK(ls.contains(Square(E, EIGHT)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, rookOnE4BlackPawnOnG4LegalSquares)
{
  Square from(E, FOUR);
  Board b;
  LegalSquares ls(from);
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, ROOK), from);
  b.setPiece(PlayerPiece(BLACK, PAWN), Square(G, FOUR));
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(13, ls.count());
  CHECK(ls.contains(Square(A, FOUR)));
  CHECK(ls.contains(Square(B, FOUR)));
  CHECK(ls.contains(Square(C, FOUR)));
  CHECK(ls.contains(Square(D, FOUR)));
  CHECK(ls.contains(Square(F, FOUR)));
  CHECK(ls.contains(Square(G, FOUR)));
  CHECK(ls.contains(Square(E, ONE)));
  CHECK(ls.contains(Square(E, TWO)));
  CHECK(ls.contains(Square(E, THREE)));
  CHECK(ls.contains(Square(E, FIVE)));
  CHECK(ls.contains(Square(E, SIX)));
  CHECK(ls.contains(Square(E, SEVEN)));
  CHECK(ls.contains(Square(E, EIGHT)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, rookOnE4WithPawnOnE6LegalSquares)
{
  Square from(E, FOUR);
  Board b;
  LegalSquares ls(from);
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, ROOK), from);
  b.setPiece(PlayerPiece(WHITE, PAWN), Square(E, SIX));
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(11, ls.count());
  CHECK(ls.contains(Square(A, FOUR)));
  CHECK(ls.contains(Square(B, FOUR)));
  CHECK(ls.contains(Square(C, FOUR)));
  CHECK(ls.contains(Square(D, FOUR)));
  CHECK(ls.contains(Square(F, FOUR)));
  CHECK(ls.contains(Square(G, FOUR)));
  CHECK(ls.contains(Square(H, FOUR)));
  CHECK(ls.contains(Square(E, ONE)));
  CHECK(ls.contains(Square(E, TWO)));
  CHECK(ls.contains(Square(E, THREE)));
  CHECK(ls.contains(Square(E, FIVE)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, rookOnE4BlackPawnOnE6LegalSquares)
{
  Square from(E, FOUR);
  Board b;
  LegalSquares ls(from);
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, ROOK), from);
  b.setPiece(PlayerPiece(BLACK, PAWN), Square(E, SIX));
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(12, ls.count());
  CHECK(ls.contains(Square(A, FOUR)));
  CHECK(ls.contains(Square(B, FOUR)));
  CHECK(ls.contains(Square(C, FOUR)));
  CHECK(ls.contains(Square(D, FOUR)));
  CHECK(ls.contains(Square(F, FOUR)));
  CHECK(ls.contains(Square(G, FOUR)));
  CHECK(ls.contains(Square(H, FOUR)));
  CHECK(ls.contains(Square(E, ONE)));
  CHECK(ls.contains(Square(E, TWO)));
  CHECK(ls.contains(Square(E, THREE)));
  CHECK(ls.contains(Square(E, FIVE)));
  CHECK(ls.contains(Square(E, SIX)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, rookOnE4LegalSquares)
{
  Square from(E, FOUR);
  Board b;
  LegalSquares ls(from);
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, ROOK), from);
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(14, ls.count());
  CHECK(ls.contains(Square(A, FOUR)));
  CHECK(ls.contains(Square(B, FOUR)));
  CHECK(ls.contains(Square(C, FOUR)));
  CHECK(ls.contains(Square(D, FOUR)));
  CHECK(ls.contains(Square(F, FOUR)));
  CHECK(ls.contains(Square(G, FOUR)));
  CHECK(ls.contains(Square(H, FOUR)));
  CHECK(ls.contains(Square(E, ONE)));
  CHECK(ls.contains(Square(E, TWO)));
  CHECK(ls.contains(Square(E, THREE)));
  CHECK(ls.contains(Square(E, FIVE)));
  CHECK(ls.contains(Square(E, SIX)));
  CHECK(ls.contains(Square(E, SEVEN)));
  CHECK(ls.contains(Square(E, EIGHT)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, getWBishopOnB2CrlSquareWithWhitePawnOnC3)
{
  Board b;
  GameLogic gl;
  SquaresList ctrlBlack;
  SquaresList ctrlWhite;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, BISHOP), Square(B, TWO));
  b.setPiece(PlayerPiece(WHITE, PAWN), Square(C, THREE));
  gl.setBoard(b);

  gl.getControlledSquares(WHITE, ctrlWhite);
  gl.getControlledSquares(BLACK, ctrlBlack);

  CHECK_EQUAL(6, ctrlWhite.count());
  CHECK(ctrlWhite.contains(Square(A, ONE)));
  CHECK(ctrlWhite.contains(Square(A, THREE)));
  CHECK(ctrlWhite.contains(Square(C, ONE)));
  CHECK(ctrlWhite.contains(Square(C, THREE)));
  CHECK(ctrlWhite.contains(Square(B, FOUR)));
  CHECK(ctrlWhite.contains(Square(D, FOUR)));
  CHECK_EQUAL(0, ctrlBlack.count());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, getControlledSquareOneWhiteBishop)
{
  Board b;
  GameLogic gl;
  SquaresList ctrlBlack;
  SquaresList ctrlWhite;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, BISHOP), Square(A, FOUR));
  gl.setBoard(b);

  gl.getControlledSquares(WHITE, ctrlWhite);
  gl.getControlledSquares(BLACK, ctrlBlack);

  CHECK_EQUAL(7, ctrlWhite.count());
  CHECK(ctrlWhite.contains(Square(B, THREE)));
  CHECK(ctrlWhite.contains(Square(C, TWO)));
  CHECK(ctrlWhite.contains(Square(D, ONE)));
  CHECK(ctrlWhite.contains(Square(B, FIVE)));
  CHECK(ctrlWhite.contains(Square(C, SIX)));
  CHECK(ctrlWhite.contains(Square(D, SEVEN)));
  CHECK(ctrlWhite.contains(Square(E, EIGHT)));
  CHECK_EQUAL(0, ctrlBlack.count());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, getControlledSquareOneBlackPawn)
{
  Board b;
  GameLogic gl;
  SquaresList ctrlBlack;
  SquaresList ctrlWhite;

  b.clear();
  b.setPiece(PlayerPiece(BLACK, PAWN), Square(E, FIVE));
  gl.setBoard(b);

  gl.getControlledSquares(WHITE, ctrlWhite);
  gl.getControlledSquares(BLACK, ctrlBlack);

  CHECK_EQUAL(0, ctrlWhite.count());
  CHECK_EQUAL(2, ctrlBlack.count());
  CHECK(ctrlBlack.contains(Square(D, FOUR)));
  CHECK(ctrlBlack.contains(Square(F, FOUR)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, getControlledSquareOneWhitePawn)
{
  Board b;
  GameLogic gl;
  SquaresList ctrlBlack;
  SquaresList ctrlWhite;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, PAWN), Square(B, TWO));
  gl.setBoard(b);

  gl.getControlledSquares(WHITE, ctrlWhite);
  gl.getControlledSquares(BLACK, ctrlBlack);

  CHECK_EQUAL(2, ctrlWhite.count());
  CHECK(ctrlWhite.contains(Square(A, THREE)));
  CHECK(ctrlWhite.contains(Square(C, THREE)));
  CHECK_EQUAL(0, ctrlBlack.count());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, getControlledSquareEmptyBoardButFilledSquares)
{
  Board b;
  GameLogic gl;
  SquaresList ctrlBlack;
  SquaresList ctrlWhite;

  b.clear();
  gl.setBoard(b);
  ctrlBlack.add(Square(A, ONE));
  ctrlWhite.add(Square(A, ONE));

  gl.getControlledSquares(WHITE, ctrlWhite);
  gl.getControlledSquares(BLACK, ctrlBlack);

  CHECK_EQUAL(0, ctrlWhite.count());
  CHECK_EQUAL(0, ctrlBlack.count());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, bishopMovesOnEmptyBoardOnF1)
{
  Square from(F, ONE);
  Board b;
  LegalSquares ls(from);
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, BISHOP), from);
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(7, ls.count());
  CHECK(ls.contains(Square(E, TWO)));
  CHECK(ls.contains(Square(D, THREE)));
  CHECK(ls.contains(Square(C, FOUR)));
  CHECK(ls.contains(Square(B, FIVE)));
  CHECK(ls.contains(Square(A, SIX)));
  CHECK(ls.contains(Square(G, TWO)));
  CHECK(ls.contains(Square(H, THREE)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, bishopMovesOnEmptyBoardWhitePawnG6)
{
  Square from(E, FOUR);
  Board b;
  LegalSquares ls(from);
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, BISHOP), from);
  b.setPiece(PlayerPiece(WHITE, PAWN), Square(G, SIX));
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(11, ls.count());
  CHECK(ls.contains(Square(A, EIGHT)));
  CHECK(ls.contains(Square(B, SEVEN)));
  CHECK(ls.contains(Square(C, SIX)));
  CHECK(ls.contains(Square(D, FIVE)));
  CHECK(ls.contains(Square(F, THREE)));
  CHECK(ls.contains(Square(G, TWO)));
  CHECK(ls.contains(Square(H, ONE)));
  CHECK(ls.contains(Square(B, ONE)));
  CHECK(ls.contains(Square(C, TWO)));
  CHECK(ls.contains(Square(D, THREE)));
  CHECK(ls.contains(Square(F, FIVE)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, bishopMovesOnEmptyBoardBlackPawnG6)
{
  Square from(E, FOUR);
  Board b;
  LegalSquares ls(from);
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, BISHOP), from);
  b.setPiece(PlayerPiece(BLACK, PAWN), Square(G, SIX));
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(12, ls.count());
  CHECK(ls.contains(Square(A, EIGHT)));
  CHECK(ls.contains(Square(B, SEVEN)));
  CHECK(ls.contains(Square(C, SIX)));
  CHECK(ls.contains(Square(D, FIVE)));
  CHECK(ls.contains(Square(F, THREE)));
  CHECK(ls.contains(Square(G, TWO)));
  CHECK(ls.contains(Square(H, ONE)));
  CHECK(ls.contains(Square(B, ONE)));
  CHECK(ls.contains(Square(C, TWO)));
  CHECK(ls.contains(Square(D, THREE)));
  CHECK(ls.contains(Square(F, FIVE)));
  CHECK(ls.contains(Square(G, SIX)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, bishopMovesOnEmptyBoard)
{
  Square from(E, FOUR);
  Board b;
  LegalSquares ls(from);
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, BISHOP), from);
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(13, ls.count());
  CHECK(ls.contains(Square(A, EIGHT)));
  CHECK(ls.contains(Square(B, SEVEN)));
  CHECK(ls.contains(Square(C, SIX)));
  CHECK(ls.contains(Square(D, FIVE)));
  CHECK(ls.contains(Square(F, THREE)));
  CHECK(ls.contains(Square(G, TWO)));
  CHECK(ls.contains(Square(H, ONE)));
  CHECK(ls.contains(Square(B, ONE)));
  CHECK(ls.contains(Square(C, TWO)));
  CHECK(ls.contains(Square(D, THREE)));
  CHECK(ls.contains(Square(F, FIVE)));
  CHECK(ls.contains(Square(G, SIX)));
  CHECK(ls.contains(Square(H, SEVEN)));
}

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
  ls.add(Square(G, TWO));

  gl.getLegalSquares(ls);

  CHECK_EQUAL(2, ls.count());
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

  CHECK_EQUAL(2, ls.count());
  CHECK(ls.contains(Square(E, SIX)));
  CHECK(ls.contains(Square(E, FIVE)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, noLegalMoveOnWrongPlayer)
{
  LegalSquares ls(Square(E, SEVEN));
  GameLogic gl;

  gl.getLegalSquares(ls);

  CHECK_EQUAL(0, ls.count());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, whitePawnLegalMovesAFile)
{
  LegalSquares ls(Square(A, TWO));
  GameLogic gl;

  gl.getLegalSquares(ls);

  CHECK_EQUAL(2, ls.count());
  CHECK(ls.contains(Square(A, THREE)));
  CHECK(ls.contains(Square(A, FOUR)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, whitePawnLegalMovesHFile)
{
  LegalSquares ls(Square(H, TWO));
  GameLogic gl;

  gl.getLegalSquares(ls);

  CHECK_EQUAL(2, ls.count());
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

  CHECK_EQUAL(4, ls.count());
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

  CHECK_EQUAL(1, ls.count());
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

  CHECK_EQUAL(1, ls.count());
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

  CHECK_EQUAL(0, ls.count());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, whitePawnStartLegalMoves)
{
  LegalSquares ls(Square(E, TWO));
  GameLogic gl;

  gl.getLegalSquares(ls);

  CHECK_EQUAL(2, ls.count());
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
