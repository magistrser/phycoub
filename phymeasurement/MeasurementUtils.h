/*
 * @Author: Sergey Frantsishkov, mgistrser@gmail.com
 * @Date: 2019-10-26 11:59:29
 * @Last Modified by: Sergey Frantsishkov, mgistrser@gmail.com
 * @Last Modified time: 2019-10-26 13:10:47
 */

#pragma once

#include <vector>

#include "ParticleGroup.h"

namespace phycoub
{

class MeasurementUtils final
{
  public:
    MeasurementUtils() = delete;

    static double getTemperature( double kB, ParticleGroupPtr particles );
    static double getTemperatureWithoutEnergyTranslationalMotionSystem(
        double kB, ParticleGroupPtr particles );

    static double getWk( ParticleGroupPtr particles );
    static double getWkWithoutTranslationalMotion( ParticleGroupPtr particles );
};

} // namespace phycoub
