#include <string>

template <class T> class auto_ptr {
    private: T* ptr;
    public:
      explicit auto_ptr(T* p = 0) : ptr(p) { }
      ~auto_ptr() { delete ptr; }
      T& operator*() { return *ptr; }
      T* operator->() { return ptr; }
};

void foo0() {
    auto_ptr<std::string> p(new std::string("I did one P.O.F!\n"));
}


int main(void) {
    
    foo0();
    return 0;
}