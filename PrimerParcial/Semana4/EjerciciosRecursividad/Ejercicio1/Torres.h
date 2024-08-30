#include <iostream>
#include <functional>

using namespace std;
template <typename T>
class Torres{
    public:
    std::function<void(T,char,char,char)> torresHanoi;
    Torres();
    ~Torres();
};