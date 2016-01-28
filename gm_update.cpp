#include "../incl/gm_update.h"

int gm_update(CApp * pApp, Game_State * pstate, unsigned short int * ppoly_mode)
{
  int exit_code = ERR_GM_NO_ERROR;

	// Events

	event_handler(pApp->get_eventx(), pstate, ppoly_mode);

	// Spielzustände

	switch(*pstate)
	{
		case load_menu:
		{
      // Projektion von Model 0 berechnen

			pApp->proj_model(0);
		} break;
		case quit:
		{
			// Shader entladen

			unload_shader(pApp);
		} break;
	};

  return exit_code;
}
