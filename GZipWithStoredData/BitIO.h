#pragma once
class CBitIO
{
public:
	CBitIO(FILE *fp);
	~CBitIO();

	void flush(void);
	void write(unsigned char bit);

private:
	unsigned char accumulator, currentBit;
	FILE *_fp;

};

