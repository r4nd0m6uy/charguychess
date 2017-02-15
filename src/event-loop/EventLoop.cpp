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
#include "EventLoop.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
void libeventIoCallback(evutil_socket_t fd, short what, void* data)
{
  HandledIoLibevent* handle = static_cast<HandledIoLibevent*>(data);

  if((what & EV_READ) != 0)
    handle->getHandledIo().readReady();
}

//--------------------------------------------------------------------------------------------
EventLoop::EventLoop():
    m_eventBase(nullptr)
{
  for(auto& handledIo : m_handledIos)
    delete handledIo;
}

//--------------------------------------------------------------------------------------------
EventLoop::~EventLoop()
{
  if(m_eventBase != nullptr)
    event_base_free(m_eventBase);
}

//--------------------------------------------------------------------------------------------
int EventLoop::init()
{
  if(m_eventBase != nullptr)
  {
    LOGWA() << "Event loop already initialized!";
    return 0;
  }

  m_eventBase = event_base_new();
  if(m_eventBase == nullptr)
  {
    LOGER() << "Cannot initialize libevent";
    return -1;
  }

  return 0;
}

//--------------------------------------------------------------------------------------------
void EventLoop::registerHandledIo(IHandledIo& handler, int what)
{
  struct event* ev;
  int libeventWhat = 0;
  HandledIoLibevent* wrappedEvent = new HandledIoLibevent(handler);

  if((what & READ) != 0)
    libeventWhat |= EV_READ;
  if((what & PERSIST) != 0)
    libeventWhat |= EV_PERSIST;

  ev = event_new(
      m_eventBase,
      handler.getHandle(),
      libeventWhat,
      libeventIoCallback,
      wrappedEvent);
  if(ev == nullptr)
  {
    LOGER() << "Error creating libevent event!";
    delete wrappedEvent;
    return;
  }

  event_add(ev, NULL);
  wrappedEvent->setEvent(ev);
  m_handledIos.push_back(wrappedEvent);
}

//--------------------------------------------------------------------------------------------
int EventLoop::run()
{
  int ret = 0;

  if(m_eventBase == nullptr)
  {
    LOGER() << "Cannot run an non initialized event loop";
    return -1;
  }

  LOGDB() << "Starting event loop ...";

  ret = event_base_loop(m_eventBase, 0);

  LOGDB() << "Event loop broke with code " << ret;

  return ret;
}

}       // namespace
