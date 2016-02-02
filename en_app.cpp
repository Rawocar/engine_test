#include "../incl/en_app.h"

///////////////////////////////////////////
///////////////////////////////////////////
// Konstruktor / Destruktor
///////////////////////////////////////////
///////////////////////////////////////////

//------------------------------------------------------------------------
//------------------------------------------------------------------------

CApp::CApp():
shader_program(0),
size_shader(0),
number_models(0),
poly_mode(POLY_MODE_FILL),
en_error(ERR_EN_NO_ERROR),
gm_error(0),
debug_i(0),
debug_size(0)
{
  this->pWindow = NULL;
	this->pShaders = NULL;
	this->ppModel = NULL;
	this->pDebug_Str = NULL;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

CApp::~CApp()
{
	if(this->pDebug_Str != NULL)
		{delete [] this->pDebug_Str;}

  if(this->ppModel != NULL)
	{
		for(unsigned int i = 0 ; i < this->number_models ; i++)
			{delete ppModel[i];}
	}

	if(this->ppModel != NULL)
		{delete [] ppModel;}

	if(this->size_shader > 0)
		{delete [] pShaders;}
}

///////////////////////////////////////////
///////////////////////////////////////////
// private methods
///////////////////////////////////////////
///////////////////////////////////////////

int CApp::set_ogl_attr()
{
  int exit_code = ERR_EN_NO_ERROR;

	#if EMODE == EDEBUG_MODE
		char * pBuffer = NULL;
		pBuffer = new char[200];
	#endif

  // Setzen

  if(SDL_GL_SetAttribute(SDL_GL_RED_SIZE, RED_BIT_SIZE) == 0)
	{
    if(SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, GREEN_BIT_SIZE) == 0)
    {
      if(SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, BLUE_BIT_SIZE) == 0)
      {
				if(SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, ALPHA_BIT_SIZE) == 0)
				{
          if(SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, DOUBLE_BUFFER) == 0)
					{
						if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) == 0)
						{
							if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, MAJOR_VERSION) == 0)
							{
								if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, MINOR_VERSION) == 0)
								{
									if(SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, DEPTH_SIZE) != 0)
										{exit_code = ERR_EN_OGL_DEPTHSIZE;}
								}								
								else									
									{exit_code = ERR_EN_OGL_MINORVERSION;}
							}
							else
								{exit_code = ERR_EN_OGL_MAJORVERSION;}
						}
						else
							{exit_code = ERR_EN_OGL_CONTEXT_PROFILE_MASK;}
					}
					else
						{exit_code = ERR_EN_OGL_DOUBLEBUFFER;}
				}
				else
				  {exit_code = ERR_EN_OGL_ALPHA_SIZE;}
			}
			else
				{exit_code = ERR_EN_OGL_BLUE_SIZE;}
    }
    else
			{exit_code = ERR_EN_OGL_GREEN_SIZE;}
	}
	else
		{exit_code = ERR_EN_OGL_RED_SIZE;}

  #if EMODE == EDEBUG_MODE
		if(exit_code != ERR_EN_NO_ERROR)
		{
			sprintf(pBuffer, "<b>ENGINE:</b> set_ogl_attr(): SDL Error: %s --end OpenGL Error: %s", SDL_GetError(), glewGetErrorString(glGetError()));
			this->write_log(pBuffer, DB_MSG_ERR);
		}
		else
			{this->write_log("<b>ENGINE:</b> set_ogl_attr(): OK", DB_MSG_OK);}

		delete [] pBuffer;
	#endif

  return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

