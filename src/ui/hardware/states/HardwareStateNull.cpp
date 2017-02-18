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

#include "../../../logging/LogMacros.hpp"
#include "HardwareStateNull.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
HardwareStateNull::HardwareStateNull()
{
}

//--------------------------------------------------------------------------------------------
HardwareStateNull::~HardwareStateNull()
{
}

//--------------------------------------------------------------------------------------------
void HardwareStateNull::enter()
{
  // Something is wrong
  LOGER() << "Entering hardware state null, this should not happen!";
  assert(0);
}

//--------------------------------------------------------------------------------------------
IHardwareState& HardwareStateNull::execute(BoardValue bv)
{
  // Something is wrong
  LOGER() << "Executing hardware state null, this should not happen!";
  assert(0);

  return *this;
};

}       // namespace
