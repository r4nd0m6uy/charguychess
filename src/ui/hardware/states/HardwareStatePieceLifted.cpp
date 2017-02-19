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

#include "../../../logging/LogMacros.hpp"
#include "HardwareStatePieceLifted.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
HardwareStatePieceLifted::HardwareStatePieceLifted(IHardwareStatePool& statesPool,
    GameLogic& gl):
  m_statesPool(statesPool),
  m_gl(gl)
{
}

//--------------------------------------------------------------------------------------------
HardwareStatePieceLifted::~HardwareStatePieceLifted()
{
}

//--------------------------------------------------------------------------------------------
void HardwareStatePieceLifted::enter(BoardValue bv)
{
  LOGIN() << "Entering piece lifted (" << m_gl.getTurn() << ")";
}

//--------------------------------------------------------------------------------------------
IHardwareState& HardwareStatePieceLifted::execute(BoardValue bv)
{
  BitBoard gameStatus(m_gl.getBoard());
  SquaresList changedSquares;

  gameStatus.getChangedSquares(bv, changedSquares);

  // Back to the game status
  if(changedSquares.count() == 0)
    return m_statesPool.enterState(IHardwareStatePool::PLAYER_THINKING, bv);

  // Not enough change to compute the move
  if(changedSquares.count() == 1)
    return m_statesPool.enterState(IHardwareStatePool::PLAYER_LIFTED_PIECE, bv);

  if(changedSquares.count() == 2)
  {
    LegalSquares ls1(changedSquares.getSquares().front());
    LegalSquares ls2(changedSquares.getSquares().back());

    m_gl.getLegalSquares(ls1);
    m_gl.getLegalSquares(ls2);

    // Invalid move
    if(ls1.count() == 0 && ls2.count() == 0)
      LOGWA() << "No legal move from " << ls1.getFrom() << " neither from " << ls2.getFrom();

    // Two pieces of the same color lifted
    else if(ls1.count() > 0 && ls2.count() > 0)
      LOGWA() << "Two piece of the same player lifted on " << ls1.getFrom() <<
        " and " << ls2.getFrom();

    // Legal move
    else
    {
      Move m(ls1.getFrom(), ls2.getFrom());

      if(ls1.count() == 0)
        m = Move(ls2.getFrom(), ls1.getFrom());

      if(!m_gl.applyMove(m))
        LOGWA() << "Illegal move " << m;
      else
      {
        LOGIN() << m_gl.getTurn() << " plays " << m << " on the hardware";
        return m_statesPool.enterState(IHardwareStatePool::PLAYER_THINKING, bv);
      }
    }
  }
  else
    LOGWA() << "Too many squares have changed at once";

  return m_statesPool.enterState(IHardwareStatePool::PANIC, bv);
}

}       // namespace
