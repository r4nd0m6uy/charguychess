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

#include "chess/Move.hpp"

using namespace cgc;

//--------------------------------------------------------------------------------------------
TEST_GROUP(MoveTest)
{
  TEST_SETUP()
  {
  }

  TEST_TEARDOWN()
  {
  }
};

//--------------------------------------------------------------------------------------------
TEST(MoveTest, toStringQueenSideCastling)
{
  std::string strMove = "O-O-O";
  Move m;

  m.setQueenSideCastling(true);

  STRCMP_EQUAL(strMove.c_str(), m.toString().c_str());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, toStringKingSideCastling)
{
  std::string strMove = "O-O";
  Move m;

  m.setKingSideCastling(true);

  STRCMP_EQUAL(strMove.c_str(), m.toString().c_str());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, parseStringBishopPromotional)
{
  std::string strMove = "e2e1=B";
  Move m;

  CHECK(m.parseString(strMove));
  CHECK_EQUAL(BISHOP, m.getPromotion());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, parseStringKnightPromotional)
{
  std::string strMove = "e2e1=N";
  Move m;

  CHECK(m.parseString(strMove));
  CHECK_EQUAL(KNIGHT, m.getPromotion());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, parseStringRookPromotional)
{
  std::string strMove = "e2e1=R";
  Move m;

  CHECK(m.parseString(strMove));
  CHECK_EQUAL(ROOK, m.getPromotion());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, parseStringQueenPromotional)
{
  std::string strMove = "e2e1=Q";
  Move m;

  CHECK(m.parseString(strMove));
  CHECK(m.hasPromotion());
  CHECK_EQUAL(QUEEN, m.getPromotion());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, toStringKnightPromotion)
{
  std::string strMove = "c8=N";
  Move m(PAWN, Square(C, SEVEN), Square(C, EIGHT));

  m.setPromotion(KNIGHT);

  STRCMP_EQUAL(strMove.c_str(), m.toString().c_str());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, setPawnPromotion)
{
  Move m;

  m.setPromotion(PAWN);

  CHECK_FALSE(m.hasPromotion());
  CHECK_EQUAL(NO_PIECE, m.getPromotion());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, setKingPromotion)
{
  Move m;

  m.setPromotion(KING);

  CHECK_FALSE(m.hasPromotion());
  CHECK_EQUAL(NO_PIECE, m.getPromotion());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, getQueenPromotion)
{
  Move m;

  m.setPromotion(QUEEN);

  CHECK_EQUAL(QUEEN, m.getPromotion());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, setRookPromotion)
{
  Move m;

  m.setPromotion(ROOK);

  CHECK(m.hasPromotion());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, defaultConstructorNotPromotion)
{
  Move m;

  CHECK_FALSE(m.hasPromotion());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, toStringKnightCheckMate)
{
  std::string strMove = "Nc3#";
  Move m(KNIGHT, Square(C, TWO), Square(C, THREE));

  m.setMate(true);
  m.setCheck(true);

  STRCMP_EQUAL(strMove.c_str(), m.toString().c_str());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, toStringKnightMate)
{
  std::string strMove = "Nc3#";
  Move m(KNIGHT, Square(C, TWO), Square(C, THREE));

  m.setMate(true);

  STRCMP_EQUAL(strMove.c_str(), m.toString().c_str());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, toStringKnightCheck)
{
  std::string strMove = "Nc3+";
  Move m(KNIGHT, Square(C, TWO), Square(C, THREE));

  m.setCheck(true);

  STRCMP_EQUAL(strMove.c_str(), m.toString().c_str());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, toStringPawnCapture)
{
  std::string strMove = "cxd3";
  Move m(PAWN, Square(C, TWO), Square(D, THREE));

  m.setIsCapture(true);

  STRCMP_EQUAL(strMove.c_str(), m.toString().c_str());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, toStringKnightCapture)
{
  std::string strMove = "Nxc3";
  Move m(KNIGHT, Square(C, TWO), Square(C, THREE));

  m.setIsCapture(true);

  STRCMP_EQUAL(strMove.c_str(), m.toString().c_str());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, toStringMoveWithKnight)
{
  std::string strMove = "Nc3";
  Move m(KNIGHT, Square(C, TWO), Square(C, THREE));

  STRCMP_EQUAL(strMove.c_str(), m.toString().c_str());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, toStringMoveWithBishop)
{
  std::string strMove = "Bc3";
  Move m(BISHOP, Square(C, TWO), Square(C, THREE));

  STRCMP_EQUAL(strMove.c_str(), m.toString().c_str());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, toStringMoveWithRook)
{
  std::string strMove = "Rc3";
  Move m(ROOK, Square(C, TWO), Square(C, THREE));

  STRCMP_EQUAL(strMove.c_str(), m.toString().c_str());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, toStringMoveWithQueen)
{
  std::string strMove = "Qc3";
  Move m(QUEEN, Square(C, TWO), Square(C, THREE));

  STRCMP_EQUAL(strMove.c_str(), m.toString().c_str());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, toStringMoveWithKing)
{
  std::string strMove = "Kc3";
  Move m(KING, Square(C, TWO), Square(C, THREE));

  STRCMP_EQUAL(strMove.c_str(), m.toString().c_str());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, toStringMoveWithPawn)
{
  std::string strMove = "c3";
  Move m(Square(C, TWO), Square(C, THREE));

  m.setWho(PAWN);
  STRCMP_EQUAL(strMove.c_str(), m.toString().c_str());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, toStringBareMove)
{
  std::string strMove = "c2c3";
  Move m(Square(C, TWO), Square(C, THREE));

  STRCMP_EQUAL(strMove.c_str(), m.toString().c_str());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, fromValidString)
{
  Move m("a1a2");

  CHECK(m.isValid());
  CHECK_EQUAL(A, m.getFrom().getFile());
  CHECK_EQUAL(ONE, m.getFrom().getRank());
  CHECK_EQUAL(A, m.getTo().getFile());
  CHECK_EQUAL(TWO, m.getTo().getRank());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, fromInvalidString)
{
  Move m("abcde");

  CHECK_FALSE(m.isValid());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, invalidMoveToSameSquareSquare)
{
  Move m(Square(A, ONE), Square(A, ONE));

  CHECK_FALSE(m.isValid());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, fromValidSquare)
{
  Move m(Square(A, ONE), Square(B, TWO));

  CHECK(m.isValid());
}

//--------------------------------------------------------------------------------------------
TEST(MoveTest, defaultConstructor)
{
  Move m;

  CHECK_FALSE(m.isValid());
}
