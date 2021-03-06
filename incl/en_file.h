#ifndef H_EN_FILE
#define H_EN_FILE

/*
	Author: 	Patrick-Christopher Mattulat
	City:			Berlin
	License:	See License File!
	Contact: 	drumstar@hotmail.de
*/

///////////////////////////////////////////
///////////////////////////////////////////
// Einbindungen
///////////////////////////////////////////
///////////////////////////////////////////

#include <stdlib.h>
#include <cstdio>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "en_glb.h"
#include "en_error.h"

///////////////////////////////////////////
///////////////////////////////////////////
// Strukturen
///////////////////////////////////////////
///////////////////////////////////////////

typedef struct EN_bmp
{
	short int bfType;
	int bfSize;
	int bfReserved;
	int bfOffBits;
	int biSize;
	int biWidth;
	int biHeight;
	short int biPlanes;
	short int biBitCount;
	int biCompression;
	int biSizeImage;
	int biXPelsPerMeter;
	int biYPelsPerMeter;
	int biClrUsed;
	int biClrImportant;
	unsigned char * pData;
	int num_bytes;
} BMP;

///////////////////////////////////////////
///////////////////////////////////////////
// Funktionsprototypen
///////////////////////////////////////////
///////////////////////////////////////////

/*
	Beschreibung:			Diese Funktion liest den Inhalt einer Datei und gibt ihn
										zurück.
	1. Parameter:			Dateipfad
	2. Parameter:			Buffer zum beschreiben, muss bereits richtige Größe haben
	3. Parameter:			Länge des Inhaltes der Datei (mit Nullterminierung)
	return:						en_err
*/

int read_file(const char*, char*, unsigned int);

/*
	Beschreibung:			Diese Funktion gibt die Länge des Inhaltes einer Datei zurück.
	1. Parameter:			Pfad zur Datei
	return:						Länge des Inhaltes
*/

int len_file(const char*);

/*
	Beschreibung:			Diese Funktion lädt eine bitmap Datei und übergibt sie an einen
										Buffer.
	1. Parameter:			Dateipfad
	return:						Bilddaten
*/

BMP * load_bmp(const char*);

#endif
