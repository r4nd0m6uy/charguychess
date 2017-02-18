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
#include "Timer.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
Timer::Timer(const std::string& name, ITimedOut& to):
    m_name(name),
    m_to(to),
    m_timeout(0)
{
}

//--------------------------------------------------------------------------------------------
Timer::~Timer()
{
}

//--------------------------------------------------------------------------------------------
const std::string& Timer::getName()
{
  return m_name;
}

//--------------------------------------------------------------------------------------------
void Timer::start()
{
  struct timeval tvTimeout;

  tvTimeout.tv_sec = m_timeout / 1000;
  tvTimeout.tv_usec = (m_timeout % 1000) * 1000;

  event_add(getEvent(), &tvTimeout);
}

//--------------------------------------------------------------------------------------------
void Timer::stop()
{
  event_del(getEvent());
}

//--------------------------------------------------------------------------------------------
void Timer::setTimeout(int ms)
{
  m_timeout = ms;
}

//--------------------------------------------------------------------------------------------
void Timer::timedOut()
{
  m_to.timedOut(m_name);
}

}       // namespace
