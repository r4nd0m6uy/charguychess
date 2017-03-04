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
#include "CastleStatus.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
CastleStatus::CastleStatus():
    m_canCastleQueenSide(true),
    m_canCastleKingSide(true)
{
}

//--------------------------------------------------------------------------------------------
CastleStatus::~CastleStatus()
{
}

//--------------------------------------------------------------------------------------------
bool CastleStatus::canCastleQueenSide() const
{
  return m_canCastleQueenSide;
}

//--------------------------------------------------------------------------------------------
void CastleStatus::setCanCastleQueenSide(bool canCastle)
{
  m_canCastleQueenSide = canCastle;
}

//--------------------------------------------------------------------------------------------
bool CastleStatus::canCastleKingSide() const
{
  return m_canCastleKingSide;
}

//--------------------------------------------------------------------------------------------
void CastleStatus::setCanCastleKingSide(bool canCastle)
{
  m_canCastleKingSide = canCastle;
}

}       // namespace
