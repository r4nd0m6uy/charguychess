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
LegalSquares::LegalSquares(File f, Rank r):
    m_from(f, r)
{
}

//--------------------------------------------------------------------------------------------
LegalSquares::~LegalSquares()
{
}

//--------------------------------------------------------------------------------------------
const Square& LegalSquares::getFrom() const
{
  return m_from;
}

//--------------------------------------------------------------------------------------------
void LegalSquares::clear()
{
  m_legalSquares.clear();
}

//--------------------------------------------------------------------------------------------
void LegalSquares::add(const Square& square)
{
  m_legalSquares.add(square);
}

//--------------------------------------------------------------------------------------------
void LegalSquares::add(File f, Rank r)
{
  this->add(Square(f, r));
}

//--------------------------------------------------------------------------------------------
bool LegalSquares::contains(const Square& square) const
{
  return m_legalSquares.contains(square);
}

//--------------------------------------------------------------------------------------------
bool LegalSquares::contains(File f, Rank r) const
{
  return this->contains(Square(f, r));
}

//--------------------------------------------------------------------------------------------
int LegalSquares::count() const
{
  return m_legalSquares.count();
}

//--------------------------------------------------------------------------------------------
const SquaresList& LegalSquares::getSquaresList()
{
  return m_legalSquares;
}

}       // namespace
