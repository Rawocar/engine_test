#ifndef H_EN_SHADER
#define H_EN_SHADER

///////////////////////////////////////////
///////////////////////////////////////////
// Einbindungen
///////////////////////////////////////////
///////////////////////////////////////////

#include <stdlib.h>
#include <GL/glew.h>
#include <string.h>

#include "en_error.h"
#include "en_app.h"
#include "en_file.h"

///////////////////////////////////////////
///////////////////////////////////////////
// Funktionsdeklaration
///////////////////////////////////////////
///////////////////////////////////////////

/*
	Beschreibung:			Diese Funktion lädt einen Shader und gibt die ID
										zurück.
	1. Parameter:			Dateipfad
	2. Parameter:			Die Art des Shader
	3. Parameter:			Programmvariable
	return:						Shader ID
*/

int load_shader(const char*, GLenum, CApp*);

/*
	Beschreibung:			Diese Funktion entlädt das Shader Programm.
	1. Parameter:     Programmvariable
*/

void unload_shader(CApp*);

#endif
