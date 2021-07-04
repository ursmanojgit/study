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
struct Stopped;
struct Running;
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
        if (state_cast<const Stopped*>() != 0)
        {
            return elapsedTime_;
        }
        else if (state_cast<const Running*>() != 0)
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
    // startTime_ is only meaningful when the machine is in Running
    std::time_t startTime_;
};

struct EvReset : sc::event<EvReset> {};
struct EvStartStop : sc::event<EvStartStop> {};

struct Active : sc::state< Active, StopWatch, Stopped >
{
    typedef sc::transition< EvReset, Active > reactions;

    Active(my_context ctx) : my_base(ctx)
    {
        cout << "Entering Active" << endl;
        outermost_context().elapsedTime_ = 0.0;
    }
};

struct Running : sc::state< Running, Active >
{
    typedef sc::transition< EvStartStop, Stopped > reactions;

    Running(my_context ctx) : my_base(ctx)
    {
        cout << "Entering Running" << endl;
        outermost_context().startTime_ = std::time(0);
    }

    ~Running()
    {
        cout << "exiting Running" << endl;
        outermost_context().elapsedTime_ +=
            std::difftime(std::time(0), outermost_context().startTime_);
    }
};

struct Stopped : sc::simple_state< Stopped, Active >
{
    typedef sc::transition< EvStartStop, Running > reactions;
};


// The Main function
//
//int main() {
//	
//    StopWatch sm;
//	sm.initiate();
//	sm.process_event(EvStartStop());
//	sm.process_event(EvReset());
//	return 0;
//}

