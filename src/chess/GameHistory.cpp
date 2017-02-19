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
#include "GameHistory.hpp"

namespace cgc {

//--------------------------------------------------------------------------------------------
GameHistory::GameHistory()
{
  clear();
}

//--------------------------------------------------------------------------------------------
GameHistory::~GameHistory()
{
}

//--------------------------------------------------------------------------------------------
void GameHistory::clear()
{
  // TODO TDD
  m_turns.clear();
  m_turns.push_back(GameTurn());
}

//--------------------------------------------------------------------------------------------
void GameHistory::addMove(const Move& m)
{
  // TODO TDD
  GameTurn& last = m_turns.back();

  if(last.getWhiteMove().isValid())
  {
    last.setBlackMove(m);
    m_turns.push_back(GameTurn());
  }
  else
    last.setWhiteMove(m);
}

//--------------------------------------------------------------------------------------------
const std::list<GameTurn>& GameHistory::getTurns() const
{
  return m_turns;
}

//--------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const GameHistory& c)
{
  int i = 1;

  for(auto& turn : c.getTurns())
  {
    if(turn.getWhiteMove().isValid())
      os << i << ". " << turn.getWhiteMove();
    if(turn.getBlackMove().isValid())
      os << " " << turn.getBlackMove() << " ";
    else
      break;

    ++i;
  }

  return os;
}

}       // namespace
