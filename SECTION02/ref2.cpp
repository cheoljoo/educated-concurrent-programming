#include <iostream>

template<typename T> struct reference_wrapper
{
    T* obj;
public:
    reference_wrapper(T& t) : obj(&t) {}    
    operator T&() { return *obj;}
};

int main()
{
    int n = 0;
    reference_wrapper<int> rw = n;
  
    
    // std::reference_wrapper는 객체의 주소를 보관 하고 , T& 로 암시적 변환이 가능하다.
    int& r = rw; // rw.operator int&() 
    r = 100;
  
    std::cout << n << std::endl; // 100
}