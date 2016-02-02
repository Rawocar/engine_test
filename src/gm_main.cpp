#include "../incl/gm_main.h"

///////////////////////////////////////////
///////////////////////////////////////////
// Programm
///////////////////////////////////////////
///////////////////////////////////////////

int main(int arg, char ** argv)
{
  int exit_code = EXIT_SUCCESS;

  switch(arg)
  {
    case 1:
		{
      exit_code = run();
		} break;
    case 2:
		{
      // prüfe den Parameter

      if(strcmp(argv[1], "-d") == 0)
			  {exit_code = run();}
      else 
			{
				if(strcmp(argv[1], "-i") == 0)
	        {print_info();}
        else
				{
					exit_code = EINVAL;
					printf("ERROR: invalid parameter for executable...\ntry: -d, -i\n");
				}
			}
    } break;
    default:
		{
			printf("ERROR: invalid number of parameters! only 1 is allowed...\n");
		} break;
  };

  exit(exit_code);
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void print_info()
{
  char line[40 + 1] = "----------------------------------------";

  printf("%s\n3D Fighter\n\nWritten By Patrick-Christopher Mattulat\n%s\n", line, line);
}
