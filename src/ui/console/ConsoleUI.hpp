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

#include "../../event-loop/EventLoop.hpp"
#include "../../chess/GameLogic.hpp"
#include "../../chess/Pgn.hpp"
#include "../hardware/IBoardInputObserver.hpp"
namespace cgc {

/**
 * \brief An user interface done in console
 */
class ConsoleUI:
    public IBoardObserver,
    public IHandledIo,
    public IBoardInputObserver
{
public:
  ConsoleUI(GameLogic& gl, EventLoop& eventLoop);
  virtual ~ConsoleUI();

  int init();
  void enableMoveCommand(bool isEnabled);

  // IBoardObserver
  virtual void boardChanged(Color playerTurn, const Board& newStatus) override;

  // IHandledIo
  virtual IoHandle getHandle() override;
  virtual void readReady() override;

  // IBoardInputObserver
  virtual void boardValueChanged(BoardValue bv) override;

private:
  Pgn m_pgn;
  GameLogic& m_gl;
  EventLoop& m_eventLoop;
  bool m_isMoveEnabled;
  bool m_isDriverBbEnabled;

  void showBoard(Color playerTurn, const Board& newStatus);
  void printPrompt();
  void printGreeting();
  void printHelp();
  void readMove(const std::string& move);
  void showLegalSquare(const std::string& square);
  void displayCtrlSquares();
  void savePgn();
  void showPgnInfo();
  void setPgnTag(const std::string& args);
};

}       // namespace
#endif  // _CGC_CONSOLE_UI_HPP_
