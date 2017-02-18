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
#include "HardwareStatePieceLifted.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
HardwareStatePieceLifted::HardwareStatePieceLifted(IHardwareStatePool& statesPool,
    GameLogic& gl):
  m_statesPool(statesPool),
  m_gl(gl),
  m_previous(0)
{
}

//--------------------------------------------------------------------------------------------
HardwareStatePieceLifted::~HardwareStatePieceLifted()
{
}

//--------------------------------------------------------------------------------------------
void HardwareStatePieceLifted::enter(BoardValue bv)
{
  LOGDB() << "Entering piece lifted";

  // TODO TDD
  BitBoard game(m_gl.getBoard());
  game.getChangedSquares(bv, m_liftedPieces);
  m_previous.setBoardValue(bv);
}

//--------------------------------------------------------------------------------------------
IHardwareState& HardwareStatePieceLifted::execute(BoardValue bv)
{
  // TODO TDD
  SquaresList changedSquare;
  m_previous.getChangedSquares(bv, changedSquare);

  if(changedSquare.count() == 1)
  {
    const Square& s = changedSquare.getSquares().front();

    // Piece put back
    if(m_liftedPieces.contains(s))
    {
      LOGDB() << "Piece put back on " << s;
      return m_statesPool.enterState(IHardwareStatePool::PLAYER_THINKING, bv);
    }

    // New movement
    else
    {
      Move m(m_liftedPieces.getSquares().front(), s);

      LOGIN() << m << " played on the hardware";

      if(!m_gl.applyMove(m))
      {
        LOGDB() << "Illegal move " << m;
        return m_statesPool.enterState(IHardwareStatePool::PANIC, bv);
      }
      else
        return m_statesPool.enterState(IHardwareStatePool::PLAYER_THINKING, bv);
    }
  }


  return *this;
}

}       // namespace
