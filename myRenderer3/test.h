//#pragma once
//#include "logger.h"
////#include <string>
//#include "frameRateController.h"
//#define CHAR_MAX_LIMIT 256

------------------------------------------------------------------------
class profile
{
public:
    profile(const char* name,
        void(*cbbegin)(profile*) = nullptr,
        void(*cbend)(profile*) = nullptr
    )
        :
        cbbegin{ cbbegin }, cbend{ cbend }
    {
        strcpy_s(m_name, sizeof(m_name), name);
        if (cbbegin)
            cbbegin(this);
    }
    ~profile()
    {
        if (cbend)
            cbend(this);
    }
    void(*cbbegin)(profile*);
    void(*cbend)(profile*);

    const char* getstring() { return m_name; }

private:
    char m_name[char_max_limit];
    timer m_start;
    timer m_elapsed;
};
//------------------------------------------------------------------------


void profilebegin(profile* profile)
{
#if defined(RELEASE_BUILD)

#else

#endif
}

void profileend(profile* profile)
{
    logmsg("profile end: %s\n", profile->getstring());

}
#define PROFILE_BEGIN(NAME) beginProfile(name,)
#define profile_scoped() \
profile __timer__{__func__, &profilebegin, &profileend}

void func1()
{
    profile_scoped();
    logmsg("func1\n");
}
void testprofile()
{
    logmsg("===========================\n");
    func1();
    //func2();
    logmsg("===========================\n");
}

#if defined(RELEASE_BUILD)
    #define PROFILE() profilebegin();
#elif defined(FINAL_BUILD)
    #define PROFILE()
#endif