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
#include "UciOptions.hpp"

namespace cgc {

const std::string UciOptions::DEFAULT_UCI_PATH  = "/usr/bin/stockfish";
const int UciOptions::DEFAULT_THREADS_COUNT     = 1;

//--------------------------------------------------------------------------------------------
UciOptions::UciOptions():
    m_uciPath(DEFAULT_UCI_PATH),
    m_threadsCount(DEFAULT_THREADS_COUNT)
{
}

//--------------------------------------------------------------------------------------------
UciOptions::~UciOptions()
{
}

//--------------------------------------------------------------------------------------------
const std::string& UciOptions::getUciPath() const
{
  return m_uciPath;
}

//--------------------------------------------------------------------------------------------
void UciOptions::setUciPath(const std::string& uciPath)
{
  m_uciPath = uciPath;
}

//--------------------------------------------------------------------------------------------
int UciOptions::getThreadsCount() const
{
  return m_threadsCount;
}

//--------------------------------------------------------------------------------------------
void UciOptions::setThreadsCount(int tc)
{
  m_threadsCount = tc;
}

//--------------------------------------------------------------------------------------------
UciPlayerOptions& UciOptions::getWhiteOptions()
{
  return m_whiteOptions;
}

//--------------------------------------------------------------------------------------------
UciPlayerOptions& UciOptions::getBlackOptions()
{
  return m_blackOptions;
}

//--------------------------------------------------------------------------------------------
UciPlayerOptions& UciOptions::getHintOptions()
{
  return m_hintOptions;
}

}       // namespace
