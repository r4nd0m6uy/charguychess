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
#include <cassert>

#include "../logging/LogMacros.hpp"
#include "Board.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
Board::Board()
{
  initialPosition();
}

//--------------------------------------------------------------------------------------------
Board::~Board()
{
}

//--------------------------------------------------------------------------------------------
void Board::clear()
{
  m_boardPieces =
      BoardPieces(LAST_FILE + 1, std::vector<PlayerPiece>(LAST_RANK + 1));
}

//--------------------------------------------------------------------------------------------
void Board::clear(const Square& s)
{
  setPiece(PlayerPiece(NO_COLOR, NO_PIECE), s);
}

//--------------------------------------------------------------------------------------------
void Board::clear(File f, Rank r)
{
  this->clear(Square(f, r));
}

//--------------------------------------------------------------------------------------------
void Board::initialPosition()
{
  clear();

  // White player initial position
  this->setPiece(PlayerPiece(WHITE, ROOK),    Square(A, ONE));
  this->setPiece(PlayerPiece(WHITE, KNIGHT),  Square(B, ONE));
  this->setPiece(PlayerPiece(WHITE, BISHOP),  Square(C, ONE));
  this->setPiece(PlayerPiece(WHITE, QUEEN),   Square(D, ONE));
  this->setPiece(PlayerPiece(WHITE, KING),    Square(E, ONE));
  this->setPiece(PlayerPiece(WHITE, BISHOP),  Square(F, ONE));
  this->setPiece(PlayerPiece(WHITE, KNIGHT),  Square(G, ONE));
  this->setPiece(PlayerPiece(WHITE, ROOK),    Square(H, ONE));
  this->setPiece(PlayerPiece(WHITE, PAWN),    Square(A, TWO));
  this->setPiece(PlayerPiece(WHITE, PAWN),    Square(B, TWO));
  this->setPiece(PlayerPiece(WHITE, PAWN),    Square(C, TWO));
  this->setPiece(PlayerPiece(WHITE, PAWN),    Square(D, TWO));
  this->setPiece(PlayerPiece(WHITE, PAWN),    Square(E, TWO));
  this->setPiece(PlayerPiece(WHITE, PAWN),    Square(F, TWO));
  this->setPiece(PlayerPiece(WHITE, PAWN),    Square(G, TWO));
  this->setPiece(PlayerPiece(WHITE, PAWN),    Square(H, TWO));

  // Black player initial position
  this->setPiece(PlayerPiece(BLACK, PAWN),    Square(A, SEVEN));
  this->setPiece(PlayerPiece(BLACK, PAWN),    Square(B, SEVEN));
  this->setPiece(PlayerPiece(BLACK, PAWN),    Square(C, SEVEN));
  this->setPiece(PlayerPiece(BLACK, PAWN),    Square(D, SEVEN));
  this->setPiece(PlayerPiece(BLACK, PAWN),    Square(E, SEVEN));
  this->setPiece(PlayerPiece(BLACK, PAWN),    Square(F, SEVEN));
  this->setPiece(PlayerPiece(BLACK, PAWN),    Square(G, SEVEN));
  this->setPiece(PlayerPiece(BLACK, PAWN),    Square(H, SEVEN));
  this->setPiece(PlayerPiece(BLACK, ROOK),    Square(A, EIGHT));
  this->setPiece(PlayerPiece(BLACK, KNIGHT),  Square(B, EIGHT));
  this->setPiece(PlayerPiece(BLACK, BISHOP),  Square(C, EIGHT));
  this->setPiece(PlayerPiece(BLACK, QUEEN),   Square(D, EIGHT));
  this->setPiece(PlayerPiece(BLACK, KING),    Square(E, EIGHT));
  this->setPiece(PlayerPiece(BLACK, BISHOP),  Square(F, EIGHT));
  this->setPiece(PlayerPiece(BLACK, KNIGHT),  Square(G, EIGHT));
  this->setPiece(PlayerPiece(BLACK, ROOK),    Square(H, EIGHT));
}

//--------------------------------------------------------------------------------------------
const PlayerPiece& Board::getPiece(const Square& s) const
{
  // Precondition
  if(!s.isValid())
  {
    LOGER() << "Getting a piece on an invalid square!";
    assert(0);
    return m_invalidPiece;
  }

  return m_boardPieces[s.getFile()][s.getRank()];
}

//--------------------------------------------------------------------------------------------
void Board::setPiece(const PlayerPiece& p, const Square& s)
{
  if(!s.isValid())
  {
    LOGER() << "Setting a piece on an invalid square!";
    assert(0);
    return;
  }

  m_boardPieces[s.getFile()][s.getRank()] = p;
}

//--------------------------------------------------------------------------------------------
void Board::setPiece(Color c, PieceType p, File f, Rank r)
{
  this->setPiece(PlayerPiece(c, p), Square(f, r));
}

//--------------------------------------------------------------------------------------------
bool Board::isEmpty(const Square& s) const
{
  return this->getPieceColor(s) == NO_COLOR;
}

//--------------------------------------------------------------------------------------------
Color Board::getPieceColor(const Square& s) const
{
  return this->getPiece(s).getColor();
}

//--------------------------------------------------------------------------------------------
Color Board::getPieceColor(File f, Rank r) const
{
  return this->getPieceColor(Square(f, r));
}

//--------------------------------------------------------------------------------------------
PieceType Board::getPieceType(const Square& s) const
{
  return this->getPiece(s).getType();
}

//--------------------------------------------------------------------------------------------
PieceType Board::getPieceType(File f, Rank r) const
{
  return this->getPiece(Square(f, r)).getType();
}

}       // namespace
