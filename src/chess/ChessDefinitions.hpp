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
#ifndef _CGC_BITBOARD_HPP_
#define _CGC_BITBOARD_HPP_

#include <cstdint>

namespace cgc {

/**
 * Occupied squares on the board as bitset:
 * MSB    ... LSB
 * A1,A2, ... H7,H8
 */
typedef uint64_t BitBoard;

enum Rank{
  ONE = 0,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  LAST_RANK = EIGHT
};

enum File{
  A = 0,
  B,
  C,
  D,
  E,
  F,
  G,
  H,
  LAST_FILE = H
};

enum Color
{
  WHITE,
  BLACK,
  NO_COLOR
};

enum Piece
{
  KING,
  QUEEN,
  ROOK,
  BISHOP,
  KNIGHT,
  PAWN,
  NO_PIECE
};

}       // namespace
#endif  // _CGC_BITBOARD_HPP_
