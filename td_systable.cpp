/* ******************************************************************** **
** @@ td_systable
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  : All necessary include files (tci.h) and import library (tci.lib)
** @  Notes  : are installed with TCI SDK package into corresponding subdirectories.
** ******************************************************************** */

/* ******************************************************************** **
**                uses pre-compiled headers
** ******************************************************************** */

/* ******************************************************************** **
**                uses pre-compiled headers
** ******************************************************************** */

#include "stdafx.h"

#include <stdlib.h>
#include <stdio.h>

#include "tci.h"
#include "tberror.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef NDEBUG
#pragma optimize("gsy",on)
#pragma comment(linker,"/FILEALIGN:512 /MERGE:.rdata=.text /MERGE:.data=.text /SECTION:.text,EWR /IGNORE:4078")
#endif

/* ******************************************************************** **
** @@                   internal defines
** ******************************************************************** */

#define TD_DB_NAME            "TECDOC_CD_3_2015@localhost:2024"
#define TD_TB_LOGIN           "tecdoc"
#define TD_TB_PASSWORD        "tcd_error_0"

/* ******************************************************************** **
** @@                   internal prototypes
** ******************************************************************** */

/* ******************************************************************** **
** @@                   external global variables
** ******************************************************************** */

extern DWORD      dwKeepError = 0;

/* ******************************************************************** **
** @@                   static global variables
** ******************************************************************** */
                           
static TCIEnvironment*        pEnv  = NULL;
static TCIError*              pErr  = NULL;
static TCIConnection*         pConn = NULL;
static TCIStatement*          pStmt = NULL;
static TCIResultSet*          pRes  = NULL;
static TCITransaction*        pTa   = NULL;

static const char*   _pszTable = "systable.csv";

static FILE*         _pOut = NULL;

/* ******************************************************************** **
** @@                   real code
** ******************************************************************** */

