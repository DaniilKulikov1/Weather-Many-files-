#include"Formatirovanie.h"


string Formatirovanie(string& Zapros)
{
	for (int i = 0; i < Zapros.size(); ++i)
	{


		int marker = Zapros.find(",", i);
		if (marker != string::npos)
		{
			Zapros.replace(marker, 1, "\n");

		}
	}

	return Zapros;
}