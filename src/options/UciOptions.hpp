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
#ifndef _CGC_UCI_OPTIONS_HPP_
#define _CGC_UCI_OPTIONS_HPP_

#include <string>

#include "UciPlayerOptions.hpp"

namespace cgc {

/**
 * \brief Holds options about the UCI engine
 */
class UciOptions
{
public:
  static const std::string DEFAULT_UCI_PATH;
  static const int DEFAULT_THREADS_COUNT;

  UciOptions();
  ~UciOptions();

  const std::string& getUciPath() const;
  void setUciPath(const std::string& uciPath);
  int getThreadsCount() const;
  void setThreadsCount(int tc);
  UciPlayerOptions& getWhiteOptions();
  UciPlayerOptions& getBlackOptions();
  UciPlayerOptions& getHintOptions();

private:
  std::string m_uciPath;
  int m_threadsCount;
  UciPlayerOptions m_blackOptions;
  UciPlayerOptions m_whiteOptions;
  UciPlayerOptions m_hintOptions;
};

}       // namespace
#endif  // _CGC_OPTIONS_HPP_
