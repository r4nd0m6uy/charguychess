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
TEST(BitBoardTest, startPosD2Lifted)
{
  SquaresList cs;
  BitBoard bb(0xFFFF00000000FFFF);

  bb.getChangedSquares(0xFFEF00000000FFFF, cs);

  CHECK_EQUAL(1, cs.count());
  CHECK(cs.contains(Square(D, TWO)));
}

//--------------------------------------------------------------------------------------------
TEST(BitBoardTest, getChangedSquaresEmptyE2Added)
{
  SquaresList cs;
  BitBoard bb(0x0);

  bb.getChangedSquares(0x0008000000000000, cs);

  CHECK_EQUAL(1, cs.count());
  CHECK(cs.contains(Square(E, TWO)));
}

//--------------------------------------------------------------------------------------------
TEST(BitBoardTest, getChangedSquaresNoChangeButFilledList)
{
  SquaresList cs;
  BitBoard bb(1234);

  cs.add(Square(A, ONE));
  bb.getChangedSquares(1234, cs);

  CHECK_EQUAL(0, cs.count());
}

//--------------------------------------------------------------------------------------------
TEST(BitBoardTest, getChangedSquaresNoChange)
{
  SquaresList cs;
  BitBoard bb(1234);

  bb.getChangedSquares(1234, cs);

  CHECK_EQUAL(0, cs.count());
}

//--------------------------------------------------------------------------------------------
TEST(BitBoardTest, getActiveSquaresG8)
{
  SquaresList cs;
  BitBoard bb(0x0000000000000002);

  bb.getActiveSquares(cs);

  CHECK_EQUAL(1, cs.count());
  CHECK(cs.contains(Square(G, EIGHT)));
}

//--------------------------------------------------------------------------------------------
TEST(BitBoardTest, getActiveSquaresB1)
{
  SquaresList cs;
  BitBoard bb(0x4000000000000000);

  bb.getActiveSquares(cs);

  CHECK_EQUAL(1, cs.count());
  CHECK(cs.contains(Square(B, ONE)));
}

//--------------------------------------------------------------------------------------------
TEST(BitBoardTest, getActiveSquaresH8)
{
  SquaresList cs;
  BitBoard bb(0x0000000000000001);

  bb.getActiveSquares(cs);

  CHECK_EQUAL(1, cs.count());
  CHECK(cs.contains(Square(H, EIGHT)));
}

//--------------------------------------------------------------------------------------------
TEST(BitBoardTest, getActiveSquaresA1)
{
  SquaresList cs;
  BitBoard bb(0x8000000000000000);

  bb.getActiveSquares(cs);

  CHECK_EQUAL(1, cs.count());
  CHECK(cs.contains(Square(A, ONE)));
}

//--------------------------------------------------------------------------------------------
TEST(BitBoardTest, getActiveSquaresNoSquare)
{
  SquaresList cs;
  BitBoard bb(0);

  bb.getActiveSquares(cs);

  CHECK_EQUAL(0, cs.count());
}

//--------------------------------------------------------------------------------------------
TEST(BitBoardTest, buildFromBoardValue)
{
  BoardValue bv = 887766;
  BitBoard bb(bv);

  CHECK_EQUAL(bv, bb.getBoardValue());
}

//--------------------------------------------------------------------------------------------
TEST(BitBoardTest, buildFromHex)
{
  BitBoard bb("0xFF000000000000FF");

  CHECK_EQUAL(0xFF000000000000FF, bb.getBoardValue());
}

//--------------------------------------------------------------------------------------------
TEST(BitBoardTest, buildFromStringMaxUint64)
{
  BitBoard bb("18446744073709551615");

  CHECK_EQUAL(0xFFFFFFFFFFFFFFFF, bb.getBoardValue());
}

//--------------------------------------------------------------------------------------------
TEST(BitBoardTest, buildFromString)
{
  BitBoard bb("1234");

  CHECK_EQUAL(1234, bb.getBoardValue());
}

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
TEST(BitBoardTest, isBitSetSetAt63)
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
