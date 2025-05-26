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
#line 2 "Yacc.y"

    #include <stdio.h>
    #include <stdlib.h>
	#include <string.h>
	#include <ctype.h>

	//#include "lex.yy.c"
	int yylex();
	int yydebug = 0;
	void yyerror(const char*);
	extern int yylineno;
	extern int st[100];
	extern int top;
	extern int count;
	extern void display();
	extern void insert_in_st(char*, char*, int, char*);
	char st1[100][100];
	char i_[2]="0";
	int temp_i = 0;				//current available temporary number
	char tmp_i[10];				//an array to hold temporary variable number as string. We assume this is below 999999999				
	char temp[10]="";			//an array to hold temporary varialbe name as string. We assume this is below T999999999	
	int label[20];
	int lnum = 0;				//current available label number.
	int ltop = 0;
	int abcd = 0;
	int l_while=0;
	int l_for=0;
	int flag_set = 1;
	int stop = -1;				//top of stack
	char G_val[10];
	FILE* ast_tree_output;


	typedef struct quadruples
  	{
  	  char *op;
  	  char *arg1;
  	  char *arg2;
  	  char *res;
  	}quad;
  	int quadindex = 0;			//current index of Q to store the quadruple in.
	quad Q[100];

	void push(char *a)			//push to top of stack
	{
		strcpy(st1[++stop],a);
	}

	// Statements -helper
	void TAC()				//to be called after any expression. say expr is b*c -> pop top three , ti = b*c and insert ti.
	{
	    strcpy(temp,"T");
	    sprintf(tmp_i, "%d", temp_i);
	    strcat(temp,tmp_i);
	    printf("%s = %s %s %s\n",temp,st1[stop-2],st1[stop],st1[stop - 1]);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*strlen(st1[stop]));
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(st1[stop-2]));
	    Q[quadindex].arg2 = (char*)malloc(sizeof(char)*strlen(st1[stop - 1]));
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(temp));
	    strcpy(Q[quadindex].op,st1[stop]);
	    strcpy(Q[quadindex].arg1,st1[stop-2]);
	    strcpy(Q[quadindex].arg2,st1[stop - 1]);
	    strcpy(Q[quadindex].res,temp);
	    quadindex++;
	    stop-=2;
	    strcpy(st1[stop],temp);
		temp_i++;
	}

	// Assignment Operations need a different TAC function as the operation performed is different
	void TAC_assign()
{
    printf("%s = %s\n", st1[stop-2], st1[stop-1]);
    Q[quadindex].op = (char*)malloc(sizeof(char));
    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(st1[stop-1]));
    Q[quadindex].arg2 = NULL;
    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(st1[stop-2]));
    strcpy(Q[quadindex].op, "=");
    strcpy(Q[quadindex].arg1, st1[stop-1]);
    strcpy(Q[quadindex].res, st1[stop-2]);
    quadindex++;
    stop-=2;
}


	void TAC_assign_back()
	{
		temp_i--;
	    strcpy(temp,"T");
	    sprintf(tmp_i, "%d", temp_i);
	    strcat(temp,tmp_i);
		temp_i++;
		printf("%s = %s\n",G_val,temp);
	    Q[quadindex].op = (char*)malloc(sizeof(char));
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(temp));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(G_val));
	    strcpy(Q[quadindex].op,"=");
		strcpy(Q[quadindex].arg1,temp);
	    strcpy(Q[quadindex].res,G_val);
		quadindex++;
	}
	// ICG - While

	// Create label for while
	void While_Loop_Label()
	{
	
	    label[ltop++] = lnum++;			
	    printf("L%d: \n", label[ltop - 1]);			// print label and increase label number for next use	
	    Q[quadindex].op = (char*)malloc(sizeof(char)*6);		//a label's quad 	
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum + 2));   //lum + 2 is a safe way to have enough space for L0, L1, ... etc. 
	    strcpy(Q[quadindex].op,"Label");
	    char x[10];
		x[0] = '0' + label[ltop - 1];
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	}

	// While Loop Condition
	void While_loop_cond()
	{
	 	strcpy(temp,"T");			
	 	sprintf(tmp_i, "%d", temp_i);		//if temp_i = 0, tmp_i has "0"		
	 	strcat(temp,tmp_i);					//temp has "T0"
	 	printf("%s = not %s\n",temp,st1[stop]);		//T0 has not of condition

		//since this is a unary operator, one of the operands is NULL
	    Q[quadindex].op = (char*)malloc(sizeof(char)*4);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(st1[stop]));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(temp));
	    strcpy(Q[quadindex].op,"not");
	    strcpy(Q[quadindex].arg1,st1[stop]);
	    strcpy(Q[quadindex].res,temp);
	    quadindex++;

		//if T0 goto label which will be placed after body
		//in this case op -> if, arg1 -> T0 , res -> L1
	    printf("if %s goto L%d\n",temp,lnum);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*3);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(temp));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"if");
	    strcpy(Q[quadindex].arg1,temp);
	    char x[10];
	    sprintf(x,"%d",lnum);char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	 	temp_i++;
		
		label[ltop++] = lnum;
		lnum++;
	}

	// End While loop
	void While_END()			// in the end insert goto label and also insert the label which should be branched to if condition fails
	{
		printf("goto L%d \n",label[ltop - 2]);	//ltop - 2 contains the label to be branched if true
		Q[quadindex].op = (char*)malloc(sizeof(char)*5);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(l_while+2));
	    strcpy(Q[quadindex].op,"goto");
	    char x[10];
	    sprintf(x,"%d",label[ltop]);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;

	    printf("L%d: \n", label[ltop - 1]);		//ltop - 1 contains the label to be branched if false
	    Q[quadindex].op = (char*)malloc(sizeof(char)*6);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"Label");
	    char x1[10];
	    sprintf(x1,"%d", label[ltop - 1]);
	    char l1[]="L";
	    strcpy(Q[quadindex].res,strcat(l1,x1));
	    quadindex++;
		ltop -= 2;							//since these labels have been used, decrease ltop by two 
	}

	// ICG - IF

	// Handle Initial IF as well as else if
	void IFSTMT()
	{

	    strcpy(temp,"T");
	    sprintf(tmp_i, "%d", temp_i);
	    strcat(temp,tmp_i);
	    printf("%s = not %s\n",temp,st1[stop]);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*4);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(st1[stop]));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(temp));
	    strcpy(Q[quadindex].op,"not");
	    strcpy(Q[quadindex].arg1,st1[stop]);
	    strcpy(Q[quadindex].res,temp);
	    quadindex++;

	    printf("if %s goto L%d\n",temp,lnum);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*3);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(temp));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"if");
	    strcpy(Q[quadindex].arg1,temp);
	    char x[10];
	    sprintf(x,"%d",lnum);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	    temp_i++;
		
	    label[ltop++] = lnum;
		++lnum;									//increase lnum for next needed label.
		
	}

	void Elif()
	{
		printf("L%d: \n",label[--ltop]);		//print the top in label stack as this is where runtime should come if cond is false
	    										//increase lable for the next time										
		

	    strcpy(temp,"T");
	    sprintf(tmp_i, "%d", temp_i);
	    strcat(temp,tmp_i);
	    printf("%s = not %s\n",temp,st1[stop]);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*4);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(st1[stop]));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(temp));
	    strcpy(Q[quadindex].op,"not");
	    strcpy(Q[quadindex].arg1,st1[stop]);
	    strcpy(Q[quadindex].res,temp);
	    quadindex++;
		

	    printf("if %s goto L%d\n",temp,lnum);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*3);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(temp));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"if");
	    strcpy(Q[quadindex].arg1,temp);
	    char x[10];
	    sprintf(x,"%d",lnum);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	    temp_i++;

	    label[ltop++] = lnum;							//store this as top of label stack and increase ltop
		++lnum;										//increase lnum for next needed label.
	}


	// Handle cleanup

	void if_else_cleanup()
	{
		int y;
		y = label[--ltop];
		printf("L%d: \n",y);
		Q[quadindex].op = (char*)malloc(sizeof(char)*6);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(y+2));
	    strcpy(Q[quadindex].op,"Label");
	    char x[10];
	    sprintf(x,"%d",y);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	}

	// ICG - For

	//Define Label for "FOR"
	void FOR_label()
	{
		label[ltop++] = lnum++;						//label stack is used for nested loops. Increase lnum for next label use
	    // l_for = lnum;
	    printf("L%d: \n", label[ltop - 1]);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*6);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"Label");
	    char x[10];
	    sprintf(x,"%d", label[ltop - 1]);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	}

	// Handle Loop Condition
	void FOR_Condition()
	{

	    strcpy(temp,"T");						//lets take condition as b < 4. This effectively says T1 = not T0. Note that expr would have made T0 = b < 4
	    sprintf(tmp_i, "%d", temp_i);
	    strcat(temp,tmp_i);
	    printf("%s = not %s\n",temp,st1[stop]);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*4);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(st1[stop]));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(temp));
	    strcpy(Q[quadindex].op,"not");
	    strcpy(Q[quadindex].arg1,st1[stop]);
	    strcpy(Q[quadindex].res,temp);
	    quadindex++;

	    printf("if %s goto L%d\n",temp,lnum);				// if T1 goto L1. Increase labele
	    Q[quadindex].op = (char*)malloc(sizeof(char)*3);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(temp));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"if");
	    strcpy(Q[quadindex].arg1,temp);
	    char x[10];
	    sprintf(x,"%d",lnum);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	    temp_i++;
	    label[ltop++] = lnum;								//store label in stack and increase lnum.
	    lnum++;

	    printf("goto L%d\n",lnum);							//goto body part. goto L2
	    Q[quadindex].op = (char*)malloc(sizeof(char)*5);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"goto");
	    char x1[10];
	    sprintf(x1,"%d",lnum);
	    char l1[]="L";
	    strcpy(Q[quadindex].res,strcat(l1,x1));
	    quadindex++;
	    label[ltop++] = lnum++;							//store label in stack and increase lnum.


	
	    printf("L%d: \n",lnum);							//L3:
	    Q[quadindex].op = (char*)malloc(sizeof(char)*6);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"Label");
	    char x2[10];
	    sprintf(x2,"%d",lnum);
	    char l2[]="L";
	    strcpy(Q[quadindex].res,strcat(l2,x2));
	    quadindex++;
		label[ltop++] = lnum++;
	}

	// Increment
	void FOR_INC_Cond()
	{
	    int x;
	    x = label[ltop - 4];							//after processing increment, should go and evaluate condition again. goto L0
	    printf("goto L%d \n",x);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*5);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(temp));
	    strcpy(Q[quadindex].op,"goto");
	    char jug[10];
	    sprintf(jug,"%d",x);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,jug));
	    quadindex++;

	    printf("L%d: \n",label[ltop - 2]);							//this is where after processing condition you should come to . L2:
	    Q[quadindex].op = (char*)malloc(sizeof(char)*6);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(x+2));
	    strcpy(Q[quadindex].op,"Label");
	    char jug1[10];
	    sprintf(jug1,"%d", label[ltop - 2]);
	    char l1[]="L";
	    strcpy(Q[quadindex].res,strcat(l1,jug1));
	    quadindex++;
	}

	// Ending of for
	void FOR_End()
	{
	    int x;
	    x = label[ltop - 1];								//goto L3 (increment condition)
	    printf("goto L%d \n",x);

	    Q[quadindex].op = (char*)malloc(sizeof(char)*5);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(temp));
	    strcpy(Q[quadindex].op,"goto");
	    char jug[10];
	    sprintf(jug,"%d",x);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,jug));
	    quadindex++;

	    printf("L%d: \n",label[ltop - 3]);							//L1:
	    Q[quadindex].op = (char*)malloc(sizeof(char)*6);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(x+2));
	    strcpy(Q[quadindex].op,"Label");
	    char jug1[10];
	    sprintf(jug1,"%d", label[ltop - 3]);
	    char l1[]="L";
	    strcpy(Q[quadindex].res,strcat(l1,jug1));
	    quadindex++;
		ltop -= 4;	
	}

	char LineBreaker[] = "\n_______________________________________________________________________________________________________\n";
	
	//node in AST
	typedef struct ASTNode
	{
		struct ASTNode *left;
		struct ASTNode *right;
		char *token;
	} node;
	
	node *Construct_AST(node *left, node *right, char *token)
	{
		node *newnode = (node *)malloc(sizeof(node));
		char *newstr = (char *)malloc(strlen(token)+1);
		strcpy(newstr, token);
		newnode->left = left;
		newnode->right = right;
		newnode->token = newstr;
		return(newnode); 
	}
	
	void Display_tree(node *tree)
	{
		// if (tree->left || tree->right)
		// 	fprintf(ast_tree_output, "%s", "(");
		// fprintf(ast_tree_output, " %s ", tree->token);
		// if (tree->left)
		// 	Display_tree(tree->left);
		// if (tree->right)
		// 	Display_tree(tree->right);
		// if (tree->left || tree->right)
		// 	fprintf(ast_tree_output, "%s", ")");
	}

