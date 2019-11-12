clean.bat^
 && cl -Icommon/^
    -Iborderconditions/^
    -Iborderfieldconditions/^
    -Icalculationmodels/^
    -Ifieldfunctions/^
    -Iinterworkingfunctions/^
    -Iotherobjects/^
    -Iphycoubs/^
    -Iphymeasurement/^
    -Iphyobjects/^
    -Iphyobjects/particlefigurematrix/^
    -Ispecialmodellingfunctions/^
    -Itypes/^
    /EHsc^
    /MDd^
    /c^
    borderconditions/BorderCondition.cpp^
    borderconditions/CyclicBorder.cpp^
    borderconditions/ElasticBorder.cpp^
    borderconditions/ElasticCoubCondition.cpp^
    borderconditions/ThermostatBorder.cpp^
    borderfieldconditions/BorderFieldCondition.cpp^
    borderfieldconditions/CyclicBoundedField.cpp^
    calculationmodels/CalculationModel.cpp^
    calculationmodels/HighSpeedModificationVerle.cpp^
    calculationmodels/LeapFrog.cpp^
    common/HasId.cpp^
    common/ContainParticleGroupList.cpp^
    fieldfunctions/ElectricField.cpp^
    fieldfunctions/ElectricHomogeneousField.cpp^
    fieldfunctions/ElectricHomogeneousRadialField.cpp^
    fieldfunctions/HomogeneousField.cpp^
    fieldfunctions/LDField.cpp^
    fieldfunctions/MagneticHomogeneousField.cpp^
    fieldfunctions/RadialHomogeneousField.cpp^
    interworkingfunctions/CulonInterworking.cpp^
    interworkingfunctions/LDInterworking.cpp^
    interworkingfunctions/MagneticInterworking.cpp^
    phycoubs/ArCoub.cpp^
    phycoubs/ElectronInHomogeneousFieldsCoub.cpp^
    phycoubs/FigureDemonstration.cpp^
    phycoubs/NOCoub.cpp^
    phycoubs/PhyCoub.cpp^
    phymeasurement/MeasurementUtils.cpp^
    phyobjects/CalculationGroup.cpp^
    phyobjects/DynamicFieldCreator.cpp^
    phyobjects/FieldCreator.cpp^
    phyobjects/FieldReceiver.cpp^
    phyobjects/HomogeneousFieldCreator.cpp^
    phyobjects/InterCommunication.cpp^
    phyobjects/InterGroupCommunication.cpp^
    phyobjects/InterworkingCalculatorBase.cpp^
    phyobjects/Particle.cpp^
    phyobjects/ParticleGroup.cpp^
    phyobjects/particlefigurematrix/LineFigure.cpp^
    phyobjects/particlefigurematrix/ParallelepipedFigure.cpp^
    phyobjects/particlefigurematrix/PlaneFigure.cpp^
    types/Vector.cpp^
    types/VectorUtils.cpp^
 && lib^
    /out:phycoub.lib^
    *.obj