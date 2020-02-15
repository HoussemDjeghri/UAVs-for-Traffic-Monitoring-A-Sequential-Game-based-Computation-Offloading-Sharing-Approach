#include "Tache.h"



int Tache::getId() { return id; }
long double Tache::getCi() { return ci; }
long double Tache::getDi() { return di; }
long double Tache::getRsi() { return rsi; }
int Tache::getSi() { return si; }
void Tache::setCi(long double ci) { this->ci = ci; }
void Tache::setDi(long double di) { this->di = di; }
void Tache::setRsi(long double rsi) { this->rsi = rsi; }
void Tache::setSi(int si) { this->si = si; }
void Tache::setId(int id) { this->id = id; }
Tache::Tache(int id, long double ci, long double di, long double rsi, int si) {
	this->id = id;
	this->ci = ci;
	this->di = di;
	this->rsi = rsi;
	this->si = si;
}