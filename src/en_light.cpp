#include "../incl/en_light.h"

///////////////////////////////////////////
///////////////////////////////////////////
// Konstruktor / Destruktor
///////////////////////////////////////////
///////////////////////////////////////////

CLight::CLight():
vflag(0),
draw_mode(GL_TRIANGLES),
current_pos_ver(0),
number_vertexes(0),
id_vao(0)
{
	this->pPos_Vertex = NULL;
	this->pCol_Vertex = NULL;
	this->pVBO = NULL;
}

CLight::~CLight()
{}

///////////////////////////////////////////
///////////////////////////////////////////
//  private Methoden
///////////////////////////////////////////
///////////////////////////////////////////

int CLight::create_cube(float size)
{
	int exit_code = ERR_EN_NO_ERROR;
	this->number_vertexes = LCUBE_VERT;
  this->pPos_Vertex = new glm::vec3[this->number_vertexes];
	this->pCol_Vertex = new glm::vec4[this->number_vertexes];
	this->pVBO = new unsigned int[LNUMBER_VBO];

	// Positionen

	this->add_vertex_pos(-size, -size, -size);			// BACK
	this->add_vertex_pos(size, -size, -size);	
	this->add_vertex_pos(-size, size, -size);		
  this->add_vertex_pos(size, -size, -size);		
	this->add_vertex_pos(size, size, -size);			
	this->add_vertex_pos(-size, size, -size);				
  this->add_vertex_pos(-size, -size, -size);			// LEFT
	this->add_vertex_pos(-size, -size, size);		
	this->add_vertex_pos(-size, size, size);	
  this->add_vertex_pos(-size, size, size);	
	this->add_vertex_pos(-size, size, -size);	
	this->add_vertex_pos(-size, -size, -size);	
  this->add_vertex_pos(-size, -size, -size);			// FLOOR
	this->add_vertex_pos(-size, -size, size);			
  this->add_vertex_pos(size, -size, size);		
  this->add_vertex_pos(-size, -size, -size);		
  this->add_vertex_pos(size, -size, -size);		
  this->add_vertex_pos(size, -size, size);		
  this->add_vertex_pos(size, -size, size);				// RIGHT
  this->add_vertex_pos(size, -size, -size);
  this->add_vertex_pos(size, size, size);				
  this->add_vertex_pos(size, -size, -size);			
  this->add_vertex_pos(size, size, -size);		
  this->add_vertex_pos(size, size, size);				
  this->add_vertex_pos(size, -size, size);				// FRONT
  this->add_vertex_pos(-size, -size, size);				
  this->add_vertex_pos(-size, size, size);	
  this->add_vertex_pos(-size, size, size);	
  this->add_vertex_pos(size, size, size);				
  this->add_vertex_pos(size, -size, size);			
  this->add_vertex_pos(-size, size, -size);				// TOP 
	this->add_vertex_pos(-size, size, size);		
  this->add_vertex_pos(size, size, size);			
  this->add_vertex_pos(-size, size, -size);		
	this->add_vertex_pos(size, size, -size);			
  this->add_vertex_pos(size, size, size);		

	// Farben

	for(int i = 0 ; i < LCUBE_VERT ; i++)
	{
		this->pCol_Vertex[i].r = this->lcolor.r;
		this->pCol_Vertex[i].g = this->lcolor.g;
		this->pCol_Vertex[i].b = this->lcolor.b;
		this->pCol_Vertex[i].a = this->lcolor.a;
	}

	// erstelle Licht

	exit_code = this->create();

	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CLight::add_vertex_pos(float x, float y, float z)
{
	this->pPos_Vertex[this->current_pos_ver].x = x;
	this->pPos_Vertex[this->current_pos_ver].y = y;
	this->pPos_Vertex[this->current_pos_ver].z = z;
  this->current_pos_ver++;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CLight::create()
{
	int exit_code = ERR_EN_NO_ERROR;

  // VAO / VBO erstellen

	glGenVertexArrays(1, &(this->id_vao));

	if(glGetError() == GL_NO_ERROR)
	{
  	glBindVertexArray(this->id_vao);
		
		if(glGetError() == GL_NO_ERROR)
		{
  		glGenBuffers(LNUMBER_VBO, this->pVBO);

			if(glGetError() == GL_NO_ERROR)
			{
				// Positionen

				glBindBuffer(GL_ARRAY_BUFFER, this->pVBO[0]);

				if(glGetError() == GL_NO_ERROR)
				{
					glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec3) * this->number_vertexes), this->pPos_Vertex, GL_STATIC_DRAW);

					if(glGetError() == GL_NO_ERROR)
					{
  					glVertexAttribPointer(LINDEX_POS, 3, GL_FLOAT, GL_FALSE, 0, NULL);
						
						if(glGetError() == GL_NO_ERROR)
						{
	  					glEnableVertexAttribArray(LINDEX_POS);
							
							if(glGetError() == GL_NO_ERROR)
							{
								// Farben
								// =================================================>

								glBindBuffer(GL_ARRAY_BUFFER, this->pVBO[1]);
								
								if(glGetError() == GL_NO_ERROR)
								{
									glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec4) * this->number_vertexes), this->pCol_Vertex, GL_STATIC_DRAW);

									if(glGetError() == GL_NO_ERROR)
									{
										glVertexAttribPointer(LINDEX_COLOR, 4, GL_FLOAT, GL_FALSE, 0, NULL);

										if(glGetError() == GL_NO_ERROR)
										{
  										glEnableVertexAttribArray(LINDEX_COLOR);
								
											if(glGetError() != GL_NO_ERROR)
												{exit_code = ERR_EN_MDL_ENABLE_VAO;}
												
											delete [] this->pCol_Vertex;
											this->pCol_Vertex = NULL;
										}
										else
											{exit_code = ERR_EN_MDL_VAO_P;}
									}
									else
										{exit_code = ERR_EN_MDL_VBO_DATA;}
								}
								else
									{exit_code = ERR_EN_MDL_BIND_VBO;}

								// =================================================>

								// Speicher bereinigen
	
								delete [] this->pPos_Vertex;
								this->pPos_Vertex = NULL;
							}
							else
								{exit_code = ERR_EN_MDL_ENABLE_VAO;}
						}
						else
							{exit_code = ERR_EN_MDL_VAO_P;}
					}
					else
						{exit_code = ERR_EN_MDL_VBO_DATA;}
				}
				else
					{exit_code = ERR_EN_MDL_BIND_VBO;}
			}
			else
				{exit_code = ERR_EN_MDL_VBO;}
		}
		else
			{exit_code = ERR_EN_MDL_BIND_VAO;}
	}
	else
		{exit_code = ERR_EN_MDL_VAO;}

	return exit_code;
}

