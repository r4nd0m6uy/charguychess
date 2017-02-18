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
#include <stdlib.h>

#include "BitBoard.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
BitBoard::BitBoard():
    m_bVal(0)
{
}

//--------------------------------------------------------------------------------------------
BitBoard::BitBoard(BoardValue bv):
    m_bVal(bv)
{
}

//--------------------------------------------------------------------------------------------
BitBoard::BitBoard(const Board& b):
    m_bVal(0)
{
  for(File f = A ; f <= LAST_FILE ; ++f)
    for(Rank r = ONE ; r <= LAST_RANK ; ++r)
      if(!b.isEmpty(Square(f, r)))
        setBit(63 - f - (r * 8));
}

//--------------------------------------------------------------------------------------------
BitBoard::BitBoard(const std::string& value)
{
  setBoardValue(value);
}

//--------------------------------------------------------------------------------------------
BitBoard::~BitBoard()
{
}

//--------------------------------------------------------------------------------------------
void BitBoard::setBoardValue(BoardValue bv)
{
  m_bVal = bv;
}

//--------------------------------------------------------------------------------------------
void BitBoard::setBoardValue(const std::string& value)
{
  if(value[0] == '0' && value[1] == 'x')
    m_bVal = ::strtoul(&value.c_str()[2], nullptr, 16);
  else
    m_bVal = ::strtoul(value.c_str(), nullptr, 10);
}

//--------------------------------------------------------------------------------------------
BoardValue BitBoard::getBoardValue() const
{
  return m_bVal;
}

//--------------------------------------------------------------------------------------------
bool BitBoard::isBitSet(unsigned int pos) const
{
  return (m_bVal & ((BoardValue)1 << pos)) != 0;
}

//--------------------------------------------------------------------------------------------
void BitBoard::setBit(unsigned int pos)
{
  m_bVal |= (BoardValue)1 << pos;
}

//--------------------------------------------------------------------------------------------
void BitBoard::getActiveSquares(SquaresList& squares)
{
  for(unsigned int i = 0 ; i < 64 ; ++i)
  {
    if(isBitSet(i))
    {
      Rank r;
      File f = static_cast<File>(LAST_FILE - (i % 8));

      if(i < 8)
        r = EIGHT;
      else if(i < 16)
        r = SEVEN;
      else if(i < 24)
        r = SIX;
      else if(i < 32)
        r = FIVE;
      else if(i < 40)
        r = FOUR;
      else if(i < 48)
        r = THREE;
      else if(i < 56)
        r = TWO;
      else
        r = ONE;

      squares.add(Square(f, r));
    }
  }
}

//--------------------------------------------------------------------------------------------
void BitBoard::getChangedSquares(BoardValue newValue, SquaresList& squares)
{
  BitBoard masked(m_bVal ^  newValue);

  squares.clear();
  masked.getActiveSquares(squares);
}

//--------------------------------------------------------------------------------------------
std::string BitBoard::toBoardString() const
{
  std::string bStr;
  std::string rank;

  for(unsigned int i = 0; i < 64 ; ++i)
  {
    if(isBitSet(i))
      rank = "1" + rank;
    else
      rank = "0" + rank;

    if((i + 1) % 8 == 0)
    {
      if(i != 7)
        bStr += "\n";
      bStr = bStr + rank;
      rank = "";
    }
  }

  return bStr;
}

}       // namespace
