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
#ifndef _CGC_HARDWARE_STATE_PIECE_LIFTED_HPP_
#define _CGC_HARDWARE_STATE_PIECE_LIFTED_HPP_

#include "../../../chess/GameLogic.hpp"
#include "../BitBoard.hpp"
#include "IHardwareStatePool.hpp"

namespace cgc {

/**
 * \brief An hardware state when one or more pieces have been lifted
 */
class HardwareStatePieceLifted:
    public IHardwareState
{
public:
  HardwareStatePieceLifted(IHardwareStatePool& statesPool, GameLogic& gl);
  virtual ~HardwareStatePieceLifted();

  // IHardwareState
  virtual void enter(BoardValue bv) override;
  virtual IHardwareState& execute(BoardValue bv) override;

private:
  IHardwareStatePool& m_statesPool;
  GameLogic& m_gl;
  SquaresList m_liftedPieces;
  BitBoard m_previous;
};

}       // namespace
#endif  // _CGC_HARDWARE_STATE_PIECE_LIFTED_HPP_
