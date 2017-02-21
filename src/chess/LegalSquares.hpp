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
#ifndef _CGC_LEGAL_SQUARES_HPP_
#define _CGC_LEGAL_SQUARES_HPP_

#include <list>

#include "SquaresList.hpp"

namespace cgc {

/**
 * \brief Hold a list of legal moves form a given square
 */
class LegalSquares
{
public:
  LegalSquares(const Square& from);
  ~LegalSquares();

  const Square& getFrom() const;
  void clear();
  void add(const Square& square);
  bool contains(const Square& square);
  bool contains(File f, Rank r);
  int count() const;
  const SquaresList& getSquaresList();

private:
  Square m_from;
  SquaresList m_legalSquares;
};

}       // namespace
#endif  // _CGC_LEGAL_SQUARES_HPP_
