#include "printfc.h"

#ifdef __cplusplus

extern "C"

{
	
#endif

int printfc(ForeColor fc, const char* format_str, ...)
{
	int len = 0;
#ifndef WIN32
	printf("\e[%dm", fc);
#else
	CONSOLE_SCREEN_BUFFER_INFO oldInfo = {0};
	HANDLE hStd = ::GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStd != INVALID_HANDLE_VALUE && GetConsoleScreenBufferInfo(hStd, &oldInfo))
	{
		SetConsoleTextAttribute(hStd, fc);
#endif
	
		va_list p_list;
		va_start(p_list, format_str);
		len = vprintf(format_str, p_list);
		va_end(p_list);

#ifndef WIN32
		printf("\e[0m");//关闭所有属性
#else
		SetConsoleTextAttribute(hStd, oldInfo.wAttributes);
	}
#endif

	return len;
}

int printfbc(ForeColor fc, BackColor bc, const char* format_str, ...)
{
	int len = 0;
#ifndef WIN32
	static char text[MAX_STR_LEN] = {0};

	memset(text, 0, sizeof(text));

	va_list p_list;
	va_start(p_list, format_str);
	len = vsnprintf(text, sizeof(text), format_str, p_list);
	va_end(p_list);

	const char *split = "\n";
	char *p = strtok(text, split);
	bool last_is_lf = (text[len-1] == '\n'); 
	while(p != NULL)
	{ 
		printf("\e[%d;%dm%s\e[0m", fc, bc, p); 
		p = strtok(NULL, split);

		if (p != NULL || last_is_lf) printf("\n");
	}
#else
	CONSOLE_SCREEN_BUFFER_INFO oldInfo = {0};
	HANDLE hStd = ::GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStd != INVALID_HANDLE_VALUE && GetConsoleScreenBufferInfo(hStd, &oldInfo))
	{
		SetConsoleTextAttribute(hStd, fc|bc);
		
		va_list p_list;
		va_start(p_list, format_str);
		len = vprintf(format_str, p_list);
		va_end(p_list);
		
		SetConsoleTextAttribute(hStd, oldInfo.wAttributes);
	}
#endif
	
	return len;
}

#ifdef __cplusplus

}; //end of extern "C" {

#endif



