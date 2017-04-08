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

  f << *this << std::endl;
  f << std::endl;
  f << gh << std::endl;

  f.close();

  // FXME: stream error?

  return 0;
}

//--------------------------------------------------------------------------------------------
const std::string& Pgn::getEvent() const
{
  return m_event;
}

//--------------------------------------------------------------------------------------------
const std::string& Pgn::getSite() const
{
  return m_site;
}

//--------------------------------------------------------------------------------------------
const std::string& Pgn::getDate() const
{
  return m_date;
}

//--------------------------------------------------------------------------------------------
const std::string& Pgn::getRound() const
{
  return m_round;
}

//--------------------------------------------------------------------------------------------
const std::string& Pgn::getWhiteName() const
{
  return m_whiteName;
}

//--------------------------------------------------------------------------------------------
const std::string& Pgn::getBlackName() const
{
  return m_blackName;
}

//--------------------------------------------------------------------------------------------
const std::string& Pgn::getResult() const
{
  return m_result;
}

//--------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Pgn& pgn)
{
  os << "[Event \"" << pgn.getEvent() << "\"]" << std::endl;
  os << "[Site \"" << pgn.getSite() << "\"]" << std::endl;
  os << "[Date \"" << pgn.getDate() << "\"]" << std::endl;
  os << "[Round \"" << pgn.getRound() << "\"]" << std::endl;
  os << "[White \"" << pgn.getWhiteName() << "\"]" << std::endl;
  os << "[Black \"" << pgn. getBlackName() << "\"]" << std::endl;
  os << "[Result \"" << pgn.getResult() << "\"]";

  return os;
}

}       // namespace
