
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <chrono>

class String {
public:
    String() = default;
    String(const char* str)
    {
        std::cout << "Created\n";

        m_size = strlen(str);
        m_data = new char[m_size];
        memcpy(m_data, str, m_size);
    }

    //copy ctor
    String(const String& rhs)
    {
        std::cout << "Copied\n";

        m_size = rhs.m_size;
        m_data = new char[m_size];
        memcpy(m_data, rhs.m_data, m_size);
    }

    //move ctor
    String(String&& rhs) noexcept
    {
        std::cout << "Moved\n";

        m_size = rhs.m_size;
        m_data = rhs.m_data;

        rhs.m_data = nullptr;
        rhs.m_size = 0;
    }

    //move assignment operator
    String& operator=(String&& rhs) noexcept
    {
        std::cout << "Move assigned\n";

        if(this != &rhs) {
            delete[] m_data;
            m_size = rhs.m_size;
            m_data = rhs.m_data;

            rhs.m_data = nullptr;
            rhs.m_size = 0;
        }
        return *this;
    }

    virtual ~String()
    {
        std::cout << "Destroyed\n";
        delete [] m_data;
    }

    void Print() const
    {
        for (size_t i = 0; i < m_size; ++i) {
            std::cout << m_data[i];
        }
        std::cout << "\n";
    }

private:
    size_t m_size = 0;
    char* m_data = nullptr;
};

class Entity {
public:
    Entity(const String& name) : m_name{name}
    {}

    Entity(String&& name) : m_name{std::move(name)}
    {}
    virtual ~Entity() = default;

    void PrintName()
    {
        m_name.Print();
    }

private:
    String m_name;
};



void process(const String& lvalArg)
{
    std::cout << "process lvalArg: ";
    lvalArg.Print();
}

void process(String&& rvalArg)
{
    std::cout << "process rvalArg: ";
    rvalArg.Print();
}

template<typename T>
void logAndProcess(T&& param) // param here is a universal reference
{
    std::cout << "log param\n";
    process(std::forward<T>(param));  //conditional cast: it casts to an rvalue only if its argument was initialized with an rvalue 
    //process(param);
}


int fibonacci(int n) {

    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}


int main() {

    //move ctor
    //String name("fooo");
    //Entity entity(std::move(name));
    //Entity entity("foo");

    //move ctor
    //String name("fooo");
    //String other_name = std::move(name);

    //move assignemnt
    //String other;
    //other = std::move(other_name);

    //perfect forwarding
    String name("fooo");
    logAndProcess(name);
    logAndProcess(std::move(name));
    logAndProcess("alma");



    auto measureFunctionTime = 
            [](auto&& func, auto&&... params) // func is universal reference, params is universal reference parameter pack
        {
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

            std::forward<decltype(func)>(func)(
                std::forward<decltype(params)>(params)...
            );
            
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
        };

    measureFunctionTime(fibonacci, 45);

    return 0;
}