#include <algorithm>
#include <iterator>
#include <sys/time.h>
#include "TimerManager.h"

extern "C" void *create_pthread(void *data)
{
  TimerManager *thread_timer_manager = static_cast<TimerManager *>(data);
  thread_timer_manager->run();
  return data;
}

TimerManager::TimerManager() :
  m_bRunning(false),
  m_bGo(false),
  m_lMinSleep(0)
{
  int mutex_creation = pthread_mutex_init(&m_tGoLock, NULL);
  if(mutex_creation != 0) {
    std::cerr << "Failed to create mutex" << std::endl;
    return;
  }

  int mutex_cond_creation = pthread_cond_init(&m_tGoLockCondition, NULL);
  if(mutex_cond_creation != 0) {
    std::cerr << "Failed to create condition mutex" << std::endl;
    return;
  }

  int thread_creation = pthread_create(&m_tTimerThread, NULL, create_pthread, this);
  if(thread_creation != 0) {
    std::cerr << "Failed to create thread" << std::endl;
    return;
  }
  m_bRunning = true;
}

TimerManager::TimerManager(long usec, void (*callback)(void)) :
  m_bRunning(false),
  m_bGo(false),
  m_lMinSleep(0)
{
  int mutex_creation = pthread_mutex_init(&m_tGoLock, NULL);
  if(mutex_creation != 0) {
    std::cerr << "Failed to create mutex" << std::endl;
    return;
  }

  int mutex_cond_creation = pthread_cond_init(&m_tGoLockCondition, NULL);
  if(mutex_cond_creation != 0) {
    std::cerr << "Failed to create condition mutex" << std::endl;
    return;
  }

  int thread_creation = pthread_create(&m_tTimerThread, NULL, create_pthread, this);
  if(thread_creation != 0) {
    std::cerr << "Failed to create thread" << std::endl;
    return;
  }
  m_bRunning = true;

  this->one_shot = true;
  this->addTimer(usec, callback);
  this->start();
}

TimerManager::~TimerManager()
{
    pthread_mutex_lock(&m_tGoLock);
    m_bRunning = false;
    pthread_mutex_unlock(&m_tGoLock);
    void *result;
    pthread_join(m_tTimerThread, &result);
    pthread_detach(m_tTimerThread);
    pthread_mutex_destroy(&m_tGoLock);
    pthread_cond_destroy(&m_tGoLockCondition);
}

void TimerManager::run()
{
  //pthread_mutex_lock(&m_tGoLock);
  while(m_bRunning) {

    usleep(1);

    while (!m_bGo) {
      pthread_cond_wait(&m_tGoLockCondition, &m_tGoLock);
    }
    pthread_mutex_unlock(&m_tGoLock);
    if (!m_bRunning) {
      break;
    }

    struct timeval l_tv;
    gettimeofday(&l_tv, NULL);
    usleep(std::max(0l, m_lMinSleep));

    m_lMinSleep = 0;
    long l_lMin = 0;

    for(std::list<Timer>::iterator it = m_cTimers.begin(); it != m_cTimers.end(); ++it) {
      TimerManager::Timer l_oTimer = *it;
      long timenow = (l_tv.tv_sec * 1000000 + l_tv.tv_usec);
      long elapsed_time = (timenow - (l_oTimer.start));
      l_lMin = elapsed_time - l_oTimer.duration;

      if (elapsed_time >= l_oTimer.duration) {
        l_lMin = l_oTimer.duration;
        l_oTimer.callback();

        if (one_shot) {
          this->stop();
          return;
        }

        gettimeofday(&l_tv, NULL);
        it->start = (l_tv.tv_sec * 1000000) + l_tv.tv_usec;
      }
      m_lMinSleep = std::min(m_lMinSleep, l_lMin);
    }
  }
}

void TimerManager::start()
{
  pthread_mutex_lock(&m_tGoLock);
  m_bGo = true;
  pthread_cond_signal(&m_tGoLockCondition);
  pthread_mutex_unlock(&m_tGoLock);
}

void TimerManager::stop()
{
  pthread_mutex_lock(&m_tGoLock);
  m_bGo = false;
  pthread_mutex_unlock(&m_tGoLock);
}

TimerManager::Timer TimerManager::setUpTimer(long micro_duration, void (*callback)(void))
{
  struct timeval l_tv;
  gettimeofday(&l_tv, NULL);
  Timer l_oTimer(micro_duration, callback);
  l_oTimer.start = (l_tv.tv_sec * 1000000) + l_tv.tv_usec;
  return l_oTimer;
}

void TimerManager::addTimer(long usec, void (*callback)(void))
{
  pthread_mutex_lock(&m_tGoLock);
  Timer insert = setUpTimer(usec, callback);
  for (std::list<Timer>::iterator it = m_cTimers.begin(); it != m_cTimers.end(); ++it) {
    if (*it == insert) {
        return;
    }
  }
  m_cTimers.push_back(insert);
  pthread_mutex_unlock(&m_tGoLock);
}
