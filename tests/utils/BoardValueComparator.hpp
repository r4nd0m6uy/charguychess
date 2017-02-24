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
#ifndef _CGC_BOARD_VALUE_COMPARATOR_HPP_
#define _CGC_BOARD_VALUE_COMPARATOR_HPP_

#include <sstream>

#include "ui/hardware/BoardValue.hpp"

namespace cgc{
namespace tests {

/**
 * \brief Mocks an IBoardObserver
 */
class BoardValueComparator:
    public MockNamedValueComparator
{
public:
    virtual bool isEqual(const void* object1, const void* object2)
    {
      BoardValue bv1 = *((BoardValue*)object1);
      BoardValue bv2 = *((BoardValue*)object2);

      return bv1 == bv2;
    }
    virtual SimpleString valueToString(const void* object)
    {
      std::stringstream ss;

      ss << *((BoardValue*)object) << std::endl;

      return ss.str().c_str();
    }
};

}}      // namespace
#endif  // _CGC_BOARD_VALUE_COMPARATOR_HPP_

