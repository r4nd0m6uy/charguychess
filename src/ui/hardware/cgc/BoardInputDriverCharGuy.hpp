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
#ifndef _CGC_I_BOARD_INPUT_DRIVER_CHAR_GUY_HPP_
#define _CGC_I_BOARD_INPUT_DRIVER_CHAR_GUY_HPP_

#include "../IBoardInputDriver.hpp"

namespace cgc {

/**
 * \brief An interface to work with chess hardware
 */
class BoardInputDriverCharGuy:
    public IBoardInputDriver
{
public:
  BoardInputDriverCharGuy();
  virtual ~BoardInputDriverCharGuy();

  // IBoardInputDriver
  virtual int init() override;
  virtual int read(BoardValue& bv) override;
};

}       // namespace
#endif  // _CGC_I_BOARD_INPUT_DRIVER_CHAR_GUY_HPP_
