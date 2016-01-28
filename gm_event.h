#ifndef H_GM_EVENT
#define H_GM_EVENT

///////////////////////////////////////////
///////////////////////////////////////////
// Einbindungen
///////////////////////////////////////////
///////////////////////////////////////////

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "en_glb.h"
#include "gm_state.h"

///////////////////////////////////////////
///////////////////////////////////////////
// Funktionsprototypen
///////////////////////////////////////////
///////////////////////////////////////////

/*
  Beschreibung:			Diese Funktion behandelt alle Events.
	1. Parameter:			SDL_Event
	2. Parameter:			Zeiger auf Spielzustand
	3. Parameter:			poly mode
*/

void event_handler(SDL_Event, Game_State*, unsigned short int*);

/*
	Beschreibung:			Diese Funktion behandelt alle keydown events.
	1. Parameter:			SDL_Event
	2. Parameter:			Zeiger auf Spielzustand
	3. Parameter:			poly mode
*/

void event_kd(SDL_Event, Game_State*, unsigned short int*);

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

#endif
