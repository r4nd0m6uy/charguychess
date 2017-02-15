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
void GameLogic::getLegalMoves(const Square& from, std::list<Square>& legalMoves)
{
  PlayerPiece movedPiece = m_board.getPiece(from);

  if(movedPiece.getPiece() == PAWN)
  {
    int forwardDirection;

    if(movedPiece.getColor() == WHITE)
      forwardDirection = 1;
    else
      forwardDirection = -1;

    // Move forward
    Square s(from.getFile(), static_cast<Rank>(from.getRank() + forwardDirection));
    if(m_board.isEmpty(s))
    {
      legalMoves.push_back(s);

      if( (movedPiece.getColor() == WHITE && from.getRank() == TWO) ||
          (movedPiece.getColor() == BLACK && from.getRank() == SEVEN) )
      {
        s = Square(from.getFile(), static_cast<Rank>(s.getRank() + forwardDirection));
        if(m_board.isEmpty(s))
          legalMoves.push_back(s);
      }
    }

    // Capture right
    if(from.getFile() != H)
    {
      s = Square(
          static_cast<File>(from.getFile() + 1),
          static_cast<Rank>(from.getRank() + forwardDirection));
      if(!m_board.isEmpty(s) && m_board.getPieceColor(s) != m_turn)
        legalMoves.push_back(s);
    }

    // Capture left
    if(from.getFile() != A)
    {
      s = Square(
          static_cast<File>(from.getFile() - 1),
          static_cast<Rank>(from.getRank() + forwardDirection));
      if(!m_board.isEmpty(s) && m_board.getPieceColor(s) != m_turn)
        legalMoves.push_back(s);
    }
  }
}

//--------------------------------------------------------------------------------------------
bool GameLogic::isMoveLegal(const Move& m) const
{
  PlayerPiece movedPiece = m_board.getPiece(m.getFrom());

  // The source piece must be player's color
  if(movedPiece.getColor() != m_turn)
    return false;

  // Pawn move
  if(movedPiece.getPiece() == PAWN)
  {
    unsigned int sideCount = std::abs(m.getFrom().getFile() - m.getTo().getFile());
    int fwCnt = m.getTo().getRank() - m.getFrom().getRank();
    int fwCntAbs = std::abs(fwCnt);
    const PlayerPiece& capturedPiece = m_board.getPiece(m.getTo());

    // Pawn moves forward
    if(sideCount == 0)
    {
      // Can only move forward
      if( (fwCnt < 0 && m_turn == WHITE) ||
          (fwCnt > 0 && m_turn == BLACK) )
        return false;

      // Can move two foward only from start position
      if(fwCntAbs == 2)
      {
        if( (m_turn == WHITE && m.getFrom().getRank() != TWO) ||
            (m_turn == BLACK && m.getFrom().getRank() != SEVEN) )
          return false;
      }

      // Can move only one forward the rest of the time
      else if(fwCntAbs != 1)
        return false;

      // Can move forward only if square is free
      if(capturedPiece.getColor() != NO_COLOR)
        return false;
    }
    else
    {
      // Only one rank forward
      if(fwCntAbs != 1)
        return false;

      // Only one file beside
      if(sideCount != 1)
        return false;

      // Only if there is a piece of the opposite color
      if(capturedPiece.getColor() == NO_COLOR || capturedPiece.getColor() == m_turn)
        return false;
    }
  }
  else
  {
    // Not implemented
    return false;
  }

  return true;
}

//--------------------------------------------------------------------------------------------
bool GameLogic::applyMove(const Move& m)
{
  // Precondition
  if(!isMoveLegal(m))
    return false;

  // Apply move
  m_board.setPiece(m_board.getPiece(m.getFrom()), m.getTo());
  m_board.setPiece(PlayerPiece(), m.getFrom());

  // Next player turn
  if(m_turn == BLACK)
    m_turn = WHITE;
  else
    m_turn = BLACK;

  return true;
}

}       // namespace
