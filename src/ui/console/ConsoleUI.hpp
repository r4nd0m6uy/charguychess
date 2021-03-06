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
#include "../../chess/uci/UciEngine.hpp"
#include "../../options/Options.hpp"
#include "../hardware/IBoardInputObserver.hpp"

namespace cgc {

/**
 * \brief An user interface done in console
 */
class ConsoleUI:
    public IBoardObserver,
    public IHandledIo,
    public IBoardInputObserver,
    public IUciEngineListener
{
public:
  ConsoleUI(GameLogic& gl, EventLoop& eventLoop, UciEngine& uciEngine, Options& options);
  virtual ~ConsoleUI();

  int init();
  void setHasHardware(bool hasHardware);

  // IBoardObserver
  virtual void boardChanged(Color playerTurn, const Board& newStatus) override;

  // IHandledIo
  virtual IoHandle getHandle() override;
  virtual void readReady() override;

  // IBoardInputObserver
  virtual void boardValueChanged(BoardValue bv) override;

  // IUciEngineListener
  virtual void onMoveComputed(const Move& m) override;

private:
  Pgn m_pgn;
  GameLogic& m_gl;
  EventLoop& m_eventLoop;
  UciEngine& m_uciEngine;
  Options& m_options;
  bool m_hasHardware;
  bool m_isDriverBbEnabled;

  void showBoard(Color playerTurn, const Board& newStatus);
  void printPrompt();
  void printGreeting();
  void printHelp();
  void readMove(const std::string& move);
  void showLegalSquares(const std::string& square);
  void showLegalSquares(const LegalSquares& ls);
  void displayCtrlSquares();
  void savePgn();
  void showPgnInfo();
  void setPgnTag(const std::string& args);
  void setPgnPath(const std::string& args);
  void computeBestMove();
  Options::PlayerType getCurrentPlayerType();
  void startComputerMove();
  void newGame();
};

}       // namespace
#endif  // _CGC_CONSOLE_UI_HPP_
