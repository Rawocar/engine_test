#include "../incl/gm_init.h"

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int init_models_menu(CApp * pApp, Game_State * pstate)
{
	int exit_code = ERR_GM_NO_ERROR;
	int holzkiste = 0;
	int steinblock = 1;
	int trooper = 2;
	int schild = 3;
	int wnd_1 = 4;

	int rechte_lampe = 0;
	int hintere_lampe = 1;
	int linke_lampe = 2;
	int rechte_vlampe = 3;

	#if MODE == DEBUG_MODE
		pApp->write_log("init_models_menu()", DB_MSG_HL);
	#endif

	pApp->print_error("Anzahl an Lichtquellen...\n", pApp->set_number_lights(4));

	// Kamera

	pApp->print_error("Kamera...\n", pApp->proj());

  // Würfel

	if(pApp->print_error("Lade Holzkiste...\n", pApp->create_cube(holzkiste, 0.6f)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Positioniere Holzkiste...\n", pApp->set_mdl_pos(holzkiste, -1.0f, 1.0f, -5.0f)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Lade Textur container.png...\n", pApp->set_texture_cube(holzkiste, "textures/container.png", 1.0f, TEXTURE_DIFFUSE, GL_RGBA)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Lade Textur container_spec.png...\n", pApp->set_texture_cube(holzkiste, "textures/container_spec.png", 1.0f, TEXTURE_SPECULAR, GL_RGBA)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Holzkiste: Material...\n", pApp->set_material(holzkiste, MAT_STEEL)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Aktiviere Holzkiste...\n", pApp->set_mdl_active(holzkiste)) == 1)
		{*pstate = quit;}
	pApp->finish_mdl_creation(holzkiste);

	if(pApp->print_error("Lade Steinblock...\n", pApp->create_cube(steinblock, 0.6f)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Positioniere Steinblock...\n", pApp->set_mdl_pos(steinblock, -2.0f, 0.0f, -2.0f)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Lade Textur brick_light.png...\n", pApp->set_texture_cube(steinblock, "textures/brick_light.bmp", 1.5f, TEXTURE_DIFFUSE, GL_RGBA)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Steinblock: Material...\n", pApp->set_material(steinblock, MAT_GOLD)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Aktiviere Steinblock...\n", pApp->set_mdl_active(steinblock)) == 1)
		{*pstate = quit;}
	pApp->finish_mdl_creation(steinblock);

	if(pApp->print_error("Lade Stormtrooper...\n", pApp->load_mdl_from_obj(trooper, "models/trooper/Stormtrooper.obj")) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Positioniere Stormtrooper...\n", pApp->set_mdl_pos(trooper, -5.0f, -2.0f, -4.0f)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Stormtrooper: Material...\n", pApp->set_material(trooper, MAT_STEEL)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Aktiviere Stormtrooper...\n", pApp->set_mdl_active(trooper)) == 1)
		{*pstate = quit;}
	pApp->finish_mdl_creation(trooper);

	if(pApp->print_error("Lade Gras...\n", pApp->create_square(schild, 0.4f)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Lade Textur grass.png...\n", pApp->set_texture_square(schild, "textures/grass.png", 1.0f, TEXTURE_DIFFUSE, GL_RGBA)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Positioniere Gras...\n", pApp->set_mdl_pos(schild, 1.0f, 0.0f, 0.0f)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Aktiviere Gras...\n", pApp->set_mdl_active(schild)) == 1)
		{*pstate = quit;}
	pApp->finish_mdl_creation(schild);

	// Fenster

	if(pApp->print_error("Lade vorderes Femster...\n", pApp->create_square(wnd_1, 0.8f)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Lade Textur trans_window.png...\n", pApp->set_texture_square(wnd_1, "textures/trans_window.png", 1.0f, TEXTURE_DIFFUSE, GL_RGBA)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Positioniere vorderes Fenster...\n", pApp->set_mdl_pos(wnd_1, 0.0f, 1.5f, 1.0f)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Aktiviere vorderes Fenster...\n", pApp->set_mdl_active(wnd_1)) == 1)
		{*pstate = quit;}
	pApp->finish_mdl_creation(wnd_1);

	// Licht

	if(pApp->print_error("Lade rechte Lampe...\n", pApp->create_pointing_light(rechte_lampe, LIGHT_VISIBLE, LIGHT_CUBE, 1.0f, 1.0f, 1.0f, 1.0f)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Positioniere rechte Lampe...\n", pApp->set_light_pos(rechte_lampe, 3.0f, 0.0f, 1.0f)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Licht rechte Lampe...\n", pApp->set_light(rechte_lampe, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Distanz rechte Lampe...\n", pApp->set_plight_dist(rechte_lampe, 1.0f, 0.35f, 0.44f)) == 1)
		{*pstate = quit;}

	if(pApp->print_error("Lade hintere Lampe...\n", pApp->create_pointing_light(hintere_lampe, LIGHT_VISIBLE, LIGHT_CUBE, 1.0f, 1.0f, 1.0f, 1.0f)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Positioniere hintere Lampe...\n", pApp->set_light_pos(hintere_lampe, 1.0f, 0.0f, -7.0f)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Licht hintere Lampe...\n", pApp->set_light(hintere_lampe, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Distanz hintere Lampe...\n", pApp->set_plight_dist(hintere_lampe, 1.0f, 0.35f, 0.44f)) == 1)
		{*pstate = quit;}

	if(pApp->print_error("Lade linke Lampe...\n", pApp->create_pointing_light(linke_lampe, LIGHT_VISIBLE, LIGHT_CUBE, 1.0f, 1.0f, 1.0f, 1.0f)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Positioniere linke Lampe...\n", pApp->set_light_pos(linke_lampe, -5.0f, 0.0f, -2.0f)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Licht linke Lampe...\n", pApp->set_light(linke_lampe, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Distanz linke Lampe...\n", pApp->set_plight_dist(linke_lampe, 1.0f, 0.35f, 0.44f)) == 1)
		{*pstate = quit;}

	if(pApp->print_error("Lade rechte vordere Lampe...\n", pApp->create_pointing_light(rechte_vlampe, LIGHT_VISIBLE, LIGHT_CUBE, 1.0f, 1.0f, 1.0f, 1.0f)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Positioniere rechte vordere Lampe...\n", pApp->set_light_pos(rechte_vlampe, -3.0f, 0.0f, 1.7f)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Licht rechte vordere Lampe...\n", pApp->set_light(rechte_vlampe, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f)) == 1)
		{*pstate = quit;}
	if(pApp->print_error("Distanz rechte vordere Lampe...\n", pApp->set_plight_dist(rechte_vlampe, 1.0f, 0.35f, 0.44f)) == 1)
		{*pstate = quit;}

	return exit_code;
}
