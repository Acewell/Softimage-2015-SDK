#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef _WIN32
#include <windows.h>
#endif

#include "engine.h"

class ENGINE_API debug_helper
{
public:
	debug_helper( char *fncname );
	~debug_helper();

	char	function_name[255];
	LONG	in,out;

#ifdef _WIN32
	LARGE_INTEGER	l_in;
	LARGE_INTEGER	l_out;
#endif
};

void FUNC_ENTRY(char *functionname);
void FUNC_EXIT(char *functionname, float ns);
LARGE_INTEGER	get_timer();


// uncomment the following lines to trace all calls to 
// c:\functrace.dat
//#define TRACECALLS

#ifdef TRACECALLS
#define DEBUGENTRY( x ) \
	debug_helper __dbg (x);
#else
#define DEBUGENTRY 
#endif


#endif
