//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 3 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void moveOddItemsToBack(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all odd integers to the back of the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveOddItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving odd integers to the back of the linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void moveOddItemsToBack(LinkedList *ll)
{
	if (ll == NULL || ll->head == NULL || ll->size < 2) {
		return;
	}

	LinkedList oddLL;
	LinkedList evenLL;

	oddLL.head = NULL;
	oddLL.size = 0;
	evenLL.head = NULL;
	evenLL.size = 0;
	
	ListNode *curNode;
	curNode = ll->head;
	ListNode *oddLLLastNode;
	ListNode *evenLLLastNode;

	while (curNode != NULL) {
		if (curNode->item <= 0) {
			return;
		}
		if (curNode->item%2 != 0) {
			if (oddLL.head == NULL) {
				oddLL.head = curNode;
				oddLLLastNode = curNode;
			} else {
				oddLLLastNode->next = curNode;
				oddLLLastNode = curNode;
			}
		} else {
			if (evenLL.head == NULL) {
				evenLL.head = curNode;
				evenLLLastNode = curNode;
			} else {
				evenLLLastNode->next = curNode;
				evenLLLastNode = curNode;
			}
		}
		curNode = curNode->next;
	}
	ll->head = evenLL.head;
	evenLLLastNode->next = oddLL.head;
	return;
}

/*
// 제미나이의 코드 리뷰
void moveOddItemsToBack(LinkedList *ll)
{
    // 리스트가 비어있거나 노드가 하나뿐이면 처리할 필요 없음
    if (ll == NULL || ll->head == NULL || ll->size < 2) {
        return;
    }

    ListNode *evenHead = NULL, *evenTail = NULL;
    ListNode *oddHead = NULL, *oddTail = NULL;
    ListNode *cur = ll->head;

    while (cur != NULL) {
        if (cur->item % 2 == 0) { // 짝수일 때
            if (evenHead == NULL) {
                evenHead = evenTail = cur;
            } else {
                evenTail->next = cur;
                evenTail = cur;
            }
        } else { // 홀수일 때
            if (oddHead == NULL) {
                oddHead = oddTail = cur;
            } else {
                oddTail->next = cur;
                oddTail = cur;
            }
        }
        cur = cur->next;
    }

    // 짝수 노드가 하나라도 있다면
    if (evenHead != NULL) {
        ll->head = evenHead;
        evenTail->next = oddHead; // 짝수 뒤에 홀수 연결 (oddHead가 NULL이어도 상관없음)
    } else {
        // 짝수가 하나도 없다면 전체가 홀수이므로 홀수 헤드를 지정
        ll->head = oddHead;
    }

    // ★중요: 홀수 리스트의 마지막 노드는 반드시 NULL을 가리켜야 함
    if (oddTail != NULL) {
        oddTail->next = NULL;
    }
}
*/

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
