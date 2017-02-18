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
#ifndef _CGC_SQUARE_HPP_
#define _CGC_SQUARE_HPP_

#include <string>

#include "ChessDefinitions.hpp"

namespace cgc {

/**
 * \brief Represent a square on the board
 */
class Square
{
public:
  Square();
  Square(const std::string& str);
  Square(File f, Rank r);
  ~Square();

  File getFile() const;
  void setFile(File f);
  Rank getRank() const;
  void setRank(Rank r);
  bool isValid() const;

  bool operator==(const Square& rhs) const;
  bool operator!=(const Square& rhs) const;

private:
  File m_file;
  Rank m_rank;
};

std::ostream& operator<<(std::ostream& os, const Square& s);

}       // namespace
#endif  // _CGC_SQUARE_HPP_
