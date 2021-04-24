#include <glib.h>

#include <iostream>     // std::cout
#include <utility>      // std::pair
#include <string>       // std::string
#include <tuple>        // std::tuple, std::tuple_cat, std::get
#include <functional>
#include <thread>
#include <stdio.h>



template<typename BoundFunc>
void runInMainLoop(BoundFunc boundFunc)
{
	auto ptrCopyOfBoundFunc = new auto(boundFunc);

	g_idle_add(
		[](void* data)
		{
			decltype(ptrCopyOfBoundFunc) pfunc = (decltype(ptrCopyOfBoundFunc))data;
			(*pfunc)();
			delete pfunc;
			return G_SOURCE_REMOVE;
		}
	, ptrCopyOfBoundFunc);
}

#define PASSTOMAINLOOP(func, ...) runInMainLoop(std::bind(func, __VA_ARGS__))

void threadFunc()
{
	printf("Thread(%ulld)=> Helper Thread\n", std::this_thread::get_id());
	int p1 = 1;
	std::string pstr("Manoj3");


	PASSTOMAINLOOP([](auto pInt, auto pstr)
		{
			printf("Thread(%ulld)=>i:%d, j:%s\n", std::this_thread::get_id(), pInt, pstr.c_str());
		}
	, p1, pstr);
}

int main()
{
    GMainLoop *mainloop = g_main_loop_new(0, FALSE);
	
	std::thread thrd(threadFunc);

	printf("Thread(%ulld)=> Main Loop\n", std::this_thread::get_id());

    g_main_loop_run(mainloop);
	thrd.join();
    return 0;
}