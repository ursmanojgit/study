#ifndef __OAL_API_DATA_H__
#define __OAL_API_DATA_H__
typedef struct
{
	int evt;
} event_t;

typedef void(*eventCb)(event_t*);

#endif

