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
#ifndef _CGC_BIT_BOARD_HPP_
#define _CGC_BIT_BOARD_HPP_

#include <string>

#include "BoardValue.hpp"

namespace cgc {

/**
 * \brief A class to work with the chess hardware bitset
 */
class BitBoard
{
public:
  BitBoard();
  virtual ~BitBoard();

  void setBoardValue(BoardValue bv);
  BoardValue getBoardValue() const;
  bool isBitSet(unsigned int pos) const;
  std::string toBoardString() const;

private:
  BoardValue m_bVal;
};

}       // namespace
#endif  // _CGC_BIT_BOARD_HPP_
