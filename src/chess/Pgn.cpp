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
#include <string.h>
#include <errno.h>

#include <fstream>

#include "../logging/LogMacros.hpp"
#include "Pgn.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
Pgn::Pgn():
    m_event("Casual game"),
    m_site("Fribourg, Fribourg Switzerland"),
    m_date("??"),
    m_round("1"),
    m_whiteName("White player"),
    m_blackName("Black player"),
    m_result("*"),
    m_filePath("game.pgn")
{
}

//--------------------------------------------------------------------------------------------
Pgn::~Pgn()
{
}

//--------------------------------------------------------------------------------------------
int Pgn::savePgn(const GameHistory& gh) const
{
  std::fstream f;

  f.open(m_filePath, std::ios::out | std::ios::trunc);
  if(!f.is_open())
  {
    LOGER() << "Cannot open " << m_filePath << ": " << strerror(errno);
    return -1;
  }

  f << "[Event \"" << m_event << "\"]" << std::endl;
  f << "[Site \"" << m_site << "\"]" << std::endl;
  f << "[Date \"" << m_date << "\"]" << std::endl;
  f << "[Round \"" << m_round << "\"]" << std::endl;
  f << "[White \"" << m_whiteName << "\"]" << std::endl;
  f << "[Black \"" << m_blackName << "\"]" << std::endl;
  f << "[Result \"" << m_result << "\"]" << std::endl;
  f << std::endl;
  f << gh << std::endl;

  f.close();

  // FXME: stream error?

  return 0;
}

}       // namespace
