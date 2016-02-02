#ifndef H_EN_APP
#define H_EN_APP

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
		int shader_program;								// ID des Shader Programm
    int * pShaders;										// IDs der Shader, Vertex-S, Fragment-S
		unsigned short int size_shader;		// Anzahl an Shader
		CModel_3D ** ppModel;							// Zeiger auf Models
		unsigned int number_models;				// Anzahl an Models
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

		/*
			Beschreibung:			gibt Position des Model zurück.
			1. Parameter:			index des Models
			return:						Modelverhalten
		*/

		glm::mat4 get_mdl_pos(unsigned int);

		/*
			Beschreibung:			Diese Funktion prüft die gesetzten Open GL Attribute.
			return:						en_err
		*/

		int check_ogl_attributes();

		/*
			Beschreibung:			Diese Funktion lädt die Shader.
			return:						en_err
		*/

		int init_shader();

		/*
			Beschreibung:			Diese Funktion lädt einen Shader und gibt die ID
										zurück.
			1. Parameter:			Dateipfad
			2. Parameter:			Die Art des Shader
			return:						Shader ID
		*/

		int load_shader(const char*, GLenum);

  public:

		CApp();
    ~CApp();

		/*
			Beschreibung:			Diese Funktion setzt die Open GL Attribute.
			return:						en_err
		*/

		int set_ogl_attr();

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

		/*
			Beschreibung:			Diese Funktion initialisiert OpenGL.
			return:						en_err
		*/

    int init_open_gl();

		/*
			Beschreibung:			Diese Funktion setzt CPU.timestep.
			1. Parameter:			Der Wert, der angenommen werden soll	
		*/	

    void cpu_set_timestep(double);

		/*
			Beschreibung:			Diese Funktion setzt CPU.timestamp.	
			1. Parameter:			Der Wert, der angenommen werden soll
		*/	

    void cpu_set_timestamp(int);

    /*
			Beschreibung:			Diese Funktion setzt CPU.timestamp_prev auf
												CPU.timestamp.	
		*/	

    void cpu_set_timestamp_prev();

		/*
			Beschreibung:			Diese Funktion gibt CPU.timestep zurück.	
			return:						CPU.timestep
		*/

		double cpu_get_timestep();

    /*
			Beschreibung:			Diese Funktion gibt CPU.timestamp zurück.	
			return:						CPU.timestamp
		*/

		int cpu_get_timestamp();

    /*
			Beschreibung:			Diese Funktion gibt CPU.timestamp_prev zurück.	
			return:						CPU.timestamp_prev
		*/

		int cpu_get_timestamp_prev();

		/*
			Beschreibung:			Diese Funktion gibt die Adresse der SDL_Event Variable zurück.
			return:						SDL_Event*
		*/

		SDL_Event * get_event();

		/*
			Beschreibung:			Diese Funktion gibt pWindow zurück.
			return:						pWindow
		*/

		SDL_Window * get_window();

		/*
			Beschreibung:			Diese Funktion gibt event zurück.
			return:						event
		*/

		SDL_Event get_eventx();

		/*
			Beschreibung:			Diese Funktion legt die Anzahl an shader fest. Darf nur einmal
												aufgerufen werden!
			1. Parameter:			Anzahl an Shader
		*/

		void number_shader(unsigned short int);

		/*
			Beschreibung:			Setzt die ID des Shader Programmes in der Programmvariable.
			1. Parameter:			ID des Shader Programmes
		*/

		void set_shader_program_id(int);

		/*
			Beschreibung:			Setzt die ID eines Shaders.
			1. Parameter:			Index des Shaders.
			2. Parameter:			ID des Shaders
		*/

		void set_shader_id(unsigned short int, int);

		/*
			Beschreibung: 		Diese Funktion gibt die Anzahl an Shader zurück.
			return:						Anzahl an Shader
		*/

		unsigned short int get_shader_number();

		/*
			Beschreibung:			Diese Funktion gibt anhand eines Indexes die Shader ID
												zurück.
			return:						Shader ID
		*/

		int get_shader_id(unsigned short int);

		/*
			Beschreibung:			Diese Funktion gibt die Shader Programm ID zurück.
			return:						Shader Programm ID
		*/

		int get_shader_program_id();
		
		/*
			Beschreibung:			Diese Funktion legt die Anzahl der Models für's Spiel fest
												und legt den Speicher an.
		*/

		void set_number_models(unsigned int);

		/*
			Beschreibung:			Diese Funktion gibt die Adresse von pModel zurück.
			return:						ppModel
		*/

		CModel_3D ** get_model_addr();

		/*
			Beschreibung:			Zeichnet anhand eines Index ein Model
			1. Parameter:			Der index
		*/

		void draw_model(unsigned int);

		/*
			Beschreibung:			Diese Funktion erstellt die Kamera.
		*/

		void init_camera();

		/*
			Beschreibung:			Diese Funktion bereitet die Projektion der Kamera vor.
		*/

		void proj();

		/*
			Beschreibung:			Diese Funktion gibt poly_mode zurück.
			return:						Adresse von poly_mode
		*/

    unsigned short int * get_poly_mode();

		/*
			Beschreibung:			Diese Funktion fügt einen String dem Debug File hinzu.
			1. Parameter:			Der String
			2. Parameter:			DB_MSG_OK (normal) oder DM_MSG_ERR (Fehler hervorheben)
		*/

		void write_log(const char*, short int);

		/*
			Beschreibung:			Diese Funktion erstellt die Log Datei.
		*/

		void create_log();

		/*
			Beschreibung:			Diese Funktion initialisiert die Debug Log Datei.
			1. Parameter:			Anzahl an Zeichen in der Datei.
		*/

    void init_debug_log(unsigned short int);

		/*
			Beschreibung:			Diese Funktion rotiert ein Model anhand ihres Indexes.
			1. Parameter:			Der Index.
			2. Parameter:			Rotationsgeschwindigkeit
			3. Parameter:			Achsen
		*/

		void rotate(unsigned short int, float, glm::vec3);

		/*
			Beschreibung:			Diese Funktion initialisiert die Engine.
												- SDL2
												- OGL
												- Shader
			1. Parameter:			Name des Programmes
			return:						en_err
		*/
	
		int init_engine(const char*);

    /*
			Beschreibung:			Diese Funktion entlädt das Shader Programm.
			1. Parameter:     Programmvariable
		*/

		void unload_shader();

		/*
			Beschreibung:			Diese Funktion liefert die Kamera Position.
			return:						camera_pos
		*/

		glm::vec3 get_camera_pos();

		/*
			Beschreibung:			Diese Funktion setzt eine neue Kamera Position.
			1. Parameter:			neue Position
		*/

		void set_camera_pos(glm::vec3);
};

#endif
