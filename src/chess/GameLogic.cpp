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

#include "../logging/LogMacros.hpp"
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
  m_board.initialPosition();
  m_capPiecesWhite.clear();
  m_capPiecesBlack.clear();
  raiseBoardChanged();
}

//--------------------------------------------------------------------------------------------
void GameLogic::getLegalSquares(LegalSquares& ls) const
{
  PieceType t = m_board.getPieceType(ls.getFrom());

  ls.clear();

  if(m_board.getPieceColor(ls.getFrom()) != m_turn)
    return;
  else if(t == PAWN)
    this->getPawnLegalSquares(ls);
  else if(t == BISHOP)
    this->getBishopSquares(ls, false);
  else if(t == ROOK)
    this->getRookSquares(ls, false);
  else if(t == QUEEN)
    this->getQueenSquares(ls, false);
  else if(t == KNIGHT)
    this->getKnightSquares(ls, false);
  else if(t == KING)
    this->getKingSquares(ls, false);
}

//--------------------------------------------------------------------------------------------
bool GameLogic::isChecked(Color c) const
{
  SquaresList ctrlSquares;
  PlayerPiece pKing(c, KING);
  Square sKing;

  // Look for king
  for(File f = A ; f != INVALID_FILE ; ++f)
  {
    for(Rank r = ONE ; r != INVALID_RANK ; ++r)
    {
      Square s(f, r);

      if(m_board.getPiece(s) == pKing)
      {
        sKing = s;
        break;
      }
    }
  }

  // Only allowed in unit testing
  if(!sKing.isValid())
  {
    LOGER() << c << " king not found on board, cannot check if checked!";
    return false;
  }

  if(c == WHITE)
    this->getControlledSquares(BLACK, ctrlSquares);
  else
    this->getControlledSquares(WHITE, ctrlSquares);

  return ctrlSquares.contains(sKing);
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
void GameLogic::getControlledSquares(Color c, SquaresList& sl) const
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
          this->getRookSquares(ls, true);
        else if(t == QUEEN)
          this->getQueenSquares(ls, true);
        else if(t == KNIGHT)
          this->getKnightSquares(ls, true);
        else if(t == KING)
          this->getKingSquares(ls, true);

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

      if(r == INVALID_RANK)
        continue;

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

//--------------------------------------------------------------------------------------------
void GameLogic::getRookSquares(LegalSquares& ls, bool isControlled) const
{
  for(int vDir = -1 ; vDir <= 1 ; ++vDir)
  {
    for(int hDir = -1 ; hDir <= 1 ; ++hDir)
    {
      // Only vertical and horizontal moves
      if( (vDir == 0 && hDir == 0) ||
          (vDir != 0 && hDir != 0) )
        continue;

      Rank r = ls.getFrom().getRank() + vDir;
      File f = ls.getFrom().getFile() + hDir;

      while(r != INVALID_RANK && f != INVALID_FILE)
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

        r += vDir;
        f += hDir;
      }
    }
  }
}

//--------------------------------------------------------------------------------------------
void GameLogic::getQueenSquares(LegalSquares& legalSquares, bool isControlled) const
{
  this->getBishopSquares(legalSquares, isControlled);
  this->getRookSquares(legalSquares, isControlled);
}

//--------------------------------------------------------------------------------------------
void GameLogic::getKnightSquares(LegalSquares& ls, bool isControlled) const
{
  for(int vDir = -2 ; vDir <= 2 ; vDir += 2)
  {
    for(int hDir = -2 ; hDir <= 2 ; hDir += 2)
    {
      int vDir2 = 0;
      int hDir2 = 0;

      // Only vertical and horizontal moves
      if( (vDir == 0 && hDir == 0) ||
          (vDir != 0 && hDir != 0) )
        continue;

      // First jump that is two square horizontal or vertical
      Square jump1(ls.getFrom().getFile() + hDir, ls.getFrom().getRank() + vDir);

      if(!jump1.isValid())
        continue;

      // Next jump opposite direction
      if(vDir == 0)
        vDir2 = -1;
      else
        hDir2 = -1;

      while(hDir2 < 2 && vDir2 < 2)
      {
        Square s(jump1.getFile() + hDir2, jump1.getRank() + vDir2);

        if(vDir2 != 0)
          vDir2 += 2;
        else
          hDir2 += 2;

        if(s.isValid())
        {
          // Piece of the same color is on target square
          if(!m_board.isEmpty(s) &&
              m_board.getPieceColor(s) == m_board.getPieceColor(ls.getFrom()) &&
              !isControlled)
            continue;

          ls.add(s);
        }
      }
    }
  }
}

//--------------------------------------------------------------------------------------------
void GameLogic::getKingSquares(LegalSquares& ls, bool isControlled) const
{
  for(int vDir = -1 ; vDir < 2 ; ++vDir)
  {
    for(int hDir = -1 ; hDir < 2 ; ++hDir)
    {
      Square s(ls.getFrom().getFile() + vDir, ls.getFrom().getRank() + hDir);

      if(!s.isValid() || s == ls.getFrom())
        continue;

      // Piece of the same color is on target square
      if(!m_board.isEmpty(s) &&
          m_board.getPieceColor(s) == m_board.getPieceColor(ls.getFrom()) &&
          !isControlled)
        continue;

      ls.add(s);
    }
  }
}

//--------------------------------------------------------------------------------------------
void GameLogic::raiseBoardChanged()
{
  for(auto& o : m_boardObservers)
    o.get().boardChanged(m_turn, getBoard());
}
}       // namespace
