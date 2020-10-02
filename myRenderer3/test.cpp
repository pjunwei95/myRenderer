#include "test.h"
#include <iostream>
#include <iomanip>
#include <string.h>
#include "array.h"
#include "assert.h"

//------------------------------------------------------------------------
struct Scoped
{
public:
    Scoped(const std::string& name,
        void(*cbBegin)(Scoped*) = nullptr,
        void(*cbEnd)(Scoped*) = nullptr
    )
        :
        _name{name}, cbBegin{cbBegin}, cbEnd{cbEnd}
    {
        if (cbBegin)
            cbBegin(this);
    }
    ~Scoped()
    {
        if (cbEnd)
            cbEnd(this);
    }
    void(*cbBegin)(Scoped*);
    void(*cbEnd)(Scoped*);

    std::string getString();

private:
    std::string _name;


};
//------------------------------------------------------------------------

struct ScopedTimer : public Scoped
{
    ScopedTimer(const std::string& name,
        void(*cbBegin)(Scoped*) = nullptr,
        void(*cbEnd)(Scoped*) = nullptr
    )
        :
        Scoped{ name, cbBegin, cbEnd}
    {
    }

    float time_start;
    float time_end;
};

std::string Scoped::getString() { return _name; }


void PrinterStart(Scoped* timer)
{
    printf("Profle Start: %s\n", timer->getString().c_str());
}

void PrinterEnd(Scoped* timer)
{
    printf("Profle End: %s\n", timer->getString().c_str());

}

#define PROFILE_SCOPED() \
Scoped __timer__{__FUNCSIG__, &PrinterStart, &PrinterEnd}
//Scoped timer{ "func1", &PrinterStart, &PrinterEnd }

#define PROFILE_SCOPED_NAME(name) \
Scoped __timer__{name, &PrinterStart, &PrinterEnd}

void func1()
{
    PROFILE_SCOPED();
    printf("Function 1\n");
}

void func2()
{
    PROFILE_SCOPED_NAME("hahahhaa");
    printf("Function 2\n");
}


void test()
{
    func1();
    func2();
}