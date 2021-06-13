
#include <stdio.h>

#ifdef _FOR_C_API
extern "C"
{
#endif
#include "oal-api-data.h"
	#include "oal-api.h"

	void oalApi()
	{
		printf("Real OALAPI\n");
	}

	void oalInit(eventCb cb)
	{
		printf("Real %s \n", __FUNCTION__);
		event_t evt = { 1 };
		cb(&evt);
	}
#ifdef _FOR_C_API
}
#endif