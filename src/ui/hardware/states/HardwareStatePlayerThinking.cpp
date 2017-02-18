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
#include "../../../logging/LogMacros.hpp"
#include "../BitBoard.hpp"
#include "HardwareStatePlayerThinking.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
HardwareStatePlayerThinking::HardwareStatePlayerThinking(IHardwareStatePool& statesPool,
      GameLogic& gl):
    m_statesPool(statesPool),
    m_gl(gl)
{
}

//--------------------------------------------------------------------------------------------
HardwareStatePlayerThinking::~HardwareStatePlayerThinking()
{
}

//--------------------------------------------------------------------------------------------
void HardwareStatePlayerThinking::enter(BoardValue bv)
{
  LOGDB() << "Entering player thinking (" << m_gl.getTurn() << ")";
}

//--------------------------------------------------------------------------------------------
IHardwareState& HardwareStatePlayerThinking::execute(BoardValue bv)
{
  SquaresList changedSquares;
  BitBoard mask(m_gl.getBoard());

  LOGDB() << "Executing player thinking state ...";

  mask.getChangedSquares(bv, changedSquares);

  if(changedSquares.count() == 1)
  {
    const Square& s = changedSquares.getSquares().front();
    if(m_gl.getBoard().isEmpty(s))
    {
      // A piece was added from nowhere
      LOGWA() << "Too many pieces on the board!";
      return m_statesPool.enterState(IHardwareStatePool::PANIC, bv);
    }
    else
    {
      // A piece was lifted
      LOGDB() << "Piece on " << s << " lifted ";
      return m_statesPool.enterState(IHardwareStatePool::PLAYER_LIFTED_PIECE, bv);
    }
  }

  return m_statesPool.enterState(IHardwareStatePool::PLAYER_THINKING, bv);
}

}       // namespace
