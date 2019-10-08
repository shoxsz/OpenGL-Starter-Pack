#include "time.hpp"

#include <chrono>

unsigned long Time::now(){
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void Timer::start() {
	startT = 0;
}

void Timer::pause() {
	paused = true;
}

void Timer::resume() {
	paused = false;
}

void Timer::update(float elapsed) {
	if (!paused) {
		startT += elapsed;
	}
}

float Timer::getTime() const {
	return startT;
}