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
#include "BoardInputDriverCharGuy.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
BoardInputDriverCharGuy::BoardInputDriverCharGuy()
{
}

//--------------------------------------------------------------------------------------------
BoardInputDriverCharGuy::~BoardInputDriverCharGuy()
{
}

//--------------------------------------------------------------------------------------------
int BoardInputDriverCharGuy::init()
{
  // TODO
//  LOGER() << "Charguy input driver not implemented yet!";
//  return -1;

  // XXX: Testing
  return 0;
}

//--------------------------------------------------------------------------------------------
int BoardInputDriverCharGuy::read(BoardValue& bv)
{
  // TODO
//  LOGER() << "Charguy input driver not implemented yet!";
//  return -1;

  // XXX: Testing
  static BoardValue lastValue = 0;
  if(lastValue == 0)
    lastValue = 0xFFFF00000000FFFF;
  else if(lastValue == 0xFFFF00000000FFFF)
    lastValue = 0xFFF700000000FFFF;
  else
    lastValue = 0xFFF700080000FFFF;

  bv = lastValue;

  return 0;
}

}       // namespace
