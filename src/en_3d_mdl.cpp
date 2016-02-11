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
id_texture(0),
texture_set(0),
draw_mode(GL_TRIANGLE_FAN),
create_flag(0)
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

	if(this->create_flag == MDL_COLOR)
		{this->pCol_Vertex = new VEC4[this->number_vertexes];}
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
								// =================================================>

								if(this->create_flag == MDL_COLOR)
								{
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
												
												delete [] pCol_Vertex;
												pCol_Vertex = NULL;
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

								// =================================================>

								// Speicher bereinigen
	
								delete [] pPos_Vertex;
								pPos_Vertex = NULL;
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

void CModel_3D::draw(int shader_program_id)
{
	glBindVertexArray(this->id_vao);

	// Textur
	
	if(this->texture_set)
		{glBindTexture(GL_TEXTURE_2D, this->id_texture);}

	// richtige Position

	int matrix_id = glGetUniformLocation(shader_program_id, "model");
	glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &(this->mdl[0][0]));

	// Zeichnen

	glDrawArrays(this->draw_mode, 0, this->number_vertexes);

	// unbind

	glBindVertexArray(0);
	if(texture_set)
		{glBindTexture(GL_TEXTURE_2D, 0);}
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

glm::mat4 CModel_3D::get_mdl_pos()
{
	return this->mdl;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CModel_3D::set_mdl_pos(float x, float y, float z)
{
  this->mdl = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CModel_3D::create_cube(float size, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha, short int flag)
{
	this->create_flag = flag;
  this->init_vertexes(CUBE_VERT);

	float r = (float)((float) red / (float) 255);
	float g = (float)((float) green / (float) 255);
	float b = (float)((float) blue / (float) 255);
	float a = (float)((float) alpha / (float) 255);

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
  this->add_vertex_pos(size, -size, size);				// FRONT right bottom
  this->add_vertex_pos(-size, -size, size);				// FRONT left bottom
  this->add_vertex_pos(-size, size, size);				// FRONT left top
  this->add_vertex_pos(-size, size, size);				// FRONT left top
  this->add_vertex_pos(size, size, size);					// FRONT right top
  this->add_vertex_pos(size, -size, size);				// FRONT right bottom
  this->add_vertex_pos(-size, size, -size);				// TOP
	this->add_vertex_pos(-size, size, size);		
  this->add_vertex_pos(size, size, size);			
  this->add_vertex_pos(-size, size, -size);		
	this->add_vertex_pos(size, size, -size);			
  this->add_vertex_pos(size, size, size);				

	// Zeichen Modus

	this->draw_mode = GL_TRIANGLES;

	// Farben

	if(this->create_flag == MDL_COLOR)
	{
		for(int i = 0 ; i < CUBE_VERT ; i++)
			{this->add_vertex_col(r, g, b, a);}
	}
	
	// Model erstellen

	this->create_model();
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CModel_3D::rotate(float rot_speed, glm::vec3 axis)
{
  this->mdl = glm::rotate(this->mdl, rot_speed, axis);
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CModel_3D::set_texture_cube(const char * pFile)
{
  int exit_code = ERR_EN_NO_ERROR;
	int width = 0;
	int height = 0;
	BMP * pBmp = NULL;

	glBindVertexArray(this->id_vao);

	// generiere Textur

	glGenTextures(1, &(this->id_texture));

  if(glGetError() == GL_NO_ERROR)
	{
		glBindTexture(GL_TEXTURE_2D, this->id_texture);

		if(glGetError() == GL_NO_ERROR)
		{
			// Lade Textur

      pBmp = load_bmp(pFile);

			if(pBmp != NULL)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pBmp);

				if(glGetError() == GL_NO_ERROR)
				{
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					
					if(glGetError() == GL_NO_ERROR)
					{
						glGenerateMipmap(GL_TEXTURE_2D);

						if(glGetError() == GL_NO_ERROR)
						{
							// Speicher bereinigen

							delete pBmp;

							// Lege Texturkoordinaten fest

							this->pTex_Pos = new Point[this->number_vertexes];

							if(this->pTex_Pos != NULL)
							{
								pTex_Pos[0].x = 0.0f;		pTex_Pos[0].y = 0.0f;		// BACK
								pTex_Pos[1].x = 0.0f; 	pTex_Pos[1].y = 0.0f;
								pTex_Pos[2].x = 0.0f;		pTex_Pos[2].y = 0.0f;
								pTex_Pos[3].x = 0.0f; 	pTex_Pos[3].y = 0.0f;
								pTex_Pos[4].x = 0.0f; 	pTex_Pos[4].y = 0.0f;
								pTex_Pos[5].x = 0.0f; 	pTex_Pos[5].y = 0.0f;

								pTex_Pos[6].x = 0.0f;		pTex_Pos[6].y = 0.0f;		// LEFT
								pTex_Pos[7].x = 0.0f; 	pTex_Pos[7].y = 0.0f;
								pTex_Pos[8].x = 0.0f;		pTex_Pos[8].y = 0.0f;
								pTex_Pos[9].x = 0.0f; 	pTex_Pos[9].y = 0.0f;
								pTex_Pos[10].x = 0.0f; 	pTex_Pos[10].y = 0.0f;
								pTex_Pos[11].x = 0.0f; 	pTex_Pos[11].y = 0.0f;

								pTex_Pos[12].x = 0.0f;	pTex_Pos[12].y = 0.0f;	// FLOOR
								pTex_Pos[13].x = 0.0f; 	pTex_Pos[13].y = 0.0f;
								pTex_Pos[14].x = 0.0f;	pTex_Pos[14].y = 0.0f;
								pTex_Pos[15].x = 0.0f; 	pTex_Pos[15].y = 0.0f;
								pTex_Pos[16].x = 0.0f; 	pTex_Pos[16].y = 0.0f;
								pTex_Pos[17].x = 0.0f; 	pTex_Pos[17].y = 0.0f;

								pTex_Pos[18].x = 0.0f;	pTex_Pos[18].y = 0.0f;	// RIGHT
								pTex_Pos[19].x = 0.0f; 	pTex_Pos[19].y = 0.0f;
								pTex_Pos[20].x = 0.0f;	pTex_Pos[20].y = 0.0f;
								pTex_Pos[21].x = 0.0f; 	pTex_Pos[21].y = 0.0f;
								pTex_Pos[22].x = 0.0f; 	pTex_Pos[22].y = 0.0f;
								pTex_Pos[23].x = 0.0f; 	pTex_Pos[23].y = 0.0f;

								pTex_Pos[24].x = 1.0f;	pTex_Pos[24].y = 0.0f;	// FRONT
								pTex_Pos[25].x = 0.0f; 	pTex_Pos[25].y = 0.0f;
								pTex_Pos[26].x = 0.0f;	pTex_Pos[26].y = 1.0f;
								pTex_Pos[27].x = 0.0f; 	pTex_Pos[27].y = 1.0f;
								pTex_Pos[28].x = 1.0f; 	pTex_Pos[28].y = 1.0f;
								pTex_Pos[29].x = 1.0f; 	pTex_Pos[29].y = 0.0f;

								pTex_Pos[30].x = 0.0f;	pTex_Pos[30].y = 0.0f;	// TOP
								pTex_Pos[31].x = 0.0f; 	pTex_Pos[31].y = 0.0f;
								pTex_Pos[32].x = 0.0f;	pTex_Pos[32].y = 0.0f;
								pTex_Pos[33].x = 0.0f; 	pTex_Pos[33].y = 0.0f;
								pTex_Pos[34].x = 0.0f; 	pTex_Pos[34].y = 0.0f;
								pTex_Pos[35].x = 0.0f; 	pTex_Pos[35].y = 0.0f;

								glVertexAttribPointer(INDEX_UV, 2, GL_FLOAT, GL_FALSE, 0, NULL);

								if(glGetError() == GL_NO_ERROR)
								{
									glEnableVertexAttribArray(INDEX_UV); 
									this->texture_set = 1;

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
						{exit_code = ERR_EN_PAR_TEXTURE;}
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

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CModel_3D::create_square(float size, uint8_t red, uint8_t green, uint8_t blue, short int flag)
{
  this->create_flag = flag;
	this->init_vertexes(SQUARE_VERT);

	float r = (float)((float) red / (float) 255);
	float g = (float)((float) green / (float) 255);
	float b = (float)((float) blue / (float) 255);

	// Positionen
		
	this->add_vertex_pos(-size, -size, size);				// FRONT left bottom
	this->add_vertex_pos(-size, size, size);				// FRONT left top
  this->add_vertex_pos(size, -size, size);				// FRONT right bottom
	this->add_vertex_pos(size, size, size);					// FRONT right top

	// Farben

	if(this->create_flag == MDL_COLOR)
	{
		for(int i = 0 ; i < SQUARE_VERT ; i++)
			{this->add_vertex_col(r, g, b, 1.0f);}
  }

	// Zeichen Modus

	this->draw_mode = GL_TRIANGLE_STRIP;

	// Model erstellen

	this->create_model();
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CModel_3D::set_texture_square(const char * pFile)
{
  int exit_code = ERR_EN_NO_ERROR;
	unsigned char * pData = NULL;
	int width = 0;
	int height = 0;

	glBindVertexArray(this->id_vao);
	glEnable(GL_TEXTURE_2D);

	// generiere Textur

	glGenTextures(1, &(this->id_texture));

  if(glGetError() == GL_NO_ERROR)
	{
		glBindTexture(GL_TEXTURE_2D, this->id_texture);

		if(glGetError() == GL_NO_ERROR)
		{
			// Lade Textur

      pData = SOIL_load_image(pFile, &width, &height, 0, SOIL_LOAD_RGB);

			if(pData != NULL)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pData);

				if(glGetError() == GL_NO_ERROR)
				{
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
     			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					
					if(glGetError() == GL_NO_ERROR)
					{
						glGenerateMipmap(GL_TEXTURE_2D);

						if(glGetError() == GL_NO_ERROR)
						{
							// Speicher bereinigen

							SOIL_free_image_data(pData);								

							// Lege Texturkoordinaten fest

							this->pTex_Pos = new Point[this->number_vertexes];

							if(this->pTex_Pos != NULL)
							{
								glBindBuffer(GL_ARRAY_BUFFER, this->pVBO[2]);
				
								if(glGetError() == GL_NO_ERROR)
								{
									pTex_Pos[0].x = 0.0f;	pTex_Pos[0].y = 0.0f;	// FRONT
									pTex_Pos[1].x = 0.0f; pTex_Pos[1].y = 1.0f;
									pTex_Pos[2].x = 1.0f;	pTex_Pos[2].y = 0.0f;
									pTex_Pos[3].x = 1.0f; pTex_Pos[3].y = 1.0f;

									glBufferData(GL_ARRAY_BUFFER, (sizeof(Point) * 4), pTex_Pos, GL_STATIC_DRAW);

									if(glGetError() == GL_NO_ERROR)
									{
										glVertexAttribPointer(INDEX_UV, 2, GL_FLOAT, GL_FALSE, 0, NULL);

										if(glGetError() == GL_NO_ERROR)
										{
											glEnableVertexAttribArray(INDEX_UV); 
											this->texture_set = 1;
											delete [] pTex_Pos;
											pTex_Pos = NULL;

											if(glGetError() != GL_NO_ERROR)
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
								{exit_code = ERR_EN_MEM_TEXTURE;}
						}	
						else
							{exit_code = ERR_EN_MIPMAP_TEXTURE;}
					}
					else
						{exit_code = ERR_EN_PAR_TEXTURE;}
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

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CModel_3D::load_mdl_from_obj(const char * pPath)
{
  int exit_code = ERR_EN_NO_ERROR;
	FILE * pFile = NULL;
	unsigned int num_vertexes = 0;
	const unsigned short int SIZE = 100;
	char pBuffer[SIZE];
	VEC3 * pVertex = NULL;
	unsigned int vertex_i = 0;
	unsigned int v1 = 0;
	unsigned int v2 = 0;
	unsigned int v3 = 0;
	unsigned int vt1 = 0;
	unsigned int vt2 = 0;
	unsigned int vt3 = 0;
	unsigned int vn1 = 0;
	unsigned int vn2 = 0;
	unsigned int vn3 = 0;
	unsigned int num_vertexes_zip = 0;
	short int flag = 0;

	// öffne Datei

	pFile = fopen(pPath, "r");

	if(pFile != NULL)
	{
		// Ermittle Anzahl an Vertexes (echt und komprimiert)

		while(fgets(pBuffer, SIZE, pFile) != NULL)
		{			
			// echt

			if(pBuffer[0] == 'f' && pBuffer[1] == ' ')
				{num_vertexes += 3;}

			// komprimiert

			if(pBuffer[0] == 'v' && pBuffer[1] == ' ')
				{num_vertexes_zip++;}
		}

		// ermittle Art der Faces / Buffer ist als letztes mit f gefüllt

		switch(count_in_str(pBuffer, '/'))
		{
			case 0:
			{
				flag = FACES_1;
			} break;
			case 3:
			{
				flag = FACES_2;
			} break;
			case 6:
			{
				if(pBuffer[first_appear(pBuffer, '/') + 1] == '/')
					{flag = FACES_3;}
				else
					{flag = FACES_4;}
			} break;
		};

		this->init_vertexes(num_vertexes);
		pVertex = new VEC3[num_vertexes_zip];

		if(pVertex != NULL)
		{
			// bereite zum erneuten Durchlaufen vor

			rewind(pFile);
			clearerr(pFile);

			while(fgets(pBuffer, SIZE, pFile) != NULL)
			{
				// VERTEXES

				if(pBuffer[0] == 'v' && pBuffer[1] == ' ')
				{
					sscanf(pBuffer, "v %f %f %f\n", &(pVertex[vertex_i].x), &(pVertex[vertex_i].y), &(pVertex[vertex_i].z));
					vertex_i++;
      	}

				// FACES

				if(pBuffer[0] == 'f' && pBuffer[1] == ' ')
				{
					// 1. Möglichkeit v1 v2 v3

					if(flag == FACES_1)
					{
						if(sscanf(pBuffer, "f %u %u %u\n", &v1, &v2, &v3) != EOF)
						{
							this->add_vertex_pos(pVertex[v1 - 1].x, pVertex[v1 - 1].y, pVertex[v1 - 1].z);
							this->add_vertex_pos(pVertex[v2 - 1].x, pVertex[v2 - 1].y, pVertex[v2 - 1].z);
							this->add_vertex_pos(pVertex[v3 - 1].x, pVertex[v3 - 1].y, pVertex[v3 - 1].z);
						}
          }

					// 2. Möglichkeit v1/vt1 v2/vt2 v3/vt3

					if(flag == FACES_2)
					{
						if(sscanf(pBuffer, "f %u/%u %u/%u %u/%u\n", &v1, &vt1, &v2, &vt2, &v3, &vt3) != EOF)
						{
							this->add_vertex_pos(pVertex[v1 - 1].x, pVertex[v1 - 1].y, pVertex[v1 - 1].z);
							this->add_vertex_pos(pVertex[v2 - 1].x, pVertex[v2 - 1].y, pVertex[v2 - 1].z);
							this->add_vertex_pos(pVertex[v3 - 1].x, pVertex[v3 - 1].y, pVertex[v3 - 1].z);
						}
          }

					// 3. Möglichkeit v1//vn1 v2//vn2 v3//vn3

					if(flag == FACES_3)
					{
						if(sscanf(pBuffer, "f %u//%u %u//%u %u//%u\n", &v1, &vn1, &v2, &vn2, &v3, &vn3) != EOF)
						{
							this->add_vertex_pos(pVertex[v1 - 1].x, pVertex[v1 - 1].y, pVertex[v1 - 1].z);
							this->add_vertex_pos(pVertex[v2 - 1].x, pVertex[v2 - 1].y, pVertex[v2 - 1].z);
							this->add_vertex_pos(pVertex[v3 - 1].x, pVertex[v3 - 1].y, pVertex[v3 - 1].z);
						}
          }

					// 4. Möglichkeit v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3

					if(flag == FACES_4)
					{
						if(sscanf(pBuffer, "f %u/%u/%u %u/%u/%u %u/%u/%u\n", &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3) != EOF)
						{
							this->add_vertex_pos(pVertex[v1 - 1].x, pVertex[v1 - 1].y, pVertex[v1 - 1].z);
							this->add_vertex_pos(pVertex[v2 - 1].x, pVertex[v2 - 1].y, pVertex[v2 - 1].z);
							this->add_vertex_pos(pVertex[v3 - 1].x, pVertex[v3 - 1].y, pVertex[v3 - 1].z);
						}
					}
				}
			}

			// alle Daten geladen, schließe Datei

			fclose(pFile);

			// füge Farbe hinzu

			for(unsigned int i = 0 ; i < this->number_vertexes ; i++)
				{this->add_vertex_col(0.5f, 0.5f, 0.7f, 1.0f);}

			// erstelle Model

			this->draw_mode = GL_TRIANGLES;
			exit_code = this->create_model();	

			// Speicher bereinigen

			delete [] pVertex;
		}
		else
			{exit_code = ERR_EN_NO_MEM;}
	}
	else
		{exit_code = ERR_EN_FOPEN;}

  return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

unsigned int CModel_3D::get_num_vertexes()
{
	return this->number_vertexes;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CModel_3D::create_circle(float radius, float num_v, uint8_t red, uint8_t green, uint8_t blue)
{
	float r = (float)((float) red / (float) 255);
	float g = (float)((float) green / (float) 255);
	float b = (float)((float) blue / (float) 255);
	float current_angle = 0.0f;
	float angle_step = 360.0f / num_v;
	
	this->init_vertexes(num_v + 2);					// Mittelpunkt und Abschluss müssen dazugezählt werden
	this->add_vertex_pos(0.0f, 0.0f, 0.0f);	// Mittelpunkt

	for(int i = 0 ; i < num_v ; i++)
  {
		this->add_vertex_pos(radius * cosf((current_angle * PI) / 180), radius * sinf((current_angle * PI) / 180), 0.0f);
		current_angle += angle_step;
	}

	this->add_vertex_pos(radius * cosf((0.0f * PI) / 180), radius * sinf((0.0f * PI) / 180), 0.0f); // Abschluss

	// Farben

	for(int i = 0 ; i < (num_v + 2) ; i++)
		{this->add_vertex_col(r, g, b, 1.0f);}

	// Zeichen Modus

	this->draw_mode = GL_TRIANGLE_FAN;

	// Model erstellen

	this->create_model();
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CModel_3D::create_sphere(float radius, float num_v, uint8_t red, uint8_t green, uint8_t blue, short int flag)
{
	this->create_flag = flag;

	// num_v muss gerade sein

	if((int)num_v < 8)
		{num_v = 8.0f;}
	if(((int)num_v % 2) != 0)
		{num_v += 1;}
	if((((int)num_v / 2) % 2) != 0)
		{num_v += 2;}

  float r = (float)((float) red / (float) 255);
	float g = (float)((float) green / (float) 255);
	float b = (float)((float) blue / (float) 255);
	int shells_half = forced_into((((int)num_v - 2) / 2), 2);		// Schalen pro Kreishälfte auf z-Ebene
	float angle_step = 360.0f / num_v;
	float current_angle = 0.0f;
	float current_angle_z = 0.0f;
	VEC3 ** Sphere_Points = new VEC3 * [shells_half + 1];

	for(int i = 0 ; i < (shells_half + 1) ; i++)
		{Sphere_Points[i] = new VEC3[(int) num_v];}

	float z = 0.0f;
	float y = 0.0f; 

	////////////////////////
	// Modelpunkte erstellen
	////////////////////////

	// erstelle einen Halbkreis
	// beginne mit größtem Radius

	for(int i = 0 ; i < (int)num_v ; i++)
	{
		Sphere_Points[0][i].x = radius * cosf((current_angle * PI) / 180);
		Sphere_Points[0][i].y = radius * sinf((current_angle * PI) / 180);
		Sphere_Points[0][i].z = z;

		current_angle += angle_step;
	}
	
	// nun alle nach außen laufenden Schalen	

	for(int i = 1 ; i < shells_half ; i++)
	{
		current_angle = 0.0f;
		current_angle_z += angle_step;
		y = radius * cosf((current_angle_z * PI) / 180);
		z = radius * sinf((current_angle_z * PI) / 180); 

		// berechne Schale

		for(int h = 0 ; h < (int)num_v ; h++)
		{
			Sphere_Points[i][h].x = y * cosf((current_angle * PI) / 180);
			Sphere_Points[i][h].y = y * sinf((current_angle * PI) / 180);
			Sphere_Points[i][h].z = z;

			current_angle += angle_step;
		}
	}

	// ganz außen

	for(int i = 0 ; i < (int)num_v ; i++)
	{
		Sphere_Points[shells_half][i].x = 0.0f;
		Sphere_Points[shells_half][i].y = 0.0f;
		Sphere_Points[shells_half][i].z = radius;
	}

	////////////////////////
	// Modelmesh erstellen
	////////////////////////

	this->init_vertexes((int)num_v * 6 * shells_half * 2);

	// Vorderseite

	for(int i = 0 ; i < shells_half ; i++)
	{
		for(int h = 0 ; h < (int)num_v ; h++)
		{
			// Verbinde ein Viereck
			// links oben
			// links unten
			// rechts unten
			// rechts unten
			// links oben
			// rechts oben
			
			this->add_vertex_pos(Sphere_Points[i][h % (int)num_v].x, Sphere_Points[i][h % (int)num_v].y, Sphere_Points[i][h % (int)num_v].z);
			this->add_vertex_pos(Sphere_Points[i + 1][h % (int)num_v].x, Sphere_Points[i + 1][h % (int)num_v].y, Sphere_Points[i + 1][h % (int)num_v].z);
			this->add_vertex_pos(Sphere_Points[i + 1][(h + 1) % (int)num_v].x, Sphere_Points[i + 1][(h + 1) % (int)num_v].y, Sphere_Points[i + 1][(h + 1) % (int)num_v].z);	
			this->add_vertex_pos(Sphere_Points[i + 1][(h + 1) % (int)num_v].x, Sphere_Points[i + 1][(h + 1) % (int)num_v].y, Sphere_Points[i + 1][(h + 1) % (int)num_v].z);
			this->add_vertex_pos(Sphere_Points[i][h % (int)num_v].x, Sphere_Points[i][h % (int)num_v].y, Sphere_Points[i][h % (int)num_v].z);												
			this->add_vertex_pos(Sphere_Points[i][(h + 1) % (int)num_v].x, Sphere_Points[i][(h + 1) % (int)num_v].y, Sphere_Points[i][(h + 1) % (int)num_v].z);			

			// Farben hinzufügen

			this->add_vertex_col(r, g, b, 1.0f);
			this->add_vertex_col(r, g, b, 1.0f);
			this->add_vertex_col(r, g, b, 1.0f);
			this->add_vertex_col(r, g, b, 1.0f);
			this->add_vertex_col(r, g, b, 1.0f);
			this->add_vertex_col(r, g, b, 1.0f);	
		}
	}

	// Rückseite

	for(int i = 0 ; i < shells_half ; i++)
	{
		for(int h = 0 ; h < (int)num_v ; h++)
		{
			// Verbinde ein Viereck
			// links oben
			// links unten
			// rechts unten
			// rechts unten
			// links oben
			// rechts oben

			this->add_vertex_pos(Sphere_Points[i][h % (int)num_v].x, Sphere_Points[i][h % (int)num_v].y, -Sphere_Points[i][h % (int)num_v].z);
			this->add_vertex_pos(Sphere_Points[i + 1][h % (int)num_v].x, Sphere_Points[i + 1][h % (int)num_v].y, -Sphere_Points[i + 1][h % (int)num_v].z);
			this->add_vertex_pos(Sphere_Points[i + 1][(h + 1) % (int)num_v].x, Sphere_Points[i + 1][(h + 1) % (int)num_v].y, -Sphere_Points[i + 1][(h + 1) % (int)num_v].z);	
			this->add_vertex_pos(Sphere_Points[i + 1][(h + 1) % (int)num_v].x, Sphere_Points[i + 1][(h + 1) % (int)num_v].y, -Sphere_Points[i + 1][(h + 1) % (int)num_v].z);
			this->add_vertex_pos(Sphere_Points[i][h % (int)num_v].x, Sphere_Points[i][h % (int)num_v].y, -Sphere_Points[i][h % (int)num_v].z);												
			this->add_vertex_pos(Sphere_Points[i][(h + 1) % (int)num_v].x, Sphere_Points[i][(h + 1) % (int)num_v].y, -Sphere_Points[i][(h + 1) % (int)num_v].z);			

			// Farben hinzufügen
			
			if(this->create_flag == MDL_COLOR)
			{
				this->add_vertex_col(r, g, b, 1.0f);
				this->add_vertex_col(r, g, b, 1.0f);
				this->add_vertex_col(r, g, b, 1.0f);
				this->add_vertex_col(r, g, b, 1.0f);
				this->add_vertex_col(r, g, b, 1.0f);
				this->add_vertex_col(r, g, b, 1.0f);			
      }
		}
	}

	// Speicher freigeben

	for(int i = 0 ; i < (shells_half + 1) ; i++)
		{delete [] Sphere_Points[i];}
	
	delete [] Sphere_Points;

	// Zeichen Modus

	this->draw_mode = GL_TRIANGLES;

	// Model erstellen

	this->create_model();
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CModel_3D::create_pyramid(float size, float to_peak, uint8_t red, uint8_t green, uint8_t blue, short int flag)
{
	this->create_flag = flag;

	float r = (float)((float) red / (float) 255);
	float g = (float)((float) green / (float) 255);
	float b = (float)((float) blue / (float) 255);

	this->init_vertexes(PYRAMID_VERT);
	this->add_vertex_pos(-size, -(to_peak / 2), size);		// vordere Seite
	this->add_vertex_pos(size, -(to_peak / 2), size);
	this->add_vertex_pos(0.0f, (to_peak / 2), 0.0f);
	this->add_vertex_pos(-size, -(to_peak / 2), -size);		// hintere Seite
	this->add_vertex_pos(size, -(to_peak / 2), -size);
	this->add_vertex_pos(0.0f, (to_peak / 2), 0.0f);
	this->add_vertex_pos(-size, -(to_peak / 2), size);		// linke Seite
	this->add_vertex_pos(-size, -(to_peak / 2), -size);
	this->add_vertex_pos(0.0f, (to_peak / 2), 0.0f);
	this->add_vertex_pos(size, -(to_peak / 2), size);     // rechte Seite
	this->add_vertex_pos(size, -(to_peak / 2), -size);
	this->add_vertex_pos(0.0f, (to_peak / 2), 0.0f);

	if(this->create_flag == MDL_COLOR)
	{
		for(int i = 0 ; i < PYRAMID_VERT ; i++)
			{this->add_vertex_col(r, g, b, 1.0f);}
  }

	// Zeichen Modus

	this->draw_mode = GL_TRIANGLES;

	// Model erstellen

	this->create_model();
}  

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CModel_3D::create_cone(float radius, float to_peak, float num_v, uint8_t red, uint8_t green, uint8_t blue, short int flag)
{
	this->create_flag = flag;
	float r = (float)((float) red / (float) 255);
	float g = (float)((float) green / (float) 255);
	float b = (float)((float) blue / (float) 255);
	float angle_step = 360.0f / num_v;
	float current_angle = 0.0f;
	VEC3 * pVertex = new VEC3[(int)num_v];				// Kreisfläche / ein zusätzlicher für den Abschluss

	for(int i = 0 ; i < num_v ; i++)
	{
		pVertex[i].x = radius * cosf((current_angle * PI) / 180);
		pVertex[i].z = radius * sinf((current_angle * PI) / 180);
		pVertex[i].y = -(to_peak / 2);
		current_angle += angle_step;
	}

	// Model erstellen

	this->init_vertexes((3 * (int)num_v) * 2);

	// Grundfläche

  for(int i = 0 ; i < (int)num_v ; i++)
	{
		this->add_vertex_pos(pVertex[i].x, pVertex[i].y, pVertex[i].z);
		this->add_vertex_pos(pVertex[(i + 1) % (int)num_v].x, pVertex[(i + 1) % (int)num_v].y, pVertex[(i + 1) % (int)num_v].z);
		this->add_vertex_pos(0.0f, -(to_peak / 2), 0.0f);
		
		if(this->create_flag == MDL_COLOR)
		{
			this->add_vertex_col(r, g, b, 1.0f);
			this->add_vertex_col(r, g, b, 1.0f);
			this->add_vertex_col(r, g, b, 1.0f);
    }
	}

	// Spitze

	for(int i = 0 ; i < (int)num_v ; i++)
	{
		this->add_vertex_pos(pVertex[i].x, pVertex[i].y, pVertex[i].z);
		this->add_vertex_pos(pVertex[(i + 1) % (int)num_v].x, pVertex[(i + 1) % (int)num_v].y, pVertex[(i + 1) % (int)num_v].z);
		this->add_vertex_pos(0.0f, (to_peak / 2), 0.0f);

		if(this->create_flag == MDL_COLOR)
		{
			this->add_vertex_col(r, g, b, 1.0f);
			this->add_vertex_col(r, g, b, 1.0f);
			this->add_vertex_col(r, g, b, 1.0f);
    }
	}

	// Zeichen Modus

	this->draw_mode = GL_TRIANGLES;

	// Model erstellen

	this->create_model();

	delete [] pVertex;
}
