#ifndef H_EN_FILE
#define H_EN_FILE

///////////////////////////////////////////
///////////////////////////////////////////
// Einbindungen
///////////////////////////////////////////
///////////////////////////////////////////

#include <stdlib.h>
#include <cstdio>
#include <string.h>
#include <errno.h>

#include "en_glb.h"
#include "en_error.h"

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

#endif
