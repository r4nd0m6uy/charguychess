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
#include "../../logging/LogMacros.hpp"
#include "UciEngine.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
UciEngine::UciEngine(std::unique_ptr<Process> uciProcess):
    m_uciProcess(std::move(uciProcess))
{
}

//--------------------------------------------------------------------------------------------
UciEngine::~UciEngine()
{
}

//--------------------------------------------------------------------------------------------
void UciEngine::registerEngineListener(IUciEngineListener& listener)
{
}

//--------------------------------------------------------------------------------------------
int UciEngine::computeBestMove(const GameHistory& gh)
{
  if(!m_uciProcess->isRunning())
  {
    if(m_uciProcess->start() != 0)
      return -1;

    m_uciProcess->registerIoListener(*this);
  }

  LOGIN() << "Computing best move not implemented yet!";

//  // Testing
//  std::string uciCmd = "go infinite\n";
//  m_uciProcess->stdinWrite(uciCmd.c_str(), uciCmd.size());

  return 0;
}

//--------------------------------------------------------------------------------------------
void UciEngine::onStdout(const std::string& out)
{
  LOGDB() << "UCI output: " << out;
}

}       // namespace
