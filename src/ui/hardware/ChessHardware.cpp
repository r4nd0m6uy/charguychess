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
#include <cassert>

#include "../../logging/LogMacros.hpp"
#include "ChessHardware.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
ChessHardware::ChessHardware(std::unique_ptr<IBoardInputDriverObservable> inputDriver,
    GameLogic& gl):
  m_inputDriver(std::move(inputDriver)),
  m_gl(gl),
  m_currentHwState(nullptr)
{
}

//--------------------------------------------------------------------------------------------
ChessHardware::~ChessHardware()
{
}

//--------------------------------------------------------------------------------------------
int ChessHardware::init()
{
  LOGDB() << "Initializing chess hardware ...";

  if(m_statesPool.init(m_gl))
    return -1;

  if(m_inputDriver->init() != 0)
    return -1;

  m_inputDriver->registerObserver(*this);
  m_currentHwState = &m_statesPool.enterState(IHardwareStatePool::PANIC);
  m_currentHwState->enter();

  return 0;
}

//--------------------------------------------------------------------------------------------
void ChessHardware::registerBoardInputObserver(IBoardInputObserver& o)
{
  m_inputDriver->registerObserver(o);
}

//--------------------------------------------------------------------------------------------
void ChessHardware::boardValueChanged(BoardValue bv)
{
  assert(m_currentHwState != nullptr);
  m_currentHwState = &m_currentHwState->execute(bv);
}

}       // namespace
