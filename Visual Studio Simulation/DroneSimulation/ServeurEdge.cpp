#include "ServeurEdge.h"



int ServeurEdge::getId() { return id; }
long double ServeurEdge::getFrequenceCpu() { return frequence_cpu; }
void ServeurEdge::setId(int id) { this->id = id; }
void ServeurEdge::setFrequenceCpu(long double frequence_cpu) { this->frequence_cpu = frequence_cpu; }
ServeurEdge::ServeurEdge(int id, long double frequence_cpu) {
	this->id = id;
	this->frequence_cpu = frequence_cpu;
}
long double ServeurEdge::TCalculCPU(long double cycles_tache) {
   return cycles_tache / frequence_cpu;
}