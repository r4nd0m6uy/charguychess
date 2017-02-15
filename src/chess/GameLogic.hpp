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
#ifndef _CGC_GAME_LOGIC_HPP_
#define _CGC_GAME_LOGIC_HPP_

#include <list>
#include <functional>

#include "Board.hpp"
#include "Move.hpp"
#include "LegalSquares.hpp"
#include "IBoardObserver.hpp"

namespace cgc {

/**
 * \brief All the chess logic implementation
 */
class GameLogic
{
public:
  GameLogic();
  ~GameLogic();

  Color getTurn() const;
  void setTurn(Color color);
  const Board& getBoard() const;
  void setBoard(const Board& board);
  void registerBoardObserver(IBoardObserver& observer);
  void newGame();
  void getLegalSquares(LegalSquares& legalSquares) const;
  bool isMoveLegal(const Move& m) const;
  bool applyMove(const Move& m);

private:
  Board m_board;
  Color m_turn;
  std::list<std::reference_wrapper<IBoardObserver> > m_boardObservers;

  void getPawnLegalSquares(LegalSquares& legalSquares) const;
  void raiseBoardChanged();
};

}       // namespace
#endif  // _CGC_GAME_LOGIC_HPP_
