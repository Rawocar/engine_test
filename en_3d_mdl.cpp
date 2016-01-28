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
current_col_ver(0)
{
	pPos_Vertex = NULL;
	pVBO = new unsigned int[NUMBER_VBO];
	pCol_Vertex = NULL;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

CModel_3D::~CModel_3D()
{
	delete [] pCol_Vertex;
	delete [] pVBO;
	delete [] pPos_Vertex;
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

				glBindBuffer(GL_ARRAY_BUFFER, pVBO[0]);

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

								glBindBuffer(GL_ARRAY_BUFFER, pVBO[1]);

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
	glDrawArrays(GL_TRIANGLES, 0, this->number_vertexes);
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

glm::mat4 CModel_3D::get_mdl_beh()
{
	return this->mdl_beh;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void CModel_3D::set_mdl_beh(float x, float y, float z)
{
  this->mdl_beh = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}
