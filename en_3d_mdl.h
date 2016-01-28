#ifndef H_EN_3D_MDL
#define H_EN_3D_MDL

///////////////////////////////////////////
///////////////////////////////////////////
// Einbindungen
///////////////////////////////////////////
///////////////////////////////////////////

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <errno.h>
#include <stdio.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "en_error.h"
#include "en_math.h"

///////////////////////////////////////////
///////////////////////////////////////////
// Konstanten
///////////////////////////////////////////
///////////////////////////////////////////

#define NUMBER_VBO		2
#define INDEX_POS			0
#define INDEX_COLOR		1

///////////////////////////////////////////
///////////////////////////////////////////
// Klassendeklaration
///////////////////////////////////////////
///////////////////////////////////////////

class CModel_3D
{
  private:

		VEC3 * pPos_Vertex;										// die Positionen von jedem einzelnen Vertex
		unsigned int current_pos_ver;					// das ist der aktuelle Vertex, der von der Position her initialisiert wird
    unsigned int number_vertexes;					// Anzahl an Vertexes
		unsigned int * pVBO;									// hier werden die ID's der VBO gespeichert, 0 = Positionen, 1 = Farben
		unsigned int id_vao;									// die ID des VAO
		VEC4 * pCol_Vertex;										// die Farbe für jeden einzelnen Vertex
		unsigned int current_col_ver;					// aktueller Vertex, der von den Farben her initialisiert wird
		glm::mat4 mdl_beh;										// die Position des Models

	public:

		CModel_3D();
		~CModel_3D();

		/*
			Beschreibung:			Diese Funktion legt die Anzahl für Vertexes für das Model fest und initialisiert
												den Speicher. ACHTUNG: Das ist nur sinnvoll, wenn das Model NICHT aus einer Datei geladen wird.
			1. Parameter:			Anzahl an Vertexes
		*/

		void init_vertexes(unsigned int);		

		/*
			Beschreibung:			Diese Funktion fügt dem aktuellen Vertex eine Position hinzu.
			1. Parameter:			x-Koordinate
			2. Parameter:			y-Koordinate
			3. Parameter:			z-Koordinate
		*/	

		void add_vertex_pos(float, float, float);

		/*
			Beschreibung:			Diese Funktion erstellt das Model für OpenGL. Diese Funktion wird aufgerufen, nachdem die Positionen
												und Farben festgelegt wurden.
			return:						en_err
		*/

		int create_model();

		/*
			Beschreibung:			Diese Funktion fügt dem aktuellen Vertex eine Farbe hinzu.
			1. Parameter:			rot
			2. Parameter:			grün
			3. Parameter:			blau
			4. Parameter:			alpha
		*/

		void add_vertex_col(float, float, float, float);

		/*
			Beschreibung: 		Diese Funktion malt das Model.
		*/

		void draw();

		/*
			Beschreibung:			Gibt Verhalten des Models zurück. Skalierung / Rotation
			return:						Position
		*/

		glm::mat4 get_mdl_beh();

		/*
			Beschreibug:			Setzt Model verhalten.
			1. Parameter:			x-Koordinate
			2. Parameter:			y-Koordinate
			3. Parameter:			z-Koordinate
		*/

		void set_mdl_beh(float, float, float);
};

#endif
