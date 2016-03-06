#ifndef H_EN_STRING
#define H_EN_STRING

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
#include <stdio.h>
#include <string.h>

///////////////////////////////////////////
///////////////////////////////////////////
// Funktionsprototypen
///////////////////////////////////////////
///////////////////////////////////////////

/*
	Beschreibung:			Diese Funktion zählt wie oft ein Zeichen in einem
										String vorkommt.
	1. Parameter:			String
	2. Parameter:			Zeichen
	return:						Anzahl an Erscheinungen
*/

unsigned int count_in_str(const char*, char);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

/*
	Beschreibung:			Diese Funktion findet heraus wo ein Zeichen das erste Mal
										in einem String auftaucht.
	1. Parameter:			String
	2. Parameter:			Zeichen
	return:						index des 1. Mal
*/

unsigned int first_appear(const char*, char);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

/*
	Beschreibung:			Diese Funktion prüft, ob ein String in einem anderen String vorkommt.
	1. Parameter:			Quelle
	2. Parameter:			String
	return:						boolean
*/

bool is_str_in_str(const char*, const char*);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

/*
	Beschreibung:			Diese Funktion gibt den Index zurück, an dem das gesuchte Zeichen zuletzt
										im Quellstring auftaucht.
	1. Parameter:			Quelle
	2. Parameter:			gesuchtes Zeichen
	return:						letzte Position
*/

unsigned int last_position_of_char(const char*, char);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

/*
	Beschreibung:			Diese Funktion kopiert eine Quelle in einen Buffer nur bis zu einem bestimmten
										Offset.
	1. Parameter:			Quelle
	2. Parameter:			Buffer
	3. Parameter:			Offset
*/

void copy_str_offset(const char*, char*, unsigned int);

#endif
