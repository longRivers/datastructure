/*
*将中缀表达式转换成后缀表达式 stack实现 桟通过链表实现
*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#ifndef _stack_h
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;
typedef char ElementType;

int IsEmpty( Stack S );
Stack CreateStack( void );
void DisposeStack( Stack S );
void MakeEmpety( Stack S );
void Push( ElementType X, Stack S);
ElementType Top( Stack S );
void Pop( Stack S );
int IsSameBracket(char a, char b);/*判断括号种类是否相同*/

#endif /* _stack_h */

struct Node {
  ElementType Element;
  PtrToNode Next;
};

int IsEmpty( Stack S) {
  return S->Next == NULL;
}

Stack CreateStack(void) {
  Stack S;
  S = (struct Node *)malloc( sizeof( struct Node));
  if(S == NULL){
    printf("out of space");
  }
  S->Next = NULL;
  MakeEmpety(S);
  return S;
}

int SameBracket(char a, char b)
{
	if(a == ')' && b == '(')
		return 1;
	if(a == '[' && b == ']')
		return 1;
	if(a == '{' && b == '}')
		return 1;
	return 0;
}
void MakeEmpety(Stack S) {
  if(S == NULL){
    printf("Must use CreateStack first");
  }
  else
    while( !IsEmpty( S ) )
      Pop( S );
}

void Push( ElementType X,Stack S ) {
  PtrToNode TmpCell;
  // 强制类型转换 将malloc 的 void 转换成 struct Node *
  TmpCell = (struct Node *)malloc(sizeof ( struct Node ) );
  if( TmpCell == NULL)
  {
    printf( "out of space!!!");
  }
  else
  {
    TmpCell->Element = X;
    TmpCell->Next = S->Next;
    S->Next = TmpCell;
  }
}

ElementType Top( Stack S ){/*取得栈顶的元素*/
  if( !IsEmpty( S ))
  {
    return S->Next->Element;
  }
  printf( "Empty stack");
  return 0; /* return value used to avoid warning */
}
void Pop( Stack S)
{
  PtrToNode FirstCell;

  if(IsEmpty(S))
  {
    printf( "Empty stack");
  }
  else
  {
      FirstCell = S->Next;
      S->Next = S->Next->Next;
      free( FirstCell);
  }
}

int main(){
  char exp[20];
  scanf("%s", exp);
  int j = 0;
 /* for(j = 0;exp[j]!='\0';j++)
  printf("%c\n",exp[j]);
  getchar();*/
  Stack S = CreateStack();
  char tmp;
  int i = 0;
  while(exp[i] != '\0'){
    if(exp[i]=='(' || exp[i]=='[' || exp[i]=='{')/*该字符为左括号*/
    {
      Push(exp[i], S);
    }
    else if(exp[i]==')' || exp[i]==']' || exp[i]=='}')//该字符为右括号
    {
      if(!IsEmpty(S))
      {
        tmp = Top( S );
        while (!(tmp == '(' || tmp == '[' || tmp == '{'))
        {

          printf("%c ", tmp);
          Pop( S );
          tmp = Top(S);
        }
        if(!IsEmpty(S) && IsSameBracket(exp[i], tmp))/*S不为空且括号种类匹配*/
        {
          Pop(S);
        }
        else{
          printf("GRAMMER ERROR");
          exit(0);
        }

      }
    }
    else if(exp[i]=='+')
    {
      while(!IsEmpty(S)&&!(Top(S) == '(' || Top(S) == '[' || Top(S) == '{')){
        printf("%c ",Top(S));
        Pop(S);
      }
      Push( exp[i], S);
    }
    else if(exp[i] == '-')
    {
      if(IsEmpty(S) || (Top(S) == '(' || Top(S) == '[' || Top(S) == '{'))
      {
        printf("%c ",exp[i]);
      }
      else
      {
        while(!IsEmpty(S)&&!(Top(S) == '(' || Top(S) == '[' || Top(S) == '{')){
          printf("%c ",Top(S));
          Pop(S);
        }
        Push( exp[i], S);
      }
    }
    else if(exp[i] == '*' || exp[i] == '\\')/*转义字符 除号\*/
    {
      while(!IsEmpty(S) && (Top(S)== '*' || Top(S) == '\\')){
        printf("%c ",Top(S));
        Pop(S);
      }
      Push(exp[i], S);
    }
    else{
      printf("%c ",exp[i]);
    }
	i++;//循环变量 i
  }
  if(!IsEmpty(S)){
    if(Top(S) == '(' || Top(S) == '[' || Top(S) == '{')
    {
      printf("grammer error");
      exit(0);
    }
    printf("%c ", Top(S));
    Pop(S);
  }


  return 0;
}
