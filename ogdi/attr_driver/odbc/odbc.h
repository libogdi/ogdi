/*********************************************************************

  CSOURCE_INFORMATION
  
  NAME
     odbc.h

  DESCRIPTION
     Header file of the odbc attribute driver
  END_DESCRIPTION

  END_CSOURCE_INFORMATION

  Copyright (c) 1997 Logiciels et Applications Scientifiques (L.A.S.) Inc.
  Il est strictement interdit de publier ou de devoiler le contenu de ce
  programme sans avoir prealablement obtenu la permission de L.A.S. Inc.
  
  ********************************************************************/

#ifndef ODBCDRIVER
#define ODBCDRIVER

#include "ecs.h"
#include "sql.h"
#include "sqlext.h"

/*********************************************************************

  STRUCTURE_INFORMATION
  
  NAME
     PrivateODBCInfo

  DESCRIPTION
     The private information of this attribute driver. 
  END_DESCRIPTION

  ATTRIBUTES
     HSTMT odbcSqlInfo: SQL request handler
     int nb_field: Field quantity in the odbcSqlInfo structure
     int isLinked: Indicate if a link with odbc is active
     int isSelected: Indicate if the current request get something in it
     char *attributes: The attribute list.
  END_ATTRIBUTES

  END_STRUCTURE_INFORMATION

  ********************************************************************/


typedef struct {
  SQLHDBC odbcHandle;
  SQLHSTMT odbcSqlInfo;
  int nb_field;
  int isLinked;
  int isSelected;
  char *attributes;
} PrivateODBCInfo;

#endif






