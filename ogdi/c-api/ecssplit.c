#include "ecs.h"

/* 
   -------------------------------------------------
  
   ecs_freeSplitURL: deallocate all the string used in 
   SplitURL operation.

   IN/OUT: 
      type: 
      machine:
      path:    the three string to deallocate

   -------------------------------------------------
   */

void ecs_freeSplitURL(type,machine,path)
     char **type;
     char **machine;
     char **path;
{
  if (*type != NULL) {
    free(*type);
    *type = NULL;
  }
  if (*machine != NULL) {
    free(*machine);
    *machine = NULL;
  }
  if (*path != NULL) {
    free(*path);
    *path = NULL;
  }
}

/* 
   -------------------------------------------------
  
   ecs_GetRegex: Allocate and set a string with the
   values contained in the regex.

   IN: 
      ecs_regexp *reg: A pointer to ecs_regexp structure
         (initialize in ecs_SplitURL).
      int index: Index of the table contained in ecs_regexp
   OUT:
      char **chaine: String returned value
      return int: Error code
          TRUE: success
          FALSE: failure

   -------------------------------------------------
   */

int ecs_GetRegex(reg,index,chaine)
     ecs_regexp *reg;
     int index;
     char **chaine;
{
  int chaine_len;

  chaine_len = reg->endp[index] - reg->startp[index] ;
  *chaine = (char *) malloc(chaine_len+1);
  if (*chaine ==NULL)
    return FALSE;
  strncpy(*chaine,reg->startp[index],chaine_len);
  (*chaine)[chaine_len] = '\0';
  return TRUE;
}

/* 
   -------------------------------------------------
  
   ecs_SplitURL: Extract information from the URL
   and return it in the arguments.

   IN: 
      char *url: This string contain the URL

   OUT:
      machine: Machine addresses contain in the URL. If NULL,
               the server is local
      server:  The server type of the DLL to load
      path:    The string used by the dynamic database library to
               set the database server. Specific to each kind of
	       server.
      return int: A error message
          TRUE: success
          FALSE: failure

   -------------------------------------------------
   */

int ecs_SplitURL(url,machine,server,path)
     char *url;
     char **machine;
     char **server;
     char **path;
{
  static int compiled = 0;
  static ecs_regexp *local,*remote;
  int msg;

  if (!compiled) {
    remote = EcsRegComp("gltp://([0-9a-zA-Z\\.\\-]+)/([0-9a-zA-Z\\.]+)(.*)");
    local = EcsRegComp("gltp:/([0-9a-zA-Z\\.]+)(.*)");
    compiled = 1;
  }

  *machine = NULL;
  *server = NULL;
  *path = NULL;

  if (strncmp(url,"gltp://",7) != 0) {
    if (EcsRegExec(local,url,NULL) == 0)
      return FALSE;
    if (((msg = ecs_GetRegex(local,1,server)) == FALSE) ||
	((msg = ecs_GetRegex(local,2,path)) == FALSE)) {
      ecs_freeSplitURL(machine,server,path);
      return msg;
    }
  } else {
    if (EcsRegExec(remote,url,NULL) == 0)
      return FALSE;
    if (((msg = ecs_GetRegex(remote,1,machine)) == FALSE) ||
	((msg = ecs_GetRegex(remote,2,server)) == FALSE) ||
 	((msg = ecs_GetRegex(remote,3,path)) == FALSE)) {
      ecs_freeSplitURL(machine,server,path);
      return msg;
    }
  }
							 
  return TRUE;
}