#line 534 "y.tab.c"

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

#line 680 "y.tab.c"

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
  YYSYMBOL_T_keyword = 3,                  /* T_keyword  */
  YYSYMBOL_T_int = 4,                      /* T_int  */
  YYSYMBOL_T_main = 5,                     /* T_main  */
  YYSYMBOL_T_type = 6,                     /* T_type  */
  YYSYMBOL_T_return = 7,                   /* T_return  */
  YYSYMBOL_T_for = 8,                      /* T_for  */
  YYSYMBOL_T_if = 9,                       /* T_if  */
  YYSYMBOL_T_else = 10,                    /* T_else  */
  YYSYMBOL_T_while = 11,                   /* T_while  */
  YYSYMBOL_T_InputStream = 12,             /* T_InputStream  */
  YYSYMBOL_T_OutputStream = 13,            /* T_OutputStream  */
  YYSYMBOL_T_char = 14,                    /* T_char  */
  YYSYMBOL_T_double = 15,                  /* T_double  */
  YYSYMBOL_T_float = 16,                   /* T_float  */
  YYSYMBOL_T_openParenthesis = 17,         /* T_openParenthesis  */
  YYSYMBOL_T_closedParanthesis = 18,       /* T_closedParanthesis  */
  YYSYMBOL_T_openFlowerBracket = 19,       /* T_openFlowerBracket  */
  YYSYMBOL_T_closedFlowerBracket = 20,     /* T_closedFlowerBracket  */
  YYSYMBOL_T_RelationalOperator = 21,      /* T_RelationalOperator  */
  YYSYMBOL_T_LogicalOperator = 22,         /* T_LogicalOperator  */
  YYSYMBOL_T_UnaryOperator = 23,           /* T_UnaryOperator  */
  YYSYMBOL_T_AssignmentOperator = 24,      /* T_AssignmentOperator  */
  YYSYMBOL_T_Semicolon = 25,               /* T_Semicolon  */
  YYSYMBOL_T_identifier = 26,              /* T_identifier  */
  YYSYMBOL_T_numericConstants = 27,        /* T_numericConstants  */
  YYSYMBOL_T_stringLiteral = 28,           /* T_stringLiteral  */
  YYSYMBOL_T_character = 29,               /* T_character  */
  YYSYMBOL_T_plus = 30,                    /* T_plus  */
  YYSYMBOL_T_minus = 31,                   /* T_minus  */
  YYSYMBOL_T_mod = 32,                     /* T_mod  */
  YYSYMBOL_T_divide = 33,                  /* T_divide  */
  YYSYMBOL_T_multiply = 34,                /* T_multiply  */
  YYSYMBOL_T_whiteSpace = 35,              /* T_whiteSpace  */
  YYSYMBOL_T_shortHand = 36,               /* T_shortHand  */
  YYSYMBOL_T_LogicalAnd = 37,              /* T_LogicalAnd  */
  YYSYMBOL_T_LogicalOr = 38,               /* T_LogicalOr  */
  YYSYMBOL_T_less = 39,                    /* T_less  */
  YYSYMBOL_T_less_equal = 40,              /* T_less_equal  */
  YYSYMBOL_T_greater = 41,                 /* T_greater  */
  YYSYMBOL_T_greater_equal = 42,           /* T_greater_equal  */
  YYSYMBOL_T_equal_equal = 43,             /* T_equal_equal  */
  YYSYMBOL_T_not_equal = 44,               /* T_not_equal  */
  YYSYMBOL_YYACCEPT = 45,                  /* $accept  */
  YYSYMBOL_Start = 46,                     /* Start  */
  YYSYMBOL_block_end_flower = 47,          /* block_end_flower  */
  YYSYMBOL_block = 48,                     /* block  */
  YYSYMBOL_Multiple_stmts = 49,            /* Multiple_stmts  */
  YYSYMBOL_stmt = 50,                      /* stmt  */
  YYSYMBOL_for_stmt = 51,                  /* for_stmt  */
  YYSYMBOL_52_1 = 52,                      /* $@1  */
  YYSYMBOL_53_2 = 53,                      /* $@2  */
  YYSYMBOL_54_3 = 54,                      /* $@3  */
  YYSYMBOL_while_stmt = 55,                /* while_stmt  */
  YYSYMBOL_56_4 = 56,                      /* $@4  */
  YYSYMBOL_57_5 = 57,                      /* $@5  */
  YYSYMBOL_if_stmt = 58,                   /* if_stmt  */
  YYSYMBOL_59_6 = 59,                      /* $@6  */
  YYSYMBOL_elseif_else_empty = 60,         /* elseif_else_empty  */
  YYSYMBOL_61_7 = 61,                      /* $@7  */
  YYSYMBOL_62_8 = 62,                      /* $@8  */
  YYSYMBOL_63_9 = 63,                      /* $@9  */
  YYSYMBOL_Multiple_stmts_not_if = 64,     /* Multiple_stmts_not_if  */
  YYSYMBOL_stmt_without_if = 65,           /* stmt_without_if  */
  YYSYMBOL_Assignment_stmt = 66,           /* Assignment_stmt  */
  YYSYMBOL_expr_without_constants = 67,    /* expr_without_constants  */
  YYSYMBOL_expr = 68,                      /* expr  */
  YYSYMBOL_expr_or_empty_with_semicolon_and_assignment = 69, /* expr_or_empty_with_semicolon_and_assignment  */
  YYSYMBOL_expr_or_empty_with_assignment_and_closed_parent = 70, /* expr_or_empty_with_assignment_and_closed_parent  */
  YYSYMBOL_idid = 71,                      /* idid  */
  YYSYMBOL_sc = 72,                        /* sc  */
  YYSYMBOL_nc = 73,                        /* nc  */
  YYSYMBOL_expr_or_empty = 74,             /* expr_or_empty  */
  YYSYMBOL_openflower = 75,                /* openflower  */
  YYSYMBOL_closeflower = 76                /* closeflower  */
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
typedef yytype_uint8 yy_state_t;

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

