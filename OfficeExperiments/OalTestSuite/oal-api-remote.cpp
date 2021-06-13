
#include "oal-api-remote.h"
#include <stdio.h>


void socketOalApi()
{
	printf("oal-api RPC\n");
}
void RemoteOal::oalApi()
{
	printf("Remote OALAPI, calling oal-client for socket communication\n");
	socketOalApi();
}

void RemoteOal::oalInit(eventCb cb)
{
	printf("Remote OALAPI, calling  %s over RPC\n", __FUNCTION__);
	//::oalInit();
	event_t evt = { 2 };
	cb(&evt);
}
