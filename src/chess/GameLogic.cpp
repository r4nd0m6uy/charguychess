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
#include <algorithm>

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
void GameLogic::registerBoardObserver(IBoardObserver& observer)
{
  m_boardObservers.push_back(observer);
}

//--------------------------------------------------------------------------------------------
void GameLogic::newGame()
{
  m_turn = WHITE;
  m_board = Board();
  raiseBoardChanged();
}

//--------------------------------------------------------------------------------------------
void GameLogic::getLegalSquares(LegalSquares& legalSquares) const
{
  PieceType t = m_board.getPieceType(legalSquares.getFrom());

  legalSquares.clear();

  if(t == PAWN)
    this->getPawnLegalSquares(legalSquares);
}

//--------------------------------------------------------------------------------------------
bool GameLogic::isMoveLegal(const Move& m) const
{
  LegalSquares ls(m.getFrom());

  if(m_board.getPieceColor(m.getFrom()) != m_turn)
    return false;

  this->getLegalSquares(ls);

  return ls.contains(m.getTo());
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

  raiseBoardChanged();

  return true;
}

//--------------------------------------------------------------------------------------------
void GameLogic::getPawnLegalSquares(LegalSquares& legalSquares) const
{
  const Square& from = legalSquares.getFrom();
  PlayerPiece movedPawn = m_board.getPiece(from);
  int forwardDirection;

  if(movedPawn.getColor() == WHITE)
    forwardDirection = 1;
  else
    forwardDirection = -1;

  // Move forward
  Square s(from.getFile(), static_cast<Rank>(from.getRank() + forwardDirection));
  if(m_board.isEmpty(s))
  {
    legalSquares.addLegalSquare(s);

    if( (movedPawn.getColor() == WHITE && from.getRank() == TWO) ||
        (movedPawn.getColor() == BLACK && from.getRank() == SEVEN) )
    {
      s = Square(from.getFile(), static_cast<Rank>(s.getRank() + forwardDirection));
      if(m_board.isEmpty(s))
        legalSquares.addLegalSquare(s);
    }
  }

  // Capture right
  if(from.getFile() != H)
  {
    s = Square(
        static_cast<File>(from.getFile() + 1),
        static_cast<Rank>(from.getRank() + forwardDirection));
    if(!m_board.isEmpty(s) && m_board.getPieceColor(s) != m_turn)
      legalSquares.addLegalSquare(s);
  }

  // Capture left
  if(from.getFile() != A)
  {
    s = Square(
        static_cast<File>(from.getFile() - 1),
        static_cast<Rank>(from.getRank() + forwardDirection));
    if(!m_board.isEmpty(s) && m_board.getPieceColor(s) != m_turn)
      legalSquares.addLegalSquare(s);
  }
}

//--------------------------------------------------------------------------------------------
void GameLogic::raiseBoardChanged()
{
  for(auto& o : m_boardObservers)
    o.get().boardChanged(m_turn, getBoard());
}
}       // namespace
