#pragma once

typedef struct _nmsetting
{
	int hw;
	int type;
	int seed;
}Setting;

void startnemo(Setting *setting);
void nemomain();
void nmsetting(Setting *setting);
void submitnemo(bool** submit, bool** arr, int height, int width);
void gethint(bool** arr, int*** hint, int height, int width);
void ReadNFile(bool** arr, int height, int width);
void SaveNFile(bool** arr, int height, int width);