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
#include <sstream>
#include "Move.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
Move::Move():
    m_who(NO_PIECE)
{
}

//--------------------------------------------------------------------------------------------
Move::Move(const std::string& str):
    m_who(NO_PIECE)
{
  if(str.size() >= 4)
  {
    m_from = Square(str.substr(0, 2));
    m_to = Square(str.substr(2, 2));
  }
}

//--------------------------------------------------------------------------------------------
Move::Move(const Square& from, const Square& to):
    m_from(from),
    m_to(to),
    m_who(NO_PIECE)
{
}

//--------------------------------------------------------------------------------------------
Move::Move(PieceType who, const Square& from, const Square& to):
  m_from(from),
  m_to(to),
  m_who(who)
{
}

//--------------------------------------------------------------------------------------------
Move::~Move()
{
}

//--------------------------------------------------------------------------------------------
const Square& Move::getFrom() const
{
  return m_from;
}

//--------------------------------------------------------------------------------------------
const Square& Move::getTo() const
{
  return m_to;
}

//--------------------------------------------------------------------------------------------
PieceType Move::getWho() const
{
  return m_who;
}

//--------------------------------------------------------------------------------------------
void Move::setWho(PieceType who)
{
  m_who = who;
}

//--------------------------------------------------------------------------------------------
bool Move::isValid() const
{
  return m_from.isValid() &&
      m_to.isValid() &&
      m_from != m_to;
}

//--------------------------------------------------------------------------------------------
std::string Move::toString() const
{
  std::stringstream ss;

  if(m_who == NO_PIECE)
    ss << this->getFrom();
  else if(m_who != PAWN)
    ss << m_who;

  ss << this->getTo();

  return ss.str();
}

//--------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Move& m)
{
  os << m.toString();
  return os;
}

}       // namespace