#if 1

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
#endif /* 1 */

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   441

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  91
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  175

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   299


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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   499,   499,   503,   504,   509,   510,   511,   523,   524,
     531,   532,   533,   534,   535,   536,   542,   542,   542,   542,
     553,   553,   553,   557,   557,   559,   559,   560,   560,   561,
     561,   562,   565,   566,   569,   570,   571,   572,   575,   576,
     577,   578,   579,   580,   581,   582,   583,   584,   585,   586,
     587,   593,   594,   595,   596,   597,   598,   599,   600,   601,
     602,   603,   604,   605,   606,   610,   611,   612,   613,   614,
     615,   616,   617,   618,   619,   620,   621,   622,   623,   624,
     625,   628,   629,   631,   632,   634,   636,   638,   641,   642,
     645,   646
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "T_keyword", "T_int",
  "T_main", "T_type", "T_return", "T_for", "T_if", "T_else", "T_while",
  "T_InputStream", "T_OutputStream", "T_char", "T_double", "T_float",
  "T_openParenthesis", "T_closedParanthesis", "T_openFlowerBracket",
  "T_closedFlowerBracket", "T_RelationalOperator", "T_LogicalOperator",
  "T_UnaryOperator", "T_AssignmentOperator", "T_Semicolon", "T_identifier",
  "T_numericConstants", "T_stringLiteral", "T_character", "T_plus",
  "T_minus", "T_mod", "T_divide", "T_multiply", "T_whiteSpace",
  "T_shortHand", "T_LogicalAnd", "T_LogicalOr", "T_less", "T_less_equal",
  "T_greater", "T_greater_equal", "T_equal_equal", "T_not_equal",
  "$accept", "Start", "block_end_flower", "block", "Multiple_stmts",
  "stmt", "for_stmt", "$@1", "$@2", "$@3", "while_stmt", "$@4", "$@5",
  "if_stmt", "$@6", "elseif_else_empty", "$@7", "$@8", "$@9",
  "Multiple_stmts_not_if", "stmt_without_if", "Assignment_stmt",
  "expr_without_constants", "expr",
  "expr_or_empty_with_semicolon_and_assignment",
  "expr_or_empty_with_assignment_and_closed_parent", "idid", "sc", "nc",
  "expr_or_empty", "openflower", "closeflower", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-132)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-75)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      14,    11,    44,    32,  -132,    48,    41,  -132,    72,    37,
      45,    45,    60,    62,  -132,    45,    45,    45,  -132,  -132,
    -132,  -132,  -132,    72,  -132,  -132,  -132,    66,   270,   -10,
    -132,  -132,  -132,  -132,    73,    78,    89,   265,    79,    97,
      98,   102,  -132,    72,  -132,  -132,  -132,   265,   265,   265,
     265,   265,   265,   265,   265,   265,   265,   265,   265,   265,
     265,   265,   265,   265,    93,   210,  -132,   107,   165,  -132,
     265,   265,   265,   265,  -132,   284,   284,  -132,  -132,  -132,
     397,   397,   154,   154,   154,   154,   154,   154,   210,   210,
    -132,   352,    20,    22,  -132,    34,    64,  -132,    89,  -132,
    -132,   182,  -132,    94,  -132,    95,  -132,   105,   265,   265,
     265,   265,   265,   265,   265,   265,   265,   265,   265,   265,
     265,  -132,    42,  -132,   106,   256,   117,   123,   127,   367,
     382,    -1,    76,   317,   327,   337,   347,    89,  -132,   126,
    -132,    72,    42,   109,  -132,   129,    18,  -132,  -132,  -132,
    -132,    42,  -132,   132,   271,    41,  -132,   265,  -132,  -132,
    -132,  -132,    72,   128,   290,    72,   227,  -132,  -132,  -132,
    -132,  -132,    42,   126,  -132
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,    90,     0,     0,
       0,     0,     0,     0,    20,     0,     0,     0,    91,    85,
      87,    86,     2,     0,    13,    12,    11,     0,     0,    67,
      66,    65,     4,    15,     0,     0,    89,     0,     0,     0,
       0,     0,     3,     0,     9,    14,    10,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    88,    16,     0,     0,    67,
       0,     0,     0,     0,     8,    68,    69,    72,    70,    71,
      73,    74,    75,    76,    77,    78,    79,    80,    38,    39,
      43,     0,    67,    65,    40,    66,    65,    82,    89,    81,
      23,     0,    49,    66,    47,    65,    45,    65,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    17,     0,    21,    68,    69,    72,    70,    71,    57,
      58,    75,    76,    77,    78,    79,    80,    89,     7,    31,
       6,     0,     0,     0,    18,     0,    27,    24,     5,    22,
      84,     0,    83,     0,     0,     0,    19,     0,    33,    37,
      36,    28,     0,     0,     0,     0,     0,    32,    35,    34,
      30,    25,     0,    31,    26
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -132,  -132,  -129,  -131,   -37,    -4,    -3,  -132,  -132,  -132,
       5,  -132,  -132,  -132,  -132,   -13,  -132,  -132,  -132,  -132,
    -132,   -26,   -50,   119,    65,  -132,    -8,   -29,    12,    25,
      -5,   -18
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,    22,   139,    42,   140,    24,    98,   137,   151,
      25,    38,   142,    26,   122,   147,   172,   154,   155,   161,
     162,    27,    90,    28,    66,   144,    69,    30,    31,    67,
     141,    32
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      29,     8,    34,    35,    23,    44,    74,    39,    40,    41,
      64,   149,   148,    94,    60,    29,     3,   -59,     1,    43,
     156,   102,   104,   106,   -59,    44,    61,   153,    29,    47,
      48,    49,    50,    51,    95,    29,   170,   -29,   -51,    43,
     -44,   173,   103,     9,     4,   -51,    10,   -44,    11,     5,
      12,    13,   -41,    14,    92,    92,    15,    16,    17,   -41,
       7,     7,    33,    92,    92,    92,     6,   138,    19,    20,
      21,    19,    64,     9,    93,    96,    10,    36,    11,    37,
      12,    13,   -42,    14,   105,   107,    15,    16,    17,   -42,
      29,    45,    18,    10,   -60,    11,    70,    62,    19,    20,
      21,   -60,    63,    15,    16,    17,    47,    48,    49,    50,
      51,   143,   -50,   -48,    29,    19,    20,    21,    97,   -50,
     -48,    71,    72,   -46,   -52,   167,    73,   150,   163,    29,
     -46,   -52,    99,    29,    29,   -56,   146,    23,    49,    50,
      51,   -54,   -56,    29,    44,   -55,    29,   152,   -54,   157,
     165,   159,   -55,   168,    29,    65,    68,    29,    43,   160,
     174,    23,   145,   121,    29,     0,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    91,    91,   100,    47,    48,    49,    50,    51,   101,
      91,    91,    91,     0,     0,    47,    48,    49,    50,    51,
     123,     0,    52,    53,    54,    55,    56,    57,    58,    59,
       0,     0,    47,    48,    49,    50,    51,    65,     0,    52,
      53,    54,    55,    56,    57,    58,    59,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
      47,    48,    49,    50,    51,   171,     0,    52,    53,    54,
      55,    56,    57,    58,    59,     0,    65,    47,    48,    49,
      50,    51,     0,     0,    52,    53,    54,    55,    56,    57,
      58,    59,     0,   164,   -53,    10,   166,    11,     0,    12,
       0,   -53,    14,     0,     0,    15,    16,    17,    49,    50,
      51,    19,    20,    21,     0,    46,   158,    19,    20,    21,
      47,    48,    49,    50,    51,     0,     0,    52,    53,    54,
      55,    56,    57,    58,    59,   169,    49,    50,    51,     0,
      47,    48,    49,    50,    51,     0,     0,    52,    53,    54,
      55,    56,    57,    58,    59,   -61,     0,     0,     0,     0,
       0,     0,   -61,     0,     0,   -62,     0,    47,    48,    49,
      50,    51,   -62,     0,     0,   -63,     0,    47,    48,    49,
      50,    51,   -63,     0,     0,   -64,     0,    47,    48,    49,
      50,    51,   -64,     0,     0,     0,     0,    47,    48,    49,
      50,    51,   108,   109,   110,   111,   112,     0,     0,   113,
     114,   115,   116,   117,   118,   119,   120,    47,    48,    49,
      50,    51,     0,     0,   -73,   -73,    54,    55,    56,    57,
      58,    59,    47,    48,    49,    50,    51,     0,     0,   -74,
     -74,    54,    55,    56,    57,    58,    59,    47,    48,    49,
      50,    51,     0,     0,     0,     0,    54,    55,    56,    57,
      58,    59
};

