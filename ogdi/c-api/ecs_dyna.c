#include "ecs.h"
#ifdef _LINUX
#include <dlfcn.h>
#endif


/* 
   -------------------------------------------------
  
   ecs_OpenDynamicLib: Open a dynamic link in a system

   IN: 
      libname: A string with the dynamic library file name.
      The dynamic library file could be without file extension.
   OUT: 
      void *: A handle to a new link to a dynamic link. If NULL,
      the dynamic link failed.

   -------------------------------------------------
   */

void *ecs_OpenDynamicLib(libname)
     char *libname;
{
  char *temp;
#ifdef _WINDOWS
  static HINSTANCE handle;

  handle = LoadLibrary(libname);
  if ((int) handle <= (int) HINSTANCE_ERROR) {
    /* Try with the .dll extension */

    if ((temp = (char *) malloc(strlen(libname)+5)) == NULL)
      return NULL;
    strcpy(temp,libname);
    strcat(temp,".dll");
        
    handle = LoadLibrary(temp);
    free(temp);
    if ((int) handle <= (int) HINSTANCE_ERROR) {
      return NULL;
    } else {
      return (void *) handle;
    }
  } else {
    return (void *) handle;
  }
#else
  void *handle;

  handle = dlopen(libname,RTLD_LAZY);
  if (handle == NULL) {
    /* Try with the .so extension */

    if ((temp = (char *) malloc(strlen(libname)+7)) == NULL)
      return NULL;
    strcpy(temp,"lib");
    strcat(temp,libname);
    strcat(temp,".so");

    handle = dlopen(temp,RTLD_LAZY);
    free(temp);
  }
  return handle;

#endif

}

/* 
   -------------------------------------------------
   
   ecs_GetDynamicLibFunction: Initialise a pointer to
   a function in the dynamic library.

   IN: 
      handle      : A link to dynamic library initialized by
                    ecs_OpenDynamicLib
      functionname: A string with the function name

   OUT: 
      void *: A pointer to the function. If NULL, an error
      append during this operation.

   -------------------------------------------------
   */

void *ecs_GetDynamicLibFunction(handle,functionname)
     void *handle;
     char *functionname;
{
  void *function;
#ifndef _WINDOWS
  char *temp;
#endif

  /* If the handle is NULL, return NULL */
  if (handle == NULL)
    return NULL;

#ifdef _WINDOWS
  function = (void *) GetProcAddress((HINSTANCE) handle, functionname);
#else

  function = (void *) dlsym(handle, functionname);
  if (function == NULL) {
    /* try with an underscore before the function name */
    temp = (char *) malloc(strlen(functionname)+2);
    if (temp == NULL)
      return NULL;
    strcpy(temp,"_");
    strcat(temp,functionname);
    function = (void *) dlsym(handle, functionname);
    free(temp);
  }
#endif

  return (void *) function;
}

/* 
   -------------------------------------------------
   
   ecs_CloseDynamicLib: Open a dynamic link

   IN: 
      handle      : A link to dynamic library initialized by
                    ecs_OpenDynamicLib

   -------------------------------------------------
   */

void ecs_CloseDynamicLib(handle)
     void *handle;
{
  /* If the handle is NULL, end this operation */
  if (handle == NULL)
    return;

#ifdef _WINDOWS
  FreeLibrary((HINSTANCE) handle);
#else
  dlclose(handle);
#endif

  handle = NULL;
  return;
}

