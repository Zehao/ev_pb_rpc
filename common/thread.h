
#include<functional>
#include<pthread.h>
#include<memory>

#ifndef _THREAD_H_
#define _THREAD_H_

class Thread
{
public:
    Thread() = delete;
    void operator=(const Thread&) = delete;

public:
    typedef std::function<void ()> Threadfunc;
    explicit Thread(Threadfunc, const std::string& name = std::string());
    ~Thread();

    void start();
    int join();

    bool started() const
    {
        return _started;
    }



    const std::string& name() const
    {
        return _name;
    }

private:
    pthread_t _pthread_id;
    pid_t _tid;

    std::string _name;
    bool _started;
    bool _joined;


};


#endif
