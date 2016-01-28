#include "../incl/gm_event.h"

void event_handler(SDL_Event event, Game_State * pstate, unsigned short int * ppoly_mode)
{
  switch(event.type)
	{
		case SDL_KEYDOWN:
		{
			event_kd(event, pstate, ppoly_mode);
		} break;
		default:
		{

		} break;
	};
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void event_kd(SDL_Event event, Game_State * pstate, unsigned short int * ppoly_mode)
{
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
