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
#ifndef _CGC_I_HARDWARE_STATE_POOL_MOCK_HPP_
#define _CGC_I_HARDWARE_STATE_POOL_MOCK_HPP_

#include "ui/hardware/states/IHardwareStatePool.hpp"

namespace cgc {
namespace tests {

/**
 * \brief Mocks an IHardwareStatePool
 */
class IHardwareStatePoolMock:
    public IHardwareStatePool
{
public:
  IHardwareStatePoolMock();
  virtual ~IHardwareStatePoolMock();

  virtual IHardwareState& enterState(IHardwareStatePool::State which) override;
};

}}      // namespace
#endif  // _CGC_I_HARDWARE_STATE_POOL_MOCK_HPP_
