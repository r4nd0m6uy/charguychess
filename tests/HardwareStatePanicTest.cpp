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
#include "ui/hardware/states/HardwareStatePanic.hpp"
#include "ui/hardware/BitBoard.hpp"

using namespace cgc;
using namespace tests;

//--------------------------------------------------------------------------------------------
TEST_GROUP(HardwareStatePanicTest)
{
  TEST_SETUP()
  {
  }

  TEST_TEARDOWN()
  {
    mock().clear();
  }

  std::unique_ptr<HardwareStatePanic> buildHwState()
  {
    return std::unique_ptr<HardwareStatePanic>(new HardwareStatePanic(m_hsp, m_gl));
  }

  IHardwareStatePoolMock& getHwStatePool()
  {
    return m_hsp;
  }

private:
  IHardwareStatePoolMock m_hsp;
  GameLogic m_gl;
};
//--------------------------------------------------------------------------------------------
TEST(HardwareStatePanicTest, executeEntersThinkingOnExpectedValue)
{
  Board b;
  BitBoard bb(b);
  IHardwareStateMock nextState;
  std::unique_ptr<HardwareStatePanic> state = buildHwState();

  mock().expectOneCall("enterState").onObject(&getHwStatePool()).
      withParameter("which", IHardwareStatePool::PLAYER_THINKING).
      andReturnValue(&nextState);

  POINTERS_EQUAL(&nextState, &state->execute(bb.getBoardValue()));

  mock().checkExpectations();
}

//--------------------------------------------------------------------------------------------
TEST(HardwareStatePanicTest, executeDoesNothingNotExpectedValue)
{
  BoardValue bv = 1234;
  std::unique_ptr<HardwareStatePanic> state = buildHwState();

  POINTERS_EQUAL(state.get(), &state->execute(bv));

  mock().checkExpectations();
}

//--------------------------------------------------------------------------------------------
TEST(HardwareStatePanicTest, enterDoesNothing)
{
  std::unique_ptr<HardwareStatePanic> state = buildHwState();

  state->enter();

  mock().checkExpectations();
}

//--------------------------------------------------------------------------------------------
TEST(HardwareStatePanicTest, DefaultConstructor)
{
  std::unique_ptr<HardwareStatePanic> state = buildHwState();
}