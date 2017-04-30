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
#include <algorithm>

#include "../../logging/LogMacros.hpp"
#include "../hardware/BitBoard.hpp"
#include "ConsoleUI.hpp"

namespace cgc {

static const int BUFFER_SIZE = 128;
static const std::string RANK_SEPARATOR = " +---+---+---+---+---+---+---+---+";
static const std::string BOTTOM_LABEL =   "   A   B   C   D   E   F   G   H";
static const std::string PROMPT = "charguychess> ";

//--------------------------------------------------------------------------------------------
ConsoleUI::ConsoleUI(GameLogic& gl, EventLoop& eventLoop, UciEngine& uciEngine,
  Options& options):
    m_gl(gl),
    m_eventLoop(eventLoop),
    m_uciEngine(uciEngine),
    m_options(options),
    m_hasHardware(false),
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
  m_uciEngine.registerEngineListener(*this);

  printGreeting();
  newGame();

  LOGDB() << "Console UI ready!";

  return 0;
}

//--------------------------------------------------------------------------------------------
void ConsoleUI::setHasHardware(bool hasHardware)
{
  if(hasHardware)
    LOGIN() << "Hardware pressent, move input from console UI disabled";

  m_hasHardware = hasHardware;
}

//--------------------------------------------------------------------------------------------
void ConsoleUI::boardChanged(Color playerTurn, const Board& newStatus)
{
  showBoard(playerTurn, newStatus);
  printPrompt();
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
    showLegalSquares(cmd.substr(6, 2));
  else if(cmd.find("ctrlSquares") == 0)
    displayCtrlSquares();
  else if(cmd.find("move") == 0)
    readMove(cmd.substr(5));
  else if(cmd.find("new") == 0)
    newGame();
  else if(cmd.find("hwAutoDsp") == 0)
    m_isDriverBbEnabled = cmd[10] == '1';
  else if(cmd.find("pgn save") == 0)
    savePgn();
  else if(cmd.find("pgn info") == 0)
    showPgnInfo();
  else if(cmd.find("pgn set") == 0)
    setPgnTag(cmd.substr(8));
  else if(cmd.find("pgn path") == 0)
    setPgnPath(cmd.substr(9));
  else if(cmd.find("bestmove") == 0)
    computeBestMove();
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
void ConsoleUI::onMoveComputed(const Move& m)
{
  if(getCurrentPlayerType() == Options::UCI)
  {
    // Apply computer move
    if(!m_gl.applyMove(m))
    {
      LOGER() << "BUG: Game logic doesn't accept UCI move " << m;
      LOGIN() << "saving pgn for analyze ...";
      m_pgn.savePgn(m_gl.getGameHistory());
      m_eventLoop.breakLoop();
    }

    if(getCurrentPlayerType() == Options::UCI)
      startComputerMove();
  }
  else
  {
    // Show user hint
    LegalSquares ls(m.getFrom());

    ls.add(m.getTo());

    std::cout << std::endl << "Chess engine suggests " << m << std::endl;
    showLegalSquares(ls);
    printPrompt();
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
  std::cout << WHITE;

  if(m_gl.isMated(WHITE))
    std::cout << " MATE!";
  else if(m_gl.isChecked(WHITE))
    std::cout << " CHECK!";
  std::cout << std::endl;

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

      if(m_gl.isMated(BLACK))
        std::cout << " MATE!";
      else if(m_gl.isChecked(BLACK))
        std::cout <<" CHECK!";
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
  std::cout << "ctrlSquares       Display controlled square" << std::endl;
  std::cout << "new               Start a new game" << std::endl;
  std::cout << "hwAutoDsp <0|1>   Enable/disable auto display hardware" << std::endl;
  std::cout << "pgn save          Save game to PGN" << std::endl;
  std::cout << "pgn info          Show PGN info" << std::endl;
  std::cout << "pgn set <t> <v>   Set a value to the PGN tag" << std::endl;
  std::cout << "pgn path <p>      Set the PGN path" << std::endl;
  std::cout << "bestmove          Compute best move" << std::endl;
  std::cout << "quit              Quit the application" << std::endl;
}

//--------------------------------------------------------------------------------------------
void ConsoleUI::readMove(const std::string& move)
{
  Move m;

  if(m_hasHardware)
  {
    std::cout << "Move from console deactivated, please use connected hardware" << std::endl;
    return;
  }

  if(getCurrentPlayerType() == Options::UCI)
  {
    LOGER() << "Cannot move, it's computer turn!";
    return;
  }

  if(!m.parseString(move.substr(0, move.size() - 1)))
  {
    std::cout << "Cannot parse " << move << std::endl;
    return;
  }

  if(!m_gl.applyMove(m))
    std::cout << "Illegal move " << move << std::endl;

  // Computer to play
  if(getCurrentPlayerType() == Options::UCI)
    startComputerMove();
}

//--------------------------------------------------------------------------------------------
void ConsoleUI::showLegalSquares(const std::string& square)
{
  Square s(square);
  LegalSquares ls(s);

  if(!s.isValid())
  {
    std::cout << "Invalid square " << square << std::endl;
    return;
  }

  m_gl.getLegalSquares(ls);
  showLegalSquares(ls);
}

//--------------------------------------------------------------------------------------------
void ConsoleUI::showLegalSquares(const LegalSquares& ls)
{
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

//--------------------------------------------------------------------------------------------
void ConsoleUI::displayCtrlSquares()
{
  SquaresList whiteLs;
  SquaresList blackLs;

  m_gl.getControlledSquares(WHITE, whiteLs);
  m_gl.getControlledSquares(BLACK, blackLs);

  std::cout << RANK_SEPARATOR << std::endl;
  for(Rank r = EIGHT ; r != INVALID_RANK ; --r)
  {
    std::cout << r << "|";

    for(File f = A ; f <= H ; ++f)
    {
      Square s(f, r);

      if(whiteLs.contains(s))
        std::cout << "W";
      else
        std::cout << " ";

      if(m_gl.getBoard().getPieceType(s) == KING)
        std::cout << m_gl.getBoard().getPiece(s);
      else
        std::cout << " ";

      if(blackLs.contains(s))
        std::cout << "b";
      else
        std::cout << " ";
      std::cout << "|";
    }

    std::cout << std::endl << RANK_SEPARATOR << std::endl;
  }

  std::cout << BOTTOM_LABEL << std::endl;
}

//--------------------------------------------------------------------------------------------
void ConsoleUI::savePgn()
{
  if(m_pgn.savePgn(m_gl.getGameHistory()) == 0)
    std::cout << "PGN saved to " << m_pgn.getPath() << std::endl;
}

//--------------------------------------------------------------------------------------------
void ConsoleUI::showPgnInfo()
{
  std::cout << m_pgn << std::endl;
}

//--------------------------------------------------------------------------------------------
void ConsoleUI::setPgnTag(const std::string& args)
{
  std::string tag;
  std::string tagCased;
  std::string value;
  std::string::size_type argpos;

  argpos = args.find(" ");
  tag = args.substr(0, argpos);
  argpos += 1;
  value = args.substr(argpos, args.size() - argpos - 1);

  if(tag == "" || value == "")
  {
    std::cout << "Parameter missing" << std::endl;
    return;
  }

  tagCased = tag;
  std::transform(tag.begin(), tag.end(), tagCased.begin(),
      [](unsigned char c){ return std::tolower(c); });
  tagCased[0] = std::toupper(tagCased[0]);

  if(tagCased == Pgn::TAG_EVENT)
    m_pgn.setEvent(value);
  else if(tagCased == Pgn::TAG_SITE)
    m_pgn.setSite(value);
  else if(tagCased == Pgn::TAG_DATE)
    m_pgn.setDate(value);
  else if(tagCased == Pgn::TAG_ROUND)
    m_pgn.setRound(value);
  else if(tagCased == Pgn::TAG_WHITE)
    m_pgn.setWhiteName(value);
  else if(tagCased == Pgn::TAG_BLACK)
    m_pgn.setBlackName(value);
  else
    std::cout << "Unkown tag " << tag << std::endl;
}

//--------------------------------------------------------------------------------------------
void ConsoleUI::setPgnPath(const std::string& args)
{
  m_pgn.setPath(args.substr(0, args.size() - 1));
}

//--------------------------------------------------------------------------------------------
void ConsoleUI::computeBestMove()
{
  if(getCurrentPlayerType() == Options::UCI)
  {
    LOGER() << "Cannot compute best move when it's computer turn!";
    return;
  }

  if(m_uciEngine.computeBestMove(
      m_gl.getGameHistory(), m_options.getUciOptions().getHintOptions()) == 0)
    std::cout << "Computing best move ..." << std::endl;
  else
    std::cout << "Error requesting best move to UCI engine!" << std::endl;
}

//--------------------------------------------------------------------------------------------
Options::PlayerType ConsoleUI::getCurrentPlayerType()
{
  if(m_gl.getTurn() == WHITE)
    return m_options.getWhitePlayerType();
  else
    return m_options.getBlackPlayerType();
}

//--------------------------------------------------------------------------------------------
void ConsoleUI::startComputerMove()
{
  if(m_gl.isMated(m_gl.getTurn()))
  {
    LOGIN() << "Not starting computer move, it's mate!";
    return;
  }

  if(m_gl.getTurn() == WHITE)
    m_uciEngine.computeBestMove(
      m_gl.getGameHistory(), m_options.getUciOptions().getWhiteOptions());
  else
    m_uciEngine.computeBestMove(
      m_gl.getGameHistory(), m_options.getUciOptions().getBlackOptions());
}

//--------------------------------------------------------------------------------------------
void ConsoleUI::newGame()
{
  m_gl.newGame();

  // Computer start playing
  if(!m_hasHardware && getCurrentPlayerType() == Options::UCI)
    startComputerMove();
}
}       // namespace
