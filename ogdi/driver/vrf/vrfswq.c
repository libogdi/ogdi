/******************************************************************************
 *
 * Component: OGDI VRF Driver
 * Purpose: Implements VPF query capability based on SWQ in a manner similar
 *          to the vpfquery.c code distributed with vpflib. 
 * 
 ******************************************************************************
 * Copyright (C) 1995 Logiciels et Applications Scientifiques (L.A.S.) Inc
 * Permission to use, copy, modify and distribute this software and
 * its documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appear in all copies, that
 * both the copyright notice and this permission notice appear in
 * supporting documentation, and that the name of L.A.S. Inc not be used 
 * in advertising or publicity pertaining to distribution of the software 
 * without specific, written prior permission. L.A.S. Inc. makes no
 * representations about the suitability of this software for any purpose.
 * It is provided "as is" without express or implied warranty.
 ******************************************************************************
 *
 * $Log$
 * Revision 1.1  2001-06-20 21:49:16  warmerda
 * New
 *
 */

#include "ecs.h"
#include "vrf.h"
#include "swq.h"

#ifndef __LINKLIST_H__
#include "linklist.h"
#endif
#ifndef _VPFTABLE_H_
#include "vpftable.h"
#endif
#ifndef __SET_H__
#include "set.h"
#endif
#ifndef __STRFUNC_H__
#include "strfunc.h"
#endif
#ifndef _MACHINE_
#include "machine.h"
#endif

typedef struct {
    row_type	row;
    vpf_table_type  table;
} evaluator_info;

/************************************************************************/
/*                         vrf_swq_evaluator()                          */
/*                                                                      */
/*      Evaluate a single operation from the WHERE expression on a      */
/*      row from the VRF table.                                         */
/************************************************************************/

int vrf_swq_evaluator( swq_field_op *op, void *raw_info )

{
    int32 lval, count;
    short sval;
    float fval;
    char *tptr;

    evaluator_info *info = (evaluator_info *) raw_info;
    row_type	row = info->row;
    vpf_table_type  table = info->table;

    if (table.header[op->field_index].count != 1) 
        return FALSE;

    if( table.header[op->field_index].type == 'T' )
    {
        int	ret_result;

        tptr = (char *)get_table_element( op->field_index, row, table,
                                          NULL, &count );

        if( op->operation == SWQ_EQ )
            ret_result = (strcasecmp(tptr,op->string_value) == 0);
        else
            ret_result = (strcasecmp(tptr,op->string_value) != 0);
            
        xvt_free(tptr);

        return ret_result;
    }
    else
    {
        if( table.header[op->field_index].type == 'S' )
        {
            get_table_element( op->field_index, row, table, &sval, &count );
            fval = sval;
        }
        else if( table.header[op->field_index].type == 'I' )
        {
            get_table_element( op->field_index, row, table, &lval, &count );
            fval = lval;
        }
        else
        {
            get_table_element( op->field_index, row, table, &fval, &count );
        }

        switch( op->operation )
        {
          case SWQ_EQ:
            return fval == op->float_value;

          case SWQ_NE:
            return fval != op->float_value;

          case SWQ_GT:
            return fval > op->float_value;

          case SWQ_LT:
            return fval < op->float_value;

          case SWQ_GE:
            return fval >= op->float_value;

          case SWQ_LE:
            return fval <= op->float_value;
            
          default:
            return FALSE;
        }
    }
}


/************************************************************************
 *                            query_table2()                            
 *
 *     This function returns the set of selected rows of a VPF table
 *     based upon the evaluation of the given selection expression string.
 *
 *     see swq.h/swq.c for details on the expression syntax.
 *
 *   Parameters:
 *
 *    expression <input>==(char *) selection expression string.
 *    table      <input>==(vpf_table_type) VPF table structure.
 *    return    <output>==(set_type) set of selected rows.
 ************************************************************************/

set_type query_table2( char *expression, vpf_table_type table )
{
   register int32 i, ipos;
   set_type select_set;

   swq_expr *expr;
   const char *error;
   int	nfields;
   char **fieldname;
   swq_field_type *fieldtype;
   evaluator_info ev_info;

   select_set = set_init (table.nrows);

/* -------------------------------------------------------------------- */
/*      If the expression is "*" then just turn on all members of       */
/*      select_set and return.                                          */
/* -------------------------------------------------------------------- */
   if (strcmp (expression, "*") == 0)
   {
       set_on(select_set);
       return select_set;
   }

/* -------------------------------------------------------------------- */
/*      Prepare the field list.                                         */
/* -------------------------------------------------------------------- */
   nfields = (int32)table.nfields;

   fieldname = (char**) malloc(nfields * sizeof(char *));
   fieldtype = (swq_field_type *) malloc(nfields * sizeof(swq_field_type));

   for (i=0; i < nfields; i++)
   {
       fieldname[i] = (char *) table.header[i].name;
       if( table.header[i].type == 'T' )
           fieldtype[i] = SWQ_STRING;
       else if( table.header[i].type == 'F' )
           fieldtype[i] = SWQ_FLOAT;
       else if( table.header[i].type == 'I' || table.header[i].type == 'S' )
           fieldtype[i] = SWQ_INTEGER;
       else
           fieldtype[i] = SWQ_OTHER;
   }
   
/* -------------------------------------------------------------------- */
/*      Compile the WHERE expression.                                   */
/* -------------------------------------------------------------------- */
   error = swq_expr_compile( expression, nfields, fieldname, fieldtype, 
                             &expr );

   if ( error != NULL || expr == NULL ) 
       return select_set;

/* -------------------------------------------------------------------- */
/*      Process the table, one record at a time.                        */
/* -------------------------------------------------------------------- */
   if (table.storage == DISK)
   {
       ipos = index_pos (1L, table);
       fseek( table.fp, ipos, SEEK_SET );
   }

   ev_info.table = table;

   for (i=1;i<=table.nrows;i++) {

      if (table.storage == DISK)
          ev_info.row = read_next_row(table);
      else
          ev_info.row = get_row( i, table );

      if( swq_expr_evaluate( expr, vrf_swq_evaluator, (void *) &ev_info ) )
          set_insert( i, select_set );
   }

/* -------------------------------------------------------------------- */
/*      Cleanup                                                         */
/* -------------------------------------------------------------------- */
   free( fieldtype );
   free( fieldname );
   swq_expr_free( expr );

   return select_set;
}
