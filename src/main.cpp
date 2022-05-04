#include<iostream>
#include<string>
#include<memory>
#include"../inc/obj.hpp"


std::weak_ptr<Obj> w_ptr_global; // contains null ptr


// --- prototypes ---
void PassUnique(const std::unique_ptr<Obj>&); // compile error if unique_ptr not passed by reference
void PassShared(const std::shared_ptr<Obj>);
void PassWeak(const std::weak_ptr<Obj>);


int main()
{   system("cls");

    std::cout << "\nBEGIN OUTPUT" << std::endl;

    // unique
    std::unique_ptr<Obj> u_ptr = std::make_unique<Obj>("I am a Unique pointer.");
    //std::unique_ptr<Obj> u_ptr(new Obj("I am a Unique pointer.")); // alternative initialisation syntax
    std::cout << "\nFrom within main():" << std::endl;
    std::cout << "Unique pointer is located at address " << &u_ptr << std::endl;
    std::cout << "Pointed Obj is located at address " << u_ptr.get() << std::endl;
    PassUnique(u_ptr);

    // shared
    std::shared_ptr<Obj> s_ptr = std::make_shared<Obj>("I am a Shared pointer.");
    std::cout << "\nFrom within main():" << std::endl;
    std::cout << "Shared pointer is located at address " << &s_ptr << std::endl;
    std::cout << "Pointed Obj is located at address " << s_ptr.get() << std::endl;
    (s_ptr.unique()) ? std::cout << "Shared pointer is the sole manager of Obj." << std::endl : std::cout << "Shared pointer is not the sole manager of Obj." << std::endl;
    std::cout << "Obj is pointed to by " << s_ptr.use_count() << " shared pointers." << std::endl;
    PassShared(s_ptr);

    // weak
    std::weak_ptr<Obj> w_ptr = s_ptr;
    std::cout << "\nFrom within main():" << std::endl;
    std::cout << "Weak pointer is located at address " << &w_ptr << std::endl;
    (!w_ptr.expired()) ? std::cout << "Weak pointer is still valid." << std::endl : std::cout << "Weak pointer has expired." << std::endl;
    std::cout << "Pointed Obj is located at address " << w_ptr.lock().get() << std::endl;
    (w_ptr.lock().unique()) ? std::cout << "Weak pointer is the sole manager of Obj." << std::endl : std::cout << "Weak pointer is not the sole manager of Obj." << std::endl;
    std::cout << "Obj is pointed to by " << w_ptr.use_count() << " shared pointers." << std::endl;
    PassWeak(w_ptr);

    {
        std::cout << "\nAssigning another shared pointer to a weak pointer within a child scope..." << std::endl;
        std::shared_ptr<Obj> s_ptr_scoped = std::make_shared<Obj>("I am a Shared pointer within a child scope of main.");
        w_ptr_global = s_ptr_scoped;
        (!w_ptr_global.expired()) ? std::cout << "Scoped weak pointer is still valid." << std::endl : std::cout << "Scoped weak pointer has expired." << std::endl;
        std::cout << "Scoped weak pointer is located at address " << &w_ptr_global << std::endl;
    }
    std::cout << "\nOutside of child scope, within main():" << std::endl;
    (!w_ptr_global.expired()) ? std::cout << "Scoped weak pointer is still valid." << std::endl : std::cout << "Scoped weak pointer has expired." << std::endl;





    return 0;
}


// --- definitions ---
void PassUnique(const std::unique_ptr<Obj>& p)
{
    std::cout << "\nFrom within PassUnique():" << std::endl;
    std::cout << "Unique pointer is located at address " << &p << std::endl;
    std::cout << "Pointed Obj is located at address " << p.get() << std::endl;
    p->PrintLine();
}

void PassShared(const std::shared_ptr<Obj> p)
{
    std::cout << "\nFrom within PassShared():" << std::endl;
    std::cout << "Shared pointer is located at address " << &p << std::endl;
    std::cout << "Pointed Obj is located at address " << p.get() << std::endl;
    (p.unique()) ? std::cout << "Shared pointer is sole manager of Obj." << std::endl : std::cout << "Shared pointer is not the sole manager of Obj." << std::endl;
    std::cout << "Obj is pointed to by " << p.use_count() << " shared pointers." << std::endl;
    p->PrintLine();
}

void PassWeak(const std::weak_ptr<Obj> p)
{
    std::cout << "\nFrom within PassWeak():" << std::endl;
    std::cout << "Weak pointer is located at address " << &p << std::endl;
    (!p.expired()) ? std::cout << "Weak pointer is still valid." << std::endl : std::cout << "Weak pointer has expired." << std::endl;
    std::cout << "Pointed Obj is located at address " << p.lock().get() << std::endl;
    (p.lock().unique()) ? std::cout << "Weak pointer is the sole manager of Obj." << std::endl : std::cout << "Weak pointer is not the sole manager of Obj." << std::endl;
    std::cout << "Obj is pointed to by " << p.use_count() << " shared pointers." << std::endl;
}