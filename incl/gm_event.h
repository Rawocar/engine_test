#ifndef H_GM_EVENT
#define H_GM_EVENT

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

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdio.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "en_glb.h"
#include "en_app.h"
#include "gm_state.h"

///////////////////////////////////////////
///////////////////////////////////////////
// Funktionsprototypen
///////////////////////////////////////////
///////////////////////////////////////////

/*
  Beschreibung:			Diese Funktion behandelt alle Events.
	1. Parameter:			Zeiger auf Spielzustand
	2. Parameter:			poly mode
	3. Parameter:			Programmvariable
*/

void event_handler(Game_State*, unsigned short int*, CApp*);

/*
	Beschreibung:			Diese Funktion behandelt alle keydown events.
	1. Parameter:			Programmvariable
	2. Parameter:			Zeiger auf Spielzustand
	3. Parameter:			poly mode
*/

void event_kd(CApp*, Game_State*, unsigned short int*);

/*
	Beschreibung:			Diese Funktion behandelt ESC_kd events.
	1. Parameter:			Zeiger auf Spielzustand
*/

void esc_kd(Game_State*);

/*
	Beschreibung:			Diese Funktion behandelt P_kd events.
	1. Parameter:			poly mode
*/

void p_kd(unsigned short int*);

/*
	Beschreibung:			Diese Funktion behandelt alle mouse wheel events.
	1. Parameter:			Programmvariable
	2. Parameter:			Zeiger auf Spielzustand
*/

void event_mw(CApp * pApp, Game_State*);

/*
	Beschreibung:			Diese Funktion zoomt die Kamera heran oder heraus.
	1. Parameter:			Programmvariable
	2. Parameter:			Zeiger auf Spielzustand
*/

void zoom_camera(CApp*, Game_State*);

#endif
