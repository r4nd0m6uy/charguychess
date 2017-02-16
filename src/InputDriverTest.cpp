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
#include <unistd.h>

#include "logging/LogMacros.hpp"
#include "ui/hardware/BitBoard.hpp"
#include "ui/hardware/ChessHardwareFactory.hpp"

//--------------------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  int interval = 1000;
  cgc::BitBoard bb;
  std::unique_ptr<cgc::IBoardInputDriver> inputDriver =
      cgc::ChessHardwareFactory::buildCgcBoardInputDriver();

  if(inputDriver->init() != 0)
  {
    LOGER() << "Cannot intialize driver!";
    return -1;
  }

  LOGIN() << "Reading driver every " << interval << "ms ...";
  while(1)
  {
    cgc::BoardValue readValue = 0;

    if(inputDriver->read(readValue) != 0)
    {
      LOGER() << "Cannot read from driver!";
      return -1;
    }

    if(readValue != bb.getBoardValue())
    {
      LOGIN() << "Board changed";
      bb.setBoardValue(readValue);
      std::cout << "========" << std::endl;
      std::cout << bb.toBoardString() << std::endl;
      std::cout << "========" << std::endl;
    }
    else
      LOGIN() << "Board didn't change";

    usleep(interval * 1000);
  }
  return 0;
}
