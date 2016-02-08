#include "../incl/gm_draw.h"

int gm_draw(CApp * pApp, Game_State * pstate)
{
  int exit_code = ERR_GM_NO_ERROR;

  // Background

  glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	// Kamera

	pApp->proj();

	// Spielstatus

	switch(*pstate)
	{
		case load_menu:
		{
			pApp->draw_model(0);
			pApp->draw_model(1);
			pApp->draw_model(2);
			pApp->draw_model(3);
			//pApp->draw_model(4);
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
