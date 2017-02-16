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
  BoardValue mask = ((BoardValue)1 << pos);
  return (m_bVal & mask) != 0;
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
