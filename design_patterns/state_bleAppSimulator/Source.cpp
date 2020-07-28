#include <iostream>

using namespace std;

#define trace cout<<__FUNCTION__<<endl
#define notHandled cout<<__FUNCTION__<<":unhandled"<<endl
class Context;
class TvState {
public:
	enum State {
		ON,
		FLASH,
		DONE,
		NUM_STATES
	};
	TvState(Context& ctx ) :mCtx(ctx) {}
	virtual void onEntry() {
		trace;
		notHandled;
	}
	virtual void onExit() {
		trace;
		notHandled;
	}

	virtual void onAdapterEnabled() {
		trace;
		notHandled;
	}

	virtual void onDeviceFound() {
		trace;
		notHandled;
	}

	virtual void onUserBack() {
		trace;
		notHandled;
	}
protected:
	Context &mCtx;
};
class Context {
public:
	Context();
	void setState(TvState::State stateType);

	void doAdapterEnabled();
	void doDeviceFound();
	void doUserBack();
private:
	TvState * getState(TvState::State stateType) const;
	TvState * mCurState;
	TvState * mStates[TvState::NUM_STATES];
};
//states: on, inFlash, setupdone
class On :public TvState {
public:
	On(Context & ctx) : TvState(ctx) {
		trace;
	}
	void onEntry() override {
		trace;
		cout << "enable adapter request issued: " << endl;
	}
	void onAdapterEnabled() override {
		trace;
		mCtx.setState(FLASH);
	}
	void onExit() override {
		trace;
		//cout << "stop adv" << endl;
	}
	~On() {
		trace;
		
	}

};

class Flash :public TvState {
public:
	Flash(Context & ctx) : TvState(ctx) {
		trace;
	}
	void onEntry() override {
		trace;
		cout << "started ble scan" << endl;
	}
	void onDeviceFound() override {
		trace;
		cout << "stopped ble scan" << endl;
		mCtx.setState(DONE);
	}
	virtual void onUserBack() {
		trace;
		mCtx.setState(ON);
	}
};

class Done :public TvState {
public:
	Done(Context & ctx) : TvState(ctx) {
		trace;
	}
	virtual void onUserBack() {
		trace;
		mCtx.setState(FLASH);
	}
};


	Context::Context() {
		mStates[TvState::ON] = new On(*this);
		mStates[TvState::FLASH] = new Flash(*this);
		mStates[TvState::DONE] = new Done(*this);
		mCurState = mStates[TvState::ON];
		mCurState->onEntry();
	}
	void Context::setState(TvState::State stateType) {
		mCurState->onExit();
		mCurState = getState(stateType);
		mCurState->onEntry();
		
	}

	void Context::doAdapterEnabled() {
		trace;
		mCurState->onAdapterEnabled();
	}
	void Context::doDeviceFound() {
		trace;
		mCurState->onDeviceFound();
		
	}
	void Context::doUserBack() {
		trace;
		mCurState->onUserBack();
	}

	TvState * Context::getState(TvState::State stateType) const {
		return mStates[stateType];
	}


int main() {
	Context ctx;

	ctx.doDeviceFound();
	ctx.doAdapterEnabled();
	ctx.doUserBack();
	ctx.doUserBack();
	ctx.doAdapterEnabled();
	ctx.doDeviceFound();
	ctx.doUserBack();
	ctx.doUserBack();
	ctx.doAdapterEnabled();
	ctx.doDeviceFound();

	
}