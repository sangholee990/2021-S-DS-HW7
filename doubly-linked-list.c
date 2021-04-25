#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {   //doubly linked list의 노드 구성 구조체 정의 0
	int key;           //데이터 필드 
	struct Node* llink; //왼쪽 링크 
	struct Node* rlink; //오른쪽 링크 
} listNode; 



typedef struct Head { //doubly linked list에서 헤드를 가리킬 구조체정의 
	struct Node* first; // head node를 가리킬 구조체 포인터 변수 
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */

int initialize(headNode** h); // 리스트 초기화 함수  
int freeList(headNode* h); // 메모리 해제시키는 함수 
int insertNode(headNode* h, int key); // 입력받은키보다 큰노드 앞에 노드를 삽입하는 함수 
int insertLast(headNode* h, int key); //리스트의 마지막에 삽입하는 함수 
int insertFirst(headNode* h, int key); // 리스트의 맨 처음에 삽입하는 함수 
int deleteNode(headNode* h, int key); // 입력받은 키를 삭제하는 함수 
int deleteLast(headNode* h); //마지막노드 삭제 함수 
int deleteFirst(headNode* h); // 첫번째 노드 삭제 함수 
int invertList(headNode* h); // 리스트를 역순으로 뒤집는 함수 
void printList(headNode* h); // 연결리스트 상태 출력 함수 


int main()
{
	char command; //사용자 메뉴 입력 변수 
	int key; // 사용자 입력 키값 변수 
	headNode* headnode=NULL; //헤드 구조체 포인터 
	
	
    printf("[------ [이상호] [2018038016] ------]\n");
    
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
		scanf(" %c", &command); // 사용자에게 명령을 입력받는다 
		
		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode); //함수 초기화 메뉴 실행 
			break;
		case 'p': case 'P':    
			printList(headnode); // 리스트 프린트 메뉴 실행 
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key); //새로운 노드 삽입 함수 호출 
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key); // 키값을 입력받아 해당 노드 삭제 함수 호출 
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key); // 리스트의 마지막에 노드 연결 함수 호출 
			break;
		case 'e': case 'E':
			deleteLast(headnode); //마지막 노드 삭제 함수 호출 
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key); //첫번째 노드 삽입함수 호출 
			break;
		case 't': case 'T':
			deleteFirst(headnode); //첫번째 노드 삭제 함수 호출 
			break;
		case 'r': case 'R':
			invertList(headnode); //리스트 역순으로 뒤집기 
			break;
		case 'q': case 'Q':
			freeList(headnode); // 모든노드 메모리 할당 해제 
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
	listNode* p; //리스트의 노드에 접근하는 구조체 포인터 

	printf("\n---PRINT\n");

	if(h == NULL) {  //리스트가 없는경우 
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //리스트의 첫번째 노드의 접근 

	while(p != NULL) { //노드의 끝까지 
		printf("[ [%d]=%d ] ", i, p->key); //내용 출력 
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i); //노드 개수 출력 
}



int insertLast(headNode* h, int key) {
	
    listNode* node = (listNode*)malloc(sizeof(listNode)); //새로 삽입할 노드를 동적할당한다
	node->llink = NULL; // 새로운 노드 초기화 
	node->rlink = NULL;
	node->key = key;
	listNode* now = h->first; //움직일 포인터를 초기화 
	
	if(now == NULL) // 해드 포인터가 가리키는 리스트가 없다면 , 즉 노드가 없다면
	{
		h->first = node; //새로 삽입할 노드를 가장 첫 노드로 셋팅
	}
	else //노드가 하나이상 있을 경우
	{
		while(now->rlink != NULL) //마지막 노드에 도달할 때까지
		{
			now = now->rlink; //포인터를 이동시켜준다
		}
		now->rlink = node; //마지막 노드에 도달 시, 새로 삽입할 노드와 연결해준다.
		node->llink = now;
	}

	return 0;
}


