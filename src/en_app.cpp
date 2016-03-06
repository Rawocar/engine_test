#include "../incl/en_app.h"

///////////////////////////////////////////
///////////////////////////////////////////
// Konstruktor / Destruktor
///////////////////////////////////////////
///////////////////////////////////////////

//------------------------------------------------------------------------
//------------------------------------------------------------------------

CApp::CApp():
poly_mode(POLY_MODE_FILL),
en_error(ERR_EN_NO_ERROR),
gm_error(0),
debug_i(0),
debug_size(0),
gl_err(GL_NO_ERROR),
log_bytes(0),
number_lights(0)
{
  this->pWindow = NULL;
	this->pDebug_Str = NULL;
	this->pShader = new Shader[2];
	this->ppLight = NULL;

	p3DModel_Head = new Elem_3D_Mdl;
	p3DModel_Head->pLeft = p3DModel_Head;
	p3DModel_Head->pRight = p3DModel_Head;
	p3DModel_Head->pModel = NULL;
	p3DModel_Head->ID = -1;
	p3DModel_Head->active = 0;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

CApp::~CApp()
{
	if(this->pDebug_Str != NULL)
		{delete [] this->pDebug_Str;}

	delete [] pShader;

	if(this->ppLight != NULL)
	{
		for(unsigned int i = 0 ; i < this->number_lights ; i++)
			{delete this->ppLight[i];}
	}

	if(this->ppLight != NULL)
		{delete [] ppLight;}

	// lösche restliche Models

	Elem_3D_Mdl * pCurrent = this->p3DModel_Head->pRight;
	int ID = 0;

	while(pCurrent != p3DModel_Head)
	{
		ID = pCurrent->ID;
		pCurrent = pCurrent->pRight;
		this->delete_3d_mdl(ID);
	}

	delete p3DModel_Head;
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

glm::mat4 CApp::get_mdl_pos(int ID)
{
	glm::mat4 mdl = glm::mat4(1.0f);

	CModel_3D * pModel = this->get_mdl(ID);
	
	if(pModel != NULL)
		{mdl = pModel->get_mdl_pos();}

	return mdl;
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
  int param = 0;
	int length_log = 0;
	const unsigned short int SIZE_LOG = 400 + 1;
	char compile_log[SIZE_LOG];

	#if EMODE == EDEBUG_MODE
		char * pBuffer = NULL;
		pBuffer = new char[2048];
	#endif

	////////////////////////////////////////
  // erstelle Shader Hauptprogramm
	////////////////////////////////////////

	#if EMODE == EDEBUG_MODE
		this->write_log("<b>ENGINE:</b> --------------- Shader Main ---------------", DB_MSG_OK);
	#endif

	this->pShader[SHADER_MAIN].prog_id = glCreateProgram();

	if(this->pShader[SHADER_MAIN].prog_id)
	{
		#if EMODE == EDEBUG_MODE
			this->write_log("<b>ENGINE:</b> glCreateProgram: OK", DB_MSG_OK);
		#endif

		// Anzahl an Shader Schritte
		
		this->pShader[SHADER_MAIN].shader_steps = 2;
		this->pShader[SHADER_MAIN].pID = new int [this->pShader[SHADER_MAIN].shader_steps];

		// Lade Shader

		this->set_shader_id(SHADER_MAIN, 0, this->load_shader(SHADER_MAIN, "shader/vert.glsl", GL_VERTEX_SHADER));
		this->set_shader_id(SHADER_MAIN, 1, this->load_shader(SHADER_MAIN, "shader/frag.glsl", GL_FRAGMENT_SHADER));

		// an die GPU senden und auf use schalten

		glLinkProgram(this->pShader[SHADER_MAIN].prog_id);
						
		if((this->gl_err = glGetError()) == GL_NO_ERROR)
		{
			glGetProgramiv(this->pShader[SHADER_MAIN].prog_id, GL_LINK_STATUS, &param);
		
			if((this->gl_err = glGetError()) == GL_NO_ERROR)
			{
				if(param == GL_TRUE)
				{
					#if EMODE == EDEBUG_MODE
						this->write_log("<b>ENGINE:</b> glLinkProgram: OK", DB_MSG_OK);
					#endif

					glUseProgram(this->pShader[SHADER_MAIN].prog_id);
			
					if((this->gl_err = glGetError()) == GL_NO_ERROR)
					{
						#if EMODE == EDEBUG_MODE
							this->write_log("<b>ENGINE:</b> glUseProgram: OK", DB_MSG_OK);
						#endif
					}
					else
					{
						exit_code = ERR_EN_USE_PROG;

						#if EMODE == EDEBUG_MODE
							sprintf(pBuffer, "<b>ENGINE:</b> glUseProgram() failed --end GL Flag: %d --end OpenGL Error: %s --end", this->gl_err, glewGetErrorString(this->gl_err));
							this->write_log(pBuffer, DB_MSG_ERR);
						#endif
					}
        }
				else
				{
					exit_code = ERR_EN_LINK_PROG;

					#if EMODE == EDEBUG_MODE
						glGetProgramInfoLog(this->pShader[SHADER_MAIN].prog_id, SIZE_LOG, &length_log, compile_log);
						sprintf(pBuffer, "<b>ENGINE:</b> failed to link shader program: %s --end", compile_log);
						this->write_log(pBuffer, DB_MSG_ERR);
					#endif
				}
      }
			else
			{
				exit_code = ERR_EN_CHECKLINK_PROG;

				#if EMODE == EDEBUG_MODE
					sprintf(pBuffer, "<b>ENGINE:</b> glGetProgramiv() failed --end GL Flag: %d --end OpenGL Error: %s --end", this->gl_err, glewGetErrorString(this->gl_err));
					this->write_log(pBuffer, DB_MSG_ERR);
				#endif
			}
		}
		else
		{
			exit_code = ERR_EN_LINK_PROG;

			#if EMODE == EDEBUG_MODE
				sprintf(pBuffer, "<b>ENGINE:</b> glLinkProgram() failed --end OpenGL Error: %s --end", glewGetErrorString(this->gl_err));
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

	glUseProgram(0);

	////////////////////////////////////////
  // erstelle Shader Licht Programm
	////////////////////////////////////////

	if(exit_code == ERR_EN_NO_ERROR)
	{
		#if EMODE == EDEBUG_MODE
			this->write_log("<b>ENGINE:</b> --------------- Shader Light ---------------", DB_MSG_OK);
		#endif

		this->pShader[SHADER_LIGHT].prog_id = glCreateProgram();

		if(this->pShader[SHADER_LIGHT].prog_id)
		{
			#if EMODE == EDEBUG_MODE
				this->write_log("<b>ENGINE:</b> glCreateProgram: OK", DB_MSG_OK);
			#endif

			// Anzahl an Shader Schritte
		
			this->pShader[SHADER_LIGHT].shader_steps = 2;
			this->pShader[SHADER_LIGHT].pID = new int [this->pShader[SHADER_LIGHT].shader_steps];

			// Lade Shader

			this->set_shader_id(SHADER_LIGHT, 0, this->load_shader(SHADER_LIGHT, "shader/vert_light.glsl", GL_VERTEX_SHADER));
			this->set_shader_id(SHADER_LIGHT, 1, this->load_shader(SHADER_LIGHT, "shader/frag_light.glsl", GL_FRAGMENT_SHADER));

			// an die GPU senden und auf use schalten

			glLinkProgram(this->pShader[SHADER_LIGHT].prog_id);
						
			if((this->gl_err = glGetError()) == GL_NO_ERROR)
			{
				glGetProgramiv(this->pShader[SHADER_LIGHT].prog_id, GL_LINK_STATUS, &param);
		
				if((this->gl_err = glGetError()) == GL_NO_ERROR)
				{
					if(param == GL_TRUE)
					{
						#if EMODE == EDEBUG_MODE
							this->write_log("<b>ENGINE:</b> glLinkProgram: OK", DB_MSG_OK);
						#endif

						glUseProgram(this->pShader[SHADER_LIGHT].prog_id);
			
						if((this->gl_err = glGetError()) == GL_NO_ERROR)
						{
							#if EMODE == EDEBUG_MODE
								this->write_log("<b>ENGINE:</b> glUseProgram: OK", DB_MSG_OK);
							#endif
						}
						else
						{
							exit_code = ERR_EN_USE_PROG;
	
							#if EMODE == EDEBUG_MODE
								sprintf(pBuffer, "<b>ENGINE:</b> glUseProgram() failed --end GL Flag: %d --end OpenGL Error: %s --end", this->gl_err, glewGetErrorString(this->gl_err));
								this->write_log(pBuffer, DB_MSG_ERR);
							#endif
						}
    	    }
					else
					{
						exit_code = ERR_EN_LINK_PROG;
	
						#if EMODE == EDEBUG_MODE
							glGetProgramInfoLog(this->pShader[SHADER_LIGHT].prog_id, SIZE_LOG, &length_log, compile_log);
							sprintf(pBuffer, "<b>ENGINE:</b> failed to link shader program: %s --end", compile_log);
							this->write_log(pBuffer, DB_MSG_ERR);
						#endif
					}
    	  }
				else
				{
					exit_code = ERR_EN_CHECKLINK_PROG;
	
					#if EMODE == EDEBUG_MODE
						sprintf(pBuffer, "<b>ENGINE:</b> glGetProgramiv() failed --end GL Flag: %d --end OpenGL Error: %s --end", this->gl_err, glewGetErrorString(this->gl_err));
						this->write_log(pBuffer, DB_MSG_ERR);
					#endif
				}
			}
			else
			{
				exit_code = ERR_EN_LINK_PROG;

				#if EMODE == EDEBUG_MODE
					sprintf(pBuffer, "<b>ENGINE:</b> glLinkProgram() failed --end OpenGL Error: %s --end", glewGetErrorString(this->gl_err));
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
	}

	glUseProgram(0);

	#if EMODE == EDEBUG_MODE
		delete [] pBuffer;
	#endif

	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::init_wnd(const char * pName, int x, int y, int w, int h, int flags)
{
  int exit_code = ERR_EN_NO_ERROR;
	SDL_DisplayMode dmode;

	if(w == 0 && h == 0)
	{
		if(!SDL_GetCurrentDisplayMode(0, &dmode))
			{this->pWindow = SDL_CreateWindow(pName, x, y, dmode.w, dmode.h, flags);}
	}
	else
		{this->pWindow = SDL_CreateWindow(pName, x, y, w, h, flags);}

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

void CApp::set_shader_id(unsigned short int si, unsigned short int index, int id)
{
  this->pShader[si].pID[index] = id;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

unsigned short int CApp::get_shader_number(unsigned short int si)
{
  return this->pShader[si].shader_steps;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::get_shader_step_id(unsigned short int si, unsigned short int index)
{
  return this->pShader[si].pID[index];
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::get_shader_program_id(unsigned short int si)
{
  return this->pShader[si].prog_id;
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

CModel_3D * CApp::add_3d_mdl(int ID)
{
	Elem_3D_Mdl * pLeft_Before = this->p3DModel_Head->pLeft;

	// initialisieren

	Elem_3D_Mdl * pNew = new Elem_3D_Mdl;
	pNew->ID = ID;
	pNew->pModel = new CModel_3D();
	pNew->active = 0;

	// links einfügen

	this->p3DModel_Head->pLeft = pNew;
	pNew->pRight = this->p3DModel_Head;
	pNew->pLeft = pLeft_Before;
	pLeft_Before->pRight = pNew;

	return pNew->pModel;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

CModel_3D * CApp::get_mdl(int ID)
{
	Elem_3D_Mdl * pCurrent = this->p3DModel_Head->pRight;
	CModel_3D * pRet = NULL;

	while(pCurrent->ID != ID && pCurrent != this->p3DModel_Head)
		{pCurrent = pCurrent->pRight;}

	// gefunden?

	if(pCurrent->ID == ID)
		{pRet = pCurrent->pModel;}

	return pRet;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

Elem_3D_Mdl * CApp::get_mdl_elem(int ID)
{
  Elem_3D_Mdl * pCurrent = this->p3DModel_Head->pRight;
	Elem_3D_Mdl * pRet = NULL;

	while(pCurrent->ID != ID && pCurrent != this->p3DModel_Head)
		{pCurrent = pCurrent->pRight;}

	// gefunden?

	if(pCurrent->ID == ID)
		{pRet = pCurrent;}

	return pRet;
}

///////////////////////////////////////////
///////////////////////////////////////////
// public methods
///////////////////////////////////////////
///////////////////////////////////////////

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

int CApp::draw_mdl()
{
	int exit_code = ERR_EN_NO_ERROR;
	Elem_3D_Mdl * pCurrent = this->p3DModel_Head->pRight;

	while(pCurrent != this->p3DModel_Head)
	{
		// aktiv?

		if(pCurrent->active == 1)
		{
			exit_code = pCurrent->pModel->draw(this->pShader[SHADER_MAIN].prog_id);

			if(exit_code != ERR_EN_NO_ERROR)
				{break;}
		}

		pCurrent = pCurrent->pRight;
	}	

	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::proj()
{
	int exit_code = ERR_EN_NO_ERROR;

  this->mvp = this->projection * this->camera;
	int matrix_id = 0;
	int vec_id = 0;

	glUseProgram(this->pShader[SHADER_MAIN].prog_id);

	if(glGetError() == GL_NO_ERROR)
	{
		matrix_id = glGetUniformLocation(this->pShader[SHADER_MAIN].prog_id, "mvp");

		if(glGetError() == GL_NO_ERROR)
		{
			glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &(this->mvp[0][0]));

			if(glGetError() == GL_NO_ERROR)
			{
				vec_id = glGetUniformLocation(this->pShader[SHADER_MAIN].prog_id, "camera");

				if(glGetError() == GL_NO_ERROR)
				{
					glUniform3f(vec_id, this->camera_pos.x, this->camera_pos.y, this->camera_pos.z);

					if(glGetError() == GL_NO_ERROR)
					{
						glUseProgram(0);
						
						if(glGetError() != GL_NO_ERROR)
							{exit_code = ERR_EN_USE_PROG;}
					}
				}
				else
					{exit_code = ERR_EN_UNIF_LOC;}
			}
			else
				{exit_code = ERR_EN_MAT4F;}
		}
		else
			{exit_code = ERR_EN_UNIF_LOC;}
	}
	else
		{exit_code = ERR_EN_USE_PROG;}

	if(exit_code == ERR_EN_NO_ERROR)
	{
		glUseProgram(this->pShader[SHADER_LIGHT].prog_id);

		if(glGetError() == GL_NO_ERROR)
		{
			matrix_id = glGetUniformLocation(this->pShader[SHADER_LIGHT].prog_id, "mvp");

			if(glGetError() == GL_NO_ERROR)
			{
				glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &(this->mvp[0][0]));

				if(glGetError() == GL_NO_ERROR)
				{
					glUseProgram(0);

					if(glGetError() != GL_NO_ERROR)
						{exit_code = ERR_EN_USE_PROG;}
				}
				else
					{exit_code = ERR_EN_MAT4F;}
			}
			else
				{exit_code = ERR_EN_UNIF_LOC;}
		}
		else
			{exit_code = ERR_EN_USE_PROG;}
	}

	return exit_code;
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
		{len = strlen(pStr) + (OPEN_TAG - 1) + (OPEN_TAG_STYLE - 1) + (2 * (CLOSE_TAG - 1)) + (HR_TAG - 1);}

	// prüfe, ob String reinpasst

  if((this->debug_i + len) < (this->debug_size - 1))
	{
		this->log_bytes += len;

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
		fprintf(pFile, "<html><head><title>DEBUG File</title><style>hr{border-bottom: 0px; border-top: 1px solid black;}</style></head><body><h1 style=\"font-size: 16px;\">Debug File - %s</h1><h2 style=\"font-size: 14px; margin: 0px;\">Window: %dpx * %dpx</h2><h3 style=\"font-size: 14px; margin: 0px;\">GL Version: %s</h3><h4 style=\"font-size: 14px; margin: 0px;\">GLSL Version: %s</h4><h5 style=\"font-size: 14px; margin: 0px;\">Zeichen: %u</h5><table style=\"width: 450px; font-size: 10px;\">%s</table></body></html>", asctime(ts), width, height, glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION), this->log_bytes, this->pDebug_Str);
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

int CApp::rotate(int ID, float rot_speed, glm::vec3 axis)
{
	int exit_code = ERR_EN_NO_ERROR;
	Elem_3D_Mdl * pElem = this->get_mdl_elem(ID);

	if(pElem != NULL)
	{
		if(pElem->active == 1)
			{pElem->pModel->rotate(rot_speed, axis);}
	}
	else
		{exit_code = ERR_EN_NO_MEMORY;}

	return exit_code;
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

  		exit_code = this->init_wnd(pApp_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);

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

						if((this->gl_err = glGetError()) == GL_NO_ERROR)
						{
							#if EMODE == EDEBUG_MODE
								this->write_log("<b>ENGINE:</b> glEnable(GL_DEPTH_TEST) OK", DB_MSG_OK);
							#endif

  	  	    	glDepthFunc(GL_LEQUAL);

							if((this->gl_err = glGetError()) == GL_NO_ERROR)
							{
								#if EMODE == EDEBUG_MODE
									this->write_log("<b>ENGINE:</b> glDepthFunc(GL_LEQUAL) OK", DB_MSG_OK);
								#endif

								// initialisiere Stencil Buffer

								glEnable(GL_STENCIL_TEST);

								if((this->gl_err = glGetError()) == GL_NO_ERROR)
								{
									#if EMODE == EDEBUG_MODE
										this->write_log("<b>ENGINE:</b> glEnable(GL_STENCIL_TEST) OK", DB_MSG_OK);
									#endif

									// Blending

									glEnable(GL_BLEND);

									if((this->gl_err = glGetError()) == GL_NO_ERROR)
									{
										#if EMODE == EDEBUG_MODE
											this->write_log("<b>ENGINE:</b> glEnable(GL_BLEND) OK", DB_MSG_OK);
										#endif

										glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

										if((this->gl_err = glGetError()) == GL_NO_ERROR)
										{
											#if EMODE == EDEBUG_MODE
												this->write_log("<b>ENGINE:</b> glBlendFunc() OK", DB_MSG_OK);
											#endif
										}
										else
										{
											exit_code = ERR_EN_BLEND_FUNC;

											#if EMODE == EDEBUG_MODE
												sprintf(pBuffer, "<b>ENGINE:</b> glBlendFunc() ist fehlgeschlagen... FEHLERCODE: %d --end OpenGL Error: %s --end", exit_code, glewGetErrorString(this->gl_err));
												this->write_log(pBuffer, DB_MSG_ERR);
											#endif
										}
									}
									else
									{
										exit_code = ERR_EN_BLEND;

										#if EMODE == EDEBUG_MODE
											sprintf(pBuffer, "<b>ENGINE:</b> glEnable(GL_BLEND) ist fehlgeschlagen... FEHLERCODE: %d --end OpenGL Error: %s --end", exit_code, glewGetErrorString(this->gl_err));
											this->write_log(pBuffer, DB_MSG_ERR);
										#endif
									}
								}
								else
								{
									exit_code = ERR_EN_STENCIL_TEST;

									#if EMODE == EDEBUG_MODE
										sprintf(pBuffer, "<b>ENGINE:</b> glEnable(GL_STENCIL_TEST) ist fehlgeschlagen... FEHLERCODE: %d --end OpenGL Error: %s --end", exit_code, glewGetErrorString(this->gl_err));
										this->write_log(pBuffer, DB_MSG_ERR);
									#endif
								}
							}
							else
							{
								exit_code = ERR_EN_DEPTH_FUNC;

								#if EMODE == EDEBUG_MODE
									sprintf(pBuffer, "<b>ENGINE:</b> glDepthFunc(GL_LEQUAL) ist fehlgeschlagen... FEHLERCODE: %d --end OpenGL Error: %s --end", exit_code, glewGetErrorString(this->gl_err));
									this->write_log(pBuffer, DB_MSG_ERR);
								#endif
							}
						}
						else
						{
							exit_code = ERR_EN_DEPTH_TEST;

							#if EMODE == EDEBUG_MODE
								sprintf(pBuffer, "<b>ENGINE:</b> glEnable(GL_DEPTH_TEST) ist fehlgeschlagen... FEHLERCODE: %d --end OpenGL Error: %s --end", exit_code, glewGetErrorString(this->gl_err));
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
		exit_code = ERR_EN_SDL;

		#if EMODE == EDEBUG_MODE
    	this->write_log("<b>ENGINE:</b> SDL2 - Initialisierung ist fehlgeschlagen...", DB_MSG_ERR);
		#endif
	}

	// Lade Kamera

	this->init_camera();

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

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::create_cube(int ID, float size)
{
	int exit_code = ERR_EN_NO_ERROR;
	CModel_3D * pModel = this->add_3d_mdl(ID);

	if(pModel != NULL)
		{exit_code = pModel->create_cube(size);}
	else
		{exit_code = ERR_EN_NO_MEMORY;}

  return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::set_mdl_pos(int ID, float x, float y, float z)
{
	int exit_code = ERR_EN_NO_ERROR;

	CModel_3D * pModel = this->get_mdl(ID);

	if(pModel != NULL)
  	{pModel->set_mdl_pos(x, y, z);}
	else
		{exit_code = ERR_EN_NO_MEMORY;}

	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::create_directional_light(unsigned int i, unsigned short int flag, short int geometry, float r, float g, float b, float a)
{
	int exit_code = ERR_EN_NO_ERROR;
  int id = 0;
	char pBuffer[100];
  exit_code = this->ppLight[i]->create_pointing_light(flag, geometry, r, g, b, a);

	if(exit_code == ERR_EN_NO_ERROR)
	{
		glUseProgram(this->pShader[SHADER_MAIN].prog_id);

		if(glGetError() == GL_NO_ERROR)
		{
			// Art des Lichtes

			sprintf(pBuffer, "light[%u].light_kind", i);
  		id = glGetUniformLocation(this->pShader[SHADER_MAIN].prog_id, pBuffer);

			if(glGetError() == GL_NO_ERROR)
			{
				glUniform1i(id, 1);

				if(glGetError() == GL_NO_ERROR)
				{
					glUseProgram(0);

					if(glGetError() == GL_NO_ERROR)
					{
						// Lichtschalter

						exit_code = this->switch_light(i, ON);
					}
					else
						{exit_code = ERR_EN_USE_PROG;}
				}
				else
					{exit_code = ERR_EN_1I;}
			}
			else
				{exit_code = ERR_EN_UNIF_LOC;}
		}
		else
			{exit_code = ERR_EN_USE_PROG;}
  }

	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::set_number_lights(unsigned int number)
{
	int exit_code = ERR_EN_NO_ERROR;
  this->number_lights = number;
	this->ppLight = new CLight * [this->number_lights];
	int id = 0;

	for(unsigned int i = 0 ; i < this->number_lights ; i++)
		{this->ppLight[i] = new CLight();}

	glUseProgram(this->pShader[SHADER_MAIN].prog_id);

	if(glGetError() == GL_NO_ERROR)
	{
		id = glGetUniformLocation(this->pShader[SHADER_MAIN].prog_id, "number_lights");

		if(glGetError() == GL_NO_ERROR)
		{
			glUniform1i(id, this->number_lights);

			if(glGetError() == GL_NO_ERROR)
			{
  			glUseProgram(0);

				if(glGetError() != GL_NO_ERROR)
					{exit_code = ERR_EN_USE_PROG;}
			}
			else
				{exit_code = ERR_EN_1I;}
		}
		else
			{exit_code = ERR_EN_UNIF_LOC;}
	}
	else
		{exit_code = ERR_EN_USE_PROG;}

	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::set_light_pos(unsigned int i, float x, float y, float z)
{
	int exit_code = ERR_EN_NO_ERROR;

	char pBuffer[100];
	int vec3_id = 0;

	this->ppLight[i]->set_light_pos(x, y, z);	
	glUseProgram(this->pShader[SHADER_MAIN].prog_id);

	if(glGetError() == GL_NO_ERROR)
	{
		this->ppLight[i]->set_direction(-x, -y, -z);
		sprintf(pBuffer, "light[%u].direction", i);
		vec3_id = glGetUniformLocation(this->pShader[SHADER_MAIN].prog_id, pBuffer);

		if(glGetError() == GL_NO_ERROR)
		{
			glUniform3f(vec3_id, -x, -y, -z);

			if(glGetError() != GL_NO_ERROR)
				{exit_code = ERR_EN_3F;}
		}
		else
			{exit_code = ERR_EN_UNIF_LOC;}
	}
	else
		{exit_code = ERR_EN_USE_PROG;}

	if(exit_code == ERR_EN_NO_ERROR)
	{
		glm::vec3 light_pos = this->ppLight[i]->get_light_pos();
		sprintf(pBuffer, "light[%u].position", i);
		vec3_id = glGetUniformLocation(this->pShader[SHADER_MAIN].prog_id, pBuffer);

		if(glGetError() == GL_NO_ERROR)
		{
			glUniform3f(vec3_id, light_pos.x, light_pos.y, light_pos.z);

			if(glGetError() != GL_NO_ERROR)
				{exit_code = ERR_EN_3F;}
		}
		else
			{exit_code = ERR_EN_UNIF_LOC;}
  }

	glUseProgram(0);

	if(exit_code == ERR_EN_NO_ERROR)
	{
		if(glGetError() != GL_NO_ERROR)
			{exit_code = ERR_EN_USE_PROG;}
	}

	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::draw_light(unsigned int i)
{
	return ppLight[i]->draw(this->pShader[SHADER_LIGHT].prog_id);
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::set_material(int ID, int flag)
{
	int exit_code = ERR_EN_NO_ERROR;

	CModel_3D * pModel = this->get_mdl(ID);

	if(pModel != NULL)
		{pModel->set_material(flag);}
	else
		{exit_code = ERR_EN_NO_MEMORY;}

	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::set_light(unsigned int i, float ax, float ay, float az, float dx, float dy, float dz, float sx, float sy, float sz)
{
	int exit_code = ERR_EN_NO_ERROR;
	int vec3_id = 0;
	char pBuffer[100];
  this->ppLight[i]->set_light(ax, ay, az, dx, dy, dz, sx, sy, sz);

	glUseProgram(this->pShader[SHADER_MAIN].prog_id);

	if(glGetError() == GL_NO_ERROR)
	{
		// Lichteigentschaften

		sprintf(pBuffer, "light[%u].ambient", i);
		vec3_id = glGetUniformLocation(this->pShader[SHADER_MAIN].prog_id, pBuffer);

		if(glGetError() == GL_NO_ERROR)
		{
			glUniform3f(vec3_id, ax, ay, az);

			if(glGetError() == GL_NO_ERROR)
			{
				sprintf(pBuffer, "light[%u].diffuse", i);
				vec3_id = glGetUniformLocation(this->pShader[SHADER_MAIN].prog_id, pBuffer);

				if(glGetError() == GL_NO_ERROR)
				{
					glUniform3f(vec3_id, dx, dy, dz);

					if(glGetError() == GL_NO_ERROR)
					{
						sprintf(pBuffer, "light[%u].specular", i);
						vec3_id = glGetUniformLocation(this->pShader[SHADER_MAIN].prog_id, pBuffer);
				
						if(glGetError() == GL_NO_ERROR)
						{
							glUniform3f(vec3_id, sx, sy, sz);

							if(glGetError() == GL_NO_ERROR)
							{
								// entbinden

								glUseProgram(0);
		
								if(glGetError() != GL_NO_ERROR)
									{exit_code = ERR_EN_USE_PROG;}
							}
							else
								{exit_code = ERR_EN_3F;}
						}
						else
							{exit_code = ERR_EN_UNIF_LOC;}
					}
					else
						{exit_code = ERR_EN_3F;}
				}
				else
					{exit_code = ERR_EN_UNIF_LOC;}
			}
			else
				{exit_code = ERR_EN_3F;}
		}
		else
			{exit_code = ERR_EN_UNIF_LOC;}
	}
	else
		{exit_code = ERR_EN_USE_PROG;}

	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::set_texture_cube(int ID, const char * pFile, float repeat, int flag, int channels)
{
	int exit_code = ERR_EN_NO_ERROR;

	CModel_3D * pModel = this->get_mdl(ID);

	if(pModel != NULL)
		{exit_code =  pModel->set_texture_cube(pFile, repeat, this->pShader[SHADER_MAIN].prog_id, flag, channels);}
	else
		{exit_code = ERR_EN_NO_MEMORY;}

	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::switch_light(unsigned int i, unsigned short int value)
{
	int exit_code = ERR_EN_NO_ERROR;
	int id = 0;
	char pBuffer[100];
  this->ppLight[i]->switch_light(value);

	// ist das Licht an oder aus?

	glUseProgram(this->pShader[SHADER_MAIN].prog_id);

	if(glGetError() == GL_NO_ERROR)
	{
		sprintf(pBuffer, "light[%u].light_switcher", i);
  	id = glGetUniformLocation(this->pShader[SHADER_MAIN].prog_id, pBuffer);

		if(glGetError() == GL_NO_ERROR)
		{
			glUniform1i(id, value);

			if(glGetError() == GL_NO_ERROR)
			{
				// entbinden

				glUseProgram(0);

				if(glGetError() != GL_NO_ERROR)
					{exit_code = ERR_EN_USE_PROG;}
			}
			else
				{exit_code = ERR_EN_1F;}
		}
		else
			{exit_code = ERR_EN_UNIF_LOC;}
	}
	else
		{exit_code = ERR_EN_USE_PROG;}

	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::get_light_state(unsigned int i)
{
	return this->ppLight[i]->get_light_state();
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::create_pointing_light(unsigned int i, unsigned short int flag, short int geometry, float r, float g, float b, float a)
{
	int exit_code = ERR_EN_NO_ERROR;
  int id = 0;
	char pBuffer[100];
  exit_code = this->ppLight[i]->create_pointing_light(flag, geometry, r, g, b, a);

	if(exit_code == ERR_EN_NO_ERROR)
	{
		glUseProgram(this->pShader[SHADER_MAIN].prog_id);

		if(glGetError() == GL_NO_ERROR)
		{
			// Art des Lichtes

			sprintf(pBuffer, "light[%u].light_kind", i);
  		id = glGetUniformLocation(this->pShader[SHADER_MAIN].prog_id, pBuffer);

			if(glGetError() == GL_NO_ERROR)
			{
				glUniform1i(id, 2);

				if(glGetError() == GL_NO_ERROR)
				{
					glUseProgram(0);

					if(glGetError() == GL_NO_ERROR)
					{
						// Lichtschalter

						exit_code = this->switch_light(i, ON);
					}
					else
						{exit_code = ERR_EN_USE_PROG;}
				}
				else
					{exit_code = ERR_EN_1I;}
			}
			else
				{exit_code = ERR_EN_UNIF_LOC;}
		}
		else
			{exit_code = ERR_EN_USE_PROG;}
  }

	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::set_plight_dist(unsigned int i, float constant, float linear, float quadratic)
{
	int exit_code = ERR_EN_NO_ERROR;
	int id = 0;
	char pBuffer[100];
	this->ppLight[i]->set_plight_dist(constant, linear, quadratic);

	glUseProgram(this->pShader[SHADER_MAIN].prog_id);

	if(glGetError() == GL_NO_ERROR)
	{
		// Konstante

		sprintf(pBuffer, "light[%u].constant", i);
  	id = glGetUniformLocation(this->pShader[SHADER_MAIN].prog_id, pBuffer);

		if(glGetError() == GL_NO_ERROR)
		{
			glUniform1f(id, constant);

			if(glGetError() == GL_NO_ERROR)
			{
				// Linear

				sprintf(pBuffer, "light[%u].linear", i);
  			id = glGetUniformLocation(this->pShader[SHADER_MAIN].prog_id, pBuffer);

				if(glGetError() == GL_NO_ERROR)
				{
					glUniform1f(id, linear);

					if(glGetError() == GL_NO_ERROR)
					{
						// Quadrat

						sprintf(pBuffer, "light[%u].quadratic", i);
  					id = glGetUniformLocation(this->pShader[SHADER_MAIN].prog_id, pBuffer);

						if(glGetError() == GL_NO_ERROR)
						{
							glUniform1f(id, quadratic);

							if(glGetError() == GL_NO_ERROR)
							{
								// entbinden

								glUseProgram(0);
		
								if(glGetError() != GL_NO_ERROR)
									{exit_code = ERR_EN_USE_PROG;}
							}
							else
								{exit_code = ERR_EN_1F;}
						}
						else
							{exit_code = ERR_EN_UNIF_LOC;}
					}
					else
						{exit_code = ERR_EN_1F;}
				}
				else
					{exit_code = ERR_EN_UNIF_LOC;}
			}
			else
				{exit_code = ERR_EN_1F;}
		}
		else
			{exit_code = ERR_EN_UNIF_LOC;}
	}
	else
		{exit_code = ERR_EN_USE_PROG;}

	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

unsigned int CApp::get_number_lights()
{
	return this->number_lights;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::finish_mdl_creation(int ID)
{
	int exit_code = ERR_EN_NO_MEMORY;

	CModel_3D * pModel = this->get_mdl(ID);

	if(pModel != NULL)
  	{pModel->finish_creation();}
	else
		{exit_code = ERR_EN_NO_MEMORY;}

	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::load_mdl_from_obj(int ID, const char * pPath)
{
	int exit_code = ERR_EN_NO_ERROR;	

	CModel_3D * pModel = this->add_3d_mdl(ID);

	if(pModel != NULL)
		{exit_code = pModel->load_mdl_from_obj(pPath, this->pShader[SHADER_MAIN].prog_id);}
	else
		{exit_code = ERR_EN_NO_MEMORY;}
		
	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::print_error(const char * pText, int exit_code)
{
	int ret = 0;
	char pBuffer[1000];
	pBuffer[0] = '\0';

	if(exit_code != ERR_EN_NO_ERROR)
	{
		// Layout

		const SDL_MessageBoxButtonData buttons[1] = {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Beenden"};
		const SDL_MessageBoxColorScheme color_scheme =
		{{ 
			/*background*/ 				{0, 0, 0 }, 
			/*Textcolor*/					{200, 200, 200}, 
			/*Buttonborder*/			{220, 220, 220},
			/*Buttonbackground*/	{30, 30, 30},
			/*Buttonselected*/		{200, 0, 0}
		}};

		// Fehlermeldungen

		if(pText != NULL)
			{strcat(pBuffer, pText);}
	
		switch(exit_code)
		{
			case ERR_EN_OGL_DEPTHSIZE:
			{
				strcat(pBuffer, "SDL_GL_DEPTH_SIZE konnte nicht gesetzt werden!");
			}	break;
			case ERR_EN_OGL_MINORVERSION:
			{
				strcat(pBuffer, "SDL_GL_CONTEXT_MINOR_VERSION konnte nicht gesetzt werden!");
			}	break;
			case ERR_EN_OGL_MAJORVERSION:
			{
				strcat(pBuffer, "SDL_GL_CONTEXT_MAJOR_VERSION konnte nicht gesetzt werden!");
			}	break;
			case ERR_EN_OGL_CONTEXT_PROFILE_MASK:
			{
				strcat(pBuffer, "SDL_GL_CONTEXT_PROFILE_MASK konnte nicht gesetzt werden!");
			}	break;
			case ERR_EN_OGL_DOUBLEBUFFER:
			{
				strcat(pBuffer, "SDL_GL_DOUBLEBUFFER konnte nicht gesetzt werden!");
			}	break;
			case ERR_EN_OGL_ALPHA_SIZE:
			{
				strcat(pBuffer, "SDL_GL_ALPHA_SIZE konnte nicht gesetzt werden!");
			}	break;
			case ERR_EN_OGL_BLUE_SIZE:
			{
				strcat(pBuffer, "SDL_GL_BLUE_SIZE konnte nicht gesetzt werden!");
			}	break;
			case ERR_EN_OGL_GREEN_SIZE:
			{
				strcat(pBuffer, "SDL_GL_GREEN_SIZE konnte nicht gesetzt werden!");
			}	break;
			case ERR_EN_OGL_RED_SIZE:
			{
				strcat(pBuffer, "SDL_GL_RED_SIZE konnte nicht gesetzt werden!");
			}	break;
			case ERR_EN_OGL_GET_ATTR:
			{
				strcat(pBuffer, "Die Funktion SDL_GL_GetAttribute() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_WND_FAILED:
			{
				strcat(pBuffer, "Die Funktion SDL_CreateWindow() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_OGL_CONTEXT_FAILED:
			{
				strcat(pBuffer, "Die Funktion SDL_GL_CreateContext() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_OGL_GLEW:
			{
				strcat(pBuffer, "Die Funktion glewInit() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_OGL_SWAP_INTERVAL:
			{
				strcat(pBuffer, "Die Funktion SDL_GL_SetSwapInterval() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_FOPEN:
			{
				strcat(pBuffer, "Die Funktion fopen() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_ATTR:
			{
			strcat(pBuffer, "Die Funktion SDL_GL_GetAttribute() gibt nicht die gesetzten Werte zurück!");
			}	break;
			case ERR_EN_MDL_VAO:
			{
				strcat(pBuffer, "Die Funktion glGenVertexArrays() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_MDL_BIND_VAO:
			{
				strcat(pBuffer, "Die Funktion glBindVertexArray() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_MDL_VBO:
			{
				strcat(pBuffer, "Die Funktion glGenBuffers() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_MDL_BIND_VBO:
			{
				strcat(pBuffer, "Die Funktion glBindBuffer() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_MDL_VBO_DATA:
			{
				strcat(pBuffer, "Die Funktion glBufferData() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_MDL_VAO_P:
			{
				strcat(pBuffer, "Die Funktion glVertexAttribPointer() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_MDL_ENABLE_VAO:
			{
				strcat(pBuffer, "Die Funktion glEnableVertexAttribArray() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_DEPTH_FUNC:
			{
				strcat(pBuffer, "Die Funktion glDepthFunc() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_DEPTH_TEST:
			{
				strcat(pBuffer, "Die Funktion glEnable(GL_DEPTH_TEST) ist fehlgeschlagen!");
			}	break;
			case ERR_EN_USE_PROG:
			{
				strcat(pBuffer, "Die Funktion glUseProgram() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_LINK_PROG:
			{
				strcat(pBuffer, "Die Funktion glLinkProgram() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_SHADER_PROG:
			{
				strcat(pBuffer, "Die Funktion glCreateProgram() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_GEN_TEXTURE:
			{
				strcat(pBuffer, "Die Funktion glGenTextures() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_BIND_TEXTURE:
			{
				strcat(pBuffer, "Die Funktion glBindTexture() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_LOAD_IMG:
			{
				strcat(pBuffer, "Die Funktion SOIL_load_image() ist fehlgeschlagen!\n\n");
				strcat(pBuffer, SOIL_last_result());
			}	break;
			case ERR_EN_GL_TEXTURE:
			{
				strcat(pBuffer, "Die Funktion glTexImage2D() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_MIPMAP_TEXTURE:
			{
				strcat(pBuffer, "Die Funktion glGenerateMipmap() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_PARI_TEXTURE:
			{
				strcat(pBuffer, "Die Funktion glTexParameteri() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_CHECKLINK_PROG:
			{
				strcat(pBuffer, "Die Funktion glGetProgramiv() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_NO_MEM:
			{
			strcat(pBuffer, "Es konnte kein Speicher alloziiert werden!");
			}	break;
			case ERR_EN_SDL:
			{
				strcat(pBuffer, "SDL konnte nicht initialisiert werden!");
			}	break;
			case ERR_EN_STENCIL_TEST:
			{
				strcat(pBuffer, "Die Funktion glEnable(GL_STENCIL_TEST) ist fehlgeschlagen!");
			}	break;
			case ERR_EN_NO_MEMORY:
			{
				strcat(pBuffer, "Es existiert kein Speicherverweis (NULL)!");
			}	break;
			case ERR_EN_ACTIVE_TEX:
			{
				strcat(pBuffer, "Die Funktion glActiveTexture() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_UNIF_LOC:
			{
				strcat(pBuffer, "Die Funktion glGetUniformLocation() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_MAT4F:
			{
				strcat(pBuffer, "Die Funktion glUniformMatrix4fv() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_DRAW_ARR:
			{
				strcat(pBuffer, "Die Funktion glDrawArrays() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_1F:
			{
				strcat(pBuffer, "Die Funktion glUniform1f() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_2DTEX:
			{
				strcat(pBuffer, "Die Funktion glEnable(GL_TEXTURE_2D) ist fehlgeschlagen!");
			}	break;
			case ERR_EN_1I:
			{
				strcat(pBuffer, "Die Funktion glUniform1i() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_3F:
			{
				strcat(pBuffer, "Die Funktion glUniform3f() ist fehlgeschlagen!");
			}	break;
			case ERR_EN_BLEND:
			{
				strcat(pBuffer, "Die Funktion glEnable(GL_BLEND) ist fehlgeschlagen!");
			}	break;
			case ERR_EN_BLEND_FUNC:
			{
				strcat(pBuffer, "Die Funktion glBlendFunc() ist fehlgeschlagen!");
			}	break;
		};

		const SDL_MessageBoxData mb_data = 
		{
		  SDL_MESSAGEBOX_ERROR,
  	  this->pWindow,
  	  "FEHLER", /* .title */
  	  pBuffer,
  	  SDL_arraysize(buttons),
  	  buttons,
  	  &color_scheme
  	};

		int id = 0;
		SDL_ShowMessageBox(&mb_data, &id);

		switch(id)
		{
			case 0:
			{
				ret = 1;
			} break;;
		};
	}

	return ret;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::create_square(int ID, float size)
{
	int exit_code = ERR_EN_NO_ERROR;

	CModel_3D * pModel = this->add_3d_mdl(ID);

	if(pModel != NULL)
  	{exit_code = pModel->create_square(size);}
	else
		{exit_code = ERR_EN_NO_MEMORY;}

	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::set_texture_square(int ID, const char * pFile, float repeat, int flag, int channels)
{
	int exit_code = ERR_EN_NO_ERROR;

	CModel_3D * pModel = this->get_mdl(ID);

	if(pModel != NULL)
  	{exit_code = pModel->set_texture_square(pFile, repeat, this->pShader[SHADER_MAIN].prog_id, flag, channels);}
	else
		{exit_code = ERR_EN_NO_MEMORY;}

	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

unsigned int CApp::get_number_models()
{
	Elem_3D_Mdl * pCurrent = this->p3DModel_Head->pRight;
	unsigned int number = 0;

	while(pCurrent != this->p3DModel_Head)
	{
		number++;
		pCurrent = pCurrent->pRight;
	}

	return number;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CApp::delete_3d_mdl(int ID)
{
  Elem_3D_Mdl * pCurrent = this->p3DModel_Head->pRight;

	while(pCurrent->ID != ID)
		{pCurrent = pCurrent->pRight;}

	// gefunden?

	if(pCurrent->ID == ID)
	{
		// neu verlinken

		pCurrent->pLeft->pRight = pCurrent->pRight;
		pCurrent->pRight->pLeft = pCurrent->pLeft;

		// löschen / GPU nicht vergessen!

		delete pCurrent->pModel;
		delete pCurrent;
	}
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::set_mdl_active(int ID)
{
  int exit_code = ERR_EN_NO_ERROR;
	Elem_3D_Mdl * pElem = this->get_mdl_elem(ID);

	if(pElem != NULL)
		{pElem->active = 1;}
	else
		{exit_code = ERR_EN_NO_MEMORY;}

	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CApp::set_mdl_inactive(int ID)
{
  int exit_code = ERR_EN_NO_ERROR;
	Elem_3D_Mdl * pElem = this->get_mdl_elem(ID);

	if(pElem != NULL)
		{pElem->active = 0;}
	else
		{exit_code = ERR_EN_NO_MEMORY;}

	return exit_code;
}
