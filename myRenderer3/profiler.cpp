//#define PROFILE_CAPTURE(name)
//#define PROFILE_END()
//#define PROFILE_FUNCTION()
//#define PROFILE_SCOPED(name)
//
//
////each profiling blocks will store the CPU time in milli - seconds
////then you should have an option to dump out the profiling results to a text file
////for the past ~50 frames or so
//
//#define min(X, Y)  ((X) < (Y) ? (X) : (Y))
//PROFILE_CAPTURE(HeavyBlockOfCode);
//// Perform heavy CPU computation here
//PROFILE_END();


void function() 
{
    //PROFILE_CAPTURE(name);
    // log  this name
    // init timer
    // update time stamp

    //HeavyBlockOfCode

    //PROFILE_END
    //update time stamp
    // getTimerElapsedUs function
    // log time in milliseconds time
}