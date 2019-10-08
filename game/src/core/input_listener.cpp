#include "input_listener.hpp"

bool InputDispatcher::onKeyDown(int key, bool repeat, int mods){
	for(InputListener* listener : listeners){
		if(listener->onKeyDown(key, repeat, mods)) return true;
	}
	return false;
}

bool InputDispatcher::onKeyUp(int key, int mods){
	for(InputListener* listener : listeners){
		if(listener->onKeyUp(key, mods)) return true;
	}
	return false;
}

bool InputDispatcher::onMouseMove(double x, double y){
	for(InputListener* listener : listeners){
		if(listener->onMouseMove(x, y)) return true;
	}
	return false;
}

bool InputDispatcher::onMouseButtonDown(int button, int mods){
	for(InputListener* listener : listeners){
		if(listener->onMouseButtonDown(button, mods)) return true;
	}
	return false;
}

bool InputDispatcher::onMouseButtonUp(int button, int mods){
	for(InputListener* listener : listeners){
		if(listener->onMouseButtonUp(button, mods)) return true;
	}
	return false;
}

bool InputDispatcher::onWindowClose(){
	for(InputListener* listener : listeners){
		if(listener->onWindowClose()) return true;
	}
	return false;
}

bool InputDispatcher::onWindowFocusChange(bool focused){
	for(InputListener* listener : listeners){
		if(listener->onWindowFocusChange(focused)) return true;
	}
	return false;
}

bool InputDispatcher::onWindowInconify(bool iconified){
	for(InputListener* listener : listeners){
		if(listener->onWindowInconify(iconified)) return true;
	}
	return false;
}

bool InputDispatcher::onWindowResize(int width, int height){
	for(InputListener* listener : listeners){
		if(listener->onWindowResize(width, height)) return true;
	}
	return false;
}

void InputDispatcher::registerListener(InputListener* listener, bool back){
	if(back){
		listeners.emplace_back(listener);
	}else{
		listeners.emplace_front(listener);
	}
}

void InputDispatcher::unregisterListener(InputListener* listener){
	for(auto it = listeners.begin(); it != listeners.end(); ++it){
		if(*it == listener){
			listeners.erase(it);
			return;
		}
	}
}
