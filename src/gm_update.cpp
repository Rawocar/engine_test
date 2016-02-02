#include "../incl/gm_update.h"

int gm_update(CApp * pApp, Game_State * pstate, unsigned short int * ppoly_mode)
{
  int exit_code = ERR_GM_NO_ERROR;

	// Events

	event_handler(pApp->get_eventx(), pstate, ppoly_mode, pApp);

	// Spielzustände

	switch(*pstate)
	{
		case load_menu:
		{
      // Projektion von Model 0 berechnen

			pApp->rotate(0, (pApp->cpu_get_timestep() * 0.90f), glm::vec3(0.0f, 1.0f, 0.0f));
			pApp->rotate(1, (pApp->cpu_get_timestep() * 0.90f), glm::vec3(0.0f, 1.0f, 0.0f));
		} break;
		case quit:
		{
			// Shader entladen

			pApp->unload_shader();
		} break;
	};

  return exit_code;
}
