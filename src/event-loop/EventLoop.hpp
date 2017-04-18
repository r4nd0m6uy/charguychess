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
#ifndef _CGC_EVENT_LOOP_HPP_
#define _CGC_EVENT_LOOP_HPP_

#include <list>
#include <map>
#include <memory>

#include <event2/event.h>

#include "IHandledIo.hpp"
#include "HandledIoLibevent.hpp"
#include "IHandledSignal.hpp"
#include "HandledSignalLibevent.hpp"
#include "Timer.hpp"

namespace cgc {

/**
 * \brief An event loop
 */
class EventLoop
{
public:
  enum EventType
  {
    READ    = 0x01,
    PERSIST = 0x02
  };

  EventLoop();
  virtual ~EventLoop();

  int init();
  int registerHandledIo(IHandledIo& handler, int what);
  void deregisterHandledIo(IHandledIo& handler);
  int registerHandledSignal(IHandledSignal& handler, SignalHandle s);
  int createTimer(const std::string& name, ITimedOut& to, std::unique_ptr<Timer>& timer);
  int run();
  int breakLoop();

private:
  struct event_base* m_eventBase;
  std::list<HandledIoLibevent*> m_handledIos;
  std::map<SignalHandle, HandledSignalLibevent*> m_handleSignals;
};

}       // namespace
#endif  // _CGC_EVENT_LOOP_HPP_
