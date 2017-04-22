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
#ifndef _CGC_MOVE_HPP_
#define _CGC_MOVE_HPP_

#include "Square.hpp"

namespace cgc {

/**
 * \brief Represent a move
 */
class Move
{
public:
  Move();
  Move(const std::string& str);
  Move(const Square& from, const Square& to);
  Move(File fFrom, Rank rFrom, File fTo, Rank rTo);
  Move(PieceType who, const Square& from, const Square& to);
  ~Move();

  bool parseString(const std::string& s);
  const Square& getFrom() const;
  const Square& getTo() const;
  PieceType getWho() const;
  void setWho(PieceType who);
  bool isValid() const;
  bool isCapture() const;
  void setIsCapture(bool isCapture);
  bool isCheck() const;
  void setCheck(bool isCheck);
  bool isMate() const;
  void setMate(bool isMate);
  bool hasPromotion() const;
  PieceType getPromotion() const;
  void setPromotion(PieceType p);
  bool isKingSideCastling() const;
  void setKingSideCastling(bool isCastling);
  bool isQueenSideCastling() const;
  void setQueenSideCastling(bool isCastling);
  void setRankAmbiguous(bool isAmbiguous);
  void setFileAmbiguous(bool isAmbiguous);
  std::string toString() const;

private:
  Square m_from;
  Square m_to;
  PieceType m_who;
  bool m_isCapture;
  bool m_isCheck;
  bool m_isMate;
  PieceType m_promotion;
  bool m_isKingSideCastling;
  bool m_isQueenSideCastling;
  bool m_isRankAmbiguous;
  bool m_isFileAmbiguous;
};

std::ostream& operator<<(std::ostream& os, const Move& m);

}       // namespace
#endif  // _CGC_MOVE_HPP_
