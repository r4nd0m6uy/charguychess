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

  showBoard(m_gl.getTurn(), m_gl.getBoard());

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
  std::cout << "TODO: displayBoard " << std::endl;
}

}       // namespace
