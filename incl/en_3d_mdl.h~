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
// Einbindungen
///////////////////////////////////////////
///////////////////////////////////////////

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <errno.h>
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

///////////////////////////////////////////
///////////////////////////////////////////
// Konstanten
///////////////////////////////////////////
///////////////////////////////////////////

#define NUMBER_VBO		3
#define INDEX_POS			0
#define INDEX_COLOR		1
#define INDEX_UV			2
#define SQUARE_VERT		4
#define CUBE_VERT			36
#define PYRAMID_VERT	12
#define FACES_1				-33
#define FACES_2				-34
#define FACES_3				-35
#define FACES_4				-36
#define MDL_COLOR			-502
#define MDL_TEXTURE		-503

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
		glm::mat4 mdl;												// die Position des Models
		unsigned int id_texture;							// ID der Textur
		Point * pTex_Pos;											// Texture Mapping
		bool texture_set;											// sagt aus, ob eine Textur gesetzt wurde
		GLenum draw_mode;											// sagt aus, wie OpenGL zeichnen soll, standard auf GL_TRIANGLES	
		short int create_flag;								// MDL_COLOR oder MDL_TEXTURE

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
												und Farben festgelegt wurden. Sie löscht auch die Buffer für die Farben und Positionen für alle Vertexes,
												um Speicher zu sparen.
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
			1. Parameter:			Shader Programm ID
		*/

		void draw(int);

		/*
			Beschreibung:			Gibt Position des Models zurück. Skalierung / Rotation
			return:						Position
		*/

		glm::mat4 get_mdl_pos();

		/*
			Beschreibug:			Setzt Model Position.
			1. Parameter:			x-Koordinate
			2. Parameter:			y-Koordinate
			3. Parameter:			z-Koordinate
		*/

		void set_mdl_pos(float, float, float);

		/*
			Beschreibung:			Diese Funktion generiert einen Würfel.
			1. Parameter:			Spannweite in eine Dimension
			2. Parameter:			rot wert (0 - 255)
			3. Parameter:			grün wert (0 - 255)
			4. Parameter:			blau wert (0 - 255)
			5. Parameter:			alpha wert (0 - 255)
			6. Parameter:			flag, das aussagt, ob das Model eine Textur oder eine Farbe haben wird
		*/

		void create_cube(float, uint8_t, uint8_t, uint8_t, uint8_t, short int);

		/*
			Beschreibung:			Diese Funktion rotiert ein Model.
			1. Parameter:			Rotationsgeschwindigkeit
			2. Parameter:			Rotationsachsen
		*/

		void rotate(float, glm::vec3);

		/*
			Beschreibung:			Diese Funktion legt eine Textur auf einen Würfel. Diese Funktion kann nach create_cube aufgerufen werden.
			1. Parameter:			Texturpfad
			return:						en_err
		*/

		int set_texture_cube(const char*);

		/*
			Beschreibung:			Diese Funktion erzeugt ein 2D Quadrat.
			1. Parameter:			Spannweite in eine Dimension.
			2. Parameter:			rot wert (0 - 255)
			3. Parameter:			grün wert (0 - 255)
			4. Parameter:			blau wert (0 - 255)
			5. Parameter:			flag, das aussagt, ob das Model eine Textur oder eine Farbe haben wird
		*/

		void create_square(float, uint8_t, uint8_t, uint8_t, short int);

		/*
			Beschreibung:			Diese Funktion legt eine Textur auf ein Quadrat. Diese Funktion kann nach create_square aufgerufen werden.
			1. Parameter:			Texturpfad
			return:						en_err
		*/

		int set_texture_square(const char*);

		/*
			Beschreibung:			Diese Funktion lädt ein Model aus einer .obj Datei.
			1. Parameter:			Pfad der Datei
			return:						en_err
		*/

		int load_mdl_from_obj(const char*);

		/*
			Beschreibung:			Gibt die Anzahl an Vertexes zurück.
			return:						Anzahl an Vertexes
		*/

		unsigned int get_num_vertexes();

		/*
			Beschreibung:			Diese Funktion erstellt eine Kreisfläche.
			1. Parameter:			Radius
			2. Parameter:			Anzahl an Kreispunkten für Genauigkeit
			3. Parameter:			rot wert
			4. Parameter:			grün wert
			5. Parameter:			blau wert
		*/

		void create_circle(float, float, uint8_t, uint8_t, uint8_t);

		/*
			Beschreibung:			Diese Funktion erstellt eine Kugel.
			1. Parameter:			Größter Radius
			2. Parameter:			Anzahl an Kreispunkten pro Schale. Muss eine gerade Zahl sein, die durch 2 geteilt ebenfalls gerade ist!
			3. Parameter:			rot wert
			4. Parameter:			grün wert
			5. Parameter:			blau wert
			6. Parameter:			flag, das aussagt, ob das Model eine Textur oder eine Farbe haben wird
		*/

		void create_sphere(float, float, uint8_t, uint8_t, uint8_t, short int);

		/*
			Beschreibung:			Diese Funktion erstellt eine Pyramide.
			1. Parameter:			Spannweit in eine Dimension für den Boden
			2. Parameter:			Abstand Boden zur Spitze
			3. Parameter:			rot wert
			4. Parameter:			grün wert
			5. Parameter:			blau wert
			6. Parameter:			flag, das aussagt, ob das Model eine Textur oder eine Farbe haben wird
		*/

		void create_pyramid(float, float, uint8_t, uint8_t, uint8_t, short int);

		/*
			Beschreibung:			Diese Funktion erstellt einen Kegel.
			1. Parameter:			radius
			2. Parameter:			Abstand Boden zur Spitze
			3. Parameter:			Anzahl an Kreispunkten für Genauigkeit
			4. Parameter:			rot wert
			5. Parameter:			grün wert
			6. Parameter:			blau wert
			7. Parameter:			flag, das aussagt, ob das Model eine Textur oder eine Farbe haben wird
		*/

		void create_cone(float, float, float, uint8_t, uint8_t, uint8_t, short int);
};

#endif
