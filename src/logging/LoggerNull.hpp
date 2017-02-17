/**
 * RGRogue a rogue like adventure game
 *
 * Copyright (C) <2016>  R4nd0m 6uy
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
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _CGC_LOGGER_NULL_HPP_
#define _CGC_LOGGER_NULL_HPP_

#include "Logger.hpp"

namespace cgc{

class LoggerNull:
        public Logger
{
public:
    LoggerNull();
    virtual ~LoggerNull();

    virtual void sinkLogLine(LogLevel level, const std::string& line) override;
};

}       // namespace
#endif  // _CGC_LOGGER_NULL_HPP_
