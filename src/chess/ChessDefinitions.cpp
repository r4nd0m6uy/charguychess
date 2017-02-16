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
#include "ChessDefinitions.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Rank& r)
{
  if(r == ONE)
    os << "1";
  else if(r == TWO)
    os << "2";
  else if(r == THREE)
    os << "3";
  else if(r == FOUR)
    os << "4";
  else if(r == FIVE)
    os << "5";
  else if(r == SIX)
    os << "6";
  else if(r == SEVEN)
    os << "7";
  else if(r == EIGHT)
    os << "8";
  else if(r == INVALID_RANK)
    os << "invalid";
  else
    os << "unkown rank";

  return os;
}

//--------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const File& f)
{
  if(f == A)
    os << "A";
  else if(f == B)
    os << "B";
  else if(f == C)
    os << "C";
  else if(f == D)
    os << "D";
  else if(f == E)
    os << "E";
  else if(f == F)
    os << "F";
  else if(f == G)
    os << "G";
  else if(f == H)
    os << "H";
  else if(f == INVALID_FILE)
    os << "invalid";
  else
    os << "unkown rank";

  return os;
}

//--------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Color& c)
{
  if(c == WHITE)
    os << "WHITE";
  else if(c == BLACK)
    os << "black";
  else if(c == NO_COLOR)
    os << "no color";
  else
    os << "Unkown color";

  return os;
}

}       // namespace
