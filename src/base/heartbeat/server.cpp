#include "Heartbeat.h"
#include <stdio.h>

int main()
{
	Heartbeat hb;
	hb.init(HB_SERVER);
	hb.run();

	while (getchar() != 'q')
	{
#ifdef WIN32
		Sleep(100);
#else
		usleep(100*1000);
#endif
	}

	return 0;
}
