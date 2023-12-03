#ifndef _LOG_H_
#define _LOG_H_

#define INFO_STRING "[info]"
#define WARN_STRING "[warn]"
#define ERRO_STRING "[error]"

void log_info(char* string, ...);
void log_warn(char* string, ...);
void log_erro(char* string, ...);
#endif