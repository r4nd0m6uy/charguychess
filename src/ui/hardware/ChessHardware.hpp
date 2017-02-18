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
#ifndef _CGC_CHESS_HARDWARE_HPP_
#define _CGC_CHESS_HARDWARE_HPP_

#include <memory>

#include "../../chess/GameLogic.hpp"
#include "states/HardwareStatePool.hpp"
#include "IBoardInputDriverObservable.hpp"

namespace cgc {

/**
 * \brief An interface to work with chess hardware
 */
class ChessHardware:
    public IBoardInputObserver
{
public:
  ChessHardware(std::unique_ptr<IBoardInputDriverObservable> inputDriver, GameLogic& gl);
  virtual ~ChessHardware();

  int init();
  void registerBoardInputObserver(IBoardInputObserver& o);

  // IBoardInputObserver
  virtual void boardValueChanged(BoardValue bv) override;

private:
  std::unique_ptr<IBoardInputDriverObservable> m_inputDriver;
  GameLogic& m_gl;
  IHardwareState* m_currentHwState;
  HardwareStatePool m_statesPool;

};

}       // namespace
#endif  // _CGC_CONSOLE_UI_HPP_
