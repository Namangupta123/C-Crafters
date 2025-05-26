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
    T_keyword = 258,               /* T_keyword  */
    T_int = 259,                   /* T_int  */
    T_main = 260,                  /* T_main  */
    T_type = 261,                  /* T_type  */
    T_return = 262,                /* T_return  */
    T_for = 263,                   /* T_for  */
    T_if = 264,                    /* T_if  */
    T_else = 265,                  /* T_else  */
    T_while = 266,                 /* T_while  */
    T_InputStream = 267,           /* T_InputStream  */
    T_OutputStream = 268,          /* T_OutputStream  */
    T_char = 269,                  /* T_char  */
    T_double = 270,                /* T_double  */
    T_float = 271,                 /* T_float  */
    T_openParenthesis = 272,       /* T_openParenthesis  */
    T_closedParanthesis = 273,     /* T_closedParanthesis  */
    T_openFlowerBracket = 274,     /* T_openFlowerBracket  */
    T_closedFlowerBracket = 275,   /* T_closedFlowerBracket  */
    T_RelationalOperator = 276,    /* T_RelationalOperator  */
    T_LogicalOperator = 277,       /* T_LogicalOperator  */
    T_UnaryOperator = 278,         /* T_UnaryOperator  */
    T_AssignmentOperator = 279,    /* T_AssignmentOperator  */
    T_Semicolon = 280,             /* T_Semicolon  */
    T_identifier = 281,            /* T_identifier  */
    T_numericConstants = 282,      /* T_numericConstants  */
    T_stringLiteral = 283,         /* T_stringLiteral  */
    T_character = 284,             /* T_character  */
    T_plus = 285,                  /* T_plus  */
    T_minus = 286,                 /* T_minus  */
    T_mod = 287,                   /* T_mod  */
    T_divide = 288,                /* T_divide  */
    T_multiply = 289,              /* T_multiply  */
    T_whiteSpace = 290,            /* T_whiteSpace  */
    T_shortHand = 291,             /* T_shortHand  */
    T_LogicalAnd = 292,            /* T_LogicalAnd  */
    T_LogicalOr = 293,             /* T_LogicalOr  */
    T_less = 294,                  /* T_less  */
    T_less_equal = 295,            /* T_less_equal  */
    T_greater = 296,               /* T_greater  */
    T_greater_equal = 297,         /* T_greater_equal  */
    T_equal_equal = 298,           /* T_equal_equal  */
    T_not_equal = 299              /* T_not_equal  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define T_keyword 258
#define T_int 259
#define T_main 260
#define T_type 261
#define T_return 262
#define T_for 263
#define T_if 264
#define T_else 265
#define T_while 266
#define T_InputStream 267
#define T_OutputStream 268
#define T_char 269
#define T_double 270
#define T_float 271
#define T_openParenthesis 272
#define T_closedParanthesis 273
#define T_openFlowerBracket 274
#define T_closedFlowerBracket 275
#define T_RelationalOperator 276
#define T_LogicalOperator 277
#define T_UnaryOperator 278
#define T_AssignmentOperator 279
#define T_Semicolon 280
#define T_identifier 281
#define T_numericConstants 282
#define T_stringLiteral 283
#define T_character 284
#define T_plus 285
#define T_minus 286
#define T_mod 287
#define T_divide 288
#define T_multiply 289
#define T_whiteSpace 290
#define T_shortHand 291
#define T_LogicalAnd 292
#define T_LogicalOr 293
#define T_less 294
#define T_less_equal 295
#define T_greater 296
#define T_greater_equal 297
#define T_equal_equal 298
#define T_not_equal 299

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 465 "Yacc.y"

    char *str;
	struct ASTNode *NODE;

#line 160 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
