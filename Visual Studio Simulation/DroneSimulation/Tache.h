#pragma once
class Tache
{
private:
	int id;
	long double ci;
	long double di;
	long double rsi;
	int si;
public:
	Tache();
	int getId();
	long double getCi();
	long double getDi();
	long double getRsi();
	int getSi();
	void setCi(long double ci);
	void setDi(long double di);
	void setRsi(long double rsi);
	void setSi(int si);
	void setId(int id);
	Tache(int id, long double ci, long double di, long double rsi, int si);
};