int deleteLast(headNode* h) { // 제일 마지막의 노드를 삭제한다 
	
    listNode* now = h->first;	// 접근할 노드 생성	
    int cnt=0;
									
	if (h == NULL) {					// head 즉, 초기화된 리스트 존재하지 않으면 
		printf(">>> 리스트가 초기화 되지 않았습니다. <<<\n");
		return -1;		//비정상 종료 표현
	}
	
	if (h->first == NULL) {				//초기화된 리스트에 노드가 존재하지 않으면 
		printf(">>> 리스트에 노드가 어느 노드도 없습니다. <<<\n");
		return -1;		//비정상 종료 표현
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
	
    listNode *now=h->first; // 움직이는 포인터를 헤드 포인터로 초기화 
    
    if(h->first == NULL) //리스트에 노드가 하나도 없을 때
	{
		printf("리스트에 노드가 없습니다.\n"); //오류 메세지 출력
		return 0;
	}


	h->first = now->rlink;		//doubly linked list의 첫번째 노드를 삭제할 노드의 오른쪽 노드와 연결
	free(now);					//삭제 노드의 메모리 해제

	return 0;		//정상 종료
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
    
	listNode* lead = h->first; //가장 첫번째 노드를 가리키는 노드 설정 
	listNode* pre = NULL; //이전 노드 위치 기억 변수 
	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운노드 동적 할당 
	node->rlink = NULL; //새로 넣을 노드 널로 초기화 
	node->llink = NULL;
	int cnt = 0; //반복문 횟수세는 변수 
	node -> key = key; //키값을 받아 노드에 삽입 

	if (h->first == NULL) //리스트가 비었을때 
		h->first = node; //새로만든 노드를 제일 앞에 삽입 

	else //리스트에 노드가 1개 이상 있을때 
	{
		if (lead->rlink == NULL) //노드가 1개만 있으면 
		{
			if (lead->key >= key) //새로 만든 노드가 더작을때 
			{
				node->rlink = lead; // 유일했던 그노드앞에 새로운 노드를 삽입 
				lead->llink = node;
				h->first = node;
			}
			else //새로 만든 노드의 키가 더크면 
			{
				lead->rlink = node; //유일했던 그노드뒤에 새로운 노드를 연결 
				node->llink = lead;
			}
			return 0; //함수 out 
		}
		while(lead != NULL) //노드가 2개이상이면 
		{
			cnt ++; //카운팅  
			if(lead->key >= key) //리드가 가리키는 키값이 새로 만든 노드의 키값보다 클경우
			{
				node->rlink = lead; //새로만든 노드를 리드 앞에 삽입
				lead->llink = node;
				if (cnt == 1) //새로만든 노드가 맨 앞에 있을 때
				{
					h->first = node; //맨 앞을 가리키는 헤드포인터를 새로만든 노드로 초기화
					return 0; //함수 탈출
				}
				else //새로만든 노드가 맨 앞에 있지 않을 때 (노드와 노드 사이에 있을 때)
				{
					pre->rlink = node; //이전 노드의 다음노드로 새로만든 노드를 삽입
					node->llink = pre;
					return 0; //함수 out
				}
			}

			pre = lead; //이전을 가리키는 노드를 현재 리드가 가리키는 곳으로 지정
			lead = lead->rlink; //리드가 다음 노드를 가리키도록 지정

		}

		if(lead == NULL) //새로 만든 노드가 가장 뒤쪽에 삽입되어야할 때
		{
			pre->rlink = node; //이전의 노드 뒤로 삽입한다.
			node->llink = pre;
		}
	} 
     
	return 0;
}


int deleteNode(headNode* h, int key) {
    listNode *lead = NULL; //리스트의 노드에 접근할 포인터 선언
    listNode* pre = NULL; //이전 노드를 가리킬 previous 변수를 널포인터로 생성
	lead=h->first;
	
	if(h->first == NULL) //노드가 없으면 
	{
		printf("삭제할 노드가 없습니다.\n");
		return 0; // 종료 
	} 

	
	else //노드가 적어도 한개 이상 있을 때
	{
		while(lead->rlink != NULL) //리스트의 모든 노드를 검사
		{
			if (lead->key == key) //리드가 가리키는 키값과 입력받은 키값이 같으면
			{
				break; //반복문 탈출
			}
			pre = lead; //키값이 같지 않으면 이전노드를 현 위치로 설정
			lead = lead->rlink; //현 리드를 다음 위치로 변경
		}

		if(lead->key != key) //반복문에서 결국 키 값을 찾지 못하고 빠져나오는 케이스를 분류
		{
			printf("일치하는 키 값이 없습니다.\n");
			return 0; //함수 탈출
		}

		if(pre == NULL) //키 값을 찾은 경우 총 세가지 케이스로 분류
		{//가장 앞에 노드가 키 값과 일치하는 경우
			h->first = lead->rlink;
			free(lead);
		}
		else if(lead->rlink == NULL) //가장 끝에 노드가 키 값과 일치하는 경우
		{
			pre->rlink = lead->rlink;
			free(lead);
		}
		else //노드가 양 끝에 있지 않고 가운데 있는 경우
		{
			pre->rlink = lead->rlink;
			(lead->rlink)->llink = pre;
			free(lead);
		}

	}

	return 1;

}