static const yytype_int16 yycheck[] =
{
       8,     6,    10,    11,     8,    23,    43,    15,    16,    17,
      36,   142,   141,    63,    24,    23,     5,    18,     4,    23,
     151,    71,    72,    73,    25,    43,    36,     9,    36,    30,
      31,    32,    33,    34,    63,    43,   165,    19,    18,    43,
      18,   172,    71,     1,     0,    25,     4,    25,     6,    17,
       8,     9,    18,    11,    62,    63,    14,    15,    16,    25,
      19,    19,    25,    71,    72,    73,    18,    25,    26,    27,
      28,    26,    98,     1,    62,    63,     4,    17,     6,    17,
       8,     9,    18,    11,    72,    73,    14,    15,    16,    25,
      98,    25,    20,     4,    18,     6,    17,    24,    26,    27,
      28,    25,    24,    14,    15,    16,    30,    31,    32,    33,
      34,   137,    18,    18,   122,    26,    27,    28,    25,    25,
      25,    24,    24,    18,    18,   162,    24,    18,   154,   137,
      25,    25,    25,   141,   142,    18,    10,   141,    32,    33,
      34,    18,    25,   151,   162,    18,   154,    18,    25,    17,
     155,   154,    25,    25,   162,    36,    37,   165,   162,   154,
     173,   165,   137,    98,   172,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    18,    30,    31,    32,    33,    34,    70,
      71,    72,    73,    -1,    -1,    30,    31,    32,    33,    34,
      18,    -1,    37,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    30,    31,    32,    33,    34,    98,    -1,    37,
      38,    39,    40,    41,    42,    43,    44,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
      30,    31,    32,    33,    34,    18,    -1,    37,    38,    39,
      40,    41,    42,    43,    44,    -1,   137,    30,    31,    32,
      33,    34,    -1,    -1,    37,    38,    39,    40,    41,    42,
      43,    44,    -1,   154,    18,     4,   157,     6,    -1,     8,
      -1,    25,    11,    -1,    -1,    14,    15,    16,    32,    33,
      34,    26,    27,    28,    -1,    25,    25,    26,    27,    28,
      30,    31,    32,    33,    34,    -1,    -1,    37,    38,    39,
      40,    41,    42,    43,    44,    25,    32,    33,    34,    -1,
      30,    31,    32,    33,    34,    -1,    -1,    37,    38,    39,
      40,    41,    42,    43,    44,    18,    -1,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    -1,    18,    -1,    30,    31,    32,
      33,    34,    25,    -1,    -1,    18,    -1,    30,    31,    32,
      33,    34,    25,    -1,    -1,    18,    -1,    30,    31,    32,
      33,    34,    25,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    30,    31,    32,    33,    34,    -1,    -1,    37,
      38,    39,    40,    41,    42,    43,    44,    30,    31,    32,
      33,    34,    -1,    -1,    37,    38,    39,    40,    41,    42,
      43,    44,    30,    31,    32,    33,    34,    -1,    -1,    37,
      38,    39,    40,    41,    42,    43,    44,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    39,    40,    41,    42,
      43,    44
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,    46,     5,     0,    17,    18,    19,    75,     1,
       4,     6,     8,     9,    11,    14,    15,    16,    20,    26,
      27,    28,    47,    50,    51,    55,    58,    66,    68,    71,
      72,    73,    76,    25,    71,    71,    17,    17,    56,    71,
      71,    71,    49,    50,    76,    25,    25,    30,    31,    32,
      33,    34,    37,    38,    39,    40,    41,    42,    43,    44,
      24,    36,    24,    24,    66,    68,    69,    74,    68,    71,
      17,    24,    24,    24,    49,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      67,    68,    71,    73,    67,    72,    73,    25,    52,    25,
      18,    68,    67,    72,    67,    73,    67,    73,    30,    31,
      32,    33,    34,    37,    38,    39,    40,    41,    42,    43,
      44,    69,    59,    18,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    53,    25,    48,
      50,    75,    57,    66,    70,    74,    10,    60,    47,    48,
      18,    54,    18,     9,    62,    63,    48,    17,    25,    51,
      55,    64,    65,    66,    68,    75,    68,    49,    25,    25,
      47,    18,    61,    48,    60
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    47,    48,    48,    48,    49,    49,
      50,    50,    50,    50,    50,    50,    52,    53,    54,    51,
      56,    57,    55,    59,    58,    61,    60,    62,    60,    63,
      60,    60,    64,    64,    65,    65,    65,    65,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    69,    69,    70,    70,    71,    72,    73,    74,    74,
      75,    76
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     6,     2,     1,     2,     1,     1,     2,     1,
       2,     1,     1,     1,     2,     2,     0,     0,     0,     9,
       0,     0,     7,     0,     7,     0,     8,     0,     3,     0,
       4,     0,     2,     1,     2,     2,     1,     1,     3,     3,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     2,     1,     1,     1,     1,     0,
       1,     1
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


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

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

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
  case 2: /* Start: T_int T_main T_openParenthesis T_closedParanthesis openflower block_end_flower  */
#line 499 "Yacc.y"
                                                                                        {(yyval.NODE) = (yyvsp[0].NODE);}
#line 2183 "y.tab.c"
    break;

  case 3: /* block_end_flower: stmt Multiple_stmts  */
#line 503 "Yacc.y"
                                                                                        {(yyval.NODE) = (yyvsp[-1].NODE);}
#line 2189 "y.tab.c"
    break;

  case 4: /* block_end_flower: closeflower  */
#line 504 "Yacc.y"
                                                                                                                {(yyval.NODE) = Construct_AST(NULL, NULL, ";"); }
#line 2195 "y.tab.c"
    break;

  case 5: /* block: openflower block_end_flower  */
#line 509 "Yacc.y"
                                                                                {(yyval.NODE) = (yyvsp[0].NODE);}
#line 2201 "y.tab.c"
    break;

  case 6: /* block: stmt  */
#line 510 "Yacc.y"
                                                                                                                {(yyval.NODE) = (yyvsp[0].NODE);}
#line 2207 "y.tab.c"
    break;

  case 7: /* block: T_Semicolon  */
#line 511 "Yacc.y"
                                                                                                        {(yyval.NODE) = Construct_AST(NULL, NULL, ";"); }
#line 2213 "y.tab.c"
    break;

  case 8: /* Multiple_stmts: stmt Multiple_stmts  */
#line 523 "Yacc.y"
                                                                                {(yyval.NODE) = (yyvsp[-1].NODE);}
#line 2219 "y.tab.c"
    break;

  case 9: /* Multiple_stmts: closeflower  */
#line 524 "Yacc.y"
                                                                                                        {(yyval.NODE) = Construct_AST(NULL, NULL, ";"); }
#line 2225 "y.tab.c"
    break;

  case 10: /* stmt: expr T_Semicolon  */
#line 531 "Yacc.y"
                                                        {(yyval.NODE) = (yyvsp[-1].NODE); Display_tree((yyval.NODE)); fprintf(ast_tree_output, "\n");}
#line 2231 "y.tab.c"
    break;

  case 11: /* stmt: if_stmt  */
#line 532 "Yacc.y"
                                                                        {(yyval.NODE) = (yyvsp[0].NODE); Display_tree((yyval.NODE)); fprintf(ast_tree_output, "\n");}
#line 2237 "y.tab.c"
    break;

  case 12: /* stmt: while_stmt  */
#line 533 "Yacc.y"
                                                                {(yyval.NODE) = (yyvsp[0].NODE); Display_tree((yyval.NODE));fprintf(ast_tree_output, "\n");}
#line 2243 "y.tab.c"
    break;

  case 13: /* stmt: for_stmt  */
#line 534 "Yacc.y"
                                                                        {(yyval.NODE) = (yyvsp[0].NODE); Display_tree((yyval.NODE)); fprintf(ast_tree_output, "\n");}
#line 2249 "y.tab.c"
    break;

  case 14: /* stmt: Assignment_stmt T_Semicolon  */
#line 535 "Yacc.y"
                                                {(yyval.NODE) = (yyvsp[-1].NODE); Display_tree((yyval.NODE)); fprintf(ast_tree_output, "\n");}
#line 2255 "y.tab.c"
    break;

  case 15: /* stmt: error T_Semicolon  */
#line 536 "Yacc.y"
                                                        {(yyval.NODE) = Construct_AST(NULL, NULL, ";"); }
#line 2261 "y.tab.c"
    break;

  case 16: /* $@1: %empty  */
#line 542 "Yacc.y"
                                                                               {FOR_label();}
#line 2267 "y.tab.c"
    break;

  case 17: /* $@2: %empty  */
#line 542 "Yacc.y"
                                                                                                                                          {FOR_Condition();}
#line 2273 "y.tab.c"
    break;

  case 18: /* $@3: %empty  */
#line 542 "Yacc.y"
                                                                                                                                                                                                             {FOR_INC_Cond();}
#line 2279 "y.tab.c"
    break;

  case 19: /* for_stmt: T_for T_openParenthesis expr_or_empty_with_semicolon_and_assignment $@1 expr_or_empty_with_semicolon_and_assignment $@2 expr_or_empty_with_assignment_and_closed_parent $@3 block  */
#line 542 "Yacc.y"
                                                                                                                                                                                                                                        {{ 	FOR_End();node* left;
																																	node* right;
																																	left = Construct_AST((yyvsp[-4].NODE), (yyvsp[-2].NODE), "Cond_Loopstmts");
																																	right = Construct_AST((yyvsp[-6].NODE),(yyvsp[-4].NODE),"Init_&_Increment");
																																	(yyval.NODE) = Construct_AST(left,right,"FOR");
																																	}}
#line 2290 "y.tab.c"
    break;

  case 20: /* $@4: %empty  */
#line 553 "Yacc.y"
                     {While_Loop_Label();}
#line 2296 "y.tab.c"
    break;

  case 21: /* $@5: %empty  */
#line 553 "Yacc.y"
                                                                                      {While_loop_cond();}
#line 2302 "y.tab.c"
    break;

  case 22: /* while_stmt: T_while $@4 T_openParenthesis expr T_closedParanthesis $@5 block  */
#line 553 "Yacc.y"
                                                                                                                                        {While_END();(yyval.NODE) = Construct_AST((yyvsp[-4].str), (yyvsp[-2].str), "While"); }
#line 2308 "y.tab.c"
    break;

  case 23: /* $@6: %empty  */
#line 557 "Yacc.y"
                                                          {IFSTMT();}
#line 2314 "y.tab.c"
    break;

  case 24: /* if_stmt: T_if T_openParenthesis expr T_closedParanthesis $@6 block elseif_else_empty  */
#line 557 "Yacc.y"
                                                                                              {(yyval.NODE) = Construct_AST((yyvsp[-4].NODE), (yyvsp[-1].NODE), "IF");}
#line 2320 "y.tab.c"
    break;

  case 25: /* $@7: %empty  */
#line 559 "Yacc.y"
                                                                           {;Elif();}
#line 2326 "y.tab.c"
    break;

  case 26: /* elseif_else_empty: T_else T_if T_openParenthesis expr T_closedParanthesis $@7 block elseif_else_empty  */
#line 559 "Yacc.y"
                                                                                                              {(yyval.NODE) = Construct_AST((yyvsp[-4].NODE), (yyvsp[-1].NODE), "ELSEIF"); }
#line 2332 "y.tab.c"
    break;

  case 27: /* $@8: %empty  */
#line 560 "Yacc.y"
                                                 {if_else_cleanup();}
#line 2338 "y.tab.c"
    break;

  case 28: /* elseif_else_empty: T_else $@8 Multiple_stmts_not_if  */
#line 560 "Yacc.y"
                                                                                            {(yyval.NODE) = (yyvsp[0].NODE);}
#line 2344 "y.tab.c"
    break;

  case 29: /* $@9: %empty  */
#line 561 "Yacc.y"
                                                 {if_else_cleanup();}
#line 2350 "y.tab.c"
    break;

  case 30: /* elseif_else_empty: T_else $@9 openflower block_end_flower  */
#line 561 "Yacc.y"
                                                                                                  {(yyval.NODE) = (yyvsp[0].NODE);}
#line 2356 "y.tab.c"
    break;

  case 31: /* elseif_else_empty: %empty  */
#line 562 "Yacc.y"
                                          {if_else_cleanup(); (yyval.NODE) = Construct_AST(NULL, NULL, ";"); }
#line 2362 "y.tab.c"
    break;

  case 32: /* Multiple_stmts_not_if: stmt_without_if Multiple_stmts  */
#line 565 "Yacc.y"
                                                       {(yyval.NODE) = (yyvsp[-1].NODE);}
#line 2368 "y.tab.c"
    break;

  case 33: /* Multiple_stmts_not_if: T_Semicolon  */
#line 566 "Yacc.y"
                                                     {(yyval.NODE) = Construct_AST(NULL, NULL, ";"); }
#line 2374 "y.tab.c"
    break;

  case 34: /* stmt_without_if: expr T_Semicolon  */
#line 569 "Yacc.y"
                                                                                                                {(yyval.NODE) = (yyvsp[-1].NODE);}
#line 2380 "y.tab.c"
    break;

  case 35: /* stmt_without_if: Assignment_stmt T_Semicolon  */
#line 570 "Yacc.y"
                                                                                                                {(yyval.NODE) = (yyvsp[-1].NODE);Display_tree((yyval.NODE));fprintf(ast_tree_output, "\n");}
#line 2386 "y.tab.c"
    break;

  case 36: /* stmt_without_if: while_stmt  */
#line 571 "Yacc.y"
                                                                                                                                {(yyval.NODE) = (yyvsp[0].NODE);}
#line 2392 "y.tab.c"
    break;

  case 37: /* stmt_without_if: for_stmt  */
#line 572 "Yacc.y"
                                                                                                                                        {(yyval.NODE) = (yyvsp[0].NODE);}
#line 2398 "y.tab.c"
    break;

  case 38: /* Assignment_stmt: idid T_AssignmentOperator expr  */
#line 575 "Yacc.y"
                                                       {push("=");TAC_assign();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE),(yyvsp[0].NODE),"=");}
