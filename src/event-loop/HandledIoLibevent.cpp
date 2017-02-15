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
#include "HandledIoLibevent.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
HandledIoLibevent::HandledIoLibevent(IHandledIo& handledIo):
    m_handledIo(handledIo),
    m_event(nullptr)
{
}

//--------------------------------------------------------------------------------------------
HandledIoLibevent::~HandledIoLibevent()
{
  if(m_event != nullptr)
    event_del(m_event);
}

//--------------------------------------------------------------------------------------------
struct event* HandledIoLibevent::getEvent()
{
  return m_event;
}

//--------------------------------------------------------------------------------------------
void HandledIoLibevent::setEvent(struct event* ev)
{
  m_event = ev;
}

//--------------------------------------------------------------------------------------------
IHandledIo& HandledIoLibevent::getHandledIo()
{
  return m_handledIo;
}

}       // namespace
