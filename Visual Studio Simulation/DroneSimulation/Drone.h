#pragma once
class Drone
{
private:
	int id;
	long double energie;
	long double frequence_cpu;

public:
	int getId();
	long double getEngerie();
	long double getFrequenceCpu();
	void setId(int id);
	void setEnergie(long double energie);
	void setFrequenceCpu(long double frequence_cpu);
	Drone(int id, long double energie, long double frequence_cpu);
	long double TCalculCPU(long double cycles_tache);
	long double ECalculCPU(long double cycles_tache);
	void majEnergie(long double taux);
};

