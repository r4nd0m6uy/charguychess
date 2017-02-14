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

  const PlayerPiece& getPiece(File f, Rank r) const;

private:
  typedef std::vector< std::vector<PlayerPiece> > BoardPieces;
  BoardPieces m_boardPieces;
};

}       // namespace
#endif  // _CGC_BOARD_HPP_
