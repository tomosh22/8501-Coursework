#include <iostream>
#include "Approach1.h"
#include "Approach2.h"
#include "Sets.h"
//#include <windows.h>
#include <thread>
#include <map>
#include <string>
//class Thread {
//public:
//    Thread() {};
//    virtual ~Thread() { CloseHandle(thread_handle); }
//    virtual void start();
//    virtual void join();
//    virtual DWORD get_id() const { return tid; }
//protected:
//    virtual void run() = 0;
//    friend DWORD thread_ftn(LPVOID T);
//    HANDLE thread_handle;
//    DWORD tid;
//private:
//    Thread(const Thread& src);
//    Thread& operator=(const Thread& rhs);
//};
//DWORD thread_ftn(LPVOID T) {
//    Thread* t = static_cast<Thread*>(T);
//    t->run();
//    return NULL;
//}
//void Thread::start() {
//    thread_handle = CreateThread(
//        NULL,
//        0,
//        (LPTHREAD_START_ROUTINE)&thread_ftn,
//        (LPVOID)this,
//        0,
//        &tid
//    );
//}
//void Thread::join() {
//    WaitForSingleObject(thread_handle, INFINITE);
//}

void create_set() {
    std::string string;
    std::cin >> string;
    return;
}

int main()
{
    //create_set();
    std::map<int, int*> setsMap;
    setsMap[0] = Sets::a;
    setsMap[1] = Sets::b;
    setsMap[2] = Sets::c;
    setsMap[3] = Sets::d;
    setsMap[4] = Sets::e;
    setsMap[5] = Sets::f;
    std::thread threads[6]{};
    Approach1::result results[6];
    for (int x = 0; x < 6; x++)
    {
        threads[x] = std::thread(Approach1::run, setsMap[x]);
    }
    for (int x = 0; x < 6; x++) {
        threads[x].join();
    }

    /*Approach1::result a1 = Approach1::run(Sets::a);
    Approach1::result b1 = Approach1::run(Sets::b);
    Approach1::result c1 = Approach1::run(Sets::c);
    Approach1::result d1 = Approach1::run(Sets::d);
    Approach1::result e1 = Approach1::run(Sets::e);
    Approach1::result f1 = Approach1::run(Sets::f);

    Approach2::result a2 = Approach2::run(Sets::a);
    Approach2::result b2 = Approach2::run(Sets::b);
    Approach2::result c2 = Approach2::run(Sets::c);
    Approach2::result d2 = Approach2::run(Sets::d);
    Approach2::result e2 = Approach2::run(Sets::e);
    Approach2::result f2 = Approach2::run(Sets::f);*/
    
    return 0;
}

