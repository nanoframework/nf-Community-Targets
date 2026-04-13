#ifndef TIMERMANAGER_H_
#define TIMERMANAGER_H_

#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include <list>
#include <unistd.h>

extern "C" {
  void *create_pthread(void *data);
}

class TimerManager {
public:
  TimerManager();
  TimerManager(long usec, void (*callback)(void));
  ~TimerManager();
  void start();
  void stop();
  void addTimer(long usec, void (*callback)(void));
private:
  class Timer  
  {
  public:
    Timer(long usec, void (*callback)(void)) :
      duration(usec),
      callback(callback),
      start(0)
    {      
    }
    bool operator ==(Timer other)
    {
      if ((this->callback == other.callback) && (this->duration == other.duration)) {
        return true;
      }
      return false;
    }
    void operator =(Timer other)
    {
      duration = other.duration;
      callback = other.callback;
      start = other.start;
    }
    suseconds_t duration;
    void (*callback)(void);
    suseconds_t start;
  };
  Timer setUpTimer(long micro_duration, void (*callback)(void));
  friend void *create_pthread(void *data);
  void run();
  bool m_bRunning;
  bool m_bGo;
  bool one_shot;
  long m_lMinSleep;
  std::list<Timer> m_cTimers;
  pthread_t m_tTimerThread;
  pthread_cond_t m_tGoLockCondition;
  pthread_mutex_t m_tGoLock;
};

#endif