#line 2404 "y.tab.c"
    break;

  case 39: /* Assignment_stmt: idid T_shortHand expr  */
#line 576 "Yacc.y"
                                                                {push("se");TAC_assign();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE),(yyvsp[0].NODE),"SE"); }
#line 2410 "y.tab.c"
    break;

  case 40: /* Assignment_stmt: T_type idid T_AssignmentOperator expr_without_constants  */
#line 577 "Yacc.y"
                                                                                                  {push("=");strcpy(G_val,(yyvsp[-2].NODE)->token);TAC_assign_back();insert_in_st((yyvsp[-3].str), (yyvsp[-2].NODE)->token, st[top], "j");(yyval.NODE) = Construct_AST((yyvsp[-2].NODE),(yyvsp[0].NODE),"=");}
#line 2416 "y.tab.c"
    break;

  case 41: /* Assignment_stmt: T_type idid T_AssignmentOperator sc  */
#line 578 "Yacc.y"
                                                                              {push("=");TAC_assign();insert_in_st((yyvsp[-3].str), (yyvsp[-2].NODE)->token, st[top], (yyvsp[0].NODE)->token);(yyval.NODE) = Construct_AST((yyvsp[-2].NODE),(yyvsp[0].NODE),"=");}
#line 2422 "y.tab.c"
    break;

  case 42: /* Assignment_stmt: T_type idid T_AssignmentOperator nc  */
