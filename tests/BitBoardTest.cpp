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

#include "ui/hardware/BitBoard.hpp"

using namespace cgc;

//--------------------------------------------------------------------------------------------
TEST_GROUP(BitBoardTest)
{
  TEST_SETUP()
  {
  }

  TEST_TEARDOWN()
  {
  }
};

//--------------------------------------------------------------------------------------------
TEST(BitBoardTest, toBoardStringE2E4)
{
  BitBoard bb;
  std::string expectedStr =
      "11111111\n"  // FF
      "11111111\n"  // FF
      "00000000\n"  // 00
      "00000000\n"  // 00
      "00001000\n"  // 08
      "00000000\n"  // 00
      "11110111\n"  // F7
      "11111111";   // FF

  bb.setBoardValue(0xFFF700080000FFFF);
  STRCMP_EQUAL(expectedStr.c_str(), bb.toBoardString().c_str());
}

//--------------------------------------------------------------------------------------------
TEST(BitBoardTest, toBoardStringBlackTowers)
{
  BitBoard bb;
  std::string expectedStr =
      "10000001\n"  // 81
      "00000000\n"  // 00
      "00000000\n"  // 00
      "00000000\n"  // 00
      "00000000\n"  // 00
      "00000000\n"  // 00
      "00000000\n"  // 00
      "00000000";   // 00

  bb.setBoardValue(0x0000000000000081);
  STRCMP_EQUAL(expectedStr.c_str(), bb.toBoardString().c_str());
}

//--------------------------------------------------------------------------------------------
TEST(BitBoardTest, toBoardStringAllBitSet)
{
  BitBoard bb;
  std::string expectedStr =
      "11111111\n"  // FF
      "11111111\n"  // FF
      "11111111\n"  // FF
      "11111111\n"  // FF
      "11111111\n"  // FF
      "11111111\n"  // FF
      "11111111\n"  // FF
      "11111111";   // FF

  bb.setBoardValue(0xFFFFFFFFFFFFFFFF);
  STRCMP_EQUAL(expectedStr.c_str(), bb.toBoardString().c_str());
}

//--------------------------------------------------------------------------------------------
TEST(BitBoardTest, toBoardStringEmptySet)
{
  BitBoard bb;
  std::string expectedStr =
      "00000000\n"
      "00000000\n"
      "00000000\n"
      "00000000\n"
      "00000000\n"
      "00000000\n"
      "00000000\n"
      "00000000";

  STRCMP_EQUAL(expectedStr.c_str(), bb.toBoardString().c_str());
}

//--------------------------------------------------------------------------------------------
TEST(BitBoardTest, isBitSetSetAt64)
{
  BitBoard bb;

  bb.setBoardValue(0x8000000000000000);

  CHECK(bb.isBitSet(63));
}

//--------------------------------------------------------------------------------------------
TEST(BitBoardTest, isBitSetSetAtOne)
{
  BitBoard bb;

  bb.setBoardValue(0x2);

  CHECK_FALSE(bb.isBitSet(0));
  CHECK(bb.isBitSet(1));
}

//--------------------------------------------------------------------------------------------
TEST(BitBoardTest, DefaultConstructor)
{
  BitBoard bb;

  CHECK_EQUAL(0, bb.getBoardValue());
}
