#ifndef H_EN_LIGHT
#define H_EN_LIGHT

///////////////////////////////////////////
///////////////////////////////////////////
// Einbindungen
///////////////////////////////////////////
///////////////////////////////////////////

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdlib.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "en_math.h"
#include "en_error.h"

///////////////////////////////////////////
///////////////////////////////////////////
// Konstanten
///////////////////////////////////////////
///////////////////////////////////////////

#define LNUMBER_VBO					2
#define LINDEX_POS					0
#define LINDEX_COLOR				1
#define LIGHT_VISIBLE				13
#define LIGHT_INVISIBLE			14
#define LIGHT_NO_GEOMETRY		15
#define LIGHT_CUBE					-1
#define LCUBE_VERT					36

///////////////////////////////////////////
///////////////////////////////////////////
// Strukturen
///////////////////////////////////////////
///////////////////////////////////////////

typedef struct En_Light
{
	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	int light_kind;					// 1 Directional Light, 2 Pointing Light, 3 Spotlight
	int light_switcher;			// 0 aus, 1 an
	float constant;
	float linear;
	float quadratic;
} Light;

///////////////////////////////////////////
///////////////////////////////////////////
// Klassendeklaration
///////////////////////////////////////////
///////////////////////////////////////////

class CLight
{
	private:

		glm::vec3 * pPos_Vertex;							// die Positionen von jedem einzelnen Vertex
		glm::vec4 * pCol_Vertex;							// die Farbe für jeden einzelnen Vertex
		glm::vec4 lcolor;											// Farbe des geometrischen Körpers!
		Light light;													// Eigentschaften des Lichtes
		unsigned short int vflag;							// Flag, ob die Lampe sichtbar ist, oder nicht
		GLenum draw_mode;											// sagt aus, wie OpenGL zeichnen soll, standard auf GL_TRIANGLES	
		unsigned int current_pos_ver;					// das ist der aktuelle Vertex, der von der Position her initialisiert wird
		glm::mat4 mlight;											// die Position des Lichtes / deswegen nicht in der Struktur En_Light vorhanden
		unsigned int number_vertexes;					// Anzahl an Vertexes
		unsigned int id_vao;									// die ID des VAO
		unsigned int * pVBO;									// hier werden die ID's der VBO gespeichert, 0 = Positionen, 1 = Farben

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion erstellt einen Lichtwürfel.
			1. Parameter:			Die Spannweite in eine Dimension
		*/

		int create_cube(float);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion fügt einen Vertex hinzu.
			1. Parameter:			x-Koordinate
			2. Parameter:			y-Koordinate
			3. Parameter:			z-Koordinate
		*/

		void add_vertex_pos(float, float, float);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion erstellt das Licht und sendet es an die GPU.
			return:						en_err
		*/

		int create();

	///////////////////////////////////////////
	// public
	///////////////////////////////////////////

	public:

		CLight();
		~CLight();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion erstellt eine direkte Lichtquelle.
			1. Parameter:			flag, ob die Lampe sichtbar oder unsichtbar ist (Lichtquelle bleibt aber erhalten!)
			2. Parameter:			welche geometrische Form die Lampe haben soll
			3. Parameter:			Rotlichtanteil (0 - 1), bezieht sich nur auf LIGHT_VISIBLE! (Würfel oder ähnliches)
			4. Parameter:			Grünlichtanteil (0 - 1), bezieht sich nur auf LIGHT_VISIBLE! (Würfel oder ähnliches)
			5. Parameter:			Blaulichtanteil (0 - 1), bezieht sich nur auf LIGHT_VISIBLE! (Würfel oder ähnliches)
			6. Parameter:			Alphalichtanteil (0 - 1), bezieht sich nur auf LIGHT_VISIBLE! (Würfel oder ähnliches)
			return:						err_en
		*/

		int create_directional_light(unsigned short int, short int, float, float, float, float);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion malt das Licht, sollte es sichtbar sein.
			1. Parameter:			Shader Programm ID
			return:						err_en
		*/

		int draw(int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion legt die Position des Lichtes fest.
			1. Parameter:			x-Koordinate
			2. Parameter:			y-Koordinate
			3. Parameter:			z-Koordinate
		*/

		void set_light_pos(float, float, float);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion gibt die Farbe des Lichtes zurück.
		*/

		glm::vec4 get_color();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Gibt die Position des Lichtes zurück.
			return:						vec3
		*/

		glm::vec3 get_light_pos();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Setze das eigentliche Licht!
			1. Parameter:			ambient x
			2. Parameter:			ambient y
			3. Parameter:			ambient z
			4. Parameter:			diffuse x
			5. Parameter:			diffuse y
			6. Parameter:			diffuse z
			7. Parameter:			specular x
			8. Parameter:			specular y
			9. Parameter:			specular z
		*/
	
		void set_light(float, float, float, float, float, float, float, float, float);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion gibt die Ambienteigentschaften des Lichtes zurück.
			return:						vec3
		*/

		glm::vec3 get_ambient_light();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion gibt die Diffuseeigentschaften des Lichtes zurück.
			return:						vec3
		*/

		glm::vec3 get_diffuse_light();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion gibt die Speculareigentschaften des Lichtes zurück.
			return:						vec3
		*/

		glm::vec3 get_specular_light();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion setzt den direction Vektor eines Lichtes.
			1. Parameter:			x-Komponente
			2. Parameter:			y-Komponente
			3. Parameter:			z-Komponente
		*/
	
		void set_direction(float, float, float);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion schaltet das Licht an oder aus.
			1. Parameter:			0 aus, 1 an
		*/

		void switch_light(unsigned short int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion gibt die Information, ob die Lichtquelle an ist.
			return:						flag
		*/

		int get_light_state();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion erstellt eine punktuelle Lichtquelle.
			1. Parameter:			flag, ob die Lampe sichtbar oder unsichtbar ist (Lichtquelle bleibt aber erhalten!)
			2. Parameter:			welche geometrische Form die Lampe haben soll
			3. Parameter:			Rotlichtanteil (0 - 1), bezieht sich nur auf LIGHT_VISIBLE! (Würfel oder ähnliches)
			4. Parameter:			Grünlichtanteil (0 - 1), bezieht sich nur auf LIGHT_VISIBLE! (Würfel oder ähnliches)
			5. Parameter:			Blaulichtanteil (0 - 1), bezieht sich nur auf LIGHT_VISIBLE! (Würfel oder ähnliches)
			6. Parameter:			Alphalichtanteil (0 - 1), bezieht sich nur auf LIGHT_VISIBLE! (Würfel oder ähnliches)
			return:						err_en
		*/

		int create_pointing_light(unsigned short int, short int, float, float, float, float);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion setzt die Distanz für eine punktuelle Lichtquelle. (So weit kommt es)
			1. Parameter:			Konstante
			2. Parameter: 		Linear
			3. Parameter:			Quadrat
		*/

		void set_plight_dist(float, float, float);
};

#endif
