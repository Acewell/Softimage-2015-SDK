#include <stdio.h>
#include <string.h>
#include "debug.h"

LARGE_INTEGER	cpu_freq;
static bool must_init = true;

debug_helper::debug_helper( char *fncname )
{
	if ( must_init )
	{

		QueryPerformanceFrequency( &cpu_freq );

		::DeleteFile ( "c:\\functrace.dat" );

		must_init = false;
	}

	strcpy(this->function_name , fncname);
	FUNC_ENTRY(fncname);

#ifdef _WIN32
	l_in = get_timer();
#endif

}

debug_helper::~debug_helper ()
{
	float value;
#ifdef _WIN32
	l_out = get_timer();

	__int64 diff = l_out.QuadPart - l_in.QuadPart;

	double dv;
	dv = ((double)diff / (double)cpu_freq.QuadPart) * 100;

	value = (float)dv;
#endif
	
	FUNC_EXIT(this->function_name, value);
}

static	int fn_entries = 0;

void FUNC_ENTRY(char *functionname)
{
	fn_entries++;

	FILE *f = fopen("c:\\functrace.dat","at");
	for (int t=0;t<fn_entries;t++)
	{
		fprintf(f,"\t");
	}

	fprintf(f,"->%s()\n",functionname);

	fclose(f);

}

void FUNC_EXIT(char *functionname, float ns)
{
	FILE *f = fopen("c:\\functrace.dat","at");
	for (int t=0;t<fn_entries;t++)
	{
		fprintf(f,"\t");
	}
			
	fprintf(f,"<-%s() %f\n",functionname, ns);

	fclose(f);
	
	fn_entries--;

}

LARGE_INTEGER	get_timer()
{
	LARGE_INTEGER	count1;

	QueryPerformanceCounter (&count1);

	return (count1);

}
