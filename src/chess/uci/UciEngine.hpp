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
#ifndef _CGC_UCI_ENGINE_HPP_
#define _CGC_UCI_ENGINE_HPP_

#include <memory>

#include "../GameHistory.hpp"
#include "Process.hpp"
#include "IUciEngineListener.hpp"

namespace cgc {

/**
 * \brief Represent an UCI engine
 */
class UciEngine:
    public IProcessIoListener
{
public:
  UciEngine(std::unique_ptr<Process> uciProcess);
  ~UciEngine();

  void registerEngineListener(IUciEngineListener& listener);
  int computeBestMove(const GameHistory& gh);

  // IProcessIoListener
  virtual void onStdout(const std::string& out) override;

private:
  std::unique_ptr<Process> m_uciProcess;
  std::string m_uciBuffer;
};

}       // namespace
#endif  // _CGC_UCI_ENGINE_HPP_
