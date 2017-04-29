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
#include "../logging/LogMacros.hpp"
#include "Options.hpp"

namespace cgc {

const Options::PlayerType Options::DEFAULT_WHITE_PLAYER_TYPE  = Options::HUMAN;
const Options::PlayerType Options::DEFAULT_BLACK_PLAYER_TYPE  = Options::UCI;

//--------------------------------------------------------------------------------------------
Options::Options():
    m_whitePt(DEFAULT_WHITE_PLAYER_TYPE),
    m_blackPt(DEFAULT_BLACK_PLAYER_TYPE)
{
}

//--------------------------------------------------------------------------------------------
Options::~Options()
{
}

//--------------------------------------------------------------------------------------------
int Options::parseOptions(const std::string file)
{
  libconfig::Config cfg;
  std::string stringOption;

  try
  {
    cfg.readFile(file.c_str());
  }
  catch(const libconfig::ParseException& ex)
  {
    LOGER() << "Cannot parse configuration " << file << " on line " << ex.getLine() << ": "
        << ex.getError();
    return -1;
  }
  catch(const std::exception& ex)
  {
    LOGER() << "Cannot parse configuration " << file << ": " << ex.what();
    return -1;
  }

  if(cfg.lookupValue("uci.path", stringOption))
  {
    LOGDB() << "Using UCI engine path " << stringOption;
    m_uciOptions.setUciPath(stringOption);
  }

  parsePlayerType("white", m_whitePt, cfg);
  parsePlayerType("black", m_blackPt, cfg);
  parseUciOptions("black", m_uciOptions.getBlackOptions(), cfg);
  parseUciOptions("white", m_uciOptions.getWhiteOptions(), cfg);
  parseUciOptions("hint", m_uciOptions.getHintOptions(), cfg);

  return 0;
}

//--------------------------------------------------------------------------------------------
Options::PlayerType Options::getWhitePlayerType() const
{
  return m_whitePt;
}

//--------------------------------------------------------------------------------------------
Options::PlayerType Options::getBlackPlayerType() const
{
  return m_blackPt;
}

//--------------------------------------------------------------------------------------------
UciOptions& Options::getUciOptions()
{
  return m_uciOptions;
}

//--------------------------------------------------------------------------------------------
void Options::parsePlayerType(const std::string& color, PlayerType& pt, libconfig::Config& c)
{
  std::string stringOption;

  if(c.lookupValue("players." + color, stringOption))
  {
    if(stringOption == "human")
    {
      LOGDB() << "Using human for " << color << " player";
      pt = HUMAN;
    }
    else if(stringOption == "uci")
    {
      LOGDB() << "Using uci engine for " << color << " player";
      pt = UCI;
    }
    else
      LOGWA() << "Invalid player type for " << color << ": " << stringOption;
  }
}

//--------------------------------------------------------------------------------------------
void Options::parseUciOptions(const std::string& color, UciPlayerOptions& po,
    libconfig::Config& c)
{
  std::string stringOption;
  int intOption;

  if(c.lookupValue("uci." + color + ".mode", stringOption))
  {
    if(stringOption == "depth")
    {
      LOGDB() << "Using UCI depth mode for " << color;
      po.setSearchMode(UciPlayerOptions::DEPTH);
    }
    else if(stringOption == "time")
    {
      LOGDB() << "Using UCI time limit mode for " << color;
      po.setSearchMode(UciPlayerOptions::TIME_LIMIT);
    }
    else
      LOGWA() << "Invalid UCI mode for " << color << ": " << stringOption;
  }

  if(c.lookupValue("uci." + color + ".depth", intOption))
  {
    LOGDB() << "Using UCI depth of " << intOption << " for " << color;
    po.setSearchMaxDepth(intOption);
  }

  if(c.lookupValue("uci." + color + ".time", intOption))
  {
    LOGDB() << "Using UCI time limit of " << intOption << " ms for " << color;
    po.setSearchTimeout(intOption);
  }
}
}       // namespace
