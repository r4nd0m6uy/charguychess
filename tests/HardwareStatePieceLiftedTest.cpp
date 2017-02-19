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
#include <memory>

#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

#include "mocks/IHardwareStatePoolMock.hpp"
#include "mocks/IHardwareStateMock.hpp"
#include "ui/hardware/states/HardwareStatePieceLifted.hpp"
#include "ui/hardware/BitBoard.hpp"

using namespace cgc;
using namespace tests;

//--------------------------------------------------------------------------------------------
TEST_GROUP(HardwareStatePieceLiftedTest)
{
  TEST_SETUP()
  {
  }

  TEST_TEARDOWN()
  {
    mock().clear();
  }

  std::unique_ptr<HardwareStatePieceLifted> buildHwState()
  {
    return std::unique_ptr<HardwareStatePieceLifted>(
        new HardwareStatePieceLifted(m_hsp, m_gl));
  }

  IHardwareStatePoolMock& getHwStatePool()
  {
    return m_hsp;
  }

  GameLogic& getGl()
  {
    return m_gl;
  }

private:
  IHardwareStatePoolMock m_hsp;
  GameLogic m_gl;
};

//--------------------------------------------------------------------------------------------
TEST(HardwareStatePieceLiftedTest, executeTwoBitsChangedTwoPiecesLiftedForCapture)
{
  IHardwareStateMock nextState;
  BoardValue bv = 0xFFF700000000EFFF; // e4 and d5 lifted
  Board b;
  std::unique_ptr<HardwareStatePieceLifted> state = buildHwState();

  // Fake 1. e2e4 d7d5
  b.setPiece(PlayerPiece(), Square(E, TWO));
  b.setPiece(PlayerPiece(), Square(D, SEVEN));
  b.setPiece(PlayerPiece(WHITE, PAWN), Square(E, FOUR));
  b.setPiece(PlayerPiece(BLACK, PAWN), Square(D, FIVE));
  getGl().setBoard(b);

  mock().expectOneCall("enterState").onObject(&getHwStatePool()).
      withParameter("which", IHardwareStatePool::PLAYER_CAPTURE).
      withParameter("bv", bv).
      andReturnValue(&nextState);

  POINTERS_EQUAL(&nextState, &state->execute(bv));

  mock().checkExpectations();
}

//--------------------------------------------------------------------------------------------
TEST(HardwareStatePieceLiftedTest, executeStateLegalMove)
{
  Board b;
  BoardValue bvExecute = 0xFFFE01000000FFFF; // h3 dropped
  IHardwareStateMock nextState;
  std::unique_ptr<HardwareStatePieceLifted> state = buildHwState();

  getGl().setBoard(b);

  mock().expectOneCall("enterState").onObject(&getHwStatePool()).
      withParameter("which", IHardwareStatePool::PLAYER_THINKING).
      withParameter("bv", bvExecute).
      andReturnValue(&nextState);

  POINTERS_EQUAL(&nextState, &state->execute(bvExecute));

  // Move was done
  CHECK(getGl().getBoard().isEmpty(Square(H, TWO)));
  CHECK(PlayerPiece(WHITE, PAWN) == getGl().getBoard().getPiece(Square(H, THREE)));

  mock().checkExpectations();
}

//--------------------------------------------------------------------------------------------
TEST(HardwareStatePieceLiftedTest, executeStateIllegalMove)
{
  Board b;
  BoardValue bv = 0xFFFE00000100FFFF;
  IHardwareStateMock nextState;
  std::unique_ptr<HardwareStatePieceLifted> state = buildHwState();

  getGl().setBoard(b);

  mock().expectOneCall("enterState").onObject(&getHwStatePool()).
      withParameter("which", IHardwareStatePool::PANIC).
      withParameter("bv", bv).
      andReturnValue(&nextState);

  POINTERS_EQUAL(&nextState, &state->execute(bv));

  mock().checkExpectations();
}

//--------------------------------------------------------------------------------------------
TEST(HardwareStatePieceLiftedTest, executeStateTwoPlayerPieces)
{
  Board b;
  BoardValue bv = 0xFFFC00000000FFFF;
  IHardwareStateMock nextState;
  std::unique_ptr<HardwareStatePieceLifted> state = buildHwState();

  getGl().setBoard(b);

  mock().expectOneCall("enterState").onObject(&getHwStatePool()).
      withParameter("which", IHardwareStatePool::PANIC).
      withParameter("bv", bv).
      andReturnValue(&nextState);

  POINTERS_EQUAL(&nextState, &state->execute(bv));

  mock().checkExpectations();
}

//--------------------------------------------------------------------------------------------
TEST(HardwareStatePieceLiftedTest, executeStateBackToGameStatus)
{
  Board b;
  BoardValue bv = 0xFFFF00000000FFFF;
  IHardwareStateMock nextState;
  std::unique_ptr<HardwareStatePieceLifted> state = buildHwState();

  getGl().setBoard(b);

  mock().expectOneCall("enterState").onObject(&getHwStatePool()).
      withParameter("which", IHardwareStatePool::PLAYER_THINKING).
      withParameter("bv", bv).
      andReturnValue(&nextState);

  POINTERS_EQUAL(&nextState, &state->execute(bv));

  mock().checkExpectations();
}

//--------------------------------------------------------------------------------------------
TEST(HardwareStatePieceLiftedTest, executeStateOnePieceLifted)
{
  Board b;
  BoardValue bv = 0xFFFE00000000FFFF;
  IHardwareStateMock nextState;
  std::unique_ptr<HardwareStatePieceLifted> state = buildHwState();

  getGl().setBoard(b);

  mock().expectOneCall("enterState").onObject(&getHwStatePool()).
      withParameter("which", IHardwareStatePool::PLAYER_LIFTED_PIECE).
      withParameter("bv", bv).
      andReturnValue(&nextState);

  POINTERS_EQUAL(&nextState, &state->execute(bv));

  mock().checkExpectations();
}

//--------------------------------------------------------------------------------------------
TEST(HardwareStatePieceLiftedTest, executeStateTooManyPiecesLifted)
{
  Board b;
  BoardValue bv = 0xFF0F00000000FFFF;
  IHardwareStateMock nextState;
  std::unique_ptr<HardwareStatePieceLifted> state = buildHwState();

  getGl().setBoard(b);

  mock().expectOneCall("enterState").onObject(&getHwStatePool()).
      withParameter("which", IHardwareStatePool::PANIC).
      withParameter("bv", bv).
      andReturnValue(&nextState);

  POINTERS_EQUAL(&nextState, &state->execute(bv));

  mock().checkExpectations();
}

//--------------------------------------------------------------------------------------------
TEST(HardwareStatePieceLiftedTest, enterStateDoesNothing)
{
  Board b;
  BoardValue newBv = 0xFFFE00000000FFFF; // h2 lifted
  std::unique_ptr<HardwareStatePieceLifted> state = buildHwState();

  getGl().setBoard(b);

  state->enter(newBv);
}

//--------------------------------------------------------------------------------------------
TEST(HardwareStatePieceLiftedTest, DefaultConstructor)
{
  std::unique_ptr<HardwareStatePieceLifted> state = buildHwState();
}
