#ifndef __OBSERVER_H__
#define __OBSERVER_H__

class Subject;

class Observer {
  public:
    // Pass in the Subject that called the notify method.
    virtual void notify(Subject &  whoNotified) noexcept = 0; 

    virtual ~Observer() = default;
};

#endif
