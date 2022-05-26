#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <shared_mutex>
#include <string_view>
#include <queue>
using namespace std::literals;
using namespace std;

//std::mutex m;
std::shared_mutex m;
std::mutex qm;
int share_data = 0;
std::queue<int> q;

void producer()
{
    while(1)
    {
        m.lock();
        share_data = (share_data + 1)%10000;
        
        if(q.size() < 1000){
            q.push(share_data);
        } else {
            cout << "producer over 1000 (" << std::this_thread::get_id() << ") : data=" << share_data << " , qsize=" << q.size() << endl;
            std::this_thread::sleep_for(1s);
        }
        // std::this_thread::sleep_for(1ms);        
        m.unlock();
        std::this_thread::sleep_for(1ms);
    }
}
void consumer(std::string_view name)
{
    
    while(1)
    {      
        int qp = -1;
        int qs = 0;
        m.lock_shared();
        
        qm.lock();
        if(q.size() >= 100){
            qp = q.front();
            q.pop();
            qs = q.size();
        } 
        qm.unlock();

        if(qp != -1){
            std::cout << name << " : consumer(" << std::this_thread::get_id() << ") : pop=" << qp << ", qsize=" << qs << endl;
        }
                
        m.unlock_shared();
        std::this_thread::sleep_for(10ms);
    }
} 

int main()
{
	std::thread t1(producer);
    std::thread t2(consumer, "A");
    std::thread t3(consumer, "B");
    std::thread t4(consumer, "C");
	t1.join();
	t2.join();
    t3.join();
	t4.join();
}



