#ifndef _TIME_HPP_
#define _TIME_HPP_

class Time{
public:
	static unsigned long now();
};

class Timer {
public:
	void start();
	void pause();
	void resume();

	void update(float time);
	float getTime() const;

private:
	float startT = 0;
	bool paused = false;
};

#endif