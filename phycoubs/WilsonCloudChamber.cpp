/*
 * @Author: Sergey Frantsishkov, mgistrser@gmail.com
 * @Date: 2020-03-28 17:16:01
 * @Last Modified by: Sergey Frantsishkov, mgistrser@gmail.com
 * @Last Modified time: 2020-03-28 22:39:54
 */

#include "WilsonCloudChamber.h"

namespace phycoub
{

WilsonCloudChamber::WilsonCloudChamber()
{
    initLog();
    initCalculationGroup();
    initElectricField();
    initMagneticField();
    initInterCommunication();
    initSourcesAndLifeTimeControllers();
    initWithParticleGroups();

    setDeltaTime( 1E-13 );
    updateUniqParticleGroupList();
}

Vector WilsonCloudChamber::getBorders() const
{
    return cyclicBorder_->getBorders();
}

void WilsonCloudChamber::setBorders( Vector borders )
{
    cyclicBorder_->setBorders( borders );
}

void WilsonCloudChamber::setElectricFieldDirection( Vector direction )
{
    electricHomogeneousDirectField_->setDirection( direction );
}

Vector WilsonCloudChamber::getElectricFieldDirection() const
{
    return electricHomogeneousDirectField_->getDirection();
}

void WilsonCloudChamber::setElectricFieldCharge( double charge )
{
    electricHomogeneousDirectField_->setCharge(
        charge * ElectricConstants::electronCharge );
}

double WilsonCloudChamber::getElectricFieldCharge() const
{
    return electricHomogeneousDirectField_->getCharge();
}

void WilsonCloudChamber::setMagneticFieldDirection( Vector direction )
{
    magneticHomogeneousDirectField_->setDirection( direction );
}

Vector WilsonCloudChamber::getMagneticFieldDirection() const
{
    return magneticHomogeneousDirectField_->getDirection();
}

void WilsonCloudChamber::setMagneticFieldInduction( double B )
{
    magneticHomogeneousDirectField_->setMagneticInduction( B );
}

double WilsonCloudChamber::getMagneticFieldInduction() const
{
    return magneticHomogeneousDirectField_->getMagneticInduction();
}

void WilsonCloudChamber::setElectronSourceDirection( Vector direction )
{
    electronConeParticleSource_->setGuideCosines( direction );
}

Vector WilsonCloudChamber::getElectronSourceDirection() const
{
    return electronConeParticleSource_->getGuideCosines();
}

void WilsonCloudChamber::setElectronSourceAngel( double angle )
{
    electronConeParticleSource_->setAngle( angle );
}

double WilsonCloudChamber::getElectronSourceAngle() const
{
    return electronConeParticleSource_->getAngle();
}

void WilsonCloudChamber::setElectronSourcBornPeriod( double bornPeriod )
{
    electronBornPeriodLifeTimeController_->setBornPeriod( bornPeriod );
}

double WilsonCloudChamber::getElectronSourceBornPeriod() const
{
    return electronBornPeriodLifeTimeController_->getBornPeriod();
}

void WilsonCloudChamber::setProtonSourceDirection( Vector direction )
{
    protonConeParticleSource_->setGuideCosines( direction );
}

Vector WilsonCloudChamber::getProtonSourceDirection() const
{
    return protonConeParticleSource_->getGuideCosines();
}

void WilsonCloudChamber::setProtonSourceAngel( double angle )
{
    protonConeParticleSource_->setAngle( angle );
}

double WilsonCloudChamber::getProtonSourceAngle() const
{
    return protonConeParticleSource_->getAngle();
}

void WilsonCloudChamber::setProtonSourcBornPeriod( double bornPeriod )
{
    protonBornPeriodLifeTimeController_->setBornPeriod( bornPeriod );
}

double WilsonCloudChamber::getProtonSourceBornPeriod() const
{
    return protonBornPeriodLifeTimeController_->getBornPeriod();
}

void WilsonCloudChamber::setSpecificSourceDirection( Vector direction )
{
    specificConeParticleSource_->setGuideCosines( direction );
}

Vector WilsonCloudChamber::getSpecificSourceDirection() const
{
    return specificConeParticleSource_->getGuideCosines();
}

void WilsonCloudChamber::setSpecificSourceAngel( double angle )
{
    specificConeParticleSource_->setAngle( angle );
}

double WilsonCloudChamber::getSpecificSourceAngle() const
{
    return specificConeParticleSource_->getAngle();
}

void WilsonCloudChamber::setSpecificSourcBornPeriod( double bornPeriod )
{
    specificBornPeriodLifeTimeController_->setBornPeriod( bornPeriod );
}

double WilsonCloudChamber::getSpecificSourceBornPeriod() const
{
    return specificBornPeriodLifeTimeController_->getBornPeriod();
}

void WilsonCloudChamber::setSpecificSourceParticleOptions( ParticleOptions options )
{
    specificConeParticleSource_->setParticleOptions( options );
}

ParticleOptions WilsonCloudChamber::getSpecificSourceParticleOptions() const
{
    return specificConeParticleSource_->getParticleOptions();
}

void WilsonCloudChamber::initLog()
{
    stdErrLog = std::make_shared< Log >();
    stdErrLogObserver = std::make_shared< StdErrLogObserver >();

    setLog( stdErrLog );
    stdErrLog->subsribeForUpdates( stdErrLogObserver );
}

void WilsonCloudChamber::initCalculationGroup()
{
    constexpr static double borderSize_ = 1.e-4;
    cyclicBorder_ = std::make_shared< CyclicBorder >( Vector{ borderSize_ } );
    cyclicBorder_->setLog( stdErrLog );

    leapFrog_ = std::make_shared< LeapFrog >();
    leapFrogCalculationGroup_
        = std::make_shared< CalculationGroup >( leapFrog_, cyclicBorder_ );

    addCalculationGroup( leapFrogCalculationGroup_ );
    addContainParticleGroup( leapFrogCalculationGroup_ );
}

void WilsonCloudChamber::initElectricField()
{
    culonInterworking_ = std::make_shared< CulonInterworking >();

    electricHomogeneousDirectField_ = std::make_shared< ElectricHomogeneousDirectField >(
        Vector{ 0, 0, 1 }, ElectricConstants::electronCharge * 0 );
    electricHomogeneousDirectFieldCreator_ = std::make_shared< HomogeneousFieldCreator >(
        electricHomogeneousDirectField_, "ElectricHomogeneousField" );
    feelElectricHomogeneousDirectWithCulonInterworking_
        = std::make_shared< FieldReceiver >( electricHomogeneousDirectFieldCreator_,
            culonInterworking_, "CulonInterworking" );

    addFieldResponsive( feelElectricHomogeneousDirectWithCulonInterworking_ );
    addContainParticleGroup( feelElectricHomogeneousDirectWithCulonInterworking_ );
}

void WilsonCloudChamber::initMagneticField()
{
    magneticHomogeneousDirectField_
        = std::make_shared< MagneticHomogeneousDirectField >( Vector{ 0, 1, 1 }, 3e-2 );
    magneticHomogeneousDirectFieldCreator_ = std::make_shared< HomogeneousFieldCreator >(
        magneticHomogeneousDirectField_, "MagneticHomogeneousField" );
    magneticInterworking_ = std::make_shared< MagneticInterworking >();
    feelWithMagneticInterworking_
        = std::make_shared< FieldReceiver >( magneticHomogeneousDirectFieldCreator_,
            magneticInterworking_, "MagneticInterworking" );

    addFieldResponsive( feelWithMagneticInterworking_ );
    addContainParticleGroup( feelWithMagneticInterworking_ );
}

void WilsonCloudChamber::initInterCommunication()
{
    borderFieldCondition_ = std::make_shared< BorderFieldCondition >();
    electricField_ = std::make_shared< ElectricField >();
    interworking_ = std::make_shared< CulonInterworking >();

    electronInterCommunication_ = std::make_shared< InterCommunication >( electricField_,
        borderFieldCondition_, interworking_, "Electron InterCommunication" );
    addFieldResponsive( electronInterCommunication_ );
    addContainParticleGroup( electronInterCommunication_ );

    protonInterCommunication_ = std::make_shared< InterCommunication >( electricField_,
        borderFieldCondition_, interworking_, "Proton InterCommunication" );
    addFieldResponsive( protonInterCommunication_ );
    addContainParticleGroup( protonInterCommunication_ );

    specificInterCommunication_ = std::make_shared< InterCommunication >( electricField_,
        borderFieldCondition_, interworking_, "Specific InterCommunication" );
    addFieldResponsive( specificInterCommunication_ );
    addContainParticleGroup( specificInterCommunication_ );

    groupInterCommunication_
        = std::make_shared< InterGroupCommunication >( electricField_,
            borderFieldCondition_, interworking_, "Group InterCommunication" );
    addFieldResponsive( groupInterCommunication_ );
    addContainParticleGroup( groupInterCommunication_ );
}

void WilsonCloudChamber::initSourcesAndLifeTimeControllers()
{
    const Vector& borders = cyclicBorder_->getBorders();
    const double bornPeriod = 1e-11;

    const Vector guideCosines{ 1., 0., 0. };
    const double coneHeight = 1.;
    const double coneAngle = 0.;
    const Vector sourceCoordinate = { 0., borders.y_ / 2, borders.z_ / 2 };
    const double energy = 1e-14;

    const ParticleOptions electronOptions{ ElectricConstants::electronWeight,
        ElectricConstants::electronCharge };
    const ParticleOptions protonOptions{ ElectricConstants::protonWeight,
        ElectricConstants::protonCharge };

    electronConeParticleSource_ = std::make_shared< ConeParticleSource >(
        guideCosines, coneHeight, coneAngle, sourceCoordinate, electronOptions, energy );
    electronBornPeriodLifeTimeController_
        = std::make_shared< BornPeriodLifeTimeController >(
            bornPeriod, electronConeParticleSource_ );

    addLifeTimeController( electronBornPeriodLifeTimeController_ );
    addContainParticleGroup( electronBornPeriodLifeTimeController_ );

    protonConeParticleSource_ = std::make_shared< ConeParticleSource >(
        guideCosines, coneHeight, coneAngle, sourceCoordinate, protonOptions, energy );
    protonBornPeriodLifeTimeController_
        = std::make_shared< BornPeriodLifeTimeController >(
            bornPeriod, protonConeParticleSource_ );

    addLifeTimeController( protonBornPeriodLifeTimeController_ );
    addContainParticleGroup( protonBornPeriodLifeTimeController_ );

    specificConeParticleSource_ = std::make_shared< ConeParticleSource >(
        guideCosines, coneHeight, coneAngle, sourceCoordinate, electronOptions, energy );
    specificBornPeriodLifeTimeController_
        = std::make_shared< BornPeriodLifeTimeController >(
            bornPeriod, specificConeParticleSource_ );

    addLifeTimeController( specificBornPeriodLifeTimeController_ );
    addContainParticleGroup( specificBornPeriodLifeTimeController_ );
}

void WilsonCloudChamber::initWithParticleGroups()
{
    ParticleGroupPtr electrons = std::make_shared< ParticleGroup >();
    ParticleGroupPtr protons = std::make_shared< ParticleGroup >();
    ParticleGroupPtr specific = std::make_shared< ParticleGroup >();

    leapFrogCalculationGroup_->addParticleGroup( electrons );
    leapFrogCalculationGroup_->addParticleGroup( protons );
    leapFrogCalculationGroup_->addParticleGroup( specific );

    feelElectricHomogeneousDirectWithCulonInterworking_->addParticleGroup( electrons );
    feelElectricHomogeneousDirectWithCulonInterworking_->addParticleGroup( protons );
    feelElectricHomogeneousDirectWithCulonInterworking_->addParticleGroup( specific );

    feelWithMagneticInterworking_->addParticleGroup( electrons );
    feelWithMagneticInterworking_->addParticleGroup( protons );
    feelWithMagneticInterworking_->addParticleGroup( specific );

    electronInterCommunication_->addParticleGroup( electrons );
    protonInterCommunication_->addParticleGroup( protons );
    specificInterCommunication_->addParticleGroup( specific );

    groupInterCommunication_->addParticleGroup( electrons );
    groupInterCommunication_->addParticleGroup( protons );
    groupInterCommunication_->addParticleGroup( specific );

    electronBornPeriodLifeTimeController_->addParticleGroup( electrons );
    protonBornPeriodLifeTimeController_->addParticleGroup( protons );
    specificBornPeriodLifeTimeController_->addParticleGroup( specific );
}

} // namespace phycoub