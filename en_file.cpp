#include "../incl/en_file.h"

int read_file(const char * pFile, char * pBuffer, unsigned int length)
{
	int exit_code = ERR_EN_NO_ERROR;
  unsigned char c = '\0';

	// Datei öffnen

	FILE * pHandle = fopen(pFile, "r");

	if(pHandle != NULL)
	{
		// in Buffer schreiben

    for(unsigned int i = 0 ; i < length ; i++)
    {
      c = fgetc(pHandle);

			if(i == (length - 1))
				{*(pBuffer + i) = '\0';}
			else
				{*(pBuffer + i) = c;}
		}

		// Datei schließen

		fclose(pHandle);
	}
  else
	  {exit_code = ERR_EN_FOPEN;}
 
  return exit_code;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

int len_file(const char * pFile)
{
  unsigned int length = 0;
  unsigned char c = '\0';

  // Datei öffnen

  FILE * pHandle = fopen(pFile, "r");

	if(pHandle != NULL)
  {
		// Auslesen

    do
    {
      c = fgetc(pHandle);
			
			if(c != EOF)
				{length++;} 
		} while(!feof(pHandle));

		// Datei schließen

		fclose(pHandle);
  }

  return length;
}
