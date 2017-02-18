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
#ifndef _CGC_I_BOARD_INPUT_DRIVER_POLLED_HPP_
#define _CGC_I_BOARD_INPUT_DRIVER_POLLED_HPP_

#include <memory>

#include "../../event-loop/EventLoop.hpp"
#include "IBoardInputDriverObservable.hpp"
#include "DispatchedBoardInputEvent.hpp"

namespace cgc {

/**
 * \brief Poll an BoardInputeDriver and raise event when changed
 */
class BoardInputDriverPolled:
    public IBoardInputDriverObservable,
    public ITimedOut
{
public:
  BoardInputDriverPolled(std::unique_ptr<IBoardInputDriver> inputDriver,
      EventLoop& el);
  virtual ~BoardInputDriverPolled();

  // IBoardInputDriver
  virtual int init() override;
  virtual int read(BoardValue& bv) override;

  // IBoardInputDriverObservable
  virtual void registerObserver(IBoardInputObserver& o) override;

  // ITimedOut
  virtual void timedOut(const std::string& which) override;

private:
  std::unique_ptr<IBoardInputDriver> m_inputDriver;
  EventLoop& m_el;
  std::unique_ptr<Timer> m_pollTimer;
  DispatchedBoardInputEvent m_dispBoardInputEvent;
};

}       // namespace
#endif  // _CGC_I_BOARD_INPUT_DRIVER_POLLED_HPP_
