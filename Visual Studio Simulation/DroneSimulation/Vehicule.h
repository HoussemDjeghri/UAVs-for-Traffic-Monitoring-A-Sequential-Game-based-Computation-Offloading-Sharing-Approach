#pragma once
class Vehicule
{
private:
	int id;
	bool est_electrique;
	long double energie;
	long double frequence_cpu;

public:
	int getId();
	long double getEngerie();
	long double getFrequenceCpu();
	bool estElectrique();
	void setId(int id);
	void setEnergie(long double energie);
	void setFrequenceCpu(long double frequence_cpu);
	void estElectrique(bool est_electrique);
	Vehicule(int id, long double frequence_cpu, bool est_electrique, long double energie);
	Vehicule(int id, long double frequence_cpu, bool est_electrique);
	long double TCalculCPU(long double cycles_tache);
	long double ECalculCPU(long double cycles_tache);
	void majEnergie(long double taux);
};

