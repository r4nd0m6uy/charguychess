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
TEST(GameLogicTest, applyMoveWhitePromotionInHistory)
{
  Board b;
  Square to(C, EIGHT);
  Move m(Square(C, SEVEN), to);
  GameLogic gl;

  b.clear();
  b.setPiece(WHITE, PAWN, C, SEVEN);
  gl.setBoard(b);
  m.setPromotion(ROOK);

  CHECK(gl.applyMove(m));
  Move mH= gl.getGameHistory().getTurns().front().getWhiteMove();
  CHECK(mH.hasPromotion());
  CHECK_EQUAL(ROOK, mH.getPromotion());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, applyMoveWhitePromotesToBishop)
{
  Board b;
  Square to(C, EIGHT);
  Move m(Square(C, SEVEN), to);
  GameLogic gl;

  b.clear();
  b.setPiece(WHITE, PAWN, C, SEVEN);
  gl.setBoard(b);
  m.setPromotion(ROOK);

  CHECK(gl.applyMove(m));
  CHECK_EQUAL(WHITE, gl.getBoard().getPieceColor(to));
  CHECK_EQUAL(ROOK, gl.getBoard().getPieceType(to));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, isLegalBlackPawntMoveWhenMissingPromotion)
{
  Board b;
  Move m(Square(B, TWO), Square(B, ONE));
  GameLogic gl;

  b.clear();
  b.setPiece(BLACK, PAWN, B, TWO);
  gl.setBoard(b);
  gl.setTurn(BLACK);

  CHECK_FALSE(gl.isMoveLegal(m));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, isLegalWhiePawntMoveWhenMissingPromotion)
{
  Board b;
  Move m(Square(C, SEVEN), Square(C, EIGHT));
  GameLogic gl;

  b.clear();
  b.setPiece(WHITE, PAWN, C, SEVEN);
  gl.setBoard(b);

  CHECK_FALSE(gl.isMoveLegal(m));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, applyMoveMateInHistory)
{
  GameLogic gl;
  Square from(F, SIX);
  Square to(F, SEVEN);
  Move m(from, to);
  Board b;
  GameTurn firstTurn;

  b.setPiece(PlayerPiece(WHITE, QUEEN), from);
  b.setPiece(PlayerPiece(WHITE, ROOK), Square(F, THREE));
  gl.setBoard(b);

  CHECK(gl.applyMove(m));
  CHECK(gl.isMated(BLACK));

  firstTurn = gl.getGameHistory().getTurns().front();
  CHECK(firstTurn.getWhiteMove().isMate());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, applyMoveCheckInHistory)
{
  GameLogic gl;
  Square from(E, SIX);
  Square to(E, SEVEN);
  Move m(from, to);
  Board b;
  GameTurn firstTurn;

  b.setPiece(PlayerPiece(WHITE, QUEEN), from);
  gl.setBoard(b);

  CHECK(gl.applyMove(m));

  firstTurn = gl.getGameHistory().getTurns().front();
  CHECK(firstTurn.getWhiteMove().isCheck());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, applyMoveCaptureInHistory)
{
  GameLogic gl;
  Square from(E, FOUR);
  Square to(D, FIVE);
  Move m(from, to);
  Board b;
  GameTurn firstTurn;

  b.setPiece(PlayerPiece(BLACK, PAWN), to);
  b.setPiece(PlayerPiece(WHITE, PAWN), from);
  gl.setBoard(b);

  CHECK(gl.applyMove(m));

  firstTurn = gl.getGameHistory().getTurns().front();
  CHECK(firstTurn.getWhiteMove().isCapture());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, applyMovelegalMoveInHistory)
{
  GameLogic gl;
  Square from(A, TWO);
  Square to(A, THREE);
  Move m(from, to);
  GameTurn firstTurn;

  CHECK(gl.applyMove(m));

  firstTurn = gl.getGameHistory().getTurns().front();
  CHECK(firstTurn.getWhiteMove().isValid());
  CHECK(firstTurn.getWhiteMove().getFrom() == from);
  CHECK(firstTurn.getWhiteMove().getTo() == to);
  CHECK(firstTurn.getWhiteMove().getWho() == PAWN);
  CHECK_FALSE(firstTurn.getWhiteMove().isCapture());
  CHECK_FALSE(firstTurn.getWhiteMove().isCheck());
  CHECK_FALSE(firstTurn.getBlackMove().isValid());
  CHECK_FALSE(firstTurn.getWhiteMove().isMate());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, applyMoveillegalMoveNOtInHistory)
{
  GameLogic gl;
  Square from(A, TWO);
  Square to(A, EIGHT);
  Move m(from, to);
  GameTurn firstTurn;

  CHECK_FALSE(gl.applyMove(m));

  firstTurn = gl.getGameHistory().getTurns().front();
  CHECK_FALSE(firstTurn.getWhiteMove().isValid());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, isMatedWhiteMate)
{
  Board b;
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(BLACK, ROOK), Square(A, EIGHT));
  b.setPiece(PlayerPiece(BLACK, ROOK), Square(B, EIGHT));
  b.setPiece(PlayerPiece(WHITE, KING), Square(A, ONE));
  gl.setBoard(b);

  CHECK(gl.isMated(WHITE));
  CHECK_FALSE(gl.isMated(BLACK));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, isMatedInitialPosition)
{
  GameLogic gl;

  CHECK_FALSE(gl.isMated(WHITE));
  CHECK_FALSE(gl.isMated(BLACK));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, legalSquaresKingCheckedByQueen)
{
  Board b;
  Square from(E, FOUR);
  LegalSquares ls(from);
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, KING), from);
  b.setPiece(BLACK, QUEEN, A, FOUR);
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(6, ls.count());
  CHECK(ls.contains(D, FIVE));
  CHECK(ls.contains(E, FIVE));
  CHECK(ls.contains(F, FIVE));
  CHECK(ls.contains(D, THREE));
  CHECK(ls.contains(E, THREE));
  CHECK(ls.contains(F, THREE));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, legalSquaresQueenDiscoveredCheckHori)
{
  Board b;
  Square from(E, FOUR);
  LegalSquares ls(from);
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, QUEEN), from);
  b.setPiece(PlayerPiece(WHITE, KING), Square(E, TWO));
  b.setPiece(PlayerPiece(BLACK, QUEEN), Square(E, SIX));
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(3, ls.count());
  CHECK(ls.contains(Square(E, THREE)));
  CHECK(ls.contains(Square(E, FIVE)));
  CHECK(ls.contains(Square(E, SIX)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, legalSquaresQueenDiscoveredCheckDiag)
{
  Board b;
  Square from(E, FOUR);
  LegalSquares ls(from);
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, QUEEN), from);
  b.setPiece(PlayerPiece(WHITE, KING), Square(G, TWO));
  b.setPiece(PlayerPiece(BLACK, QUEEN), Square(C, SIX));
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(3, ls.count());
  CHECK(ls.contains(Square(D, FIVE)));
  CHECK(ls.contains(Square(C, SIX)));
  CHECK(ls.contains(Square(F, THREE)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, legalSquaresPawnDiscoveredCheck)
{
  Board b;
  Square from(E, FOUR);
  LegalSquares ls(from);
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, PAWN), from);
  b.setPiece(PlayerPiece(WHITE, KING), Square(G, TWO));
  b.setPiece(PlayerPiece(BLACK, QUEEN), Square(C, SIX));
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(0, ls.count());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, legalSquaresBishopDiscoveredCheck)
{
  Board b;
  Square from(E, FOUR);
  LegalSquares ls(from);
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, BISHOP), from);
  b.setPiece(PlayerPiece(WHITE, KING), Square(G, TWO));
  b.setPiece(PlayerPiece(BLACK, QUEEN), Square(C, SIX));
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(3, ls.count());
  CHECK(ls.contains(Square(D, FIVE)));
  CHECK(ls.contains(Square(C, SIX)));
  CHECK(ls.contains(Square(F, THREE)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, legalSquaresKnightDiscoveredCheck)
{
  Board b;
  Square from(E, FOUR);
  LegalSquares ls(from);
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, KNIGHT), from);
  b.setPiece(PlayerPiece(WHITE, KING), Square(E, TWO));
  b.setPiece(PlayerPiece(BLACK, QUEEN), Square(E, SIX));
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(0, ls.count());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, legalRookDiscoveredCheck)
{
  Board b;
  Square from(E, FOUR);
  LegalSquares ls(from);
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, ROOK), from);
  b.setPiece(PlayerPiece(WHITE, KING), Square(E, TWO));
  b.setPiece(PlayerPiece(BLACK, QUEEN), Square(E, SIX));
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(3, ls.count());
  CHECK(ls.contains(Square(E, THREE)));
  CHECK(ls.contains(Square(E, FIVE)));
  CHECK(ls.contains(Square(E, SIX)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, legalSquaresKingOnE4BlackQueenOnF6NoCheckedMove)
{
  Square from(E, FOUR);
  Board b;
  LegalSquares ls(from);
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, KING), from);
  b.setPiece(PlayerPiece(BLACK, QUEEN), Square(F, SIX));
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(3, ls.count());
  CHECK(ls.contains(Square(D, THREE)));
  CHECK(ls.contains(Square(D, FIVE)));
  CHECK(ls.contains(Square(E, THREE)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, isCheckedInitialPosBlackQueenOnE2)
{
  Board b;
  GameLogic gl;

  b.setPiece(PlayerPiece(BLACK, QUEEN), Square(E, TWO));
  gl.setBoard(b);

  CHECK_FALSE(gl.isChecked(BLACK));
  CHECK(gl.isChecked(WHITE));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, isCheckedInitialPosition)
{
  Board b;
  GameLogic gl;

  CHECK_FALSE(gl.isChecked(BLACK));
  CHECK_FALSE(gl.isChecked(WHITE));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, controlledSquaresKingOnE4PawnOnE5)
{
  Square from(E, FOUR);
  Board b;
  SquaresList ctrlBlack;
  SquaresList ctrlWhite;
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, KING), from);
  b.setPiece(PlayerPiece(WHITE, PAWN), Square(E, FIVE));
  gl.setBoard(b);

  gl.getControlledSquares(WHITE, ctrlWhite);
  gl.getControlledSquares(BLACK, ctrlBlack);

  CHECK_EQUAL(10, ctrlWhite.count());
  CHECK(ctrlWhite.contains(Square(D, FIVE)));
  CHECK(ctrlWhite.contains(Square(F, FIVE)));
  CHECK(ctrlWhite.contains(Square(D, FOUR)));
  CHECK(ctrlWhite.contains(Square(F, FOUR)));
  CHECK(ctrlWhite.contains(Square(D, THREE)));
  CHECK(ctrlWhite.contains(Square(E, THREE)));
  CHECK(ctrlWhite.contains(Square(F, THREE)));
  CHECK(ctrlWhite.contains(Square(D, SIX)));
  CHECK(ctrlWhite.contains(Square(F, SIX)));
  CHECK_EQUAL(0, ctrlBlack.count());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, legalSquaresKingOnE4PawnOnE5)
{
  Square from(E, FOUR);
  Board b;
  LegalSquares ls(from);
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, KING), from);
  b.setPiece(PlayerPiece(WHITE, PAWN), Square(E, FIVE));
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(7, ls.count());
  CHECK(ls.contains(Square(D, FIVE)));
  CHECK(ls.contains(Square(F, FIVE)));
  CHECK(ls.contains(Square(D, FOUR)));
  CHECK(ls.contains(Square(F, FOUR)));
  CHECK(ls.contains(Square(D, THREE)));
  CHECK(ls.contains(Square(E, THREE)));
  CHECK(ls.contains(Square(F, THREE)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, legalSquaresKingOnA1)
{
  Square from(A, ONE);
  Board b;
  LegalSquares ls(from);
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, KING), from);
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(3, ls.count());
  CHECK(ls.contains(Square(A, TWO)));
  CHECK(ls.contains(Square(B, ONE)));
  CHECK(ls.contains(Square(B, TWO)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, legalSquaresKingOnE4)
{
  Square from(E, FOUR);
  Board b;
  LegalSquares ls(from);
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, KING), from);
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(8, ls.count());
  CHECK(ls.contains(Square(D, FIVE)));
  CHECK(ls.contains(Square(E, FIVE)));
  CHECK(ls.contains(Square(F, FIVE)));
  CHECK(ls.contains(Square(D, FOUR)));
  CHECK(ls.contains(Square(F, FOUR)));
  CHECK(ls.contains(Square(D, THREE)));
  CHECK(ls.contains(Square(E, THREE)));
  CHECK(ls.contains(Square(F, THREE)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, controlledSquareKnightOnA1WhitePawnB3)
{
  Board b;
  SquaresList ctrlBlack;
  SquaresList ctrlWhite;
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, KNIGHT), Square(A, ONE));
  b.setPiece(PlayerPiece(WHITE, PAWN), Square(B, THREE));
  gl.setBoard(b);

  gl.getControlledSquares(WHITE, ctrlWhite);
  gl.getControlledSquares(BLACK, ctrlBlack);

  CHECK_EQUAL(4, ctrlWhite.count());
  CHECK(ctrlWhite.contains(Square(B, THREE)));
  CHECK(ctrlWhite.contains(Square(C, TWO)));
  CHECK(ctrlWhite.contains(Square(A, FOUR)));
  CHECK(ctrlWhite.contains(Square(C, FOUR)));

  CHECK_EQUAL(0, ctrlBlack.count());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, legalSquaresKnightOnA1WhitPawnB3)
{
  Square from(A, ONE);
  Board b;
  LegalSquares ls(from);
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, KNIGHT), from);
  b.setPiece(PlayerPiece(WHITE, PAWN), Square(B, THREE));
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(1, ls.count());
  CHECK(ls.contains(Square(C, TWO)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, legalSquaresKnightOnA1)
{
  Square from(A, ONE);
  Board b;
  LegalSquares ls(from);
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, KNIGHT), from);
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(2, ls.count());
  CHECK(ls.contains(Square(B, THREE)));
  CHECK(ls.contains(Square(C, TWO)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, legalSquaresKnightOnE4)
{
  Square from(E, FOUR);
  Board b;
  LegalSquares ls(from);
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, KNIGHT), from);
  gl.setBoard(b);

  gl.getLegalSquares(ls);

  CHECK_EQUAL(8, ls.count());
  CHECK(ls.contains(Square(C, THREE)));
  CHECK(ls.contains(Square(C, FIVE)));
  CHECK(ls.contains(Square(D, TWO)));
  CHECK(ls.contains(Square(D, SIX)));
  CHECK(ls.contains(Square(F, TWO)));
  CHECK(ls.contains(Square(F, SIX)));
  CHECK(ls.contains(Square(G, THREE)));
  CHECK(ls.contains(Square(G, FIVE)));
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, controlledSquareQueenOnE4WhitePawnsBlocking)
{
  Board b;
  SquaresList ctrlBlack;
  SquaresList ctrlWhite;
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, QUEEN), Square(B, THREE));
  b.setPiece(PlayerPiece(WHITE, PAWN), Square(A, FOUR));
  b.setPiece(PlayerPiece(WHITE, PAWN), Square(B, FOUR));
  b.setPiece(PlayerPiece(WHITE, PAWN), Square(C, FOUR));
  b.setPiece(PlayerPiece(WHITE, PAWN), Square(A, THREE));
  b.setPiece(PlayerPiece(WHITE, PAWN), Square(C, THREE));
  b.setPiece(PlayerPiece(WHITE, PAWN), Square(A, TWO));
  b.setPiece(PlayerPiece(WHITE, PAWN), Square(B, TWO));
  b.setPiece(PlayerPiece(WHITE, PAWN), Square(C, TWO));
  gl.setBoard(b);

  gl.getControlledSquares(WHITE, ctrlWhite);
  gl.getControlledSquares(BLACK, ctrlBlack);

  CHECK_EQUAL(15, ctrlWhite.count());
  CHECK(ctrlWhite.contains(Square(A, FIVE)));
  CHECK(ctrlWhite.contains(Square(B, FIVE)));
  CHECK(ctrlWhite.contains(Square(C, FIVE)));
  CHECK(ctrlWhite.contains(Square(D, FIVE)));
  CHECK(ctrlWhite.contains(Square(A, FOUR)));
  CHECK(ctrlWhite.contains(Square(B, FOUR)));
  CHECK(ctrlWhite.contains(Square(C, FOUR)));
  CHECK(ctrlWhite.contains(Square(D, FOUR)));
  CHECK(ctrlWhite.contains(Square(A, THREE)));
  CHECK(ctrlWhite.contains(Square(B, THREE)));
  CHECK(ctrlWhite.contains(Square(C, THREE)));
  CHECK(ctrlWhite.contains(Square(D, THREE)));
  CHECK(ctrlWhite.contains(Square(A, TWO)));
  CHECK(ctrlWhite.contains(Square(B, TWO)));
  CHECK(ctrlWhite.contains(Square(C, TWO)));

  CHECK_EQUAL(0, ctrlBlack.count());
}