glm::mat4 CApp::get_mdl_pos(unsigned int i)
{
  return ppModel[i]->get_mdl_pos();
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::check_ogl_attributes()
{
  int exit_code = ERR_EN_NO_ERROR;
  int red_size = 0;
  int green_size = 0;
  int blue_size = 0;
  int alpha_size = 0;
  int double_buffer = 0;
  int major_version = 0;
	int minor_version = 0;
	int depth_size = 0;

	#if EMODE == EDEBUG_MODE
		char * pBuffer = NULL;
		pBuffer = new char[2048];
	#endif

  if(!SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &red_size) && !SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &green_size) && !SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &blue_size) && !SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &alpha_size) && !SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &double_buffer) && !SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major_version) && !SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor_version) && !SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &depth_size))
	{
		// prüfe hier die Werte

		if(!(red_size == RED_BIT_SIZE && green_size == GREEN_BIT_SIZE && blue_size == BLUE_BIT_SIZE && alpha_size == ALPHA_BIT_SIZE && major_version == MAJOR_VERSION && minor_version == MINOR_VERSION && depth_size == DEPTH_SIZE))
      {exit_code = ERR_EN_ATTR;}
	}
	else
	{
		exit_code = ERR_EN_OGL_GET_ATTR;
		sprintf(pBuffer, "<b>ENGINE:</b> SDL Error: %s --end OpenGL Error: %s --end", SDL_GetError(), glewGetErrorString(glGetError()));
		this->write_log(pBuffer, DB_MSG_ERR);
	}

  #if EMODE == EDEBUG_MODE
	  if(exit_code == ERR_EN_ATTR)
		{
      if(pBuffer != NULL)
			{
				sprintf(pBuffer, "<b>ENGINE:</b><br><table style=\"width: 400px;\"><tr><td style=\"width: 220px; text-decoration: underline; height: 30px;\">GL Attribut</td><td style=\"width: 90px; text-decoration: underline; height: 30px;\">erwartet</td><td style=\"width: 90px; text-decoration: underline; height: 30px;\">gesetzt</td></tr><tr><td>red size:</td><td>%d</td><td>%d</td></tr><tr><td>green size:</td><td>%d</td><td>%d</td></tr><tr><td>blue size:</td><td>%d</td><td>%d</td></tr><tr><td>alpha size:</td><td>%d</td><td>%d</td></tr><tr><td>doublebuffer:</td><td>%d</td><td>%d</td></tr><tr><td>major version:</td><td>%d</td><td>%d</td></tr><tr><td>minor version:</td><td>%d</td><td>%d</td></tr><tr><td>depth size:</td><td>%d</td><td>%d</td></tr><tr><td>SDL Error: %s</td></tr><tr><td>GL Error: %d</td></tr></table>", RED_BIT_SIZE, red_size, GREEN_BIT_SIZE, green_size, BLUE_BIT_SIZE, blue_size, ALPHA_BIT_SIZE, alpha_size, DOUBLE_BUFFER, double_buffer, MAJOR_VERSION, major_version, MINOR_VERSION, minor_version, DEPTH_SIZE, depth_size, SDL_GetError(), glGetError());

				if(this->pDebug_Str != NULL)
					{this->write_log(pBuffer, DB_MSG_ERR);}
      }
		}
	#endif

	#if EMODE == EDEBUG_MODE
		delete [] pBuffer;
	#endif

  return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::init_shader()
{
	int exit_code = ERR_EN_NO_ERROR;

	#if EMODE == EDEBUG_MODE
		char * pBuffer = NULL;
		pBuffer = new char[2048];
	#endif

  // erstelle Shader Programm

	this->shader_program = glCreateProgram();

	if(this->shader_program)
	{
		#if EMODE == EDEBUG_MODE
			this->write_log("<b>ENGINE:</b> glCreateProgram: OK", DB_MSG_OK);
		#endif

		// Anzahl an Shader

  	this->number_shader(2);

		// Lade Shader

		this->set_shader_id(0, this->load_shader("shader/vert.glsl", GL_VERTEX_SHADER));
		this->set_shader_id(1, this->load_shader("shader/frag.glsl", GL_FRAGMENT_SHADER));

		// an die GPU senden und auf use schalten

		glLinkProgram(this->shader_program);
						
		if(glGetError() == GL_NO_ERROR)
		{
			#if EMODE == EDEBUG_MODE
				this->write_log("<b>ENGINE:</b> glLinkProgram: OK", DB_MSG_OK);
			#endif

			glUseProgram(this->shader_program);

			if(glGetError() == GL_NO_ERROR)
			{
				#if EMODE == EDEBUG_MODE
					this->write_log("<b>ENGINE:</b> glUseProgram: OK", DB_MSG_OK);
				#endif
			}
			else
			{
				exit_code = ERR_EN_USE_PROG;

				#if EMODE == EDEBUG_MODE
					sprintf(pBuffer, "<b>ENGINE:</b> glUseProgram() failed --end OpenGL Error: %s --end", glewGetErrorString(glGetError()));
					this->write_log(pBuffer, DB_MSG_ERR);
				#endif
			}
		}
		else
		{
			exit_code = ERR_EN_LINK_PROG;

			#if EMODE == EDEBUG_MODE
				sprintf(pBuffer, "<b>ENGINE:</b> glLinkProgram() failed --end OpenGL Error: %s --end", glewGetErrorString(glGetError()));
				this->write_log(pBuffer, DB_MSG_ERR);
			#endif
		}
	}
	else
	{
		exit_code = ERR_EN_SHADER_PROG;

		#if EMODE == EDEBUG_MODE
			sprintf(pBuffer, "<b>ENGINE:</b> glCreateProgram() failed --end OpenGL Error: %s --end", glewGetErrorString(glGetError()));
			this->write_log(pBuffer, DB_MSG_ERR);
		#endif
	}

	#if EMODE == EDEBUG_MODE
		delete [] pBuffer;
	#endif

	return exit_code;
}

