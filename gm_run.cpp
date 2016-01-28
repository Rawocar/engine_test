#include "../incl/gm_run.h"

int run()
{
  int exit_code = ERR_GM_NO_ERROR;
  CApp * pApp = new CApp();
	Game_State state = load_menu;

	// Debug Mode?

  #if MODE == DEBUG_MODE
  	pApp->init_debug_log(8182);
	#endif

  // init SDL

	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
  {
    #if MODE == DEBUG_MODE
			pApp->write_log("<b>GAME:</b> SDL2 initialisiert...", DB_MSG_OK);
		#endif
	
    // initialisiere das Spiel

		exit_code = init(pApp);
    
		if(exit_code == ERR_GM_NO_ERROR)
		{
			// initialisiere CPU Messgerät

      pApp->cpu_set_timestamp(SDL_GetTicks());
      pApp->cpu_set_timestep(pApp->cpu_get_timestamp() * 0.001);
			pApp->cpu_set_timestamp_prev();

			// Programmschleife

		  while(SDL_PollEvent(pApp->get_event()) || (exit_code == ERR_GM_NO_ERROR && state != quit))
			{
				if(exit_code == ERR_GM_NO_ERROR) // von gm_update
				{
					exit_code = gm_draw(pApp, &state);
				
					if(exit_code == ERR_GM_NO_ERROR)
					{
						exit_code = gm_update(pApp, &state, pApp->get_poly_mode());

						// Prozessor messen

						pApp->cpu_set_timestamp_prev();
						pApp->cpu_set_timestamp(SDL_GetTicks());
						pApp->cpu_set_timestep((pApp->cpu_get_timestamp() - pApp->cpu_get_timestamp_prev()) * 0.001);
					}
				}
			}
		}
		else
		{
			#if MODE == DEBUG_MODE
				pApp->write_log("<b>GAME:</b> Init() fehlgeschlagen...", DB_MSG_ERR);
			#endif
		}
  }
  else
	{
		exit_code = EINVAL;

		#if MODE == DEBUG_MODE
    	pApp->write_log("<b>GAME:</b> SDL2 - Initialisierung ist fehlgeschlagen...", DB_MSG_ERR);
		#endif
  }

	// Debug Log?

	#if MODE == DEBUG_MODE
    pApp->create_log();
	#endif

	// Speicher zerlegen

	delete pApp;

  return exit_code;
}
