
#include <stdio.h>

#include "oal-api-data.h"
#include "oal-api.h"
#include "oal-api-local.h"
#include "oal-api-remote.h"


#include "oal-api-remote.h"

//void eventcb(event_t *evt)
//{
//	printf("event_t.evt: %d\n", evt->evt);
//};

int main()
{
	
	printf("I am oal-sanity-tester\n");
	oalApi();
	LocalOal localOal;
	RemoteOal remoteOal;
	localOal.oalApi();
	remoteOal.oalApi();

	printf("Now testing callback api\n");
	auto cb = [](event_t *evt)
	{
		printf("event_t.evt: %d\n", evt->evt);
	};
	oalInit(cb);
	localOal.oalInit(cb);
	remoteOal.oalInit(cb);

}