///////////////////////////////////////////
///////////////////////////////////////////
// public methods
///////////////////////////////////////////
///////////////////////////////////////////

int CApp::init_wnd(const char * pName, int x, int y, int w, int h, int flags)
{
  int exit_code = ERR_EN_NO_ERROR;

	this->pWindow = SDL_CreateWindow(pName, x, y, w, h, flags);

  if(this->pWindow == NULL)
		{exit_code = ERR_EN_WND_FAILED;}

	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::init_open_gl()
{
  int exit_code = ERR_EN_NO_ERROR;

	// erstelle Kontext

	this->context = SDL_GL_CreateContext(this->pWindow);
    
	if(context != NULL)
	{
    // v-sync on!

		if(SDL_GL_SetSwapInterval(1) == 0)
		{
      glewExperimental = GL_TRUE;

      // init Open GL

			if(glewInit() != GLEW_OK)
			{
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "Could not initialize Open GL...", NULL);
				exit_code = ERR_EN_OGL_GLEW;
			}
			else
			{
				// prüfen

				exit_code = this->check_ogl_attributes();
			}
		}
		else
			{exit_code = ERR_EN_OGL_SWAP_INTERVAL;}
	}
	else
		{exit_code = ERR_EN_OGL_CONTEXT_FAILED;}

  return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CApp::cpu_set_timestep(double value)
{
  this->cpu.timestep = value;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CApp::cpu_set_timestamp(int value)
{
  this->cpu.timestamp = value;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CApp::cpu_set_timestamp_prev()
{
  this->cpu.timestamp_prev = this->cpu.timestamp;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

double CApp::cpu_get_timestep()
{
  return this->cpu.timestep;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::cpu_get_timestamp()
{
  return this->cpu.timestamp;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::cpu_get_timestamp_prev()
{
  return this->cpu.timestamp_prev;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

SDL_Event * CApp::get_event()
{
  return &(this->event);
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

SDL_Window * CApp::get_window()
{
  return this->pWindow;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

SDL_Event CApp::get_eventx()
{
  return this->event;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CApp::number_shader(unsigned short int x)
{
	this->size_shader = x;
	this->pShaders = new int[this->size_shader];
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CApp::set_shader_program_id(int id)
{
  this->shader_program = id;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CApp::set_shader_id(unsigned short int index, int id)
{
  this->pShaders[index] = id;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

unsigned short int CApp::get_shader_number()
{
  return this->size_shader;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::get_shader_id(unsigned short int index)
{
  return this->pShaders[index];
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::get_shader_program_id()
{
  return this->shader_program;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CApp::set_number_models(unsigned int number)
{
  this->number_models = number;
	this->ppModel = new CModel_3D * [this->number_models];

	for(unsigned int i = 0 ; i < this->number_models ; i++)
		{this->ppModel[i] = new CModel_3D();}
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

CModel_3D ** CApp::get_model_addr()
{
  return this->ppModel;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CApp::draw_model(unsigned int i)
{
  this->ppModel[i]->draw();
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CApp::init_camera()
{
	int width = 0;
	int height = 0;
  SDL_GetWindowSize(this->pWindow, &width, &height);

	this->projection = glm::perspective
	(
    45.0f,              // 45 Grad Sichtfeld
    (float)((float) width / (float) height),
    0.1f,               // Only render what's 0.1 or more away from camera
    100.0f              // Only render what's 100 or less away from camera
	);

	// Kamera

	this->camera_pos = glm::vec3(0.0f, 1.0f, 3.0f);
  this->camera_from_dir = glm::normalize(camera_pos - glm::vec3(0.0f, 0.0f, 0.0f));
	this->camera_up = glm::cross(camera_from_dir, (glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), camera_from_dir))));
	this->camera = glm::lookAt(camera_pos, camera_from_dir, camera_up);
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CApp::proj_model(unsigned int i)
{
  this->mvp = this->projection * this->camera * this->get_mdl_pos(i);
	int matrix_id = glGetUniformLocation(this->shader_program, "mvp");
	glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &(this->mvp[0][0]));
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

unsigned short int * CApp::get_poly_mode()
{
  return &(this->poly_mode);
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CApp::write_log(const char * pStr, short int flag)
{
  const unsigned short int OPEN_TAG = 4 + 1;
  const unsigned short int CLOSE_TAG = 5 + 1;
  const unsigned short int HR_TAG = 12 + 1;
  const unsigned short int OPEN_TAG_STYLE = 39 + 1;
  char pTr[OPEN_TAG] = "<tr>";
  char pTrc[CLOSE_TAG] = "</tr>";
  char pTd[OPEN_TAG] = "<td>";
  char pTdr[OPEN_TAG_STYLE] = "<td style=\"background-color: #ffaaaa;\">";
	char pTdb[OPEN_TAG_STYLE] = "<td style=\"background-color: #aaaaff;\">";
  char pTdc[CLOSE_TAG] = "</td>";
	char pHr[HR_TAG] = "<hr noshade>";
  unsigned short int len = strlen(pStr) + (2 * (OPEN_TAG - 1)) + (2 * (CLOSE_TAG - 1)) + (HR_TAG - 1);

  if(flag == DB_MSG_ERR || flag == DB_MSG_HL)
		{len = strlen(pStr) + this->debug_i + (OPEN_TAG - 1) + (OPEN_TAG_STYLE - 1) + (2 * (CLOSE_TAG - 1)) + (HR_TAG - 1);}

	// prüfe, ob String reinpasst

  if((this->debug_i + len) < (this->debug_size - 1))
	{
    strcat(this->pDebug_Str, pTr);

		if(flag == DB_MSG_HL)
			{strcat(this->pDebug_Str, pTdb);}
		else
		{
			if(flag == DB_MSG_ERR)
				{strcat(this->pDebug_Str, pTdr);}
			else
				{strcat(this->pDebug_Str, pTd);} 
    }

		strcat(this->pDebug_Str, pStr);
    strcat(this->pDebug_Str, pHr);
		strcat(this->pDebug_Str, pTdc);
		strcat(this->pDebug_Str, pTrc);
    this->debug_i += len;
    this->pDebug_Str[this->debug_i] = '\0';
	}
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CApp::create_log()
{
  FILE * pFile = NULL;
  time_t t = time(NULL);
  struct tm * ts = localtime(&t);
	int width = 0;
	int height = 0;
  SDL_GetWindowSize(this->pWindow, &width, &height);

	// Datei erzeugen / vorher löschen, wenn existiert

  pFile = fopen("debug.htm", "w+");

  if(pFile != NULL)
	{
		fprintf(pFile, "<html><head><title>DEBUG File</title><style>hr{border-bottom: 0px; border-top: 1px solid black;}</style></head><body><h1 style=\"font-size: 16px;\">Debug File - %s</h1><h2 style=\"font-size: 14px;\">Window: %dpx * %dpx</h2><table style=\"width: 450px; font-size: 10px;\">%s</table></body></html>", asctime(ts), width, height, this->pDebug_Str);
		fclose(pFile);
	}
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CApp::init_debug_log(unsigned short int bytes)
{
  if(bytes > 0)
	{
		this->debug_size = bytes;
		this->pDebug_Str = new char[this->debug_size];
	}
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CApp::rotate(unsigned short int i, float rot_speed, glm::vec3 axis)
{
	this->ppModel[i]->rotate(rot_speed, axis);
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::init_engine(const char * pApp_name)
{
  int exit_code = ERR_EN_NO_ERROR;

	#if EMODE == EDEBUG_MODE
		char * pBuffer = NULL;
		pBuffer = new char[200];
	#endif

	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
  {
    #if EMODE == EDEBUG_MODE
			this->write_log("<b>ENGINE:</b> SDL2 initialisiert...", DB_MSG_OK);
		#endif

  	// initialisiere SDL_GL_Attribute

		exit_code = this->set_ogl_attr();

		if(exit_code == ERR_EN_NO_ERROR)
		{
  		// initialisiere das Fenster

  		exit_code = this->init_wnd(pApp_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);

			if(exit_code == ERR_EN_NO_ERROR)
			{
				#if EMODE == EDEBUG_MODE
					this->write_log("<b>ENGINE:</b> SDL2 Fenster initialisiert...", DB_MSG_OK);
				#endif

  	  	// initialisiere Open GL

				exit_code = this->init_open_gl();

  	  	if(exit_code == ERR_EN_NO_ERROR)
				{
					#if EMODE == EDEBUG_MODE
						this->write_log("<b>ENGINE:</b> OpenGL initialisiert...", DB_MSG_OK);
					#endif

					// Lade Shader

					exit_code = this->init_shader();

					if(exit_code == ERR_EN_NO_ERROR)
					{
						#if EMODE == EDEBUG_MODE
							this->write_log("<b>ENGINE:</b> Shader initialisiert...", DB_MSG_OK);
						#endif

						// initialisiere depth buffer

						glEnable(GL_DEPTH_TEST);

						if(glGetError() == GL_NO_ERROR)
						{
							#if EMODE == EDEBUG_MODE
								this->write_log("<b>ENGINE:</b> glEnable(GL_DEPTH_TEST) OK", DB_MSG_OK);
							#endif

  	  	    	glDepthFunc(GL_LEQUAL);

							if(glGetError() == GL_NO_ERROR)
							{
								#if EMODE == EDEBUG_MODE
									this->write_log("<b>ENGINE:</b> glDepthFunc(GL_LEQUAL) OK", DB_MSG_OK);
								#endif

								// Lade Kamera

								this->init_camera();
							}
							else
							{
								exit_code = ERR_EN_DEPTH_FUNC;

								#if EMODE == EDEBUG_MODE
									sprintf(pBuffer, "<b>ENGINE:</b> glDepthFunc(GL_LEQUAL) ist fehlgeschlagen... FEHLERCODE: %d --end OpenGL Error: %s --end", exit_code, glewGetErrorString(glGetError()));
									this->write_log(pBuffer, DB_MSG_ERR);
								#endif
							}
						}
						else
						{
							exit_code = ERR_EN_DEPTH_TEST;

							#if EMODE == EDEBUG_MODE
								sprintf(pBuffer, "<b>ENGINE:</b> glEnable(GL_DEPTH_TEST) ist fehlgeschlagen... FEHLERCODE: %d --end OpenGL Error: %s --end", exit_code, glewGetErrorString(glGetError()));
								this->write_log(pBuffer, DB_MSG_ERR);
							#endif
						}
					}
					else
					{
						#if EMODE == EDEBUG_MODE
							sprintf(pBuffer, "<b>ENGINE:</b> Shader konnten nicht initialisiert werden... FEHLERCODE: %d --end OpenGL Error: %s --end", exit_code, glewGetErrorString(glGetError()));
							this->write_log(pBuffer, DB_MSG_ERR);
						#endif
					}
				}
				else
				{
  	  	  #if EMODE == EDEBUG_MODE
						sprintf(pBuffer, "<b>ENGINE:</b> OpenGL konnte nicht initialisiert werden... FEHLERCODE: %d --end SDL Error: %s --end OpenGL Error: %s --end", exit_code, SDL_GetError(), glewGetErrorString(glGetError()));
						this->write_log(pBuffer, DB_MSG_ERR);
					#endif
				}
			}
			else
			{
				#if EMODE == EDEBUG_MODE
					sprintf(pBuffer, "<b>ENGINE:</b> SDL2 Fenster konnte nicht initialisiert werden... FEHLERCODE: %d --end SDL Error: %s --end", exit_code, SDL_GetError());
					this->write_log(pBuffer, DB_MSG_ERR);
				#endif
			}
  	}
		else
		{
			#if EMODE == EDEBUG_MODE
				sprintf(pBuffer, "<b>ENGINE:</b> SDL_GL_Attribute konnten nicht gesetzt werden. FEHLERCODE: %d", exit_code);
				this->write_log(pBuffer, DB_MSG_ERR);
			#endif
		}

		#if EMODE == EDEBUG_MODE
			delete [] pBuffer;
		#endif
	}
	else
	{
		#if EMODE == EDEBUG_MODE
    	this->write_log("<b>ENGINE:</b> SDL2 - Initialisierung ist fehlgeschlagen...", DB_MSG_ERR);
		#endif
	}

	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

glm::vec3 CApp::get_camera_pos()
{
	return this->camera_pos;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CApp::set_camera_pos(glm::vec3 new_pos)
{
  this->camera_pos = new_pos;
	this->camera_from_dir = glm::normalize(camera_pos - glm::vec3(0.0f, 0.0f, 0.0f));
	this->camera_up = glm::cross(camera_from_dir, (glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), camera_from_dir))));
	this->camera = glm::lookAt(camera_pos, camera_from_dir, camera_up);
}