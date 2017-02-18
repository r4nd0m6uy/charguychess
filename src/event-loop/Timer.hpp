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
#ifndef _CGC_TIMER_HPP_
#define _CGC_TIMER_HPP_

#include "ITimedOut.hpp"
#include "HandledByLibevent.hpp"

namespace cgc {

/**
 * \brief A class to work with timers
 */
class Timer:
    public HandledByLibevent
{
public:
  Timer(const std::string& name, ITimedOut& to);
  virtual ~Timer();

  const std::string& getName();
  void start();
  void stop();
  void setTimeout(int ms);
  void timedOut();

private:
  std::string m_name;
  ITimedOut& m_to;
  int m_timeout;
};

}       // namespace
#endif  // _CGC_TIMER_HPP_
