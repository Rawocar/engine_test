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
id_diff_texture(0),
id_spec_texture(0),
diff_texture_set(0),
spec_texture_set(0),
draw_mode(GL_TRIANGLE_FAN),
current_norm_vec(0),
material_flag(0),
uv_set(0),
shine_intensity(0.0f),
current_uv(0)
{
	this->pPos_Vertex = NULL;
	this->pVBO = new unsigned int[NUMBER_VBO];
	this->pTex_Pos = NULL;
	this->pNorm_Vec = NULL;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

CModel_3D::~CModel_3D()
{
	if(this->pTex_Pos != NULL)
		{delete [] this->pTex_Pos;}

  if(this->pPos_Vertex != NULL)
		{delete [] this->pPos_Vertex;}

	if(this->pNorm_Vec != NULL)
		{delete [] this->pNorm_Vec;}

	delete [] pVBO;	
}

///////////////////////////////////////////
///////////////////////////////////////////
// private Methoden
///////////////////////////////////////////
///////////////////////////////////////////

int CModel_3D::send_material(int shader_program_id)
{
	int exit_code = ERR_EN_NO_ERROR;

  int vec_id = 0;
	vec_id = glGetUniformLocation(shader_program_id, "material.shine");

	if(glGetError() == GL_NO_ERROR)
	{
		glUniform1f(vec_id, this->shine_intensity);

		if(glGetError() != GL_NO_ERROR)
			{exit_code = ERR_EN_1F;}
	}
	else
		{exit_code = ERR_EN_UNIF_LOC;}

	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CModel_3D::init_vertexes(unsigned int number)
{
  this->number_vertexes = number;
  this->pPos_Vertex = new glm::vec3[this->number_vertexes];
	this->pNorm_Vec = new glm::vec3[this->number_vertexes];
	this->pTex_Pos = new glm::vec2[this->number_vertexes];
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

void CModel_3D::add_normal_vec(float x, float y, float z)
{
	this->pNorm_Vec[this->current_norm_vec].x = x;
	this->pNorm_Vec[this->current_norm_vec].y = y;
	this->pNorm_Vec[this->current_norm_vec].z = z;
  this->current_norm_vec++;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CModel_3D::add_uv(float x, float y)
{
	this->pTex_Pos[this->current_uv].x = x;
	this->pTex_Pos[this->current_uv].y = y;
  this->current_uv++;
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
  		glGenBuffers(NUMBER_VBO, this->pVBO);

			if(glGetError() == GL_NO_ERROR)
			{
				// Positionen

				glBindBuffer(GL_ARRAY_BUFFER, this->pVBO[INDEX_POS]);

				if(glGetError() == GL_NO_ERROR)
				{
					glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec3) * this->number_vertexes), this->pPos_Vertex, GL_STATIC_DRAW);

					if(glGetError() == GL_NO_ERROR)
					{
  					glVertexAttribPointer(INDEX_POS, 3, GL_FLOAT, GL_FALSE, 0, NULL);
						
						if(glGetError() == GL_NO_ERROR)
						{
	  					glEnableVertexAttribArray(INDEX_POS);
							
							if(glGetError() == GL_NO_ERROR)
							{
								// Normalvektor
								
								if(exit_code == ERR_EN_NO_ERROR)
								{
									glBindBuffer(GL_ARRAY_BUFFER, this->pVBO[INDEX_NORMAL]);
								
									if(glGetError() == GL_NO_ERROR)
									{
										glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec3) * this->number_vertexes), this->pNorm_Vec, GL_STATIC_DRAW);

										if(glGetError() == GL_NO_ERROR)
										{
											glVertexAttribPointer(INDEX_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

											if(glGetError() == GL_NO_ERROR)
											{
	  										glEnableVertexAttribArray(INDEX_NORMAL);
								
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
		
								// Speicher bereinigen
	
								delete [] this->pNorm_Vec;
								this->pNorm_Vec = NULL;
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

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CModel_3D::set_texture(const char * pFile, int shader_program_id, int flag, int channels)
{
  int exit_code = ERR_EN_NO_ERROR;
	int width = 0;
	int height = 0;
	unsigned char * pData = NULL;

	// Aktiviere material struct
		
	glUseProgram(shader_program_id);

	if(glGetError() == GL_NO_ERROR)
	{
		glBindVertexArray(this->id_vao);

		if(glGetError() == GL_NO_ERROR)
		{
			glEnable(GL_TEXTURE_2D);

			if(glGetError() == GL_NO_ERROR)
			{
				// generiere Textur

				if(flag == TEXTURE_DIFFUSE)
					{glGenTextures(1, &(this->id_diff_texture));}
				if(flag == TEXTURE_SPECULAR)
					{glGenTextures(1, &(this->id_spec_texture));}

				if(glGetError() != GL_NO_ERROR)
					{exit_code = ERR_EN_GEN_TEXTURE;}
			}
			else
				{exit_code = ERR_EN_2DTEX;}
		}
		else
			{exit_code = ERR_EN_MDL_BIND_VAO;}
  }
	else
		{exit_code = ERR_EN_USE_PROG;}

  if(exit_code == ERR_EN_NO_ERROR)
	{
		if(flag == TEXTURE_DIFFUSE)
			{glBindTexture(GL_TEXTURE_2D, this->id_diff_texture);}
		if(flag == TEXTURE_SPECULAR)
			{glBindTexture(GL_TEXTURE_2D, this->id_spec_texture);}

		if(glGetError() == GL_NO_ERROR)
		{
			// Lade Textur
			
			if(channels == GL_RGB)
      	{pData = SOIL_load_image(pFile, &width, &height, NULL, SOIL_LOAD_RGB);}
			if(channels == GL_RGBA)
      	{pData = SOIL_load_image(pFile, &width, &height, NULL, SOIL_LOAD_RGBA);}

			if(pData != NULL)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, channels, width, height, 0, channels, GL_UNSIGNED_BYTE, pData);

				if(glGetError() == GL_NO_ERROR)
				{
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

					if(glGetError() == GL_NO_ERROR)
					{
     				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

						if(glGetError() == GL_NO_ERROR)
						{
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

							if(glGetError() == GL_NO_ERROR)
							{
 								glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
								
								if(glGetError() != GL_NO_ERROR)
									{exit_code = ERR_EN_PARI_TEXTURE;}
							}
							else
								{exit_code = ERR_EN_PARI_TEXTURE;}
						}
						else
							{exit_code = ERR_EN_PARI_TEXTURE;}
					}
					else
						{exit_code = ERR_EN_PARI_TEXTURE;}
					
					if(exit_code == ERR_EN_NO_ERROR)
					{
						glGenerateMipmap(GL_TEXTURE_2D);

						if(glGetError() == GL_NO_ERROR)
						{
							// Speicher bereinigen

							SOIL_free_image_data(pData);

							if(!this->uv_set)
							{
								// Lege Texturkoordinaten fest

								glBindBuffer(GL_ARRAY_BUFFER, this->pVBO[INDEX_UV]);
				
								if(glGetError() == GL_NO_ERROR)
								{
									glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec2) * this->number_vertexes), this->pTex_Pos, GL_STATIC_DRAW);

									if(glGetError() == GL_NO_ERROR)
									{									
										glVertexAttribPointer(INDEX_UV, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	
										if(glGetError() == GL_NO_ERROR)
										{
											glEnableVertexAttribArray(INDEX_UV); 
											this->uv_set = 1;												

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

							switch(flag)
							{
								case TEXTURE_DIFFUSE:
								{
									this->diff_texture_set = 1;
									glUniform1i(glGetUniformLocation(shader_program_id, "material.diffuse"), 0);
								} break;
								case TEXTURE_SPECULAR:
								{
									this->spec_texture_set = 1;
									glUniform1i(glGetUniformLocation(shader_program_id, "material.specular"), 1);
								} break;
							};

							if(glGetError() != GL_NO_ERROR)
								{exit_code = ERR_EN_1I;}
						}	
						else
							{exit_code = ERR_EN_MIPMAP_TEXTURE;}
					}
				}
				else
					{exit_code = ERR_EN_GL_TEXTURE;}
			}
			else
				{exit_code = ERR_EN_LOAD_IMG;}
		}
		else
			{exit_code = ERR_EN_BIND_TEXTURE;}
	}

	return exit_code;
}

///////////////////////////////////////////
///////////////////////////////////////////
// public Methoden
///////////////////////////////////////////
///////////////////////////////////////////

int CModel_3D::draw(int shader_program_id)
{
	int exit_code = ERR_EN_NO_ERROR;

	glUseProgram(shader_program_id);

	if(glGetError() == GL_NO_ERROR)
	{
		glBindVertexArray(this->id_vao);

		if(glGetError() == GL_NO_ERROR)
		{
			// Textur
	
			if(this->diff_texture_set)
			{
				glActiveTexture(GL_TEXTURE0);

				if(glGetError() == GL_NO_ERROR)
				{
					glBindTexture(GL_TEXTURE_2D, this->id_diff_texture);

					if(glGetError() != GL_NO_ERROR)
						{exit_code = ERR_EN_BIND_TEXTURE;}
				}
				else
					{exit_code = ERR_EN_ACTIVE_TEX;}
			}
	
			if(exit_code == ERR_EN_NO_ERROR)
			{
				if(this->spec_texture_set)
				{
					glActiveTexture(GL_TEXTURE1);
					
					if(glGetError() == GL_NO_ERROR)
					{
						glBindTexture(GL_TEXTURE_2D, this->id_spec_texture);

						if(glGetError() != GL_NO_ERROR)
							{exit_code = ERR_EN_BIND_TEXTURE;}
					}
					else
						{exit_code = ERR_EN_ACTIVE_TEX;}
				}

				if(exit_code == ERR_EN_NO_ERROR)
				{
					// richtige Position
	
					int matrix_id = glGetUniformLocation(shader_program_id, "model");

					if(glGetError() == GL_NO_ERROR)
					{
						glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &(this->mdl[0][0]));

						if(glGetError() == GL_NO_ERROR)
						{
							// Material

							exit_code = this->send_material(shader_program_id);

							if(exit_code == ERR_EN_NO_ERROR)
							{
								// Zeichnen

								glDrawArrays(this->draw_mode, 0, this->number_vertexes);

								if(glGetError() == GL_NO_ERROR)
								{
									// unbind

									glBindVertexArray(0);

									if(glGetError() == GL_NO_ERROR)
									{		
										if(this->diff_texture_set)
										{
											glBindTexture(GL_TEXTURE_2D, 0);
											
											if(glGetError() != GL_NO_ERROR)
												{exit_code = ERR_EN_BIND_TEXTURE;}
										}
	
										if(exit_code == ERR_EN_NO_ERROR)
										{
											glUseProgram(0);

											if(glGetError() != GL_NO_ERROR)
												{exit_code = ERR_EN_USE_PROG;}
										}
									}
									else
										{exit_code = ERR_EN_MDL_BIND_VAO;}
								}
								else
									{exit_code = ERR_EN_DRAW_ARR;}
							}
						}
						else
							{exit_code = ERR_EN_MAT4F;}
					}
					else
						{exit_code = ERR_EN_UNIF_LOC;}
				}
			}
		}
		else
			{exit_code = ERR_EN_MDL_BIND_VAO;}
	}
	else
		{exit_code = ERR_EN_USE_PROG;}

	return exit_code;
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

int CModel_3D::create_cube(float size)
{
	int exit_code = ERR_EN_NO_ERROR;
  this->init_vertexes(CUBE_VERT);

	// Positionen / Normalvektoren

	this->add_vertex_pos(-size, -size, -size);		this->add_normal_vec(0.0f, 0.0f, -1.0f);		// BACK
	this->add_vertex_pos(size, -size, -size);			this->add_normal_vec(0.0f, 0.0f, -1.0f);
	this->add_vertex_pos(-size, size, -size);			this->add_normal_vec(0.0f, 0.0f, -1.0f);
  this->add_vertex_pos(size, -size, -size);			this->add_normal_vec(0.0f, 0.0f, -1.0f);
	this->add_vertex_pos(size, size, -size);			this->add_normal_vec(0.0f, 0.0f, -1.0f);
	this->add_vertex_pos(-size, size, -size);			this->add_normal_vec(0.0f, 0.0f, -1.0f);
  this->add_vertex_pos(-size, -size, -size);		this->add_normal_vec(-1.0f, 0.0f, 0.0f);		// LEFT
	this->add_vertex_pos(-size, -size, size);			this->add_normal_vec(-1.0f, 0.0f, 0.0f);
	this->add_vertex_pos(-size, size, size);			this->add_normal_vec(-1.0f, 0.0f, 0.0f);
  this->add_vertex_pos(-size, size, size);			this->add_normal_vec(-1.0f, 0.0f, 0.0f);
	this->add_vertex_pos(-size, size, -size);			this->add_normal_vec(-1.0f, 0.0f, 0.0f);
	this->add_vertex_pos(-size, -size, -size);		this->add_normal_vec(-1.0f, 0.0f, 0.0f);
  this->add_vertex_pos(-size, -size, -size);		this->add_normal_vec(0.0f, -1.0f, 0.0f);		// FLOOR
	this->add_vertex_pos(-size, -size, size);			this->add_normal_vec(0.0f, -1.0f, 0.0f);
  this->add_vertex_pos(size, -size, size);			this->add_normal_vec(0.0f, -1.0f, 0.0f);
  this->add_vertex_pos(-size, -size, -size);		this->add_normal_vec(0.0f, -1.0f, 0.0f);
  this->add_vertex_pos(size, -size, -size);			this->add_normal_vec(0.0f, -1.0f, 0.0f);
  this->add_vertex_pos(size, -size, size);			this->add_normal_vec(0.0f, -1.0f, 0.0f);
  this->add_vertex_pos(size, -size, size);			this->add_normal_vec(1.0f, 0.0f, 0.0f);			// RIGHT
  this->add_vertex_pos(size, -size, -size);			this->add_normal_vec(1.0f, 0.0f, 0.0f);
  this->add_vertex_pos(size, size, size);				this->add_normal_vec(1.0f, 0.0f, 0.0f);
  this->add_vertex_pos(size, -size, -size);			this->add_normal_vec(1.0f, 0.0f, 0.0f);
  this->add_vertex_pos(size, size, -size);			this->add_normal_vec(1.0f, 0.0f, 0.0f);
  this->add_vertex_pos(size, size, size);				this->add_normal_vec(1.0f, 0.0f, 0.0f);
  this->add_vertex_pos(size, -size, size);			this->add_normal_vec(0.0f, 0.0f, 1.0f);			// FRONT
  this->add_vertex_pos(-size, -size, size);			this->add_normal_vec(0.0f, 0.0f, 1.0f);		
  this->add_vertex_pos(-size, size, size);			this->add_normal_vec(0.0f, 0.0f, 1.0f);
  this->add_vertex_pos(-size, size, size);			this->add_normal_vec(0.0f, 0.0f, 1.0f);
  this->add_vertex_pos(size, size, size);				this->add_normal_vec(0.0f, 0.0f, 1.0f);
  this->add_vertex_pos(size, -size, size);			this->add_normal_vec(0.0f, 0.0f, 1.0f);
  this->add_vertex_pos(-size, size, -size);			this->add_normal_vec(0.0f, 1.0f, 0.0f);			// TOP 
	this->add_vertex_pos(-size, size, size);			this->add_normal_vec(0.0f, 1.0f, 0.0f);
  this->add_vertex_pos(size, size, size);				this->add_normal_vec(0.0f, 1.0f, 0.0f);
  this->add_vertex_pos(-size, size, -size);			this->add_normal_vec(0.0f, 1.0f, 0.0f);
	this->add_vertex_pos(size, size, -size);			this->add_normal_vec(0.0f, 1.0f, 0.0f);
  this->add_vertex_pos(size, size, size);				this->add_normal_vec(0.0f, 1.0f, 0.0f);

	// Zeichen Modus

	this->draw_mode = GL_TRIANGLES;
	
	// Model erstellen

	exit_code = this->create_model();

	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CModel_3D::rotate(float rot_speed, glm::vec3 axis)
{
  this->mdl = glm::rotate(this->mdl, rot_speed, axis);
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CModel_3D::set_texture_cube(const char * pFile, float repeat, int shader_program_id, int flag, int channels)
{
  int exit_code = ERR_EN_NO_ERROR;	

	if(!this->uv_set)
	{
		this->add_uv(1.0f * repeat, (1.0f - 0.0f) * repeat);		// BACK
		this->add_uv(0.0f * repeat, (1.0f - 0.0f) * repeat);
		this->add_uv(1.0f * repeat, (1.0f - 1.0f) * repeat);
		this->add_uv(0.0f * repeat, (1.0f - 0.0f) * repeat);
		this->add_uv(0.0f * repeat, (1.0f - 1.0f) * repeat);
		this->add_uv(1.0f * repeat, (1.0f - 1.0f) * repeat);

		this->add_uv(0.0f * repeat, (1.0f - 0.0f) * repeat);		// LEFT
		this->add_uv(1.0f * repeat, (1.0f - 0.0f) * repeat);
		this->add_uv(1.0f * repeat, (1.0f - 1.0f) * repeat);
		this->add_uv(1.0f * repeat, (1.0f - 1.0f) * repeat);
		this->add_uv(0.0f * repeat, (1.0f - 1.0f) * repeat);
		this->add_uv(0.0f * repeat, (1.0f - 0.0f) * repeat);

		this->add_uv(0.0f * repeat, (1.0f - 1.0f) * repeat);		// FLOOR
		this->add_uv(0.0f * repeat, (1.0f - 0.0f) * repeat);
		this->add_uv(1.0f * repeat, (1.0f - 0.0f) * repeat);
		this->add_uv(0.0f * repeat, (1.0f - 1.0f) * repeat);
		this->add_uv(1.0f * repeat, (1.0f - 1.0f) * repeat);
		this->add_uv(1.0f * repeat, (1.0f - 0.0f) * repeat);

		this->add_uv(0.0f * repeat, (1.0f - 0.0f) * repeat);		// RIGHT
		this->add_uv(1.0f * repeat, (1.0f - 0.0f) * repeat);
		this->add_uv(0.0f * repeat, (1.0f - 1.0f) * repeat);
		this->add_uv(1.0f * repeat, (1.0f - 0.0f) * repeat);
		this->add_uv(1.0f * repeat, (1.0f - 1.0f) * repeat);
		this->add_uv(0.0f * repeat, (1.0f - 1.0f) * repeat);

		this->add_uv(1.0f * repeat, (1.0f - 0.0f) * repeat);		// FRONT
		this->add_uv(0.0f * repeat, (1.0f - 0.0f) * repeat);
		this->add_uv(0.0f * repeat, (1.0f - 1.0f) * repeat);
		this->add_uv(0.0f * repeat, (1.0f - 1.0f) * repeat);
		this->add_uv(1.0f * repeat, (1.0f - 1.0f) * repeat);
		this->add_uv(1.0f * repeat, (1.0f - 0.0f) * repeat);

		this->add_uv(0.0f * repeat, (1.0f - 1.0f) * repeat);		// TOP
		this->add_uv(0.0f * repeat, (1.0f - 0.0f) * repeat);
		this->add_uv(1.0f * repeat, (1.0f - 0.0f) * repeat);
		this->add_uv(0.0f * repeat, (1.0f - 1.0f) * repeat);
		this->add_uv(1.0f * repeat, (1.0f - 1.0f) * repeat);
		this->add_uv(1.0f * repeat, (1.0f - 0.0f) * repeat);
	}

	exit_code = this->set_texture(pFile, shader_program_id, flag, channels);

	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CModel_3D::create_square(float size)
{
	int exit_code = ERR_EN_NO_ERROR;
	this->init_vertexes(SQUARE_VERT);

	// Positionen
		
	this->add_vertex_pos(-size, -size, 0.0f);				// FRONT left bottom
	this->add_vertex_pos(size, -size, 0.0f);				// FRONT right bottom
	this->add_vertex_pos(-size, size, 0.0f);				// FRONT left top
	this->add_vertex_pos(size, -size, 0.0f);				// FRONT right bottom
	this->add_vertex_pos(-size, size, 0.0f);				// FRONT left top
	this->add_vertex_pos(size, size, 0.0f);					// FRONT right top

	// Normal Vektoren

	for(int i = 0 ; i < SQUARE_VERT ; i++)
		{this->add_normal_vec(0.0f, 0.0f, 1.0f);}

	// Zeichen Modus

	this->draw_mode = GL_TRIANGLES;

	// Model erstellen

	exit_code = this->create_model();

	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CModel_3D::set_texture_square(const char * pFile, float repeat, int shader_program_id, int flag, int channels)
{
  int exit_code = ERR_EN_NO_ERROR;
				
	if(!this->uv_set)
	{	
		this->add_uv(0.0f * repeat, (1.0f - 0.0f) * repeat);		// left bottom
		this->add_uv(1.0f * repeat, (1.0f - 0.0f) * repeat);		// right bottom
		this->add_uv(0.0f * repeat, (1.0f - 1.0f) * repeat);		// left top
		this->add_uv(1.0f * repeat, (1.0f - 0.0f) * repeat);		// right bottom
		this->add_uv(0.0f * repeat, (1.0f - 1.0f) * repeat);		// left top
		this->add_uv(1.0f * repeat, (1.0f - 1.0f) * repeat);		// right top
	}

	exit_code = this->set_texture(pFile, shader_program_id, flag, channels);

	return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int CModel_3D::load_mdl_from_obj(const char * pPath, int shader_program_id)
{
	int exit_code = ERR_EN_NO_ERROR;
	FILE * pFile = NULL;
	const unsigned short int ROW = 100;
	char pRow[ROW];
	unsigned int num_v = 0;
	unsigned int num_uv = 0;
	unsigned int num_nor = 0;
	unsigned int num_faces = 0;
	glm::vec3 * pPos = NULL;
	glm::vec2 * pUV = NULL;
	glm::vec3 * pNor = NULL;
	char * pMtl = new char [ROW];
	short int flag = 0;
	unsigned int v1 = 0;
	unsigned int v2 = 0;
	unsigned int v3 = 0;
	unsigned int vt1 = 0;
	unsigned int vt2 = 0;
	unsigned int vt3 = 0;
	unsigned int vn1 = 0;
	unsigned int vn2 = 0;
	unsigned int vn3 = 0;
	char pDir[ROW];
	pDir[0] = '\0';
	char pDir_combine[ROW];
	pDir_combine[0] = '\0';

	// Ermittle einen Dateipfad, falls es einen gibt

	copy_str_offset(pPath, pDir, last_position_of_char(pPath, '/'));

	// Datei öffnen

	pFile = fopen(pPath, "r");

	if(pFile != NULL)
	{
		// Ermittle Anzahl an Vertexes / Normalvektoren / UV Koordinaten / faces

		while(fgets(pRow, ROW, pFile) != NULL)
		{
			if(pRow[0] == 'v' && pRow[1] == ' ')
				{num_v++;}
			if(pRow[0] == 'v' && pRow[1] == 't')
				{num_uv++;}
			if(pRow[0] == 'v' && pRow[1] == 'n')
				{num_nor++;}
			if(pRow[0] == 'f' && pRow[1] == ' ')
				{num_faces += 3;}
		}

		// Lege Speicher an

		if(num_v > 0)
			{pPos = new glm::vec3[num_v];}
		if(num_uv > 0)
			{pUV = new glm::vec2[num_uv];}
		if(num_nor > 0)
			{pNor = new glm::vec3[num_nor];}
		this->init_vertexes(num_faces);

		// ermittle Art der Faces / Buffer ist als letztes mit f gefüllt

		switch(count_in_str(pRow, '/'))
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
				if(pRow[first_appear(pRow, '/') + 1] == '/')
					{flag = FACES_3;}
				else
					{flag = FACES_4;}
			} break;
		};

		// bereite für erneutes durchlesen vor

		rewind(pFile);
		clearerr(pFile);
		num_v = 0;
		num_uv = 0;
		num_nor = 0;

		// Nehme Daten nun auf

		while(fgets(pRow, ROW, pFile) != NULL)
		{
			// Vertexkoordinaten

			if(pRow[0] == 'v' && pRow[1] == ' ')
			{
				sscanf(pRow, "v %f %f %f\n", &(pPos[num_v].x), &(pPos[num_v].y), &(pPos[num_v].z));
				num_v++;
			}

			// Texturkoordinaten

			if(pRow[0] == 'v' && pRow[1] == 't')
			{
				sscanf(pRow, "vt %f %f\n", &(pUV[num_uv].x), &(pUV[num_uv].y));
				num_uv++;
			}

			// Normalvektoren

			if(pRow[0] == 'v' && pRow[1] == 'n')
			{
				sscanf(pRow, "vn %f %f %f\n", &(pNor[num_nor].x), &(pNor[num_nor].y), &(pNor[num_nor].z));
				num_nor++;
			}

			// Ermittle Material Datei

			if(is_str_in_str(pRow, "mtllib"))
			{
				sscanf(pRow, "mtllib %s\n", pMtl);

				if(strlen(pDir) > 0)
				{
					strcat(pDir_combine, pDir);
					strcat(pDir_combine, pMtl);
				}
			}

			// faces

			if(pRow[0] == 'f' && pRow[1] == ' ')
			{
				switch(flag)
				{
					case FACES_1:
					{
						sscanf(pRow, "f %u %u %u\n", &v1, &v2, &v3);
						this->add_vertex_pos(pPos[v1 - 1].x, pPos[v1 - 1].y, pPos[v1 - 1].z);
						this->add_vertex_pos(pPos[v2 - 1].x, pPos[v2 - 1].y, pPos[v2 - 1].z);
						this->add_vertex_pos(pPos[v3 - 1].x, pPos[v3 - 1].y, pPos[v3 - 1].z);
					} break;
					case FACES_2:
					{
						sscanf(pRow, "f %u/%u %u/%u %u/%u\n", &v1, &vt1, &v2, &vt2, &v3, &vt3);
						this->add_vertex_pos(pPos[v1 - 1].x, pPos[v1 - 1].y, pPos[v1 - 1].z);		this->add_uv(pUV[vt1 - 1].x, 1.0f - pUV[vt1 - 1].y);
						this->add_vertex_pos(pPos[v2 - 1].x, pPos[v2 - 1].y, pPos[v2 - 1].z);		this->add_uv(pUV[vt2 - 1].x, 1.0f - pUV[vt2 - 1].y);
						this->add_vertex_pos(pPos[v3 - 1].x, pPos[v3 - 1].y, pPos[v3 - 1].z);		this->add_uv(pUV[vt3 - 1].x, 1.0f - pUV[vt3 - 1].y);
					} break;
					case FACES_3:
					{
						sscanf(pRow, "f %u//%u %u//%u %u//%u\n", &v1, &vn1, &v2, &vn2, &v3, &vn3);
						this->add_vertex_pos(pPos[v1 - 1].x, pPos[v1 - 1].y, pPos[v1 - 1].z);		this->add_normal_vec(pNor[vn1 - 1].x, pNor[vn1 - 1].y, pNor[vn1 - 1].z);
						this->add_vertex_pos(pPos[v2 - 1].x, pPos[v2 - 1].y, pPos[v2 - 1].z);   this->add_normal_vec(pNor[vn2 - 1].x, pNor[vn2 - 1].y, pNor[vn2 - 1].z);
						this->add_vertex_pos(pPos[v3 - 1].x, pPos[v3 - 1].y, pPos[v3 - 1].z);		this->add_normal_vec(pNor[vn3 - 1].x, pNor[vn3 - 1].y, pNor[vn3 - 1].z);
					} break;
					case FACES_4:
					{
						sscanf(pRow, "f %u/%u/%u %u/%u/%u %u/%u/%u\n", &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3);
						this->add_vertex_pos(pPos[v1 - 1].x, pPos[v1 - 1].y, pPos[v1 - 1].z);		this->add_uv(pUV[vt1 - 1].x, 1.0f - pUV[vt1 - 1].y);		this->add_normal_vec(pNor[vn1 - 1].x, pNor[vn1 - 1].y, pNor[vn1 - 1].z);
						this->add_vertex_pos(pPos[v2 - 1].x, pPos[v2 - 1].y, pPos[v2 - 1].z);		this->add_uv(pUV[vt2 - 1].x, 1.0f - pUV[vt2 - 1].y);		this->add_normal_vec(pNor[vn2 - 1].x, pNor[vn2 - 1].y, pNor[vn2 - 1].z);
						this->add_vertex_pos(pPos[v3 - 1].x, pPos[v3 - 1].y, pPos[v3 - 1].z);		this->add_uv(pUV[vt3 - 1].x, 1.0f - pUV[vt3 - 1].y);		this->add_normal_vec(pNor[vn3 - 1].x, pNor[vn3 - 1].y, pNor[vn3 - 1].z);
					} break;
				};
			}
		}

		// Datei schließen

		fclose(pFile);

		// Speicher bereinigen

		if(pPos != NULL)
			{delete [] pPos;}
		if(pUV != NULL)
			{delete [] pUV;}
		if(pNor != NULL)
			{delete [] pNor;}

		// Model erstellen

		this->draw_mode = GL_TRIANGLES;
		exit_code = this->create_model();

		if(exit_code == ERR_EN_NO_ERROR)
		{
			// Materialdatei öffnen
		
			pFile = fopen(pDir_combine, "r");

			if(pFile != NULL)
			{
				while(fgets(pRow, ROW, pFile) != NULL)
				{
					if(is_str_in_str(pRow, "map_Kd"))
					{
						sscanf(pRow, "map_Kd %s\n", pMtl);
						pDir_combine[0] = '\0';
						strcat(pDir_combine, pDir);
						strcat(pDir_combine, pMtl);
						exit_code = this->set_texture(pDir_combine, shader_program_id, TEXTURE_DIFFUSE, GL_RGB);
					}

					if(exit_code == ERR_EN_NO_ERROR)
					{
						if(is_str_in_str(pRow, "map_Ks"))
						{
							sscanf(pRow, "map_Ks %s\n", pMtl);
							pDir_combine[0] = '\0';
							strcat(pDir_combine, pDir);
							strcat(pDir_combine, pMtl);
							exit_code = this->set_texture(pDir_combine, shader_program_id, TEXTURE_SPECULAR, GL_RGB);
						}
					}
				}

				// Datei schließen

				fclose(pFile);
			}
			else
				{exit_code = ERR_EN_FOPEN;}
		}
	}
	else
		{exit_code = ERR_EN_FOPEN;}

	delete [] pMtl;
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

void CModel_3D::set_material(int flag)
{
  this->material_flag = flag;

	switch(this->material_flag)
	{
		case MAT_EMERALD:
		{
			this->shine_intensity = 0.6f;
		} break;
		case MAT_JADE:
		{
			this->shine_intensity = 0.1f;
		} break;
		case MAT_OBSIDIAN:
		{
			this->shine_intensity = 0.3f;
		} break;
		case MAT_PEARL:
		{
			this->shine_intensity = 0.088f;
		} break;
		case MAT_RUBY:
		{
			this->shine_intensity = 0.6f;
		} break;
		case MAT_TURQUOISE:
		{
			this->shine_intensity = 0.1f;
		} break;
		case MAT_BRASS:
		{
			this->shine_intensity = 0.21794872f;
		} break;
		case MAT_BRONZE:
		{
			this->shine_intensity = 0.2f;
		} break;
		case MAT_CHROME:
		{
			this->shine_intensity = 0.6f;
		} break;
		case MAT_COPPER:
		{
			this->shine_intensity = 0.1f;
		} break;
		case MAT_GOLD:
		{
			this->shine_intensity = 0.4f;
		} break;
		case MAT_SILVER:
		{
			this->shine_intensity = 0.4f;
		} break;
		case MAT_BLACK_PLASTIC:
		{
			this->shine_intensity = 0.25f;
		} break;
		case MAT_CYAN_PLASTIC:
		{
			this->shine_intensity = 0.25f;
		} break;
		case MAT_GREEN_PLASTIC:
		{
			this->shine_intensity = 0.25f;
		} break;
		case MAT_RED_PLASTIC:
		{
			this->shine_intensity = 0.25f;
		} break;
		case MAT_WHITE_PLASTIC:
		{
			this->shine_intensity = 0.25f;
		} break;
		case MAT_YELLOW_PLASTIC:
		{
			this->shine_intensity = 0.25f;
		} break;
		case MAT_BLACK_RUBBER:
		{
			this->shine_intensity = 0.078125f;
		} break;
		case MAT_CYAN_RUBBER:
		{
			this->shine_intensity = 0.078125f;
		} break;
		case MAT_GREEN_RUBBER:
		{
			this->shine_intensity = 0.078125f;
		} break;
		case MAT_RED_RUBBER:
		{
			this->shine_intensity = 0.078125f;
		} break;
		case MAT_BLUE_RUBBER:
		{
			this->shine_intensity = 0.078125f;
		} break;
		case MAT_WHITE_RUBBER:
		{
			this->shine_intensity = 0.078125f;
		} break;
		case MAT_YELLOW_RUBBER:
		{
			this->shine_intensity = 0.078125f;
		} break;
		case MAT_STEEL:
		{
			this->shine_intensity = 64.0f;
		} break;
	};
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CModel_3D::finish_creation()
{
	if(this->pTex_Pos != NULL)
	{
		delete [] pTex_Pos;
		this->pTex_Pos = NULL;
	}
}
