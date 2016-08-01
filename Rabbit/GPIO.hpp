// This file is part of Rabbit, a C++ API of Raspberry Pi.
//
// Copyright (C) 2016 Chen-Pang He <https://jdh8.org/>
//
// Rabbit is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Rabbit is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef RABBIT_GPIO_HPP
#define RABBIT_GPIO_HPP

#include "AutoCloseable.hpp"
#include "MemoryMap.hpp"
#include <fcntl.h>

namespace Rabbit {

struct GPIO
{
  static const int Output = 1;
  static const int ALT0 = 4;
  static const int ALT1 = 5;
  static const int ALT2 = 6;
  static const int ALT3 = 7;
  static const int ALT4 = 3;
  static const int ALT5 = 2;

  MemoryMap<volatile int*> registers;

  GPIO();
  void set(int);
  void clear(int);
  int operator()() const;
};

inline GPIO::GPIO()
  : registers(AutoCloseable<int>(::open("/dev/gpiomem", O_RDWR|O_SYNC)), 45)
{}

inline void GPIO::set(int mask)
{
  registers[7] = mask;
}

inline void GPIO::clear(int mask)
{
  registers[10] = mask;
}

inline int GPIO::operator()() const
{
  return registers[13];
}

} // namespace Rabbit

#endif // RABBIT_GPIO_HPP
