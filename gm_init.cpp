#include "../incl/gm_init.h"

int init(CApp * pApp)
{
  int exit_code = ERR_GM_NO_ERROR;

	#if MODE == DEBUG_MODE
		pApp->write_log("FUNKTION: init()", DB_MSG_HL);
	#endif

	#if MODE == DEBUG_MODE
		char * pBuffer = NULL;
		pBuffer = new char[200];
	#endif

  // initialisiere SDL_GL_Attribute

	exit_code = pApp->set_ogl_attr();

	if(exit_code == ERR_EN_NO_ERROR)
	{
  	// initialisiere das Fenster

  	exit_code = pApp->init_wnd("Star Wars Legacy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);

		if(exit_code == ERR_EN_NO_ERROR)
		{
			#if MODE == DEBUG_MODE
				pApp->write_log("<b>GAME:</b> SDL2 Fenster initialisiert...", DB_MSG_OK);
			#endif

    	// initialisiere Open GL

			exit_code = pApp->init_open_gl();

    	if(exit_code == ERR_EN_NO_ERROR)
			{
				#if MODE == DEBUG_MODE
					pApp->write_log("<b>GAME:</b> OpenGL initialisiert...", DB_MSG_OK);
				#endif

				// Lade Shader

				exit_code = init_shader(pApp);

				if(exit_code == ERR_GM_NO_ERROR)
				{
					#if MODE == DEBUG_MODE
						pApp->write_log("<b>GAME:</b> Shader initialisiert...", DB_MSG_OK);
					#endif

					// initialisiere depth buffer

					glEnable(GL_DEPTH_TEST);

					if(glGetError() == GL_NO_ERROR)
					{
						#if MODE == DEBUG_MODE
							pApp->write_log("<b>GAME:</b> glEnable(GL_DEPTH_TEST) OK", DB_MSG_OK);
						#endif

    	    	glDepthFunc(GL_LEQUAL);

						if(glGetError() == GL_NO_ERROR)
						{
							#if MODE == DEBUG_MODE
								pApp->write_log("<b>GAME:</b> glDepthFunc(GL_LEQUAL) OK", DB_MSG_OK);
							#endif

							// Initialisiere Anzahl von Models

							pApp->set_number_models(1);

							// Initialisiere Models

							exit_code = init_models_menu(pApp->get_model_addr());

							if(exit_code == ERR_EN_NO_ERROR)
							{
								#if MODE == DEBUG_MODE
									pApp->write_log("<b>GAME:</b> Models wurden geladen...", DB_MSG_OK);
								#endif

								// initialisiere Kamera

								pApp->init_camera();
							}
							else
							{
								#if MODE == DEBUG_MODE
									sprintf(pBuffer, "<b>GAME:</b> Models konnten nicht geladen werden... FEHLERCODE: %d --end OpenGL Error: %s --end", exit_code, glewGetErrorString(glGetError()));
									pApp->write_log(pBuffer, DB_MSG_ERR);
								#endif
							}
						}
						else
						{
							exit_code = ERR_GM_DEPTH_FUNC;

							#if MODE == DEBUG_MODE
								sprintf(pBuffer, "<b>GAME:</b> glDepthFunc(GL_LEQUAL) ist fehlgeschlagen... FEHLERCODE: %d --end OpenGL Error: %s --end", exit_code, glewGetErrorString(glGetError()));
								pApp->write_log(pBuffer, DB_MSG_ERR);
							#endif
						}
					}
					else
					{
						exit_code = ERR_GM_DEPTH_TEST;

						#if MODE == DEBUG_MODE
							sprintf(pBuffer, "<b>GAME:</b> glEnable(GL_DEPTH_TEST) ist fehlgeschlagen... FEHLERCODE: %d --end OpenGL Error: %s --end", exit_code, glewGetErrorString(glGetError()));
							pApp->write_log(pBuffer, DB_MSG_ERR);
						#endif
					}
				}
				else
				{
					#if MODE == DEBUG_MODE
						sprintf(pBuffer, "<b>GAME:</b> Shader konnten nicht initialisiert werden... FEHLERCODE: %d --end OpenGL Error: %s --end", exit_code, glewGetErrorString(glGetError()));
						pApp->write_log(pBuffer, DB_MSG_ERR);
					#endif
				}
			}
			else
			{
    	  #if MODE == DEBUG_MODE
					sprintf(pBuffer, "<b>GAME:</b> OpenGL konnte nicht initialisiert werden... FEHLERCODE: %d --end SDL Error: %s --end OpenGL Error: %s --end", exit_code, SDL_GetError(), glewGetErrorString(glGetError()));
					pApp->write_log(pBuffer, DB_MSG_ERR);
				#endif
			}
		}
		else
		{
			#if MODE == DEBUG_MODE
				sprintf(pBuffer, "<b>GAME:</b> SDL2 Fenster konnte nicht initialisiert werden... FEHLERCODE: %d --end SDL Error: %s --end", exit_code, SDL_GetError());
				pApp->write_log(pBuffer, DB_MSG_ERR);
			#endif
		}
  }
	else
	{
		#if MODE == DEBUG_MODE
			sprintf(pBuffer, "<b>GAME:</b> SDL_GL_Attribute konnten nicht gesetzt werden. FEHLERCODE: %d", exit_code);
			pApp->write_log(pBuffer, DB_MSG_ERR);
		#endif
	}

	#if MODE == DEBUG_MODE
		delete [] pBuffer;
	#endif

  return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int init_shader(CApp * pApp)
{
	int exit_code = ERR_GM_NO_ERROR;
	int shader_program_id = 0;
	int id_vert = 0;
	int id_frag = 0;

	#if MODE == DEBUG_MODE
		char * pBuffer = NULL;
		pBuffer = new char[2048];
	#endif

  // erstelle Shader Programm

	shader_program_id = glCreateProgram();

	if(shader_program_id)
	{
		#if MODE == DEBUG_MODE
			pApp->write_log("<b>GAME:</b> glCreateProgram: OK", DB_MSG_OK);
		#endif

		pApp->set_shader_program_id(shader_program_id);

		// Anzahl an Shader

  	pApp->number_shader(2);

		// Lade Shader

		id_vert = load_shader("shader/vert.glsl", GL_VERTEX_SHADER, pApp);
		pApp->set_shader_id(0, id_vert);
 		id_frag = load_shader("shader/frag.glsl", GL_FRAGMENT_SHADER, pApp);
		pApp->set_shader_id(1, id_frag);

		// an die GPU senden und auf use schalten

		glLinkProgram(shader_program_id);
						
		if(glGetError() == GL_NO_ERROR)
		{
			#if MODE == DEBUG_MODE
				pApp->write_log("<b>GAME:</b> glLinkProgram: OK", DB_MSG_OK);
			#endif

			glUseProgram(shader_program_id);

			if(glGetError() == GL_NO_ERROR)
			{
				#if MODE == DEBUG_MODE
					pApp->write_log("<b>GAME:</b> glUseProgram: OK", DB_MSG_OK);
				#endif
			}
			else
			{
				exit_code = ERR_GM_USE_PROG;

				#if MODE == DEBUG_MODE
					sprintf(pBuffer, "<b>GAME:</b> glUseProgram() failed --end OpenGL Error: %s --end", glewGetErrorString(glGetError()));
					pApp->write_log(pBuffer, DB_MSG_ERR);
				#endif
			}
		}
		else
		{
			exit_code = ERR_GM_LINK_PROG;

			#if MODE == DEBUG_MODE
				sprintf(pBuffer, "<b>GAME:</b> glLinkProgram() failed --end OpenGL Error: %s --end", glewGetErrorString(glGetError()));
				pApp->write_log(pBuffer, DB_MSG_ERR);
			#endif
		}
	}
	else
	{
		exit_code = ERR_GM_SHADER_PROG;

		#if MODE == DEBUG_MODE
			sprintf(pBuffer, "<b>GAME:</b> glCreateProgram() failed --end OpenGL Error: %s --end", glewGetErrorString(glGetError()));
			pApp->write_log(pBuffer, DB_MSG_ERR);
		#endif
	}

	#if MODE == DEBUG_MODE
		delete [] pBuffer;
	#endif

	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int init_models_menu(CModel_3D ** ppModel)
{
	int exit_code = ERR_GM_NO_ERROR;

  // Viereck
	// Pos Vertexes (0, 0, 0) = Modelcenter

	ppModel[0]->init_vertexes(36);

	ppModel[0]->add_vertex_pos(-0.4f, -0.4f, -0.4f);			// FRONT: left top
	ppModel[0]->add_vertex_pos(0.4f, -0.4f, -0.4f);				// FRONT: right top
	ppModel[0]->add_vertex_pos(-0.4f, 0.4f, -0.4f);				// FRONT: left bottom
  ppModel[0]->add_vertex_pos(0.4f, -0.4f, -0.4f);				// FRONT: right top
	ppModel[0]->add_vertex_pos(0.4f, 0.4f, -0.4f);				// FRONT: right bottom
	ppModel[0]->add_vertex_pos(-0.4f, 0.4f, -0.4f);				// FRONT: left bottom

  ppModel[0]->add_vertex_pos(-0.4f, -0.4f, -0.4f);			// LEFT:	left top
	ppModel[0]->add_vertex_pos(-0.4f, -0.4f, 0.4f);				// LEFT:	left top back
	ppModel[0]->add_vertex_pos(-0.4f, 0.4f, 0.4f);				// LEFT:	left bottom back
  ppModel[0]->add_vertex_pos(-0.4f, 0.4f, 0.4f);				// LEFT:	left bottom back
	ppModel[0]->add_vertex_pos(-0.4f, 0.4f, -0.4f);				// LEFT:	left bottom 
	ppModel[0]->add_vertex_pos(-0.4f, -0.4f, -0.4f);			// LEFT:	left top

  ppModel[0]->add_vertex_pos(-0.4f, -0.4f, -0.4f);			// TOP: 	left top
	ppModel[0]->add_vertex_pos(-0.4f, -0.4f, 0.4f);				// TOP: 	left top back
  ppModel[0]->add_vertex_pos(0.4f, -0.4f, 0.4f);				// TOP: 	right top back
  ppModel[0]->add_vertex_pos(-0.4f, -0.4f, -0.4f);			// TOP: 	left top
  ppModel[0]->add_vertex_pos(0.4f, -0.4f, -0.4f);				// TOP: 	right top
  ppModel[0]->add_vertex_pos(0.4f, -0.4f, 0.4f);				// TOP: 	right top back

  ppModel[0]->add_vertex_pos(0.4f, -0.4f, 0.4f);				// RIGHT:	right top back
  ppModel[0]->add_vertex_pos(0.4f, -0.4f, -0.4f);				// RIGHT: right top
  ppModel[0]->add_vertex_pos(0.4f, 0.4f, 0.4f);					// RIGHT: right bottom back
  ppModel[0]->add_vertex_pos(0.4f, -0.4f, -0.4f);				// RIGHT: right top
  ppModel[0]->add_vertex_pos(0.4f, 0.4f, -0.4f);				// RIGHT: right bottom
  ppModel[0]->add_vertex_pos(0.4f, 0.4f, 0.4f);					// RIGHT: right bottom back

  ppModel[0]->add_vertex_pos(0.4f, -0.4f, 0.4f);				// BACK: 	right top back
  ppModel[0]->add_vertex_pos(-0.4f, -0.4f, 0.4f);				// BACK: 	left top back
  ppModel[0]->add_vertex_pos(-0.4f, 0.4f, 0.4f);				// BACK: 	left bottom back
  ppModel[0]->add_vertex_pos(-0.4f, 0.4f, 0.4f);				// BACK: 	left bottom back
  ppModel[0]->add_vertex_pos(0.4f, 0.4f, 0.4f);					// RIGHT: right bottom back
  ppModel[0]->add_vertex_pos(0.4f, -0.4f, 0.4f);				// RIGHT: right top back

  ppModel[0]->add_vertex_pos(-0.4f, 0.4f, -0.4f);				// FLOOR:	left top
	ppModel[0]->add_vertex_pos(-0.4f, 0.4f, 0.4f);				// FLOOR:	left top back
  ppModel[0]->add_vertex_pos(0.4f, 0.4f, 0.4f);					// FLOOR:	right top back
  ppModel[0]->add_vertex_pos(-0.4f, 0.4f, -0.4f);				// FLOOR:	left top
	ppModel[0]->add_vertex_pos(0.4f, 0.4f, -0.4f);				// FLOOR:	right top
  ppModel[0]->add_vertex_pos(0.4f, 0.4f, 0.4f);					// FLOOR:	right top back

	// Colour Vertexes

	ppModel[0]->add_vertex_col(0.5f, 0.0f, 0.0f, 1.0f);			
	ppModel[0]->add_vertex_col(0.5f, 0.0f, 0.0f, 1.0f);			
	ppModel[0]->add_vertex_col(0.5f, 0.0f, 0.0f, 1.0f);
  ppModel[0]->add_vertex_col(0.5f, 0.0f, 0.0f, 1.0f);			
	ppModel[0]->add_vertex_col(0.5f, 0.0f, 0.0f, 1.0f);			
	ppModel[0]->add_vertex_col(0.5f, 0.0f, 0.0f, 1.0f);	

  ppModel[0]->add_vertex_col(0.0f, 0.5f, 0.0f, 1.0f);			
	ppModel[0]->add_vertex_col(0.0f, 0.5f, 0.0f, 1.0f);			
	ppModel[0]->add_vertex_col(0.0f, 0.5f, 0.0f, 1.0f);	
  ppModel[0]->add_vertex_col(0.0f, 0.5f, 0.0f, 1.0f);			
	ppModel[0]->add_vertex_col(0.0f, 0.5f, 0.0f, 1.0f);			
	ppModel[0]->add_vertex_col(0.0f, 0.5f, 0.0f, 1.0f);

  ppModel[0]->add_vertex_col(0.0f, 0.0f, 0.5f, 1.0f);
  ppModel[0]->add_vertex_col(0.0f, 0.0f, 0.5f, 1.0f);
  ppModel[0]->add_vertex_col(0.0f, 0.0f, 0.5f, 1.0f);	
  ppModel[0]->add_vertex_col(0.0f, 0.0f, 0.5f, 1.0f);
  ppModel[0]->add_vertex_col(0.0f, 0.0f, 0.5f, 1.0f);
  ppModel[0]->add_vertex_col(0.0f, 0.0f, 0.5f, 1.0f);

  ppModel[0]->add_vertex_col(0.5f, 0.0f, 0.5f, 1.0f);
  ppModel[0]->add_vertex_col(0.5f, 0.0f, 0.5f, 1.0f);
  ppModel[0]->add_vertex_col(0.5f, 0.0f, 0.5f, 1.0f);
  ppModel[0]->add_vertex_col(0.5f, 0.0f, 0.5f, 1.0f);
  ppModel[0]->add_vertex_col(0.5f, 0.0f, 0.5f, 1.0f);
  ppModel[0]->add_vertex_col(0.5f, 0.0f, 0.5f, 1.0f);

  ppModel[0]->add_vertex_col(0.5f, 0.5f, 0.5f, 1.0f);
  ppModel[0]->add_vertex_col(0.5f, 0.5f, 0.5f, 1.0f);
  ppModel[0]->add_vertex_col(0.5f, 0.5f, 0.5f, 1.0f);
  ppModel[0]->add_vertex_col(0.5f, 0.5f, 0.5f, 1.0f);
  ppModel[0]->add_vertex_col(0.5f, 0.5f, 0.5f, 1.0f);
  ppModel[0]->add_vertex_col(0.5f, 0.5f, 0.5f, 1.0f);

  ppModel[0]->add_vertex_col(0.0f, 0.0f, 0.0f, 1.0f);
  ppModel[0]->add_vertex_col(0.0f, 0.0f, 0.0f, 1.0f);
  ppModel[0]->add_vertex_col(0.0f, 0.0f, 0.0f, 1.0f);
  ppModel[0]->add_vertex_col(0.0f, 0.0f, 0.0f, 1.0f);
  ppModel[0]->add_vertex_col(0.0f, 0.0f, 0.0f, 1.0f);
  ppModel[0]->add_vertex_col(0.0f, 0.0f, 0.0f, 1.0f);

	// Setze Model verhalten

	ppModel[0]->set_mdl_beh(1, 1, 1);

	// Model erstellen

	exit_code = ppModel[0]->create_model();

	return exit_code;
}
