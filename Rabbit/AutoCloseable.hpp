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

#ifndef RABBIT_AUTOCLOSEABLE_HPP
#define RABBIT_AUTOCLOSEABLE_HPP

#include <unistd.h>

namespace Rabbit {

template<typename Resource>
class AutoCloseable
{
  private:
    Resource _resource;

  public:
    AutoCloseable(Resource);
    ~AutoCloseable();
    operator Resource() const;
};

template<typename Resource>
AutoCloseable<Resource>::AutoCloseable(Resource resource)
  : _resource(resource)
{}

template<typename Resource>
AutoCloseable<Resource>::~AutoCloseable()
{
  close(_resource);
}

template<typename Resource>
AutoCloseable<Resource>::operator Resource() const
{
  return _resource;
}

} // namespace Rabbit

#endif // RABBIT_AUTOCLOSEABLE_HPP
