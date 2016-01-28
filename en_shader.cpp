#include "../incl/en_shader.h"

int load_shader(const char * pFile, GLenum shader_spec, CApp * pApp)
{
  int id = 0;
  int len = len_file(pFile);
  char * pSrc = new char[len + 1];
	const char * pCSrc = (const char*)pSrc;
  int exit_code = ERR_EN_NO_ERROR;

	#if EMODE == EDEBUG_MODE
		char * pBuffer = NULL;
		pBuffer = new char[2048];
	#endif

  // lese die GLSL Datei aus

  exit_code = read_file(pFile, pSrc, len);

	if(exit_code == ERR_EN_NO_ERROR)
	{
		#if EMODE == EDEBUG_MODE
			sprintf(pBuffer, "<b>ENGINE:</b> read_file: \"%s\" OK", pFile);
			pApp->write_log(pBuffer, DB_MSG_OK);
		#endif

		// erstelle Shader handle

		id = glCreateShader(shader_spec);

		if(id)
		{
			#if EMODE == EDEBUG_MODE
				pApp->write_log("<b>ENGINE:</b> glCreateShader: OK", DB_MSG_OK);
			#endif

			// sende den Shadercode an OpenGL mittels der ID

  		glShaderSource(id, 1, &pCSrc, &len);

			if(glGetError() == GL_NO_ERROR)
			{
				#if EMODE == EDEBUG_MODE
					pApp->write_log("<b>ENGINE:</b> glShaderSource: OK", DB_MSG_OK);
				#endif

				// kompiliere den Code

				glCompileShader(id);

				if(glGetError() == GL_NO_ERROR)
				{
					#if EMODE == EDEBUG_MODE
						pApp->write_log("<b>ENGINE:</b> glCompileShader: OK", DB_MSG_OK);
					#endif

					glAttachShader(pApp->get_shader_program_id(), id);

					if(glGetError() == GL_NO_ERROR)
					{
						#if EMODE == EDEBUG_MODE
							pApp->write_log("<b>ENGINE:</b> glAttachShader: OK", DB_MSG_OK);
						#endif
					}
					else
					{
						#if EMODE == EDEBUG_MODE
							sprintf(pBuffer, "<b>ENGINE:</b> glAttachShader: OpenGL Error: %s --end", glewGetErrorString(glGetError()));
							pApp->write_log(pBuffer, DB_MSG_ERR);
						#endif
					}
				}
				else
				{
					#if EMODE == EDEBUG_MODE
						sprintf(pBuffer, "<b>ENGINE:</b> glCompileShader: OpenGL Error: %s --end", glewGetErrorString(glGetError()));
						pApp->write_log(pBuffer, DB_MSG_ERR);
					#endif
				}
      }
			else
			{
				#if EMODE == EDEBUG_MODE
					sprintf(pBuffer, "<b>ENGINE:</b> glShaderSource: OpenGL Error: %s --end", glewGetErrorString(glGetError()));
					pApp->write_log(pBuffer, DB_MSG_ERR);
				#endif
			}
    }
		else
		{
			#if EMODE == EDEBUG_MODE
				sprintf(pBuffer, "<b>ENGINE:</b> glCreateShader: OpenGL Error: %s --end", glewGetErrorString(glGetError()));
				pApp->write_log(pBuffer, DB_MSG_ERR);
			#endif
		}
	}
	else
	{
		#if EMODE == EDEBUG_MODE
			sprintf(pBuffer, "<b>ENGINE:</b> load_shader: FEHLERCODE: %d --end", exit_code);
			pApp->write_log(pBuffer, DB_MSG_ERR);
		#endif
	}

	// zerlegen

	#if EMODE == EDEBUG_MODE
		delete [] pBuffer;
	#endif

	delete [] pSrc;

	return id;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void unload_shader(CApp * pApp)
{
	// shader entladen

  for(unsigned short int i = 0 ; i < (pApp->get_shader_number()) ; i++)
		{glDetachShader(pApp->get_shader_program_id(), pApp->get_shader_id(i));}

	// Programm löschen

	glDeleteProgram(pApp->get_shader_program_id());

	// shader löschen

	for(unsigned short int i = 0 ; i < (pApp->get_shader_number()) ; i++)
    {glDeleteShader(pApp->get_shader_id(i));}
}
