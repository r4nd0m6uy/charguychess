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
#include "simulation/BoardInputDriverPipe.hpp"
#include "cgc/BoardInputDriverCharGuy.hpp"
#include "BoardInputDriverPolled.hpp"
#include "ChessHardwareFactory.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
ChessHardwareFactory::~ChessHardwareFactory()
{
}

//--------------------------------------------------------------------------------------------
std::unique_ptr<ChessHardware> ChessHardwareFactory::buildCgcHardware()
{
  return std::unique_ptr<ChessHardware>(
      new ChessHardware(
          std::unique_ptr<IBoardInputDriverObservable>(
              new BoardInputDriverPolled(
                  std::unique_ptr<IBoardInputDriver>(buildCgcBoardInputDriver())
              )
           )
      )
  );
}

//--------------------------------------------------------------------------------------------
std::unique_ptr<ChessHardware> ChessHardwareFactory::buildSimulatedHardware()
{
  return std::unique_ptr<ChessHardware>(
      new ChessHardware(
          std::unique_ptr<IBoardInputDriverObservable>(new BoardInputDriverPipe())
      )
  );
}

//--------------------------------------------------------------------------------------------
std::unique_ptr<IBoardInputDriver> ChessHardwareFactory::buildCgcBoardInputDriver()
{
  return std::unique_ptr<IBoardInputDriver>(new BoardInputDriverCharGuy());
}

}       // namespace

