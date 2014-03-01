/*
 * (C) 2014 HuangJinDong
 *
 * include/build_in.h
 *
 * The build-in commands interface for the ddsh 
 * 
 */

#ifndef _BUILDIN_H_
#define _BUILDIN_H_

/* which build in command, NO -> not build in */
typedef enum{
	NO, CD, PWD, EXIT, HISTORY 
}BuildInType;

/*
 * if it is build in command then return which
 * one, else return NO.
 *
 */
int isbuildin(char *s);

/* run build in command called buildin */
void runbuildin(BuildInType command);

#endif /* _BUILDIN_H_ */

