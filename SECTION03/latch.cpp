#include <iostream>
#include <mutex>
#include <latch>     // c++20
#include <thread>
using namespace std;

std::latch complete{3};   // 1회만 가능
std::latch gohone{1};
void foo(string name)
{
    cout <<  "start work : " << name << endl;
    cout <<  "end work : " << name << endl;

    complete.count_down(); // --count

    gohome.wait();
    cout <<  "go home " << name << endl;
}

int main()
{
    jthread t1(foo,"kim") , t2(foo,"lee") , t3(foo,"park");
    complete.wait();   // count가 0일때를 대기
    
    cout << "receive signal" << endl;
    gohome.count_down();
    return 0;
}