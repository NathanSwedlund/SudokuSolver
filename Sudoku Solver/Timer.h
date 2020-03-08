#include <ctime>

class Timer
{
    private:
        clock_t c;

    public:
        //sets the timers clock to the current clock?
        void start() { c = clock(); }

        //returns the amount of time since the timer has been started
        long double getTime()
        { 
            return double(clock()-c)/double(CLOCKS_PER_SEC);
        }
        //pauses program for the given number of seconds
        void pauseForSec(float sec)
        {
            Timer t;
            t.start();
            while(t.getTime() < sec);
        }
};