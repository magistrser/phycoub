/*
 * @Author: Sergey Frantsishkov, mgistrser@gmail.com
 * @Date: 2020-03-15 23:05:16
 * @Last Modified by: Sergey Frantsishkov, mgistrser@gmail.com
 * @Last Modified time: 2020-03-30 10:42:58
 */

#pragma once

#include <memory>

#include "ParticleSourceBase.h"
#include "ConeShape.h"
#include "RotationMatrix.h"

namespace phycoub
{

class ConeParticleSource
    : public ParticleSourceBase
    , public ConeShape
{
  public:
    ConeParticleSource( const Vector& rotation, double angle,
        const Vector& sourceCoordinate, const ParticleOptions& particleOptions,
        double energy );
    virtual ~ConeParticleSource() override = default;

    void setRotation(const Vector& rotation);
    const Vector& getRotation() const;

    // Implementation of ParticleSourceBase::ParticleSourceIface
    virtual ParticlePtr phyGiveBirthParticle() override;

  private:
    Vector _rotation;
    RotationMatrix _rotationMatrix;
};

using ConeParticleSourcePtr = std::shared_ptr< ConeParticleSource >;

} // namespace phycoub