#line 579 "Yacc.y"
                                                                              {push("=");TAC_assign();insert_in_st((yyvsp[-3].str), (yyvsp[-2].NODE)->token, st[top], (yyvsp[0].NODE)->token);(yyval.NODE) = Construct_AST((yyvsp[-2].NODE),(yyvsp[0].NODE),"=");}
#line 2428 "y.tab.c"
    break;

  case 43: /* Assignment_stmt: T_int idid T_AssignmentOperator expr_without_constants  */
#line 580 "Yacc.y"
                                                                                                 {push("=");strcpy(G_val,(yyvsp[-2].NODE)->token);TAC_assign_back();insert_in_st((yyvsp[-3].str), (yyvsp[-2].NODE)->token, st[top], "j");(yyval.NODE) = Construct_AST((yyvsp[-2].NODE),(yyvsp[0].NODE),"=");}
#line 2434 "y.tab.c"
    break;

  case 44: /* Assignment_stmt: T_int idid T_AssignmentOperator nc  */
#line 581 "Yacc.y"
                                                                             {push("=");TAC_assign();insert_in_st((yyvsp[-3].str), (yyvsp[-2].NODE)->token, st[top], (yyvsp[0].NODE)->token);(yyval.NODE) = Construct_AST((yyvsp[-2].NODE),(yyvsp[0].NODE),"=");}
#line 2440 "y.tab.c"
    break;

  case 45: /* Assignment_stmt: T_float idid T_AssignmentOperator expr_without_constants  */
#line 582 "Yacc.y"
                                                                                                   {push("=");strcpy(G_val,(yyvsp[-2].NODE)->token);TAC_assign_back();insert_in_st((yyvsp[-3].str), (yyvsp[-2].NODE)->token, st[top], "f");(yyval.NODE) = Construct_AST((yyvsp[-2].NODE),(yyvsp[0].NODE),"=");}
#line 2446 "y.tab.c"
    break;

  case 46: /* Assignment_stmt: T_float idid T_AssignmentOperator nc  */
#line 583 "Yacc.y"
                                                                               {push("=");TAC_assign();insert_in_st((yyvsp[-3].str), (yyvsp[-2].NODE)->token, st[top], (yyvsp[0].NODE)->token);(yyval.NODE) = Construct_AST((yyvsp[-2].NODE),(yyvsp[0].NODE),"=");}
#line 2452 "y.tab.c"
    break;

  case 47: /* Assignment_stmt: T_double idid T_AssignmentOperator expr_without_constants  */
#line 584 "Yacc.y"
                                                                                                    {push("=");strcpy(G_val,(yyvsp[-2].NODE)->token);TAC_assign_back();insert_in_st((yyvsp[-3].str), (yyvsp[-2].NODE)->token, st[top], "d");(yyval.NODE) = Construct_AST((yyvsp[-2].NODE),(yyvsp[0].NODE),"=");}
