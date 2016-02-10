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

/*
	Beschreibung:			Diese Funktion findet heraus wo ein Zeichen das erste Mal
										in einem String auftaucht.
	1. Parameter:			String
	2. Parameter:			Zeichen
	return:						index des 1. Mal
*/

unsigned int first_appear(const char*, char);

#endif
