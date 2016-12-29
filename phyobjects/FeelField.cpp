/*
 * FeelField.cpp
 *
 *  Created on: 17 ���. 2016 �.
 *      Author: SFrancishkov
 */

#include <FeelField.h>
#include <algorithm>
#include <thread>
#include <functional>

#include "../calculationmodels/CalculationModel.h"

namespace phycoub {

FeelField::FeelField(CreateField* createField ,InterworkingFunction* interworkingFunction, std::string fieldName): createField_(createField), particles_(0), interworkingFunction_(interworkingFunction), fieldName_(fieldName) {}
FeelField::~FeelField() {}

void phyCalcInterworkingThread(FeelField* feelField, int start, int end);

void FeelField::phyCalcInterworking() {
	int numCPU =  std::thread::hardware_concurrency() - 2;
	if(numCPU < 2 || (int)particles_.size() < numCPU * 100) {
		for(Particle* particle : particles_) {
			particle->resultant_ += interworkingFunction_->psyForce(createField_->getFieldInMark(particle->coordinate_), particle);
		}
	}
	else {
		int sizeBlockOfThread = particles_.size() / numCPU;
		std::thread* threads[numCPU];

		int start = 0, stop = start + sizeBlockOfThread;
		for(int i = 0; i < numCPU - 1; ++i) {
			threads[i] = new std::thread(phyCalcInterworkingThread, this, start, stop);
			start = stop;
			stop = start + i * sizeBlockOfThread;
		}
		threads[numCPU - 1] = new std::thread(phyCalcInterworkingThread, this, start, particles_.size());

		for(int i = 0; i < numCPU; ++i) {
			if(threads[i]->joinable()) {
				threads[i]->join();
			}
		}
		for(int i = 0; i < numCPU; ++i) {
			delete threads[i];

		}
	}
}

void FeelField::addParticle(Particle* particle) {
	particles_.push_back(particle);
}
void FeelField::addGroupParticle(std::vector<Particle*> &particles) {
	for_each(particles.begin(), particles.end(), [&](Particle* particle){
		particles_.push_back(particle);
	});
}
void FeelField::removeParticle(Particle* particle) {
	std::vector<Particle *>::iterator itr = particles_.begin();
	while(itr != particles_.end()) {
		if((*itr)->index == particle->index) {
			particles_.erase(itr);
			break;
		}
		++itr;
	}
}

// Функция потока, для распаралеливания процесса моделировани/
void phyCalcInterworkingThread(FeelField* feelField, int start, int end) {
	for(int i = start; i < end; ++i) {
		feelField->particles_[i]->resultant_ += feelField->interworkingFunction_->psyForce(feelField->createField_->getFieldInMark(feelField->particles_[i]->coordinate_), feelField->particles_[i]);
	}
}
//

} /* namespace phycoub */
