#ifndef _GE_TRACE_H_
#define _GE_TRACE_H_
#ifdef __cplusplus
extern "C" {
#endif
	static void dummy(char* format,...){}
#ifdef TRACE_ENABLE
#define GETRACE TraceOut("Trace at File:%s Line:%d\n",__FILE__,__LINE__)
#define TRACE_INIT TraceInit()
#define TRACE_CLOSE TraceClose()
#define TRACE_OUT TraceOut
#else
#define GETRACE 
#define TRACE_INIT 
#define TRACE_CLOSE 
#define TRACE_OUT dummy
#endif
	int TraceInit();
	int TraceClose();
unsigned long TraceOut(char* format,...);
#ifdef __cplusplus
}
#endif
#endif
