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

/*
 * if it is build in command then return which
 * one, else return NO.
 *
 */
int isbuildin(char *command);

/* run build in command called buildin */
void runbuildin(int buildin);

#endif /* _BUILDIN_H_ */

