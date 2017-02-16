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
#ifndef _CGC_CHESS_HARDWARE_FACTORY_HPP_
#define _CGC_CHESS_HARDWARE_FACTORY_HPP_

#include "../../event-loop/EventLoop.hpp"
#include "ChessHardware.hpp"

namespace cgc {

/**
 * \brief Build different chess hardware types
 */
class ChessHardwareFactory
{
public:
  ChessHardwareFactory() = delete;
  ~ChessHardwareFactory();

  static std::unique_ptr<ChessHardware> buildCgcHardware();
  static std::unique_ptr<ChessHardware> buildSimulatedHardware(EventLoop& el);
  static std::unique_ptr<IBoardInputDriver> buildCgcBoardInputDriver();
};

}       // namespace
#endif  // _CGC_I_BOARD_INPUT_DRIVER_CHAR_GUY_HPP_
