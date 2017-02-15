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
#include "ui/ConsoleUI.hpp"
#include "logging/LogMacros.hpp"

//--------------------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  cgc::GameLogic gl;
  cgc::ConsoleUI cUi(gl);

  LOGIN() << "Starting application ...";

  if(cUi.init() != 0)
    return -1;

  // TODO

  LOGIN() << "Exiting application";

  return 0;
}
