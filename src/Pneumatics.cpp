#include "Pneumatics.h"

Pneumatics::Pneumatics(unsigned int compport, unsigned int gearport, unsigned int gearplaceport)
: compressor(compport), gear(gearport), gearplace(gearplaceport)
{

}

void Pneumatics::compstart()
{
	compressor.Start();
}

void Pneumatics::compstop()
{
	compressor.Stop();
}

void Pneumatics::gearchange(bool gearshift)
{
	gear.Set(gearshift);
}
void Pneumatics::gearplacer(bool placevalue)
{
	gearplace.Set(placevalue);
}
