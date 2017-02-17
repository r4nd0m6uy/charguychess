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
#include <CppUTestExt/MockSupport.h>

#include "mocks/IBoardInputObserverMock.hpp"
#include "ui/hardware/DispatchedBoardInputEvent.hpp"

using namespace cgc;
using namespace tests;

//--------------------------------------------------------------------------------------------
TEST_GROUP(DispatchedBoardInputEventTest)
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
TEST(DispatchedBoardInputEventTest, twiceSameValueOneCallback)
{
  IBoardInputObserverMock bio;
  BoardValue bv = 4321;
  DispatchedBoardInputEvent dbie;

  dbie.registerObserver(bio);

  mock().expectOneCall("boardValueChanged").onObject(&bio).
      withParameter("bv", bv);

  dbie.raiseBoardChanged(bv);
  dbie.raiseBoardChanged(bv);

  mock().checkExpectations();
}

//--------------------------------------------------------------------------------------------
TEST(DispatchedBoardInputEventTest, observerCallback)
{
  IBoardInputObserverMock bio;
  BoardValue bv = 1234;
  DispatchedBoardInputEvent dbie;

  dbie.registerObserver(bio);

  mock().expectOneCall("boardValueChanged").onObject(&bio).
      withParameter("bv", bv);

  dbie.raiseBoardChanged(bv);

  mock().checkExpectations();
}

//--------------------------------------------------------------------------------------------
TEST(DispatchedBoardInputEventTest, DefaultConstructor)
{
  DispatchedBoardInputEvent dbie;
}
