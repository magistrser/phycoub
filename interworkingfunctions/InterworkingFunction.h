/*
 * @Author: Sergey Frantsishkov, mgistrser@gmail.com
 * @Date: 2019-10-25 18:30:46
 * @Last Modified by: Sergey Frantsishkov, mgistrser@gmail.com
 * @Last Modified time: 2019-10-26 11:45:58
 */

#pragma once

#include <memory>

#include "Vector.h"
#include "Particle.h"

namespace phycoub
{
/*
 * Абстрактный класс для реализации функции расчета силы.
 * Для создания собственной функции расчета силы необходимо унаследоваться от данного
 * класса и определить функцию psyForce.
 */
class InterworkingFunction
{
  public:
    virtual ~InterworkingFunction() = default;

    const virtual Vector psyForce( const Vector& field, const ParticlePtr particle ) = 0;
};

using InterworkingFunctionPtr = std::shared_ptr< InterworkingFunction >;

} // namespace phycoub