#line 2458 "y.tab.c"
    break;

  case 48: /* Assignment_stmt: T_double idid T_AssignmentOperator nc  */
#line 585 "Yacc.y"
                                                                                {push("=");TAC_assign();insert_in_st((yyvsp[-3].str), (yyvsp[-2].NODE)->token, st[top], (yyvsp[0].NODE)->token);(yyval.NODE) = Construct_AST((yyvsp[-2].NODE),(yyvsp[0].NODE),"=");}
#line 2464 "y.tab.c"
    break;

  case 49: /* Assignment_stmt: T_char idid T_AssignmentOperator expr_without_constants  */
#line 586 "Yacc.y"
                                                                                                  {push("=");strcpy(G_val,(yyvsp[-2].NODE)->token);TAC_assign_back();insert_in_st((yyvsp[-3].str), (yyvsp[-2].NODE)->token, st[top], "c");(yyval.NODE) = Construct_AST((yyvsp[-2].NODE),(yyvsp[0].NODE),"=");}
#line 2470 "y.tab.c"
    break;

  case 50: /* Assignment_stmt: T_char idid T_AssignmentOperator sc  */
#line 587 "Yacc.y"
                                                                              {push("=");TAC_assign();insert_in_st((yyvsp[-3].str), (yyvsp[-2].NODE)->token, st[top], (yyvsp[0].NODE)->token);(yyval.NODE) = Construct_AST((yyvsp[-2].NODE),(yyvsp[0].NODE),"=");}
#line 2476 "y.tab.c"
    break;

  case 51: /* expr_without_constants: idid  */
#line 593 "Yacc.y"
                                                                                        {(yyval.NODE) = (yyvsp[0].NODE);}
#line 2482 "y.tab.c"
    break;

  case 52: /* expr_without_constants: expr T_plus expr  */
#line 594 "Yacc.y"
                                                                                                        {push("+");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), "+");}
#line 2488 "y.tab.c"
    break;

  case 53: /* expr_without_constants: expr T_minus expr  */
#line 595 "Yacc.y"
                                                                                                        {push("-");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), "-");}
#line 2494 "y.tab.c"
    break;

  case 54: /* expr_without_constants: expr T_divide expr  */
#line 596 "Yacc.y"
                                                                                                {push("/");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), "/");}
#line 2500 "y.tab.c"
    break;

  case 55: /* expr_without_constants: expr T_multiply expr  */
#line 597 "Yacc.y"
                                                                                                {push("*");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), "*");}
#line 2506 "y.tab.c"
    break;

  case 56: /* expr_without_constants: expr T_mod expr  */
#line 598 "Yacc.y"
                                                                                                        {push("%");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), "%");}
#line 2512 "y.tab.c"
    break;

  case 57: /* expr_without_constants: expr T_LogicalAnd expr  */
#line 599 "Yacc.y"
                                                                                                {push("&");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), "&");}
#line 2518 "y.tab.c"
    break;

  case 58: /* expr_without_constants: expr T_LogicalOr expr  */
#line 600 "Yacc.y"
                                                                                                {push("|");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), "|");}
#line 2524 "y.tab.c"
    break;

  case 59: /* expr_without_constants: expr T_less expr  */
#line 601 "Yacc.y"
                                                                                                        {push("<");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), "<");}
#line 2530 "y.tab.c"
    break;

  case 60: /* expr_without_constants: expr T_less_equal expr  */
#line 602 "Yacc.y"
                                                                                                {push("<=");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), "<=");}
#line 2536 "y.tab.c"
    break;

  case 61: /* expr_without_constants: expr T_greater expr  */
#line 603 "Yacc.y"
                                                                                                {push(">");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), ">");}
#line 2542 "y.tab.c"
    break;

  case 62: /* expr_without_constants: expr T_greater_equal expr  */
#line 604 "Yacc.y"
                                                                                                {push(">=");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), ">=");}
#line 2548 "y.tab.c"
    break;

  case 63: /* expr_without_constants: expr T_equal_equal expr  */
#line 605 "Yacc.y"
                                                                                                {push("==");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), "==");}
#line 2554 "y.tab.c"
    break;

  case 64: /* expr_without_constants: expr T_not_equal expr  */
#line 606 "Yacc.y"
                                                                                                {push("!=");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), "!=");}
#line 2560 "y.tab.c"
    break;

  case 65: /* expr: nc  */
#line 610 "Yacc.y"
                                                                                                                {(yyval.NODE) = (yyvsp[0].NODE);}
#line 2566 "y.tab.c"
    break;

  case 66: /* expr: sc  */
#line 611 "Yacc.y"
                                                                                                                {(yyval.NODE) = (yyvsp[0].NODE);}
#line 2572 "y.tab.c"
    break;

  case 67: /* expr: idid  */
#line 612 "Yacc.y"
                                                                                                                {(yyval.NODE) = (yyvsp[0].NODE);}
#line 2578 "y.tab.c"
    break;

  case 68: /* expr: expr T_plus expr  */
#line 613 "Yacc.y"
                                                                                                        {push("+");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), "+");}
#line 2584 "y.tab.c"
    break;

  case 69: /* expr: expr T_minus expr  */
#line 614 "Yacc.y"
                                                                                                        {push("-");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), "-");}
#line 2590 "y.tab.c"
    break;

  case 70: /* expr: expr T_divide expr  */
#line 615 "Yacc.y"
                                                                                                {push("/");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), "/");}
#line 2596 "y.tab.c"
    break;

  case 71: /* expr: expr T_multiply expr  */
#line 616 "Yacc.y"
                                                                                                {push("*");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), "*");}
#line 2602 "y.tab.c"
    break;

  case 72: /* expr: expr T_mod expr  */
#line 617 "Yacc.y"
                                                                                                        {push("%");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), "%");}
#line 2608 "y.tab.c"
    break;

  case 73: /* expr: expr T_LogicalAnd expr  */
#line 618 "Yacc.y"
                                                                                                {push("&");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), "&");}
#line 2614 "y.tab.c"
    break;

  case 74: /* expr: expr T_LogicalOr expr  */
#line 619 "Yacc.y"
                                                                                                {push("|");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), "|");}
#line 2620 "y.tab.c"
    break;

  case 75: /* expr: expr T_less expr  */
#line 620 "Yacc.y"
                                                                                                        {push("<");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), "<");}
#line 2626 "y.tab.c"
    break;

  case 76: /* expr: expr T_less_equal expr  */
#line 621 "Yacc.y"
                                                                                                {push("<=");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), "<=");}
#line 2632 "y.tab.c"
    break;

  case 77: /* expr: expr T_greater expr  */
#line 622 "Yacc.y"
                                                                                                {push(">");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), ">");}
#line 2638 "y.tab.c"
    break;

  case 78: /* expr: expr T_greater_equal expr  */
#line 623 "Yacc.y"
                                                                                                {push(">=");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), ">=");}
#line 2644 "y.tab.c"
    break;

  case 79: /* expr: expr T_equal_equal expr  */
#line 624 "Yacc.y"
                                                                                                {push("==");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), "==");}
#line 2650 "y.tab.c"
    break;

  case 80: /* expr: expr T_not_equal expr  */
#line 625 "Yacc.y"
                                                                                                {push("!=");TAC();(yyval.NODE) = Construct_AST((yyvsp[-2].NODE), (yyvsp[0].NODE), "!=");}
#line 2656 "y.tab.c"
    break;

  case 81: /* expr_or_empty_with_semicolon_and_assignment: expr_or_empty T_Semicolon  */
#line 628 "Yacc.y"
                                                                                        {(yyval.NODE) = (yyvsp[-1].NODE);}
#line 2662 "y.tab.c"
    break;

  case 82: /* expr_or_empty_with_semicolon_and_assignment: Assignment_stmt T_Semicolon  */
