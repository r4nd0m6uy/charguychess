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
  m_capPiecesWhite.clear();
  m_capPiecesBlack.clear();
  raiseBoardChanged();
}

//--------------------------------------------------------------------------------------------
void GameLogic::getLegalSquares(LegalSquares& legalSquares) const
{
  PieceType t = m_board.getPieceType(legalSquares.getFrom());

  legalSquares.clear();

  if(m_board.getPieceColor(legalSquares.getFrom()) != m_turn)
    return;
  else if(t == PAWN)
    this->getPawnLegalSquares(legalSquares);
  else if(t == BISHOP)
    this->getBishopSquares(legalSquares, false);
  else if(t == ROOK)
    this->getRookLegalSquares(legalSquares);
  else if(t == QUEEN)
    this->getQueenLegalSquares(legalSquares);
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

  // Remember captured piece
  if(!m_board.isEmpty(m.getTo()))
  {
    if(m_turn == WHITE)
      m_capPiecesBlack.push_back(m_board.getPiece(m.getTo()));
    else
      m_capPiecesWhite.push_back(m_board.getPiece(m.getTo()));
  }

  // Apply move
  m_board.setPiece(m_board.getPiece(m.getFrom()), m.getTo());
  m_board.setPiece(PlayerPiece(), m.getFrom());

  // Next player turn
  if(m_turn == BLACK)
    m_turn = WHITE;
  else
    m_turn = BLACK;

  m_gh.addMove(m);  // TODO TDD

  raiseBoardChanged();

  return true;
}

//--------------------------------------------------------------------------------------------
const std::list<PlayerPiece>& GameLogic::getCapturedWhitePieces() const
{
  return m_capPiecesWhite;
}

//--------------------------------------------------------------------------------------------
const std::list<PlayerPiece>& GameLogic::getCapturedBlackPieces() const
{
  return m_capPiecesBlack;
}

//--------------------------------------------------------------------------------------------
const GameHistory& GameLogic::getGameHistory() const
{
  return m_gh;
}

//--------------------------------------------------------------------------------------------
void GameLogic::getControlledSquares(Color c, SquaresList& sl)
{
  sl.clear();

  for(File f = A ; f != INVALID_FILE ; ++f)
  {
    for(Rank r = ONE ; r != INVALID_RANK ; ++r)
    {
      Square s(f, r);

      if(m_board.getPieceColor(s) == c)
      {
        LegalSquares ls(s);
        PieceType t = m_board.getPieceType(s);

        if(t == PAWN)
          this->getPawnControlledSquares(ls);
        else if(t == BISHOP)
          this->getBishopSquares(ls, true);
        else if(t == ROOK)
          this->getRookLegalSquares(ls);
        else if(t == QUEEN)
          this->getQueenLegalSquares(ls);

        sl.append(ls.getSquaresList());
      }
    }
  }
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
  Square s(from.getFile(), from.getRank() + forwardDirection);
  if(m_board.isEmpty(s))
  {
    legalSquares.add(s);

    if( (movedPawn.getColor() == WHITE && from.getRank() == TWO) ||
        (movedPawn.getColor() == BLACK && from.getRank() == SEVEN) )
    {
      s = Square(from.getFile(), s.getRank() + forwardDirection);
      if(m_board.isEmpty(s))
        legalSquares.add(s);
    }
  }

  // Capture right
  if(from.getFile() != H)
  {
    s = Square(from.getFile() + 1, from.getRank() + forwardDirection);
    if(!m_board.isEmpty(s) && m_board.getPieceColor(s) != m_turn)
      legalSquares.add(s);
  }

  // Capture left
  if(from.getFile() != A)
  {
    s = Square(from.getFile() - 1, from.getRank() + forwardDirection);
    if(!m_board.isEmpty(s) && m_board.getPieceColor(s) != m_turn)
      legalSquares.add(s);
  }
}

