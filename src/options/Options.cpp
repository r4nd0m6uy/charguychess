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

//--------------------------------------------------------------------------------------------
Options::Options()
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

  parseUciOptions("black", m_uciOptions.getBlackOptions(), cfg);
  parseUciOptions("white", m_uciOptions.getWhiteOptions(), cfg);
  parseUciOptions("hint", m_uciOptions.getHintOptions(), cfg);

  return 0;
}

//--------------------------------------------------------------------------------------------
UciOptions& Options::getUciOptions()
{
  return m_uciOptions;
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
