#include "../incl/gm_init.h"

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int init_models_menu(CApp * pApp)
{
	int exit_code = ERR_GM_NO_ERROR;
	CModel_3D ** ppModel = pApp->get_model_addr();

	#if MODE == DEBUG_MODE
		pApp->write_log("init_models_menu()", DB_MSG_HL);
	#endif

  // Würfel

	ppModel[0]->create_cube(0.6f, 230, 0, 0, 255);
	ppModel[0]->set_mdl_pos(0.0f, 0.0f, -2.0f);

	ppModel[1]->create_cube(0.6f, 0, 230, 0, 255);
	ppModel[1]->set_mdl_pos(2.0f, 0.0f, -1.0f);

	ppModel[2]->create_cube(0.6f, 0, 0, 230, 255);
	ppModel[2]->set_mdl_pos(-2.0f, 0.0f, -1.0f);

	ppModel[3]->create_square(0.3f, 130, 0, 130);
	ppModel[3]->set_texture_square("textures/default.bmp");
	ppModel[3]->set_mdl_pos(0.0f, 1.0f, -1.0f);

	exit_code = ppModel[4]->load_mdl_from_obj("models/Stormtrooper.obj");
  ppModel[4]->set_mdl_pos(0.0f, 0.0f, 0.0f);

	return exit_code;
}
