/* ==== pthread_attr.c =======================================================
 * Copyright (c) 1993 by Chris Provenzano, proven@athena.mit.edu
 *
 * Description : Pthread attribute functions.
 *
 *  1.00 93/11/04 proven
 *      -Started coding this file.
 */

/*
 * Copyright (c) 1993 by Chris Provenzano and contributors, proven@mit.edu
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *  This product includes software developed by Chris Provenzano,
 *	the University of California, Berkeley, and contributors.
 * 4. Neither the name of Chris Provenzano, the University, nor the names of
 *	  contributors may be used to endorse or promote products derived
 *	  from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY CHRIS PROVENZANO AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL CHRIS PROVENZANO, THE REGENTS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "pthread.h"
#include <errno.h>

/* Currently we do no locking, should we just to be safe? CAP */
/* ==========================================================================
 * pthread_attr_init()
 */
int pthread_attr_init(pthread_attr_t *attr)
{
	memcpy(attr, &pthread_default_attr, sizeof(pthread_attr_t));
	return(OK);
}

/* ==========================================================================
 * pthread_attr_destroy()
 */
int pthread_attr_destroy(pthread_attr_t *attr)
{
	return(OK);
}

/* ==========================================================================
 * pthread_attr_getstacksize()
 */
int pthread_attr_getstacksize(pthread_attr_t *attr, size_t * stacksize)
{
	*stacksize = attr->stacksize_attr;
	return(OK);
}

/* ==========================================================================
 * pthread_attr_setstacksize()
 */
int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize)
{
	if (stacksize >= PTHREAD_STACK_MIN) {
		attr->stacksize_attr = stacksize;
		return(OK);
	}
	return(EINVAL);
}

/* ==========================================================================
 * pthread_attr_getstackaddr()
 */
int pthread_attr_getstackaddr(pthread_attr_t *attr, void ** stackaddr)
{
	*stackaddr = attr->stackaddr_attr;
	return(OK);
}

/* ==========================================================================
 * pthread_attr_setstackaddr()
 */
int pthread_attr_setstackaddr(pthread_attr_t *attr, void * stackaddr)
{
	attr->stackaddr_attr = stackaddr;
	return(OK);
}
