#include <thread>

void foo() {}
void goo() {}

int main()
{
    std::thread t1(&foo);
    std::thread t2(&goo);

    t1.swap(t2);

//    std::thread t3 = t1;  // error  
    std::thread t4 = std::move(t1);  // ok  thread는 복사는 안되지만 move는 가능하다.

//    t1.join(); // 예외.
    t2.join();
    t4.join();
}

