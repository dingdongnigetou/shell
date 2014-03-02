/*
 * (C) 2014 HuangJinDong
 *
 * src/errorprocess.c
 * 
 */

#include "errorprocess.h"
#include "globals.h"
#include <stdio.h>
#include <errno.h>

int   errno;             /* from errno.h to finger out the error */

void error_process()
{
	switch(errno)
	{
	case E2BIG:fprintf(stderr, "ddsh: Argument list too long\n");
		   break;
	case EACCES:fprintf(stderr, "ddsh: %s: Permission denied\n", commands);
		    break;
	case EBUSY:fprintf(stderr, "ddsh: Device or resource busy\n");
		   break;
	case EEXIST:fprintf(stderr, "ddsh: File exists\n");
		    break;
	case EFBIG:fprintf(stderr, "ddsh: File too large\n");
		   break;
	case EINVAL:fprintf(stderr, "ddsh: Invalid argument\n");
		    break;
	case EIO:fprintf(stderr, "ddsh: Input/output error\n");
		 break;
	case EISDIR:fprintf(stderr, "ddsh: %s: Is a dirextory\n", commands);
		    break;
	case ENODEV:fprintf(stderr, "ddsh: No such device\n");
		    break;
	case ENOENT:fprintf(stderr, "ddsh: %s: command not found\n", commands);
		    break;
	}

	/* resume */
	errno = 0;
}

