#ifndef _GE_TRACE_H_
#define _GE_TRACE_H_
#define GETRACE TraceOut("Trace at File:%s Line:%d\n",__FILE__,__LINE__)
#define TRACE_INIT TraceInit()
#define TRACE_CLOSE TraceClose()
#define TRACE_OUT TraceOut
int TraceInit();
int TraceClose();
unsigned long TraceOut(char* format,...);
#endif