///////////////////////////////////////////
///////////////////////////////////////////
//  public Methoden
///////////////////////////////////////////
///////////////////////////////////////////

int CLight::create_directional_light(unsigned short int flag, short int geometry, float r, float g, float b, float a)
{
  int exit_code = ERR_EN_NO_ERROR;
	this->lcolor = glm::vec4(r, g, b, a);
	this->light.light_kind = 1;

	switch(flag)
	{
		case LIGHT_VISIBLE:	
		{
			this->vflag = flag;

      switch(geometry)
			{
				case LIGHT_CUBE:
				{
					exit_code = this->create_cube(0.5);
				} break;
			};
		} break;
		case LIGHT_INVISIBLE:
		{
			this->vflag = flag;
		} break;
	};

  return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CLight::set_light_pos(float x, float y, float z)
{
  this->mlight = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CLight::draw(int shader_program_id)
{
	int exit_code = ERR_EN_NO_ERROR;

	if(this->vflag == LIGHT_VISIBLE)
	{
  	glUseProgram(shader_program_id);

		if(glGetError() == GL_NO_ERROR)
		{
			glBindVertexArray(this->id_vao);

			if(glGetError() == GL_NO_ERROR)
			{
				// richtige Position

				int matrix_id = glGetUniformLocation(shader_program_id, "mlight");

				if(glGetError() == GL_NO_ERROR)
				{
					glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &(this->mlight[0][0]));
					
					if(glGetError() == GL_NO_ERROR)
					{
						// Zeichnen

						glDrawArrays(this->draw_mode, 0, this->number_vertexes);

						if(glGetError() == GL_NO_ERROR)
						{
							// unbind

							glBindVertexArray(0);

							if(glGetError() == GL_NO_ERROR)
							{
								glUseProgram(0);

								if(glGetError() != GL_NO_ERROR)
									{exit_code = ERR_EN_USE_PROG;}
							}
							else
								{exit_code = ERR_EN_MDL_BIND_VAO;}
						}
						else
							{exit_code = ERR_EN_DRAW_ARR;}
					}
					else
						{exit_code = ERR_EN_MAT4F;}
				}
				else
					{exit_code = ERR_EN_UNIF_LOC;}
			}
			else
				{exit_code = ERR_EN_MDL_BIND_VAO;}
		}
		else
			{exit_code = ERR_EN_USE_PROG;}
	}

  return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

glm::vec4 CLight::get_color()
{
  return lcolor;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

glm::vec3 CLight::get_light_pos()
{
  return glm::vec3(this->mlight[3]);
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CLight::set_light(float ax, float ay, float az, float dx, float dy, float dz, float sx, float sy, float sz)
{
	light.ambient.x = ax; light.ambient.y = ay; light.ambient.z = az;
	light.diffuse.x = dx; light.diffuse.y = dy; light.diffuse.z = dz;
	light.specular.x = sx; light.specular.y = sy; light.specular.z = sz;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

glm::vec3 CLight::get_ambient_light()
{
  return this->light.ambient;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

glm::vec3 CLight::get_diffuse_light()
{
  return this->light.diffuse;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

glm::vec3 CLight::get_specular_light()
{
  return this->light.specular;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CLight::set_direction(float x, float y, float z)
{
	this->light.direction.x = x;
	this->light.direction.y = y;
	this->light.direction.z = z;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CLight::switch_light(unsigned short int value)
{
	this->light.light_switcher = value;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CLight::get_light_state()
{
  return this->light.light_switcher;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CLight::create_pointing_light(unsigned short int flag, short int geometry, float r, float g, float b, float a)
{
  int exit_code = ERR_EN_NO_ERROR;
	this->lcolor = glm::vec4(r, g, b, a);
	this->light.light_kind = 2;

	switch(flag)
	{
		case LIGHT_VISIBLE:	
		{
			this->vflag = flag;

      switch(geometry)
			{
				case LIGHT_CUBE:
				{
					exit_code = this->create_cube(0.5);
				} break;
			};
		} break;
		case LIGHT_INVISIBLE:
		{
			this->vflag = flag;
		} break;
	};

  return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CLight::set_plight_dist(float constant, float linear, float quadratic)
{
	this->light.constant = constant;
	this->light.linear = linear;
	this->light.quadratic = quadratic;
}
