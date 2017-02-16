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
#include <getopt.h>

#include <iostream>

#include "event-loop/EventLoop.hpp"
#include "ui/console/ConsoleUI.hpp"
#include "ui/hardware/ChessHardwareFactory.hpp"
#include "logging/LogMacros.hpp"

/* local variables */
std::string hardwareArg = "none";

//--------------------------------------------------------------------------------------------
void printHelp(char* appName)
{
  std::cout << appName << " [OPTIONS]:" << std::endl;
  std::cout << "-h|--help       Show this help message" << std::endl;
  std::cout << "-H|--hardware   Hardware to use" << std::endl;
  std::cout << "                * none: No hardware" << std::endl;
  std::cout << "                * sim:  Simulate hardware" << std::endl;
  std::cout << "                * cgc:  Charguy chess hardware" << std::endl;
}

//--------------------------------------------------------------------------------------------
int parseArgs(int argc, char* argv[], int& retCode)
{
  int c;

  static struct option long_options[] =
  {
    {"help",      no_argument,        0,    'h'},
    {"hardware",  required_argument,  0,    'H'},
    {0, 0, 0, 0}
  };

  while(1)
  {
    c = getopt_long(argc, argv, "hH:", long_options, 0);

    if(c == -1)
      break;

    switch(c)
    {
    case 'h':
      printHelp(argv[0]);
      retCode = 0;
      return -1;
      break;
    case 'H':
      hardwareArg = optarg;
      break;
    case '?':
    default:
      printHelp(argv[0]);
      retCode = -1;
      return -1;
    }
  }

  return 0;
}

//--------------------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  cgc::EventLoop el;
  cgc::GameLogic gl;
  cgc::ConsoleUI cUi(gl, el);
  std::unique_ptr<cgc::ChessHardware> hw(nullptr);
  int ret;

  if(parseArgs(argc, argv, ret) != 0)
    return ret;

  // Create the driver when requested
  if(hardwareArg == "none")
    cUi.enableMoveInput(true);
  else
  {
    cgc::ChessHardwareFactory hwFactory;
    if(hardwareArg == "cgc")
      hw = hwFactory.buildCgc();
    else if(hardwareArg == "sim")
      hw = hwFactory.buildSimulated();
    else
    {
      std::cout << "Unknown hardware " << hardwareArg << std::endl;
      printHelp(argv[0]);
      return -1;
    }

    if(hw->init() != 0)
    {
      LOGWA() << "Cannot initialize chess hardware, it will not work!";
      hw = nullptr;
      cUi.enableMoveInput(true);
    }
    else
      cUi.enableMoveInput(false);
  }

  // Initialize the event loop
  if(el.init() != 0)
    return -1;

  // Intialize the console UI
  if(cUi.init() != 0)
    return -1;

  // Run the event loop
  LOGIN() << "Starting application ...";
  ret = el.run();
  LOGIN() << "Exiting application with code " << ret;

  return ret;
}
