#include "../incl/gm_update.h"

int gm_update(CApp * pApp, Game_State * pstate, unsigned short int * ppoly_mode)
{
  int exit_code = ERR_GM_NO_ERROR;

	// Events

	event_handler(pstate, ppoly_mode, pApp);

	// Spielzustände

	switch(*pstate)
	{
		case load_menu:
		{
      // Projektion von Model berechnen

			if(pApp->print_error("Rotiere Holzkiste...\n", pApp->rotate(0, (pApp->cpu_get_timestep() * 0.90f), glm::vec3(0.0f, 1.0f, 0.0f))) == 1)
				{*pstate = quit;}
			if(pApp->print_error("Rotiere Steinblock...\n", pApp->rotate(1, (pApp->cpu_get_timestep() * 0.90f), glm::vec3(0.0f, 1.0f, 0.0f))) == 1)
				{*pstate = quit;}
			if(pApp->print_error("Rotiere Trooper...\n", pApp->rotate(2, (pApp->cpu_get_timestep() * 0.90f), glm::vec3(0.0f, 1.0f, 0.0f))) == 1)
				{*pstate = quit;}
		} break;
		case quit:
		{
			// Shader entladen

			pApp->unload_shader(SHADER_MAIN);
			pApp->unload_shader(SHADER_LIGHT);
			*pstate = end;
		} break;
		case end:
		{

		} break;
	};

  return exit_code;
}
