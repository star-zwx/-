#include <stdio.h>
#include<stdlib.h>

typedef char TElemType;
//树结构
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

//栈结构
typedef struct Stack
{
    BiTree  date;
    int stacksize;  //记录元素个数
    struct Stack *next;
    struct Stack *base;  //栈底指针
    struct Stack *top;  //栈顶指针
}Stack;


//栈初始化
void InitStack(Stack *s)
{
    s->stacksize=0;
    s->base=NULL;
    s->top=s->base;
}

//插入数据
void Push(Stack *s,BiTree T)
{
        Stack *p;
        p=(Stack *)malloc(sizeof(Stack));
        if(!p)
            exit(0);
        p->date=T;
        if(s->stacksize==0)  //当插入第一个元素时，指针的变化
        {
            s->base=p;    //赋给栈底指针
            s->top=p;
            p->next=NULL;
        }
        else
        {
            p->next=s->top;
            s->top=p;

        }
        s->stacksize++;
}


//删除并返回栈顶元素
BiTree Pop(Stack *s)
{
    BiTree t;
    Stack *p;
    p=s->top;
    t=p->date;
    s->top=p->next;
    free(p);
    s->stacksize--;
    return t;
}

/*构建二叉树*/
void CreateBiTree(BiTree *T)
{
    TElemType e;

    if ((e=getchar()) == '#')
    {
        *T = NULL;
    }
    else
    {
        *T = (BiTree) malloc(sizeof(BiTNode));
        if (!T)
        {
            exit(0);
        }
        (*T)->data = e;
        CreateBiTree(&(*T)->lchild);    //创建左子树
        CreateBiTree(&(*T)->rchild);    //创建右子树
    }
}

//中序遍历(非递归)
void InorderTraverse(BiTree T,Stack *s)
{
    BiTree P=T;
    while(P||s->stacksize!=0)
    {
        if(P)
        {
            Push(s, P);
            P=P->lchild;
        }
        else
        {
            P=Pop(s);
            printf("%c ",P->data);
            P=P->rchild;
        }
    }
}

//先序遍历(非递归)
void preOrderTraverse(BiTree T,Stack *s)
{
    BiTree p=T;
    while(p||s->stacksize!=0)
    {
        if(p)
        {
            printf("%c ",p->data);
            Push(s, p);
            p=p->lchild;
        }
        else
        {
            p=Pop(s);
            p=p->rchild;
        }
    }
}

//后序遍历
void PostOrderTraverse(BiTree T,Stack *s1,Stack *s2)
{
    BiTree p=T;
    while(p||s1->stacksize!=0)
    {
        if(p)
        {
            Push(s1,p);
            Push(s2,p);
            p=p->rchild;
        }
        else
        {
            p=Pop(s1);
            p=p->lchild;
        }
    }
    while(s2->stacksize!=0)
    {
        p=Pop(s2);
        printf("%c ",p->data);
    }
}

int main()
{
    printf("请输入二叉树，#代表空树：\n");
    BiTree T;
    Stack stack1,stack2,*p1,*p;
    p=&stack1;p1=&stack2;
    InitStack(p);
    InitStack(p1);
    CreateBiTree(&T);
    printf("前序遍历结果为：");
    preOrderTraverse(T, p);
    printf("\n");
    printf("中序遍历结果为：");
    InorderTraverse(T, p);
    printf("\n");
    printf("后序遍历结果为：");
    PostOrderTraverse(T, p,p1);
    printf("\n");
    return 0;
}
/* 测试
ABD##E##CF##G##
前序遍历结果为：A B D E C F G
中序遍历结果为：D B E A F C G
后序遍历结果为：D E B F G C A
Program ended with exit code: 0
*/
