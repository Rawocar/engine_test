#ifndef H_EN_APP
#define H_EN_APP

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
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "en_glb.h"
#include "en_error.h"
#include "en_file.h"
#include "en_3d_mdl.h"
#include "en_light.h"

///////////////////////////////////////////
///////////////////////////////////////////
// Konstanten
///////////////////////////////////////////
///////////////////////////////////////////

#define RED_BIT_SIZE 			8
#define GREEN_BIT_SIZE		8
#define BLUE_BIT_SIZE			8
#define ALPHA_BIT_SIZE		0
#define MAJOR_VERSION			2
#define MINOR_VERSION			1
#define DOUBLE_BUFFER			1
#define DEPTH_SIZE				24					// ? Funktioniert nicht auf 24...
#define GL3_PROTOTYPES 		1						// exclude deprecated functions / core only

///////////////////////////////////////////
///////////////////////////////////////////
// Strukturen
///////////////////////////////////////////
///////////////////////////////////////////

typedef struct SCPU
{
  double timestep;
  int timestamp;
  int timestamp_prev;
} CPU;

typedef struct En_Shader
{
	int prog_id;					// Shader Programm ID
	int *	pID;						// ID der Shader Stufen
	int shader_steps;			// Anzahl der Shader in einem Programm
} Shader;

typedef struct En_Mdl_3D_elem
{
	En_Mdl_3D_elem * pLeft;			// Zeiger auf linkes Element
	En_Mdl_3D_elem * pRight;		// Zeiger auf rechtes Element
	CModel_3D * pModel;					// Das Model selbst
	int ID;											// Primary Key, darf alles außer -1 sein!
	bool active;								// sagt aus, ob ein Model aktiv ist. Folgende Funktionen werden nur ausgeführt, wenn das Model aktiv ist: draw_mdl(), rotate();
} Elem_3D_Mdl;

///////////////////////////////////////////
///////////////////////////////////////////
// Klassendeklaration
///////////////////////////////////////////
///////////////////////////////////////////

class CApp
{
  private:

		SDL_Window * pWindow;							// Das SDL Fenster
		SDL_Event event;									// Das SDL Event
		SDL_GLContext context;						// Der Open GL Renderer
		CPU cpu;													// Das CPU Messgerät
		Shader * pShader;									// Shader Programme
		Elem_3D_Mdl * p3DModel_Head;			// Listenkopf der 3D Modelle
		glm::mat4 projection;							// Projektion auf dem Bildschirm
		glm::mat4 mvp;										// Kombination aus allen Spaces
    unsigned short int poly_mode;			// sagt aus, ob Punkte, Linien oder Fill gezeichnet werden soll
		int en_error;											// Hier werden Fehlercodes der Engine gespeichert
		int gm_error;											// Hier werden Fehlercodes des Spieles gespeichert
		char * pDebug_Str;								// Hier werden Fehlernachrichten gespeichert
		unsigned short int debug_i;				// hier wird der aktuelle Index gespeichert
		unsigned short int debug_size;		// Länge des Debug Strings 
		glm::vec3 camera_pos;							// Position der Kamera
		glm::vec3 camera_from_dir;				// Richtung, in die die Kamera zeigt
		glm::vec3 camera_up;							// Up
		glm::mat4 camera;									// die fertige Kamera
		GLenum gl_err;										// Fehlercode OpenGL
		unsigned int log_bytes;						// Anzahl an Bytes, die tatsächlich reingeschrieben wurden
		CLight ** ppLight;								// Zeiger auf Lichtquellen
		unsigned int number_lights;				// Anzahl an Lichtquellen

		/*
			Beschreibung:			gibt Position des Model zurück.
			1. Parameter:			ID des Models
			return:						Modelverhalten
		*/

