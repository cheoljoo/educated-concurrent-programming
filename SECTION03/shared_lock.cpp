#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <shared_mutex>
#include <string_view>
using namespace std::literals;

std::shared_mutex m;
int share_data = 0;

void Writer()
{
    while(1)
    {
        {
            std::lock_guard<std::shared_mutex> lg(m);   // RAII   
                        //예외가 발생해도 지역변수는 안전하게 소멸된다. 
            share_data = share_data + 1;
            std::cout << "Writer : " << share_data << std::endl;
            std::this_thread::sleep_for(1s);        
        }        

        std::this_thread::sleep_for(10ms);
    }
}
void Reader(std::string_view name)
{
    while(1)
    {   
        {  
            //m.lock_shared();
        
            //std::lock_guard<std::shared_mutex> lg(m);    
            std::shared_lock<std::shared_mutex> lg(m);   // shared_mutex를 사용할때 unlock을 알아서 하게 하고 싶을 때
                
            std::cout << "Reader(" << name <<  ") : " << share_data << std::endl;
            std::this_thread::sleep_for(500ms);
            
            //m.unlock_shared();
        }
        
        std::this_thread::sleep_for(10ms);
    }
}

int main()
{
	std::thread t1(Writer);
    std::thread t2(Reader, "A");
    std::thread t3(Reader, "B");
    std::thread t4(Reader, "C");
	t1.join();
	t2.join();
    t3.join();
	t4.join();
}



