#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/state.hpp>

#include <iostream>

namespace sc = boost::statechart;

using namespace std;
struct Active;


struct Idle;
struct Entering_SUB1;
struct Entering_MAIN1;
struct MAIN1;
struct SUB1;
struct Entering_SUB2;
struct Entering_MAIN2;
struct MAIN2;
struct SUB2;
struct Exiting_SUB2;
struct Exiting_MAIN2;
struct Entering_MAIN_SUB;
struct MAIN_SUB;
struct Exiting_MAIN_SUB;


struct StopWatch : sc::state_machine< StopWatch, Idle >
{
    // startTime_ remains uninitialized, because there is no reasonable default
    StopWatch(int p) /* replace this param by A2dpSrcQ pointer*/ {
        cout << "StateMachine" << endl;
    };
    ~StopWatch()
    {
        terminate();
    }

    int mA2dpSrcQ;
};

struct EvReset : sc::event<EvReset> {};
struct EvStartSUB : sc::event<EvStartSUB> {};

struct Entering_SUB1 : sc::state< Entering_SUB1, StopWatch >
{
    typedef sc::transition< EvStartSUB, Idle > reactions;

    Entering_SUB1(my_context ctx) : my_base(ctx)
    {
        cout << "Entering Entering_SUB1" << endl;
        //outermost_context().startTime_ = std::time(0);
    }

    ~Entering_SUB1()
    {
        cout << "exiting Entering_SUB1" << endl;
        /*outermost_context().elapsedTime_ +=
            std::difftime(std::time(0), outermost_context().startTime_);*/
    }
};

struct Idle : sc::simple_state< Idle, StopWatch >
{
    typedef sc::transition< EvStartSUB, Entering_SUB1 > reactions;
};


// The Main function

int main() {
	
    StopWatch sm(1);
	sm.initiate();
	sm.process_event(EvStartSUB());
	sm.process_event(EvReset());
	return 0;
}

