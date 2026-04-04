//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 2 */

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
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll1, ll2;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll1.head = NULL;
	ll1.size = 0;

	//Initialize the linked list 2 as an empty linked list
	ll2.head = NULL;
	ll2.size = 0;

	printf("1: Insert an integer to the linked list 1:\n");
	printf("2: Insert an integer to the linked list 2:\n");
	printf("3: Create the alternate merged linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list 1: ");
			scanf("%d", &i);
			j = insertNode(&ll1, ll1.size, i);
			printf("Linked list 1: ");
			printList(&ll1);
			break;
		case 2:
			printf("Input an integer that you want to add to the linked list 2: ");
			scanf("%d", &i);
			j = insertNode(&ll2, ll2.size, i);
			printf("Linked list 2: ");
			printList(&ll2);
			break;
		case 3:
		    printf("The resulting linked lists after merging the given linked list are:\n");
			alternateMergeLinkedList(&ll1, &ll2); // You need to code this function
			printf("The resulting linked list 1: ");
			printList(&ll1);
			printf("The resulting linked list 2: ");
			printList(&ll2);
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		case 0:
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
{
    /* add your code here */
	if (ll1->head == NULL || ll2->head == NULL) {
		return;
	}
	ListNode *curOne = ll1->head;
	ListNode *curTwo = ll2->head;

	while (curOne != NULL || curTwo != NULL) {
			// ll2에서 가져 올 노드와 ll2의 분리. 다음 노드를 가지고 있는지 없는지에 따라 ll2 head의 값이 바뀐다
			if (curTwo->next == NULL) {
				ll2->head = NULL;
				ll2->size--;
			} else {
				ll2->head = curTwo->next;
				ll2->size--;
			}
			// ll1에서 현재 가리키고 있는 노드와 그 노드의 다음 노드 사이에 ll2에서 가져 온 노드를 끼워 넣는다.
			// ll1에 사이공간이 더 있는지 확인한다.
			if (curOne->next == NULL) {
				curOne->next = curTwo;
				curTwo->next = NULL;
				ll1->size++;
				break;	
			} 
			else {
				curTwo->next = curOne->next;
				curOne->next = curTwo;
				ll1->size++;	
				// curOne과 curTwo 업데이트
				//// 더 끼워넣을 노드가 남아 있는지 확인한다.
				if (ll2->head == NULL) {
					break;
				//// 더 끼워넣을 노드가 남아 있다면 포인터의 위치를 업데이트 한다.
				} else {
					curOne = curTwo->next;
					curTwo = ll2->head;
				}
			}

	}
	return;
}

/*
// 제미나이에게 코드 리뷰 부탁했을 때 써 준 코드
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
{
    // 한쪽이라도 비어있으면 작업할 게 없음
    if (ll1->head == NULL || ll2->head == NULL) {
        return;
    }

    ListNode *cur1 = ll1->head;
    ListNode *cur2 = ll2->head;
    ListNode *next1, *next2;

    // 두 리스트 모두 노드가 있을 때까지만 반복
    while (cur1 != NULL && cur2 != NULL) {
        // 1. 다음 노드들 미리 백업 (길을 잃지 않기 위해)
        next1 = cur1->next;
        next2 = cur2->next;

        // 2. cur1 뒤에 cur2를 연결
        cur1->next = cur2;
        ll1->size++;
        ll2->size--;

        // 3. cur2의 다음을 어떻게 처리할지 결정
        if (next1 == NULL) {
            // ll1이 여기서 끝난다면, cur2를 ll1의 진짜 마지막으로 만듦
            cur2->next = NULL;
            ll2->head = next2; // ll2의 새로운 시작점 설정
            break;
        } else {
            // ll1에 노드가 더 있다면, cur2 뒤에 원래 ll1의 다음 노드를 연결
            cur2->next = next1;
			ll2->head = next2; // ll2의 새로운 시작점 설정
        }

        // 4. 다음 쌍으로 이동
        cur1 = next1;
        cur2 = next2;
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
