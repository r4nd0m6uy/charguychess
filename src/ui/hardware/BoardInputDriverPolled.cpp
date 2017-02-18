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
#include "../../logging/LogMacros.hpp"
#include "BoardInputDriverPolled.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
BoardInputDriverPolled::BoardInputDriverPolled(
    std::unique_ptr<IBoardInputDriver> inputDriver, EventLoop& el):
  m_inputDriver(std::move(inputDriver)),
  m_el(el)
{
}

//--------------------------------------------------------------------------------------------
BoardInputDriverPolled::~BoardInputDriverPolled()
{
}

//--------------------------------------------------------------------------------------------
int BoardInputDriverPolled::init()
{
  if(m_el.createTimer("PollHardware", *this, m_pollTimer))
    return -1;
  m_pollTimer->setTimeout(10);
  m_pollTimer->start();

  return m_inputDriver->init();
}

//--------------------------------------------------------------------------------------------
int BoardInputDriverPolled::read(BoardValue& bv)
{
  return m_inputDriver->read(bv);
}

//--------------------------------------------------------------------------------------------
void BoardInputDriverPolled::registerObserver(IBoardInputObserver& o)
{
  m_dispBoardInputEvent.registerObserver(o);
}

//--------------------------------------------------------------------------------------------
void BoardInputDriverPolled::timedOut(const std::string& which)
{
  BoardValue bv;

  if(m_inputDriver->read(bv))
  {
    LOGER() << "Cannot read from board driver, stop polling!";
    return;
  }

  m_dispBoardInputEvent.raiseBoardChanged(bv);
  m_pollTimer->start();
}

}       // namespace
