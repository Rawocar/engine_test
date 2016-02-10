#ifndef H_GM_RUN
#define H_GM_RUN

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
#include <errno.h>
#include <SDL2/SDL.h>

#include "gm_error.h"
#include "en_app.h"
#include "gm_glb.h"
#include "gm_init.h"
#include "gm_draw.h"
#include "gm_update.h"
#include "gm_state.h"

///////////////////////////////////////////
///////////////////////////////////////////
// Funktionsprototypen
///////////////////////////////////////////
///////////////////////////////////////////

/*
  Beschreibung:			Diese Funktion bildet die Programmschleife im Releasemodus.
  return:						gm_err
*/

int run();

#endif
