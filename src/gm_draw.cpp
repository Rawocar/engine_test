#include "../incl/gm_draw.h"

int gm_draw(CApp * pApp, Game_State * pstate)
{
  int exit_code = ERR_GM_NO_ERROR;

  // Background

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Spielstatus

	switch(*pstate)
	{
		case load_menu:
		{
			pApp->draw_mdl();

			if(pApp->print_error("Zeichne rechte Lampe...\n", pApp->draw_light(0)) == 1)
				{*pstate = quit;}
			if(pApp->print_error("Zeichne hintere Lampe...\n", pApp->draw_light(1)) == 1)
				{*pstate = quit;}
			if(pApp->print_error("Zeichne linke Lampe...\n", pApp->draw_light(2)) == 1)
				{*pstate = quit;}
			if(pApp->print_error("Zeichne rechte vordere Lampe...\n", pApp->draw_light(3)) == 1)
				{*pstate = quit;}
		} break;
		case quit:
		{

		} break;
		case end:
		{

		} break;
	};

  SDL_GL_SwapWindow(pApp->get_window());

  return exit_code;
}
