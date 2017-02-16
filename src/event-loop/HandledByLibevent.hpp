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
#ifndef _CGC_HANDLED_BY_LIBEVENT_HPP_
#define _CGC_HANDLED_BY_LIBEVENT_HPP_

#include <event2/event.h>

#include "IHandledSignal.hpp"

namespace cgc {

/**
 * \brief Wraps a libevent event
 */
class HandledByLibevent
{
public:
  HandledByLibevent();
  virtual ~HandledByLibevent();

  struct event* getEvent();
  void setEvent(struct event* ev);

private:
  struct event* m_event;
};

}       // namespace
#endif  // _CGC_HANDLED_BY_LIBEVENT_HPP_
