/*
 * $Id: assert.h,v 1.1 2005/12/21 19:48:23 itix Exp $
 *
 * :ts=8
 */

/* IMPORTANT: If DEBUG is redefined, it must happen only here. This
 *            will cause all modules to depend upon it to be rebuilt
 *            by the smakefile (that is, provided the smakefile has
 *            all the necessary dependency lines in place).
 */

/*#define DEBUG*/

/****************************************************************************/

#ifdef ASSERT
#undef ASSERT
#endif	/* ASSERT */

#ifdef DEBUG
 void _ASSERT(int x,const char *xs,const char *file,int line,const char *function);
 void _SHOWVALUE(unsigned long value,int size,const char *name,const char *file,int line);
 void _SHOWSTRING(const char *string,const char *name,const char *file,int line);
 void _SHOWMSG(const char *msg,const char *file,int line);
 void _ENTER(const char *file,int line,const char *function);
 void _LEAVE(const char *file,int line,const char *function);
 void _RETURN(const char *file,int line,const char *function,unsigned long result);

 #ifdef __SASC
  #define ASSERT(x)	_ASSERT((int)(x),#x,__FILE__,__LINE__,__FUNC__);
  #ifdef ASSERT_CALL_TRACING
   #define ENTER()	_ENTER(__FILE__,__LINE__,__FUNC__)
   #define LEAVE()	_LEAVE(__FILE__,__LINE__,__FUNC__)
   #define RETURN(r)	_RETURN(__FILE__,__LINE__,__FUNC__,(unsigned long)r)
  #else
   #define ENTER()	((void)0)
   #define LEAVE()	((void)0)
   #define RETURN(r)	((void)0)
  #endif /* ASSERT_CALL_TRACING */
 #else
   #define ASSERT(x)	_ASSERT((int)(x),#x,__FILE__,__LINE__,"unknown_function");
   #define ENTER()	((void)0)
   #define LEAVE()	((void)0)
   #define RETURN(r)	((void)0)
 #endif	/* __SASC */

 #ifdef ASSERT_REPORTS
  #define SHOWVALUE(v)	_SHOWVALUE((unsigned long)(v),sizeof(v),#v,__FILE__,__LINE__);
  #define SHOWSTRING(s)	_SHOWSTRING((const char *)(s),#s,__FILE__,__LINE__);
  #define SHOWMSG(s)	_SHOWMSG((const char *)(s),__FILE__,__LINE__);
 #else
  #define SHOWVALUE(ignore)	((void)0)
  #define SHOWSTRING(ignore)	((void)0)
  #define SHOWMSG(ignore)	((void)0)
 #endif /* ASSERT_REPORTS */
#else
 #define ASSERT(ignore)		((void)0)
 #define SHOWVALUE(ignore)	((void)0)
 #define SHOWSTRING(ignore)	((void)0)
 #define SHOWMSG(ignore)	((void)0)
 #define ENTER()		((void)0)
 #define LEAVE()		((void)0)
 #define RETURN(r)		((void)0)
#endif /* DEBUG */
