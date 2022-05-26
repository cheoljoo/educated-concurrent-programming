#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <vector>
using namespace std;
using namespace chrono;


#define MAX 100000000
#define LL long long

void Sum(std::promise<LL>&& p,vector<int> v,size_t from,size_t to)
{
    LL s = 0;
    cout << "Sum (" << std::this_thread::get_id() << "):" << from << "~" << to << endl;
    for(size_t i = from ; i <= to ; i++){
        s += v[i];
    }
    // cout << s << endl;
    p.set_value(s);
}

LL asyncSum(vector<int> v,size_t from,size_t to)
{
    LL s = 0;
    cout << "Sum (" << std::this_thread::get_id() << "):" << from << "~" << to << endl;
    for(size_t i = from ; i <= to ; i++){
        s += v[i];
    }
    // cout << s << endl;
    return s;
}

int main()
{
    vector<int> v;
    for(int i = 0 ;i < MAX;i++){
        v.push_back(i%100);
    }

    std::promise<LL> pm;
    std::future<LL> ft = pm.get_future();
    std::thread t(&Sum, std::move(pm),v,0,MAX);
    // long long ret = ft.get();
    std::cout << "single thread : " << ft.get() << std::endl;
    t.join();

    std::future<LL> ft0 = std::async( std::launch::async, asyncSum, v,MAX/4*0,MAX/4*1-1);
    std::future<LL> ft1 = std::async( std::launch::async, asyncSum, v,MAX/4*1,MAX/4*2-1);
    std::future<LL> ft2 = std::async( std::launch::async, asyncSum, v,MAX/4*2,MAX/4*3-1);
    std::future<LL> ft3 = std::async( std::launch::async, asyncSum, v,MAX/4*3,MAX/4*4-1);
    std::cout << "parallel thread : " << ft0.get()+ft1.get()+ft2.get()+ft3.get() << std::endl;


}
