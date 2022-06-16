#include "stdafx.h"
#include "BitIO.h"

CBitIO::CBitIO(FILE *fp)
{
	accumulator = 0;
	currentBit = 1;
	_fp = fp;
}

CBitIO::~CBitIO()
{
}

void CBitIO::write(unsigned char bit)
{
	if (bit)
	{
		accumulator |= currentBit;
	}
	currentBit <<= 1;
	if (currentBit == 0)
	{
		fwrite(&accumulator, sizeof(unsigned char), 1, _fp);
		accumulator = 0;
		currentBit = 1;
	}
}

void CBitIO::flush(void)
{
	while (currentBit != 1)
	{
		write(0);
	}
}

