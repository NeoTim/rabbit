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

#ifndef RABBIT_MEMORY_MAP_HPP
#define RABBIT_MEMORY_MAP_HPP

#include <sys/mman.h>

namespace Rabbit {

namespace internal {

template<typename>
struct memory_map_mode
{
  static const int value = PROT_READ | PROT_WRITE;
};

template<typename T>
struct memory_map_mode<const T>
{
  static const int value = PROT_READ;
};

} // namespace internal

template<typename>
class MemoryMap;

template<typename T>
class MemoryMap<T*>
{
  private:
    size_t _size;
    void* _map;

    MemoryMap(const MemoryMap&);
    MemoryMap& operator=(const MemoryMap&);

  public:
    MemoryMap(int, size_t = 1, off_t = 0, int = MAP_SHARED, int = internal::memory_map_mode<T>::value);
    ~MemoryMap();
    operator T*();
    operator const T*() const;
};

template<typename T>
MemoryMap<T*>::MemoryMap(int fd, size_t size, off_t offset, int flags, int mode)
  : _size(size * sizeof(T)),
    _map(mmap(0, _size, mode, flags, fd, offset))
{}

template<typename T>
MemoryMap<T*>::~MemoryMap()
{
  munmap(_map, _size);
}

template<typename T>
MemoryMap<T*>::operator T*()
{
  return static_cast<T*>(_map);
}

template<typename T>
MemoryMap<T*>::operator const T*() const
{
  return static_cast<const T*>(_map);
}

} // namespace Rabbit

#endif // RABBIT_MEMORY_MAP_HPP
