#include "Tankdrive.h"

Tankdrive::Tankdrive(unsigned int Left1C,unsigned int Left2C, unsigned int Left3C,
		unsigned int Right1C, unsigned int Right2C, unsigned int Right3C)
: Left1(Left1C), Left2(Left2C), Left3(Left3C), Right1(Right1C), Right2(Right2C), Right3(Right3C)
{
	throttle = 0;
}

void Tankdrive::drive(float left, float right)
{
	Left1.Set(left*-1*throttle);
	Left2.Set(left*-1*throttle);
	Left3.Set(left*-1*throttle);
	Right1.Set(right*throttle);
	Right2.Set(right*throttle);
	Right3.Set(right*throttle);
}

void Tankdrive::Throttle(float Ithrottle)
{
	throttle = Ithrottle;
}

void Tankdrive::DirectDrive(float dleft, float dright)
{
	Left1.Set(dleft);
	Left2.Set(dleft);
	Left3.Set(dleft);
	Right1.Set(dright*-1);
	Right2.Set(dright*-1);
	Right3.Set(dright*-1);
}
