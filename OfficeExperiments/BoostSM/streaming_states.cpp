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


struct StopWatch : sc::state_machine< StopWatch, Active >
{
    // startTime_ remains uninitialized, because there is no reasonable default
    StopWatch() : elapsedTime_(0.0) {
        cout << "StateMachine" << endl;
    };
    ~StopWatch()
    {
        terminate();
    }

    double ElapsedTime() const
    {
        // Ugly switch over the current state.
        if (state_cast<const Idle*>() != 0)
        {
            return elapsedTime_;
        }
        else if (state_cast<const Entering_SUB1*>() != 0)
        {
            return elapsedTime_ + std::difftime(std::time(0), startTime_);
        }
        else // we're terminated
        {
            throw std::bad_cast();
        }
    }

    // elapsedTime_ is only meaningful when the machine is not terminated
    double elapsedTime_;
    // startTime_ is only meaningful when the machine is in Entering_SUB1
    std::time_t startTime_;
};

struct EvReset : sc::event<EvReset> {};
struct EvStartSUB : sc::event<EvStartSUB> {};

struct Active : sc::state< Active, StopWatch, Idle >
{
    typedef sc::transition< EvReset, Active > reactions;

    Active(my_context ctx) : my_base(ctx)
    {
        cout << "Entering Active" << endl;
        outermost_context().elapsedTime_ = 0.0;
    }
};

struct Entering_SUB1 : sc::state< Entering_SUB1, Active >
{
    typedef sc::transition< EvStartSUB, Idle > reactions;

    Entering_SUB1(my_context ctx) : my_base(ctx)
    {
        cout << "Entering Entering_SUB1" << endl;
        outermost_context().startTime_ = std::time(0);
    }

    ~Entering_SUB1()
    {
        cout << "exiting Entering_SUB1" << endl;
        outermost_context().elapsedTime_ +=
            std::difftime(std::time(0), outermost_context().startTime_);
    }
};

struct Idle : sc::simple_state< Idle, Active >
{
    typedef sc::transition< EvStartSUB, Entering_SUB1 > reactions;
};


// The Main function

int main() {
	
    StopWatch sm;
	sm.initiate();
	sm.process_event(EvStartSUB());
	sm.process_event(EvReset());
	return 0;
}

