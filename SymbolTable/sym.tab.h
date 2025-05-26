/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SYM_TAB_H_INCLUDED
# define YY_YY_SYM_TAB_H_INCLUDED
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
    HASH = 258,                    /* HASH  */
    INCLUDE = 259,                 /* INCLUDE  */
    STDIO = 260,                   /* STDIO  */
    STDLIB = 261,                  /* STDLIB  */
    MATH = 262,                    /* MATH  */
    STRING = 263,                  /* STRING  */
    TIME = 264,                    /* TIME  */
    STRING_LITERAL = 265,          /* STRING_LITERAL  */
    HEADER_LITERAL = 266,          /* HEADER_LITERAL  */
    PRINT = 267,                   /* PRINT  */
    RETURN = 268,                  /* RETURN  */
    INTEGER_LITERAL = 269,         /* INTEGER_LITERAL  */
    CHARACTER_LITERAL = 270,       /* CHARACTER_LITERAL  */
    FLOAT_LITERAL = 271,           /* FLOAT_LITERAL  */
    IDENTIFIER = 272,              /* IDENTIFIER  */
    INC_OP = 273,                  /* INC_OP  */
    DEC_OP = 274,                  /* DEC_OP  */
    LE_OP = 275,                   /* LE_OP  */
    GE_OP = 276,                   /* GE_OP  */
    EQ_OP = 277,                   /* EQ_OP  */
    NE_OP = 278,                   /* NE_OP  */
    MUL_ASSIGN = 279,              /* MUL_ASSIGN  */
    DIV_ASSIGN = 280,              /* DIV_ASSIGN  */
    MOD_ASSIGN = 281,              /* MOD_ASSIGN  */
    ADD_ASSIGN = 282,              /* ADD_ASSIGN  */
    SUB_ASSIGN = 283,              /* SUB_ASSIGN  */
    CHAR = 284,                    /* CHAR  */
    INT = 285,                     /* INT  */
    FLOAT = 286,                   /* FLOAT  */
    VOID = 287,                    /* VOID  */
    FOR = 288                      /* FOR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 64 "sym.y"

	int ival;
	float fval;
	char cval;
	struct node *ptr;

#line 104 "sym.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SYM_TAB_H_INCLUDED  */
