#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

void sum(std::promise<int>&& p, int from,int to)
{
    int s = 0;
    for(int i = from ; i <= to ; i++){
        s += i;
    }
    p.set_value(s);
}
int main()
{
    std::promise<int> pm;
    std::future<int> ft = pm.get_future();
    std::thread t(sum, std::move(pm), 1,1000);

    int ret = ft.get();
    std::cout << ret << std::endl;
    t.join();
}
