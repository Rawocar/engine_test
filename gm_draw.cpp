#include "../incl/gm_draw.h"

int gm_draw(CApp * pApp, Game_State * pstate)
{
  int exit_code = ERR_GM_NO_ERROR;

  // Background

  glClearColor(0.0, 0.0, 0.11, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	// Spielstatus

	switch(*pstate)
	{
		case load_menu:
		{
			pApp->draw_model(0);
		} break;
		case quit:
		{

		} break;
	};

  SDL_GL_SwapWindow(pApp->get_window());

  return exit_code;
}
