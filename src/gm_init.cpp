#include "../incl/gm_init.h"

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int init_models_menu(CApp * pApp)
{
	int exit_code = ERR_GM_NO_ERROR;
	CModel_3D ** ppModel = pApp->get_model_addr();
	//BMP * pBmp = NULL;

	#if MODE == DEBUG_MODE
		pApp->write_log("init_models_menu()", DB_MSG_HL);
	#endif

  // Würfel

	ppModel[0]->create_cube(0.6f, 128, 128, 200, 255, MDL_COLOR);
	ppModel[0]->set_mdl_pos(0.0f, 0.0f, -2.0f);

	ppModel[1]->create_cube(0.6f, 128, 128, 200, 255, MDL_COLOR);
	ppModel[1]->set_mdl_pos(2.0f, 0.0f, -1.0f);

	ppModel[2]->create_cube(0.6f, 128, 128, 200, 255, MDL_COLOR);
	ppModel[2]->set_mdl_pos(-2.0f, 0.0f, -1.0f);

	ppModel[3]->create_square(1.3f, 130, 0, 130, MDL_TEXTURE);
	ppModel[3]->set_texture_square("textures/tiles.bmp");
	ppModel[3]->set_mdl_pos(0.0f, 1.0f, -6.0f);

	//exit_code = ppModel[4]->load_mdl_from_obj("models/trooper.obj");
  //ppModel[4]->set_mdl_pos(0.0f, -1.0f, 0.0f);

	ppModel[5]->create_sphere(0.5f, 40, 128, 128, 200, MDL_COLOR);
	ppModel[5]->set_mdl_pos(-1.3f, 1.7f, 0.0f);

	ppModel[6]->create_pyramid(0.5f, 0.9f, 128, 128, 200, MDL_COLOR);
	ppModel[6]->set_mdl_pos(1.3f, 1.7f, 0.0f);

	ppModel[7]->create_cone(0.5f, 0.9f, 16, 128, 128, 200, MDL_COLOR);
	ppModel[7]->set_mdl_pos(-2.0f, 2.6f, -2.0f);

	return exit_code;
}
