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
#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <iomanip>

#include "../../../logging/LogMacros.hpp"
#include "../BitBoard.hpp"
#include "BoardInputDriverPipe.hpp"

namespace cgc {

const std::string PIPE_PATH = "/tmp/board_input";
const int BUFFER_SIZE = 128;

//--------------------------------------------------------------------------------------------
BoardInputDriverPipe::BoardInputDriverPipe(EventLoop& el):
    m_el(el),
    m_bv(0),
    m_pipeFd(-1)
{
}

//--------------------------------------------------------------------------------------------
BoardInputDriverPipe::~BoardInputDriverPipe()
{
  if(m_pipeFd >= 0)
  {
    unlink(PIPE_PATH.c_str());
    close(m_pipeFd);
  }
}

//--------------------------------------------------------------------------------------------
int BoardInputDriverPipe::init()
{
  if(m_pipeFd >= 0)
  {
    LOGWA() << "Driver pipe already initialized";
    return 0;
  }

  if(mkfifo(PIPE_PATH.c_str(), S_IRUSR | S_IWUSR))
  {
    LOGER() << "Cannot create pipe " << PIPE_PATH << ": " << strerror(errno);
    return -1;
  }

  m_pipeFd = open(PIPE_PATH.c_str(), O_RDWR);
  if(m_pipeFd < 0)
  {
    LOGER() << "Cannot create pipe: " << strerror(errno);
    unlink(PIPE_PATH.c_str());
    return -1;
  }

  if(m_el.registerHandledIo(*this, EventLoop::READ | EventLoop::PERSIST))
  {
    LOGER() << "Cannot register pipe to the event loop";
    unlink(PIPE_PATH.c_str());
    close(m_pipeFd);
    return -1;
  }

  LOGDB() << "Simulated hardware ready!";

  return 0;
}

//--------------------------------------------------------------------------------------------
int BoardInputDriverPipe::read(BoardValue& bv)
{
  bv = m_bv;
  return 0;
}

//--------------------------------------------------------------------------------------------
void BoardInputDriverPipe::registerObserver(IBoardInputObserver& o)
{
  m_dispatchedInputEvent.registerObserver(o);
}

//--------------------------------------------------------------------------------------------
IoHandle BoardInputDriverPipe::getHandle()
{
  return m_pipeFd;
}

//--------------------------------------------------------------------------------------------
void BoardInputDriverPipe::readReady()
{
  char buffer[BUFFER_SIZE];
  ssize_t readSize;
  size_t endLine;

  readSize = ::read(m_pipeFd, buffer, BUFFER_SIZE);
  if(readSize < 0)
  {
    LOGER() << "Cannot read pipe " << strerror(errno);
    return;
  }

  m_buffer += std::string(buffer, readSize);
  while((endLine = m_buffer.find('\n', 0)) != std::string::npos)
  {
    std::string strVal = m_buffer.substr(0, endLine);
    m_buffer = m_buffer.substr(endLine + 1);

    if(strVal == "")
      continue;

    BitBoard bb(strVal);
    m_bv = bb.getBoardValue();
    LOGDB() << "New simulated board value: 0x" <<
        std::setfill('0') << std::setw(16) << std::hex << m_bv << " -> " << strVal;
    m_dispatchedInputEvent.raiseBoardChanged(m_bv);

    endLine = m_buffer.find('\n', 0);
  }
}

}       // namespace
