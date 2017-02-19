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
#include "../BitBoard.hpp"
#include "HardwareStateCapture.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
HardwareStateCapture::HardwareStateCapture(IHardwareStatePool& statesPool, GameLogic& gl):
    m_statesPool(statesPool),
    m_gl(gl)
{
}

//--------------------------------------------------------------------------------------------
HardwareStateCapture::~HardwareStateCapture()
{
}

//--------------------------------------------------------------------------------------------
void HardwareStateCapture::enter(BoardValue bv)
{
  // TODO TDD
  BitBoard gameState(m_gl.getBoard());
  gameState.getChangedSquares(bv, m_captureSquares);

  assert(m_captureSquares.count() == 2);

  LOGIN() << "Entering capture state (" << m_gl.getTurn() << ")";
}

//--------------------------------------------------------------------------------------------
IHardwareState& HardwareStateCapture::execute(BoardValue bv)
{
  // TODO TDD
  SquaresList captureTo;
  BitBoard gameState(m_gl.getBoard());
  gameState.getChangedSquares(bv, captureTo);

  // Too many change
  if(captureTo.count() != 1)
  {
    LOGWA() << "Cannot compute capture, too many changes";
    return m_statesPool.enterState(IHardwareStatePool::PANIC, bv);
  }
  else
  {
    const Square& s1 = m_captureSquares.getSquares().front();
    const Square& s2 = m_captureSquares.getSquares().back();
    Move m(s1, s2);

    if(m_gl.getTurn() != m_gl.getBoard().getPieceColor(s1))
      m = Move(s2, s1);

    LOGIN() << "Doing capture move " << m;
    if(m_gl.applyMove(m))
      return m_statesPool.enterState(IHardwareStatePool::PLAYER_THINKING, bv);
    else
      LOGWA() << "Illegal capture move " << m;
  }

  return m_statesPool.enterState(IHardwareStatePool::PANIC, bv);
}

}       // namespace
