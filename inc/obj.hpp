#ifndef OBJ_HPP
#define OBJ_HPP

#include<string>

class Obj
{
    std::string msg;
    public:
        explicit Obj(const std::string&);
        void Identify();
        void PrintLine();
};

#endif