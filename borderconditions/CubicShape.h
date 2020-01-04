/*
 * @Author: Sergey Frantsishkov, mgistrser@gmail.com
 * @Date: 2020-01-04 14:17:09
 * @Last Modified by: Sergey Frantsishkov, mgistrser@gmail.com
 * @Last Modified time: 2020-01-04 14:23:23
 */

#pragma once

#include "Vector.h"

namespace phycoub
{

class CubicShape
{
  public:
    CubicShape( const Vector& borders );
    virtual ~CubicShape() = default;

    void setBorders( const Vector& borders );
    const Vector& getBorders() const;

  private:
    Vector borders_;
};

} // namespace phycoub