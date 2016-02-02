#include "../incl/gm_event.h"

void event_handler(SDL_Event event, Game_State * pstate, unsigned short int * ppoly_mode, CApp * pApp)
{
  switch(event.type)
	{
		case SDL_KEYDOWN:
		{
			event_kd(event, pstate, ppoly_mode);
		} break;
		case SDL_MOUSEWHEEL:
		{
      event_mw(event, pApp);
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

void event_mw(SDL_Event event, CApp * pApp)
{
	// Kamera zoom

	zoom_camera(event, pApp);
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

void zoom_camera(SDL_Event event, CApp * pApp)
{
  glm::vec3 camera_pos = pApp->get_camera_pos();
	float factor_inc = 1.05f;
	float factor_dec = 0.95f;

	// heraus zoomen bix max .z = 6.0f

	if(event.wheel.y < 0)
	{
    if(camera_pos.z * factor_inc < 6.0f)
			{pApp->set_camera_pos(glm::vec3(camera_pos.x, camera_pos.y * factor_inc, camera_pos.z * factor_inc));}
	}

	// heran zoomen bis max .z = 3.0f

	if(event.wheel.y > 0)
	{
		if(camera_pos.z * factor_dec > 3.0f)
			{pApp->set_camera_pos(glm::vec3(camera_pos.x, camera_pos.y * factor_dec, camera_pos.z * factor_dec));}
	}
}
