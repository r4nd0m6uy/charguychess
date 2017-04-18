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
#ifndef _CGC_UCI_PLAYER_OPTIONS_HPP_
#define _CGC_UCI_PLAYER_OPTIONS_HPP_

namespace cgc {

/**
 * \brief Holds options about the UCI engine
 */
class UciPlayerOptions
{
public:
  enum SearchMode{
    DEPTH,
    TIME_LIMIT
  };

  static const SearchMode DEFAULT_SEARCH_MODE;
  static const int DEFAULT_MAX_DEPTH;
  static const int DEFAULT_MAX_TIMEOUT;

  UciPlayerOptions();
  ~UciPlayerOptions();

  SearchMode getSearchMode() const;
  void setSearchMode(const SearchMode& mode);
  int getSearchMaxDepth() const;
  void setSearchMaxDepth(int searchMaxDepth);
  int getSearchTimeout() const;
  void setSearchTimeout(int serachTimeout);

private:
  SearchMode m_searchMode;
  int m_maxDepth;
  int m_timeout;
};

}       // namespace
#endif  // _CGC_UCI_PLAYER_OPTIONS_HPP_
