/*
 * @Author: Sergey Frantsishkov, mgistrser@gmail.com
 * @Date: 2019-10-25 13:13:41
 * @Last Modified by: Sergey Frantsishkov, mgistrser@gmail.com
 * @Last Modified time: 2019-10-26 00:50:37
 */

#pragma once

#include <vector>
#include <string>

#include "FeelField.h"
#include "CalculationGroup.h"

namespace phycoub
{

class PhyCoub
{
  public:
    explicit PhyCoub() = default;
    virtual ~PhyCoub() = default;

    virtual void phyCoub();

    void setDeltaTime( double dt );
    double getDeltaTime() const;

    double getExperimentTime() const;

  protected:
    void addFieldResponsive( FeelFieldPtr fieldResponsive );
    void removeFieldResponsive( std::string id );

    void addCalculationGroup( CalculationGroupPtr calculationGroup );
    void removeCalculationGroup( std::string id );

  private:
    double dt_ = 0.;
    double experimentTime = 0;

    FeelFieldList fieldsResponsive_;
    CalculationGroupList calculationGroups_;
};

} // namespace phycoub