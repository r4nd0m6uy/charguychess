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
#include "PlayerPiece.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
PlayerPiece::PlayerPiece():
    m_color(NO_COLOR),
    m_piece(NO_PIECE)
{
}

//--------------------------------------------------------------------------------------------
PlayerPiece::PlayerPiece(Color c, Piece p):
    m_color(c),
    m_piece(p)
{
}

//--------------------------------------------------------------------------------------------
PlayerPiece::~PlayerPiece()
{
}

//--------------------------------------------------------------------------------------------
Color PlayerPiece::getColor()
{
  return m_color;
}

//--------------------------------------------------------------------------------------------
Piece PlayerPiece::getPiece()
{
  return m_piece;
}

}       // namespace
