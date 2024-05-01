#include"Formatirovanie.h"


string Formatirovanie2(string& Zapros)
{

	for (int i = 0; i < Zapros.size(); ++i)
	{
		int marker = Zapros.find("}", i);
		int marker1 = Zapros.find("{", i);
		int marker2 = Zapros.find("[", i);
		int marker3 = Zapros.find("]", i);
		int marker4 = Zapros.find("\"", i);


		if (marker != string::npos)
		{
			Zapros.replace(marker, 1, " ");
		}
		if (marker1 != string::npos)
		{
			Zapros.replace(marker1, 1, " ");
		}

		if (marker2 != string::npos)
		{
			Zapros.replace(marker2, 1, " ");
		}

		if (marker3 != string::npos)
		{
			Zapros.replace(marker3, 1, " ");
		}

		if (marker4 != string::npos)
		{
			Zapros.replace(marker4, 1, " ");
		}
	}

	return Zapros;
}

