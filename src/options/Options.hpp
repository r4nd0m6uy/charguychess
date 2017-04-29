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
#ifndef _CGC_OPTIONS_HPP_
#define _CGC_OPTIONS_HPP_

#include <libconfig.h++>

#include "UciOptions.hpp"

namespace cgc {

/**
 * \brief Holds options of the game
 */
class Options
{
public:
  enum PlayerType{
    HUMAN,
    UCI
  };

  static const PlayerType DEFAULT_WHITE_PLAYER_TYPE;
  static const PlayerType DEFAULT_BLACK_PLAYER_TYPE;

  Options();
  ~Options();

  int parseOptions(const std::string file);
  PlayerType getWhitePlayerType() const;
  PlayerType getBlackPlayerType() const;
  UciOptions& getUciOptions();

private:
  PlayerType m_whitePt;
  PlayerType m_blackPt;
  UciOptions m_uciOptions;

  static void parseUciOptions(const std::string& color, UciPlayerOptions& po,
      libconfig::Config& c);
  static void parsePlayerType(const std::string& color, PlayerType& pt, libconfig::Config& c);
};

}       // namespace
#endif  // _CGC_OPTIONS_HPP_
