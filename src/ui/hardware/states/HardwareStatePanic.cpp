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
#include "HardwareStatePanic.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
HardwareStatePanic::HardwareStatePanic(IHardwareStatePool& statesPool, GameLogic& gl):
    m_statesPool(statesPool),
    m_gl(gl)
{
}

//--------------------------------------------------------------------------------------------
HardwareStatePanic::~HardwareStatePanic()
{
}

//--------------------------------------------------------------------------------------------
void HardwareStatePanic::enter()
{
}

//--------------------------------------------------------------------------------------------
IHardwareState& HardwareStatePanic::execute(BoardValue bv)
{
  (void)m_gl;

  return m_statesPool.enterState(IHardwareStatePool::PANIC);
}

}       // namespace
