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
#ifndef _CGC_PROCESS_HPP_
#define _CGC_PROCESS_HPP_

#include "IProcessIoListener.hpp"
#include "../../event-loop/EventLoop.hpp"

namespace cgc {

/**
 * \brief Represent a backgroung process
 */
class Process:
    public IHandledIo
{
public:
  Process(const std::string& command, EventLoop& el);
  ~Process();

  bool isRunning();
  int start();
  int stop();
  int stdinWrite(const char* data, int size);
  void registerIoListener(IProcessIoListener& listener);

  // IHandledIo
  virtual IoHandle getHandle() override;
  virtual void readReady() override;

private:
  std::string m_command;
  EventLoop& m_el;
  pid_t m_pid;
  int m_inputPipe[2];
  int m_outputPipe[2];
  std::list<IProcessIoListener*> m_processIoListener;

  void closePipes();
};

}       // namespace
#endif  // _CGC_PROCESS_HPP_
