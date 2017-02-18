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
#ifndef _CGC_SQUARES_LIST_HPP_
#define _CGC_SQUARES_LIST_HPP_

#include <list>

#include "Square.hpp"

namespace cgc {

/**
 * \brief Hold a list of legal moves form a given square
 */
class SquaresList
{
public:
  SquaresList();
  ~SquaresList();

  void clear();
  void add(const Square& square);
  bool contains(const Square& square);
  int count() const;

private:
  std::list<Square> m_squaresList;
};

}       // namespace
#endif  // _CGC_SQUARES_LIST_HPP_
