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
#include <errno.h>
#include <string.h>

#include <iostream>

#include "../../logging/LogMacros.hpp"
#include "../hardware/BitBoard.hpp"
#include "ConsoleUI.hpp"

namespace cgc {

static const int BUFFER_SIZE = 128;
static const std::string RANK_SEPARATOR = " +---+---+---+---+---+---+---+---+";
static const std::string BOTTOM_LABEL =   "   A   B   C   D   E   F   G   H";
static const std::string PROMPT = "charguychess> ";

//--------------------------------------------------------------------------------------------
ConsoleUI::ConsoleUI(GameLogic& gl, EventLoop& eventLoop):
    m_gl(gl),
    m_eventLoop(eventLoop),
    m_isMoveEnabled(true),
    m_isDriverBbEnabled(false)
{
}

//--------------------------------------------------------------------------------------------
ConsoleUI::~ConsoleUI()
{
}

//--------------------------------------------------------------------------------------------
int ConsoleUI::init()
{
  LOGDB() << "Initializing console UI ...";

  if(m_eventLoop.registerHandledIo(*this, EventLoop::READ | EventLoop::PERSIST))
    return -1;

  m_gl.registerBoardObserver(*this);

  printGreeting();
  printPrompt();

  LOGDB() << "Console UI ready!";

  return 0;
}

//--------------------------------------------------------------------------------------------
void ConsoleUI::enableMoveCommand(bool isEnabled)
{
  if(isEnabled)
    LOGIN() << "Move input from console UI enabled";
  else
    LOGIN() << "Move input from console UI disabled";

  m_isMoveEnabled = isEnabled;
}

//--------------------------------------------------------------------------------------------
void ConsoleUI::boardChanged(Color playerTurn, const Board& newStatus)
{
  showBoard(playerTurn, newStatus);
}

//--------------------------------------------------------------------------------------------
IoHandle ConsoleUI::getHandle()
{
  // XXX: This might not be always true (socket)
  return 1;
}

//--------------------------------------------------------------------------------------------
void ConsoleUI::readReady()
{
  char buffer[BUFFER_SIZE];
  ssize_t readCount = BUFFER_SIZE;
  std::string cmd;

  while(readCount == BUFFER_SIZE)
  {
    readCount = read(1, buffer, BUFFER_SIZE);
    if(readCount < 0)
    {
      LOGER() << "Error reading from console " << strerror(errno);
      return;
    }
    cmd += std::string(buffer, readCount);
  }

  if(cmd.find("help") == 0)
    printHelp();
  else if(cmd.find("show") == 0)
    showBoard(m_gl.getTurn(), m_gl.getBoard());
  else if(cmd.find("legal") == 0)
    showLegalSquare(cmd.substr(6, 2));
  else if(cmd.find("move") == 0)
    readMove(cmd.substr(5, 4));
  else if(cmd.find("new") == 0)
    m_gl.newGame();
  else if(cmd.find("hwAutoDsp") == 0)
    m_isDriverBbEnabled = cmd[10] == '1';
  else if(cmd.find("quit") == 0)
    m_eventLoop.breakLoop();
  else if(cmd != "\n")
    std::cout << "Unknown command, type 'help' for more information" << std::endl;

  printPrompt();
}

//--------------------------------------------------------------------------------------------
void ConsoleUI::boardValueChanged(BoardValue bv)
{
  if(m_isDriverBbEnabled)
  {
    BitBoard bb(bv);

    std::cout << std::endl << "New hardware position:" << std::endl;
    std::cout << bb.toBoardString() << std::endl;
  }
}

//--------------------------------------------------------------------------------------------
void ConsoleUI::printPrompt()
{
  std::cout << PROMPT << std::flush;
}

//--------------------------------------------------------------------------------------------
void ConsoleUI::showBoard(Color playerTurn, const Board& newStatus)
{
  std::cout << std::endl << RANK_SEPARATOR;

  // Show white turn
  if(playerTurn == WHITE)
    std::cout << "   * ";
  else
    std::cout << "     ";
  std::cout << WHITE << std::endl;

  // Show each rank
  for(Rank r = EIGHT ; r != INVALID_RANK ; --r)
  {
    std::cout << r << "|";  // Label

    for(File f = A ; f <= H ; ++f)
      std::cout << " " <<  m_gl.getBoard().getPiece(Square(f, r)) << " |";

    // Show black turn
    if(r == EIGHT)
    {
      if(playerTurn == BLACK)
        std::cout << "   * ";
      else
        std::cout << "     ";

      std::cout << BLACK;
    }

    std::cout << std::endl << RANK_SEPARATOR << std::endl;
  }

  // Label
  std::cout << BOTTOM_LABEL << std::endl;

  // Captured black pieces
  std::cout << WHITE << ": ";
  for(auto& cp: m_gl.getCapturedBlackPieces())
    std::cout << cp;
  std::cout << std::endl;

  // Captured white pieces
  std::cout << BLACK << ": ";
  for(auto& cp : m_gl.getCapturedWhitePieces())
    std::cout << cp;
  std::cout << std::endl;

  // History
  std::cout << m_gl.getGameHistory() << std::endl;

}

//--------------------------------------------------------------------------------------------
void ConsoleUI::printGreeting()
{
  std::cout << "Welcome to charguy chess!" << std::endl;
  std::cout << "Type 'help' for the list of available commands" << std::endl << std::endl;
}

//--------------------------------------------------------------------------------------------
void ConsoleUI::printHelp()
{
  std::cout << "help              Print this help" << std::endl;
  std::cout << "show              Show the board" << std::endl;
  std::cout << "legal <square>    Show legal moves from <square> (e2)" << std::endl;
  std::cout << "move <move>       Make a move (e2e4)" << std::endl;
  std::cout << "new               Start a new game" << std::endl;
  std::cout << "hwAutoDsp <0|1>   Enable/disable auto display hardware" << std::endl;
  std::cout << "quit              Quit the application" << std::endl;
}

//--------------------------------------------------------------------------------------------
void ConsoleUI::readMove(const std::string& move)
{
  if(!m_isMoveEnabled)
  {
    std::cout << "Move from console deactivated, please use connected hardware" << std::endl;
    return;
  }

  Move m(move);
  if(!m.isValid())
  {
    std::cout << "Invalid move " << move << std::endl;
    return;
  }

  if(!m_gl.applyMove(m))
    std::cout << "Illegal move " << move << std::endl;
}

//--------------------------------------------------------------------------------------------
void ConsoleUI::showLegalSquare(const std::string& square)
{
  Square s(square);
  LegalSquares ls(s);

  if(!s.isValid())
  {
    std::cout << "Invalid square " << square << std::endl;
    return;
  }

  m_gl.getLegalSquares(ls);
  std::cout << RANK_SEPARATOR << std::endl;
  for(Rank r = EIGHT ; r != INVALID_RANK ; --r)
  {
    std::cout << r << "|";

    for(File f = A ; f <= H ; ++f)
    {
      Square s(f, r);

      if(ls.getFrom() == s)
        std::cout << "*" << m_gl.getBoard().getPiece(s) << "*";
      else if(ls.contains(s))
        std::cout << "x" << m_gl.getBoard().getPiece(s) << "x";
      else
        std::cout << " " << m_gl.getBoard().getPiece(s) << " ";
      std::cout << "|";
    }
    std::cout << std::endl << RANK_SEPARATOR << std::endl;
  }

  std::cout << BOTTOM_LABEL << std::endl;
}

}       // namespace
