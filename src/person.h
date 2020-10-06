#pragma once
#include <string>

class Person
{
public:
    Person()
        :   m_Name("Unclaimed"), m_Credits(-1), m_Driver(true)
    {
    }

    Person(std::string& name, int credits, bool driver = true)
        :   m_Name(name), m_Credits(credits), m_Driver(driver)
    {
    }

    void UseCredits(int numCredits) { m_Credits -= numCredits; }

    std::string& GetName() { return m_Name; }
    int GetCredits() { return m_Credits; }
    bool IsDriver() { return m_Driver; }

    bool operator==(std::string& name) { return name == m_Name; }

private:
    std::string m_Name;
    int m_Credits;
    bool m_Driver;
};