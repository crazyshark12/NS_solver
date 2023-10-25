#pragma once
#ifndef _MACROPARS_
#define _MACROPARS_

class Macropars
{
	double dens;
	double pres;
	double velc;
	double temp;
public:
	Macropars() {};
	Macropars(double dens, double pres, double velc, double temp);
	~Macropars() {};
	void setdens(double dens);
	void setpres(double pres);
	void setvelc(double velc);
	void settemp(double temp);
	double getdens();
	double getpres();
	double getvelc();
	double gettemp();
};

#endif