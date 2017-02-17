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
#ifndef _CGC_I_LOG_SINK_HPP_
#define _CGC_I_LOG_SINK_HPP_

#include <iostream>
#include <string>

namespace cgc {

class ILogSink
{
public:
    enum LogLevel
    {
        DEBUG       = 0,
        INFO        = 1,
        WARNING     = 2,
        ERROR       = 3,
        MAX       = 3
    };

    ILogSink();
    virtual ~ILogSink();

    virtual void sinkLogLine(LogLevel level, const std::string& line) = 0;
};

std::ostream& operator<<(std::ostream& os, const ILogSink::LogLevel& loglevel);

}       // namespace
#endif  // _CGC_I_LOG_SINK_HPP_
