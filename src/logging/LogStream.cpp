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
#include "LogStream.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
LogStream::LogStream(ILogSink& logSink, ILogSink::LogLevel loglevel):
        m_logSink(logSink),
        m_loglevel(loglevel)
{
}

//--------------------------------------------------------------------------------------------
LogStream::LogStream(const LogStream& rhs):
        m_logSink(rhs.m_logSink),
        m_loglevel(rhs.m_loglevel)
{
}

//--------------------------------------------------------------------------------------------
LogStream::~LogStream()
{
    m_logSink.sinkLogLine(m_loglevel, m_ss.str());
}

//--------------------------------------------------------------------------------------------
std::ostream& LogStream::get()
{
    return m_ss;
}

}       // namespace
