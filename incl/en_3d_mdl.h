#ifndef H_EN_3D_MDL
#define H_EN_3D_MDL

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

#define NUMBER_VBO		4
#define INDEX_POS			0
#define INDEX_UV			1
#define INDEX_NORMAL  2
#define SQUARE_VERT		6
#define CUBE_VERT			36
#define PYRAMID_VERT	18

// obj File

#define FACES_1				-33
#define FACES_2				-34
#define FACES_3				-35
#define FACES_4				-36

// Materials

#define MAT_EMERALD						-3001
#define MAT_JADE							-3002
#define MAT_OBSIDIAN					-3003
#define MAT_PEARL							-3004
#define MAT_RUBY							-3005
#define MAT_TURQUOISE   			-3006
#define MAT_BRASS							-3007
#define MAT_BRONZE						-3008
#define MAT_CHROME						-3009
#define MAT_COPPER						-3010
#define MAT_GOLD							-3011
#define MAT_SILVER						-3012
#define MAT_BLACK_PLASTIC 		-3013
#define MAT_CYAN_PLASTIC			-3014
#define MAT_GREEN_PLASTIC			-3015
#define MAT_RED_PLASTIC				-3016
#define MAT_WHITE_PLASTIC			-3017
#define MAT_YELLOW_PLASTIC		-3018
#define MAT_BLACK_RUBBER			-3019
#define MAT_CYAN_RUBBER				-3020
#define MAT_GREEN_RUBBER			-3021
#define MAT_RED_RUBBER				-3022
#define MAT_BLUE_RUBBER				-3023
#define MAT_WHITE_RUBBER			-3024
#define MAT_YELLOW_RUBBER			-3025
#define MAT_STEEL							-3026

// Texturarten

#define TEXTURE_DIFFUSE				-202
#define TEXTURE_SPECULAR			-203

///////////////////////////////////////////
///////////////////////////////////////////
// Einbindungen
///////////////////////////////////////////
///////////////////////////////////////////

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "SOIL/SOIL.h"
#include <math.h>

#include "en_error.h"
#include "en_math.h"
#include "en_string.h"
#include "en_file.h"
#include "en_glb.h"

///////////////////////////////////////////
///////////////////////////////////////////
// Klassendeklaration
///////////////////////////////////////////
///////////////////////////////////////////

class CModel_3D
{
  private:

		glm::vec3 * pPos_Vertex;							// die Positionen von jedem einzelnen Vertex
		unsigned int current_pos_ver;					// das ist der aktuelle Vertex, der von der Position her initialisiert wird
    unsigned int number_vertexes;					// Anzahl an Vertexes
		unsigned int * pVBO;									// hier werden die ID's der VBO gespeichert, 0 = Positionen, 1 = Farben, 2 = Texturkoordinaten, 3 = Normalvektoren
		unsigned int id_vao;									// die ID des VAO
		glm::mat4 mdl;												// die Position des Models
		unsigned int id_diff_texture;					// ID der Diffuse Textur
		unsigned int id_spec_texture;					// ID der Specular Textur
		glm::vec2 * pTex_Pos;									// Texture Mapping
		glm::vec3 * pNorm_Vec;								// Zeiger auf Normalvektor
		bool diff_texture_set;								// sagt aus, ob eine Diffuse Textur gesetzt wurde
		bool spec_texture_set;								// sagt aus, ob eine Specular Textur gesetzt wurde
		GLenum draw_mode;											// sagt aus, wie OpenGL zeichnen soll, standard auf GL_TRIANGLES	
		unsigned int current_norm_vec;				// aktueller Normalvektor
		int material_flag;										// legt das Meterial fest
		bool uv_set;													// sagt aus, ob Texturkoordinaten bereits existieren
		float shine_intensity;								// gibt die Reflektionsintensität eines Models an
		unsigned int current_uv;							// aktuelle Texturkoordinate

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion sendet das Material an die GPU.
			1. Parameter:			Shader Programm ID
			return:						err_en
		*/