/* ******************************************************************** **
** @@ AllocationError()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

static void AllocationError(char* what)
{
   printf("Can't allocate %s\n",what);

   if (pEnv)
   {
      TCIFreeEnvironment(pEnv);
   }

   exit(1);
}

/* ******************************************************************** **
** @@ Init()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

static void Init()
{
   if (TCIAllocEnvironment(&pEnv))
   {
      AllocationError("environment handle");
   }

   if (TCIAllocError(pEnv,&pErr))
   {
      AllocationError("error handle");
   }

   if (TCIAllocTransaction(pEnv,pErr,&pTa))
   {
      AllocationError("transaction handle");
   }

   if (TCIAllocConnection(pEnv,pErr,&pConn))
   {
      AllocationError("connection handle");
   }

   if (TCIAllocStatement(pConn,pErr,&pStmt))
   {
      AllocationError("statement handle");
   }

   if (TCIAllocResultSet(pStmt,pErr,&pRes))
   {
      AllocationError("resultset handle");
   }
}

/* ******************************************************************** **
** @@ Cleanup()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

static void Cleanup()
{
   TCIFreeResultSet(pRes);
   TCIFreeStatement(pStmt);
   TCIFreeConnection(pConn);
   TCIFreeTransaction(pTa);
   TCIFreeError(pErr);
   TCIFreeEnvironment(pEnv);
}

/* ******************************************************************** **
** @@ TBEerror()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

static TCIState TBEerror(TCIState rc)
{
   if (rc && (TCI_NO_DATA_FOUND != rc))
   {
      TCIState    erc = TCI_SUCCESS;

      char     errmsg[1024];
      char     sqlcode[6];

      Error    tberr = E_NO_ERROR;

      sqlcode[5] = 0;

      erc = TCIGetError(pErr,1,1,errmsg,sizeof(errmsg),&tberr,sqlcode);

      if (erc)
      {
         erc = TCIGetEnvironmentError(pEnv,1,errmsg,sizeof(errmsg),&tberr,sqlcode);

         if (erc)
         {
            // Error !
            ASSERT(0);
            printf("Can't get error info for error %d (reason: error %d)\n",rc,erc);
            exit(rc);
         }
      }

      // Error !
      ASSERT(0);
      printf("Transbase Error %d (SQLCode %s):\n%s\n",tberr,sqlcode,errmsg);

      exit(rc);
   }

   return rc;
}

/* ******************************************************************** **
** @@ ShowHelp()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

static void ShowHelp()
{
   const char pszCopyright[] = "-*-   td_systable 1.0  *   Copyright (c) Gazlan, 2015   -*-";
   const char pszDescript [] = "TECDOC_CD_3_2015 DB SysTable dumper";
   const char pszE_Mail   [] = "complains_n_suggestions direct to gazlan@yandex.ru";

   printf("%s\n\n",pszCopyright);
   printf("%s\n\n",pszDescript);
   printf("Usage: td_systable.com\n");
   printf("%s\n",pszE_Mail);
}

/* ******************************************************************** **
** @@ main()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

int main(int argc,char** argv)
{           
   if (argc > 1)
   {
      ShowHelp();
      return 0;
   }

   if (argc == 2)
   {
      if ((!strcmp(argv[1],"?")) || (!strcmp(argv[1],"/?")) || (!strcmp(argv[1],"-?")) || (!stricmp(argv[1],"/h")) || (!stricmp(argv[1],"-h")))
      {
         ShowHelp();
         return 0;
      }
   }

   struct TD_SYSTABLE
   {
      char*          _pszName;        // CHAR(*)
      Int4           _iOwner;         // INTEGER
      char*          _pszType;        // CHAR(*)
      Int4           _iSegNo;         // INTEGER
      Int4           _iColNo;         // INTEGER
      TCITimestamp   _Date;           // DATETIME[YY:MS]
      Int2           _iCluster;       // SMALL INT
      Int4           _iVersion;       // INTEGER
      char*          _pszIndexType;   // CHAR(*)
   };
   
   _pOut = fopen(_pszTable,"wt");

   if (!_pOut)
   {
      // Error !
      ASSERT(0);
      printf("Err: Can't open [%s] for write.\n",_pszTable);
      return 0;
   }

   TD_SYSTABLE    tdSysTable;

   memset(&tdSysTable,0,sizeof(TD_SYSTABLE));

   Init();

   TBEerror(TCIConnect(pConn,TD_DB_NAME));
   TBEerror(TCILogin(pConn,TD_TB_LOGIN,TD_TB_PASSWORD));
   
   // Select TecDoc tables only !
   TBEerror(TCIExecuteDirectA(pRes,"SELECT * FROM SYSTABLE WHERE OWNER=2 ORDER BY TNAME",1,0));

   int      iRow  = 0;

   Int2     Indicator = 0;

   TCIState    Err;

   // 1. Name
   TBEerror(TCIBindColumnA(pRes,1,&tdSysTable._pszName,sizeof(Int4),NULL,TCI_C_SCHARPTR,&Indicator));
   // 2. Owner
   TBEerror(TCIBindColumnA(pRes,2,&tdSysTable._iOwner,sizeof(Int4),NULL,TCI_C_INT4,&Indicator));
   // 3. Type
   TBEerror(TCIBindColumnA(pRes,3,&tdSysTable._pszType,sizeof(Int4),NULL,TCI_C_SCHARPTR,&Indicator));
   // 4. SegNo
   TBEerror(TCIBindColumnA(pRes,4,&tdSysTable._iSegNo,sizeof(Int4),NULL,TCI_C_INT4,&Indicator));
   // 5. ColNo
   TBEerror(TCIBindColumnA(pRes,5,&tdSysTable._iColNo,sizeof(Int4),NULL,TCI_C_INT4,&Indicator));
   // 6. Date
   TBEerror(TCIBindColumnA(pRes,6,&tdSysTable._Date,sizeof(TCITimestamp),NULL,TCI_C_TIMESTAMP,&Indicator));
   // 7. Cluster
   TBEerror(TCIBindColumnA(pRes,7,&tdSysTable._iCluster,sizeof(Int2),NULL,TCI_C_INT2,&Indicator));
   // 8. Version
   TBEerror(TCIBindColumnA(pRes,8,&tdSysTable._iVersion,sizeof(Int4),NULL,TCI_C_INT4,&Indicator));
   // 9. IndexType
   TBEerror(TCIBindColumnA(pRes,9,&tdSysTable._pszIndexType,sizeof(Int4),NULL,TCI_C_SCHARPTR,&Indicator));

   fprintf(_pOut,"\"##\", \"TNAME\", \"OWNER\", \"TTYPE\", \"SEGNO\", \"COLNO\", \"DATE\", \"CLUSTER\", \"VERSION\", \"INDEXTYPE\"\n");

   while ((Err = TCIFetchA(pRes,1,TCI_FETCH_NEXT,0)) == TCI_SUCCESS) 
   { 
      fprintf(_pOut,"%d",++iRow);

      // 1. Name
      fprintf(_pOut,", \"%s\"",tdSysTable._pszName);
      // 2. Owner
      fprintf(_pOut,", %lu",tdSysTable._iOwner);
      // 3. Type
      fprintf(_pOut,", \"%s\"",tdSysTable._pszType);
      // 4. SegNo
      fprintf(_pOut,", %lu",tdSysTable._iSegNo);
      // 5. ColNo
      fprintf(_pOut,", %lu",tdSysTable._iColNo);
      
      // 6. Date
      CString     sTimeStamp = _T("");

      sTimeStamp.Format("%04d-%02d-%02d %02d:%02d:%02d",tdSysTable._Date.year,tdSysTable._Date.month,tdSysTable._Date.day,tdSysTable._Date.hour,tdSysTable._Date.minute,tdSysTable._Date.second);

      fprintf(_pOut,", \"%s\"",sTimeStamp);
      
      // 7. Cluster
      fprintf(_pOut,", %lu",tdSysTable._iCluster);
      // 8. Version
      fprintf(_pOut,", %lu",tdSysTable._iVersion);
      // 9. IndexType
      fprintf(_pOut,", \"%s\"",tdSysTable._pszIndexType);

      fprintf(_pOut,"\n");
   } 

   if (Err != TCI_NO_DATA_FOUND) 
   {
     TBEerror(Err); 
   }
   
   TBEerror(TCICloseA(pRes));

   TBEerror(TCICloseA(pRes));
   TBEerror(TCILogout(pConn));
   TBEerror(TCIDisconnect(pConn));

   Cleanup();

   fclose(_pOut);
   _pOut = NULL;

   return 0;
}
