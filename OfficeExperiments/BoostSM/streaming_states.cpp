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


struct StreamHandler : sc::state_machine< StreamHandler, Idle >
{
    // startTime_ remains uninitialized, because there is no reasonable default
    StreamHandler(int p) /* replace this param by A2dpSrcQ pointer*/ {
        cout << "StateMachine" << endl;
    };
    ~StreamHandler()
    {
        terminate();
    }

    int mA2dpSrcQ;
};

struct EvRequestStartSUB : sc::event<EvRequestStartSUB> {};
struct EvOnStartedSUB : sc::event<EvOnStartedSUB> {};
struct EvRequestStartMAIN : sc::event<EvRequestStartMAIN> {};
struct EvOnStartedMAIN : sc::event<EvOnStartedMAIN> {};

struct Idle : sc::simple_state< Idle, StreamHandler >
{
    typedef sc::transition< EvRequestStartSUB, Entering_SUB1 > reactions;
};

struct Entering_SUB1 : sc::state< Entering_SUB1, StreamHandler >
{
    typedef sc::transition< EvOnStartedSUB, SUB1 > reactions;

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

struct SUB1 : sc::state< SUB1, StreamHandler >
{
    typedef sc::transition< EvRequestStartMAIN, Entering_MAIN_SUB > reactions;

    SUB1(my_context ctx) : my_base(ctx)
    {
        cout << "Entering SUB1" << endl;
        //outermost_context().startTime_ = std::time(0);
    }

    ~SUB1()
    {
        cout << "exiting SUB1" << endl;
        /*outermost_context().elapsedTime_ +=
            std::difftime(std::time(0), outermost_context().startTime_);*/
    }
};

struct Entering_MAIN_SUB : sc::state< Entering_MAIN_SUB, StreamHandler >
{
    typedef sc::transition< EvOnStartedMAIN, MAIN_SUB > reactions;

    Entering_MAIN_SUB(my_context ctx) : my_base(ctx)
    {
        cout << "Entering Entering_MAIN_SUB" << endl;
        //outermost_context().startTime_ = std::time(0);
    }

    ~Entering_MAIN_SUB()
    {
        cout << "exiting Entering_MAIN_SUB" << endl;
        /*outermost_context().elapsedTime_ +=
            std::difftime(std::time(0), outermost_context().startTime_);*/
    }
};

struct MAIN_SUB : sc::state< MAIN_SUB, StreamHandler >
{
    typedef sc::transition< EvOnStartedMAIN, MAIN_SUB > reactions;

    MAIN_SUB(my_context ctx) : my_base(ctx)
    {
        cout << "Entering MAIN_SUB" << endl;
        //outermost_context().startTime_ = std::time(0);
    }

    ~MAIN_SUB()
    {
        cout << "exiting MAIN_SUB" << endl;
        /*outermost_context().elapsedTime_ +=
            std::difftime(std::time(0), outermost_context().startTime_);*/
    }
};



// The Main function

int main() {
	
    StreamHandler sm(1);//TODO: pass A2dpSrcQ's *this so that SM has access to all context data. also make StreamHandler nested of A2dpSrcQ to allow access to all data
	sm.initiate();
	sm.process_event(EvRequestStartSUB());
	sm.process_event(EvOnStartedSUB());
    sm.process_event(EvRequestStartMAIN());
    sm.process_event(EvOnStartedMAIN());
    printf("Exiting main\n");
	return 0;
}

