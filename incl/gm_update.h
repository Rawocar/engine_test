#ifndef H_GM_UPDATE
#define H_GM_UPDATE

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
#include <errno.h>

#include "gm_error.h"
#include "gm_event.h"
#include "gm_state.h"
#include "en_app.h"
#include "en_shader.h"

///////////////////////////////////////////
///////////////////////////////////////////
// Funktionsprototypen
///////////////////////////////////////////
///////////////////////////////////////////

/*
	Beschreibung:			Diese Funktion berechnet die einzelnen Spielabschnitte.
	1. Parameter:			Zeiger auf Programmvariable
	2. Parameter:			Zeiger auf Spielzustand
	3. Parameter:			poly_mode
	return:						gm_err / en_err
*/

int gm_update(CApp*, Game_State*, unsigned short int*);

#endif
