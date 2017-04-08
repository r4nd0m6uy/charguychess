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

const std::string Pgn::TAG_EVENT  = "Event";
const std::string Pgn::TAG_SITE   = "Site";
const std::string Pgn::TAG_DATE   = "Date";
const std::string Pgn::TAG_ROUND  = "Round";
const std::string Pgn::TAG_WHITE  = "White";
const std::string Pgn::TAG_BLACK  = "Black";
const std::string Pgn::TAG_RESULT = "Result";

//--------------------------------------------------------------------------------------------
Pgn::Pgn():
    m_event("?"),
    m_site("?"),
    m_date("?"),
    m_round("?"),
    m_whiteName("?"),
    m_blackName("?"),
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
  f << gh << " " << m_result << std::endl;

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
void Pgn::setEvent(const std::string& e)
{
  m_event = e;
}

//--------------------------------------------------------------------------------------------
const std::string& Pgn::getSite() const
{
  return m_site;
}

//--------------------------------------------------------------------------------------------
void Pgn::setSite(const std::string& s)
{
  m_site = s;
}

//--------------------------------------------------------------------------------------------
const std::string& Pgn::getDate() const
{
  return m_date;
}

//--------------------------------------------------------------------------------------------
void Pgn::setDate(const std::string& d)
{
  // XXX Validation?
  m_date = d;
}

//--------------------------------------------------------------------------------------------
const std::string& Pgn::getRound() const
{
  return m_round;
}

//--------------------------------------------------------------------------------------------
void Pgn::setRound(const std::string& r)
{
  m_round = r;
}

//--------------------------------------------------------------------------------------------
const std::string& Pgn::getWhiteName() const
{
  return m_whiteName;
}

//--------------------------------------------------------------------------------------------
void Pgn::setWhiteName(const std::string& w)
{
  m_whiteName = w;
}

//--------------------------------------------------------------------------------------------
const std::string& Pgn::getBlackName() const
{
  return m_blackName;
}

//--------------------------------------------------------------------------------------------
void Pgn::setBlackName(const std::string& b)
{
  m_blackName = b;
}
//--------------------------------------------------------------------------------------------
const std::string& Pgn::getResult() const
{
  return m_result;
}

//--------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Pgn& pgn)
{
  os << "[" << Pgn::TAG_EVENT << " \"" << pgn.getEvent() << "\"]" << std::endl;
  os << "[" << Pgn::TAG_SITE << " \"" << pgn.getSite() << "\"]" << std::endl;
  os << "[" << Pgn::TAG_DATE << " \"" << pgn.getDate() << "\"]" << std::endl;
  os << "[" << Pgn::TAG_ROUND << " \"" << pgn.getRound() << "\"]" << std::endl;
  os << "[" << Pgn::TAG_WHITE << " \"" << pgn.getWhiteName() << "\"]" << std::endl;
  os << "[" << Pgn::TAG_BLACK << " \"" << pgn. getBlackName() << "\"]" << std::endl;
  os << "[" << Pgn::TAG_RESULT << " \"" << pgn.getResult() << "\"]";

  return os;
}

}       // namespace
