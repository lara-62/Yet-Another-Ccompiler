/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include<bits/stdc++.h>
#include "1905062.h"


using namespace std;

int yyparse(void);
int yylex(void);
extern FILE *yyin;
ofstream logfile;
ofstream errorfile;
ofstream parsefile;
extern int line_count;
extern int error_count;
FILE *logout;
extern int yylineno;
SymbolTable *table;

//parameters for including them in the scope
vector<Symbolinfo*>*function_parameter;
vector<Symbolinfo*>*variable_declaration;
vector<Symbolinfo*>*ArgumentList;
vector<Symbolinfo*>*Argument;

void DFS(Symbolinfo* StartState,string space)
{    
	 
     if(StartState->getisLeaf())
	    {   
			parsefile<<space<<StartState->getType()<<" : "<<StartState->getName()<<"\t"<<"<Line: "<<StartState->GetStartLine()<<">"<<endl;
			
			return;
		}
	 parsefile<<space<<StartState->getType()<<" : "<<StartState->getName()<<" \t"<<"<Line: "<<StartState->GetStartLine()<<"-"<<StartState->GetEndLine()<<">"<<endl;
	 vector<Symbolinfo*>*temp=StartState->getChildList();
	 for(Symbolinfo *next:*temp)
	 {
		DFS(next,space+" ");
	 }
	    
}

void yyerror(char *s)
{
	//write your code
}
void variable_declare(string type,vector<Symbolinfo*>* variablelist)
{   cout<<"what the"<<endl;
	for(Symbolinfo *symbol:*variablelist)
	{   cout<<"what the2"<<endl;
		if (type=="VOID")
      {  cout<<"bleh1"<<endl;
		errorfile<<"Line# "<<line_count<<": Variable or field '"<<symbol->getName()<<"' declared void"<<endl;
		return;
	  }
	  else {
		cout<<"bleh2"<<endl;
		if(table->Insert(symbol->getName(),symbol->getType()))
		{  cout<<"bleh3"<<endl;
          Symbolinfo *info=table->LookUp(symbol->getName());
		  info->setDataType(type);
		  if(symbol->getisArray())
		     {
				info->setisArray(true);
				info->setarraysize(symbol->getarraysize());
			 }      
		}
		else
		{    cout<<"bleh4"<<endl;
			Symbolinfo *info=table->LookUp(symbol->getName());
			if(info->getDataType()!=symbol->getDataType())
			   {
				errorfile<<"Line# "<<line_count<<": Conflicting types for'"<<symbol->getName()<<"'"<<endl;

			   }
			else if(info->getisArray()!=symbol->getisArray())
			{
				errorfile<<"Line# "<<line_count<<": Conflicting types for'"<<symbol->getName()<<"'"<<endl;
			}
			else
			{
				errorfile<<"Line# "<<line_count<<": redeclaration of '"<<symbol->getName()<<"'"<<endl;
			}
		}
	  }
		
	}
}
void define_function(string returnType,Symbolinfo* function_name,vector<Symbolinfo*>*param)
{
	 if(table->Insert(function_name->getName(),function_name->getType()))
	   {
		Symbolinfo* temp=table->LookUp(function_name->getName());
		temp->setDataType(returnType);
		temp->setisFunctionDefination(true);
		temp->setisFunction(true);
		for(int i=0;i<(*param).size();i++)
			 {  cout<<"testing:"<<(*param)[i]->getDataType()<<" ";
			    Symbolinfo *test=new Symbolinfo((*param)[i]->getName(),(*param)[i]->getType(),(*param)[i]->getDataType());
				temp->add_parameter(test);
			 }
	   }
	   else
	   {
		  Symbolinfo* temp=table->LookUp(function_name->getName());
		  if (temp->getDataType()!=returnType)
		     {
				errorfile<<"Line# "<<line_count<<": Conflicting types for '"<<function_name->getName()<<"'"<<endl;
				return;
				
			 }
		  if(temp->getisFunctionDefination()==true)
		  {
			errorfile<<"Line# "<<line_count<<": Redefinition of '"<<function_name->getName()<<"'"<<endl;
			return;
		  }
		  if(temp->getisFunctionDeclaration()==true)
		  {  
             vector<Symbolinfo*>*list=temp->getParameterList();
			 if((*list).size()!=(*param).size())
			 {
				errorfile<<"Line# "<<line_count<<": Conflicting types for '"<<function_name->getName()<<"'"<<endl;
				return;
				
			 }
			 cout<<"hello"<<endl;
			 	 for(Symbolinfo *y:*list)
		{
			cout<<y->getDataType()<<" ";
		}
			 for(int i=0;i<(*list).size();i++)
			 {
				if((*list)[i]->getDataType()!=(*param)[i]->getDataType())
				{
					errorfile<<"Line# "<<line_count<<": Type mismatch for argument "<<i+1<<" of '"<<function_name->getName()<<"'"<<endl;
					
				}
			 }
		  }
		  else
		  {
			errorfile<<"Line# "<<line_count<<": '"<<function_name->getName()<<"' redeclared as different kind of symbol"<<endl;
			return;
		  }
	   }
}
void declare_function(string returnType,Symbolinfo* function_name,vector<Symbolinfo*>*param)
{
       if(table->Insert(function_name->getName(),function_name->getType()))
	   {
		Symbolinfo* temp=table->LookUp(function_name->getName());
		temp->setDataType(returnType);
		temp->setisFunctionDeclaration(true);
		temp->setisFunction(true);
		cout<<"ok2"<<endl;
		if(param!=NULL){
		cout<<(*param).size()<<endl;
		for(Symbolinfo* symbol:*param)
			 {  
				Symbolinfo *test=new Symbolinfo(symbol->getName(),symbol->getType(),symbol->getDataType());
				temp->add_parameter(test);
			 }
			cout<<"ok3"<<endl;
		Symbolinfo *x=table->LookUp(function_name->getName());
		vector<Symbolinfo*>* ok=x->getParameterList();
		for(Symbolinfo *y:*ok)
		{
			cout<<y->getDataType()<<" ";
		}
		cout<<endl;
		}
		cout<<"okay4"<<endl;
	   }
	   else
	   {
		  Symbolinfo* temp=table->LookUp(function_name->getName());
		  if (temp->getDataType()!=returnType)
		     {
				errorfile<<"Line# "<<line_count<<": Conflicting types for '"<<function_name->getName()<<"'"<<endl;
				return;
				
			 }
		  if(temp->getisFunctionDeclaration()==true)
		  {
			errorfile<<"Line# "<<line_count<<": Redeclaration of '"<<function_name->getName()<<"'"<<endl;
			return;
		  }
		  if(temp->getisFunctionDefination()==true)
		  {  
             vector<Symbolinfo*>*list=temp->getParameterList();
			 if((*list).size()!=(*param).size())
			 {
				errorfile<<"Line# "<<line_count<<": Conflicting types for '"<<function_name->getName()<<"'"<<endl;
				return;
				
			 }
		
			 for(int i=0;i<(*list).size();i++)
			 {
				if((*list)[i]->getDataType()!=(*param)[i]->getDataType())
				{
					errorfile<<"Line# "<<line_count<<": Type mismatch for argument "<<i+1<<" of '"<<function_name->getName()<<"'"<<endl;
					
				}
			 }
		  }
		  else
		  {
			errorfile<<"Line# "<<line_count<<": '"<<function_name->getName()<<"' redeclared as different kind of symbol"<<endl;
			return;
		  }
	   }
}
void add_parameter_toScopeTable(vector<Symbolinfo*>*param)
{
   if (param !=NULL)
    {
       for(Symbolinfo* symbol:*param)
	   { 
		if(symbol->getName()!=""){
		 if(table->Insert(symbol->getName(),symbol->getType()))
		 {
			Symbolinfo *temp=table->LookUp(symbol->getName());
			if(symbol->getisArray()){
			  temp->setisArray(symbol->getisArray());
			  temp->setarraysize(symbol->getarraysize());
			}
			temp->setDataType(symbol->getDataType());
		 }
		 else
		 {
			errorfile<<"Line# "<<line_count<<": Redefinition of parameter '"<<symbol->getName()<<"'"<<endl;
			return;
		 }
		}
	   }
    }
	param=NULL;
}
void clear_list(vector<Symbolinfo*>*symbols)
{
       for(Symbolinfo* symbol:*symbols)
	   {
		delete symbol;
	   }
	   delete symbols;
}

//function call;

