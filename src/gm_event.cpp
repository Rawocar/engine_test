#include "../incl/gm_event.h"

void event_handler(Game_State * pstate, unsigned short int * ppoly_mode, CApp * pApp)
{
	SDL_Event event = pApp->get_eventx();

  switch(event.type)
	{
		case SDL_KEYDOWN:
		{
			event_kd(pApp, pstate, ppoly_mode);
		} break;
		case SDL_MOUSEWHEEL:
		{
      event_mw(pApp, pstate);
		} break;
		default:
		{

		} break;
	};
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void event_kd(CApp * pApp, Game_State * pstate, unsigned short int * ppoly_mode)
{
	SDL_Event event = pApp->get_eventx();

  switch(event.key.keysym.sym)
	{
		case SDLK_ESCAPE:
		{
			esc_kd(pstate);
		} break;
		case SDLK_p:
		{
			p_kd(ppoly_mode);
		} break;
		case SDLK_l:
		{
			for(unsigned int i = 0 ; i < pApp->get_number_lights() ; i++)
			{
				if(pApp->get_light_state(i) == ON)
					{pApp->switch_light(i, OFF);}
				else
					{pApp->switch_light(i, ON);}
			}
		} break;
		default:
		{

		} break;
	};
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void esc_kd(Game_State * pstate)
{
  switch(*pstate)
	{
		case load_menu:
		{
			*pstate = quit;
		} break;
		default:
		{

		} break;
	}; 
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void event_mw(CApp * pApp, Game_State * pstate)
{
	// Kamera zoom

	zoom_camera(pApp, pstate);
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void p_kd(unsigned short int * ppoly_mode)
{
  *ppoly_mode = (*ppoly_mode + 1) % 3;

  switch(*ppoly_mode)
  {
		case POLY_MODE_FILL:
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		} break;
    case POLY_MODE_LINE:
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		} break;
    case POLY_MODE_POINT:
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		} break;
	};
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void zoom_camera(CApp * pApp, Game_State * pstate)
{
	SDL_Event event = pApp->get_eventx();
  glm::vec3 camera_pos = pApp->get_camera_pos();
	float factor_inc = 1.05f;
	float factor_dec = 0.95f;

	// heraus zoomen bis max .z = 9.0f

	if(event.wheel.y < 0)
	{
    if(camera_pos.z * factor_inc < 9.0f)
		{
			pApp->set_camera_pos(glm::vec3(camera_pos.x, camera_pos.y * factor_inc, camera_pos.z * factor_inc));

			if(pApp->print_error("Kamera...\n", pApp->proj()) == 1)
				{*pstate = quit;}
		}
	}

	// heran zoomen bis max .z = 3.0f

	if(event.wheel.y > 0)
	{
		if(camera_pos.z * factor_dec > 3.0f)
		{
			pApp->set_camera_pos(glm::vec3(camera_pos.x, camera_pos.y * factor_dec, camera_pos.z * factor_dec));

			if(pApp->print_error("Kamera...\n", pApp->proj()) == 1)
				{*pstate = quit;}
		}
	}
}
