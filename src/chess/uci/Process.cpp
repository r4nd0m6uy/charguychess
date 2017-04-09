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
#include <sys/types.h>
#include <sys/wait.h>

#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "../../logging/LogMacros.hpp"
#include "Process.hpp"

namespace cgc {

static const int INVALID_FD = -1;
static const pid_t INVALID_PID = -1;
//--------------------------------------------------------------------------------------------
Process::Process(const std::string& command, EventLoop& el):
    m_command(command),
    m_el(el),
    m_pid(INVALID_PID)
{
  m_inputPipe[0] = INVALID_FD;
  m_inputPipe[1] = INVALID_FD;
  m_outputPipe[0] = INVALID_FD;
  m_outputPipe[1] = INVALID_FD;
}

//--------------------------------------------------------------------------------------------
Process::~Process()
{
  stop();
}

//--------------------------------------------------------------------------------------------
bool Process::isRunning()
{
  if(m_pid != INVALID_PID)
  {
    int wstatus;
    int waitPidStatus;

    waitPidStatus = waitpid(m_pid, &wstatus, WNOHANG);
    if(waitPidStatus == -1)
    {
      if(errno == ECHILD)
      {
        LOGWA() << m_command << " stopped unexpectly!";
        closePipes();
        m_pid = INVALID_PID;
      }

      LOGER() << "Error getting process status: " << strerror(errno);
      return false;
    }
    else if(waitPidStatus != 0)
    {
      if(WIFEXITED(wstatus))
      {
        LOGIN() << "Process " << m_command << " has terminated";
        m_pid = INVALID_PID;
        return false;
      }
    }

    return true;
  }

  return false;
}

//--------------------------------------------------------------------------------------------
int Process::start()
{
  pid_t forkRes;

  if(isRunning())
    return 0;

  closePipes();

  if(pipe(m_inputPipe))
  {
    LOGER() << "Cannot create pipe: " << strerror(errno);
    return -1;
  }
  if(pipe(m_outputPipe))
  {
    LOGER() << "Cannot create pipe: " << strerror(errno);
    closePipes();
    return -1;
  }

  forkRes = fork();
  if(forkRes == -1)
  {
    LOGER() << "Cannot fork: " << strerror(errno);
    closePipes();
    return -1;
  }
  else if(forkRes > 0)
  {
    m_pid = forkRes;

    close(m_inputPipe[1]);
    m_inputPipe[1] = INVALID_FD;
    close(m_outputPipe[0]);
    m_outputPipe[0] = INVALID_FD;

    m_el.registerHandledIo(*this, EventLoop::READ | EventLoop::PERSIST);
  }
  else
  {
    int buffsize = 64;
    char cmd[buffsize];
    char *argv[]={ cmd, 0 };

    dup2(m_inputPipe[1], 1);
    dup2(m_outputPipe[0], 0);
    // XXX: stderr not handled but printed in console ...

    closePipes();

    strncpy(cmd, m_command.c_str(), buffsize);
    execv(argv[0], argv);

    LOGER() << "Cannot execv: " << strerror(errno);
    exit(-1);
  }

  return 0;
}

//--------------------------------------------------------------------------------------------
int Process::stop()
{
  if(isRunning())
  {
    LOGDB() << "Stopping " << m_command;
    kill(m_pid, SIGTERM);
    closePipes();
  }

  return 0;
}

//--------------------------------------------------------------------------------------------
int Process::stdinWrite(const char* data, int size)
{
  return write(m_outputPipe[1] ,data, size);
}

//--------------------------------------------------------------------------------------------
void Process::registerIoListener(IProcessIoListener& listener)
{
  m_processIoListener.push_back(&listener);
}

//--------------------------------------------------------------------------------------------
IoHandle Process::getHandle()
{
  return m_inputPipe[0];
}

//--------------------------------------------------------------------------------------------
void Process::readReady()
{
  int bufferSize = 128;
  char buffer[bufferSize];
  int readSize;

  readSize = read(m_inputPipe[0], buffer, bufferSize);
  if(readSize < 0)
  {
    LOGER() << "Error reading sub process pipe: " << strerror(errno) << std::endl;
    return;
  }

  std::string ioData(buffer, readSize);
  for(auto& processIoListener : m_processIoListener)
    processIoListener->onStdout(ioData);
}

//--------------------------------------------------------------------------------------------
void Process::closePipes()
{
  if(m_inputPipe[0] != INVALID_FD)
  {
    close(m_inputPipe[0]);
    m_inputPipe[0] = INVALID_FD;
  }
  if(m_inputPipe[1] != INVALID_FD)
  {
    close(m_inputPipe[1]);
    m_inputPipe[1] = INVALID_FD;
  }
  if(m_outputPipe[0] != INVALID_FD)
  {
    close(m_outputPipe[0]);
    m_outputPipe[0] = INVALID_FD;
  }
  if(m_outputPipe[1] != INVALID_FD)
  {
    close(m_outputPipe[1]);
    m_outputPipe[1] = INVALID_FD;
  }
}

}       // namespace
