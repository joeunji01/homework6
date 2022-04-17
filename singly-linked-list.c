/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	printf("[----- [조은지]  [2021076020] -----]");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h); //헤드노드 초기화

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; 

	listNode* prev = NULL;
	while(p != NULL) { //헤드노드가 존재
		prev = p; //prev= 첫번째 노드
		p = p->link; //p는 p 다음 노드를 가리킴
		free(prev); //prev 메모리 해제
	}
	free(h); //헤드노드 메모리 해제
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	//listNode 동적 메모리 할당
	node->key = key; 

	node->link = h->first; //node의 link가 헤드노드를 가리킴
	h->first = node; //헤드노드가 node를 가리킴

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	//삽입할 새로운 노드 메모리 할당
	listNode *node = (listNode*)malloc(sizeof(listNode)); 
	node->key=key; //key 값 저장
	node->link=NULL; 

	if(h->first==NULL){ //헤드노드가 가리키는게 없음 = 생성된 노드X
		h->first=node; //node가 첫번째 노드가 됨
		return 0;
	}

	listNode *n=h->first; //n은 첫번째 노드를 가리킴
	listNode *trail =h->first; //trail은 첫번째 노드를 가리킴

	while (n!=NULL){ //n이 가리키는 노드가 있음
		if (n->key>=key){ //삽입할 key 값이 n의 key 값보다 작음
			if(n==h->first){ //n=이 첫번째 노드라면
				h->first=node; //헤드노드가 새로운 node를 가리킴
				node->link=n; //새로운 node의 link는 n을 가리킴
			}
			else{ //n이 첫번째 노드가 아님
				node->link=n; //새로운 node의 link는 n을 가리킴
				trail->link=node; //trail의 link는 새로운 node를 가리킴
			}
			return 0;
		}
		trail=n; 
		n=n->link; //n이 n 다음 노드를 가리킴

		// 마지막 노드까지 key보다 큰 값이 없을 때
		
	}
	trail->link=node; //trail의 link가 새로운 node를 가리킴
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	//삽입할 새로운 노드 메모리 할당
	listNode *node =(listNode*)malloc(sizeof(listNode));
	node->key=key; //key 값 저장
	node->link=NULL;

	if (h->first ==NULL){ //헤드노드가 가리키는게 없다면
		h->first=node; //새로운 node를 가리킴
		return 0;
	}
	
	listNode *n=h->first; //h->first= 첫번째 노드, n은 첫번째 노드를 가리킴

	while(n->link!=NULL) //n의 link가 가리키고 있음
		n=n->link; //n은 그 다음 노드가 됨

	n->link =node; //n의 link는 새로운 node를 가리킴
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	if(h->first==NULL){ //첫번째 노드가 없음
		printf("nothing to delete.\n"); 
		return 0;
		}
	listNode* n=h->first; //*n =첫번째 노드
	
	h->first=n->link; // 첫번째 노드 -> n 다음의 노드로 바뀜
	free(n); //노드 n 메모리 할당 해제

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first ==NULL){ //노드가 없음
		printf("nothing to delete");
		return 0;
	}
	listNode* n= h->first; //n이 첫번째 노드를 가리킴
	listNode* trail=NULL; 

	while(n!=NULL) {
		if(n->key==key) { //삭제할 노드의 key 값을 갖고있는 노드
			if (n==h->first) //n이 첫번째 노드
				h->first=n->link; //헤드노드가 n 다음의 노드를 가리킴
			else
				trail->link=n->link; //trail의 link가 n 다음의 노드를 가리킴
			free(n); //n 메모리 할당 해제
			return 0;
		}

		trail=n; //trail은 n을 가리킴
		n=n->link; //n은 다음 노드가 됨
	}

	printf("cannot find the node for key = %d\n",key);
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) { //헤드노드가 가리키고 있지 않음 =첫번째 노드 없음
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; //n은 첫번째 노드를 가리킴
	listNode* trail = NULL; 

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) { //첫번째 노드의 link가 가리키고 있지 않음
		h->first = NULL; //헤드노드를 아무것도 가리키지 않게
		free(n); //n(첫번째 노드였던)을 메모리 할당 해제
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) { //노드 n이 다음 노드로 연결되어 있음
		trail = n; //삭제할 노드를 n
		n = n->link;
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL;
	free(n);

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	if(h->first == NULL) { //헤드노드가 가리키는게 없음
		printf("nothing to invert...\n"); 
		return 0;
	}
	listNode *n = h->first; //n이 첫번째 노드를 가리킴
	listNode *trail = NULL; 
	listNode *middle = NULL;

	while(n != NULL){ //n이 가리키는게 있는 동안 ->n이 마지막 노드까지
		trail = middle; 
		middle = n; //middle이 n이 가리키던 노드를 가리킴
		n = n->link; //n -> 그 다음 노드를 가리킴
		middle->link = trail; //middle->link =trail (전 순서 노드를 가리킴)
	}
	//역순으로 뒤에있는 노드부터 link를 가리킴 
		h->first = middle; //헤드노드가 middle 가리킴

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { //헤드노드가 없음
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //p는 첫번째 노드를 가리킴

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link; //p가 다음 노드를 가리킴
		i++;
	}

	printf("  items = %d\n", i);
}

