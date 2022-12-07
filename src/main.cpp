
#include <iostream>
#include <stdio.h>
#include <string.h>

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
        delete m_data;
    }

    void Print()
    {
        for (size_t i = 0; i < m_size; ++i) {
            std::cout << m_data[i];
        }
        std::cout << "\n";
    }

private:
    size_t m_size;
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

int main() {

    //move ctor
    //Entity entity(std::move(name));
    Entity entity("foo");

    String name("fooo");
    //move ctor
    String other_name = std::move(name);

    String other;
    //move assignemnt
    other = std::move(other_name);

    entity.PrintName();

    std::cin.get();
    return 0;
}