Symbolinfo* CallFunction(Symbolinfo* function_name,vector<Symbolinfo*>*symbols)
{
     Symbolinfo* temp=table->LookUp(function_name->getName());
	 if(temp==NULL)
	 {  
		errorfile<<"Line# "<<line_count<<": Undeclared function '"<<function_name->getName()<<"'"<<endl;
		

	 }
	 else
	 {
        if(temp->getisFunction()==false)
		{
			temp=NULL;
			errorfile<<"Line# "<<line_count<<": Undeclared function '"<<function_name->getName()<<"'"<<endl;
		}
		else
		{
			vector<Symbolinfo*>* argu=temp->getParameterList();
			cout<<"SIZE"<<(*argu).size()<<endl;
			if((*argu).size()<(*symbols).size())
			{
				errorfile<<"Line# "<<line_count<<": Too many arguments to function '"<<function_name->getName()<<"'"<<endl;
				
			}
			else if((*argu).size()>(*symbols).size())
			{
				errorfile<<"Line# "<<line_count<<": Too few arguments to function '"<<function_name->getName()<<"'"<<endl;
				
			}
			else
			{
                for(int i=0;i<(*argu).size();i++)
				{
					if((*argu)[i]->getDataType()!=(*symbols)[i]->getDataType())
					{
						cout<<(*argu)[i]->getDataType()<<"okay"<<(*symbols)[i]->getDataType()<<"okay"<<endl;
                      errorfile<<"Line# "<<line_count<<": Type mismatch for argument "<<i+1<<" of '"<<function_name->getName()<<"'"<<endl;
					  
					}
				}
			}

		}
	 }
	return temp;
}


#line 372 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IF = 258,                      /* IF  */
    ELSE = 259,                    /* ELSE  */
    FOR = 260,                     /* FOR  */
    WHILE = 261,                   /* WHILE  */
    DO = 262,                      /* DO  */
    BREAK = 263,                   /* BREAK  */
    INT = 264,                     /* INT  */
    CHAR = 265,                    /* CHAR  */
    FLOAT = 266,                   /* FLOAT  */
    DOUBLE = 267,                  /* DOUBLE  */
    VOID = 268,                    /* VOID  */
    RETURN = 269,                  /* RETURN  */
    SWITCH = 270,                  /* SWITCH  */
    CASE = 271,                    /* CASE  */
    DEFAULT = 272,                 /* DEFAULT  */
    CONTINUE = 273,                /* CONTINUE  */
    PRINTLN = 274,                 /* PRINTLN  */
    ADDOP = 275,                   /* ADDOP  */
    MULOP = 276,                   /* MULOP  */
    RELOP = 277,                   /* RELOP  */
    LOGICOP = 278,                 /* LOGICOP  */
    BITOP = 279,                   /* BITOP  */
    INCOP = 280,                   /* INCOP  */
    DECOP = 281,                   /* DECOP  */
    ASSIGNOP = 282,                /* ASSIGNOP  */
    NOT = 283,                     /* NOT  */
    LPAREN = 284,                  /* LPAREN  */
    RPAREN = 285,                  /* RPAREN  */
    LCURL = 286,                   /* LCURL  */
    RCURL = 287,                   /* RCURL  */
    LSQUARE = 288,                 /* LSQUARE  */
    RSQUARE = 289,                 /* RSQUARE  */
    COMMA = 290,                   /* COMMA  */
    SEMICOLON = 291,               /* SEMICOLON  */
    CONST_INT = 292,               /* CONST_INT  */
    CONST_FLOAT = 293,             /* CONST_FLOAT  */
    CONST_CHAR = 294,              /* CONST_CHAR  */
    ID = 295,                      /* ID  */
    MULTI_LINE_STRING = 296,       /* MULTI_LINE_STRING  */
    SINGLE_LINE_STRING = 297,      /* SINGLE_LINE_STRING  */
    LOWER_THAN_ELSE = 298          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define IF 258
#define ELSE 259
#define FOR 260
#define WHILE 261
#define DO 262
#define BREAK 263
#define INT 264
#define CHAR 265
#define FLOAT 266
#define DOUBLE 267
#define VOID 268
#define RETURN 269
#define SWITCH 270
#define CASE 271
#define DEFAULT 272
#define CONTINUE 273
#define PRINTLN 274
#define ADDOP 275
#define MULOP 276
#define RELOP 277
#define LOGICOP 278
#define BITOP 279
#define INCOP 280
#define DECOP 281
#define ASSIGNOP 282
#define NOT 283
#define LPAREN 284
#define RPAREN 285
#define LCURL 286
#define RCURL 287
#define LSQUARE 288
#define RSQUARE 289
#define COMMA 290
#define SEMICOLON 291
#define CONST_INT 292
#define CONST_FLOAT 293
#define CONST_CHAR 294
#define ID 295
#define MULTI_LINE_STRING 296
#define SINGLE_LINE_STRING 297
#define LOWER_THAN_ELSE 298

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 303 "parser.y"

	Symbolinfo* symbolinfo; 
	vector<Symbolinfo*>* symbolinfo_list;

