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
#include "../../../logging/LogMacros.hpp"
#include "HardwareStatePlayerThinking.hpp"
#include "HardwareStatePanic.hpp"
#include "HardwareStatePool.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
HardwareStatePool::HardwareStatePool()
{
}

//--------------------------------------------------------------------------------------------
HardwareStatePool::~HardwareStatePool()
{
}

//--------------------------------------------------------------------------------------------
int HardwareStatePool::init(GameLogic& gl)
{
  m_states[PLAYER_THINKING].reset(new HardwareStatePlayerThinking(*this, gl));
  m_states[PANIC].reset(new HardwareStatePanic(*this, gl));

  return 0;
}

//--------------------------------------------------------------------------------------------
IHardwareState& HardwareStatePool::enterState(State which)
{
  IHardwareState& next = m_nullState;

  if(m_states.find(which) == m_states.end())
    LOGWA() << "State " << which << " not found in pool, using null state";
  else
    next = *m_states[which];

  next.enter();
  return next;
}

}       // namespace
