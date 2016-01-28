#ifndef H_GM_INIT
#define H_GM_INIT

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

///////////////////////////////////////////
///////////////////////////////////////////
// Funktionsprototypen
///////////////////////////////////////////
///////////////////////////////////////////

/*
  Beschreibung:			Diese Funktion erstellt das Fenster und
										initialisiert OpenGL.
  1. Parameter:			Zeiger auf Programmvariable
	return:						gm_err / en_err
*/

int init(CApp*);

/*
	Beschreibung:			Diese Funktion erstellt das Shader Programm.
  1. Parameter:			Zeiger auf Programmvariable
  return:						gm_err / en_err
*/

int init_shader(CApp*);

/*
	Beschreibung:			Diese Funktion initialisiert alle Models fürs Hauptmenü.
	return:						gm_err / en_err
*/

int init_models_menu(CModel_3D**);

#endif