#line 516 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_FOR = 5,                        /* FOR  */
  YYSYMBOL_WHILE = 6,                      /* WHILE  */
  YYSYMBOL_DO = 7,                         /* DO  */
  YYSYMBOL_BREAK = 8,                      /* BREAK  */
  YYSYMBOL_INT = 9,                        /* INT  */
  YYSYMBOL_CHAR = 10,                      /* CHAR  */
  YYSYMBOL_FLOAT = 11,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 12,                    /* DOUBLE  */
  YYSYMBOL_VOID = 13,                      /* VOID  */
  YYSYMBOL_RETURN = 14,                    /* RETURN  */
  YYSYMBOL_SWITCH = 15,                    /* SWITCH  */
  YYSYMBOL_CASE = 16,                      /* CASE  */
  YYSYMBOL_DEFAULT = 17,                   /* DEFAULT  */
  YYSYMBOL_CONTINUE = 18,                  /* CONTINUE  */
  YYSYMBOL_PRINTLN = 19,                   /* PRINTLN  */
  YYSYMBOL_ADDOP = 20,                     /* ADDOP  */
  YYSYMBOL_MULOP = 21,                     /* MULOP  */
  YYSYMBOL_RELOP = 22,                     /* RELOP  */
  YYSYMBOL_LOGICOP = 23,                   /* LOGICOP  */
  YYSYMBOL_BITOP = 24,                     /* BITOP  */
  YYSYMBOL_INCOP = 25,                     /* INCOP  */
  YYSYMBOL_DECOP = 26,                     /* DECOP  */
  YYSYMBOL_ASSIGNOP = 27,                  /* ASSIGNOP  */
  YYSYMBOL_NOT = 28,                       /* NOT  */
  YYSYMBOL_LPAREN = 29,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 30,                    /* RPAREN  */
  YYSYMBOL_LCURL = 31,                     /* LCURL  */
  YYSYMBOL_RCURL = 32,                     /* RCURL  */
  YYSYMBOL_LSQUARE = 33,                   /* LSQUARE  */
  YYSYMBOL_RSQUARE = 34,                   /* RSQUARE  */
  YYSYMBOL_COMMA = 35,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 36,                 /* SEMICOLON  */
  YYSYMBOL_CONST_INT = 37,                 /* CONST_INT  */
  YYSYMBOL_CONST_FLOAT = 38,               /* CONST_FLOAT  */
  YYSYMBOL_CONST_CHAR = 39,                /* CONST_CHAR  */
  YYSYMBOL_ID = 40,                        /* ID  */
  YYSYMBOL_MULTI_LINE_STRING = 41,         /* MULTI_LINE_STRING  */
  YYSYMBOL_SINGLE_LINE_STRING = 42,        /* SINGLE_LINE_STRING  */
  YYSYMBOL_LOWER_THAN_ELSE = 43,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 44,                  /* $accept  */
  YYSYMBOL_start = 45,                     /* start  */
  YYSYMBOL_program = 46,                   /* program  */
  YYSYMBOL_unit = 47,                      /* unit  */
  YYSYMBOL_func_declaration = 48,          /* func_declaration  */
  YYSYMBOL_func_definition = 49,           /* func_definition  */
  YYSYMBOL_50_1 = 50,                      /* $@1  */
  YYSYMBOL_51_2 = 51,                      /* $@2  */
  YYSYMBOL_parameter_list = 52,            /* parameter_list  */
  YYSYMBOL_compound_statement = 53,        /* compound_statement  */
  YYSYMBOL_54_3 = 54,                      /* $@3  */
  YYSYMBOL_55_4 = 55,                      /* $@4  */
  YYSYMBOL_var_declaration = 56,           /* var_declaration  */
  YYSYMBOL_type_specifier = 57,            /* type_specifier  */
  YYSYMBOL_declaration_list = 58,          /* declaration_list  */
  YYSYMBOL_statements = 59,                /* statements  */
  YYSYMBOL_statement = 60,                 /* statement  */
  YYSYMBOL_expression_statement = 61,      /* expression_statement  */
  YYSYMBOL_variable = 62,                  /* variable  */
  YYSYMBOL_expression = 63,                /* expression  */
  YYSYMBOL_logic_expression = 64,          /* logic_expression  */
  YYSYMBOL_rel_expression = 65,            /* rel_expression  */
  YYSYMBOL_simple_expression = 66,         /* simple_expression  */
  YYSYMBOL_term = 67,                      /* term  */
  YYSYMBOL_unary_expression = 68,          /* unary_expression  */
  YYSYMBOL_factor = 69,                    /* factor  */
  YYSYMBOL_argument_list = 70,             /* argument_list  */
  YYSYMBOL_arguments = 71                  /* arguments  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   147

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  122

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   298


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   326,   326,   338,   345,   354,   361,   369,   379,   397,
     414,   414,   428,   428,   443,   455,   466,   478,   492,   492,
     503,   503,   516,   533,   542,   551,   561,   573,   589,   600,
     617,   624,   634,   641,   648,   655,   668,   679,   692,   703,
     714,   725,   732,   742,   757,   789,   802,   826,   840,   857,
     872,   889,   902,   928,   941,   969,   982,   994,  1010,  1019,
    1037,  1046,  1059,  1068,  1076,  1087,  1095,  1102,  1114
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IF", "ELSE", "FOR",
  "WHILE", "DO", "BREAK", "INT", "CHAR", "FLOAT", "DOUBLE", "VOID",
  "RETURN", "SWITCH", "CASE", "DEFAULT", "CONTINUE", "PRINTLN", "ADDOP",
  "MULOP", "RELOP", "LOGICOP", "BITOP", "INCOP", "DECOP", "ASSIGNOP",
  "NOT", "LPAREN", "RPAREN", "LCURL", "RCURL", "LSQUARE", "RSQUARE",
  "COMMA", "SEMICOLON", "CONST_INT", "CONST_FLOAT", "CONST_CHAR", "ID",
  "MULTI_LINE_STRING", "SINGLE_LINE_STRING", "LOWER_THAN_ELSE", "$accept",
  "start", "program", "unit", "func_declaration", "func_definition", "$@1",
  "$@2", "parameter_list", "compound_statement", "$@3", "$@4",
  "var_declaration", "type_specifier", "declaration_list", "statements",
  "statement", "expression_statement", "variable", "expression",
  "logic_expression", "rel_expression", "simple_expression", "term",
  "unary_expression", "factor", "argument_list", "arguments", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-73)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-21)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      36,   -73,   -73,   -73,     4,    36,   -73,   -73,   -73,   -73,
     -29,   -73,   -73,    -8,    22,     3,    -9,    10,   -73,    19,
     -12,    20,    25,    28,   -73,    31,    33,    36,   -73,   -73,
      38,    41,   -73,   -73,    31,    23,    43,   101,    50,   -73,
     -73,   -73,    54,    57,    58,    71,    66,    71,    71,    71,
     -73,   -73,   -73,    -3,   -73,   -73,    73,    65,   -73,   -73,
       9,    62,   -73,    93,    26,    96,   -73,   -73,   -73,    71,
      52,    71,    82,    79,    27,   -73,   -73,    92,    71,    71,
      90,   -73,   -73,   -73,   -73,    71,   -73,    71,    71,    71,
      71,    94,    52,    95,   -73,    97,   -73,   -73,    98,    91,
      99,   -73,   -73,    96,   111,   -73,   101,    71,   101,   100,
     -73,    71,   -73,   130,   105,   -73,   -73,   -73,   101,   101,
     -73,   -73
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    23,    24,    25,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    28,     0,     0,     0,     0,    22,    12,
       0,    17,     0,    26,     9,     0,    10,     0,    16,    29,
       0,    18,    13,     8,     0,    15,     0,     0,     0,    11,
      14,    27,     0,     0,     0,     0,     0,     0,     0,     0,
      41,    61,    62,    43,    34,    32,     0,     0,    30,    33,
      58,     0,    45,    47,    49,    51,    53,    57,    21,     0,
       0,     0,     0,     0,    58,    55,    56,     0,    66,     0,
      28,    19,    31,    63,    64,     0,    42,     0,     0,     0,
       0,     0,     0,     0,    40,     0,    60,    68,     0,    65,
       0,    46,    48,    52,    50,    54,     0,     0,     0,     0,
      59,     0,    44,    36,     0,    38,    39,    67,     0,     0,
      37,    35
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -73,   -73,   -73,   135,   -73,   -73,   -73,   -73,   -73,   -15,
     -73,   -73,    15,    17,   -73,   -73,   -52,   -68,   -47,   -42,
     -72,    55,    56,    59,   -39,   -73,   -73,   -73
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,     7,     8,    34,    25,    20,    54,
      37,    38,    55,    56,    14,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    98,    99
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      74,    74,    92,    72,    11,    82,    97,    77,    75,    76,
      32,    13,     1,   101,     2,     9,     3,    10,    26,    39,
       9,    15,    10,    27,   107,    16,    78,    91,    22,    93,
      79,    74,    21,    19,    83,    84,    85,   100,    74,   117,
      74,    74,    74,    74,    35,     1,    88,     2,    89,     3,
      23,   105,    83,    84,   113,    24,   115,    17,    18,    29,
      28,    30,    31,    40,    74,   114,   120,   121,    42,    33,
      43,    44,    47,   -20,     1,    36,     2,    41,     3,    45,
      48,    49,    68,    69,    46,    47,    70,    71,    50,    51,
      52,    47,    53,    48,    49,    73,    31,    81,    86,    48,
      49,    50,    51,    52,    42,    53,    43,    44,    51,    52,
       1,    53,     2,    80,     3,    45,    87,    90,    94,    95,
      46,    47,    96,    16,   106,   108,   111,   109,   110,    48,
      49,    88,    31,   112,   118,   119,   116,    50,    51,    52,
      12,    53,   102,     0,     0,   104,     0,   103
};

static const yytype_int8 yycheck[] =
{
      47,    48,    70,    45,     0,    57,    78,    49,    47,    48,
      25,    40,     9,    85,    11,     0,    13,     0,    30,    34,
       5,    29,     5,    35,    92,    33,    29,    69,    37,    71,
      33,    78,    15,    30,    25,    26,    27,    79,    85,   111,
      87,    88,    89,    90,    27,     9,    20,    11,    22,    13,
      40,    90,    25,    26,   106,    36,   108,    35,    36,    34,
      40,    33,    31,    40,   111,   107,   118,   119,     3,    36,
       5,     6,    20,    32,     9,    37,    11,    34,    13,    14,
      28,    29,    32,    29,    19,    20,    29,    29,    36,    37,
      38,    20,    40,    28,    29,    29,    31,    32,    36,    28,
      29,    36,    37,    38,     3,    40,     5,     6,    37,    38,
       9,    40,    11,    40,    13,    14,    23,    21,    36,    40,
      19,    20,    30,    33,    30,    30,    35,    30,    30,    28,
      29,    20,    31,    34,     4,    30,    36,    36,    37,    38,
       5,    40,    87,    -1,    -1,    89,    -1,    88
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     9,    11,    13,    45,    46,    47,    48,    49,    56,
      57,     0,    47,    40,    58,    29,    33,    35,    36,    30,
      52,    57,    37,    40,    36,    51,    30,    35,    40,    34,
      33,    31,    53,    36,    50,    57,    37,    54,    55,    53,
      40,    34,     3,     5,     6,    14,    19,    20,    28,    29,
      36,    37,    38,    40,    53,    56,    57,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    32,    29,
      29,    29,    63,    29,    62,    68,    68,    63,    29,    33,
      40,    32,    60,    25,    26,    27,    36,    23,    20,    22,
      21,    63,    61,    63,    36,    40,    30,    64,    70,    71,
      63,    64,    65,    67,    66,    68,    30,    61,    30,    30,
      30,    35,    34,    60,    63,    60,    36,    64,     4,    30,
      60,    60
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    44,    45,    46,    46,    47,    47,    47,    48,    48,
      50,    49,    51,    49,    52,    52,    52,    52,    54,    53,
      55,    53,    56,    57,    57,    57,    58,    58,    58,    58,
      59,    59,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    61,    61,    62,    62,    63,    63,    64,    64,    65,
      65,    66,    66,    67,    67,    68,    68,    68,    69,    69,
      69,    69,    69,    69,    69,    70,    70,    71,    71
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       0,     7,     0,     6,     4,     3,     2,     1,     0,     4,
       0,     3,     3,     1,     1,     1,     3,     6,     1,     4,
       1,     2,     1,     1,     1,     7,     5,     7,     5,     5,
       3,     1,     2,     1,     4,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     2,     2,     1,     1,     4,
       3,     1,     1,     2,     2,     1,     0,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* start: program  */
