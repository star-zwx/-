#include<stdio.h>
#include<stdlib.h>
#define MAX 1000
typedef struct node//结点
{
	char info;
	struct node* lchild;
	struct node* rchild;
}tree;
typedef struct stack_1//顺序栈
{
	tree* a[MAX];//用来存树的每一个结点
	int tag[MAX];//起标记作用，用于非递归建树和非递归后序遍历
	int top;//始终指向当前栈中元素的下一个位置，下标从零开始
}stack;
void push(stack* st, tree* t)//入栈
{
	st->a[st->top] = t;
	st->top++;
}
tree* pop(stack* st)//出栈，即删除栈顶元素，并返回指向已删除元素的指针
{
	if (st->top != 0)
	{
		st->top--;
		return st->a[st->top];
	}
	else
		return NULL;
}
tree* top(stack* st)//取栈顶元素，但不删除，返回指向栈顶元素的指针。
{
	if (st->top != 0)
	{
		return st->a[st->top - 1];
	}
	else
	{
		return NULL;
	}
}
tree *create()//非递归建树
{
	//0---左孩子为空，1---右孩子为空，2建树完成，“#”代表空；
	stack A;
	stack *st;
	st = &A;
	tree *root;//树的跟节点
	tree *p1, *p2;//因为跟节点不能动，所有用两个移动指针，用来建树，
	int i = 0;//访问ch数组
	char ch[MAX];//存放结点的info值的字符数组。
	scanf("%s", ch, MAX);
	st->top = 0;//栈初始化
	while (ch[i] != '\0')
	{
		if (i == 0)//建立根节点
		{
			root = (tree*)malloc(sizeof(tree));//建立跟节点
			root->info = ch[i];
			root->lchild = NULL;//左右孩子都置空；
			root->rchild = NULL;
			p1 = root;//p1代替root操作，因为root不能移动。
			push(st, p1);//入栈
			st->tag[st->top - 1] = 0;//将他标记为0---左孩子为空，当然右孩子也为空，但是用不着标记，
			//因为是按照前序遍历的顺序来建树，即：根节点-左子树-右子树。先建左树

		}
		else//非根节点
		{
			if (ch[i] != '#'&&st->tag[st->top - 1] == 0)//建左树(元素非空，即输入不是“#”，并且他的标记是0)；
			{
				p2 = (tree*)malloc(sizeof(tree));//创建一个新结点
				p2->info = ch[i];
				p2->lchild = NULL;//一定要有，不然会和下面的代码冲突，可以看做是对这个结点的初始化；
				p2->rchild = NULL;
				push(st, p2);//入栈
				p1->lchild = p2;//将新创建的左孩子连接的树上
				p1 = p2;//指针下移，即：指针指向现在的左孩子。
				st->tag[st->top - 1] = 0;//标记为0，表示此节点没有左孩子
			}
			else if (ch[i] == '#'&&st->tag[st->top - 1] == 0)//左树完成
			{
				p1->lchild = NULL;
				st->tag[st->top - 1] = 1;//左子树构建完成
			}
			else if (ch[i] == '#'&&st->tag[st->top - 1] == 1)//右树完成
			{
				p1->rchild = NULL;
				st->tag[st->top - 1] = 2;//右子树构建完成，即：这课小树构建完成;
			}
			else if (ch[i] != '#'&&st->tag[st->top - 1] == 1)//建右树
			{
				p2 = (tree*)malloc(sizeof(tree));
				p2->info = ch[i];
				p2->lchild = NULL;
				p2->rchild = NULL;
				push(st, p2);
				p1->rchild = p2;
				p1 = p2;
				st->tag[st->top - 1] = 0;
			}
			while (st->tag[st->top - 1] == 2)//是否出栈操作，当左右子树都已建立时，出栈
			{
				st->tag[st->top - 1] = 0;//出栈之后，清除标记
				p1 = pop(st);//出栈

				if (st->top != 0)//避免最后一个节点误操作，如果没有此句，会导致栈的top越界
					p1 = top(st);//取当前的栈顶元素
				else
					break;//所有元素均已出栈，当前的栈为空
				if (st->tag[st->top - 1] == 1)//说明此时结点的左子树已存在，并且当前指针是从下一右子树返上来的结点，即：右子树也存在；
				{
					st->tag[st->top - 1] = 2;
				}
			}
			if (p1->lchild != NULL || st->tag[st->top - 1] ==1)//对返上来的结点进行判断，有左子树则改变标记为1
			{
				st->tag[st->top - 1] = 1;
			}

		}
		i++;//输入下一个元素
	}
	return root;

}
void preprint(tree* t)//递归前序输出
{
	tree* p1;
	p1 = t;
	if (!p1)
		return;
	else
	{
		printf("%c->", p1->info);
		preprint(p1->lchild);
		preprint(p1->rchild);

	}
}
void inorprint(tree* t)
{
	tree* p1;
	p1 = t;
	if (!p1)
		return;
	else
	{
		inorprint(p1->lchild);
		printf("%c->", p1->info);
		inorprint(p1->rchild);

	}
}
int main()
{
	tree* root;
	printf("输入一组数据(以#分隔):\n");
	root = create();
	printf("前序遍历：");
	preprint(root);
	printf("\n");
	printf("后序遍历：");
	inorprint(root);
	printf("\n");
	return 0;
}