		int send_material(int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion legt die Anzahl für Vertexes für das Model fest und initialisiert
												den Speicher. ACHTUNG: Das ist nur sinnvoll, wenn das Model NICHT aus einer Datei geladen wird.
			1. Parameter:			Anzahl an Vertexes
		*/

		void init_vertexes(unsigned int);	

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion fügt dem aktuellen Vertex eine Position hinzu.
			1. Parameter:			x-Koordinate
			2. Parameter:			y-Koordinate
			3. Parameter:			z-Koordinate
		*/	

		void add_vertex_pos(float, float, float);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion fügt dem aktuellen Vertex einen Normalvektor hinzu.
			1. Parameter:			x-Richtung
			2. Parameter:			y-Richtung
			3. Parameter:			z-Richtung
		*/

		void add_normal_vec(float, float, float);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion fügt dem aktuellen Vertex eine UV Koordinate hinzu.
			1. Parameter:			x-Koordinate
			2. Parameter:			y-Koordinate
		*/

		void add_uv(float, float);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion erstellt das Model für OpenGL. Diese Funktion wird aufgerufen, nachdem die Positionen
												und Farben festgelegt wurden. Sie löscht auch die Buffer für die Farben und Positionen für alle Vertexes,
												um Speicher zu sparen.
			return:						en_err
		*/

		int create_model();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion erstellt eine Textur und sendet sie an die GPU. UV Koordinaten müssen schon vorhanden sein!
			1. Parameter:			Dateipfad
			2. Parameter:			Shader Program ID
			3. Parameter:			Art der Textur
			4. Parameter:			Kanäle, die gezeichnet werden sollen
			return:						err_en
		*/

		int set_texture(const char*, int, int, int);

	///////////////////////////////////////////
	// public
	///////////////////////////////////////////

	public:

		CModel_3D();
		~CModel_3D();	

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung: 		Diese Funktion malt das Model.
			1. Parameter:			Shader Programm ID
			return:						err_en
		*/

		int draw(int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Gibt Position des Models zurück. Skalierung / Rotation
			return:						Position
		*/

		glm::mat4 get_mdl_pos();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibug:			Setzt Model Position.
			1. Parameter:			x-Koordinate
			2. Parameter:			y-Koordinate
			3. Parameter:			z-Koordinate
		*/

		void set_mdl_pos(float, float, float);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion generiert einen Würfel.
			1. Parameter:			Spannweite in eine Dimension
			return:						err_en
		*/

		int create_cube(float);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion rotiert ein Model.
			1. Parameter:			Rotationsgeschwindigkeit
			2. Parameter:			Rotationsachsen
		*/

		void rotate(float, glm::vec3);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion legt eine Textur auf einen Würfel. Diese Funktion kann nach create_cube aufgerufen werden.
			1. Parameter:			Texturpfad
			2. Parameter:			Faktor, wie oft die Textur wiederholt werden soll
			3. Parameter:			Shader Programm ID
			4. Parameter:			welche Art von Textur soll erzeugt werden?
			5. Parameter:			Kanäle, die gezeichnet werden sollen
			return:						en_err
		*/

		int set_texture_cube(const char*, float, int, int, int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion erzeugt ein 2D Quadrat.
			1. Parameter:			Spannweite in eine Dimension
			return:						err_en
		*/

		int create_square(float);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion legt eine Textur auf ein Quadrat. Diese Funktion kann nach create_square aufgerufen werden.
			1. Parameter:			Texturpfad
			2. Parameter:			Faktor, wie oft Textur wiederholt werden soll
			3. Parameter:			Welche Art von Textur
			4. Parameter:			Shader Programm ID
			5. Parameter:			Kanäle, die gemalt werden sollen
			return:						en_err
		*/

		int set_texture_square(const char*, float, int, int, int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion lädt ein Model aus einer .obj Datei.
			1. Parameter:			Pfad der Datei
			2. Parameter:			Shader Programm ID
			return:						en_err
		*/

		int load_mdl_from_obj(const char*, int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Gibt die Anzahl an Vertexes zurück.
			return:						Anzahl an Vertexes
		*/

		unsigned int get_num_vertexes();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion legt das Meterial fest.
			1. Parameter:			Material flag
		*/

		void set_material(int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion bereinigt den Arbeitsspeicher, nachdem das
												Model erstellt wurde.
		*/

		void finish_creation();
};

#endif