#line 629 "Yacc.y"
                                                                                                                                {(yyval.NODE) = (yyvsp[-1].NODE);}
#line 2668 "y.tab.c"
    break;

  case 83: /* expr_or_empty_with_assignment_and_closed_parent: expr_or_empty T_closedParanthesis  */
#line 631 "Yacc.y"
                                                                                                                                        {(yyval.NODE) = (yyvsp[-1].NODE);}
#line 2674 "y.tab.c"
    break;

  case 84: /* expr_or_empty_with_assignment_and_closed_parent: Assignment_stmt T_closedParanthesis  */
#line 632 "Yacc.y"
                                                                                                                                                                                {(yyval.NODE) = (yyvsp[-1].NODE);}
#line 2680 "y.tab.c"
    break;

  case 85: /* idid: T_identifier  */
#line 634 "Yacc.y"
                                                                                                {push((char*)yylval.str);(yyval.NODE) = Construct_AST(NULL, NULL, (char*)yylval.str); }
#line 2686 "y.tab.c"
    break;

  case 86: /* sc: T_stringLiteral  */
#line 636 "Yacc.y"
                                                                                                {push((char*)yylval.str);(yyval.NODE) = Construct_AST(NULL, NULL, (char*)yylval.str); }
#line 2692 "y.tab.c"
    break;

  case 87: /* nc: T_numericConstants  */
#line 638 "Yacc.y"
                                                                                        {push((char*)yylval.str);(yyval.NODE) = Construct_AST(NULL, NULL, (char*)yylval.str); }
#line 2698 "y.tab.c"
    break;

  case 88: /* expr_or_empty: expr  */
#line 641 "Yacc.y"
                                                                                                {(yyval.NODE) = (yyvsp[0].NODE);}
#line 2704 "y.tab.c"
    break;

  case 89: /* expr_or_empty: %empty  */
#line 642 "Yacc.y"
                                  {(yyval.NODE) = Construct_AST(NULL, NULL, ";"); }
#line 2710 "y.tab.c"
    break;

  case 90: /* openflower: T_openFlowerBracket  */
#line 645 "Yacc.y"
                                {}
#line 2716 "y.tab.c"
    break;

  case 91: /* closeflower: T_closedFlowerBracket  */
#line 646 "Yacc.y"
                                   {}
#line 2722 "y.tab.c"
    break;


#line 2726 "y.tab.c"

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 649 "Yacc.y"


void yyerror(const char *str) 
{ 
	printf("Error | Line: %d\n%s\n",yylineno,str);
} 

void symboldisplay()
{
	//printf("Hi");
	//printf("%s",LineBreaker);
	//for (int i = 0;i < stop;i++)
	//{
	//	printf("%s\t",st1[i]);
	//}

	// Display Quads
	printf("%s",LineBreaker);
	//printf("Quadruplets\n");
	for(int i=0;i<quadindex;i++)
    {
        printf("%-8s \t %-8s \t %-8s \t %-6s \n",Q[i].op,Q[i].arg1,Q[i].arg2,Q[i].res);
    }
	printf("%s",LineBreaker);
}

int isDigit(char* in)
{
    int hasDecimal = 0;
    for(int i = 0; i < strlen(in); ++i)
    {
        if(in[i] == '.' && !hasDecimal)
            hasDecimal = 1;
        else if(!isdigit(in[i]))
            return 0;
    }
    return 1;
}


void icg_optimize()
{
    for(int i = 0; i < quadindex; ++i)
    {
        if((strcmp(Q[i].op, "+") == 0 || strcmp(Q[i].op, "-") == 0 || strcmp(Q[i].op, "*") == 0 || strcmp(Q[i].op, "/") == 0
        || strcmp(Q[i].op, "%") == 0 || strcmp(Q[i].op, "&") == 0 || strcmp(Q[i].op, "|") == 0 || strcmp(Q[i].op, "^") == 0)
        && isDigit(Q[i].arg1) && isDigit(Q[i].arg2))
        {
            // Check if either operand contains a decimal point
            int isFloat = (strchr(Q[i].arg1, '.') != NULL || strchr(Q[i].arg2, '.') != NULL);
            
            if(isFloat) {
                double res;
                double arg1 = atof(Q[i].arg1);
                double arg2 = atof(Q[i].arg2);
                
                if(strcmp(Q[i].op, "+") == 0)
                    res = arg1 + arg2;
                else if(strcmp(Q[i].op, "-") == 0)
                    res = arg1 - arg2;
                else if(strcmp(Q[i].op, "*") == 0)
                    res = arg1 * arg2;
                else if(strcmp(Q[i].op, "/") == 0)
                    res = arg1 / arg2;
                else
                    continue; // Skip operations that don't make sense for floats
                
                strcpy(Q[i].op, "=");
                sprintf(Q[i].arg1, "%f", res);
            } else {
                // Original integer code
                int res;
                if(strcmp(Q[i].op, "+") == 0)
                    res = atoi(Q[i].arg1) + atoi(Q[i].arg2);
                else if(strcmp(Q[i].op, "-") == 0)
                    res = atoi(Q[i].arg1) - atoi(Q[i].arg2);
                else if(strcmp(Q[i].op, "*") == 0)
                    res = atoi(Q[i].arg1) * atoi(Q[i].arg2);
                else if(strcmp(Q[i].op, "/") == 0)
                    res = atoi(Q[i].arg1) / atoi(Q[i].arg2);
                else if(strcmp(Q[i].op, "%") == 0)
                    res = atoi(Q[i].arg1) % atoi(Q[i].arg2);
                else if(strcmp(Q[i].op, "&") == 0)
                    res = atoi(Q[i].arg1) & atoi(Q[i].arg2);
                else if(strcmp(Q[i].op, "|") == 0)
                    res = atoi(Q[i].arg1) | atoi(Q[i].arg2);
                else if(strcmp(Q[i].op, "^") == 0)
                    res = atoi(Q[i].arg1) ^ atoi(Q[i].arg2);
                
                strcpy(Q[i].op, "=");
                sprintf(Q[i].arg1, "%d", res);
            }
            
            Q[i].arg2 = NULL;
        }
    }
}


int main()
{
    ast_tree_output = fopen("ast_tree_output.txt", "w");
    if(ast_tree_output == NULL)
    {
        printf("Could not open output file, aborting\n");
        exit(1);
    }
    yyparse();				//parse through the input. This step effectively also fills the symbol table, generates the AST and computes & prints ICG.
    
    printf("\n**************************************Symbol Table****************************************\n");
    
    display();				//display the symbol table. The function is defined in lex.l
    
    printf("\n*************************************************************************************************\n");
    
    printf("Intermediate Code Generation (Quadraple Form):\n");
    symboldisplay();

    icg_optimize();

    printf("After Optimization:\n");
    symboldisplay();
    
    // Add this new functionality to write optimized ICG to file
    FILE *opt_file = fopen("../CodeOpt/input.txt", "w");
    if(opt_file == NULL)
    {
        printf("Error: Could not open CodeOpt/input.txt for writing\n");
    }
    else
    {
        fprintf(opt_file, "Optimized Intermediate Code Generation (Quadruple Form):\n");
        fprintf(opt_file, "_______________________________________________________________________________________________________\n");
        for(int i=0; i<quadindex; i++)
        {
            fprintf(opt_file, "%-8s \t %-8s \t %-8s \t %-6s \n", Q[i].op, Q[i].arg1, Q[i].arg2, Q[i].res);
        }
        fprintf(opt_file, "_______________________________________________________________________________________________________\n");
        fclose(opt_file);
        printf("Optimized ICG written to CodeOpt/input.txt\n");
    }
    
    fclose(ast_tree_output);
    return 0;
}
