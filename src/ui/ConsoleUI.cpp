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
#include <iostream>

#include "ConsoleUI.hpp"

namespace cgc {

static const std::string RANK_SEPARATOR = " +---+---+---+---+---+---+---+---+";
static const std::string PROMPT = "charguychess> ";

//--------------------------------------------------------------------------------------------
ConsoleUI::ConsoleUI(GameLogic& gl):
    m_gl(gl)
{
}

//--------------------------------------------------------------------------------------------
ConsoleUI::~ConsoleUI()
{
}

//--------------------------------------------------------------------------------------------
int ConsoleUI::init()
{
  m_gl.registerBoardObserver(*this);
  printGreeting();
  showBoard(m_gl.getTurn(), m_gl.getBoard());
  std::cout << PROMPT;

  return 0;
}

//--------------------------------------------------------------------------------------------
void ConsoleUI::boardChanged(Color playerTurn, const Board& newStatus)
{
  showBoard(playerTurn, newStatus);
}

//--------------------------------------------------------------------------------------------
void ConsoleUI::showBoard(Color playerTurn, const Board& newStatus)
{
  std::cout << "Current position: " << std::endl;
  std::cout << RANK_SEPARATOR;

  if(playerTurn == WHITE)
    std::cout << "   * ";
  else
    std::cout << "     ";

  std::cout << "white" << std::endl;

  for(Rank r = EIGHT ; r >= ONE ; )
  {
    std::cout << r + 1 << "|";

    for(File f = A ; f <= H ; )
    {
      std::cout << " " <<  m_gl.getBoard().getPiece(Square(f, r)) << " |";

      f = static_cast<File>(f + 1);
    }

    if(r == EIGHT)
    {
      if(playerTurn == BLACK)
        std::cout << "   * ";
      else
        std::cout << "     ";

      std::cout << "black";
    }

    std::cout << std::endl << RANK_SEPARATOR << std::endl;

    r = static_cast<Rank>(r - 1);
  }

  std::cout <<"   A   B   C   D   E   F   G   H" << std::endl;
}

//--------------------------------------------------------------------------------------------
void ConsoleUI::printGreeting()
{
  std::cout << "Welcome to charguy chess!" << std::endl;
  std::cout << "Type 'help' for the list of available commands" << std::endl << std::endl;
}

}       // namespace
