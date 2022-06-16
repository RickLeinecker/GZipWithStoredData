// GZipWithStoredData.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "crc32.h"
#include "structs.h"
#include "BitIO.h"
#include <io.h>
#include <malloc.h>

static char inFile[] = "D:\\work\\Data Compression Dev\\TestData\\VOX.BMP";
static char outFile[] = "D:\\work\\Data Compression Dev\\TestData\\VOX.STORED";

int main(int argc, char* argv[])
{
	GZipHeader header;
	header.magic[0] = 31;
	header.magic[0] = 139;
	header.cm = 8;
	header.flags = 0;
	header.timedate[0] = header.timedate[1] = header.timedate[2] = header.timedate[3] = 0;
	header.xfl = 0;
	header.os = 3;

	FILE *in = fopen(inFile, "rb");
	int fileLength = _filelength(_fileno(in));
	unsigned char *data = (unsigned char *)malloc(fileLength);
	fread(data, sizeof(unsigned char), fileLength, in );
	fclose(in);

	FILE *out = fopen(outFile, "wb");
	fwrite(&header, sizeof(GZipHeader), 1, out);

	CBitIO io(out);

	// Store bits for the last block and the stored type.

	// This represents that this is the last block.
	io.write(1);

	// This represents that this is a "stored" type.
	io.write(0);
	io.write(0);

//	io.write(1); == 1
//	io.write(0);

//	io.write(0); == 2
//	io.write(1);

	// Now we need to save enough bits to get the an even byte boundary.
	io.write(0);
	io.write(0);
	io.write(0);
	io.write(0);
	io.write(0);

	// Write the data length and its complement.
	unsigned short len = (unsigned short)fileLength;
	unsigned short complement = ~len;

	fwrite(&len, sizeof(unsigned short), 1, out);
	fwrite(&complement, sizeof(unsigned short), 1, out);

	fwrite(data, sizeof(unsigned char), fileLength, out);

	unsigned int crc32 = CCRC32::xcrc32(data, fileLength, 0);
	fwrite(&crc32, sizeof(unsigned int), 1, out);
	fwrite(&fileLength, sizeof(unsigned int), 1, out);

	fclose(out);

	return 0;
}

unsigned short swapBytes(unsigned short *data)
{
	unsigned short ret = 0;

	ret = (*data) >> 8;
	ret |= ((*data) << 8);

	return ret;
}