#ifndef H_GM_ERROR
#define H_GM_ERROR

///////////////////////////////////////////
///////////////////////////////////////////
// Konstanten
///////////////////////////////////////////
///////////////////////////////////////////

#define ERR_GM_NO_ERROR										0									// Es sind keine Fehler aufgetreten
#define ERR_GM_SHADER_PROG								1									// glCreateProgram ist fehlgeschlagen
#define ERR_GM_LOAD_SHADER								2									// load_shader ist fehlgeschlagen
#define ERR_GM_ATTACH_SHADER							3									// glAttachShader ist fehlgeschlagen
#define	ERR_GM_LINK_PROG									4									// glLinkProgram ist fehlgeschlagen
#define ERR_GM_USE_PROG										5									// glUseProgram ist fehlgeschlagen
#define ERR_GM_DEPTH_TEST									6									// glEnable depth test ist fehlgeschlagen
#define ERR_GM_DEPTH_FUNC									7									// glDepthFunc ist fehlgeschlagen

#endif
