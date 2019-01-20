#include "Pneumatics.h"

Pneumatics::Pneumatics(unsigned int compport, unsigned int gearport)
: compressor(compport), gear(gearport)
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