//--------------------------------------------------------------------------------------------
void GameLogic::getPawnControlledSquares(LegalSquares& legalSquares) const
{
  Square s;
  const Square& from = legalSquares.getFrom();
  PlayerPiece movedPawn = m_board.getPiece(from);
  int forwardDirection;

  if(movedPawn.getColor() == WHITE)
    forwardDirection = 1;
  else
    forwardDirection = -1;

  // Move right
  if(from.getFile() != H)
    legalSquares.add(Square(from.getFile() + 1, from.getRank() + forwardDirection));

  // Move left
  if(from.getFile() != A)
    legalSquares.add(Square(from.getFile() - 1, from.getRank() + forwardDirection));

}

//--------------------------------------------------------------------------------------------
void GameLogic::getBishopSquares(LegalSquares& ls, bool isControlled) const
{
  for(int vDir = -1 ; vDir <= 1 ; vDir += 2)
  {
    for(int hDir = -1 ; hDir <= 1 ; hDir += 2)
    {
      Rank r = ls.getFrom().getRank() + hDir;

      if(r != INVALID_RANK)
      {
        for(File f = ls.getFrom().getFile() + vDir ; f != INVALID_FILE ; f += vDir)
        {
          Square s(f, r);

          // Piece of the same color is blocking the way
          if(!m_board.isEmpty(s) &&
              m_board.getPieceColor(s) == m_board.getPieceColor(ls.getFrom()))
          {
            if(isControlled)
              ls.add(s);
            break;
          }

          ls.add(s);

          // Piece of opposite color is blocking the way
          if(!m_board.isEmpty(s) &&
              m_board.getPieceColor(s) != m_board.getPieceColor(ls.getFrom()))
            break;

          r = r + hDir;
          if(r == INVALID_RANK)
            break;
        }
      }
    }
  }
}

//--------------------------------------------------------------------------------------------
void GameLogic::getRookLegalSquares(LegalSquares& ls) const
{
  for(int vDir = -1 ; vDir <= 1 ; ++vDir)
  {
    for(int hDir = -1 ; hDir <= 1 ; ++hDir)
    {
      // Check vertical squares
      if(vDir == 0 && hDir != 0)
      {
        Rank r = ls.getFrom().getRank();
        for(File f = ls.getFrom().getFile() + hDir ; f != INVALID_FILE ; f += hDir)
        {
          Square s(f, r);

          // Piece of the same color is blocking the way
          if(!m_board.isEmpty(s) &&
              m_board.getPieceColor(s) == m_board.getPieceColor(ls.getFrom()))
            break;

          ls.add(s);

          // Piece of opposite color is blocking the way
          if(!m_board.isEmpty(s) &&
              m_board.getPieceColor(s) != m_board.getPieceColor(ls.getFrom()))
            break;
        }
      }

      // Check horizontal squares
      else if(hDir == 0 && vDir != 0)
      {
        File f = ls.getFrom().getFile();
        for(Rank r = ls.getFrom().getRank() + vDir ; r != INVALID_RANK ; r += vDir)
        {
          Square s(f, r);

          // Piece of the same color is blocking the way
          if(!m_board.isEmpty(s) &&
              m_board.getPieceColor(s) == m_board.getPieceColor(ls.getFrom()))
            break;

          ls.add(s);

          // Piece of opposite color is blocking the way
          if(!m_board.isEmpty(s) &&
              m_board.getPieceColor(s) != m_board.getPieceColor(ls.getFrom()))
            break;
        }
      }
    }
  }
}

//--------------------------------------------------------------------------------------------
void GameLogic::getQueenLegalSquares(LegalSquares& legalSquares) const
{
  this->getBishopSquares(legalSquares, false);
  this->getRookLegalSquares(legalSquares);
}

//--------------------------------------------------------------------------------------------
void GameLogic::raiseBoardChanged()
{
  for(auto& o : m_boardObservers)
    o.get().boardChanged(m_turn, getBoard());
}
}       // namespace
