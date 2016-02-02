#include "../incl/en_3d_mdl.h"

///////////////////////////////////////////
///////////////////////////////////////////
// Konstruktor / Destruktor
///////////////////////////////////////////
///////////////////////////////////////////

CModel_3D::CModel_3D():
current_pos_ver(0),
number_vertexes(0),
id_vao(0),
current_col_ver(0),
id_texture(0)
{
	this->pPos_Vertex = NULL;
	this->pVBO = new unsigned int[NUMBER_VBO];
	this->pCol_Vertex = NULL;
	this->pTex_Pos = NULL;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

CModel_3D::~CModel_3D()
{
	if(pTex_Pos != NULL)
		{delete [] pTex_Pos;}

	if(pCol_Vertex != NULL)
		{delete [] pCol_Vertex;}

	delete [] pVBO;
	
	if(pCol_Vertex != NULL)
		{delete [] pPos_Vertex;}
}

///////////////////////////////////////////
///////////////////////////////////////////
// public methods
///////////////////////////////////////////
///////////////////////////////////////////

void CModel_3D::init_vertexes(unsigned int number)
{
  this->number_vertexes = number;
  this->pPos_Vertex = new VEC3[this->number_vertexes];
	this->pCol_Vertex = new VEC4[this->number_vertexes];
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CModel_3D::add_vertex_pos(float x, float y, float z)
{
	this->pPos_Vertex[this->current_pos_ver].x = x;
	this->pPos_Vertex[this->current_pos_ver].y = y;
	this->pPos_Vertex[this->current_pos_ver].z = z;
  this->current_pos_ver++;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CModel_3D::create_model()
{
	int exit_code = ERR_EN_NO_ERROR;

  // VAO / VBO erstellen

	glGenVertexArrays(1, &(this->id_vao));

	if(glGetError() == GL_NO_ERROR)
	{
  	glBindVertexArray(this->id_vao);
		
		if(glGetError() == GL_NO_ERROR)
		{
  		glGenBuffers(NUMBER_VBO, pVBO);

			if(glGetError() == GL_NO_ERROR)
			{
				// Positionen

				glBindBuffer(GL_ARRAY_BUFFER, this->pVBO[0]);

				if(glGetError() == GL_NO_ERROR)
				{
					glBufferData(GL_ARRAY_BUFFER, (sizeof(VEC3) * this->number_vertexes), pPos_Vertex, GL_STATIC_DRAW);

					if(glGetError() == GL_NO_ERROR)
					{
  					glVertexAttribPointer(INDEX_POS, 3, GL_FLOAT, GL_FALSE, 0, NULL);
						
						if(glGetError() == GL_NO_ERROR)
						{
	  					glEnableVertexAttribArray(INDEX_POS);
							
							if(glGetError() == GL_NO_ERROR)
							{
								// Farben

								glBindBuffer(GL_ARRAY_BUFFER, this->pVBO[1]);

								if(glGetError() == GL_NO_ERROR)
								{
									glBufferData(GL_ARRAY_BUFFER, (sizeof(VEC4) * this->number_vertexes), pCol_Vertex, GL_STATIC_DRAW);

									if(glGetError() == GL_NO_ERROR)
									{
										glVertexAttribPointer(INDEX_COLOR, 4, GL_FLOAT, GL_FALSE, 0, NULL);

										if(glGetError() == GL_NO_ERROR)
										{
	  									glEnableVertexAttribArray(INDEX_COLOR);
								
											if(glGetError() != GL_NO_ERROR)
												{exit_code = ERR_EN_MDL_ENABLE_VAO;}
											else
											{
												// Speicher bereinigen

												delete [] pCol_Vertex;
												delete [] pPos_Vertex;
												pCol_Vertex = NULL;
												pPos_Vertex = NULL;
											}
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

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CModel_3D::add_vertex_col(float r, float g, float b, float a)
{
	this->pCol_Vertex[this->current_col_ver].r = r;
	this->pCol_Vertex[this->current_col_ver].g = g;
	this->pCol_Vertex[this->current_col_ver].b = b;
  this->pCol_Vertex[this->current_col_ver].a = a;
  this->current_col_ver++;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CModel_3D::draw()
{
	glBindVertexArray(this->id_vao);
	glDrawArrays(GL_TRIANGLES, 0, this->number_vertexes);
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

glm::mat4 CModel_3D::get_mdl_pos()
{
	return this->mdl_pos;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CModel_3D::set_mdl_pos(float x, float y, float z)
{
  this->mdl_pos = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CModel_3D::create_cube(float size, uint8_t red, uint8_t green, uint8_t blue)
{
  this->init_vertexes(CUBE_VERT);

	float r = (float)((float) red / (float) 255);
	float g = (float)((float) green / (float) 255);
	float b = (float)((float) blue / (float) 255);

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

	for(int i = 0 ; i < CUBE_VERT ; i++)
		{this->add_vertex_col(r, g, b, 1.0f);}

	// Model erstellen

	this->create_model();
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CModel_3D::rotate(float rot_speed, glm::vec3 axis)
{
  this->mdl_pos = glm::rotate(this->mdl_pos, rot_speed, axis);
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CModel_3D::set_texture(const char * pFile)
{
  int exit_code = ERR_EN_NO_ERROR;
	int width = 0;
	int height = 0;
  unsigned char * pImg_data = NULL;

	// generiere Textur

	glGenTextures(1, &(this->id_texture));

  if(glGetError() == GL_NO_ERROR)
	{
		glBindTexture(GL_TEXTURE_2D, this->id_texture);

		if(glGetError() == GL_NO_ERROR)
		{
			// Lade Textur

      pImg_data = SOIL_load_image(pFile, &width, &height, 0, SOIL_LOAD_RGB);

			if(pImg_data != NULL)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pImg_data);

				if(glGetError() == GL_NO_ERROR)
				{
					glGenerateMipmap(GL_TEXTURE_2D);

					if(glGetError() == GL_NO_ERROR)
					{
						// Speicher bereinigen

						SOIL_free_image_data(pImg_data);

						// Lege Texturkoordinaten fest

						this->pTex_Pos = new Point[4];

						if(this->pTex_Pos != NULL)
						{
							pTex_Pos[0].x = 0.0f;			// bottom left
							pTex_Pos[0].y = 0.0f;
							pTex_Pos[1].x = 0.1f;			// bottom right
							pTex_Pos[1].y = 0.0f;
							pTex_Pos[2].x = 0.1f;			// top right
							pTex_Pos[2].y = 0.1f;
							pTex_Pos[3].x = 0.0f;			// top left
							pTex_Pos[3].y = 0.1f;

							glVertexAttribPointer(INDEX_TEXTURE, 2, GL_FLOAT, GL_FALSE, 0, NULL);

							if(glGetError() == GL_NO_ERROR)
							{
								glEnableVertexAttribArray(INDEX_TEXTURE); 

								if(glGetError() != GL_NO_ERROR)
									{exit_code = ERR_EN_MDL_ENABLE_VAO;} 
							}
							else
								{exit_code = ERR_EN_MDL_VAO_P;}
						}
						else
							{exit_code = ERR_EN_MEM_TEXTURE;}
					}	
					else
						{exit_code = ERR_EN_MIPMAP_TEXTURE;}
				}
				else
					{exit_code = ERR_EN_GL_TEXTURE;}
			}
			else
				{exit_code = ERR_EN_LOAD_TEXTURE;}
		}
		else
			{exit_code = ERR_EN_BIND_TEXTURE;}
	}
	else
		{exit_code = ERR_EN_GEN_TEXTURE;}

	return exit_code;
}
