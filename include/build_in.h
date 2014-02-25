/*
 * include/build_in.h
 *
 * (C) 2014 HuangJinDong
 *
 * the prototype of functions
 * 
 */

#ifndef _BUILDIN_
#define _BUILDIN_

#include <stdio.h>

/* which build in command, NO -> not build in */
typedef enum{
	NO, CD, PWD, EXIT, HISTORY 
}BuildInCommand;

/*
 * if it is build in command then return which
 * one, else return NO.
 *
 */
int isbuildin(char *command);

/* run build in command called buildin */
void runbuildin(int buildin);

/* toggle current directory */
void do_cd();

/* display current directory */
void do_pwd();

/* exit current shell with exit number */
void do_exit();

/* read .history which contains historical commands */
void do_history();

#endif /* _BUILDIN_ */

