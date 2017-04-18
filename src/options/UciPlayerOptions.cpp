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
#include "UciPlayerOptions.hpp"

namespace cgc {

const UciPlayerOptions::SearchMode UciPlayerOptions::DEFAULT_SEARCH_MODE  = TIME_LIMIT;
const int UciPlayerOptions::DEFAULT_MAX_DEPTH                             = 1;
const int UciPlayerOptions::DEFAULT_MAX_TIMEOUT                           = 2000;

//--------------------------------------------------------------------------------------------
UciPlayerOptions::UciPlayerOptions():
    m_searchMode(DEFAULT_SEARCH_MODE),
    m_maxDepth(DEFAULT_MAX_DEPTH),
    m_timeout(DEFAULT_MAX_TIMEOUT)
{
}

//--------------------------------------------------------------------------------------------
UciPlayerOptions::~UciPlayerOptions()
{
}

//--------------------------------------------------------------------------------------------
UciPlayerOptions::SearchMode UciPlayerOptions::getSearchMode() const
{
  return m_searchMode;
}

//--------------------------------------------------------------------------------------------
void UciPlayerOptions::setSearchMode(const UciPlayerOptions::SearchMode& mode)
{
  m_searchMode = mode;
}

//--------------------------------------------------------------------------------------------
int UciPlayerOptions::getSearchMaxDepth() const
{
  return m_maxDepth;
}

//--------------------------------------------------------------------------------------------
void UciPlayerOptions::setSearchMaxDepth(int searchMaxDepth)
{
  m_maxDepth = searchMaxDepth;
}

//--------------------------------------------------------------------------------------------
int UciPlayerOptions::getSearchTimeout() const
{
  return m_timeout;
}

//--------------------------------------------------------------------------------------------
void UciPlayerOptions::setSearchTimeout(int serachTimeout)
{
  m_timeout = serachTimeout;
}

}       // namespace
