
#include "oal-api-local.h"
#include "oal-api.h"
#include <stdio.h>

void LocalOal::oalApi()
{
	printf("Local OALAPI, calling real oalApi\n");
	::oalApi();
}

void LocalOal::oalInit(eventCb cb)
{
	printf("Local OALAPI, calling real %s\n", __FUNCTION__);
	::oalInit(cb);
}
