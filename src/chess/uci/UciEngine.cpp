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
#include <sstream>

#include "../../logging/LogMacros.hpp"
#include "UciEngine.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
UciEngine::UciEngine(std::unique_ptr<Process> uciProcess, UciOptions& uciOptions):
    m_uciProcess(std::move(uciProcess)),
    m_uciOptions(uciOptions)
{
}

//--------------------------------------------------------------------------------------------
UciEngine::~UciEngine()
{
}

//--------------------------------------------------------------------------------------------
void UciEngine::registerEngineListener(IUciEngineListener& listener)
{
  m_uciListeners.push_back(&listener);
}

//--------------------------------------------------------------------------------------------
int UciEngine::computeBestMove(const GameHistory& gh, const UciPlayerOptions& upo)
{
  std::stringstream uciCmd;
  if(!m_uciProcess->isRunning())
  {
    m_uciProcess->setCommand(m_uciOptions.getUciPath());
    if(m_uciProcess->start() != 0)
      return -1;

    m_uciProcess->registerIoListener(*this);
  }

  uciCmd << "position startpos moves";

  for(auto& turn : gh.getTurns())
  {
    Move wm = turn.getWhiteMove();
    Move bm = turn.getBlackMove();

    if(wm.isValid())
      uciCmd << " " << wm.toUciString();
    if(bm.isValid())
      uciCmd << " " << bm.toUciString();
  }
  uciCmd << std::endl;

  LOGDB() << "Sending position to UCI engine: " << uciCmd.str();
  m_uciProcess->stdinWrite(uciCmd.str().c_str(), uciCmd.str().size());

  uciCmd.str("");
  if(upo.getSearchMode() == UciPlayerOptions::DEPTH)
    uciCmd << "go depth " << upo.getSearchMaxDepth() << std::endl;
  else
    uciCmd << "go movetime " << upo.getSearchTimeout() << std::endl;

  LOGDB() << "Sending search command to UCI engine: " << uciCmd.str();
  m_uciProcess->stdinWrite(uciCmd.str().c_str(), uciCmd.str().size());

  return 0;
}

//--------------------------------------------------------------------------------------------
void UciEngine::onStdout(const std::string& out)
{
  m_uciBuffer += out;

  LOGDB() << "UCI output: " << out;

  while(1)
  {
    std::string::size_type lineEnd = m_uciBuffer.find('\n');

    if(lineEnd == std::string::npos)
      break;

    std::string line = m_uciBuffer.substr(0, lineEnd);
    m_uciBuffer = m_uciBuffer.substr(lineEnd + 1);

    if(line.find("bestmove") != std::string::npos)
    {
      Move m;
      std::string::size_type moveStart;
      std::string::size_type moveEnd;
      std::string move;

      moveStart = line.find(" ");
      moveEnd = line.find(" ", moveStart + 1);

      if(!m.parseString(line.substr(moveStart + 1, moveEnd - moveStart - 1)))
      {
        LOGER() << "BUG: unparsable UCI move " << line;
        exit(-1);
      }

      LOGDB() << "Parsed UCI best move " << m;
      for(auto& uciListener : m_uciListeners)
        uciListener->onMoveComputed(m);
    }
  }
}

}       // namespace
