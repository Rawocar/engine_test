#ifndef H_GM_DRAW
#define H_GM_DRAW

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
#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "gm_error.h"
#include "en_app.h"
#include "gm_state.h"

///////////////////////////////////////////
///////////////////////////////////////////
// Funktionsprototypen
///////////////////////////////////////////
///////////////////////////////////////////

/*
	Beschreibung:			Diese Funktion malt das aktuelle Bild.
	1. Parameter:			Zeiger auf Programmvariable
	return:						gm_err
*/

int gm_draw(CApp*, Game_State*);

#endif
