#ifndef H_EN_ERROR
#define H_EN_ERROR

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

#define ERR_EN_NO_ERROR											0									// Keine Fehler aufgetreten
#define ERR_EN_OGL_DEPTHSIZE								-1								// SDL_GL_DEPTH_SIZE konnte nicht gesetzt werden
#define ERR_EN_OGL_MINORVERSION							-2								// SDL_GL_CONTEXT_MINOR_VERSION konnte nicht gesetzt werden
#define ERR_EN_OGL_MAJORVERSION							-3								// SDL_GL_CONTEXT_MAJOR_VERSION konnte nicht gesetzt werden
#define ERR_EN_OGL_CONTEXT_PROFILE_MASK			-4								// SDL_GL_CONTEXT_PROFILE_MASK konnte nicht gesetzt werden
#define ERR_EN_OGL_DOUBLEBUFFER							-5								// SDL_GL_DOUBLEBUFFER konnte nicht gesetzt werden
#define ERR_EN_OGL_ALPHA_SIZE								-6								// SDL_GL_ALPHA_SIZE konnte nicht gesetzt werden
#define ERR_EN_OGL_BLUE_SIZE								-7								// SDL_GL_BLUE_SIZE konnte nicht gesetzt werden		
#define ERR_EN_OGL_GREEN_SIZE								-8								// SDL_GL_GREEN_SIZE konnte nicht gesetzt werden	
#define ERR_EN_OGL_RED_SIZE									-9								// SDL_GL_RED_SIZE konnte nicht gesetzt werden		
#define ERR_EN_OGL_GET_ATTR									-10								// Funktion SDL_GL_GetAttribute() ist fehlgeschlagen
#define ERR_EN_WND_FAILED										-11								// SDL_CreateWindow() ist fehlgeschlagen		
#define ERR_EN_OGL_CONTEXT_FAILED						-12								// SDL_GL_CreateContext() ist fehlgeschlagen
#define ERR_EN_OGL_GLEW											-13								// glewInit() ist fehlgeschlagen
#define ERR_EN_OGL_SWAP_INTERVAL						-14								// SDL_GL_SetSwapInterval() ist fehlgeschlagen
#define ERR_EN_FOPEN												-15								// fopen() ist fehlgeschlagen
#define ERR_EN_ATTR													-16								// SDL_GL_GetAttribute() liefert falsche Werte
#define ERR_EN_MDL_VAO											-17								// glGenVertexArrays() ist fehlgeschlagen
#define ERR_EN_MDL_BIND_VAO									-18								// glBindVertexArray() ist fehlgeschlagen
#define ERR_EN_MDL_VBO											-19								// glGenBuffers() ist fehlgeschlagen
#define ERR_EN_MDL_BIND_VBO									-20								// glBindBuffer() ist fehlgeschlagen
#define ERR_EN_MDL_VBO_DATA									-21								// glBufferData() ist fehlgeschlagen
#define ERR_EN_MDL_VAO_P										-22								// glVertexAttribPointer() ist fehlgeschlagen
#define ERR_EN_MDL_ENABLE_VAO								-23								// glEnableVertexAttribArray() ist fehlgeschlagen
#define ERR_EN_DEPTH_FUNC										-24								// glDepthFunc ist fehlgeschlagen
#define ERR_EN_DEPTH_TEST										-25								// glEnable depth test ist fehlgeschlagen
#define ERR_EN_USE_PROG											-26								// glUseProgram ist fehlgeschlagen
#define	ERR_EN_LINK_PROG										-27								// glLinkProgram ist fehlgeschlagen
#define ERR_EN_SHADER_PROG									-28								// glCreateProgram ist fehlgeschlagen
#define ERR_EN_GEN_TEXTURE									-29								// glGenTextures ist fehlgeschlagen
#define ERR_EN_BIND_TEXTURE									-30								// glBindTexture ist fehlgeschlagen
#define ERR_EN_LOAD_IMG											-31								// SOIL_load_image ist fehlgeschlagen
#define ERR_EN_GL_TEXTURE										-32								// glTexImage2D ist fehlgeschlagen
#define ERR_EN_MIPMAP_TEXTURE								-33								// glGenerateMipmap ist fehlgeschlagen
#define ERR_EN_PARI_TEXTURE									-34								// glTexParameteri ist fehlgeschlagen
#define	ERR_EN_CHECKLINK_PROG								-35								// glGetProgramiv ist fehlgeschlagen
#define ERR_EN_NO_MEM												-36								// es konnte kein Speicher alloziiert werden
#define ERR_EN_SDL													-37								// SDL konnte nicht initialisiert werden
#define ERR_EN_STENCIL_TEST									-38								// gl Enable stencil test ist fehlgeschlagen
#define ERR_EN_NO_MEMORY										-39								// NULL, kein Speicherverweis
#define ERR_EN_ACTIVE_TEX										-40								// glActiveTexture ist fehlgeschlagen
#define	ERR_EN_UNIF_LOC											-41								// glGetUniformLocation ist fehlgeschlagen
#define ERR_EN_MAT4F												-42								// glUniformMatrix4fv ist fehlgeschlagen
#define ERR_EN_DRAW_ARR											-43								// glDrawArrays ist fehlgeschlagen
#define ERR_EN_1F														-44								// glUniform1f ist fehlgeschlagen
#define ERR_EN_2DTEX												-45								// glEnable(GL_TEXTURE_2D) ist fehlgeschlagen
#define ERR_EN_1I														-46								// glUniform1i ist fehlgeschlagen
#define ERR_EN_3F														-47								// glUniform3f ist fehlgeschlagen
#define ERR_EN_BLEND												-48								// glEnable(GL_BLEND) fehlgeschlagen
#define ERR_EN_BLEND_FUNC										-49								// glBlendFunc() ist fehlgeschlagen

#endif
