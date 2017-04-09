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
  static const std::string TAG_EVENT;
  static const std::string TAG_SITE;
  static const std::string TAG_DATE;
  static const std::string TAG_ROUND;
  static const std::string TAG_WHITE;
  static const std::string TAG_BLACK;
  static const std::string TAG_RESULT;

  Pgn();
  ~Pgn();

  int savePgn(const GameHistory& gh) const;
  const std::string& getEvent() const;
  void setEvent(const std::string& e);
  const std::string& getSite() const;
  void setSite(const std::string& s);
  const std::string& getDate() const;
  void setDate(const std::string& d);
  const std::string& getRound() const;
  void setRound(const std::string& r);
  const std::string& getWhiteName() const;
  void setWhiteName(const std::string& w);
  const std::string& getBlackName() const;
  void setBlackName(const std::string& b);
  const std::string& getResult() const;
  const std::string& getPath() const;
  void setPath(const std::string& p);

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

std::ostream& operator<<(std::ostream& os, const Pgn& pgn);

}       // namespace
#endif  // _CGC_PGN_HPP_
