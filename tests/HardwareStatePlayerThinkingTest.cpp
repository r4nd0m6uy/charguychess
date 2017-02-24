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

#include "utils/BoardValueComparator.hpp"
#include "mocks/IHardwareStatePoolMock.hpp"
#include "mocks/IHardwareStateMock.hpp"
#include "ui/hardware/states/HardwareStatePlayerThinking.hpp"
#include "ui/hardware/BitBoard.hpp"

using namespace cgc;
using namespace tests;

//--------------------------------------------------------------------------------------------
TEST_GROUP(HardwareStatePlayerThinkingTest)
{
  TEST_SETUP()
  {
    m_gl.newGame();
    mock().installComparator("BoardValue", m_bvComp);
  }

  TEST_TEARDOWN()
  {
    mock().removeAllComparatorsAndCopiers();
    mock().clear();
  }

  std::unique_ptr<HardwareStatePlayerThinking> buildHwState()
  {
    return std::unique_ptr<HardwareStatePlayerThinking>(
        new HardwareStatePlayerThinking(m_hsp, m_gl));
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
  BoardValueComparator m_bvComp;
  IHardwareStatePoolMock m_hsp;
  GameLogic m_gl;
};

//--------------------------------------------------------------------------------------------
TEST(HardwareStatePlayerThinkingTest, executeTwoBitsChangedLegalMove)
{
  IHardwareStateMock nextState;
  BoardValue bv = 0xFF7F80000000FFFF; // a2a3
  std::unique_ptr<HardwareStatePlayerThinking> state = buildHwState();

  mock().expectOneCall("enterState").onObject(&getHwStatePool()).
      withParameter("which", IHardwareStatePool::PLAYER_LIFTED_PIECE).
      withParameterOfType("BoardValue", "bv", &bv).
      andReturnValue(&nextState);
  mock().expectOneCall("execute").onObject(&nextState).
      withParameterOfType("BoardValue", "bv", &bv).
      andReturnValue(&nextState);

  POINTERS_EQUAL(&nextState, &state->execute(bv));

  mock().checkExpectations();
}

//--------------------------------------------------------------------------------------------
TEST(HardwareStatePlayerThinkingTest, executeOnePieceLiftedWrongPlayer)
{
  Board b;
  IHardwareStateMock nextState;
  Square liftedSquare(B, SEVEN);
  std::unique_ptr<HardwareStatePlayerThinking> state = buildHwState();

  getGl().setBoard(b);
  b.clear(liftedSquare);
  BitBoard bb(b);
  BoardValue bv = bb.getBoardValue();

  mock().expectOneCall("enterState").onObject(&getHwStatePool()).
      withParameter("which", IHardwareStatePool::PANIC).
      withParameterOfType("BoardValue", "bv", &bv).
      andReturnValue(&nextState);

  POINTERS_EQUAL(&nextState, &state->execute(bb.getBoardValue()));

  mock().checkExpectations();
}

//--------------------------------------------------------------------------------------------
TEST(HardwareStatePlayerThinkingTest, executeTooManyPieces)
{
  Board b;
  IHardwareStateMock nextState;
  std::unique_ptr<HardwareStatePlayerThinking> state = buildHwState();

  b.setPiece(PlayerPiece(BLACK, QUEEN), Square(C, FIVE));
  BitBoard bb(b);
  BoardValue bv = bb.getBoardValue();

  mock().expectOneCall("enterState").onObject(&getHwStatePool()).
      withParameter("which", IHardwareStatePool::PANIC).
      withParameterOfType("BoardValue", "bv", &bv).
      andReturnValue(&nextState);

  POINTERS_EQUAL(&nextState, &state->execute(bb.getBoardValue()));

  mock().checkExpectations();
}

//--------------------------------------------------------------------------------------------
TEST(HardwareStatePlayerThinkingTest, enterDoesNothing)
{
  BoardValue bv(234);
  std::unique_ptr<HardwareStatePlayerThinking> state = buildHwState();

  state->enter(bv);

  mock().checkExpectations();
}

//--------------------------------------------------------------------------------------------
TEST(HardwareStatePlayerThinkingTest, DefaultConstructor)
{
  std::unique_ptr<HardwareStatePlayerThinking> state = buildHwState();
}
