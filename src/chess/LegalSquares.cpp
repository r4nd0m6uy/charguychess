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
#include <algorithm>

#include "LegalSquares.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
LegalSquares::LegalSquares(const Square& from):
    m_from(from)
{
}

//--------------------------------------------------------------------------------------------
LegalSquares::~LegalSquares()
{
}

//--------------------------------------------------------------------------------------------
void LegalSquares::clear()
{
  m_legalSquares.clear();
}

//--------------------------------------------------------------------------------------------
void LegalSquares::addLegalSquare(const Square& square)
{
  m_legalSquares.push_back(square);
}

//--------------------------------------------------------------------------------------------
bool LegalSquares::contains(const Square& square)
{
  return std::find(m_legalSquares.begin(), m_legalSquares.end(), square) !=
      m_legalSquares.end();
}

//--------------------------------------------------------------------------------------------
const Square& LegalSquares::getFrom() const
{
  return m_from;
}

//--------------------------------------------------------------------------------------------
int LegalSquares::getLegalSquaresCount() const
{
  return m_legalSquares.size();
}

}       // namespace