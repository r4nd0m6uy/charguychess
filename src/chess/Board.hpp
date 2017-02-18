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
#ifndef _CGC_BOARD_HPP_
#define _CGC_BOARD_HPP_

#include <vector>

#include "ChessDefinitions.hpp"
#include "Square.hpp"
#include "PlayerPiece.hpp"

namespace cgc {

/**
 * \brief Represent a chess board at a given point of the game
 */
class Board
{
public:
  Board();
  ~Board();

  void clear();
  void clear(const Square& s);
  const PlayerPiece& getPiece(const Square& s) const;
  void setPiece(const PlayerPiece& p, const Square& s);
  bool isEmpty(const Square& s) const;
  Color getPieceColor(const Square& s) const;
  PieceType getPieceType(const Square& s) const;

private:
  typedef std::vector< std::vector<PlayerPiece> > BoardPieces;
  BoardPieces m_boardPieces;
  PlayerPiece m_invalidPiece;
};

}       // namespace
#endif  // _CGC_BOARD_HPP_
