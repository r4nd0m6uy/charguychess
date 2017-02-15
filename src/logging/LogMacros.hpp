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
#ifndef _CGC_LOG_MACROS_HPP_
#define _CGC_LOG_MACROS_HPP_

#include "LoggerInstance.hpp"

#define LOGDB()     (*cgc::LoggerInstance::getInstance()).getLogStream(cgc::ILogSink::DEBUG).get()
#define LOGIN()     (*cgc::LoggerInstance::getInstance()).getLogStream(cgc::ILogSink::INFO).get()
#define LOGWA()     (*cgc::LoggerInstance::getInstance()).getLogStream(cgc::ILogSink::WARNING).get()
#define LOGER()     (*cgc::LoggerInstance::getInstance()).getLogStream(cgc::ILogSink::ERROR).get()
#define LOG()       LOGIN()

#endif  // _CGC_LOG_MACROS_HPP_
