#include<stdio.h>
#include<stdlib.h>



typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

int initialize(headNode** h);

int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);

}


int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;
    printf("2018038016 이상호");
    
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
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
			initialize(&headnode);
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


int initialize(headNode** h) {
	
    if(*h != NULL) // head를 가리키는 주소가 있으면  
	      freeList(*h); // 할당된 메모리 모두 해제 
	
	*h = (headNode*)malloc(sizeof(headNode));	// 헤드노드 동적할당	 
	(**h).first=NULL; //headnode 초기화 
			  
	return 1;
}

int freeList(headNode* h){ // listnode 메모리 해제 함수 (headnode도 해제) 
	
	listNode *now = h -> first; //헤드 노드가 가리키는 곳을 now가 가리키게 
	
	if(!now) //리스트에 노드가 한개도 없을때 
	{
		free(now); //헤드 노드만 동적할당 반납 
		return 0; 
	}
	
	while(now->rlink != NULL){
		    now = now->rlink; // p가 다음노드를 가리키게
			free(now->llink); // 이전 노드들 해제 
	}
	
	free(now);
	free(h); //  headnode 해제 
	 
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}



int insertLast(headNode* h, int key) {
	
    listNode* node = (listNode*)malloc(sizeof(listNode)); //새로 삽입할 노드를 동적할당한다
	node->llink = NULL; //새로 생성한 노드에 널 포인터로 초기화하고 키 값을 넣는다.
	node->rlink = NULL;
	node->key = key;
	listNode* p = h->first; //움직일 포인터를 초기화 
	
	if(p == NULL) // 해드 포인터가 가리키는 리스트가 없다면 , 즉 노드가 없다면
	{
		h->first = node; //새로 삽입할 노드를 가장 첫 노드로 셋팅
	}
	else //노드가 하나이상 있을 경우
	{
		while(p->rlink != NULL) //마지막 노드에 도달할 때까지
		{
			p = p->rlink; //포인터를 이동시켜준다
		}
		p->rlink = node; //마지막 노드에 도달 시, 새로 삽입할 노드와 연결해준다.
		node->llink = p;
	}

	return 0;
}


int deleteLast(headNode* h) { // 제일 마지막의 노드를 삭제한다 
	
    listNode* now = h->first;	// 접근할 노드 생성	
    int cnt=0;
									
	if (h == NULL) {					// head 즉, 초기화된 리스트 존재하지 않으면 
		printf(">>> 리스트가 초기화 되지 않았습니다. <<<\n");
		return -1;		//비정상 종료 
	}
	
	if (h->first == NULL) {				//초기화된 리스트에 노드가 존재하지 않으면 
		printf(">>> 리스트에 노드가 어느 노드도 없습니다. <<<\n");
		return -1;		//비정상 종료 
	}
	
	else //노드가 하나이상 있을 때
	{
		while(now->rlink != NULL) //가장 마지막 노드에 도달할때까지
		{
			cnt++;
			now = now->rlink;
		}

		if(cnt != 0) //노드가 2개이상 있을 때
		{
			(now->llink)->rlink=NULL;
		}
		else //노드가 1개일 때
		{
			h->first = NULL;
		}
	}
	free(now); //동적할당 해제

	return 0;		//정상 종료 표현 

}



int insertFirst(headNode* h, int key) { //list처음에 key에 대한 노드를 추가 
	
	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로 삽입할 노드를 동적할당
	listNode* p = h->first;
	
	if(p == NULL) //리스트가 비어있을 때
	{
		h->first = node; //노드의 시작을 새로삽입한 노드로 변경
		node->llink = node->rlink = NULL;
	}
	
	node->key=key;
	
	if(p == NULL) //리스트가 비어있을 때
	{
		h->first = node; //노드의 시작을 새로삽입한 노드로 변경
	}
	else //노드가 하나이상 있을 때
	{
		h->first = node; //양방향으로 노드를 링크해준다.
		node->rlink = p;
		p->llink = node;
	}

	return 0;
	
}


int deleteFirst(headNode* h) {

	return 0;
}



int invertList(headNode* h) {
	
    listNode* now=NULL;
    listNode* tail;
	listNode* mid=NULL;
	
	if(h->first == NULL) //리스트에 노드가 하나도 없을 때
	{
		printf("리스트에 노드가 없습니다.\n");
		return 0;
	} 
	
	now= h->first;
	
	for(;now!=NULL;){  // 리스트를 벗어날때 까지 
		tail = mid;						//연결될 노드의 위치 저장
		mid = now;						//연결해야하는 노드의 위치 저장
		now = now->rlink;				//링크 변경 전 다음 노드의 위치 저장
		mid->rlink = tail;				//기존의 오른쪽 링크를 왼쪽 링크가 가리키는 쪽으로 연결
		mid->llink = now;				//기존의 왼쪽 링크를 오른쪽 링크가 가리키는 쪽으로 연결
	}
	
	h->first=mid; //헤드 포인터가 역순이된 리스트의 제일  첫번째 노드를 가리키게 
    
	return 0;
}

int insertNode(headNode* h, int key) {

	return 0;
}


int deleteNode(headNode* h, int key) {

	return 1;
}

