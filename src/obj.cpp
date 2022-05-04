#include<iostream>
#include"../inc/obj.hpp"


Obj::Obj(const std::string& str) : msg(str) {}
void Obj::Identify(){ std::cout << msg << std::endl; }
void Obj::PrintLine(){ std::cout << "--------------------------" << std::endl; } 