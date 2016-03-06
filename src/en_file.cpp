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

//------------------------------------------------------------------------
//------------------------------------------------------------------------

BMP * load_bmp(const char * pPath)
{
	FILE * pFile = NULL;
	BMP * pBmp = new BMP;
	unsigned char * pBuffer_File = NULL;
	unsigned char * pData_BGRA = NULL;
	int i = 0;
	char c;
	int RGBbytes_in_row = 0;

	if(pBmp != NULL)
	{
		pFile = fopen(pPath, "rb");

		if(pFile != NULL)
		{
			// Bestimme Größe der Datei

			pBmp->num_bytes = 0;

			while(fgetc(pFile) != EOF)
				{pBmp->num_bytes++;}

			// lege Speicher an

			pBuffer_File = new unsigned char[pBmp->num_bytes];

			if(pBuffer_File != NULL)
			{
				// für erneutes Durchlaufen vorbereiten

				rewind(pFile);		
				clearerr(pFile);

				while((c = fgetc(pFile)) != EOF)
				{
					pBuffer_File[i] = c;
					i++;
				}

				// Daten füllen

				pBmp->bfType = *((short int*)(void*)(pBuffer_File + 0));
				pBmp->bfSize = *((int*)(void*)(pBuffer_File + 2));
				pBmp->bfReserved = *((int*)(void*)(pBuffer_File + 6));
				pBmp->bfOffBits = *((int*)(void*)(pBuffer_File + 10));
				pBmp->biSize = *((int*)(void*)(pBuffer_File + 14));
				pBmp->biWidth = *((int*)(void*)(pBuffer_File + 18));
				pBmp->biHeight = *((int*)(void*)(pBuffer_File + 22));
				pBmp->biPlanes = *((short int*)(void*)(pBuffer_File + 26));
				pBmp->biBitCount = *((short int*)(void*)(pBuffer_File + 28));
				pBmp->biCompression = *((int*)(void*)(pBuffer_File + 30));
				pBmp->biSizeImage = *((int*)(void*)(pBuffer_File + 34));
				pBmp->biXPelsPerMeter = *((int*)(void*)(pBuffer_File + 38));
				pBmp->biYPelsPerMeter = *((int*)(void*)(pBuffer_File + 42));
				pBmp->biClrUsed = *((int*)(void*)(pBuffer_File + 46));
				pBmp->biClrImportant = *((int*)(void*)(pBuffer_File + 50));

				// Speicher für Bilddaten anlegen

				pData_BGRA = new unsigned char[pBmp->biSizeImage];

				if(pBmp->pData != NULL)
				{
					// Bilddaten übertragen

					rewind(pFile);		
					clearerr(pFile);
					fseek(pFile, pBmp->bfOffBits, SEEK_SET);
					fread(pData_BGRA, pBmp->biSizeImage, 1, pFile);

					// Filtere Alpha

					pBmp->pData = new unsigned char[(pBmp->biSizeImage / 4) * 3];
					i = 0;

					for(int g = 0 ; g < ((pBmp->biSizeImage / 4) * 3) ; g++)
					{
						pBmp->pData[g] = pData_BGRA[i];

						if(RGBbytes_in_row < ((3 * pBmp->biWidth) - 1))
						{
							RGBbytes_in_row++;
							i++;
						}
						else
						{
							RGBbytes_in_row = 0;
							i += (pBmp->biWidth + 1);
						}
					}

					// Datei schließen

					fclose(pFile);

					// Speicher bereinigen

					delete [] pData_BGRA;
					delete [] pBuffer_File;
				}
			}
		}	
  }

	return pBmp;
}
