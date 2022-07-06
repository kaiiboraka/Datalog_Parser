#ifndef DEBUGGER_H
#define DEBUGGER_H
/// Comment me out to disable all debug messages
//#define DEBUG

#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str << endl; } while( false )
#define ENABLED (true)
#else
#define DEBUG_MSG(str) do { } while ( false )
#define ENABLED (false)
#endif
struct Debugger
{
	static const bool enabled = ENABLED;
};

/// obtained from : https://stackoverflow.com/questions/3371540/c-enable-disable-debug-messages-of-stdcouts-on-the-fly

#endif