//--------------------------------------------------------------------------------------------
TEST(GameLogicTest, queenOnE4LegalSquares)
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
TEST(GameLogicTest, controlledSquareQueenOnE4)
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
TEST(GameLogicTest, controlledSquareWhiteRookOnB2WhitPawnOnB4AndD2)
{
  Board b;
  SquaresList whiteSquares;
  SquaresList blackSquares;
  GameLogic gl;

  b.clear();
  b.setPiece(PlayerPiece(WHITE, ROOK), Square(B, TWO));
  b.setPiece(PlayerPiece(WHITE, PAWN), Square(B, FOUR));
  b.setPiece(PlayerPiece(WHITE, PAWN), Square(D, TWO));
  gl.setBoard(b);

  gl.getControlledSquares(WHITE, whiteSquares);
  gl.getControlledSquares(BLACK, blackSquares);

  CHECK_EQUAL(10, whiteSquares.count());
  // Rook
  CHECK(whiteSquares.contains(Square(A, TWO)));
  CHECK(whiteSquares.contains(Square(C, TWO)));
  CHECK(whiteSquares.contains(Square(D, TWO)));
  CHECK(whiteSquares.contains(Square(B, ONE)));
  CHECK(whiteSquares.contains(Square(B, THREE)));
  CHECK(whiteSquares.contains(Square(B, FOUR)));
  // b4 pawn
  CHECK(whiteSquares.contains(Square(A, FIVE)));
  CHECK(whiteSquares.contains(Square(C, FIVE)));
  // D2 pawn
  CHECK(whiteSquares.contains(Square(C, THREE)));
  CHECK(whiteSquares.contains(Square(E, THREE)));
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
TEST(GameLogicTest, legalSquaresRookOnE4BWhitePawnOnG4)
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
TEST(GameLogicTest, legalSquaresRookOnE4BlackPawnOnG4)
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
TEST(GameLogicTest, legalSquaresRookOnE4WithPawnOnE6)
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
TEST(GameLogicTest, legalSquaresrookOnE4BlackPawnOnE6)
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
TEST(GameLogicTest, legalSquaresRookOnE4)
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
TEST(GameLogicTest, controlledSquaresWhiteBishopOnB2WithWhitePawnOnC3)
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
TEST(GameLogicTest, controlledSquareOneWhiteBishop)
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
TEST(GameLogicTest, controlledSquareOneBlackPawn)
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
TEST(GameLogicTest, controlledSquareOneWhitePawn)
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
TEST(GameLogicTest, controlledSquareEmptyBoardButFilledSquares)
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
TEST(GameLogicTest, legalSquareBishopOnF1)
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
TEST(GameLogicTest, legalSquareBbishopE4WhitePawnG6)
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
TEST(GameLogicTest, legalSquarebishopE4BoardBlackPawnG6)
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
TEST(GameLogicTest, legalSquaresBishopOnE4)
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
TEST(GameLogicTest, newGameGameHistoryCleared)
{
  Move m(Square(E, TWO), Square(E, THREE));
  Board b;
  GameLogic gl;

  CHECK(gl.applyMove(m));
  gl.newGame();

  GameTurn firstTurn = gl.getGameHistory().getTurns().front();
  CHECK_FALSE(firstTurn.getWhiteMove().isValid());
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
