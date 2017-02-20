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
Rank& operator--(Rank& r)
{
  r = r - 1;
  return r;
}

//--------------------------------------------------------------------------------------------
Rank& operator++(Rank& r)
{
  r = r + 1;
  return r;
}

//--------------------------------------------------------------------------------------------
Rank operator+(const Rank& r, const int& i)
{
  int rInt = (int)r + i;

  if(r == INVALID_RANK)
    return INVALID_RANK;

  if(rInt > LAST_RANK || rInt < ONE)
    return INVALID_RANK;

  return static_cast<Rank>(rInt);
}

//--------------------------------------------------------------------------------------------
Rank operator-(const Rank& r, const int& i)
{
  int rInt = (int)r - i;

  if(r == INVALID_RANK)
    return INVALID_RANK;

  if(rInt > LAST_RANK || rInt < ONE)
    return INVALID_RANK;

  return static_cast<Rank>(rInt);
}

//--------------------------------------------------------------------------------------------
Rank& operator+=(Rank& r, const int& i)
{
  r = r + i;
  return r;
}

//--------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const File& f)
{
  if(f == A)
    os << "a";
  else if(f == B)
    os << "b";
  else if(f == C)
    os << "c";
  else if(f == D)
    os << "d";
  else if(f == E)
    os << "e";
  else if(f == F)
    os << "f";
  else if(f == G)
    os << "g";
  else if(f == H)
    os << "h";
  else if(f == INVALID_FILE)
    os << "invalid";
  else
    os << "unkown rank";

  return os;
}

//--------------------------------------------------------------------------------------------
File& operator--(File& f)
{
  f = f - 1;
  return f;
}

//--------------------------------------------------------------------------------------------
File& operator++(File& f)
{
  f = f + 1;
  return f;
}

//--------------------------------------------------------------------------------------------
File operator+(const File& f, const int& i)
{
  int fInt = (int)f + i;

  if(f == INVALID_FILE)
    return INVALID_FILE;

  if(fInt > LAST_FILE || fInt < A)
    return INVALID_FILE;

  return static_cast<File>(fInt);
}

//--------------------------------------------------------------------------------------------
File operator-(const File& f, const int& i)
{
  int fInt = (int)f - i;

  if(f == INVALID_FILE)
    return INVALID_FILE;

  if(fInt > LAST_FILE || fInt < A)
    return INVALID_FILE;

  return static_cast<File>(fInt);
}

//--------------------------------------------------------------------------------------------
File& operator+=(File& f, const int& i)
{
  f = f + i;

  return f;
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

//--------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const PieceType& pt)
{
  if(pt == NO_PIECE)
    os << "NOPIECE";
  else if(pt == KING)
    os << "K";
  else if(pt == QUEEN)
    os << "Q";
  else if(pt == ROOK)
    os << "R";
  else if(pt == BISHOP)
    os << "B";
  else if(pt == KNIGHT)
    os << "N";
  else if(pt == PAWN)
    os << "P";
  else
    os << "UNKNOWN PIECE";

  return os;
}

}       // namespace
