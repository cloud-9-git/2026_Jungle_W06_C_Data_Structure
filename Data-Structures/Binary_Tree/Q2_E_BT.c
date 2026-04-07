//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section E - Binary Trees Questions
Purpose: Implementing the required functions for Question 2 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////
typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

/////////////////////////////////////////////////////////////////////////////////

typedef struct _stackNode{
    BTNode *btnode;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
    StackNode *top;
}Stack;

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int maxHeight(BTNode *node);

BTNode *createBTNode(int item);

BTNode *createTree();
void push( Stack *stk, BTNode *node);
BTNode* pop(Stack *stk);

void printTree(BTNode *node);
void removeAll(BTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    int c;
    char e;
	c = 1;

    BTNode *root;
    root = NULL;

    printf("1: Create a binary tree.\n");
    printf("2: Find the maximum height of the binary tree.\n");
    printf("0: Quit;\n");

    while(c != 0){
        printf("\nPlease input your choice(1/2/0): ");
        if(scanf("%d", &c) > 0)
        {
            switch(c)
            {
            case 1:
                removeAll(&root);
                root = createTree();
                printf("The resulting binary tree is: ");
                printTree(root);
                printf("\n");
                break;
            case 2:
                c = maxHeight(root);
                printf("The maximum height of the binary tree is: %d\n",c);
                removeAll(&root);
                break;
            case 0:
                removeAll(&root);
                break;
            default:
                printf("Choice unknown;\n");
                break;
            }
		}
        else
        {
            scanf("%c",&e);
        }

    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int maxHeight(BTNode *node)
{
    if (node == NULL || node->item == NULL) {
        return -1;
    } 
    if (node->left == NULL && node->right == NULL) {
        return 0;
    }
    if (node->left || node->right) {
        int max = maxHeight(node->left);
        if (maxHeight(node->right) > max) max = maxHeight(node->right);
        return (max + 1);
    }
}

/*
// 제미나이의 코드 리뷰 내용
① int와 NULL의 혼동
C
if (node == NULL || node->item == NULL) // 이 부분!
node->item은 int 타입이죠? C언어에서 NULL은 보통 0으로 정의되어 있습니다.

만약 사용자가 노드에 숫자 0을 입력하면, 코드는 "값이 없네?"라고 오해하고 -1을 반환할 수 있습니다.

포인터(node)가 NULL인지만 체크하는 것이 더 정확합니다.

② "두 번 물어보기" (효율성 문제)
지금 코드에서 가장 눈에 띄는 부분은 이 대목이에요.

C
int max = maxHeight(node->left); // 1번 호출
if (maxHeight(node->right) > max) // 2번 호출
    max = maxHeight(node->right); // 3번 호출 (조건이 맞으면 또 호출!)
재귀 함수에서 같은 함수를 여러 번 호출하면, 트리가 커질수록 컴퓨터가 했던 계산을 수만 번 반복하게 됩니다. (이걸 지수적 시간 복잡도라고 해요.)

팁: 오른쪽 자식의 높이도 변수(int rightMax)에 딱 한 번만 저장해두고 비교하면 컴퓨터가 훨씬 고마워할 거예요!

3️⃣ 한 걸음 더 나아가기 (Scope 활용)
아까 우리가 얘기했던 Scope(범위) 기억나시죠?
maxHeight 안에서 왼쪽 높이와 오른쪽 높이를 저장할 변수를 if 문 근처에서 선언해 보세요. 그러면 함수가 끝날 때 깔끔하게 사라지면서 메모리도 아끼고, 계산 속도는 훨씬 빨라질 겁니다.

// 제미나이가 수정한 코드
int maxHeight(BTNode *node)
{
    // 1. 기저 조건: 노드가 없으면 높이는 -1 (자식 노드에서 0을 만들기 위함)
    if (node == NULL) {
        return -1;
    }

    // 2. 왼쪽과 오른쪽의 높이를 '딱 한 번씩만' 물어보고 변수에 저장 (Scope 활용!)
    int leftHeight = maxHeight(node->left);
    int rightHeight = maxHeight(node->right);

    // 3. 둘 중 더 큰 값에 나 자신(1)을 더해서 반환
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    } else {
        return rightHeight + 1;
    }
}

// 더 줄인 버전
int maxHeight(BTNode *node) {
    if (node == NULL) return -1;
    int l = maxHeight(node->left);
    int r = maxHeight(node->right);
    return (l > r ? l : r) + 1; // 삼항 연산자: (조건 ? 참일때 : 거짓일때)
}
*/

///////////////////////////////////////////////////////////////////////////////////

BTNode *createBTNode(int item){
    BTNode *newNode = malloc(sizeof(BTNode));
    newNode->item = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


//////////////////////////////////////////////////////////////////////////////////

BTNode *createTree()
{
    Stack stk;
    BTNode *root, *temp;
    char s;
    int item;

    stk.top = NULL;
    root = NULL;

    printf("Input an integer that you want to add to the binary tree. Any Alpha value will be treated as NULL.\n");
    printf("Enter an integer value for the root: ");
    if(scanf("%d",&item) > 0)
    {
        root = createBTNode(item);
        push(&stk,root);
    }
    else
    {
        scanf("%c",&s);
    }

    while((temp =pop(&stk)) != NULL)
    {

        printf("Enter an integer value for the Left child of %d: ", temp->item);

        if(scanf("%d",&item)> 0)
        {
            temp->left = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        printf("Enter an integer value for the Right child of %d: ", temp->item);
        if(scanf("%d",&item)>0)
        {
            temp->right = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        if(temp->right != NULL)
            push(&stk,temp->right);
        if(temp->left != NULL)
            push(&stk,temp->left);
    }
    return root;
}

void push( Stack *stk, BTNode *node){
    StackNode *temp;

    temp = malloc(sizeof(StackNode));
    if(temp == NULL)
        return;
    temp->btnode = node;
    if(stk->top == NULL){
        stk->top = temp;
        temp->next = NULL;
    }
    else{
        temp->next = stk->top;
        stk->top = temp;
    }
}

BTNode* pop(Stack *stk){
   StackNode *temp, *top;
   BTNode *ptr;
   ptr = NULL;

   top = stk->top;
   if(top != NULL){
        temp = top->next;
        ptr = top->btnode;

        stk->top = temp;
        free(top);
        top = NULL;
   }
   return ptr;
}

void printTree(BTNode *node){
    if(node == NULL) return;

    printTree(node->left);
    printf("%d ",node->item);
    printTree(node->right);
}

void removeAll(BTNode **node){
    if(*node != NULL){
        removeAll(&((*node)->left));
        removeAll(&((*node)->right));
        free(*node);
        *node = NULL;
    }
}
