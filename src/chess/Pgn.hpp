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
#ifndef _CGC_PGN_HPP_
#define _CGC_PGN_HPP_

#include "GameHistory.hpp"

namespace cgc {

/**
 * \brief Write a game history into a PGN file
 */
class Pgn
{
public:
  Pgn();
  ~Pgn();

  int savePgn(const GameHistory& gh) const;

private:
  std::string m_event;
  std::string m_site;
  std::string m_date;   // XXX: Switch to date object?
  std::string m_round;
  std::string m_whiteName;
  std::string m_blackName;
  std::string m_result;
  std::string m_filePath;
};

}       // namespace
#endif  // _CGC_PGN_HPP_
