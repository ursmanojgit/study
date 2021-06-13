#include <stdio.h>
#include <chrono>
#include <ctime>

#define CURRENT_EPOCH_MICROSECS std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count()

#define INFO(fmt, ...)   printf("%lu " fmt "\n", std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count(), __VA_ARGS__)
#define ERR(fmt, ...)    INFO("!!!!!!!!ERROR!!!!!!" fmt, __VA_ARGS__)

#define BUFFER_SIZE 6656
#define LOOP_COUNT 10