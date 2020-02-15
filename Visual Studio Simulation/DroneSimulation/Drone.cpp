#include "Drone.h"


Drone::Drone(int id, long double energie, long double frequence_cpu) {
	this->id = id;
	this->energie = energie;
	this->frequence_cpu = frequence_cpu;
}
int Drone::getId() { return id; }
long double Drone::getEngerie() { return energie; }
long double Drone::getFrequenceCpu() { return frequence_cpu; }
void Drone::setId(int id) { this->id = id; }
void Drone::setEnergie(long double energie) { this->energie = energie; }
void Drone::setFrequenceCpu(long double frequence_cpu) { this->frequence_cpu = frequence_cpu; }
long double Drone::TCalculCPU(long double cycles_tache) {
	return cycles_tache / frequence_cpu;
}

long double Drone::ECalculCPU(long double cycles_tache) {
	return cycles_tache * 2;
}

void Drone::majEnergie(long double taux) { energie = energie - taux; }