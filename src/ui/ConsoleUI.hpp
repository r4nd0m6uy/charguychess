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
#ifndef _CGC_CONSOLE_UI_HPP_
#define _CGC_CONSOLE_UI_HPP_

#include "../event-loop/EventLoop.hpp"
#include "../chess/GameLogic.hpp"

namespace cgc {

/**
 * \brief An user interface done in console
 */
class ConsoleUI:
    public IBoardObserver,
    public IHandledIo
{
public:
  ConsoleUI(GameLogic& gl, EventLoop& eventLoop);
  virtual ~ConsoleUI();

  int init();

  // IBoardObserver
  virtual void boardChanged(Color playerTurn, const Board& newStatus) override;

  // IHandledIo
  virtual IoHandle getHandle();
  virtual void readReady();

private:
  GameLogic& m_gl;
  EventLoop& m_eventLoop;

  void showBoard(Color playerTurn, const Board& newStatus);
  void printPrompt();
  void printGreeting();
  void printHelp();
  void readMove(const std::string& move);
};

}       // namespace
#endif  // _CGC_CONSOLE_UI_HPP_
