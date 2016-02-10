#ifndef H_GM_INIT
#define H_GM_INIT

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
#include "en_app.h"
#include "en_shader.h"
#include "en_3d_mdl.h"
#include "en_file.h"

///////////////////////////////////////////
///////////////////////////////////////////
// Funktionsprototypen
///////////////////////////////////////////
///////////////////////////////////////////

/*
	Beschreibung:			Diese Funktion initialisiert alle Models fürs Hauptmenü.
	1. Parameter:			Modelzeiger
	return:						gm_err / en_err
*/

int init_models_menu(CApp*);

#endif
