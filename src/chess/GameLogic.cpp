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
#include <cassert>

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
  m_gh.clear();
  m_whiteCastleStatus = CastleStatus();
  m_blackCastleStatus = CastleStatus();
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
  Square sKing = this->getKingLocation(c);

  // No king found
  if(!sKing.isValid())
    return false;

  if(c == WHITE)
    this->getControlledSquares(BLACK, ctrlSquares);
  else
    this->getControlledSquares(WHITE, ctrlSquares);

  return ctrlSquares.contains(sKing);
}

//--------------------------------------------------------------------------------------------
bool GameLogic::isMated(Color c) const
{
  GameLogic gl;

  // Cannot be mated without king ...
  if(!getKingLocation(c).isValid())
    return false;

  // Set the current turn and board to check legal moves
  gl.setTurn(c);
  gl.setBoard(m_board);

  for(File f = A ; f != INVALID_FILE ; ++f)
  {
    for(Rank r = ONE ; r != INVALID_RANK ; ++r)
    {
      LegalSquares ls(Square(f, r));

      if(m_board.getPieceColor(ls.getFrom()) != c)
        continue;

      gl.getLegalSquares(ls);
      if(ls.count() > 0)
        return false;
    }
  }

  // No legal move found for this player
  return true;
}

//--------------------------------------------------------------------------------------------
bool GameLogic::isMoveLegal(const Move& m) const
{
  LegalSquares ls(m.getFrom());

  if(m_board.getPieceColor(m.getFrom()) != m_turn)
  {
    if(m_board.getPieceColor(m.getFrom()) == NO_COLOR)
      LOGER() << "No piece on " << m.getFrom();
    else
      LOGER() << "It's not " << m_board.getPieceColor(m.getFrom()) << " to play";

    return false;
  }

  this->getLegalSquares(ls);

  if(!ls.contains(m.getTo()))
  {
    LOGER() << m_board.getPiece(m.getFrom()) << " cannot move to " << m.getTo();
    return false;
  }

  // Check that promotional moves contains promotion information
  const PlayerPiece& pSrc = m_board.getPiece(m.getFrom());
  if(pSrc.getType() == PAWN && !m.hasPromotion())
  {
    bool isPromo = false;
    if(m_turn == WHITE &&
        m.getFrom().getRank() == SEVEN)
      isPromo = true;
    else if(m_turn == BLACK &&
        m.getFrom().getRank() == TWO)
      isPromo = true;

    if(isPromo)
    {
      LOGER() << "Promotion information is missing";
      return false;
    }
  }

  return true;
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

  // Save move for history
  Move mHist(m_board.getPieceType(m.getFrom()), m.getFrom(), m.getTo());
  mHist.setIsCapture(m_board.getPieceType(m.getTo()) != NO_PIECE);

  // Apply move
  m_board.setPiece(m_board.getPiece(m.getFrom()), m.getTo());
  m_board.clear(m.getFrom());

  // Apply promotional move
  if(m.hasPromotion())
  {
    m_board.setPiece(PlayerPiece(m_turn, m.getPromotion()), m.getTo());
    mHist.setPromotion(m.getPromotion());
  }

  // White castling move
  if(m_turn == WHITE &&
      m_board.getPieceType(m.getTo()) == KING &&
      m.getFrom() == Square(E, ONE))
  {
    // King side
    if(m.getTo() == Square(G, ONE))
    {
      m_board.clear(H, ONE);
      m_board.setPiece(WHITE, ROOK, F, ONE);
      mHist.setKingSideCastling(true);
    }
    // Queen side
    else if(m.getTo() == Square(C, ONE))
    {
      m_board.clear(A, ONE);
      m_board.setPiece(WHITE, ROOK, D, ONE);
      mHist.setQueenSideCastling(true);
    }

    // Once white king has moved, white cannot castle
    m_whiteCastleStatus.setCanCastleKingSide(false);
    m_whiteCastleStatus.setCanCastleQueenSide(false);
  }
  // Black castling move
  else if(m_turn == BLACK &&
        m_board.getPieceType(m.getTo()) == KING &&
        m.getFrom() == Square(E, EIGHT))
  {
    // King side
    if(m.getTo() == Square(G, EIGHT))
    {
      m_board.clear(H, EIGHT);
      m_board.setPiece(BLACK, ROOK, F, EIGHT);
      mHist.setKingSideCastling(true);
    }
    // Queen side
    else if(m.getTo() == Square(C, EIGHT))
    {
      m_board.clear(A, EIGHT);
      m_board.setPiece(BLACK, ROOK, D, EIGHT);
      mHist.setQueenSideCastling(true);
    }

    // Once black king has moved, black cannot castle
    m_blackCastleStatus.setCanCastleKingSide(false);
    m_blackCastleStatus.setCanCastleQueenSide(false);
  }

  // Update casltling information after moving the rook
  if(m_turn == BLACK &&
      m_board.getPieceType(m.getTo()) == ROOK)
  {
    if(m.getFrom() == Square(H, EIGHT))
      m_blackCastleStatus.setCanCastleKingSide(false);
    else if(m.getFrom() == Square(A, EIGHT))
      m_blackCastleStatus.setCanCastleQueenSide(false);
  }
  else if(m_turn == WHITE &&
      m_board.getPieceType(m.getTo()) == ROOK)
  {
    if(m.getFrom() == Square(H, ONE))
      m_whiteCastleStatus.setCanCastleKingSide(false);
    else if(m.getFrom() == Square(A, ONE))
      m_whiteCastleStatus.setCanCastleQueenSide(false);
  }

  // Next player turn
  if(m_turn == BLACK)
    m_turn = WHITE;
  else
    m_turn = BLACK;

  // Add check information in move history
  if(this->isChecked(m_turn))
  {
    if(this->isMated(m_turn))
      mHist.setMate(true);
    else
      mHist.setCheck(true);
  }
  m_gh.addMove(mHist);

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
const CastleStatus& GameLogic::getWhiteCastleStatus() const
{
  return m_whiteCastleStatus;
}

//--------------------------------------------------------------------------------------------
void GameLogic::setWhiteCastleStatus(const CastleStatus& cs)
{
  m_whiteCastleStatus = cs;
}

//--------------------------------------------------------------------------------------------
const CastleStatus& GameLogic::getBlackCastleStatus() const
{
  return m_blackCastleStatus;
}

//--------------------------------------------------------------------------------------------
void GameLogic::setBlackCastleStatus(const CastleStatus& cs)
{
  m_blackCastleStatus = cs;
}

//--------------------------------------------------------------------------------------------
void GameLogic::getPawnLegalSquares(LegalSquares& ls) const
{
  const Square& from = ls.getFrom();
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
    if(!this->doesMoveMakeCheck(Move(ls.getFrom(), s)))
      ls.add(s);

    if( (movedPawn.getColor() == WHITE && from.getRank() == TWO) ||
        (movedPawn.getColor() == BLACK && from.getRank() == SEVEN) )
    {
      s = Square(from.getFile(), s.getRank() + forwardDirection);
      if(m_board.isEmpty(s) && !this->doesMoveMakeCheck(Move(ls.getFrom(), s)))
        ls.add(s);
    }
  }

  // Capture right
  if(from.getFile() != H)
  {
    s = Square(from.getFile() + 1, from.getRank() + forwardDirection);
    if(!m_board.isEmpty(s) &&
        m_board.getPieceColor(s) != m_turn &&
        !this->doesMoveMakeCheck(Move(ls.getFrom(), s)))
      ls.add(s);
  }

  // Capture left
  if(from.getFile() != A)
  {
    s = Square(from.getFile() - 1, from.getRank() + forwardDirection);
    if(!m_board.isEmpty(s) &&
        m_board.getPieceColor(s) != m_turn &&
        !this->doesMoveMakeCheck(Move(ls.getFrom(), s)))
      ls.add(s);
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

        // Check that the move doesn't create any check situation for legal moves
        if(!isControlled && this->doesMoveMakeCheck(Move(ls.getFrom(), s)))
        {
          r += hDir;
          if(r == INVALID_RANK)
            break;
          else
            continue;
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
          // ... but the square is still under control
          if(isControlled)
            ls.add(s);
          break;
        }

        // Check that the move doesn't create any check situation for legal moves
        if(!isControlled && this->doesMoveMakeCheck(Move(ls.getFrom(), s)))
          break;

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

          // Check that the move doesn't create any check situation for legal moves
          if(!isControlled && this->doesMoveMakeCheck(Move(ls.getFrom(), s)))
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
  SquaresList checkedSquares;

  // Get the list of checked squares when getgting legal squares
  if(!isControlled)
  {
    Board bNoKing = m_board;
    GameLogic gl;

    bNoKing.clear(getKingLocation(m_turn));
    gl.setBoard(bNoKing);

    if(m_turn == WHITE)
      gl.getControlledSquares(BLACK, checkedSquares);
    else
      gl.getControlledSquares(WHITE, checkedSquares);
  }

  // Check each possible move
  for(int vDir = -1 ; vDir < 2 ; ++vDir)
  {
    for(int hDir = -1 ; hDir < 2 ; ++hDir)
    {
      Square s(ls.getFrom().getFile() + vDir, ls.getFrom().getRank() + hDir);

      if(!s.isValid() || s == ls.getFrom() || checkedSquares.contains(s))
        continue;

      // Piece of the same color is on target square or controlled by the opponent
      if(!m_board.isEmpty(s) &&
          m_board.getPieceColor(s) == m_board.getPieceColor(ls.getFrom()) &&
          !isControlled)
        continue;

      ls.add(s);
    }
  }

  // Check white king castling moves
  if(m_turn == WHITE &&
      ls.getFrom() == Square(E, ONE) &&
      !checkedSquares.contains(E, ONE))
  {
    // King side
    if(m_whiteCastleStatus.canCastleKingSide() &&
        m_board.getPieceColor(F, ONE) == NO_COLOR &&
        m_board.getPieceColor(G, ONE) == NO_COLOR &&
        !checkedSquares.contains(F, ONE) &&
        !checkedSquares.contains(G, ONE))
      ls.add(G, ONE);

    // Queen side
    if(m_whiteCastleStatus.canCastleKingSide() &&
        m_board.getPieceColor(B, ONE) == NO_COLOR &&
        m_board.getPieceColor(C, ONE) == NO_COLOR &&
        m_board.getPieceColor(D, ONE) == NO_COLOR &&
        !checkedSquares.contains(B, ONE) &&
        !checkedSquares.contains(C, ONE) &&
        !checkedSquares.contains(D, ONE))
      ls.add(C, ONE);
  }

  // Check black king castling moves
  else if(m_turn == BLACK &&
      ls.getFrom() == Square(E, EIGHT) &&
      !checkedSquares.contains(E, EIGHT))
  {
    // King side
    if(m_blackCastleStatus.canCastleKingSide() &&
        m_board.getPieceColor(F, EIGHT) == NO_COLOR &&
        m_board.getPieceColor(G, EIGHT) == NO_COLOR &&
        !checkedSquares.contains(F, EIGHT) &&
        !checkedSquares.contains(G, EIGHT))
      ls.add(G, EIGHT);

    // Queen side
    if(m_blackCastleStatus.canCastleQueenSide() &&
        m_board.getPieceColor(B, EIGHT) == NO_COLOR &&
        m_board.getPieceColor(C, EIGHT) == NO_COLOR &&
        m_board.getPieceColor(D, EIGHT) == NO_COLOR &&
        !checkedSquares.contains(B, EIGHT) &&
        !checkedSquares.contains(C, EIGHT) &&
        !checkedSquares.contains(D, EIGHT))
      ls.add(C, EIGHT);
  }
}

//--------------------------------------------------------------------------------------------
Square GameLogic::getKingLocation(Color c) const
{
  PlayerPiece pKing(c, KING);

  for(File f = A ; f != INVALID_FILE ; ++f)
  {
    for(Rank r = ONE ; r != INVALID_RANK ; ++r)
    {
      Square s(f, r);

      if(m_board.getPiece(s) == pKing)
        return s;
    }
  }

  LOGER() << c << " king not found on board, cannot check if checked!";
  return Square();
}

//--------------------------------------------------------------------------------------------
bool GameLogic::doesMoveMakeCheck(const Move& m) const
{
  GameLogic gl;
  PlayerPiece p = m_board.getPiece(m.getFrom());
  Board bNext = m_board;

  bNext.clear(m.getFrom());
  bNext.setPiece(p, m.getTo());
  gl.setBoard(bNext);

  return gl.isChecked(m_turn);
}

//--------------------------------------------------------------------------------------------
void GameLogic::raiseBoardChanged()
{
  for(auto& o : m_boardObservers)
    o.get().boardChanged(m_turn, getBoard());
}
}       // namespace