		glm::mat4 get_mdl_pos(int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion prüft die gesetzten Open GL Attribute.
			return:						en_err
		*/

		int check_ogl_attributes();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion lädt die Shader.
			return:						en_err
		*/

		int init_shader();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion lädt einen Shader und gibt die ID
										zurück.
			1. Parameter:			Shader Program
			2. Parameter:			Dateipfad
			3. Parameter:			Die Art des Shader
			return:						Shader ID
		*/

		int load_shader(unsigned short int, const char*, GLenum);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion setzt die Open GL Attribute.
			return:						en_err
		*/

		int set_ogl_attr();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion erstellt das Fenster.
			1. Parameter:			Der Name des Fensters
			2. Parameter:			x-Koordinate
			3. Parameter:			y-Koordinate
			4. Parameter:			Breite des Fensters in Pixel
			5. Parameter:			Höhe des Fensters in Pixel
			6. Parameter:			Flags / Eigentschaften des Fensters
			return:						en_err
		*/

		int init_wnd(const char*, int, int, int, int, int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion initialisiert OpenGL.
			return:						en_err
		*/

    int init_open_gl();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Setzt die ID eines Shaders.
			1. Parameter:			Shader Program
			2. Parameter:			Index des Shaders.
			3. Parameter:			ID des Shaders
		*/

		void set_shader_id(unsigned short, unsigned short int, int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung: 		Diese Funktion gibt die Anzahl an Shader zurück.
			1. Parameter:			Shader Program
			return:						Anzahl an Shader
		*/

		unsigned short int get_shader_number(unsigned short int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion gibt anhand eines Indexes die Shader ID
												zurück.
			1. Parameter:			Shader Program
			2. Parameter:			Shader Step ID
			return:						Shader ID
		*/

		int get_shader_step_id(unsigned short int, unsigned short int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion gibt die Shader Programm ID zurück.
			1. Parameter:			Shader Program
			return:						Shader Programm ID
		*/

		int get_shader_program_id(unsigned short int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion erstellt die Kamera.
		*/

		void init_camera();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion fügt der 3D Modell Liste ein neues Element hinzu.
			1. Parameter:			zugewiesene ID des Models
			2. Parameter:			Das Modelobjekt
			return:						Model Objekt Zeiger
		*/

	CModel_3D * add_3d_mdl(int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Gibt anhand einer ID das Modelobjekt zurück.
			1. Parameter:			ID
			return:						Model Objekt Zeiger
		*/

	CModel_3D * get_mdl(int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Gibt anhand einer ID ein Modelelement zurück.
			1. Parameter:			ID
			return:						Modelelement
		*/

	Elem_3D_Mdl * get_mdl_elem(int);

	///////////////////////////////////////////
	// public
	///////////////////////////////////////////

  public:

		CApp();
    ~CApp();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

    /*
			Beschreibung:			Diese Funktion entlädt das Shader Programm.
			1. Parameter:			Shader Program
		*/

		void unload_shader(unsigned short int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion setzt CPU.timestep.
			1. Parameter:			Der Wert, der angenommen werden soll	
		*/	

    void cpu_set_timestep(double);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion setzt CPU.timestamp.	
			1. Parameter:			Der Wert, der angenommen werden soll
		*/	

    void cpu_set_timestamp(int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

    /*
			Beschreibung:			Diese Funktion setzt CPU.timestamp_prev auf
												CPU.timestamp.	
		*/	

    void cpu_set_timestamp_prev();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion gibt CPU.timestep zurück.	
			return:						CPU.timestep
		*/

		double cpu_get_timestep();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

    /*
			Beschreibung:			Diese Funktion gibt CPU.timestamp zurück.	
			return:						CPU.timestamp
		*/

		int cpu_get_timestamp();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

    /*
			Beschreibung:			Diese Funktion gibt CPU.timestamp_prev zurück.	
			return:						CPU.timestamp_prev
		*/

		int cpu_get_timestamp_prev();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion gibt die Adresse der SDL_Event Variable zurück.
			return:						SDL_Event*
		*/

		SDL_Event * get_event();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion gibt pWindow zurück.
			return:						pWindow
		*/

		SDL_Window * get_window();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion gibt event zurück.
			return:						event
		*/

		SDL_Event get_eventx();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Zeichnet alle Modelle, die aktiv UND sichtbar sind
			return:						err_en
		*/

		int draw_mdl();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion bereitet die Projektion der Kamera vor und
												sendet die Daten an die GPU.
			return:						err_en
		*/

		int proj();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion gibt poly_mode zurück.
			return:						Adresse von poly_mode
		*/

    unsigned short int * get_poly_mode();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion fügt einen String dem Debug File hinzu.
			1. Parameter:			Der String
			2. Parameter:			DB_MSG_OK (normal) oder DM_MSG_ERR (Fehler hervorheben)
		*/

		void write_log(const char*, short int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion erstellt die Log Datei.
		*/

		void create_log();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion initialisiert die Debug Log Datei.
			1. Parameter:			Anzahl an Zeichen in der Datei.
		*/

    void init_debug_log(unsigned short int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion rotiert ein Model anhand ihres Indexes.
			1. Parameter:			ID des Models
			2. Parameter:			Rotationsgeschwindigkeit
			3. Parameter:			Achsen
			return:						err_en
		*/

		int rotate(int, float, glm::vec3);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion initialisiert die Engine.
												- SDL2
												- OGL
												- Shader
			1. Parameter:			Name des Programmes
			return:						en_err
		*/
	
		int init_engine(const char*);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion liefert die Kamera Position.
			return:						camera_pos
		*/

		glm::vec3 get_camera_pos();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion setzt eine neue Kamera Position.
			1. Parameter:			neue Position
		*/

		void set_camera_pos(glm::vec3);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion erstellt einen Würfel als Model.
			1. Parameter:			Model ID zur Identifizierung
			2. Parameter:			Spannweite in eine Dimension
			return:						err_en
		*/

		int create_cube(int, float);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion setzt die Position eines Models.
			1. Parameter:			ID des Models
			2. Parameter:			x-Koordinate
			3. Parameter:			y-Koordinate
			4. Parameter:			z-Koordinate		
			return:						err_en	
		*/
		
		int set_mdl_pos(int, float, float, float);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion erstellt eine direkte Lichtquelle.
			1. Parameter:			Index des Lichtes
			2. Parameter:			flag, ob die Lampe sichtbar oder unsichtbar ist (Lichtquelle bleibt aber erhalten!)
			3. Parameter:			welche geometrische Form die Lampe haben soll
			4. Parameter:			Rotlichtanteil (0 - 1)
			5. Parameter:			Grünlichtanteil (0 - 1)
			6. Parameter:			Blaulichtanteil (0 - 1)
			7. Parameter:			Alphalichtanteil (0 - 1)
			return:						err_en
		*/

		int create_directional_light(unsigned int, unsigned short int, short int, float, float, float, float);

//------------------------------------------------------------------------
//------------------------------------------------------------------------
		
		/*
			Beschreibung:			Diese Funktion legt die Anzahl der Lichtquellen für's Spiel fest
												und legt den Speicher an.
			1. Parameter:			Anzahl an Lichtquellen
			return:						err_en
		*/

		int set_number_lights(unsigned int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Legt die Position einer direkten Lichtquelle fest / auch den dir Vektor.
			1. Parameter:			Index der Lichtquelle
			2. Parameter:			x-Koordinate
			3. Parameter:			y-Koordinate
			4. Parameter:			z-Koordinate
		*/

		int set_light_pos(unsigned int, float, float, float);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion zeichnet eine Lichtquelle.
			1. Parameter:			Index der Lichtquelle
			return:						err_en
		*/

		int draw_light(unsigned int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion bestimmt das Material für ein Model.
			1. Parameter:			ID des Models
			2. Parameter:			Material flag
			return:						err_en
		*/

		int set_material(int, int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion setzt das eigentliche Licht.
			1. Parameter:			Index des Lichtes
			2. Parameter:			ambient x
			3. Parameter:			ambient y
			4. Parameter:			ambient z
			5. Parameter:			diffuse x
			6. Parameter:			diffuse y
			7. Parameter:			diffuse z
			8. Parameter:			specular x
			9. Parameter:			specular y
			10. Parameter:		specular z
			return:						err_en
		*/

		int set_light(unsigned int, float, float, float, float, float, float, float, float, float);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion setzt die Textur für einen Würfel.
			1. Parameter:			ID des Models
			2. Parameter:			Texturpfad
			3. Parameter:			repeat Faktor
			4. Parameter:			Art der Texture
			5. Parameter:			Kanäle, die gezeichnet werden sollen
			return:						err_en
		*/

		int set_texture_cube(int, const char*, float, int, int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion schaltet das Licht an oder aus.
			1. Parameter:			index des Lichtes
			2. Parameter:			0 aus, 1 an
			return:						err_en
		*/

		int switch_light(unsigned int, unsigned short int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion gibt die Information, ob ein Licht aus oder an ist.
			1. Parameter:			Index der Lichtquelle
			return:						flag
		*/

		int get_light_state(unsigned int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion erstellt eine punktuelle Lichtquelle.
			1. Parameter:			Index des Lichtes
			2. Parameter:			flag, ob die Lampe sichtbar oder unsichtbar ist (Lichtquelle bleibt aber erhalten!)
			3. Parameter:			welche geometrische Form die Lampe haben soll
			4. Parameter:			Rotlichtanteil (0 - 1)
			5. Parameter:			Grünlichtanteil (0 - 1)
			6. Parameter:			Blaulichtanteil (0 - 1)
			7. Parameter:			Alphalichtanteil (0 - 1)
			return:						err_en
		*/

		int create_pointing_light(unsigned int, unsigned short int, short int, float, float, float, float);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion setzt die Distanz für eine punktuelle Lichtquelle. (So weit kommt es)
			1. Parameter:			index der Lichtquelle
			2. Parameter:			Konstante
			3. Parameter: 		Linear
			4. Parameter:			Quadrat
			return:						err_en
		*/

		int set_plight_dist(unsigned int, float, float, float);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion gibt die Anzahl an Lichtquellen zurück.
			return:						Anzahl an Lichtquellen
		*/

		unsigned int get_number_lights();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion räumt den restlichen Arbeitspeicher beim Erstellen eines Models auf.
			1. Parameter:			ID des Models
			return:						err_en
		*/

		int finish_mdl_creation(int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion lädt ein Model aus einer .obj Datei.
			1. Parameter:			ID des Models			
			2. Parameter:			Dateipfad
		*/

		int load_mdl_from_obj(int, const char*);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion gibt ein Fehlerfenster aus, anhand eines en_err codes.
			1. Parameter:			Text, der vom Entwickler noch zum Fehler angegeben werden soll
			2. Parameter:			en_err
			return:						1 = Beenden
		*/

		int print_error(const char*, int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion erzeugt ein 2D Quadrat.
			1. Parameter:			ID des Models
			2. Parameter:			Spannweite in eine Dimension
			return:						err_en
		*/

		int create_square(int, float);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion legt eine Textur auf ein Quadrat.
			1. Parameter:			ID des Models
			2. Parameter:			Pfad der Textur
			3. Parameter:			Wiederholungsfaktor
			4. Parameter:			Art der Textur
			5. Parameter:			Kanäle, die gezeichnet werden sollen
			return:						err_en
		*/

		int set_texture_square(int, const char*, float, int, int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------
	
		/*
			Beschreibung:			Diese Funktion gibt die Anzahl an Models zurück.
			return:						Anzahl an Models
		*/

		unsigned int get_number_models();

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion löscht ein Model komplett.
			1. Prameter:			ID des Models
		*/

		void delete_3d_mdl(int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion setzt anhand einer ID ein Model auf active.
			1. Parameter:			ID des Models
			return:						err_en
		*/

		int set_mdl_active(int);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

		/*
			Beschreibung:			Diese Funktion setzt anhand einer ID ein Model auf inactive.
			1. Parameter:			ID des Models
			return:						err_en
		*/

		int set_mdl_inactive(int);
};

#endif
