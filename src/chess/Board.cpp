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
#include "Board.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
Board::Board():
    m_boardPieces(LAST_FILE + 1, std::vector<PlayerPiece>(LAST_RANK + 1))
{
  // White player initial position
  m_boardPieces[ONE][A] = PlayerPiece(WHITE, ROOK);
  m_boardPieces[ONE][B] = PlayerPiece(WHITE, KNIGHT);
  m_boardPieces[ONE][C] = PlayerPiece(WHITE, BISHOP);
  m_boardPieces[ONE][D] = PlayerPiece(WHITE, QUEEN);
  m_boardPieces[ONE][E] = PlayerPiece(WHITE, KING);
  m_boardPieces[ONE][F] = PlayerPiece(WHITE, BISHOP);
  m_boardPieces[ONE][G] = PlayerPiece(WHITE, KNIGHT);
  m_boardPieces[ONE][H] = PlayerPiece(WHITE, ROOK);
  m_boardPieces[TWO][A] = PlayerPiece(WHITE, PAWN);
  m_boardPieces[TWO][B] = PlayerPiece(WHITE, PAWN);
  m_boardPieces[TWO][C] = PlayerPiece(WHITE, PAWN);
  m_boardPieces[TWO][D] = PlayerPiece(WHITE, PAWN);
  m_boardPieces[TWO][E] = PlayerPiece(WHITE, PAWN);
  m_boardPieces[TWO][F] = PlayerPiece(WHITE, PAWN);
  m_boardPieces[TWO][G] = PlayerPiece(WHITE, PAWN);
  m_boardPieces[TWO][H] = PlayerPiece(WHITE, PAWN);
}

//--------------------------------------------------------------------------------------------
Board::~Board()
{
}

//--------------------------------------------------------------------------------------------
const PlayerPiece& Board::getPiece(File f, Rank r) const
{
  return m_boardPieces[r][f];
}

}       // namespace
