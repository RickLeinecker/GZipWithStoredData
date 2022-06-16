#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#pragma pack(1)
struct GZipHeader
{
	unsigned char magic[2];
	unsigned char cm;
	unsigned char flags;
	unsigned char timedate[4];
	unsigned char xfl;
	unsigned char os;
};
#pragma pack()

#endif
