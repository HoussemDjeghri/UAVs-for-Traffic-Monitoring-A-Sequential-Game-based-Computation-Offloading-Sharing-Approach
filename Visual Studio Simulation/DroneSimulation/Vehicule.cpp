#include "Vehicule.h"



int Vehicule::getId() { return id; }
long double Vehicule::getEngerie() { return energie; }
long double Vehicule::getFrequenceCpu() { return frequence_cpu; }
bool Vehicule::estElectrique() { return est_electrique; }
void Vehicule::setId(int id) { this->id = id; }
void Vehicule::setEnergie(long double energie) { this->energie = energie; }
void Vehicule::setFrequenceCpu(long double frequence_cpu) { this->frequence_cpu = frequence_cpu; }
void Vehicule::estElectrique(bool est_electrique) { this->est_electrique = est_electrique; }
Vehicule::Vehicule(int id, long double frequence_cpu, bool est_electrique, long double energie) {
	this->id = id;
	this->energie = energie;
	this->frequence_cpu = frequence_cpu;
	this->est_electrique = est_electrique;
}
Vehicule::Vehicule(int id, long double frequence_cpu, bool est_electrique) {
	this->id = id;
	this->frequence_cpu = frequence_cpu;
	this->est_electrique = est_electrique;
}

long double Vehicule::TCalculCPU(long double cycles_tache) {
	return cycles_tache / frequence_cpu;
}

long double Vehicule::ECalculCPU(long double cycles_tache) {
	return cycles_tache * 6;
}
void Vehicule::majEnergie(long double taux) { energie = energie - taux; }