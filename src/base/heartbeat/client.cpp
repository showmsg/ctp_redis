#include "Heartbeat.h"
#include <stdio.h>

int main()
{
	Heartbeat hb;
	hb.init(HB_CLIENT);
	hb.send_msg(HB_MSG_REG, NULL, 0);
	hb.run();

	while (getchar() != 'q')
	{
#ifdef WIN32
		Sleep(100);
#else
		usleep(100*1000);
#endif
	}

	hb.send_msg(HB_MSG_QUIT, NULL, 0);

	return 0;
}
