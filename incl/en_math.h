#ifndef H_EN_MATH
#define H_EN_MATH

/*
	Author: 	Patrick-Christopher Mattulat
	City:			Berlin
	License:	See License File!
	Contact: 	drumstar@hotmail.de
*/

///////////////////////////////////////////
///////////////////////////////////////////
// Konstanten
///////////////////////////////////////////
///////////////////////////////////////////

#define PI 			3.14159265f

///////////////////////////////////////////
///////////////////////////////////////////
// Strukturen
///////////////////////////////////////////
///////////////////////////////////////////

typedef struct En_Point
{
  float x;
	float y;
} Point;

typedef struct En_Math_fVec3
{
  float x;
  float y;
  float z;
} VEC3;

typedef struct En_Math_fVec4
{
	float r;
	float g;
	float b;
	float a;
} VEC4;

///////////////////////////////////////////
///////////////////////////////////////////
// Funktionsprototypen
///////////////////////////////////////////
///////////////////////////////////////////

/*
	Beschreibung:			Diese Funktion prüft wie oft eine Zahl in eine andere 
										Zahl reinpasst, wenn man sie reinzwingen würde.
	1. Parameter:			die Zahl in die reingestopft werden soll
	2. Parameter:			die Zahl die reingestopft werden soll
	return:					  wie oft die Zahl dann reinpasst
*/

int forced_into(int, int);

#endif