#line 327 "parser.y"
        {     (yyval.symbolinfo)=new Symbolinfo("program","start");
          (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
		  (yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
		  (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
		  DFS((yyval.symbolinfo),"");

		//write your code in this block in all the similar blocks below
          logfile<<"start : program"<<endl;
	}
#line 1661 "y.tab.c"
    break;

  case 3: /* program: program unit  */
#line 338 "parser.y"
                       {  (yyval.symbolinfo)=new Symbolinfo("program unit","program");
                          (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
						  (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
						  (yyval.symbolinfo)->SetStartLine((yyvsp[-1].symbolinfo)->GetStartLine());
			              (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
	                     logfile<<"program : program unit"<<endl;
                       }
#line 1673 "y.tab.c"
    break;

  case 4: /* program: unit  */
#line 345 "parser.y"
                     {
			  (yyval.symbolinfo)=new Symbolinfo("unit","program");
              (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			  (yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			  (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
		      logfile<<"program : unit"<<endl;           
	        }
#line 1685 "y.tab.c"
    break;

  case 5: /* unit: var_declaration  */
#line 354 "parser.y"
                      { 
	                     (yyval.symbolinfo)=new Symbolinfo("var_declaration","unit");
						 (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
						 (yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			             (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
                        logfile<<"unit : var_declaration"<<endl;
					  }
#line 1697 "y.tab.c"
    break;

  case 6: /* unit: func_declaration  */
#line 362 "parser.y"
                          {
						 (yyval.symbolinfo)=new Symbolinfo("func_declaration","unit");
						 (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
						 (yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			             (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
                        logfile<<"unit : func_declaration"<<endl;
					  }
#line 1709 "y.tab.c"
    break;

  case 7: /* unit: func_definition  */
#line 370 "parser.y"
                           {
						(yyval.symbolinfo)=new Symbolinfo("func_definition","unit");
						(yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
						(yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			            (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
						logfile<<"unit : func_definition"<<endl;
					   }
#line 1721 "y.tab.c"
    break;

  case 8: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 379 "parser.y"
                                                                            {
	             cout<<"okay"<<endl;
				 Symbolinfo *info=new Symbolinfo((yyvsp[-4].symbolinfo)->getName(),(yyvsp[-4].symbolinfo)->getType());
	             declare_function((yyvsp[-5].symbolinfo)->getDataType(),info,function_parameter);
                logfile<<"func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON"<<endl; 
				 //delete $1;
				 //delete $2;
				  (yyval.symbolinfo)=new Symbolinfo("type_specifier ID LPAREN parameter_list RPAREN SEMICOLON","func_declaration");
					 (yyval.symbolinfo)->add_child((yyvsp[-5].symbolinfo));
                     (yyval.symbolinfo)->add_child((yyvsp[-4].symbolinfo));
			         (yyval.symbolinfo)->add_child((yyvsp[-3].symbolinfo));
					 (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
					 (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
					 (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
					 (yyval.symbolinfo)->SetStartLine((yyvsp[-5].symbolinfo)->GetStartLine());
			         (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
				 clear_list(function_parameter);
                     }
#line 1744 "y.tab.c"
    break;

  case 9: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 397 "parser.y"
                                                            {
			Symbolinfo *info=new Symbolinfo((yyvsp[-3].symbolinfo)->getName(),(yyvsp[-3].symbolinfo)->getType());
			declare_function((yyvsp[-4].symbolinfo)->getDataType(),info,new vector<Symbolinfo*>());
			 //delete $1;
			 //delete $2;
			 (yyval.symbolinfo)=new Symbolinfo("type_specifier ID LPAREN RPAREN SEMICOLON","func_declaration");
					 (yyval.symbolinfo)->add_child((yyvsp[-4].symbolinfo));
                     (yyval.symbolinfo)->add_child((yyvsp[-3].symbolinfo));
			         (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
					 (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
					 (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
					 (yyval.symbolinfo)->SetStartLine((yyvsp[-4].symbolinfo)->GetStartLine());
			         (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
			logfile<<"func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON"<<endl;
		}
#line 1764 "y.tab.c"
    break;

  case 10: /* $@1: %empty  */
#line 414 "parser.y"
                                                                 { Symbolinfo *info=new Symbolinfo((yyvsp[-3].symbolinfo)->getName(),(yyvsp[-3].symbolinfo)->getType()); define_function((yyvsp[-4].symbolinfo)->getDataType(),info,function_parameter);}
#line 1770 "y.tab.c"
    break;

  case 11: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN $@1 compound_statement  */
#line 414 "parser.y"
                                                                                                                                                                                                                {
                    //clear_list($4);
					//delete $1;
					(yyval.symbolinfo)=new Symbolinfo("type_specifier ID LPAREN parameter_list RPAREN compound_statement","func_definition");
					 (yyval.symbolinfo)->add_child((yyvsp[-6].symbolinfo));
                     (yyval.symbolinfo)->add_child((yyvsp[-5].symbolinfo));
			         (yyval.symbolinfo)->add_child((yyvsp[-4].symbolinfo));
					 (yyval.symbolinfo)->add_child((yyvsp[-3].symbolinfo));
					 (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
					 (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
					 (yyval.symbolinfo)->SetStartLine((yyvsp[-6].symbolinfo)->GetStartLine());
			         (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
                    logfile<<"func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement"<<endl;
                }
#line 1789 "y.tab.c"
    break;

  case 12: /* $@2: %empty  */
#line 428 "parser.y"
                                                          {Symbolinfo *info=new Symbolinfo((yyvsp[-2].symbolinfo)->getName(),(yyvsp[-2].symbolinfo)->getType());define_function((yyvsp[-3].symbolinfo)->getDataType(),info,new vector<Symbolinfo*>());}
#line 1795 "y.tab.c"
    break;

  case 13: /* func_definition: type_specifier ID LPAREN RPAREN $@2 compound_statement  */
#line 428 "parser.y"
                                                                                                                                                                                                              {
					//delete $1;
					(yyval.symbolinfo)=new Symbolinfo("type_specifier ID LPAREN RPAREN compound_statement","func_definition");
					 (yyval.symbolinfo)->add_child((yyvsp[-5].symbolinfo));
                     (yyval.symbolinfo)->add_child((yyvsp[-4].symbolinfo));
			         (yyval.symbolinfo)->add_child((yyvsp[-3].symbolinfo));
					 (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
					 (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
					 (yyval.symbolinfo)->SetStartLine((yyvsp[-5].symbolinfo)->GetStartLine());
			         (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
                    logfile<<"func_definition : type_specifier ID LPAREN RPAREN compound_statement"<<endl;
		}
#line 1812 "y.tab.c"
    break;

  case 14: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 443 "parser.y"
                                                        {
	              Symbolinfo *info=new Symbolinfo((yyvsp[0].symbolinfo)->getName(),(yyvsp[0].symbolinfo)->getType(),(yyvsp[-1].symbolinfo)->getDataType());
				  function_parameter->push_back(info);
                  logfile<<"parameter_list : parameter_list COMMA type_specifier ID"<<endl;
				  (yyval.symbolinfo)=new Symbolinfo("parameter_list COMMA type_specifier ID","parameter_list");
					 (yyval.symbolinfo)->add_child((yyvsp[-3].symbolinfo));
                     (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
			         (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
					 (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
					 (yyval.symbolinfo)->SetStartLine((yyvsp[-3].symbolinfo)->GetStartLine());
			         (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
            }
#line 1829 "y.tab.c"
    break;

  case 15: /* parameter_list: parameter_list COMMA type_specifier  */
#line 455 "parser.y"
                                                      {
			      Symbolinfo *info=new Symbolinfo("","",(yyvsp[0].symbolinfo)->getDataType());
			      function_parameter->push_back(info);
                  logfile<<"parameter_list : parameter_list COMMA type_specifier"<<endl;
				   (yyval.symbolinfo)=new Symbolinfo("parameter_list COMMA type_specifier","parameter_list");
					 (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
                     (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
			         (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
					 (yyval.symbolinfo)->SetStartLine((yyvsp[-2].symbolinfo)->GetStartLine());
			         (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
		   }
#line 1845 "y.tab.c"
    break;

  case 16: /* parameter_list: type_specifier ID  */
#line 466 "parser.y"
                                    {
			      
				  function_parameter=new vector<Symbolinfo*>();
			      Symbolinfo *info=new Symbolinfo((yyvsp[0].symbolinfo)->getName(),(yyvsp[0].symbolinfo)->getType(),(yyvsp[-1].symbolinfo)->getDataType());
			      function_parameter->push_back(info);
                  logfile<<"parameter_list : type_specifier ID"<<endl;
				  (yyval.symbolinfo)=new Symbolinfo("type_specifier ID","parameter_list");
					 (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
                     (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
					 (yyval.symbolinfo)->SetStartLine((yyvsp[-1].symbolinfo)->GetStartLine());
			         (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
		 }
#line 1862 "y.tab.c"
    break;

  case 17: /* parameter_list: type_specifier  */
#line 478 "parser.y"
                                 {
			 
			  function_parameter=new vector<Symbolinfo*>();
			  Symbolinfo *info=new Symbolinfo("","",(yyvsp[0].symbolinfo)->getDataType());
			  function_parameter->push_back(info);
              logfile<<"parameter_list : type_specifier"<<endl;
			  (yyval.symbolinfo)=new Symbolinfo("type_specifier","parameter_list");
					 (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
					 (yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			         (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
		  }
#line 1878 "y.tab.c"
    break;

  case 18: /* $@3: %empty  */
#line 492 "parser.y"
                          { table->Enter_Scope();add_parameter_toScopeTable(function_parameter); clear_list(function_parameter);}
#line 1884 "y.tab.c"
    break;

  case 19: /* compound_statement: LCURL $@3 statements RCURL  */
#line 492 "parser.y"
                                                                                                                                                   {
                        (yyval.symbolinfo)=new Symbolinfo("LCURL statements RCURL","compound_statement");
					    (yyval.symbolinfo)->add_child((yyvsp[-3].symbolinfo));
						(yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
						(yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
					    (yyval.symbolinfo)->SetStartLine((yyvsp[-3].symbolinfo)->GetStartLine());
			           (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
					   logfile<<"compound_statement : LCURL statements RCURL"<<endl;
					   table->printAll(logfile);
					   table->Exit_Scope();
                  }
#line 1900 "y.tab.c"
    break;

  case 20: /* $@4: %empty  */
#line 503 "parser.y"
                           { table->Enter_Scope();add_parameter_toScopeTable(function_parameter);clear_list(function_parameter);}
#line 1906 "y.tab.c"
    break;

  case 21: /* compound_statement: LCURL $@4 RCURL  */
#line 503 "parser.y"
                                                                                                                                        {
				        (yyval.symbolinfo)=new Symbolinfo("LCURL RCURL","compound_statement");
					    (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
						(yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
						
					    (yyval.symbolinfo)->SetStartLine((yyvsp[-2].symbolinfo)->GetStartLine());
			           (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
					  table->printAll(logfile);
				      table->Exit_Scope();
                      logfile<<"compound_statement : LCURL RCURL"<<endl;
			}
#line 1922 "y.tab.c"
    break;

  case 22: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 516 "parser.y"
                                                            {
	                 (yyval.symbolinfo)=new Symbolinfo("type_specifier declaration_list SEMICOLON","var_declaration");
					 (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
                     (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
			         (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
					 (yyval.symbolinfo)->SetStartLine((yyvsp[-2].symbolinfo)->GetStartLine());
			         (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
	                 cout<<"yo"<<endl;
	                  variable_declare((yyvsp[-2].symbolinfo)->getDataType(),variable_declaration);
					  cout<<"bleh"<<endl;
					  clear_list(variable_declaration);
					  //delete $1;
	                  logfile<<"var_declaration	: type_specifier declaration_list SEMICOLON"<<endl;

           }
#line 1942 "y.tab.c"
    break;

  case 23: /* type_specifier: INT  */
#line 533 "parser.y"
                      { 
	                 (yyval.symbolinfo)=new Symbolinfo("INT","type_specifier");
					 (yyval.symbolinfo)->setDataType("INT");
					 (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
					 (yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			         (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
	                 logfile<<"type_specifier : INT"<<endl;
                         
                    }
#line 1956 "y.tab.c"
    break;

  case 24: /* type_specifier: FLOAT  */
#line 542 "parser.y"
                         {  
			        (yyval.symbolinfo)=new Symbolinfo("FLOAT","type_specifier");
					(yyval.symbolinfo)->setDataType("FLOAT");
					(yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
					(yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			        (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
			        logfile<<"type_specifier : FLOAT"<<endl;

                         }
#line 1970 "y.tab.c"
    break;

  case 25: /* type_specifier: VOID  */
#line 551 "parser.y"
                          {
			        (yyval.symbolinfo)=new Symbolinfo("VOID","type_specifier");
					(yyval.symbolinfo)->setDataType("VOID");
					(yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
					(yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			        (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
			        logfile<<"type_specifier : VOID"<<endl;
                         }
#line 1983 "y.tab.c"
    break;

  case 26: /* declaration_list: declaration_list COMMA ID  */
#line 561 "parser.y"
                                             {
	               Symbolinfo *child=new Symbolinfo((yyvsp[0].symbolinfo)->getName(),(yyvsp[0].symbolinfo)->getType());
	               variable_declaration->push_back(child);
                   logfile<<"declaration_list : declaration_list COMMA ID"<<endl;
				   (yyval.symbolinfo)=new Symbolinfo("declaration_list COMMA ID","declaration_list");
				   (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
                   (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
			       (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
				   (yyval.symbolinfo)->SetStartLine((yyvsp[-2].symbolinfo)->GetStartLine());
			       (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
				   
          }
#line 2000 "y.tab.c"
    break;

  case 27: /* declaration_list: declaration_list COMMA ID LSQUARE CONST_INT RSQUARE  */
#line 573 "parser.y"
                                                                        {
			    Symbolinfo *child=new Symbolinfo((yyvsp[-3].symbolinfo)->getName(),(yyvsp[-3].symbolinfo)->getType());
			    child->setisArray(true);
			    child->setarraysize((yyvsp[-1].symbolinfo)->getName());
				variable_declaration->push_back(child);
               logfile<<"declaration_list : declaration_list COMMA ID LSQUARE CONST_INT RSQUARE"<<endl;
			   (yyval.symbolinfo)=new Symbolinfo("declaration_list COMMA ID LSQUARE CONST_INT RSQUARE","declaration_list");
			  (yyval.symbolinfo)->add_child((yyvsp[-5].symbolinfo));
              (yyval.symbolinfo)->add_child((yyvsp[-4].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[-3].symbolinfo));
              (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
              (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			  (yyval.symbolinfo)->SetStartLine((yyvsp[-5].symbolinfo)->GetStartLine());
			(yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
          }
#line 2021 "y.tab.c"
    break;

  case 28: /* declaration_list: ID  */
#line 589 "parser.y"
                       { 
			    variable_declaration=new vector<Symbolinfo*>();
				Symbolinfo *child=new Symbolinfo((yyvsp[0].symbolinfo)->getName(),(yyvsp[0].symbolinfo)->getType());
				variable_declaration->push_back(child);
               logfile<<"declaration_list : ID	"<<endl;
			   (yyval.symbolinfo)=new Symbolinfo("ID","declaration_list");
			   (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			   cout<<"isleaf:"<<(yyvsp[0].symbolinfo)->getisLeaf()<<endl;
			   (yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			   (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
          }
#line 2037 "y.tab.c"
    break;

  case 29: /* declaration_list: ID LSQUARE CONST_INT RSQUARE  */
#line 600 "parser.y"
                                                 {
			Symbolinfo *child=new Symbolinfo((yyvsp[-3].symbolinfo)->getName(),(yyvsp[-3].symbolinfo)->getType());
			child->setisArray(true);
			child->setarraysize((yyvsp[-1].symbolinfo)->getName());
            variable_declaration=new vector<Symbolinfo*>();
			variable_declaration->push_back(child);
            logfile<<"declaration_list : ID LSQUARE CONST_INT RSQUARE"<<endl;
			(yyval.symbolinfo)=new Symbolinfo("ID LSQUARE CONST_INT RSQUARE","declaration_list");
			(yyval.symbolinfo)->add_child((yyvsp[-3].symbolinfo));
            (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
			(yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
            (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			(yyval.symbolinfo)->SetStartLine((yyvsp[-3].symbolinfo)->GetStartLine());
			(yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
          }
#line 2057 "y.tab.c"
    break;

  case 30: /* statements: statement  */
#line 617 "parser.y"
                       {
	               (yyval.symbolinfo)=new Symbolinfo("statement","statements");
			       (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			       (yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			       (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
                   logfile<<"statements	: statement"<<endl;
        }
#line 2069 "y.tab.c"
    break;

  case 31: /* statements: statements statement  */
#line 624 "parser.y"
                                  {
		      (yyval.symbolinfo)=new Symbolinfo("statements statement","statements");
			(yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
            (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			(yyval.symbolinfo)->SetStartLine((yyvsp[-1].symbolinfo)->GetStartLine());
			(yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
              logfile<<"statements : statements statement"<<endl;
	   }
#line 2082 "y.tab.c"
    break;

  case 32: /* statement: var_declaration  */
#line 634 "parser.y"
                            {
	           		      (yyval.symbolinfo)=new Symbolinfo("var_declaration","statement");
			              (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			              (yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			              (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
                          logfile<<"statement : var_declaration"<<endl;
        }
#line 2094 "y.tab.c"
    break;

  case 33: /* statement: expression_statement  */
#line 641 "parser.y"
                                 {
		                  (yyval.symbolinfo)=new Symbolinfo("expression_statement","statement");
			              (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			              (yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			              (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
             logfile<<"statement : expression_statement"<<endl;
	  }
#line 2106 "y.tab.c"
    break;

  case 34: /* statement: compound_statement  */
#line 648 "parser.y"
                               {
		      (yyval.symbolinfo)=new Symbolinfo("compound_statement","statement");
			              (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			              (yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			              (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
             logfile<<"statement : compound_statement"<<endl;
	  }
#line 2118 "y.tab.c"
    break;

  case 35: /* statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement  */
#line 655 "parser.y"
                                                                                             {
		      (yyval.symbolinfo)=new Symbolinfo("FOR LPAREN expression_statement expression_statement expression RPAREN statement","statement");
			  (yyval.symbolinfo)->add_child((yyvsp[-6].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[-5].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[-4].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[-3].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			  (yyval.symbolinfo)->SetStartLine((yyvsp[-6].symbolinfo)->GetStartLine());
			  (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
             logfile<<"statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement"<<endl;
	  }
#line 2136 "y.tab.c"
    break;

  case 36: /* statement: IF LPAREN expression RPAREN statement  */
#line 668 "parser.y"
                                                                       {
		      (yyval.symbolinfo)=new Symbolinfo("IF LPAREN expression RPAREN statement","statement");
			  (yyval.symbolinfo)->add_child((yyvsp[-4].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[-3].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			  (yyval.symbolinfo)->SetStartLine((yyvsp[-4].symbolinfo)->GetStartLine());
			  (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
             logfile<<"statement : IF LPAREN expression RPAREN statement"<<endl;
	  }
#line 2152 "y.tab.c"
    break;

  case 37: /* statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 679 "parser.y"
                                                                 {
		      (yyval.symbolinfo)=new Symbolinfo("IF LPAREN expression RPAREN statement ELSE statement","statement");
			  (yyval.symbolinfo)->add_child((yyvsp[-6].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[-5].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[-4].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[-3].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			  (yyval.symbolinfo)->SetStartLine((yyvsp[-6].symbolinfo)->GetStartLine());
			  (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
             logfile<<"statement : IF LPAREN expression RPAREN statement ELSE statement"<<endl;
	  }
#line 2170 "y.tab.c"
    break;

  case 38: /* statement: WHILE LPAREN expression RPAREN statement  */
#line 692 "parser.y"
                                                     {
		     (yyval.symbolinfo)=new Symbolinfo("WHILE LPAREN expression RPAREN statement","statement");
			  (yyval.symbolinfo)->add_child((yyvsp[-4].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[-3].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			  (yyval.symbolinfo)->SetStartLine((yyvsp[-4].symbolinfo)->GetStartLine());
			  (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
             logfile<<"statement : WHILE LPAREN expression RPAREN statement"<<endl;
	  }
#line 2186 "y.tab.c"
    break;

  case 39: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 703 "parser.y"
                                               {
		      (yyval.symbolinfo)=new Symbolinfo("PRINTLN LPAREN ID RPAREN SEMICOLON","statement");
			  (yyval.symbolinfo)->add_child((yyvsp[-4].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[-3].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			  (yyval.symbolinfo)->SetStartLine((yyvsp[-4].symbolinfo)->GetStartLine());
			  (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
             logfile<<"statement : PRINTLN LPAREN ID RPAREN SEMICOLON"<<endl;
	  }
#line 2202 "y.tab.c"
    break;

  case 40: /* statement: RETURN expression SEMICOLON  */
#line 714 "parser.y"
                                        {
		      (yyval.symbolinfo)=new Symbolinfo("RETURN expression SEMICOLON","statement");
			  (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			  (yyval.symbolinfo)->SetStartLine((yyvsp[-2].symbolinfo)->GetStartLine());
			  (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
             logfile<<"statement : RETURN expression SEMICOLON"<<endl;
	  }
#line 2216 "y.tab.c"
    break;

  case 41: /* expression_statement: SEMICOLON  */
#line 725 "parser.y"
                                {
	           (yyval.symbolinfo)=new Symbolinfo("SEMICOLON","expression_statement");
			  (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			  (yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			  (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
              logfile<<"expression_statement : SEMICOLON"<<endl;
            }
#line 2228 "y.tab.c"
    break;

  case 42: /* expression_statement: expression SEMICOLON  */
#line 732 "parser.y"
                                               {
				(yyval.symbolinfo)=new Symbolinfo("expression SEMICOLON","expression_statement",(yyvsp[-1].symbolinfo)->getDataType());
			  (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			  (yyval.symbolinfo)->SetStartLine((yyvsp[-1].symbolinfo)->GetStartLine());
			  (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
              logfile<<"expression_statement : expression SEMICOLON"<<endl;
			}
#line 2241 "y.tab.c"
    break;

  case 43: /* variable: ID  */
#line 742 "parser.y"
              {
	          
			  Symbolinfo *info=table->LookUp((yyvsp[0].symbolinfo)->getName());
			  
			  if(info==NULL)
			  {
                errorfile<<"Line# "<<line_count<<": Undeclared variable '"<<(yyvsp[0].symbolinfo)->getName()<<"'"<<endl;
				 (yyval.symbolinfo)=new Symbolinfo("ID","variable","");
			  }else 
			    (yyval.symbolinfo)=new Symbolinfo("ID","variable",info->getDataType());
			  (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			  (yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			  (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
              logfile<<"variable : ID"<<endl;
            }
#line 2261 "y.tab.c"
    break;

  case 44: /* variable: ID LSQUARE expression RSQUARE  */
#line 757 "parser.y"
                                         {
		   
		      Symbolinfo *info=table->LookUp((yyvsp[-3].symbolinfo)->getName());
			  if(info==NULL)
			  {
                errorfile<<"Line# "<<line_count<<": Undeclared variable '"<<(yyvsp[-3].symbolinfo)->getName()<<"'"<<endl;
                (yyval.symbolinfo)=new Symbolinfo("ID LSQUARE expression RSQUARE","variable","");
			  }
			  else
			  {
				(yyval.symbolinfo)=new Symbolinfo("ID LSQUARE expression RSQUARE","variable",info->getDataType());
				if(!info->getisArray())
				{
					errorfile<<"Line# "<<line_count<<": '"<<(yyvsp[-3].symbolinfo)->getName()<<"' is not an array"<<endl;
				}
				 if((yyvsp[-1].symbolinfo)->getDataType()!="INT")
			   {
				errorfile<<"Line# "<<line_count<<": Array subscript is not an integer"<<endl;
			   }
			  }
			    
			  (yyval.symbolinfo)->add_child((yyvsp[-3].symbolinfo));
			   (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
			    (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
				 (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			  (yyval.symbolinfo)->SetStartLine((yyvsp[-3].symbolinfo)->GetStartLine());
			  (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
		   
            logfile<<"variable	: ID LSQUARE expression RSQUARE"<<endl;
	 }
#line 2296 "y.tab.c"
    break;

  case 45: /* expression: logic_expression  */
#line 789 "parser.y"
                              {
	                 (yyval.symbolinfo)=new Symbolinfo("logic_expression","expression",(yyvsp[0].symbolinfo)->getDataType());
					 (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			  
			  (yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			  (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
	                 if((yyvsp[0].symbolinfo)->getiszero())
						 {
							(yyval.symbolinfo)->setisZero(true);
						 }
	         
             logfile<<"expression : logic_expression"<<endl;
        }
#line 2314 "y.tab.c"
    break;

  case 46: /* expression: variable ASSIGNOP logic_expression  */
#line 802 "parser.y"
                                                {
		       (yyval.symbolinfo)=new Symbolinfo("variable ASSIGNOP logic_expression","expression",(yyvsp[-2].symbolinfo)->getDataType());
					 (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			 
			  (yyval.symbolinfo)->SetStartLine((yyvsp[-2].symbolinfo)->GetStartLine());
			  (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
		      if((yyvsp[0].symbolinfo)->getiszero())
						 {
							(yyval.symbolinfo)->setisZero(true);
						 }
		      if(((yyvsp[-2].symbolinfo)->getDataType()=="INT" && (yyvsp[0].symbolinfo)->getDataType()=="FLOAT")){
		      errorfile<<"Line# "<<line_count<<": Warning: possible loss of data in assignment of "<<(yyvsp[0].symbolinfo)->getDataType()<<" to "<<(yyvsp[-2].symbolinfo)->getDataType()<<endl;
			  }
		    if((yyvsp[0].symbolinfo)->getDataType()=="VOID")
			  {
				errorfile<<"Line# "<<line_count<<": Void cannot be used in expression "<<endl;
			  }
			  
              logfile<<"expression : variable ASSIGNOP logic_expression"<<endl;
	   }
#line 2341 "y.tab.c"
    break;

  case 47: /* logic_expression: rel_expression  */
#line 826 "parser.y"
                                  {
	                    (yyval.symbolinfo)=new Symbolinfo("rel_expression","logic_expression",(yyvsp[0].symbolinfo)->getDataType());
					    (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			            (yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			            (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
	                    
	                     if((yyvsp[0].symbolinfo)->getiszero())
						 {
							(yyval.symbolinfo)->setisZero(true);
						 }
	              				cout<<"checking:"<<(yyvsp[0].symbolinfo)->getDataType()<<endl;
	              
                  logfile<<"logic_expression : rel_expression"<<endl;
        }
#line 2360 "y.tab.c"
    break;

  case 48: /* logic_expression: rel_expression LOGICOP rel_expression  */
#line 840 "parser.y"
                                                         {
			        (yyval.symbolinfo)=new Symbolinfo("rel_expression LOGICOP rel_expression","logic_expression",(yyvsp[-2].symbolinfo)->getDataType());
					 (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			 
			  (yyval.symbolinfo)->SetStartLine((yyvsp[-2].symbolinfo)->GetStartLine());
			  (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
			     if((yyvsp[0].symbolinfo)->getDataType()=="VOID"||(yyvsp[-2].symbolinfo)->getDataType()=="VOID")
			  {
				errorfile<<"Line# "<<line_count<<": Void cannot be used in expression"<<endl;
			  }
                 logfile<<"logic_expression	: rel_expression LOGICOP rel_expression "<<endl;
				
		 }
#line 2380 "y.tab.c"
    break;

  case 49: /* rel_expression: simple_expression  */
#line 857 "parser.y"
                                    {
	                             (yyval.symbolinfo)=new Symbolinfo("simple_expression","rel_expression",(yyvsp[0].symbolinfo)->getDataType());
					             (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			  
			                      (yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			                      (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
	                         
	                            if((yyvsp[0].symbolinfo)->getiszero())
						 {
							(yyval.symbolinfo)->setisZero(true);
						 }
	              				cout<<"checking:"<<(yyvsp[0].symbolinfo)->getDataType()<<endl;
	             
                  logfile<<"rel_expression : simple_expression"<<endl;
        }
#line 2400 "y.tab.c"
    break;

  case 50: /* rel_expression: simple_expression RELOP simple_expression  */
#line 872 "parser.y"
                                                                {
			    (yyval.symbolinfo)=new Symbolinfo("simple_expression RELOP simple_expression","rel_expression",(yyvsp[-2].symbolinfo)->getDataType());
					 (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
			  (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			 
			  (yyval.symbolinfo)->SetStartLine((yyvsp[-2].symbolinfo)->GetStartLine());
			  (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
			
            logfile<<"rel_expression : simple_expression RELOP simple_expression"<<endl;
			   if((yyvsp[0].symbolinfo)->getDataType()=="VOID"||(yyvsp[-2].symbolinfo)->getDataType()=="VOID")
			  {
				errorfile<<"Line# "<<line_count<<": Void cannot be used in expression "<<endl;
			  }
		}
#line 2420 "y.tab.c"
    break;

  case 51: /* simple_expression: term  */
#line 889 "parser.y"
                         {
	                  (yyval.symbolinfo)=new Symbolinfo("term","simple_expression",(yyvsp[0].symbolinfo)->getDataType());
					 (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			         (yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			          (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
	                  cout<<"checking:"<<(yyvsp[0].symbolinfo)->getDataType()<<endl;
	                  
						 if((yyvsp[0].symbolinfo)->getiszero())
						 {
							(yyval.symbolinfo)->setisZero(true);
						 }
                     logfile<<"simple_expression : term"<<endl;
        }
#line 2438 "y.tab.c"
    break;

  case 52: /* simple_expression: simple_expression ADDOP term  */
#line 902 "parser.y"
                                                 {
			            (yyval.symbolinfo)=new Symbolinfo("simple_expression ADDOP term","simple_expression",(yyvsp[-2].symbolinfo)->getDataType());
					    (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
						(yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
						(yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));

						(yyval.symbolinfo)->SetStartLine((yyvsp[-2].symbolinfo)->GetStartLine());
						(yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
			
			          
						 if ((yyvsp[-2].symbolinfo)->getName()==(yyvsp[0].symbolinfo)->getName() && (yyvsp[-1].symbolinfo)->getName()=="-")
						 {
							(yyval.symbolinfo)->setisZero(true);
						 }
						 if((yyvsp[0].symbolinfo)->getiszero() && (yyvsp[-2].symbolinfo)->getiszero())
						 {
							(yyval.symbolinfo)->setisZero(true);
						 }
						    if((yyvsp[0].symbolinfo)->getDataType()=="VOID"||(yyvsp[-2].symbolinfo)->getDataType()=="VOID")
			             {
				      errorfile<<"Line# "<<line_count<<": Void cannot be used in expression "<<endl;
			             }
                    logfile<<"simple_expression : simple_expression ADDOP term"<<endl;
		  }
#line 2467 "y.tab.c"
    break;

  case 53: /* term: unary_expression  */
#line 928 "parser.y"
                         {
	                     cout<<"checking:"<<(yyvsp[0].symbolinfo)->getDataType()<<endl;
	                        (yyval.symbolinfo)=new Symbolinfo("unary_expression","term",(yyvsp[0].symbolinfo)->getDataType());
					 (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			  
			  (yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			  (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
						 if((yyvsp[0].symbolinfo)->getiszero())
						 {
							(yyval.symbolinfo)->setisZero(true);
						 }
                         logfile<<"term : unary_expression"<<endl;
        }
#line 2485 "y.tab.c"
    break;

  case 54: /* term: term MULOP unary_expression  */
#line 941 "parser.y"
                                    {
		                 cout<<"unary_expression:"<<(yyvsp[0].symbolinfo)->getiszero()<<endl;
		                    (yyval.symbolinfo)=new Symbolinfo("term MULOP unary_expression","term",(yyvsp[-2].symbolinfo)->getDataType());
					 (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
			         (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
			          (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			  
			  (yyval.symbolinfo)->SetStartLine((yyvsp[-2].symbolinfo)->GetStartLine());
			  (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
						 if(((yyvsp[-1].symbolinfo)->getName()=="%" || (yyvsp[-1].symbolinfo)->getName()=="/")&&((yyvsp[0].symbolinfo)->getiszero()))
						 {
							errorfile<<"Line# "<<line_count<<": Warning: division by zero i=0f=1Const=0"<<endl;
						 }
						 if((yyvsp[-1].symbolinfo)->getName()=="%" && ((yyvsp[0].symbolinfo)->getDataType()!="INT")){
							errorfile<<"Line# "<<line_count<<": Operands of modulus must be integers "<<endl;
						 }
						 if(((yyvsp[-1].symbolinfo)->getName()=="*")&&((yyvsp[0].symbolinfo)->getiszero()||(yyvsp[-2].symbolinfo)->getiszero()))
						 {
							(yyval.symbolinfo)->setisZero(true);
						 }
						    if((yyvsp[0].symbolinfo)->getDataType()=="VOID"||(yyvsp[-2].symbolinfo)->getDataType()=="VOID")
			  {
				errorfile<<"Line# "<<line_count<<": Void cannot be used in expression "<<endl;
			  }
                         logfile<<"term : term MULOP unary_expression"<<endl;
	 }
#line 2516 "y.tab.c"
    break;

  case 55: /* unary_expression: ADDOP unary_expression  */
#line 969 "parser.y"
                                          {
	                    
	                     (yyval.symbolinfo)=new Symbolinfo("ADDOP unary_expression","unary_expression",(yyvsp[0].symbolinfo)->getDataType());
					     (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
			             (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			             (yyval.symbolinfo)->SetStartLine((yyvsp[-1].symbolinfo)->GetStartLine());
			             (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
                        logfile<<"unary_expression : ADDOP unary_expression"<<endl;
						   if((yyvsp[0].symbolinfo)->getDataType()=="VOID")
			              {
				             errorfile<<"Line# "<<line_count<<": Void cannot be used in expression"<<endl;
			              }
         }
#line 2534 "y.tab.c"
    break;

  case 56: /* unary_expression: NOT unary_expression  */
#line 982 "parser.y"
                                        {
			             (yyval.symbolinfo)=new Symbolinfo("NOT unary_expression","unary_expression",(yyvsp[0].symbolinfo)->getDataType());
					     (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
			             (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			             (yyval.symbolinfo)->SetStartLine((yyvsp[-1].symbolinfo)->GetStartLine());
			             (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
                        logfile<<"unary_expression : NOT unary_expression"<<endl;
						   if((yyvsp[0].symbolinfo)->getDataType()=="VOID")
			  {
				errorfile<<"Line# "<<line_count<<": Void cannot be used in expression "<<endl;
			  }
		 }
#line 2551 "y.tab.c"
    break;

  case 57: /* unary_expression: factor  */
#line 994 "parser.y"
                          {   
			          cout<<"FACTOR:"<<(yyvsp[0].symbolinfo)->getiszero()<<endl;
					  (yyval.symbolinfo)=new Symbolinfo("factor","unary_expression",(yyvsp[0].symbolinfo)->getDataType());
					     (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			             (yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			             (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
			          if((yyvsp[0].symbolinfo)->getiszero())
						 {
							(yyval.symbolinfo)->setisZero(true);
						 }
			          cout<<"checking:"<<(yyvsp[0].symbolinfo)->getDataType()<<endl;
			          
                      logfile<<"unary_expression : factor"<<endl;
		 }
#line 2570 "y.tab.c"
    break;

  case 58: /* factor: variable  */
#line 1010 "parser.y"
                   {  
	                    
					  (yyval.symbolinfo)=new Symbolinfo("variable","factor",(yyvsp[0].symbolinfo)->getDataType());
					     (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			             (yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			             (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
					  cout<<"checking:"<<(yyvsp[0].symbolinfo)->getDataType()<<endl;
                      logfile<<"factor : variable"<<endl;
        }
#line 2584 "y.tab.c"
    break;

  case 59: /* factor: ID LPAREN argument_list RPAREN  */
#line 1019 "parser.y"
                                         {//function call
	                
					 cout<<endl;
	                  Symbolinfo *info=CallFunction((yyvsp[-3].symbolinfo),ArgumentList);
					  if(info==NULL)
					   (yyval.symbolinfo)=new Symbolinfo("ID LPAREN argument_list RPAREN","factor","");
					   else
					    (yyval.symbolinfo)=new Symbolinfo("ID LPAREN argument_list RPAREN","factor",info->getDataType());
					     (yyval.symbolinfo)->add_child((yyvsp[-3].symbolinfo));
						 (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
						 (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
						 (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			             (yyval.symbolinfo)->SetStartLine((yyvsp[-3].symbolinfo)->GetStartLine());
			             (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
					  clear_list(ArgumentList);
					  //delete $1;
                      logfile<<"factor : ID LPAREN argument_list RPAREN"<<endl;
	}
#line 2607 "y.tab.c"
    break;

  case 60: /* factor: LPAREN expression RPAREN  */
#line 1037 "parser.y"
                                   {
		             (yyval.symbolinfo)=new Symbolinfo("LPAREN expression RPAREN","factor",(yyvsp[-1].symbolinfo)->getDataType());
					     (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
						 (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
						 (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			             (yyval.symbolinfo)->SetStartLine((yyvsp[-2].symbolinfo)->GetStartLine());
			             (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
                     logfile<<"factor : LPAREN expression RPAREN"<<endl;
	}
#line 2621 "y.tab.c"
    break;

  case 61: /* factor: CONST_INT  */
#line 1046 "parser.y"
                    {
                (yyvsp[0].symbolinfo)->setDataType("INT");
		        (yyval.symbolinfo)=new Symbolinfo("CONST_INT","factor",(yyvsp[0].symbolinfo)->getDataType());
					     (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			             (yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			             (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
		        
				if((yyvsp[0].symbolinfo)->getName()=="0")
				{
					(yyval.symbolinfo)->setisZero(true);
				}
                logfile<<"factor : CONST_INT"<<endl;
	}
#line 2639 "y.tab.c"
    break;

  case 62: /* factor: CONST_FLOAT  */
#line 1059 "parser.y"
                      {
		         (yyvsp[0].symbolinfo)->setDataType("FLOAT");
		       (yyval.symbolinfo)=new Symbolinfo("CONST_FLOAT","factor",(yyvsp[0].symbolinfo)->getDataType());
					     (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			             (yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			             (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
		      
               logfile<<"factor : CONST_FLOAT"<<endl;
	}
#line 2653 "y.tab.c"
    break;

  case 63: /* factor: variable INCOP  */
#line 1068 "parser.y"
                         {
		       (yyval.symbolinfo)=new Symbolinfo("variable INCOP","factor",(yyvsp[-1].symbolinfo)->getDataType());
					     (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
						 (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			             (yyval.symbolinfo)->SetStartLine((yyvsp[-1].symbolinfo)->GetStartLine());
			             (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
             logfile<<"factor : variable INCOP"<<endl;
	}
#line 2666 "y.tab.c"
    break;

  case 64: /* factor: variable DECOP  */
#line 1076 "parser.y"
                         {
		     (yyval.symbolinfo)=new Symbolinfo("variable DECOP","factor",(yyvsp[-1].symbolinfo)->getDataType());
					     (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
						 (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			             (yyval.symbolinfo)->SetStartLine((yyvsp[-1].symbolinfo)->GetStartLine());
			             (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
		  
            logfile<<"factor : variable DECOP"<<endl;
	}
#line 2680 "y.tab.c"
    break;

  case 65: /* argument_list: arguments  */
#line 1087 "parser.y"
                          {
	                  (yyval.symbolinfo)=new Symbolinfo("arguments","argument_list",(yyvsp[0].symbolinfo)->getDataType());
					     (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
			             (yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			             (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
	               ArgumentList=Argument;
                   logfile<<"argument_list	: arguments"<<endl;
              }
#line 2693 "y.tab.c"
    break;

  case 66: /* argument_list: %empty  */
#line 1095 "parser.y"
                            { 
				      (yyval.symbolinfo)=new Symbolinfo("","argument_list","");
				   ArgumentList=new vector<Symbolinfo*>();
                   logfile<<"argument_list	: "<<endl;
			  }
#line 2703 "y.tab.c"
    break;

  case 67: /* arguments: arguments COMMA logic_expression  */
#line 1102 "parser.y"
                                             {
	                 (yyval.symbolinfo)=new Symbolinfo("arguments COMMA logic_expression","arguments",(yyvsp[-2].symbolinfo)->getDataType());
					     (yyval.symbolinfo)->add_child((yyvsp[-2].symbolinfo));
						 (yyval.symbolinfo)->add_child((yyvsp[-1].symbolinfo));
						 (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
						
			             (yyval.symbolinfo)->SetStartLine((yyvsp[-2].symbolinfo)->GetStartLine());
			             (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
				  Symbolinfo *info=new Symbolinfo((yyvsp[0].symbolinfo)->getName(),(yyvsp[0].symbolinfo)->getType(),(yyvsp[0].symbolinfo)->getDataType());
	              Argument->push_back(info);
                  logfile<<"arguments	: arguments COMMA logic_expression"<<endl;
           }
#line 2720 "y.tab.c"
    break;

  case 68: /* arguments: logic_expression  */
#line 1114 "parser.y"
                                 {
			       (yyval.symbolinfo)=new Symbolinfo("logic_expression","arguments",(yyvsp[0].symbolinfo)->getDataType());
					     (yyval.symbolinfo)->add_child((yyvsp[0].symbolinfo));
					
			             (yyval.symbolinfo)->SetStartLine((yyvsp[0].symbolinfo)->GetStartLine());
			             (yyval.symbolinfo)->SetEndLine((yyvsp[0].symbolinfo)->GetEndLine());
			    cout<<"checking2:"<<(yyvsp[0].symbolinfo)->getDataType()<<endl;
			    Argument=new vector<Symbolinfo*>();
				 Symbolinfo *info=new Symbolinfo((yyvsp[0].symbolinfo)->getName(),(yyvsp[0].symbolinfo)->getType(),(yyvsp[0].symbolinfo)->getDataType());
	              Argument->push_back(info);
				
                logfile<<"arguments	: logic_expression"<<endl;
			
		  }
#line 2739 "y.tab.c"
    break;


#line 2743 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1130 "parser.y"

int main(int argc,char *argv[])
{
    FILE *fp;
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}

	// fp2= fopen(argv[2],"w");
	// fclose(fp2);
	// fp3= fopen(argv[3],"w");
	// fclose(fp3);
	
	// fp2= fopen(argv[2],"a");
	// fp3= fopen(argv[3],"a");
    logfile.open("1905062_log.txt", ios::out);
	errorfile.open("1605062_error.txt", ios::out);
	parsefile.open("1605062_parse.txt",ios::out);
    logout=fopen("1905062_log.txt","a");
	table=new SymbolTable(11);
    yylineno=1;
	yyin=fp;
	
	yyparse();
	

	// fclose(fp2);
	// fclose(fp3);
	
	return 0;
}
