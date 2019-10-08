#ifndef _INPUT_LISTENER_HPP_
#define _INPUT_LISTENER_HPP_

#include <list>

class InputListener {
public:
	virtual bool onKeyDown(int key, bool repeat, int mods) { return false; }
	virtual bool onKeyUp(int key, int mods) { return false; }

	virtual bool onMouseMove(double x, double y) { return false; }
	virtual bool onMouseButtonDown(int button, int mods) { return false; }
	virtual bool onMouseButtonUp(int button, int mods) { return false; }

	virtual bool onWindowClose() { return false; }
	virtual bool onWindowFocusChange(bool focused) { return false; }
	virtual bool onWindowInconify(bool iconified) { return false; }
	virtual bool onWindowResize(int width, int height) { return false; }
};

class InputDispatcher : public InputListener {
public:
	InputDispatcher(){}

	virtual bool onKeyDown(int key, bool repeat, int mods) override;
	virtual bool onKeyUp(int key, int mods) override;

	virtual bool onMouseMove(double x, double y) override;
	virtual bool onMouseButtonDown(int button, int mods) override;
	virtual bool onMouseButtonUp(int button, int mods) override;

	virtual bool onWindowClose() override;
	virtual bool onWindowFocusChange(bool focused) override;
	virtual bool onWindowInconify(bool iconified) override;
	virtual bool onWindowResize(int width, int height) override;

	void registerListener(InputListener* listener, bool back = true);
	void unregisterListener(InputListener* listener);
private:
	std::list<InputListener*> listeners;
};

#endif