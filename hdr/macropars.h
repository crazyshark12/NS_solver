#pragma once
#ifndef _MACROPARS_
#define _MACROPARS_

struct Macropars
{
	double dens;
	double pres;
	double velX, velY;
	double temp;

	Macropars() {};
	Macropars(double dens_, double pres_, double velX_, double velY_, double temp_) :
		dens(dens_), pres(pres_), velX(velX_), velY(velY_), temp(temp_) {};
};

#endif