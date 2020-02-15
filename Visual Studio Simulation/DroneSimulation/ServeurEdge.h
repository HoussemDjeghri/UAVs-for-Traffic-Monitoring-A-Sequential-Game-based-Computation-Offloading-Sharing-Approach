#pragma once
class ServeurEdge
{
private:
	int id;
	long double frequence_cpu;

public:
	ServeurEdge(int id, long double frequence_cpu);
	int getId();
	long double getFrequenceCpu();
	void setId(int id);
	void setFrequenceCpu(long double frequence_cpu);
	long double TCalculCPU(long double cycles_tache);
};

