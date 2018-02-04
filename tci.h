/******************************************************** 

                      T r a n s B a s e / C D
  @(#) tci.h:   V7.1.2.21.3
      Project: 4.4208.1.215
      2015/08/03 11:17:40

  Copyright (c) 1995 - 
  Transaction Software GmbH
  D 81739 Munich 

 *********************************************************/

/* Module begin */
#ifndef _TCI_H
#define _TCI_H

#if defined(__cplusplus)
extern "C"
{
#endif
#if defined(_WIN32)
#define TBX_API __cdecl
#define TBADM_API __stdcall
#define TCI_API __stdcall
#else
#define TBX_API
#define TBADM_API
#define TCI_API
#endif
/******************************************************** 

                      T r a n s B a s e / C D
  @(#) tbx.h:   V7.1.2.21.3
      Project: 4.4208.1.215
      2015/08/03 11:17:40

  Copyright (c) 1995 - 
  Transaction Software GmbH
  D 81739 Munich 

 *********************************************************/

/* Module begin */
#ifndef _TBX_H
#define _TBX_H

#if defined(__cplusplus)
extern "C"
{
#endif
#if defined(_WIN32)
#define LONG_64BITS  __int64
#define TBX_API __cdecl
#define TBADM_API __stdcall
#define TCI_API __stdcall
#else
#define LONG_64BITS long long
#define TBX_API
#define TBADM_API
#define TCI_API
#endif
#if !defined(tb_errtxt)
#define tb_errtxt tb_errtxt_adr()
#endif
#ifndef _BASICS_H

#define _BASICS_H
typedef signed char Int1;
typedef unsigned char Uint1;
typedef signed short Int2;
typedef unsigned short Uint2;
typedef signed int Int4;
typedef unsigned int Uint4;
typedef long Long;
typedef unsigned long Ulong;
typedef Int4 Long4;
typedef Uint4 Ulong4;
typedef signed LONG_64BITS Int8;
typedef unsigned LONG_64BITS Uint8;
typedef volatile Uint4 TBSpinLock;


#define os_2_sizeof sizeof
#endif


#if defined(_WIN64)
#pragma pack(8)
#elif defined(_WIN32)
#pragma pack(1)
#endif



#define _1MB ((Uint4)0x00100000)
#define _1GB ((Uint4)0x40000000)


#define FILLER_1(d1) char d1;
#define FILLER_2(d1,d2) char d1,d2;
#define FILLER_3(d1,d2,d3) char d1,d2,d3;
#define FILLER_6(d1,d2,d3,d4,d5,d6) char d1,d2,d3,d4,d5,d6;
#define DB_TRANSBASE (0)
#define DB_ICSQLS (1)
#define DB_ICSQLU (2)

#define MAXERRLEN 4096

#define MAXQUERYSIZE 4096 /* actually no restrictions in */
                                /* Transbase. Constant supported for */
                                /* compatibility */
#define MAXTUPLESIZE (32768-96) /* 32K - 96, so tuple and page header fit in 32K page */
#define OLDMAXTUPLE 4000 /* for compatibility to old clients */
#define MAXATTRNO 256 /* must be multiple of 32 */

#define BBMAXATTRNO ((MAXATTRNO)+1) /* IK in tuple */

#define PARAMMODE_UNKNOWN 'U' /* Unknown */
#define PARAMMODE_IN 'I' /* In */
#define PARAMMODE_OUT 'O' /* Out */
#define PARAMMODE_INOUT 'B' /* Both */

#define MAXSTRINGSIZE MAXTUPLESIZE
#define MAXATTRSIZE MAXSTRINGSIZE

#define MAXIDENTSIZE 127
#define OLD_MAXIDENTSIZE 31
#define SL4 os_2_sizeof(Int4)
#define ALIGNED4_MAXIDENTSIZE ( ((MAXIDENTSIZE+1)+(SL4-1))/SL4*SL4)

/* session- and transaction-control */
#define UNDEF_STATE (1<<0)
#define TA_UNDEF UNDEF_STATE
#define TA_NOT_ACTIVE (1<<1)
#define TA_ACTIVE (1<<2)
#define TA_PREP (1<<3)
#define TA_COMMITTED (1<<4)
#define TA_ABORTED (1<<5)
#define PREFIX_SYSRESERVED_NAME "@@sys"
  /* prefix for all system generated constraintnames and
         catalog tables */
#define SIZE_PREFIX_SYSRESERVED_NAME 5

/* Some special type-definitions */
/* machine dependent integer definitions */


typedef Uint4 FilterMask;

typedef Uint4 Time4log;

typedef Int2 Attr_pt;
typedef int Error;
typedef Long4 Bno;
typedef Bno Sno;
typedef char Dev;

typedef Int4 Dataspace;
typedef Int2 Deltacounter; /*  delta mechanism for Retrieval DBs */
typedef Dataspace Volid;
#define VOL_UNDEF ((Volid)-1)
#define DSPACE_UNDEF VOL_UNDEF


typedef struct {
    Dataspace dummy;
    Dataspace dspaceno; /* actual cluster */
    char dspacename[ALIGNED4_MAXIDENTSIZE];
    Uint4 extension; /* actual extension */
} Dspaceinfo;
/* in Block 0 of romfiles and (x)deltafiles, this structure
   has information about dataspace/cluster and extensions */
typedef struct {
    Dspaceinfo dspaceinfo;
    Uint4 filetype; /* NODELTA / FULLDELTA /XORDELTA */
    Uint2 deltaact; /* 0 for TB_STD and original romfiles, 
               >0 for deltafiles and xordeltasfiles */
    Uint2 deltafrom; /* relevant for transitional deltas */
} RDfileinfo;
/* in Block 0 of romfiles and (x)deltafiles, this structure
   has information about cluster and extensions */

#define SNO_UNDEF ((Sno)-1)

/* transaction identifiers */
typedef Uint4 Sta_id;
typedef Int2 Taindex; /*  position of TA in Ta_array - also main number of bfimfile,
            need -1 for description of shared bfimfile;
            Attention: if increased to > 2 bytes, Ta_anchor page
            perhaps not works any more */



#define LLF(s) "%I64"#s
#define LLF2(w,s) "%"#w"I64"#s






/********   Coding of Types of attributes    **************/

#define TB__UNDEFTYPE (0) /* represents not existing type,
              don't change this code ! */
#define TB__TINYINT (5) /* represents type 'Tinyint' */
#define TB__SMALLINT (6) /* represents type 'Smallint' */
#define TB__INTEGER (1) /* represents type 'Integer' */
#define TB__NUMERIC (3) /* represents type 'Numeric' */
#define TB__FLOAT (7) /* represents type 'Float' */
#define TB__DOUBLE (2) /* represents type 'Double' */
#define TB__CHAR (4) /* represents type 'String' var/fix */
#define TB__DATETIME (8) /* represents type 'Datetime' */
#define TB__TIMESPAN (9) /* represents type 'Timespan' */
#define TB__MONEY (10) /* represents type 'Money' */
#define TB__BOOL (11) /* represents type 'Bool' */
#define TB__BINCHAR (12) /* represents type 'binary char' var/fix */
#define TB__BLOB (13) /* represents type 'Blob' */
#define TB__BITSS (14) /* represents type 'Bits' var/fix */
#define TB__NULLTYP (15) /* represents null values in optrees */

#define C_INT (16) /* represents C type 'int' */
#define C_UCHAR (17) /* represents C type 'unsigned char' */
#define C_USHORT (18) /* represents C type 'unsigned short' */
#define C_UINT (19) /* represents C type 'unsigned int' */
#define C_ULONG (20) /* represents C type 'ulong ' */
#define C_CHAR (21) /* represents C type 'char' */
#define C_SHORT (22) /* represents C type 'short' */
#define C_LONG (23) /* represents C type 'long' */
#define C_FLOAT (24) /* represents C type 'float' */
#define C_DOUBLE (25) /* represents C type 'double' */
#define STMTVAR (26) /* represents a statement variable,
               i.e. char* or char[] */
#define TB__BLOBNAME (27) /* represents type 'Blobname' */
#define TB__FILEREF (28) /* represents type 'FILEREF' */
#define TB__VARCHAR (29) /* represents type 'VARCHAR' */
#define TB__UBVALUE (30) /* represents type 'UBVALUE' */
#define TB__BITSS2 TB__UBVALUE
    /* internal bitstring type (for 
            surrogates), definition equivalent to 
            Ub_value ,
            type BITSS has 4-byte length field,
            type BITSS2 has 2-byte length field,
            */
#define TB__XML TB__BLOB
#define TB__BIGINT (31) /* represents type 'Bigint' */
#define C_INT8 (32) /* represents C type 'long long' */
#define C_UINT8 (33) /* represents C type 'ulong long' */
#define TB__CLOB (34) /* represents type 'Clob' */

/* !! Attention to "is_conv_type" */

#define TB__MAXTYPES (34) /* for macro iskerneltype */

#define TB__STRING TB__CHAR /* for compatibility */
#define TB__REAL TB__DOUBLE /* for compatibility */




#define TB__IKVALUE TB__INTEGER /* represents internal type 'Ik-Value' */



/****** National Language Parameters ****/

#define USA 10
#define EUR 11
#define ISO 12
#define TRB 20

#define TB__MS 0
#define TB__SS 1
#define TB__MI 2
#define TB__HH 3
#define TB__DD 4
#define TB__MO 5
#define TB__YY 6
#define TB__DAY 7
#define TB__WEEKDAY 8
#define TB__WEEK 9
#define TB__ISOWEEK 10
#define TB__QUARTER 11
#define TB__UNDEFRANGE 12


/******* modes for Blobdesc ****/
#define MMADR 0
#define FILENAME 1 /* filename is in locale codepage */
#define FNAME_UTF8 2 /* filename is UTF8 */
#define C_MIN_UINT1 ((Uint1)(0x0))
#define C_MAX_UINT1 ((Uint1)(~(C_MIN_UINT1)))
#define C_MAX_SINT1 ((Int1)(C_MAX_UINT1>>1))
#define C_MIN_SINT1 ((Int1)(~C_MAX_SINT1))

#define C_MIN_UINT2 ((Uint2)(0x0))
#define C_MAX_UINT2 ((Uint2)(~(C_MIN_UINT2)))
#define C_MAX_SINT2 ((Int2)(C_MAX_UINT2>>1))
#define C_MIN_SINT2 ((Int2)(~C_MAX_SINT2))

#define C_MIN_UINT4 ((Uint4)(0x0))
#define C_MAX_UINT4 ((Uint4)(~(C_MIN_UINT4)))
#define C_MAX_SINT4 ((Int4)(C_MAX_UINT4>>1))
#define C_MIN_SINT4 ((Int4)(~C_MAX_SINT4))

#define C_MIN_UINT8 ((Uint8)(0x0))
#define C_MAX_UINT8 ((Uint8)(~(C_MIN_UINT8)))
#define C_MAX_SINT8 ((Int8)(C_MAX_UINT8>>1))
#define C_MIN_SINT8 ((Int8)(~C_MAX_SINT8))

#define TB_MAX_SINT1 C_MAX_SINT1
#define TB_MIN_SINT1 C_MIN_SINT1+1 /* symmetric for historical reasons */
#define TB_MAX_SINT2 C_MAX_SINT2
#define TB_MIN_SINT2 C_MIN_SINT2+1 /* symmetric for historical reasons */
#define TB_MAX_SINT4 C_MAX_SINT4
#define TB_MIN_SINT4 C_MIN_SINT4
#define TB_MAX_SINT8 C_MAX_SINT8
#define TB_MIN_SINT8 C_MIN_SINT8

#define TBMAXFLOAT MAXFLOAT
#define TBMINFLOAT MINFLOAT
#define PASSWDLEN 24
#define PASSLEN OLD_MAXIDENTSIZE
#define DBPATHLEN 256
#define DBNAMLEN 128


#define tb_dt_datetime(d, n, p) tb_dt_dt((d), (n), (p)) /* For upward Compatibility */


/** Macros for Tuple Handling  ( Tuple *tp ) **/
/** a tuple either has no attributes (empty tuple) or
    n>0 attributes  attr.0 ..... attr.n-1  **/

#define TP_BOAT(tp, n) (((Attr_pt*)(((Tuple*)(tp))->boat))[n])
#define TP_INFO(tp) ((char*)(((Tuple*)(tp))->info))

           /* index of last attr-pointer; might be a filling pointer */
     /* in case of filling holds number of attributes */
#define lastboatix(tp) ( TP_BOAT(tp,0)/2-1 )

         /* last attr-offset; might be a filling pointer, holds number of attr's then */
#define lastboat(tp) ( TP_BOAT(tp, lastboatix(tp)) )

        /* number of attr's: check if last attrpointer is a filling! */
  /* lastboat(tp)<TP_BOAT(tp, 0): last boat holds number attributes */
#define tpattno(tp) (lastboat(tp)<TP_BOAT(tp, 0) ? lastboat(tp) : lastboatix(tp))



       /* length of tuple */
#define tplgth(tp) ( TP_BOAT(tp, tpattno(tp)) )

              /* length of attr. i */
#define attlgth(tp,i) ( TP_BOAT(tp, (i)+1) - TP_BOAT(tp, i) )

              /* char Pointer (absolute) to attr. i; assertion: no null value */
#define ptoatt(tp,i) ( TP_INFO(tp) + TP_BOAT(tp, i) )

              /* test if attr. i is NULL value */
#define isnull(tp,i) ( TP_BOAT(tp, (i)+1) == TP_BOAT(tp, i) )

       /* pointer (char*) to attribute i: NULL if i is the null value */
#define ptoattornull(tp,i) (isnull(tp, i)?(NULL):ptoatt(tp,i))

              /* tuple empty? */
#define is_empt_tuple(tp) ( tpattno(tp)==0) /*tuple with 0 attributes*/

#define PTA(tp,i) (ptoattornull(tp,i))
#define PTANN(tp,i) (ptoatt(tp,i)) /* no need to check for NULL value */

/* constants referring to mql queries and optree size */


#define MAX_QUERY_CNT (10)
#define TA_P_KERNEL (MAX_QUERY_CNT + 1)
#define MAX_GRID_ENTRIES (TA_P_KERNEL) /* may change */

typedef union /**** TUPEL  DEFINITION  *****/
{ Attr_pt boat[BBMAXATTRNO]; /** Begin-of-attributes array **/
    char info[MAXTUPLESIZE]; /** Information  !! OVERLAYED WITH bo_attr !!*/
    double doublealign; /* just for alignment, never used */
} Tuple;

typedef Long4 Timeout;

typedef Long4 State;
typedef Long4 Id;

#define MAX_QU (MAX_QUERY_CNT)
#define MAX_TA (64)
#define MAX_DB (64) /* also used for TransbaseD, max capacity
            in catman is 256 (Smallint) */

#define CONS_1 1
#define CONS_2 2
#define CONS_3 3
#define SCHEMA_DEFAULT 0
#define SCHEMA_REL 1
#define SCHEMA_IDX 2
#define SCHEMA_DOM 3
#define SCHEMA_TRIG 4
#define SCHEMA_FUNC 5
#define DROPTABLE 1
#define DROPINDEX 2
#define CREATETABLE 3
#define CREATEINDEX 4
#define CREATEVIEW 5
#define DROPVIEW 8
#define DROPDOMAIN 6
#define CREATEDOMAIN 7
#define GRANT_ACCESS 9
#define GRANT_PRIVILEGE 10
#define REVOKE_ACCESS 11
#define REVOKE_PRIVILEGE 12

#define PASSWORD 14
#define FOREIGN_PASSWORD 15

#define DDLCL FOREIGN_PASSWORD

#define ALTERTABLE_ADDCOL 110 /* nicht einsortiert  ddl_class */
#define ALTERTABLE_DROPCOL 111
#define ALTERTABLE_SETDEFAULT 112
#define ALTERTABLE_DROPDEFAULT 113
#define ALTERTABLE_ADDCONSTR 114
#define ALTERTABLE_DROPCONSTR 115
#define ALTERDOMAIN_SETDEFAULT 116
#define ALTERDOMAIN_DROPDEFAULT 117
#define ALTERDOMAIN_ADDCONSTR 118
#define ALTERDOMAIN_DROPCONSTR 119
#define CREATESEQUENCE 120
#define DROPSEQUENCE 121

#define CREATEEXTERNAL 122 /* first in macro load_external */
#define CREATEEXTSRC 123
#define ALTEREXTERNAL 124
#define ALTEREXTSRC 125 /* last in macro load_external */
#define CREATEFUNCTION 126
#define CREATEPROCEDURE 127
#define CREATETRIGGER 128
#define ALTERFUNCTION 129
#define ALTERPROCEDURE 130
#define CREATEORREPLACE 131
#define DROPEXTERNAL 132
#define DROPPROCEDURE 133
#define DROPFUNCTION 134
#define DROPTRIGGER 135
#define CHECKTRIGGER 136
#define GRANTEXTERNAL 137
#define REVOKEEXTERNAL 138
#define GRANTPROCFUNC 139
#define REVOKEPROCFUNC 140 /* adapt ddl_class if new entries are added */
#define CALL_TYPE 141 /* do not change this! has to be consistent with JDBC ... */

#define ALTERTABLE_MOVE 150
#define ALTERDB_CHARACTERSET 151
#define ALTERTABLE_RENAME 152
#define ALTERTABLE_RENAMECOL 153

#define ALTERTABLE_MODCOL 160
#define ALTERDATASPACE 161
#define CREATEDATASPACE 162
#define CREATEMATVIEW 163
#define DROPMATVIEW 164

#define CREATEDATABASE 165 /* macro dal_class */
#define DROPDATABASE 166
#define LINKDATABASE 167
#define UNLINKDATABASE 168 /* macro dal_class */
   /* attention to macro "ddl_class" */

#define SPOOL_FILE 21
#define SPOOL_RELATION 22

#define SPCL SPOOL_RELATION


#define UPD_POS_TYPE 29
#define DEL_POS_TYPE 30

#define POSICL DEL_POS_TYPE


#define INS_TYPE 31
#define DEL_TYPE 32
#define UPD_TYPE 33
#define MERGE_TYPE 34

#define DMLCL MERGE_TYPE

#define SEL_TYPE 41
#define SEL_FOR_UPD 42

#define MQLCL SEL_FOR_UPD

#define LOCK 51
#define UNLOCK 52

#define LCKCL UNLOCK

#define LOAD_TABLE 60
#define LOAD_INDEX 61
#define LOAD_DEFAULT 62
#define LOAD_BY_QUERY 63
#define LOAD_SWITCH_ON 64
#define LOAD_SWITCH_OFF 65
#define UNLOAD_TABLE 66
#define UNLOAD_INDEX 67
#define UNLOAD_ALL 68

#define LOADCL UNLOAD_ALL

#define TBMODE_TYPE 80
#define TBMODECL TBMODE_TYPE

#define GENTREE_TYPE 90
#define GENTREECL GENTREE_TYPE
#define PROPERTY_TYPE 100
#define PROPERTYCL PROPERTY_TYPE

#define GETSORT_TYPE (200)
#define SETSORT_TYPE (201)
#define GETPLAN_TYPE (202)


#define gentree_class(type) (((type) >= GENTREE_TYPE && (type) <= GENTREECL))
#define ddl_class(type) (((type) >= DROPTABLE && (type) <= DDLCL) || ((type) >= ALTERTABLE_ADDCOL && (type) <= REVOKEPROCFUNC) || ((type) >= ALTERTABLE_MOVE && (type) <= UNLINKDATABASE))
#define dml_class(type) ((type) >= INS_TYPE && (type) <= DMLCL)
#define dal_class(type) ((type) >= CREATEDATABASE && (type) <= UNLINKDATABASE) /* Database Administration */

#define spool_class(type) ((type) >=SPOOL_FILE && (type) <= SPCL)
#define upd_class(type) (dml_class(type))
#define sel_class(type) ((type) >=SEL_TYPE && (type) <= MQLCL || (type)==CALL_TYPE)
#define lock_class(type) ((type) >=LOCK && (type) <= LCKCL)
#define load_class(type) ((type) >=LOAD_TABLE && (type) <= LOADCL)
#define posi_class(type) ((type) >=UPD_POS_TYPE && (type) <= POSICL)
#define tbmode_class(type) ((type) >=TBMODE_TYPE && (type) <= TBMODECL)
#define property_class(type) ((type) >=PROPERTY_TYPE && (type) <= PROPERTYCL)
#define cursor_class(type) ((gentree_class(type))||(sel_class(type)))


#define is_select(type) (sel_class(type))

#define ill_class(type) (!sel_class(type) && !ddl_class(type) && !spool_class(type) && !lock_class(type) && !load_class(type) && !upd_class(type) && !posi_class(type))
/*********** Requests to TRANSBASE ****************/

#define TB__CONNECT 1 /* begin session */
#define TB__DISCONNECT 2 /* end session */
#define TB__LOGIN 3
#define TB__BT 4 /* begin transaction */
#define TB__CT 5 /* commit transaction */
#define TB__AT 6 /* abort transaction */

#define TB__DML 7 /* MQL-Statement */
#define TB__GENTREE 8 /* Open query with relalgterm */
#define TB__RUN 9 /* DDL-Statement and single step
                  statements */
#define TB__CLOSE 10 /* Close evaluation of (SELECT-)Statement */

#define TB__EVAL 11 /* Evaluate compiled mql-statement */
#define TB__DELPOS 12
#define TB__UPDPOS 13

#define TB__GET_TA_STATE 14
#define TB__GET_DB_STATE 15
#define TB__GET_QU_STATE 16
#define TB__SET_TIME_OUT 17
#define TB__SET_DAT_DIR 18
#define TB__GET_VERSION 19
#define TB__SET_CONSISTENCY 20
#define TB__CONTACTK 21
#define TB__ACCEPTK 22

#define TB__TESTCOMM 23

#define TB__OPEN_STORED 24
#define TB__RUN_STORED 25
#define TB__UPDPOS_STORED 26
#define TB__DELPOS_STORED 27
#define TB__STORE 28
#define TB__DROP_STORED 29
#define TB__DROP_ALLSTORED 30

#define TB__GETBLOB 31
#define TB__MAKEBLOB 32

#define TB__SET_SORTORDER 33
#define TB__GET_SORTORDER 34

#define TB__TBMODE 35

#define TB__SIG_HANDLE 36

#define TB__MCONNECT 38

#define TB__SEND_EVENT 39



#define TB__ABORTCALLBACK 40

#define TB__GET_TBX_STATE 41
#define TB__MYCONNECT 42
#define TB__GETFILEREF 43
#define TB__CURSOROPEN 44
#define TB__CURSOROPENSTORED 45
#define TB__CURSORFETCH 46

#define TB__CODEPAGE 47
#define TB__GET_CHARMAP 48
#define TB__GETBLOB_PART 49
#define TB__GETCONNATTR 50
#define TB__GETPLAN 51
#define TB__ADD_BATCH_PARAMS 52
#define TB__CLEAR_BATCH_PARAMS 53
#define TB__RUN_STORED_BATCH 54
#define TB__CANCEL_CURSOR 55
#define TB__AUTOCOMMIT 56
#define TB__CANCEL_TA 57
#define TB__GETCLOB_PART 58
#define TB__GETCLOB 59
#define TB__MAKECLOB 60
#define TB__GETLOBSIZE 61
#define TB__CLEAR 62

#define RECEIVE_REQUEST (1<<13)
#define SEND_REQUEST (1<<14)

/* flags for cursors at compilation or activation time */
#define CURSOR_STD (0)
#define CURSOR_INSENSITIVE (1<<0)
#define CURSOR_SCROLLABLE (1<<1)

#define CURSOR_POS_REL 1
#define CURSOR_POS_ABS 2

#define DB_DCONN 1
#define DB_CONN 2
#define DB_KILLED 3
#define DB_LOGGED 4
#define DB_CONTACTED 5

#define DBACTIVE(state) ((state)==DB_LOGGED || (state)==DB_CONN)

#define QU_ACTIVE 1
#define QU_NOT_ACTIVE 2
#define QU_CANCELLING 3


#define CPG_INVALID 0
#define CPG_TEST 1
#define CPG_PROPRIET 2
#define CPG_ASCII 3
#define CPG_SINGLEBYTE 4
#define CPG_UTF8 5
#define CPG_EUC 6
#define CPG_JIS 7


/************* signs *****************/
#define UNSIGNEDS ((char)0) /* not SIGNED SIGN */
#define PLUSS ((char)1) /* indicates a pos. timespan */
#define MINUSS ((char)2) /* indicates a neg. timespan */
#define JULS ((char)3)
 /* JUL Sign indicates that datetime  lies in JULIAN period */

#define GREGS ((char)4)
 /* GREG Sign indicates that datetime lies in GREGORIAN period */


#define LOWFMASK (0x0000000F)
#define HIGHFMASK (0x000000F0)
#define SIGNMASK (0x00000F00)

#define dtgetlowf(t) ((t)->qual & LOWFMASK)
#define dtgethighf(t) (((t)->qual & HIGHFMASK)>>4)
#define dtgetsign(t) (((t)->qual & SIGNMASK)>>8)
#define dtsetlowf(t,v) ((t)->qual = ((t)->qual&~LOWFMASK)|(v))
#define dtsethighf(t,v) ((t)->qual = ((t)->qual&~HIGHFMASK)|((v)<<4))
#define dtsetsign(t,v) ((t)->qual = ((t)->qual&~SIGNMASK)|((v)<<8))
#define compno_dt_ts(dt) (dtgethighf((Datetime *)(dt)) - dtgetlowf((Datetime *)(dt)) + 1)

#define dtcomponent(t,comp) ((t)->val[(comp)-dtgetlowf(t)])
typedef Long4 Tb_pid; /* process id */
#define TBPID_UNDEF ((Tb_pid)0)

/*************   C-machine data types of tuple attributes **********/

typedef Int8 Bigint;
#define PREC_BIGINT 19
#define PREC_INTEGER 10
typedef Int2 Smallint;
#define PREC_SMALLINT 5
typedef Int1 Tinyint;
#define PREC_TINYINT 3
typedef float Float;
typedef char String[MAXSTRINGSIZE];
typedef double Double;
typedef Double Real;

typedef Int4 Integer;
typedef char Bool;

/**  type NUMERIC  **/

/* Attention: if MAXPREC is increased then we get problems with
   Ubfield_info for Hypercube because it used the original size in
   Ubfield_info (appears in description page - also compare ub_init
   where a sizeof test appears (Datetime) */


#define MAXPREC 30
typedef struct
{
   char bcd[(MAXPREC+1)/2 + 2]; /* contains prec,scale, then 
                BCD-digits in reversed order */
} Numeric;

   /* Vorzeichen, Dez.pkt., N, Exponent mit VZ (4), EOS */
#define MAXNUMSTRING (MAXPREC+8)
#define MAXFIX (MAXNUMSTRING)

/**  type DATETIME/TIMESPAN  **/

#define MAXQUAL 7 /* 7 elements in [MS:YY]  */
typedef struct
{
   Long4 qual; /* sign: PLUSS, MINUSS */
   short val[MAXQUAL]; /* array of datetime field short VALues */
} Datetime; /* order from low to high, from the least */
      /* significant to the most significant */
typedef struct
{
   Long4 qual; /* sign: PLUSS, MINUSS */
   Long4 val[MAXQUAL]; /* Timespan field Long4 VALues */
} Timespan; /* order from the least */

/**  type BINCHAR  **/

typedef Int4 Bincharlen;
#define MAXBINCHAR (MAXATTRSIZE-(int)os_2_sizeof(Bincharlen))
typedef struct
{
   Bincharlen length; /* length of array: no \0  */
   char binchar[MAXBINCHAR];
} Binchar;

#define BINCHARARR(b) ( ((Binchar *)(b))->binchar)
#define BINCHARLEN(b) ( ((Binchar *)(b))->length)
#define ASCIMAXBINCHAR (MAXBINCHAR*2+3)


/**  type BITSS  **/

typedef Int4 Bitslen;
typedef Uint2 Bits2len;

/* internal size of Bits array */
#define MAXBITS (4096-(int)os_2_sizeof(Bitslen))
/* such that number of bits fits in the 2-byte length field of type Bits2 (Ub_value) */
#define MAXUSERBITS (MAXBITS * 8)

typedef struct
{
   Bitslen length; /* number of bits, not bytes */
   unsigned char bits[MAXBITS];
} Bits;
#define BITS_TO_BYTE(b) (((b)+7)/8) /* b bits in bytes */

#define BITSARR(b) ( ( ((Bits *)(b))->bits))
#define BITSLEN(b) ( ((Bits *)(b))->length)
#define BITSLEN_BYTE(b) (BITS_TO_BYTE(BITSLEN(b))) /* used area bytes */

#define BINCHARLEN_TOT(b) (BINCHARLEN(b)+(int)os_2_sizeof(Bincharlen))
#define BITSLEN_TOT(b) (BITSLEN_BYTE(b)+(int)os_2_sizeof(Bitslen))

/* for UBTREE_VARIANT only */
/****  type Bits2 used as Ub_value   **/
/* is like Bits, but with short as length indicator */

typedef struct
{
   Bits2len length; /* number of bits, not bytes */
   unsigned char bits[MAXBITS];
} Bits2;
typedef Bits2 Ub_value;
#define UBVALUEARR(ub) ( ( ((Ub_value *)(ub))->bits))
#define UBVALUELEN(ub) ( ((Ub_value *)(ub))->length)
#define UBVALUELEN_BYTE(ub) (BITS_TO_BYTE(UBVALUELEN(ub))) /* used area bytes */
#define UBVALUELEN_TOT(ub) ((char*)&(UBVALUEARR(ub)[UBVALUELEN_BYTE(ub)]) - (char*)(ub))
#define BITS2ARR(bs) ( ( ((Bits2 *)(bs))->bits))
#define BITS2LEN(bs) ( ((Bits2 *)(bs))->length)
#define BITS2LEN_BYTE(bs) (BITS_TO_BYTE(BITS2LEN(bs))) /* used area bytes */
#define BITS2LEN_TOT(bs) ((char*)&(BITS2ARR(bs)[BITS2LEN_BYTE(bs)]) - (char*)(bs))
   /* this is more complicated than BITSLEN_TOT because of 
      possible alignment of a bad compiler (char[] after 2 byte int 
      should not be aligned) */
/* to store min and max values for a UB-indexed field in Col_desc and
   in B-tree description page in Transbase internal form, we use 
   maximum of value size for the supported data types (may change! ) */

#define MAXSIZE_UBVALUE_SOURCE_OLD os_2_sizeof(Numeric) /* may change! */
typedef Int4 Internal_ubsource_old[1+MAXSIZE_UBVALUE_SOURCE_OLD/os_2_sizeof(Int4)];

/* we now also support Datetime .. , see also test in ub_init */
#define MAXSIZE_UBVALUE_SOURCE os_2_sizeof(Datetime)
typedef Int4 Internal_ubsource[(MAXSIZE_UBVALUE_SOURCE+3)/os_2_sizeof(Int4)];
/*  end for UBTREE_VARIANT only */



/**  type BLOB  **/
typedef Uint4 High_Addr;
typedef Uint2 Low_Addr;

typedef struct {
    High_Addr haddr; /* high address part */
    Low_Addr laddr; /* low address part */
    Uint1 connid; /* for BLOB access in TransbaseD: 
                     0 : local BLOB
                     >0: connection id for remote DB */
    Uint1 type; /* bit0: 0 ... BLOB, 1 ... CLOB */
     /* bit1-7: not used */
} L_Addr;
typedef High_Addr S_Addr;

typedef struct {
    Sno segno;
    char stype;
    Dev dev;
    char checksum_1; /* in page headers, 2 bytes used for checksum */
    char checksum_2;
} Segid;

typedef struct {
    Segid segid;
    L_Addr laddr;
} Blobadr;

typedef struct {
    Ulong4 size; /* size of BLOB object */
    Blobadr blobadr;
} Blob; /* this is the type of a BLOB as it appears in a tuple
        attribute; 
        for internal use: if blobadr.laddr.haddr is SNO_UNDEF
        (0) then blobadr.laddr.laddr is an internal identifier
        for a OS file where BLOB is stored */

typedef Blob Clob;

#define CLOBTYPE 0x1
#define BLOBTYPE 0x0

#define ISCLOB(lob) ((((Blob*)(lob))->blobadr.laddr.type) & CLOBTYPE)
#define ISBLOB(lob) (!ISCLOB(lob))


typedef char Passwd[PASSLEN+1];

typedef int *TbPtr;

/* tbadmlib_incl_type_begin */

typedef char Login[MAXIDENTSIZE+1];

typedef char Dbname[DBNAMLEN+1];

typedef char Dbhost[DBNAMLEN+1];
typedef char Dbpath[DBPATHLEN+1];
/* tbadmlib_incl_type_end */

/* structure for a complete object name 
   (tables,indexes,domains,constraints) */
typedef struct
{ char schname[MAXIDENTSIZE+1]; /* schema name */
    char uqname[MAXIDENTSIZE+1]; /* object name */
    Dbname dbname; /* remote dbname */
    Dbhost dbhost; /* remote dbhost */
} Qname; /* qualified name */

typedef struct {
    int mode; /* MMADR or FILENAME */
    Ulong4 size;
    union {
            char *filename;
            struct {
                     short usrmalloc; /* 0 or 1 */
                     unsigned mallocsize;
                     char *mmadr; /* main memory address  **/
                   } mmem;
           } loc;
 short codepage;
 char locale[MAXIDENTSIZE+1];
} Blobdesc;
typedef Blobdesc Clobdesc;

typedef Int2 Attrcode;


/*************  end C-machine data types of tuple attributes **********/

typedef char *Pointer;

/* parametertype  for procedure ipr_tuplecmp   */

typedef Int2 Attrpos;
typedef struct
{ Int2 attr_pos; /* field position in tupel */
   Attrcode attr_type; /* type description */
} TupCompelem; /* field of attribute descriptions */

typedef struct
{ Int2 nattr; /* number of fields to compare */
   TupCompelem field[MAXATTRNO]; /* description of field to compare */
} TupComp;

#define tb_tuplecmp(tup0,tup1,d0,d1) (ipr_tuplecmp(tup0,tup1,d0,d1,NULL))

typedef union
{ struct
   { char prec;
   char scale;
   } ps; /* for NUMERIC */
   struct
   { char lowf;
 char highf;
   } lh; /* for DATETIME/TIMESPAN */
   short strprec; /* for CHAR[]/STRING */
} Tspec;
 /* fine type specification for CHAR/NUMERIC/DATE/TIME */

typedef struct
{ Attrcode code;
   Tspec tspec;
   Bool notnull; /* used in optree:
            FALSE: NULL's may arrive;  TRUE: noNULLS */
   FILLER_1(d1) /* required for alignment of Attrtypes in descr. pages */
} Attrtype;

typedef struct
{
   Int4 ntuples;
   Int4 tried;
} Count_result;


#define NO_TUPLE (0)
#define ONE_TUPLE (1)
#define MORE_TUPLES (2)

typedef struct
{
   char unnamed; /* fieldname generated by DB ? */
   short fieldtype;
   Tspec tspec; /* fine type specification */
   char fieldname[MAXIDENTSIZE+1];
   char orig_fieldname[MAXIDENTSIZE+1];
   char orig_tablename[MAXIDENTSIZE+1];
   char orig_schemaname[MAXIDENTSIZE+1];
   char *fieldpointer;
} Field;

typedef struct /* obsolete */
{
   char unnamed; /* fieldname generated by DB ? */
   short fieldtype;
   Tspec tspec; /* fine type specification */
   char fieldname[MAXIDENTSIZE+1];
   char *fieldpointer;
} Field_obs1;

typedef struct {
    char parammode;
    char parname[MAXIDENTSIZE+1]; /* might be empty */
    short fieldtype;
    Tspec tspec;
} Par_descr;

typedef struct
{
   Id query_id; /* identifier of the open mql-query */
   short eod;
   short qtype;
   short updatable; /* for (not)updatable select queries */
   short qattr_no; /* number of attr's in  result-tuple */
   short param_no; /* number of param's in  query */
   Field *field; /* for each result-attribute */
   Par_descr *params; /* for each parameter */
} Query_descr; /* Description of an open query */

typedef struct /* obsolete */
{
   Id query_id; /* identifier of the open mql-query */
   short eod;
   short qtype;
   short updatable; /* for (not)updatable select queries */
   short qattr_no; /* number of attr's in  result-tuple */
   short param_no; /* number of param's in  query */
   Field_obs1 *field; /* for each result-attribute */
   Par_descr *params; /* for each parameter */
} Query_descr_obs1; /* Description of an open query */


typedef struct
{
   short qtype;
   short eod;
   union{
           char tuple[MAXTUPLESIZE];
    Count_result count;
    Double doublealign; /* just for alignment */
 }_var;
} Result;


typedef struct{
 short type;
 char *value;
} Param;

typedef struct{
 short param_no;
 Param *param;
} Parameters;



#pragma pack()


typedef int (TBX_API TbxCallback)(void);
typedef TbxCallback *PTbxCallback;
Error TBX_API double_number (double value , Numeric *num );
Error TBX_API double_fix (double value , int outscale , Numeric *num );
Error TBX_API scan_fix (char *string , Numeric *num , unsigned *scanned );
Numeric * TBX_API fix_fix (Numeric *source , int outscale , Numeric *dest );
Error TBX_API fix_long (Numeric *num , Int4 *target );
Error TBX_API fix_int8 (Numeric *num , Int8 *target );
Error TBX_API fixadd (Numeric *op1 , Numeric *op2 , Numeric *op0 );
Error TBX_API fixsub (Numeric *op1 , Numeric *op2 , Numeric *op0 );
Error TBX_API fixmul (Numeric *op1 , Numeric *op2 , Numeric *op0 );
Error TBX_API fixdiv (Numeric *op1 , Numeric *op2 , Numeric *op0 );
int TBX_API fixgetsign (Numeric *num );
int TBX_API getsign (Numeric *num );
int TBX_API getscale (Numeric *num );
int TBX_API getdigit (Numeric *num , int digit );
Numeric * TBX_API fixmkzero (Numeric *num );
int TBX_API fixiszero (Numeric *num );
Numeric * TBX_API fixminus (Numeric *source , Numeric *destination );
Numeric * TBX_API fixcopy (Numeric *source , Numeric *destination );
int TBX_API fixcmp (Numeric *op1 , Numeric *op2 );
Numeric * TBX_API long_fix (Int4 value , unsigned outscale , Numeric *num );
Numeric * TBX_API int8_fix (Int8 value , unsigned outscale , Numeric *num );
double TBX_API fix_double (Numeric *num );
char * TBX_API fix_string (Numeric *num , char *target );
int TBX_API getprec (Numeric *num );
Error TBX_API set_current (void);
Error TBX_API dt_current (Datetime *dt );
Error TBX_API dt_day (Datetime *dt , int *day );
Error TBX_API dt_weekday (Datetime *dt , int *day );
Error TBX_API dt_week (Datetime *dt , int *week );
Error TBX_API dt_isoweek (Datetime *dt , int *week );
Error TBX_API dt_quarter (Datetime *dt , int *quarter );
void TBX_API dt_copy (Datetime *dtd , Datetime *dts );
void TBX_API ts_copy (Timespan *tsd , Timespan *tss );
Error TBX_API dt_cast (Datetime *dtin , Datetime *dtout , int qlowf , int qhighf );
Error TBX_API ts_cast (Timespan *tsin , Timespan *tsout , int qlowf , int qhighf );
int TBX_API dt_cmp (Datetime *dt1 , Datetime *dt2 );
int TBX_API ts_getsign (Timespan *ts );
Error TBX_API ts_cmp (Timespan *ts1 , Timespan *ts2 , int *result );
Error TBX_API ts_add (Timespan *ts1 , Timespan *ts2 , Timespan *ts0 );
Error TBX_API ts_sub (Timespan *ts1 , Timespan *ts2 , Timespan *ts0 );
Error TBX_API ts_mul (Timespan *ts , Long4 scalar , Timespan *tsresult );
Error TBX_API ts_div (Timespan *ts , Long4 scalar , Timespan *tsresult );
Error TBX_API dt_sub (Datetime *dt1 , Datetime *dt2 , Timespan *ts0 );
Error TBX_API dt_ts_add (Datetime *dt , Timespan *ts , Datetime *dtresult );
Error TBX_API dt_ts_sub (Datetime *dt , Timespan *ts , Datetime *dtresult );
void TBX_API ts_change_sign (Timespan *ts );
char * TBX_API dt_str_raw (char *str , Datetime *dt );
char * TBX_API dt_str (char *str , Datetime *dt );
char * TBX_API ts_str (char *str , Timespan *ts );
Error TBX_API dt_check (Datetime *dt );
Error TBX_API ts_check (Timespan *ts );
Error TBX_API str2date (char *str , Datetime *dt , char *format );
Error TBX_API date2str (Datetime *dt , char *str , size_t sz , char *format );
char * TBX_API tb_dt_format (char *dest , char *format , Datetime *ptr );
char * TBX_API tb_ts_format (char *dest , char *format , Timespan *ptr );
char * TBX_API tb_dt_date (char *dest , int nlp , Datetime *ptr );
char * TBX_API tb_dt_time (char *dest , int nlp , Datetime *ptr );
char * TBX_API tb_dt_dt (char *dest , int nlp , Datetime *ptr );
char * TBX_API tb_ts_timespan (char *dest , int nlp , Timespan *ptr );
char * TBX_API binchar_to_string (char *target , Binchar *binchar , Long4 number );
char * TBX_API bits_to_string (char *target , Bits *bits , Long4 destlen );
char * TBX_API bits2_to_string (char *target , Bits2 *bits2 , Long4 destlen );
int TBX_API atonumber (char *inpstr , Bigint *result , char **scannedp );
 Error TBX_API tbx (int _req , ... );
Error TBX_API TbxCursorOpen (Id p1 , Id p2 , char *p3 , Query_descr *p4 , Ulong4 p5 );
Error TBX_API TbxCursorFetch (Query_descr *p1 , int p2 , Long4 p3 , Long4 *p4 , Long4 *p5 );
Error TBX_API TbxCursorOpenStored (Id p1 , Id p2 , Id p3 , Parameters *p4 , Query_descr *p5 , Ulong4 p6 );
Error TBX_API TbxInterrupt (State *p1 );
Error TBX_API TbxConnect (char *p1 , Id *p2 );
Error TBX_API TbxMultiConnect (char *p1 , Id *p2 );
Error TBX_API TbxDisconnect (Id p1 , State *p2 );
Error TBX_API TbxLogin (Id p1 , char *p2 , char *p3 );
Error TBX_API TbxBt (Id *p1 );
Error TBX_API TbxCt (Id p1 , State *p2 );
Error TBX_API TbxAt (Id p1 , State *p2 );
Error TBX_API TbxDml (Id p1 , Id p2 , char *p3 , Query_descr *p4 );
Error TBX_API TbxRun (Id p1 , Id p2 , char *p3 , Query_descr *p4 , Result *p5 );
Error TBX_API TbxClose (Query_descr *p1 );
Error TBX_API TbxEval (Query_descr *p1 , Result *p2 );
Error TBX_API TbxDelPos (Query_descr *p1 );
Error TBX_API TbxUpdPos (Query_descr *p1 , char *p2 );
Error TBX_API TbxGetTaState (Id p1 , State *p2 );
Error TBX_API TbxGetDbState (Id p1 , State *p2 );
Error TBX_API TbxGetQuState (Id p1 , State *p2 );
Error TBX_API TbxSetTimeout (Timeout p1 );
Error TBX_API TbxSetDatDir (Id p1 , char *p2 );
Error TBX_API TbxVersion (Id p1 , char *p2 );
Error TBX_API TbxSetConsistency (int p1 );
Error TBX_API TbxContact (char *p1 , Id *p2 );
Error TBX_API TbxAccept (Id p1 );
Error TBX_API TbxOpenStored (Id p1 , Id p2 , Id p3 , Parameters *p4 , Query_descr *p5 );
Error TBX_API TbxRunStored (Id p1 , Id p2 , Id p3 , Parameters *p4 , Query_descr *p5 , Result *p6 );
Error TBX_API TbxAddBatchParams (Id p1 , Id p2 , Id p3 , Parameters *p4 , Query_descr *p5 , Long4 *p6 , Count_result **p7 );
Error TBX_API TbxClearBatchParams (Id p1 , Id p2 , Id p3 );
Error TBX_API TbxRunStoredBatch (Id p1 , Id p2 , Id p3 , Query_descr *p4 , Long4 *p5 , Count_result **p6 );
Error TBX_API TbxUpdPosStored (Query_descr *p1 , Id p2 , Parameters *p3 );
Error TBX_API TbxDelPosStored (Query_descr *p1 , Id p2 );
Error TBX_API TbxStore (Id p1 , char *p2 , Id *p3 , Query_descr *p4 );
Error TBX_API TbxDropStored (Id p1 , Id p2 );
Error TBX_API TbxDropAllStored (Id p1 );
Error TBX_API TbxGetBlob (Id p1 , Id p2 , Blob *p3 , Blobdesc *p4 );
Error TBX_API TbxGetClob (Id p1 , Id p2 , Blob *p3 , Blobdesc *p4 );
Error TBX_API TbxGetBlobPart (Id p1 , Id p2 , Blob *p3 , Blobdesc *p4 , Long4 p5 , Long4 p6 );
Error TBX_API TbxGetClobPart (Id p1 , Id p2 , Blob *p3 , Blobdesc *p4 , Long4 p5 , Long4 p6 , Long4 *p7 , Long4 *p8 );
Error TBX_API TbxMakeBlob (Id p1 , Id p2 , char *p3 , Blobdesc *p4 );
Error TBX_API TbxMakeClob (Id p1 , Id p2 , char *p3 , Blobdesc *p4 );
Error TBX_API TbxGetLobSize (Id p1 , Id p2 , Blob *p3 , Ulong4 *p4 );
Error TBX_API TbxAutoCommit (Id p1 , int p2 );
Error TBX_API TbxSetSortOrder (Id p1 , unsigned char *p2 );
Error TBX_API TbxGetSortOrder (Id p1 , unsigned char *p2 );
Error TBX_API TbxTbmode (Id p1 , char *p2 );
Error TBX_API TbxSendEvent (Id p1 , char *p2 , char *p3 , char *p4 );
Error TBX_API TbxCodePage (Id p1 , short *p2 );
Error TBX_API TbxGetConnectionAttribute (Id p1 , char *p2 , char *p3 );
Error TBX_API TbxGetFileRef (Id p1 , Id p2 , char *p3 , Blobdesc *p4 );
Error TBX_API TbxGetTbxState (State p1 );
Error TBX_API TbxMyriadConnect (char *p1 , Id *p2 );
Error TBX_API TbxTestComm (Id p1 , char *p2 );
Error TBX_API TbxGetCharmap (Id p1 , Long4 *p2 );
Error TBX_API TbxAbortCallback (PTbxCallback p1 );
Error TBX_API TbxGetPlan (Id p1 , char *p2 , char *p3 );
Error TBX_API TbxCancelCursor (Id p1 , State *p2 );
Error TBX_API TbxCancelTa (Id p1 , State *p2 );
Error TBX_API TbxClear (void);
char * TBX_API tb_errtxt_adr (void);
#if defined(__cplusplus)
}
#endif
#endif
#if defined(_UNICODE)
#include <wchar.h>
#endif


#if defined(_WIN64)
#pragma pack(8)
#elif defined(_WIN32)
#pragma pack(1)
#endif


#define TCI_TYPE (0x0100) /* TCI types starting at 256 */
#define TCI_TYPE_UNSIGNED (0x0200) /* flag for unsigned types */
#define TCI_TYPE_DATE (0x0400) /* flag for date type */
#define TCI_TYPE_INTERVAL (0x0800) /* flag for interval type */
#define TCI_TYPE_SPECIAL (0x1000) /* has no Transbase corresponding type */
#define TCI_TYPE_WIDE (0x2000) /* is wide char type */
#define TCI_TYPE_SQL (0x4000) /* is a SQL type */
#define TCI_TYPE_UNUSED (0x8000) /* not used for the moment */

#define IS_TCI_TYPE(t) (((t) & 0xFFFF) & TCI_TYPE) /* t is a TCI type */
#define IS_TCI_UNSIGNED(t) (IS_TCI_TYPE(t) && ((t) & TCI_TYPE_UNSIGNED)) /* t is a TCI unsigned type */
#define IS_TCI_DATE(t) (IS_TCI_TYPE(t) && ((t) & TCI_TYPE_DATE)) /* t is a TCI date type, low/high in lower byte */
#define IS_TCI_INTERVAL(t) (IS_TCI_TYPE(t) && ((t) & TCI_TYPE_INTERVAL)) /* t is a TCI interval type, low/high in lower byte */
#define IS_TCI_SPECIAL(t) (IS_TCI_TYPE(t) && ((t) & TCI_TYPE_SPECIAL)) /* t is a TCI ODBC-like type */
#define IS_TCI_WIDE(t) (IS_TCI_TYPE(t) && ((t) & TCI_TYPE_WIDE)) /* t is a TCI wide char type */
#define IS_TCI_SQL(t) (IS_TCI_TYPE(t) && ((t) & TCI_TYPE_SQL)) /* t is a TCI SQL type */
#define IS_TCI_UNUSED(t) (IS_TCI_TYPE(t) && ((t) & TCI_TYPE_UNUSED)) /* t is a TCI unused type */

/* classification of types */
#define IS_TCI_NATURAL(t) ((t)==TCI_C_SINT1 || (t)==TCI_C_SINT2 || (t)==TCI_C_SINT4 || (t)==TCI_C_SINT8 || (t)==TCI_C_UINT1 || (t)==TCI_C_UINT2 || (t)==TCI_C_UINT4 || (t)==TCI_C_UINT8)

#define IS_TCI_APPROX(t) ((t)==TCI_C_FLOAT || (t)==TCI_C_DOUBLE)
#define IS_TCI_ARI(t) (IS_TCI_NATURAL(t) || IS_TCI_APPROX(t))
#define IS_TCI_CHAR(t) ((t)==TCI_C_SCHAR || (t)==TCI_C_WCHAR)
#define IS_TCI_FILE(t) ((t)==TCI_C_SFILE || (t)==TCI_C_WFILE)
#define IS_TCI_BINARY(t) (IS_TCI_FILE(t) || (t)==TCI_C_BYTE)
#define IS_TCI_STREAMABLE(t) (IS_TCI_CHAR(t) || (t)==TCI_C_BYTE)

#define TCI_MILLISECOND (0x01)
#define TCI_SECOND (0x02)
#define TCI_MINUTE (0x03)
#define TCI_HOUR (0x04)
#define TCI_DAY (0x05)
#define TCI_MONTH (0x06)
#define TCI_YEAR (0x07)

#define TCI_MAKE_HL(h,l) (((h) << 4) | (l))
#define TCI_GET_HL_H(hl) (((hl) & 0x00f0) >> 4)
#define TCI_GET_HL_L(hl) ((hl) & 0x000f)

#define TCI_C_INT1 (TCI_TYPE | 0x01) /* signed char */
#define TCI_C_INT2 (TCI_TYPE | 0x02) /* signed short */
#define TCI_C_INT4 (TCI_TYPE | 0x03) /* signed int */
#define TCI_C_FLOAT (TCI_TYPE | 0x05) /* float */
#define TCI_C_DOUBLE (TCI_TYPE | 0x06) /* double */

#define TCI_C_CHAR (TCI_TYPE | TCI_TYPE_SPECIAL | 0x0a) /* char * */
#define TCI_C_INT8 (TCI_TYPE | 0x0b) /* TCIBigint */
#define TCI_C_BYTE (TCI_TYPE | TCI_TYPE_SPECIAL | 0x0c) /* unsigned char * */
#define TCI_C_FILE (TCI_TYPE | TCI_TYPE_SPECIAL | 0x0d) /* char * */
#define TCI_C_CHARPTR (TCI_TYPE | TCI_TYPE_SPECIAL | 0x0e) /* char ** */
#define TCI_C_BYTEPTR (TCI_TYPE | TCI_TYPE_SPECIAL | 0x0f) /* unsigned char ** */
#define TCI_C_FILEPTR (TCI_TYPE | TCI_TYPE_SPECIAL | 0x10) /* char ** */
#define TCI_C_CFILE (TCI_TYPE | TCI_TYPE_SPECIAL | 0x11) /* char * */
#define TCI_C_CFILEPTR (TCI_TYPE | TCI_TYPE_SPECIAL | 0x12) /* char ** */

#define TCI_C_TCINUMERIC (TCI_TYPE | TCI_TYPE_SPECIAL | 0x07) /* Transbase implementation of SQL_NUMERIC_STRUCT (ODBC) */

#define TCI_C_TBNATIVE (TCI_TYPE | TCI_TYPE_SPECIAL | 0x04) /* Transbase native type */
#define TCI_C_TBNUMERIC (TCI_TYPE | TCI_TYPE_SPECIAL | 0x13) /* Numeric */
#define TCI_C_TBBLOB (TCI_TYPE | TCI_TYPE_SPECIAL | 0x14) /* Blob */
#define TCI_C_TBCLOB (TCI_TYPE | TCI_TYPE_SPECIAL | 0x15) /* Clob */
#define TCI_C_TBBINCHAR (TCI_TYPE | TCI_TYPE_SPECIAL | 0x16) /* Binchar */
#define TCI_C_TBBITSLONG (TCI_TYPE | TCI_TYPE_SPECIAL | 0x17) /* Bits */
#define TCI_C_TBBITSHORT (TCI_TYPE | TCI_TYPE_SPECIAL | 0x18) /* Bits2 */
#define TCI_C_TBDATETIME (TCI_TYPE | TCI_TYPE_SPECIAL | 0x19) /* Datetime; no lower byte: reserved for high/low field */
#define TCI_C_TBTIMESPAN (TCI_TYPE | TCI_TYPE_SPECIAL | 0x1a) /* Timespan; no lower byte: reserved for high/low field */

#define TCI_C_TYPE_DATE (TCI_TYPE | TCI_TYPE_SPECIAL | TCI_TYPE_DATE)

#define TCI_C_DATE_YEAR (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_YEAR, TCI_YEAR)) /* TCIDate */
#define TCI_C_DATE_YEAR_TO_MONTH (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_YEAR, TCI_MONTH)) /* TCIDate */
#define TCI_C_DATE_YEAR_TO_DAY (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_YEAR, TCI_DAY)) /* TCIDate */
#define TCI_C_DATE_MONTH (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_MONTH, TCI_MONTH)) /* TCIDate */
#define TCI_C_DATE_MONTH_TO_DAY (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_MONTH, TCI_DAY)) /* TCIDate */
#define TCI_C_DATE_DAY (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_DAY, TCI_DAY)) /* TCIDate */
#define TCI_C_DATE (TCI_C_DATE_YEAR_TO_DAY) /* TCIDate */

#define TCI_C_TIME_HOUR (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_HOUR, TCI_HOUR)) /* TCITime */
#define TCI_C_TIME_HOUR_TO_MINUTE (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_HOUR, TCI_MINUTE)) /* TCITime */
#define TCI_C_TIME_HOUR_TO_SECOND (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_HOUR, TCI_SECOND)) /* TCITime */
#define TCI_C_TIME_MINUTE (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_MINUTE, TCI_MINUTE)) /* TCITime */
#define TCI_C_TIME_MINUTE_TO_SECOND (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_MINUTE, TCI_SECOND)) /* TCITime */
#define TCI_C_TIME_SECOND (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_SECOND, TCI_SECOND)) /* TCITime */
#define TCI_C_TIME (TCI_C_TIME_HOUR_TO_SECOND) /* TCITime */

#define TCI_C_TIMESTAMP_YEAR_TO_HOUR (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_YEAR, TCI_HOUR)) /* TCITimestamp */
#define TCI_C_TIMESTAMP_YEAR_TO_MINUTE (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_YEAR, TCI_MINUTE)) /* TCITimestamp */
#define TCI_C_TIMESTAMP_YEAR_TO_SECOND (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_YEAR, TCI_SECOND)) /* TCITimestamp */
#define TCI_C_TIMESTAMP_YEAR_TO_MILLISECOND (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_YEAR, TCI_MILLISECOND)) /* TCITimestamp */
#define TCI_C_TIMESTAMP_MONTH_TO_HOUR (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_MONTH, TCI_HOUR)) /* TCITimestamp */
#define TCI_C_TIMESTAMP_MONTH_TO_MINUTE (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_MONTH, TCI_MINUTE)) /* TCITimestamp */
#define TCI_C_TIMESTAMP_MONTH_TO_SECOND (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_MONTH, TCI_SECOND)) /* TCITimestamp */
#define TCI_C_TIMESTAMP_MONTH_TO_MILLISECOND (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_MONTH, TCI_MILLISECOND)) /* TCITimestamp */
#define TCI_C_TIMESTAMP_DAY_TO_HOUR (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_DAY, TCI_HOUR)) /* TCITimestamp */
#define TCI_C_TIMESTAMP_DAY_TO_MINUTE (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_DAY, TCI_MINUTE)) /* TCITimestamp */
#define TCI_C_TIMESTAMP_DAY_TO_SECOND (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_DAY, TCI_SECOND)) /* TCITimestamp */
#define TCI_C_TIMESTAMP_DAY_TO_MILLISECOND (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_DAY, TCI_MILLISECOND)) /* TCITimestamp */
#define TCI_C_TIMESTAMP_HOUR_TO_MILLISECOND (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_HOUR, TCI_MILLISECOND)) /* TCITimestamp */
#define TCI_C_TIMESTAMP_MINUTE_TO_MILLISECOND (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_MINUTE, TCI_MILLISECOND)) /* TCITimestamp */
#define TCI_C_TIMESTAMP_SECOND_TO_MILLISECOND (TCI_C_TYPE_DATE | TCI_MAKE_HL(TCI_SECOND, TCI_MILLISECOND)) /* TCITimestamp */
#define TCI_C_TIMESTAMP (TCI_C_TIMESTAMP_YEAR_TO_MILLISECOND) /* TCITimestamp */

#define TCI_C_TYPE_INTERVAL (TCI_TYPE | TCI_TYPE_SPECIAL | TCI_TYPE_INTERVAL) /* TCIInterval */

#define TCI_C_INTERVAL_YEAR (TCI_C_TYPE_INTERVAL | TCI_MAKE_HL(TCI_YEAR, TCI_YEAR)) /* TCIInterval */
#define TCI_C_INTERVAL_YEAR_TO_MONTH (TCI_C_TYPE_INTERVAL | TCI_MAKE_HL(TCI_YEAR, TCI_MONTH)) /* TCIInterval */
#define TCI_C_INTERVAL_MONTH (TCI_C_TYPE_INTERVAL | TCI_MAKE_HL(TCI_MONTH, TCI_MONTH)) /* TCIInterval */

#define TCI_C_INTERVAL_DAY (TCI_C_TYPE_INTERVAL | TCI_MAKE_HL(TCI_DAY, TCI_DAY)) /* TCIInterval */
#define TCI_C_INTERVAL_DAY_TO_HOUR (TCI_C_TYPE_INTERVAL | TCI_MAKE_HL(TCI_DAY, TCI_HOUR)) /* TCIInterval */
#define TCI_C_INTERVAL_DAY_TO_MINUTE (TCI_C_TYPE_INTERVAL | TCI_MAKE_HL(TCI_DAY, TCI_MINUTE)) /* TCIInterval */
#define TCI_C_INTERVAL_DAY_TO_SECOND (TCI_C_TYPE_INTERVAL | TCI_MAKE_HL(TCI_DAY, TCI_SECOND)) /* TCIInterval */
#define TCI_C_INTERVAL_DAY_TO_MILLISECOND (TCI_C_TYPE_INTERVAL | TCI_MAKE_HL(TCI_DAY, TCI_MILLISECOND)) /* TCIInterval */
#define TCI_C_INTERVAL_HOUR (TCI_C_TYPE_INTERVAL | TCI_MAKE_HL(TCI_HOUR, TCI_HOUR)) /* TCIInterval */
#define TCI_C_INTERVAL_HOUR_TO_MINUTE (TCI_C_TYPE_INTERVAL | TCI_MAKE_HL(TCI_HOUR, TCI_MINUTE)) /* TCIInterval */
#define TCI_C_INTERVAL_HOUR_TO_SECOND (TCI_C_TYPE_INTERVAL | TCI_MAKE_HL(TCI_HOUR, TCI_SECOND)) /* TCIInterval */
#define TCI_C_INTERVAL_HOUR_TO_MILLISECOND (TCI_C_TYPE_INTERVAL | TCI_MAKE_HL(TCI_HOUR, TCI_MILLISECOND)) /* TCIInterval */
#define TCI_C_INTERVAL_MINUTE (TCI_C_TYPE_INTERVAL | TCI_MAKE_HL(TCI_MINUTE, TCI_MINUTE)) /* TCIInterval */
#define TCI_C_INTERVAL_MINUTE_TO_SECOND (TCI_C_TYPE_INTERVAL | TCI_MAKE_HL(TCI_MINUTE, TCI_SECOND)) /* TCIInterval */
#define TCI_C_INTERVAL_MINUTE_TO_MILLISECOND (TCI_C_TYPE_INTERVAL | TCI_MAKE_HL(TCI_MINUTE, TCI_MILLISECOND)) /* TCIInterval */
#define TCI_C_INTERVAL_SECOND (TCI_C_TYPE_INTERVAL | TCI_MAKE_HL(TCI_SECOND, TCI_SECOND)) /* TCIInterval */
#define TCI_C_INTERVAL_SECOND_TO_MILLISECOND (TCI_C_TYPE_INTERVAL | TCI_MAKE_HL(TCI_SECOND, TCI_MILLISECOND)) /* TCIInterval */
#define TCI_C_INTERVAL_MILLISECOND (TCI_C_TYPE_INTERVAL | TCI_MAKE_HL(TCI_MILLISECOND, TCI_MILLISECOND)) /* TCIInterval */

#define TCI_C_SINT1 TCI_C_INT1
#define TCI_C_SINT2 TCI_C_INT2
#define TCI_C_SINT4 TCI_C_INT4
#define TCI_C_SINT8 TCI_C_INT8

#define TCI_C_UINT1 (TCI_C_INT1 | TCI_TYPE_UNSIGNED) /* unsigned char */
#define TCI_C_UINT2 (TCI_C_INT2 | TCI_TYPE_UNSIGNED) /* unsigned short */
#define TCI_C_UINT4 (TCI_C_INT4 | TCI_TYPE_UNSIGNED) /* unsigned int */
#define TCI_C_UINT8 (TCI_C_INT8 | TCI_TYPE_UNSIGNED) /* TCIUBigint */

#define TCI_C_SCHAR TCI_C_CHAR
#define TCI_C_WCHAR (TCI_C_CHAR | TCI_TYPE_WIDE) /* wchar_t * */
#define TCI_C_SCHARPTR TCI_C_CHARPTR
#define TCI_C_WCHARPTR (TCI_C_CHARPTR | TCI_TYPE_WIDE) /* wchar_t ** */

#define TCI_C_SFILE TCI_C_FILE
#define TCI_C_WFILE (TCI_C_FILE | TCI_TYPE_WIDE) /* wchar_t * */
#define TCI_C_SCFILE TCI_C_CFILE
#define TCI_C_WCFILE (TCI_C_CFILE | TCI_TYPE_WIDE) /* wchar_t * */
#define TCI_C_SFILEPTR TCI_C_FILEPTR
#define TCI_C_WFILEPTR (TCI_C_FILEPTR | TCI_TYPE_WIDE) /* wchar_t ** */
#define TCI_C_SCFILEPTR TCI_C_CFILEPTR
#define TCI_C_WCFILEPTR (TCI_C_CFILEPTR | TCI_TYPE_WIDE) /* wchar_t ** */

/* SQL data types */

#define TCI_SQL_TYPE (TCI_TYPE | TCI_TYPE_SQL)

#define TCI_SQL_UNDEFTYPE (TCI_SQL_TYPE | 0x00) /* undefined type (mapping etc.) */

#define TCI_SQL_BOOL (TCI_SQL_TYPE | 0x01) /* true / false */
#define TCI_SQL_TINYINT (TCI_SQL_TYPE | 0x02) /* -128 .. 127 */
#define TCI_SQL_SMALLINT (TCI_SQL_TYPE | 0x03) /* -2**15 .. 2**15-1 */
#define TCI_SQL_INTEGER (TCI_SQL_TYPE | 0x04) /* -2**31 .. 2**31-1 */
#define TCI_SQL_NUMERIC (TCI_SQL_TYPE | 0x05) /* no prec, prec, prec/scale */
#define TCI_SQL_FLOAT (TCI_SQL_TYPE | 0x06)
#define TCI_SQL_DOUBLE (TCI_SQL_TYPE | 0x07)
#define TCI_SQL_CHAR (TCI_SQL_TYPE | 0x08) /* prec, *, with blank padding */
#define TCI_SQL_VARCHAR (TCI_SQL_TYPE | 0x09) /* prec, *, without blank padding */
#define TCI_SQL_BINARY (TCI_SQL_TYPE | 0x0a) /* prec, * */
#define TCI_SQL_BIT (TCI_SQL_TYPE | 0x0b) /* prec, * */
#define TCI_SQL_BLOB (TCI_SQL_TYPE | 0x0c)
#define TCI_SQL_FILEREF (TCI_SQL_TYPE | 0x0d)
#define TCI_SQL_BITSHORT (TCI_SQL_TYPE | 0x0e) /* prec, * */
#define TCI_SQL_BIGINT (TCI_SQL_TYPE | 0x0f) /* -2**63 .. 2**63-1 */
#define TCI_SQL_CLOB (TCI_SQL_TYPE | 0x10)

#define TCI_SQL_TYPE_DATE (TCI_SQL_TYPE | TCI_TYPE_DATE)

#define TCI_SQL_DATE_YEAR (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_YEAR, TCI_YEAR))
#define TCI_SQL_DATE_YEAR_TO_MONTH (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_YEAR, TCI_MONTH))
#define TCI_SQL_DATE_YEAR_TO_DAY (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_YEAR, TCI_DAY))
#define TCI_SQL_DATE_YEAR_TO_HOUR (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_YEAR, TCI_HOUR))
#define TCI_SQL_DATE_YEAR_TO_MINUTE (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_YEAR, TCI_MINUTE))
#define TCI_SQL_DATE_YEAR_TO_SECOND (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_YEAR, TCI_SECOND))
#define TCI_SQL_DATE_YEAR_TO_MILLISECOND (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_YEAR, TCI_MILLISECOND))
#define TCI_SQL_DATE_MONTH (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_MONTH, TCI_MONTH))
#define TCI_SQL_DATE_MONTH_TO_DAY (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_MONTH, TCI_DAY))
#define TCI_SQL_DATE_MONTH_TO_HOUR (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_MONTH, TCI_HOUR))
#define TCI_SQL_DATE_MONTH_TO_MINUTE (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_MONTH, TCI_MINUTE))
#define TCI_SQL_DATE_MONTH_TO_SECOND (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_MONTH, TCI_SECOND))
#define TCI_SQL_DATE_MONTH_TO_MILLISECOND (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_MONTH, TCI_MILLISECOND))
#define TCI_SQL_DATE_DAY (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_DAY, TCI_DAY))
#define TCI_SQL_DATE_DAY_TO_HOUR (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_DAY, TCI_HOUR))
#define TCI_SQL_DATE_DAY_TO_MINUTE (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_DAY, TCI_MINUTE))
#define TCI_SQL_DATE_DAY_TO_SECOND (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_DAY, TCI_SECOND))
#define TCI_SQL_DATE_DAY_TO_MILLISECOND (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_DAY, TCI_MILLISECOND))
#define TCI_SQL_DATE_HOUR (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_HOUR, TCI_HOUR))
#define TCI_SQL_DATE_HOUR_TO_MINUTE (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_HOUR, TCI_MINUTE))
#define TCI_SQL_DATE_HOUR_TO_SECOND (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_HOUR, TCI_SECOND))
#define TCI_SQL_DATE_HOUR_TO_MILLISECOND (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_HOUR, TCI_MILLISECOND))
#define TCI_SQL_DATE_MINUTE (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_MINUTE, TCI_MINUTE))
#define TCI_SQL_DATE_MINUTE_TO_SECOND (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_MINUTE, TCI_SECOND))
#define TCI_SQL_DATE_MINUTE_TO_MILLISECOND (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_MINUTE, TCI_MILLISECOND))
#define TCI_SQL_DATE_SECOND (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_SECOND, TCI_SECOND))
#define TCI_SQL_DATE_SECOND_TO_MILLISECOND (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_SECOND, TCI_MILLISECOND))
#define TCI_SQL_DATE_MILLISECOND (TCI_SQL_TYPE_DATE | TCI_MAKE_HL(TCI_MILLISECOND, TCI_MILLISECOND))

#define TCI_SQL_DATE (TCI_SQL_DATE_YEAR_TO_DAY)
#define TCI_SQL_TIME (TCI_SQL_DATE_HOUR_TO_SECOND)
#define TCI_SQL_TIMESTAMP (TCI_SQL_DATE_YEAR_TO_MILLISECOND)

#define TCI_SQL_TYPE_INTERVAL (TCI_SQL_TYPE | TCI_TYPE_INTERVAL)

#define TCI_SQL_INTERVAL_YEAR (TCI_SQL_TYPE_INTERVAL | TCI_MAKE_HL(TCI_YEAR, TCI_YEAR))
#define TCI_SQL_INTERVAL_YEAR_TO_MONTH (TCI_SQL_TYPE_INTERVAL | TCI_MAKE_HL(TCI_YEAR, TCI_MONTH))
#define TCI_SQL_INTERVAL_MONTH (TCI_SQL_TYPE_INTERVAL | TCI_MAKE_HL(TCI_MONTH, TCI_MONTH))
#define TCI_SQL_INTERVAL_DAY (TCI_SQL_TYPE_INTERVAL | TCI_MAKE_HL(TCI_DAY, TCI_DAY))
#define TCI_SQL_INTERVAL_DAY_TO_HOUR (TCI_SQL_TYPE_INTERVAL | TCI_MAKE_HL(TCI_DAY, TCI_HOUR))
#define TCI_SQL_INTERVAL_DAY_TO_MINUTE (TCI_SQL_TYPE_INTERVAL | TCI_MAKE_HL(TCI_DAY, TCI_MINUTE))
#define TCI_SQL_INTERVAL_DAY_TO_SECOND (TCI_SQL_TYPE_INTERVAL | TCI_MAKE_HL(TCI_DAY, TCI_SECOND))
#define TCI_SQL_INTERVAL_DAY_TO_MILLISECOND (TCI_SQL_TYPE_INTERVAL | TCI_MAKE_HL(TCI_DAY, TCI_MILLISECOND))
#define TCI_SQL_INTERVAL_HOUR (TCI_SQL_TYPE_INTERVAL | TCI_MAKE_HL(TCI_HOUR, TCI_HOUR))
#define TCI_SQL_INTERVAL_HOUR_TO_MINUTE (TCI_SQL_TYPE_INTERVAL | TCI_MAKE_HL(TCI_HOUR, TCI_MINUTE))
#define TCI_SQL_INTERVAL_HOUR_TO_SECOND (TCI_SQL_TYPE_INTERVAL | TCI_MAKE_HL(TCI_HOUR, TCI_SECOND))
#define TCI_SQL_INTERVAL_HOUR_TO_MILLISECOND (TCI_SQL_TYPE_INTERVAL | TCI_MAKE_HL(TCI_HOUR, TCI_MILLISECOND))
#define TCI_SQL_INTERVAL_MINUTE (TCI_SQL_TYPE_INTERVAL | TCI_MAKE_HL(TCI_MINUTE, TCI_MINUTE))
#define TCI_SQL_INTERVAL_MINUTE_TO_SECOND (TCI_SQL_TYPE_INTERVAL | TCI_MAKE_HL(TCI_MINUTE, TCI_SECOND))
#define TCI_SQL_INTERVAL_MINUTE_TO_MILLISECOND (TCI_SQL_TYPE_INTERVAL | TCI_MAKE_HL(TCI_MINUTE, TCI_MILLISECOND))
#define TCI_SQL_INTERVAL_SECOND (TCI_SQL_TYPE_INTERVAL | TCI_MAKE_HL(TCI_SECOND, TCI_SECOND))
#define TCI_SQL_INTERVAL_SECOND_TO_MILLISECOND (TCI_SQL_TYPE_INTERVAL | TCI_MAKE_HL(TCI_SECOND, TCI_MILLISECOND))
#define TCI_SQL_INTERVAL_MILLISECOND (TCI_SQL_TYPE_INTERVAL | TCI_MAKE_HL(TCI_MILLISECOND, TCI_MILLISECOND))

/* attribute ids */
#define TCI_ATTR_BULKSIZE 1
#define TCI_ATTR_CODEPAGE 2
#define TCI_ATTR_COLUMN_ACTSIZE 3
#define TCI_ATTR_COLUMN_BOUND 4
#define TCI_ATTR_COLUMN_BUFFER 5
#define TCI_ATTR_COLUMN_BUFFERTYPE 6
#define TCI_ATTR_COLUMN_COUNT 7
#define TCI_ATTR_COLUMN_INDICATOR 8
#define TCI_ATTR_COLUMN_MAXSIZE 9
#define TCI_ATTR_COLUMN_NAME 10
#define TCI_ATTR_COLUMN_NAME_FROM_DB 11
#define TCI_ATTR_COLUMN_PRECISION 12
#define TCI_ATTR_COLUMN_SCALE 13
#define TCI_ATTR_COLUMN_TYPE 14
#define TCI_ATTR_CONNECTION 15
#define TCI_ATTR_CONNECTION_COUNT 16
#define TCI_ATTR_CONNECTION_TIMEOUT 17
#define TCI_ATTR_CONSISTENCY_LEVEL 18
#define TCI_ATTR_DATA_DIRECTORY 19
#define TCI_ATTR_DATABASE_NAME 20
#define TCI_ATTR_ENVIRONMENT 21
#define TCI_ATTR_ERROR 22
#define TCI_ATTR_ERROR_COUNT 23
#define TCI_ATTR_SCROLLABLE 24
#define TCI_ATTR_NAME 25
#define TCI_ATTR_PARAMETER_BOUND 26
#define TCI_ATTR_PARAMETER_BUFFER 27
#define TCI_ATTR_PARAMETER_BUFFERTYPE 28
#define TCI_ATTR_PARAMETER_COUNT 29
#define TCI_ATTR_PARAMETER_INDICATOR 30
#define TCI_ATTR_PARAMETER_MAXSIZE 31
#define TCI_ATTR_PARAMETER_PRECISION 32
#define TCI_ATTR_PARAMETER_SCALE 33
#define TCI_ATTR_PARAMETER_TYPE 34
#define TCI_ATTR_POSITION 35
#define TCI_ATTR_QUERY_TYPE 36
#define TCI_ATTR_QUERY_UPDATABLE 37
#define TCI_ATTR_RESULTSET 38
#define TCI_ATTR_RESULTSET_COUNT 39
#define TCI_ATTR_ROWCOUNT 40
#define TCI_ATTR_SINGLEBYTE_CHARSET 41
#define TCI_ATTR_SORTORDER 42
#define TCI_ATTR_SQL 43
#define TCI_ATTR_STATE 44
#define TCI_ATTR_STATEMENT 45
#define TCI_ATTR_STATEMENT_COUNT 46
#define TCI_ATTR_STATEMENT_TIMEOUT 47
#define TCI_ATTR_TIMEOUT 48
#define TCI_ATTR_TRANSACTION 49
#define TCI_ATTR_TRANSACTION_COUNT 50
#define TCI_ATTR_TRANSACTION_TIMEOUT 51
#define TCI_ATTR_USER_NAME 52
#define TCI_ATTR_WIDECHAR_SUBSTITUTE 53
#define TCI_ATTR_RECORDS_TRIED 54
#define TCI_ATTR_RECORDS_TOUCHED 55
#define TCI_ATTR_INIFILE 56
#define TCI_ATTR_INSENSITIVE 57
#define TCI_ATTR_EOD 58
#define TCI_ATTR_TRACEFILE 59
#define TCI_ATTR_TRACE 60
#define TCI_ATTR_REFERENCED_RESULTSET 61
#define TCI_ATTR_ABORT_CALLBACK 62
#define TCI_ATTR_CLIENTCODEPAGE 63
#define TCI_ATTR_NUMBER_OPEN_RESULTSETS 64
#define TCI_ATTR_CHAR_SUBSTITUTE 65
#define TCI_ATTR_PLANFILE 66
#define TCI_ATTR_PLANFILE_MODE 67
#define TCI_ATTR_VERSION 68
#define TCI_ATTR_NUMBER_PARAMETER_BINDINGS 69
#define TCI_ATTR_NUMBER_COLUMN_BINDINGS 70
#define TCI_ATTR_PARAMETER_NAME 71
#define TCI_ATTR_PARAMETER_MODE 72
#define TCI_ATTR_PARAMETER_TYPENAME 73
#define TCI_ATTR_COLUMN_TYPENAME 74
#define TCI_ATTR_PARAMETER_DISPSIZE 75
#define TCI_ATTR_COLUMN_DISPSIZE 76
#define TCI_ATTR_CONTINUE_ON_BULKERROR 77
#define TCI_ATTR_DECIMAL_POINT 78
#define TCI_ATTR_THOUSANDS_SEP 79
#define TCI_ATTR_THOUSANDS_GROUP 80
#define TCI_ATTR_PARAMETER_POSITION 81
#define TCI_ATTR_COLUMN_POSITION 82
#define TCI_ATTR_PARAMETER_BUFFER_SKIP 83
#define TCI_ATTR_PARAMETER_INDICATOR_SKIP 84
#define TCI_ATTR_PARAMETER_ACTSIZE_SKIP 85
#define TCI_ATTR_COLUMN_BUFFER_SKIP 86
#define TCI_ATTR_COLUMN_INDICATOR_SKIP 87
#define TCI_ATTR_COLUMN_ACTSIZE_SKIP 88
#define TCI_ATTR_PARAMETER_ACTSIZE 89
#define TCI_ATTR_EXPECT_NTS 90
#define TCI_ATTR_TRUNCATE_NUMBERS 91
#define TCI_ATTR_AUTO_COMMIT 92
#define TCI_ATTR_BYTE_STR_COMPAT 93
#define TCI_ATTR_AUTO_COMMIT_CONS_LEVEL 94
#define TCI_ATTR_AUTO_COMMIT_TIMEOUT 95
#define TCI_ATTR_COLUMN_DATAPOINTER 96
#define TCI_ATTR_SUPPORTED_C_TYPES 97
#define TCI_ATTR_FREE_RECURSIVELY 98
#define TCI_ATTR_COLUMN_DELIVERED_BYTES 99
#define TCI_ATTR_CFILE_LOCALE 100
#define TCI_ATTR_CFILE_CODEPAGE 101
#define TCI_ATTR_COLUMN_ORIG_COLNAME 102
#define TCI_ATTR_COLUMN_ORIG_TABNAME 103
#define TCI_ATTR_COLUMN_ORIG_SCHNAME 104
#define TCI_ATTR_SCHEMA 105
#define TCI_ATTR_TRANSBASE_D 106
#define TCI_ATTR_SINGLECHAR 107
#define TCI_ATTR_LOCALE 108
#define TCI_ATTR_DELIVER_NTS 109

/* states */
#define TCI_SUCCESS 0
#define TCI_ERROR (-1)
#define TCI_NO_DATA_FOUND 100

#define TCI_INVALID_HANDLE 17001


#define TCI_INDEX_OUT_OF_RANGE 17002


#define TCI_TRANSACTIONS_ROLLEDBACK 17027


#define TCI_DATA_TRUNCATION 17031


/* planfile modes */
#define TCI_APPEND 0
#define TCI_OVERWRITE 1
#define TCI_PROFILE 2

/* additional states */
#define NOT_PREPARED 0
#define PREPARED 1

/* TA consistency states */
#define TCI_CONS_1 1
#define TCI_CONS_2 2
#define TCI_CONS_3 3

/* query eod states */
#define TCI_NO_TUPLE 0
#define TCI_ONE_TUPLE 1
#define TCI_MORE_TUPLES 2

/* scroll modes */
#define TCI_FETCH_NEXT 1 /* Fetch next tuple (nTupleOffset ignored) */
#define TCI_FETCH_PRIOR 2 /* Fetch previous tuple (nTupleOffset ignored) */
#define TCI_FETCH_FIRST 3 /* Fetch first tuple (nTupleOffset ignored) */
#define TCI_FETCH_LAST 4 /* Fetch last tuple (nTupleOffset ignored) */
#define TCI_FETCH_ABSOLUTE 5 /* Fetch tuple nTupleOffset from start */
#define TCI_FETCH_RELATIVE 6 /* Fetch tuple nTupleOffset from here */

/* codepages */
#define TCI_CPG_INVALID 0
#define TCI_CPG_UNICODE 1
#define TCI_CPG_PROPRIET 2
#define TCI_CPG_ASCII 3
#define TCI_CPG_LOCALE 4
#define TCI_CPG_UTF8 5
#define TCI_CPG_EUC 6
#define TCI_CPG_JIS 7
#define TCI_CPG_UCS2 8 /* unicode 2 byte */
#define TCI_CPG_UCS4 10 /* unicode 4 byte */
#define TCI_CPG_UCS2_LE 8 /* unicode little endian */
#define TCI_CPG_UTF16_LE TCI_CPG_UCS2_LE
#define TCI_CPG_UCS2_BE 9 /* unicode big endian */
#define TCI_CPG_UTF16_BE TCI_CPG_UCS2_BE
#define TCI_CPG_UCS4_LE 10 /* unicode little endian */
#define TCI_CPG_UTF32_LE TCI_CPG_UCS4_LE
#define TCI_CPG_UCS4_BE 11 /* unicode big endian */
#define TCI_CPG_UTF32_BE TCI_CPG_UCS4_BE
#define TCI_CPG_MACHINE 20

/* compatibility to ODBC */
#define TCI_NTS (-3)
#define TCI_NULL_VALUE (-1)

typedef Uint2 Columnnumber;
typedef Uint2 Attribute;
typedef Uint2 Datatype;
typedef Uint2 Querytype;
typedef Uint1 Consistency;
typedef Uint1 Parametermode;
typedef int TCIState;
typedef struct _TCICodemapEntry {
    unsigned char c;
    Uint4 wc;
} TCICodemapEntry;

/* C data types */

/* TCINumeric: max. representable decimal: 340282366920938463463374607431768211455n127 */
#define TCI_MAX_NUMERIC_LEN 16
typedef struct {
    unsigned char precision;
    signed char scale;
    unsigned char sign; /* 1 if positive, 0 if negative */
    unsigned char val[TCI_MAX_NUMERIC_LEN];
} TCINumeric;

typedef Int8 TCIBigint;
typedef Uint8 TCIUBigint;

typedef struct {
    short year;
    unsigned short month;
    unsigned short day;
} TCIDate;

typedef struct {
    unsigned short hour;
    unsigned short minute;
    unsigned short second;
} TCITime;

typedef struct {
    short year;
    unsigned short month;
    unsigned short day;
    unsigned short hour;
    unsigned short minute;
    unsigned short second;
    unsigned int fraction;
} TCITimestamp;

typedef enum {
    TCI_IS_YEAR = 1,
    TCI_IS_MONTH = 2,
    TCI_IS_DAY = 3,
    TCI_IS_HOUR = 4,
    TCI_IS_MINUTE = 5,
    TCI_IS_SECOND_TO_MILLISECOND = 6,
    TCI_IS_YEAR_TO_MONTH = 7,
    TCI_IS_DAY_TO_HOUR = 8,
    TCI_IS_DAY_TO_MINUTE = 9,
    TCI_IS_DAY_TO_MILLISECOND = 10,
    TCI_IS_HOUR_TO_MINUTE = 11,
    TCI_IS_HOUR_TO_MILLISECOND = 12,
    TCI_IS_MINUTE_TO_MILLISECOND = 13,
    TCI_IS_DAY_TO_SECOND = 14,
    TCI_IS_HOUR_TO_SECOND = 15,
    TCI_IS_MINUTE_TO_SECOND = 16,
    TCI_IS_SECOND = 17,
    TCI_IS_MILLISECOND = 18
} TCIIntervalType;

typedef struct {
    unsigned int year;
    unsigned int month;
} TCIYearMonth;

typedef struct {
    unsigned int day;
    unsigned int hour;
    unsigned int minute;
    unsigned int second;
    unsigned int fraction;
} TCIDaySecond;

typedef struct {
    TCIIntervalType interval_type;
    short interval_sign;
 short filler;
    union {
 TCIYearMonth year_month;
 TCIDaySecond day_second;
    } intval;
} TCIInterval;

/* version struct */
typedef struct _TCIVersion {
    Long4 major_version;
    Long4 minor_version;
    Long4 release;
    Long4 patch;
    Long4 build;
    TCIDate date;
} TCIVersion;

typedef struct TCIEnvironment TCIEnvironment;
typedef struct TCIError TCIError;
typedef struct TCIConnection TCIConnection;
typedef struct TCITransaction TCITransaction;
typedef struct TCIStatement TCIStatement;
typedef struct TCIResultSet TCIResultSet;



#pragma pack()


/* singlechar interface */
TCIState TCI_API TCIAllocEnvironmentA (TCIEnvironment ** ppEnvId );
TCIState TCI_API TCIAllocErrorA (TCIEnvironment * pEnvId , TCIError ** ppErrId );
TCIState TCI_API TCIAllocConnectionA (TCIEnvironment * pEnvId , TCIError * pErrId , TCIConnection ** ppConnId );
TCIState TCI_API TCIAllocTransactionA (TCIEnvironment * pEnvId , TCIError * pErrId , TCITransaction ** ppTaId );
TCIState TCI_API TCIAllocStatementA (TCIConnection * pConnId , TCIError * pErrId , TCIStatement ** ppStmtId );
TCIState TCI_API TCIAllocResultSetA (TCIStatement * pStmtId , TCIError * pErrId , TCIResultSet ** ppResId );

TCIState TCI_API TCIFreeEnvironmentA (TCIEnvironment * pEnvId );
TCIState TCI_API TCIFreeErrorA (TCIError * pErrId );
TCIState TCI_API TCIFreeConnectionA (TCIConnection * pConnId );
TCIState TCI_API TCIFreeTransactionA (TCITransaction * pTaId );
TCIState TCI_API TCIFreeStatementA (TCIStatement * pStmtId );
TCIState TCI_API TCIFreeResultSetA (TCIResultSet * pResId );

TCIState TCI_API TCIConnectA (TCIConnection * pConnId , char * pszDatabaseName );
TCIState TCI_API TCIDisconnectA (TCIConnection * pConnId );
TCIState TCI_API TCILoginA (TCIConnection * pConnId , char * pszUserName , char * pszPassword );
TCIState TCI_API TCILogoutA (TCIConnection * pConnId );
TCIState TCI_API TCIGetBlobPartA (TCIConnection * pConnId , Blob * pBlob , Blobdesc * pBlobdesc , Uint4 nOffset , Uint4 nSize , Uint4 *nBytesRead , Uint4 *nBytesWritten );
TCIState TCI_API TCIGetLobSizeA (TCIConnection * pConnId , Blob * pBlob , Uint4 * nSize );

TCIState TCI_API TCIBeginTransactionA (TCITransaction * pTaId , TCIConnection * pConnId );
TCIState TCI_API TCICommitTransactionA (TCITransaction * pTaId );
TCIState TCI_API TCIRollbackTransactionA (TCITransaction * pTaId );
TCIState TCI_API TCIBreakA (TCITransaction * pTaId );

TCIState TCI_API TCIPrepareA (TCIStatement * pStmtId , char * pszStatement );
TCIState TCI_API TCIBindParameterA (TCIResultSet * pResId , Columnnumber nParamNr , void * pBuffer , Int4 nMaxBufferSize , Int4 * pnBufferSize , Datatype nType , Int2 * pnIndicator );
TCIState TCI_API TCIBindParameterByNameA (TCIResultSet * pResId , char * pszParameterName , void * pBuffer , Int4 nMaxBufferSize , Int4 * pnBufferSize , Datatype nType , Int2 * pnIndicator );
TCIState TCI_API TCIBindParameterArrayOfStructA (TCIResultSet * pResId , Columnnumber nParamNr , size_t nBufferSkip , size_t nIndicatorSkip , size_t nBufferSizeSkip );
TCIState TCI_API TCIBindParameterArrayOfStructByNameA (TCIResultSet * pResId , char * pszParameterName , size_t nBufferSkip , size_t nIndicatorSkip , size_t nBufferSizeSkip );
TCIState TCI_API TCIUnbindParametersA (TCIResultSet * pResId );
TCIState TCI_API TCIExecuteA (TCIResultSet * pResId , Uint4 nIterations , Uint4 nTuplesToFetch );
TCIState TCI_API TCIExecuteDirectA (TCIResultSet * pResId , char * pszStatement , Uint4 nIterations , Uint4 nTuplesToFetch );
TCIState TCI_API TCIBindColumnA (TCIResultSet * pResId , Columnnumber nColNr , void * pBuffer , Int4 nMaxBufferSize , Int4 * pActualSize , Datatype nType , Int2 * pIndicator );
TCIState TCI_API TCIBindColumnByNameA (TCIResultSet * pResId , char * pszColumnName , void * pBuffer , Int4 nMaxBufferSize , Int4 * pActualSize , Datatype nType , Int2 * pIndicator );
TCIState TCI_API TCIBindColumnArrayOfStructA (TCIResultSet * pResId , Columnnumber nColNr , size_t nBufferSkip , size_t nIndicatorSkip , size_t nBufferSizeSkip );
TCIState TCI_API TCIBindColumnArrayOfStructByNameA (TCIResultSet * pResId , char * pszColumnName , size_t nBufferSkip , size_t nIndicatorSkip , size_t nBufferSizeSkip );
TCIState TCI_API TCIUnbindColumnsA (TCIResultSet * pResId );
TCIState TCI_API TCIResetColumnA (TCIResultSet * pResId , Columnnumber nColNr );
TCIState TCI_API TCIFetchA (TCIResultSet * pResId , Uint4 nTuplesToFetch , Uint2 nDirection , Int4 nTupleOffset );
TCIState TCI_API TCICloseA (TCIResultSet * pResId );
TCIState TCI_API TCICancelResultSetA (TCIResultSet * pResId );

TCIState TCI_API TCISetDataA (TCIResultSet * pResId , Columnnumber nParamNr , void * pBuffer , Int4 nBufferSize , Datatype nType , Int2 nIndicator );
TCIState TCI_API TCISetDataByNameA (TCIResultSet * pResId , char * pszParameterName , void * pBuffer , Int4 nBufferSize , Datatype nType , Int2 nIndicator );
TCIState TCI_API TCIGetDataA (TCIResultSet * pResId , Columnnumber nColNr , void * pBuffer , Int4 nMaxBufferSize , Int4 * pActualSize , Datatype nType , Int2 * pIndicator );
TCIState TCI_API TCIGetDataByNameA (TCIResultSet * pResId , char * pszColumnName , void * pBuffer , Int4 nMaxBufferSize , Int4 * pActualSize , Datatype nType , Int2 * pIndicator );
TCIState TCI_API TCIGetDataSizeA (TCIResultSet * pResId , Columnnumber nColNr , Datatype nType , Int4 * pActualSize , Int2 * pIndicator );
TCIState TCI_API TCIGetDataSizeByNameA (TCIResultSet * pResId , char * pszColumnName , Datatype nType , Int4 * pActualSize , Int2 * pIndicator );
TCIState TCI_API TCIGetDataCharLengthA (TCIResultSet * pResId , Columnnumber nColNr , Int4 * pCharLength , Int2 * pIndicator );
TCIState TCI_API TCIGetDataCharLengthByNameA (TCIResultSet * pResId , char * pszColumnName , Int4 * pCharLength , Int2 * pIndicator );

TCIState TCI_API TCIGetErrorA (TCIError * pErrId , Uint4 nRecord , Uint2 nthError , char * pErrorMessage , Uint4 nMaxMessageSize , Error * pErrorCode , char * pSqlstate );
TCIState TCI_API TCIGetEnvironmentErrorA (TCIEnvironment * pEnvId , Uint2 nthError , char * pErrorMessage , Uint4 nMaxMessageSize , Error * pErrorCode , char * pSqlstate );

TCIState TCI_API TCIGetEnvironmentAttributeA (TCIEnvironment * pEnvId , Uint2 nAttributeCode , Uint4 nNumber , void * pBuffer , Uint4 nMaxBufferSize , Uint4 * pActualSize );
TCIState TCI_API TCIGetErrorAttributeA (TCIError * pErrId , Uint2 nAttributeCode , Uint4 nNumber , void * pBuffer , Uint4 nMaxBufferSize , Uint4 * pActualSize );
TCIState TCI_API TCIGetConnectionAttributeA (TCIConnection * pConnId , Uint2 nAttributeCode , Uint4 nNumber , void * pBuffer , Uint4 nMaxBufferSize , Uint4 * pActualSize );
TCIState TCI_API TCIGetTransactionAttributeA (TCITransaction * pTaId , Uint2 nAttributeCode , Uint4 nNumber , void * pBuffer , Uint4 nMaxBufferSize , Uint4 * pActualSize );
TCIState TCI_API TCIGetStatementAttributeA (TCIStatement * pStmtId , Uint2 nAttributeCode , Uint4 nNumber , void * pBuffer , Uint4 nMaxBufferSize , Uint4 * pActualSize );
TCIState TCI_API TCIGetStatementAttributeByNameA (TCIStatement * pStmtId , Uint2 nAttributeCode , char * pszName , void * pBuffer , Uint4 nMaxBufferSize , Uint4 * pActualSize );
TCIState TCI_API TCIGetResultSetAttributeA (TCIResultSet * pResId , Uint2 nAttributeCode , Uint4 nNumber , void * pBuffer , Uint4 nMaxBufferSize , Uint4 * pActualSize );
TCIState TCI_API TCIGetResultSetAttributeByNameA (TCIResultSet * pResId , Uint2 nAttributeCode , char * pszName , void * pBuffer , Uint4 nMaxBufferSize , Uint4 * pActualSize );

TCIState TCI_API TCISetEnvironmentAttributeA (TCIEnvironment * pEnvId , Uint2 nAttributeCode , Uint4 nNumber , void * pBuffer );
TCIState TCI_API TCISetErrorAttributeA (TCIError * pErrId , Uint2 nAttributeCode , Uint4 nNumber , void * pBuffer );
TCIState TCI_API TCISetConnectionAttributeA (TCIConnection * pConnId , Uint2 nAttributeCode , Uint4 nNumber , void * pBuffer );
TCIState TCI_API TCISetTransactionAttributeA (TCITransaction * pTaId , Uint2 nAttributeCode , Uint4 nNumber , void * pBuffer );
TCIState TCI_API TCISetStatementAttributeA (TCIStatement * pStmtId , Uint2 nAttributeCode , Uint4 nNumber , void * pBuffer );
TCIState TCI_API TCISetResultSetAttributeA (TCIResultSet * pResId , Uint2 nAttributeCode , Uint4 nNumber , void * pBuffer );

TCIState TCI_API TCIReleaseHeapA (TCIResultSet * pResId , void * pBuffer );
/* widechar interface */
TCIState TCI_API TCIAllocEnvironmentW (TCIEnvironment ** ppEnvId );
TCIState TCI_API TCIAllocErrorW (TCIEnvironment * pEnvId , TCIError ** ppErrId );
TCIState TCI_API TCIAllocConnectionW (TCIEnvironment * pEnvId , TCIError * pErrId , TCIConnection ** ppConnId );
TCIState TCI_API TCIAllocTransactionW (TCIEnvironment * pEnvId , TCIError * pErrId , TCITransaction ** ppTaId );
TCIState TCI_API TCIAllocStatementW (TCIConnection * pConnId , TCIError * pErrId , TCIStatement ** ppStmtId );
TCIState TCI_API TCIAllocResultSetW (TCIStatement * pStmtId , TCIError * pErrId , TCIResultSet ** ppResId );

TCIState TCI_API TCIFreeEnvironmentW (TCIEnvironment * pEnvId );
TCIState TCI_API TCIFreeErrorW (TCIError * pErrId );
TCIState TCI_API TCIFreeConnectionW (TCIConnection * pConnId );
TCIState TCI_API TCIFreeTransactionW (TCITransaction * pTaId );
TCIState TCI_API TCIFreeStatementW (TCIStatement * pStmtId );
TCIState TCI_API TCIFreeResultSetW (TCIResultSet * pResId );

TCIState TCI_API TCIConnectW (TCIConnection * pConnId , wchar_t * pszDatabaseName );
TCIState TCI_API TCIDisconnectW (TCIConnection * pConnId );
TCIState TCI_API TCILoginW (TCIConnection * pConnId , wchar_t * pszUserName , wchar_t * pszPassword );
TCIState TCI_API TCILogoutW (TCIConnection * pConnId );
TCIState TCI_API TCIGetBlobPartW (TCIConnection * pConnId , Blob * pBlob , Blobdesc * pBlobdesc , Uint4 nOffset , Uint4 nSize , Uint4 *nBytesRead , Uint4 *nBytesWritten );
TCIState TCI_API TCIGetLobSizeW (TCIConnection * pConnId , Blob * pBlob , Uint4 * nSize );

TCIState TCI_API TCIBeginTransactionW (TCITransaction * pTaId , TCIConnection * pConnId );
TCIState TCI_API TCICommitTransactionW (TCITransaction * pTaId );
TCIState TCI_API TCIRollbackTransactionW (TCITransaction * pTaId );
TCIState TCI_API TCIBreakW (TCITransaction * pTaId );

TCIState TCI_API TCIPrepareW (TCIStatement * pStmtId , wchar_t * pszStatement );
TCIState TCI_API TCIBindParameterW (TCIResultSet * pResId , Columnnumber nParamNr , void * pBuffer , Int4 nMaxBufferSize , Int4 * pnBufferSize , Datatype nType , Int2 * pnIndicator );
TCIState TCI_API TCIBindParameterByNameW (TCIResultSet * pResId , wchar_t * pszParameterName , void * pBuffer , Int4 nMaxBufferSize , Int4 * pnBufferSize , Datatype nType , Int2 * pnIndicator );
TCIState TCI_API TCIBindParameterArrayOfStructW (TCIResultSet * pResId , Columnnumber nParamNr , size_t nBufferSkip , size_t nIndicatorSkip , size_t nBufferSizeSkip );
TCIState TCI_API TCIBindParameterArrayOfStructByNameW (TCIResultSet * pResId , wchar_t * pszParameterName , size_t nBufferSkip , size_t nIndicatorSkip , size_t nBufferSizeSkip );
TCIState TCI_API TCIUnbindParametersW (TCIResultSet * pResId );
TCIState TCI_API TCIExecuteW (TCIResultSet * pResId , Uint4 nIterations , Uint4 nTuplesToFetch );
TCIState TCI_API TCIExecuteDirectW (TCIResultSet * pResId , wchar_t * pszStatement , Uint4 nIterations , Uint4 nTuplesToFetch );
TCIState TCI_API TCIBindColumnW (TCIResultSet * pResId , Columnnumber nColNr , void * pBuffer , Int4 nMaxBufferSize , Int4 * pActualSize , Datatype nType , Int2 * pIndicator );
TCIState TCI_API TCIBindColumnByNameW (TCIResultSet * pResId , wchar_t * pszColumnName , void * pBuffer , Int4 nMaxBufferSize , Int4 * pActualSize , Datatype nType , Int2 * pIndicator );
TCIState TCI_API TCIBindColumnArrayOfStructW (TCIResultSet * pResId , Columnnumber nColNr , size_t nBufferSkip , size_t nIndicatorSkip , size_t nBufferSizeSkip );
TCIState TCI_API TCIBindColumnArrayOfStructByNameW (TCIResultSet * pResId , wchar_t * pszColumnName , size_t nBufferSkip , size_t nIndicatorSkip , size_t nBufferSizeSkip );
TCIState TCI_API TCIUnbindColumnsW (TCIResultSet * pResId );
TCIState TCI_API TCIResetColumnW (TCIResultSet * pResId , Columnnumber nColNr );
TCIState TCI_API TCIFetchW (TCIResultSet * pResId , Uint4 nTuplesToFetch , Uint2 nDirection , Int4 nTupleOffset );
TCIState TCI_API TCICloseW (TCIResultSet * pResId );
TCIState TCI_API TCICancelResultSetW (TCIResultSet * pResId );

TCIState TCI_API TCISetDataW (TCIResultSet * pResId , Columnnumber nParamNr , void * pBuffer , Int4 nBufferSize , Datatype nType , Int2 nIndicator );
TCIState TCI_API TCISetDataByNameW (TCIResultSet * pResId , wchar_t * pszParameterName , void * pBuffer , Int4 nBufferSize , Datatype nType , Int2 nIndicator );
TCIState TCI_API TCIGetDataW (TCIResultSet * pResId , Columnnumber nColNr , void * pBuffer , Int4 nMaxBufferSize , Int4 * pActualSize , Datatype nType , Int2 * pIndicator );
TCIState TCI_API TCIGetDataByNameW (TCIResultSet * pResId , wchar_t * pszColumnName , void * pBuffer , Int4 nMaxBufferSize , Int4 * pActualSize , Datatype nType , Int2 * pIndicator );
TCIState TCI_API TCIGetDataSizeW (TCIResultSet * pResId , Columnnumber nColNr , Datatype nType , Int4 * pActualSize , Int2 * pIndicator );
TCIState TCI_API TCIGetDataSizeByNameW (TCIResultSet * pResId , wchar_t * pszColumnName , Datatype nType , Int4 * pActualSize , Int2 * pIndicator );
TCIState TCI_API TCIGetDataCharLengthW (TCIResultSet * pResId , Columnnumber nColNr , Int4 * pCharLength , Int2 * pIndicator );
TCIState TCI_API TCIGetDataCharLengthByNameW (TCIResultSet * pResId , wchar_t * pszColumnName , Int4 * pCharLength , Int2 * pIndicator );

TCIState TCI_API TCIGetErrorW (TCIError * pErrId , Uint4 nRecord , Uint2 nthError , wchar_t * pErrorMessage , Uint4 nMaxMessageSize , Error * pErrorCode , wchar_t * pSqlstate );
TCIState TCI_API TCIGetEnvironmentErrorW (TCIEnvironment * pEnvId , Uint2 nthError , wchar_t * pErrorMessage , Uint4 nMaxMessageSize , Error * pErrorCode , wchar_t * pSqlstate );

TCIState TCI_API TCIGetEnvironmentAttributeW (TCIEnvironment * pEnvId , Uint2 nAttributeCode , Uint4 nNumber , void * pBuffer , Uint4 nMaxBufferSize , Uint4 * pActualSize );
TCIState TCI_API TCIGetErrorAttributeW (TCIError * pErrId , Uint2 nAttributeCode , Uint4 nNumber , void * pBuffer , Uint4 nMaxBufferSize , Uint4 * pActualSize );
TCIState TCI_API TCIGetConnectionAttributeW (TCIConnection * pConnId , Uint2 nAttributeCode , Uint4 nNumber , void * pBuffer , Uint4 nMaxBufferSize , Uint4 * pActualSize );
TCIState TCI_API TCIGetTransactionAttributeW (TCITransaction * pTaId , Uint2 nAttributeCode , Uint4 nNumber , void * pBuffer , Uint4 nMaxBufferSize , Uint4 * pActualSize );
TCIState TCI_API TCIGetStatementAttributeW (TCIStatement * pStmtId , Uint2 nAttributeCode , Uint4 nNumber , void * pBuffer , Uint4 nMaxBufferSize , Uint4 * pActualSize );
TCIState TCI_API TCIGetStatementAttributeByNameW (TCIStatement * pStmtId , Uint2 nAttributeCode , wchar_t * pszName , void * pBuffer , Uint4 nMaxBufferSize , Uint4 * pActualSize );
TCIState TCI_API TCIGetResultSetAttributeW (TCIResultSet * pResId , Uint2 nAttributeCode , Uint4 nNumber , void * pBuffer , Uint4 nMaxBufferSize , Uint4 * pActualSize );
TCIState TCI_API TCIGetResultSetAttributeByNameW (TCIResultSet * pResId , Uint2 nAttributeCode , wchar_t * pszName , void * pBuffer , Uint4 nMaxBufferSize , Uint4 * pActualSize );

TCIState TCI_API TCISetEnvironmentAttributeW (TCIEnvironment * pEnvId , Uint2 nAttributeCode , Uint4 nNumber , void * pBuffer );
TCIState TCI_API TCISetErrorAttributeW (TCIError * pErrId , Uint2 nAttributeCode , Uint4 nNumber , void * pBuffer );
TCIState TCI_API TCISetConnectionAttributeW (TCIConnection * pConnId , Uint2 nAttributeCode , Uint4 nNumber , void * pBuffer );
TCIState TCI_API TCISetTransactionAttributeW (TCITransaction * pTaId , Uint2 nAttributeCode , Uint4 nNumber , void * pBuffer );
TCIState TCI_API TCISetStatementAttributeW (TCIStatement * pStmtId , Uint2 nAttributeCode , Uint4 nNumber , void * pBuffer );
TCIState TCI_API TCISetResultSetAttributeW (TCIResultSet * pResId , Uint2 nAttributeCode , Uint4 nNumber , void * pBuffer );

TCIState TCI_API TCIReleaseHeapW (TCIResultSet * pResId , void * pBuffer );
#if defined(_UNICODE)
/******************************************************** 

                      T r a n s B a s e / C D
  @(#) tciw.h:   V7.1.2.21.3
      Project: 4.4208.1.215
      2015/08/03 11:17:40

  Copyright (c) 1995 - 
  Transaction Software GmbH
  D 81739 Munich 

 *********************************************************/

/* Module begin */
#ifndef _TCIW_H
#define _TCIW_H

#define TCI_C_TCHAR TCI_C_WCHAR
#define TCI_C_TFILE TCI_C_WFILE
#define TCI_C_TCFILE TCI_C_WCFILE
#define TCI_C_TCHARPTR TCI_C_WCHARPTR
#define TCI_C_TFILEPTR TCI_C_WFILEPTR
#define TCI_C_TCFILEPTR TCI_C_WCFILEPTR

#define TCIAllocEnvironment TCIAllocEnvironmentW
#define TCIAllocError TCIAllocErrorW
#define TCIAllocConnection TCIAllocConnectionW
#define TCIAllocTransaction TCIAllocTransactionW
#define TCIAllocStatement TCIAllocStatementW
#define TCIAllocResultSet TCIAllocResultSetW
#define TCIFreeEnvironment TCIFreeEnvironmentW
#define TCIFreeError TCIFreeErrorW
#define TCIFreeConnection TCIFreeConnectionW
#define TCIFreeTransaction TCIFreeTransactionW
#define TCIFreeStatement TCIFreeStatementW
#define TCIFreeResultSet TCIFreeResultSetW
#define TCIConnect TCIConnectW
#define TCIDisconnect TCIDisconnectW
#define TCILogin TCILoginW
#define TCILogout TCILogoutW
#define TCIBeginTransaction TCIBeginTransactionW
#define TCICommitTransaction TCICommitTransactionW
#define TCIRollbackTransaction TCIRollbackTransactionW
#define TCIBreak TCIBreakW
#define TCIPrepare TCIPrepareW
#define TCIBindParameter TCIBindParameterW
#define TCIBindParameterByName TCIBindParameterByNameW
#define TCIBindParameterArrayOfStruct TCIBindParameterArrayOfStructW
#define TCIBindParameterArrayOfStructByName TCIBindParameterArrayOfStructByNameW
#define TCIUnbindParameters TCIUnbindParametersW
#define TCIExecute TCIExecuteW
#define TCIExecuteDirect TCIExecuteDirectW
#define TCIBindColumn TCIBindColumnW
#define TCIBindColumnByName TCIBindColumnByNameW
#define TCIBindColumnArrayOfStruct TCIBindColumnArrayOfStructW
#define TCIBindColumnArrayOfStructByName TCIBindColumnArrayOfStructByNameW
#define TCIUnbindColumns TCIUnbindColumnsW
#define TCIResetColumn TCIResetColumnW
#define TCIFetch TCIFetchW
#define TCIClose TCICloseW
#define TCICancelResultSet TCICancelResultSetW
#define TCISetData TCISetDataW
#define TCISetDataByName TCISetDataByNameW
#define TCIGetData TCIGetDataW
#define TCIGetDataByName TCIGetDataByNameW
#define TCIGetDataSize TCIGetDataSizeW
#define TCIGetDataSizeByName TCIGetDataSizeByNameW
#define TCIGetDataCharLength TCIGetDataCharLengthW
#define TCIGetDataCharLengthByName TCIGetDataCharLengthByNameW
#define TCIGetError TCIGetErrorW
#define TCIGetEnvironmentError TCIGetEnvironmentErrorW
#define TCIGetEnvironmentAttribute TCIGetEnvironmentAttributeW
#define TCIGetErrorAttribute TCIGetErrorAttributeW
#define TCIGetConnectionAttribute TCIGetConnectionAttributeW
#define TCIGetTransactionAttribute TCIGetTransactionAttributeW
#define TCIGetStatementAttribute TCIGetStatementAttributeW
#define TCIGetStatementAttributeByName TCIGetStatementAttributeByNameW
#define TCIGetResultSetAttribute TCIGetResultSetAttributeW
#define TCIGetResultSetAttributeByName TCIGetResultSetAttributeByNameW
#define TCISetEnvironmentAttribute TCISetEnvironmentAttributeW
#define TCISetErrorAttribute TCISetErrorAttributeW
#define TCISetConnectionAttribute TCISetConnectionAttributeW
#define TCISetTransactionAttribute TCISetTransactionAttributeW
#define TCISetStatementAttribute TCISetStatementAttributeW
#define TCISetResultSetAttribute TCISetResultSetAttributeW
#define TCIReleaseHeap TCIReleaseHeapW
#endif
#else
/******************************************************** 

                      T r a n s B a s e / C D
  @(#) tcia.h:   V7.1.2.21.3
      Project: 4.4208.1.215
      2015/08/03 11:17:40

  Copyright (c) 1995 - 
  Transaction Software GmbH
  D 81739 Munich 

 *********************************************************/

/* Module begin */
#ifndef _TCIA_H
#define _TCIA_H

#define TCI_C_TCHAR TCI_C_SCHAR
#define TCI_C_TFILE TCI_C_SFILE
#define TCI_C_TCFILE TCI_C_SCFILE
#define TCI_C_TCHARPTR TCI_C_SCHARPTR
#define TCI_C_TFILEPTR TCI_C_SFILEPTR
#define TCI_C_TCFILEPTR TCI_C_SCFILEPTR

#define TCIAllocEnvironment TCIAllocEnvironmentA
#define TCIAllocError TCIAllocErrorA
#define TCIAllocConnection TCIAllocConnectionA
#define TCIAllocTransaction TCIAllocTransactionA
#define TCIAllocStatement TCIAllocStatementA
#define TCIAllocResultSet TCIAllocResultSetA
#define TCIFreeEnvironment TCIFreeEnvironmentA
#define TCIFreeError TCIFreeErrorA
#define TCIFreeConnection TCIFreeConnectionA
#define TCIFreeTransaction TCIFreeTransactionA
#define TCIFreeStatement TCIFreeStatementA
#define TCIFreeResultSet TCIFreeResultSetA
#define TCIConnect TCIConnectA
#define TCIDisconnect TCIDisconnectA
#define TCILogin TCILoginA
#define TCILogout TCILogoutA
#define TCIBeginTransaction TCIBeginTransactionA
#define TCICommitTransaction TCICommitTransactionA
#define TCIRollbackTransaction TCIRollbackTransactionA
#define TCIBreak TCIBreakA
#define TCIPrepare TCIPrepareA
#define TCIBindParameter TCIBindParameterA
#define TCIBindParameterByName TCIBindParameterByNameA
#define TCIBindParameterArrayOfStruct TCIBindParameterArrayOfStructA
#define TCIBindParameterArrayOfStructByName TCIBindParameterArrayOfStructByNameA
#define TCIUnbindParameters TCIUnbindParametersA
#define TCIExecute TCIExecuteA
#define TCIExecuteDirect TCIExecuteDirectA
#define TCIBindColumn TCIBindColumnA
#define TCIBindColumnByName TCIBindColumnByNameA
#define TCIBindColumnArrayOfStruct TCIBindColumnArrayOfStructA
#define TCIBindColumnArrayOfStructByName TCIBindColumnArrayOfStructByNameA
#define TCIUnbindColumns TCIUnbindColumnsA
#define TCIResetColumn TCIResetColumnA
#define TCIFetch TCIFetchA
#define TCIClose TCICloseA
#define TCICancelResultSet TCICancelResultSetA
#define TCISetData TCISetDataA
#define TCISetDataByName TCISetDataByNameA
#define TCIGetData TCIGetDataA
#define TCIGetDataByName TCIGetDataByNameA
#define TCIGetDataSize TCIGetDataSizeA
#define TCIGetDataSizeByName TCIGetDataSizeByNameA
#define TCIGetDataCharLength TCIGetDataCharLengthA
#define TCIGetDataCharLengthByName TCIGetDataCharLengthByNameA
#define TCIGetError TCIGetErrorA
#define TCIGetEnvironmentError TCIGetEnvironmentErrorA
#define TCIGetEnvironmentAttribute TCIGetEnvironmentAttributeA
#define TCIGetErrorAttribute TCIGetErrorAttributeA
#define TCIGetConnectionAttribute TCIGetConnectionAttributeA
#define TCIGetTransactionAttribute TCIGetTransactionAttributeA
#define TCIGetStatementAttribute TCIGetStatementAttributeA
#define TCIGetStatementAttributeByName TCIGetStatementAttributeByNameA
#define TCIGetResultSetAttribute TCIGetResultSetAttributeA
#define TCIGetResultSetAttributeByName TCIGetResultSetAttributeByNameA
#define TCISetEnvironmentAttribute TCISetEnvironmentAttributeA
#define TCISetErrorAttribute TCISetErrorAttributeA
#define TCISetConnectionAttribute TCISetConnectionAttributeA
#define TCISetTransactionAttribute TCISetTransactionAttributeA
#define TCISetStatementAttribute TCISetStatementAttributeA
#define TCISetResultSetAttribute TCISetResultSetAttributeA
#define TCIReleaseHeap TCIReleaseHeapA
#endif
#endif
#if defined(__cplusplus)
}
#endif
#endif
