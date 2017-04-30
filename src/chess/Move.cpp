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
    m_who(NO_PIECE),
    m_isCapture(false),
    m_isCheck(false),
    m_isMate(false),
    m_promotion(NO_PIECE),
    m_isKingSideCastling(false),
    m_isQueenSideCastling(false),
    m_isRankAmbiguous(false),
    m_isFileAmbiguous(false)
{
}

//--------------------------------------------------------------------------------------------
Move::Move(const std::string& str):
    m_who(NO_PIECE),
    m_isCapture(false),
    m_isCheck(false),
    m_isMate(false),
    m_promotion(NO_PIECE),
    m_isKingSideCastling(false),
    m_isQueenSideCastling(false),
    m_isRankAmbiguous(false),
    m_isFileAmbiguous(false)
{
  parseString(str);
}

//--------------------------------------------------------------------------------------------
Move::Move(const Square& from, const Square& to):
    m_from(from),
    m_to(to),
    m_who(NO_PIECE),
    m_isCapture(false),
    m_isCheck(false),
    m_isMate(false),
    m_promotion(NO_PIECE),
    m_isKingSideCastling(false),
    m_isQueenSideCastling(false),
    m_isRankAmbiguous(false),
    m_isFileAmbiguous(false)
{
}

//--------------------------------------------------------------------------------------------
Move::Move(File fFrom, Rank rFrom, File fTo, Rank rTo):
    m_from(fFrom, rFrom),
    m_to(fTo, rTo),
    m_who(NO_PIECE),
    m_isCapture(false),
    m_isCheck(false),
    m_isMate(false),
    m_promotion(NO_PIECE),
    m_isKingSideCastling(false),
    m_isQueenSideCastling(false),
    m_isRankAmbiguous(false),
    m_isFileAmbiguous(false)
{
}

//--------------------------------------------------------------------------------------------
Move::Move(PieceType who, const Square& from, const Square& to):
    m_from(from),
    m_to(to),
    m_who(who),
    m_isCapture(false),
    m_isCheck(false),
    m_isMate(false),
    m_promotion(NO_PIECE),
    m_isKingSideCastling(false),
    m_isQueenSideCastling(false),
    m_isRankAmbiguous(false),
    m_isFileAmbiguous(false)
{
}

//--------------------------------------------------------------------------------------------
Move::~Move()
{
}

//--------------------------------------------------------------------------------------------
bool Move::parseString(const std::string& s)
{
  if(s.size() >= 4)
  {
    m_from = Square(s.substr(0, 2));
    m_to = Square(s.substr(2, 2));

    // Check for promotion information
    if(s.size() >= 6)
    {
      if(s[4] != '=')
        return false;

      if(s[5] == 'Q')
        m_promotion = QUEEN;
      else if(s[5] == 'R')
        m_promotion = ROOK;
      else if(s[5] == 'N')
        m_promotion = KNIGHT;
      else if(s[5] == 'B')
        m_promotion = BISHOP;
      else
        return false;
    }

    // Promotional move from UCI engine
    else if(s.size() >= 5)
    {
      if(s[4] == 'q')
        m_promotion = QUEEN;
      else if(s[4] == 'r')
        m_promotion = ROOK;
      else if(s[4] == 'n')
        m_promotion = KNIGHT;
      else if(s[4] == 'b')
        m_promotion = BISHOP;
      else
        return false;}
  }

  return this->isValid();
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
  if(m_isQueenSideCastling ||
      m_isKingSideCastling)
    return true;

  return m_from.isValid() &&
      m_to.isValid() &&
      m_from != m_to;
}

//--------------------------------------------------------------------------------------------
bool Move::isCapture() const
{
  return m_isCapture;
}

//--------------------------------------------------------------------------------------------
void Move::setIsCapture(bool isCapture)
{
  m_isCapture = isCapture;
}

//--------------------------------------------------------------------------------------------
bool Move::isCheck() const
{
  return m_isCheck;
}

//--------------------------------------------------------------------------------------------
void Move::setCheck(bool isCheck)
{
  m_isCheck = isCheck;
}

//--------------------------------------------------------------------------------------------
bool Move::isMate() const
{
  return m_isMate;
}

//--------------------------------------------------------------------------------------------
void Move::setMate(bool isMate)
{
  m_isMate = isMate;
}

//--------------------------------------------------------------------------------------------
bool Move::hasPromotion() const
{
  return m_promotion != NO_PIECE;
}

//--------------------------------------------------------------------------------------------
PieceType Move::getPromotion() const
{
  return m_promotion;
}

//--------------------------------------------------------------------------------------------
void Move::setPromotion(PieceType p)
{
  if(p == KING ||
      p == PAWN)
    return;

  m_promotion = p;
}

//--------------------------------------------------------------------------------------------
bool Move::isKingSideCastling() const
{
  return m_isKingSideCastling;
}

//--------------------------------------------------------------------------------------------
void Move::setKingSideCastling(bool isCastling)
{
  m_isKingSideCastling = isCastling;
}

//--------------------------------------------------------------------------------------------
bool Move::isQueenSideCastling() const
{
  return m_isQueenSideCastling;
}

//--------------------------------------------------------------------------------------------
void Move::setQueenSideCastling(bool isCastling)
{
  m_isQueenSideCastling = isCastling;
}

//--------------------------------------------------------------------------------------------
void Move::setRankAmbiguous(bool isAmbiguous)
{
  m_isRankAmbiguous = isAmbiguous;
}

//--------------------------------------------------------------------------------------------
void Move::setFileAmbiguous(bool isAmbiguous)
{
  m_isFileAmbiguous = isAmbiguous;
}

//--------------------------------------------------------------------------------------------
std::string Move::toString() const
{
  std::stringstream ss;

  if(m_isKingSideCastling)
    return "O-O";
  else if(m_isQueenSideCastling)
    return "O-O-O";

  // Source piece
  if(m_who == NO_PIECE)
    ss << this->getFrom();
  else if(m_who != PAWN)
    ss << m_who;
  else if(m_who == PAWN && m_isCapture)
    ss << getFrom().getFile();

  // Ambiguty
  if(m_isFileAmbiguous)
    ss << getFrom().getFile();
  if(m_isRankAmbiguous)
    ss << getFrom().getRank();

  // Capture
  if(m_isCapture)
    ss << "x";

  // Destination square
  ss << this->getTo();

  // Promotion
  if(this->hasPromotion())
    ss << "=" << this->getPromotion();

  // Check / mate
  if(m_isCheck && !m_isMate)
    ss << "+";
  else if(m_isMate)
    ss << "#";

  return ss.str();
}

//--------------------------------------------------------------------------------------------
std::string Move::toUciString() const
{
  std::stringstream ss;

  ss << getFrom() << getTo();

  if(hasPromotion())
    ss << m_promotion;

  return ss.str();
}

//--------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Move& m)
{
  os << m.toString();
  return os;
}

}       // namespace
