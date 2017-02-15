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
#include "Square.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
Square::Square():
    m_file(INVALID_FILE),
    m_rank(INVALID_RANK)
{
}

//--------------------------------------------------------------------------------------------
Square::Square(const std::string& str):
    m_file(INVALID_FILE),
    m_rank(INVALID_RANK)
{
  if(str.size() >= 2 &&
      str[0] >= 'a' && str[0] <= 'h' &&
      str[1] >= '1' && str[1] <= '8')
  {
    m_file = static_cast<File>(str[0] - 'a');
    m_rank = static_cast<Rank>(str[1] - '1');
  }
}

//--------------------------------------------------------------------------------------------
Square::Square(File f, Rank r):
    m_file(f),
    m_rank(r)
{
}

//--------------------------------------------------------------------------------------------
Square::~Square()
{
}

//--------------------------------------------------------------------------------------------
File Square::getFile() const
{
  return m_file;
}

//--------------------------------------------------------------------------------------------
void Square::setFile(File f)
{
  m_file = f;
}

//--------------------------------------------------------------------------------------------
Rank Square::getRank() const
{
  return m_rank;
}

//--------------------------------------------------------------------------------------------
void Square::setRank(Rank r)
{
  m_rank = r;
}

//--------------------------------------------------------------------------------------------
bool Square::isValid()
{
  return m_file != INVALID_FILE &&
      m_rank != INVALID_RANK ;
}

//--------------------------------------------------------------------------------------------
bool Square::operator==(const Square& rhs) const
{
  return rhs.getFile() == this->getFile() &&
      rhs.getRank() == this->getRank();
}

}       // namespace
