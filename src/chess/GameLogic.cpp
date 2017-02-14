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
#include <cmath>

#include "GameLogic.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
GameLogic::GameLogic():
    m_turn(WHITE)
{
}

//--------------------------------------------------------------------------------------------
GameLogic::~GameLogic()
{
}

//--------------------------------------------------------------------------------------------
Color GameLogic::getTurn() const
{
  return m_turn;
}


//--------------------------------------------------------------------------------------------
void GameLogic::setTurn(Color color)
{
  // This is not allowed
  if(color == NO_COLOR)
    return;

  m_turn = color;
}

//--------------------------------------------------------------------------------------------
const Board& GameLogic::getBoard() const
{
  return m_board;
}

//--------------------------------------------------------------------------------------------
void GameLogic::setBoard(const Board& board)
{
  m_board = board;
}

//--------------------------------------------------------------------------------------------
bool GameLogic::applyMove(const Move& m)
{
  PlayerPiece movedPiece = m_board.getPiece(m.getFrom());

  // The source piece must be player's color
  if(movedPiece.getColor() != m_turn)
    return false;

  // Check if legal
  if(movedPiece.getPiece() == PAWN)
  {
    // Pawn moves forward
    if(m.getFrom().getFile() == m.getTo().getFile())
    {
      unsigned int forwardCount = std::abs(m.getTo().getRank() - m.getFrom().getRank());

      // Can moves two foward only from start position
      if(forwardCount == 2)
      {
        if( (m_turn == WHITE && m.getFrom().getRank() != TWO) ||
            (m_turn == BLACK && m.getFrom().getRank() != SEVEN) )
          return false;
      }
      // Can move only one forward the rest of the time
      else if(forwardCount != 1)
        return false;

      // Can move forward only if square is free
      if(m_board.getPiece(m.getTo()).getColor() != NO_COLOR)
        return false;
    }
    // Pawn captures a piece
    else
    {
      return false;
    }
  }

  // Apply move
  m_board.setPiece(PlayerPiece(), m.getFrom());
  m_board.setPiece(movedPiece, m.getTo());

  // Next player turn
  if(m_turn == BLACK)
    m_turn = WHITE;
  else
    m_turn = BLACK;

  return true;
}

}       // namespace
