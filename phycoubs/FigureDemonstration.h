/*
 * FigureDemonstration.h
 *
 *  Created on: Dec 22, 2016
 *      Author: root
 */

#ifndef FIGUREDEMONSTRATION_H_
#define FIGUREDEMONSTRATION_H_

#include <vector>
#include <math.h>

#include "Vector.h"
#include "Particle.h"
#include "CreateField.h"
#include "FeelField.h"

#include "ElasticCoubCondition.h"
#include "BorderFieldCondition.h"
#include "HighSpeedModificationVerle.h"
#include "LeapFrog.h"
#include "LDFieldFunction.h"
#include "LDInterworking.h"

#include "CyclicBorder.h"
#include "CyclicBoundedField.h"

#include "LineFigure.h"
#include "PlaneFigure.h"
#include "ParallelepipedFigure.h"

namespace phycoub
{

class FigureDemonstration
{
public:
	FigureDemonstration();
	virtual ~FigureDemonstration();

	void phyCoub();

	double dt_ = 1E-15, k_ = 1.38E-23, z_ = 0.;
	Vector borders_{1E-8, 1E-8, 1E-8};
	double mN_ = 23.24E-27, epsN = 95.05 * k_, aN = 3.698E-10;
	double radiusCat_ = aN * 3;

	LineFigure lineN{Vector(0, 0, aN * 2.), 2, Vector(5E-9), Vector(0, 0, .0), mN_, z_, &elasticBorder_};
	PlaneFigure planeN{Vector(0, 0, aN *pow(2, 1 / 6.)), Vector(0, aN *pow(2, 1 / 6.), 0), 20, 20, Vector(1E-9), Vector(0, 0, 0), mN_, z_, &elasticBorder_};
	ParallelepipedFigure parallelepipedN{Vector(0, 0, aN *pow(2, 1 / 6.)), Vector(0, aN *pow(2, 1 / 6.), 0), Vector(aN *pow(2, 1 / 6.), 0, 0), 10, 10, 10, Vector(1E-9), Vector(0, 0, 0), mN_, z_, &elasticBorder_};

private:
	ElasticCoubCondition elasticBorder_{&borders_};
	BorderFieldCondition borderFieldCondition_{BorderFieldCondition()};
	HighSpeedModificationVerle highSpeedModificationVerle_{HighSpeedModificationVerle()};
	LeapFrog leapFrog_{LeapFrog()};

	CyclicBorder cyclicBorder{&borders_};
	CyclicBoundedField cyclicBoundedField{&radiusCat_, &borders_};

	LDFieldFunction azotField_{aN, aN, epsN};
	LDInterworking azotInterworking;

	std::vector<CreateField> createField_;
	std::vector<FeelField> feelField_;
};

} /* namespace phycoub */

#endif /* FIGUREDEMONSTRATION_H_ */
