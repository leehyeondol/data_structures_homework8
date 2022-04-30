#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {//노드 구조체
	int key;//키
	struct Node* llink;//왼쪽 링크
	struct Node* rlink;//오른쪽 링크
} listNode;//별명

/* 함수 리스트 */
int initialize(listNode** h);//헤드 노드 초기화
int freeList(listNode* h);//메모리 해제함수
int insertLast(listNode* h, int key);//마지막 노드 추가함수
int deleteLast(listNode* h);//마지막 노드 삭제 함수
int insertFirst(listNode* h, int key);//첫 노드 생성함수
int deleteFirst(listNode* h);//첫노드 삭제 함수
int invertList(listNode* h);//노드 역순 재배치함수

int insertNode(listNode* h, int key);//노드 생성함수
int deleteNode(listNode* h, int key);//노드 삭제함수

void printList(listNode* h);//노드 출력함수



int main()
{
	printf("[----- [Lee hyeondo]  [2019038085] -----]\n");
	char command;//커멘드 변수
	int key;//키 변수
	listNode* headnode=NULL;//헤드노드 초기화

	do{//while조건에 따라 반복
		printf("----------------------------------------------------------------\n");//메뉴 출력
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//커멘드 입력받음

		switch(command) {
		case 'z': case 'Z'://커멘드가 z면
			initialize(&headnode);//헤드노드 초기화
			break;
		case 'p': case 'P'://커멘드가 p면
			printList(headnode);//리스트 출력
			break;
		case 'i': case 'I'://커멘드가 i면
			printf("Your Key = ");
			scanf("%d", &key);//키 입력
			insertNode(headnode, key);//키를 노드에 추가
			break;
		case 'd': case 'D'://커멘드가 d면
			printf("Your Key = ");
			scanf("%d", &key);//키 입력
			deleteNode(headnode, key);//키와 같은 값을 가진 노드 삭제
			break;
		case 'n': case 'N'://커멘드가 n면
			printf("Your Key = ");
			scanf("%d", &key);//키 입력
			insertLast(headnode, key);//마지막 노드로 키 추가
			break;
		case 'e': case 'E'://커멘드가 e면
			deleteLast(headnode);//마지막 노드 삭제
			break;
		case 'f': case 'F'://커멘드가 f면
			printf("Your Key = ");
			scanf("%d", &key);//키입력
			insertFirst(headnode, key);//첫 노드로 입력
			break;
		case 't': case 'T'://커멘드가 t면
			deleteFirst(headnode);//첫 노드 삭제
			break;
		case 'r': case 'R'://커멘드가 r면
			invertList(headnode);//노드 역순 재배치
			break;
		case 'q': case 'Q'://커멘드가 q면
			freeList(headnode);//동적할당받은것들 메모리 초기화
			break;
		default://위의 케이스가 아닌경우
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");//Concentration!!출력
			break;
		}

	}while(command != 'q' && command != 'Q');//q거나Q가 커멘드가 아니면 다시 반복

	return 1;
}


int initialize(listNode** h) {//초기화 함수

	if(*h != NULL)//headNode가 NULL이 아니면
		freeList(*h);//freeNode를 호출하여 할당된 메모리 모두 해제

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));//헤드노드 동적할당
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode* h){//노드 메모리 해제함수

	if(h->rlink == h)//헤드노드 하나뿐이면
	{
		free(h);//헤드 노드 해제
		return 1;
	}

	listNode* p = h->rlink;//p노드 생성

	listNode* prev = NULL;//prev노드 생성
	while(p != NULL && p != h) {//끝까지 반복
		prev = p;//prev는 p
		p = p->rlink;//p는 다음 노드
		free(prev);//prev 해제
	}
	free(h);//해드 노드 해제
	return 0;
}



void printList(listNode* h) {//노드 출력 함수
	int i = 0;
	listNode* p;//p 노드 생성

	printf("\n---PRINT\n");

	if(h == NULL) {//헤드 노드가 NULL이면
		printf("Nothing to print....\n");//출력 못함 출력
		return;
	}

	p = h->rlink;//노드 p 는 헤드노드의 다음노드 

	while(p != NULL && p != h) {//끝까지 반복
		printf("[ [%d]=%d ] ", i, p->key);//노드들 출력
		p = p->rlink;//다음노드로 넘어감
		i++;// 갯수 저장
	}
	printf("  items = %d\n", i);//총 노드 갯수 출력


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);//노드들의 주소 출력

	i = 0;
	p = h->rlink;//p는 헤드노드의 다음 노드
	while(p != NULL && p != h) {//끝까지 반복
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);//노드의 값과 노드의 좌우 링크 주소 출력
		p = p->rlink;//다음노드로 이동
		i++;//i하나 추가
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {//마지막 노드 추가

	if (h == NULL) return -1;//헤드노드가 NULL이면 리턴 -1

	listNode* node = (listNode*)malloc(sizeof(listNode));//노드 동적할당
	node->key = key;//노드 키값
	node->rlink = NULL;//오른쪽 링크 0
	node->llink = NULL;//왼쪽 링ㅋ0

	if (h->rlink == h) //헤드노드 하나뿐이면
	{
		h->rlink = node;//다음노드는 새 노드
		h->llink = node;//전 노드도 새 노드
		node->rlink = h;//노드의 다음 노드는 헤드 노드
		node->llink = h;//노드의 전 노드는 헤드노드
	} else {//여러개면
		h->llink->rlink = node;//마지막 노드는 새 노드
		node->llink = h->llink;//노드의 전 노드는 원래 해드노드의 전노드
		h->llink = node;//해드노드의 전 노드는 노드
		node->rlink = h;//새 노드의 다음 노드는 헤드 노드
	}

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {//마지막 노드 삭제 함수

	if (h->llink == h || h == NULL)//만야갸 헤드노드 하나뿐이거나 NULL이면
	{
		printf("nothing to delete.\n");//삭제할게 없음
		return 1;
	}

	listNode* nodetoremove = h->llink;//새 노드는 헤드노드의 전노드

	/* link 정리 */
	nodetoremove->llink->rlink = h;//마지막 노드 삭제
	h->llink = nodetoremove->llink;//헤드노드의 llink는 마지막 노드의 전노드 가리킴

	free(nodetoremove);//메모리 해제

	return 1;
}

int insertFirst(listNode* h, int key) {//첫 노드 추가 함수

	listNode* node = (listNode*)malloc(sizeof(listNode));//노드 동적할당
	node->key = key;//키입력
	node->rlink = NULL;//오른쪽 링크 NULL
	node->llink = NULL;//왼쪽 링크 NULL


	node->rlink = h->rlink;//새 노드의 오른쪽은 원래 헤드노드의 오른쪽 링크
	h->rlink->llink = node;//첫 노드는 새 노드
	node->llink = h;//노드의 왼쪽 링크는 헤드노드
	h->rlink = node;//해드노드의 오른쪽 링크는 노드 


	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {//첫 노드 삭제 함수

	if (h == NULL || h->rlink == h)// 헤드노드가 NULL이거나 하나뿐이면
	{
		printf("nothing to delete.\n");//삭제할게 없음
		return 0;
	}

	listNode* nodetoremove = h->rlink;//nodetoremove 노드는 첫 노드 

	/* link 정리 */
	nodetoremove->rlink->llink = h;//첫 노드삭제
	h->rlink = nodetoremove->rlink;//헤드 노드의 다음노드는 nodetoremove의 다음노드

	free(nodetoremove);//nodetoremove 메모리 해제

	return 1;

}


int invertList(listNode* h) {//리스트의 링크를 역순으로 재 배치 함수


	if(h->rlink == h || h == NULL) {//만약 헤드노드 뿐이거나 NULL이면
		printf("nothing to invert...\n");//invert할거 없음
		return 0;
	}
	listNode *n = h->rlink;//노드 n은 헤드 노드의 다음노드
	listNode *trail = h;//trail노드는 헤드노드
	listNode *middle = h;//middle노드는 헤드노드

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink;//헤드노드의 왼쪽 링크는 오른쪽 링크

	while(n != NULL && n != h){//n이 NULL이거나 h가 될때까지 반복
		trail = middle;//trail은 middle
		middle = n;//middle 은 n
		n = n->rlink;//n은 다음노드
		middle->rlink = trail;//middle의 다음노드는 trail노드
		middle->llink = n;//middle의 전 노드는 n
	}

	h->rlink = middle;//헤드의 다음노드는 미들 노드

	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {//노드 추가 함수

	if(h == NULL) return -1;//헤드노드가 NULL이면 리턴 -1

	listNode* node = (listNode*)malloc(sizeof(listNode));//새 노드 n
	node->key = key;// 키 입력
	node->llink = node->rlink = NULL;//왼쪽, 오른쪽 링크는 NULL

	if (h->rlink == h)//만약 헤드노드 하나뿐이면
	{
		insertFirst(h, key);//첫노드 입력함수
		return 1;
	}

	listNode* n = h->rlink;//n은 헤드노드 다음노드

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) {//n이NULL이거나 h일때까지 반복
		if(n->key >= key) {//n의 키가 입력받은 키보다 크면
			if(n == h->rlink) {//근데 그게 첫 노드 다음이면
				insertFirst(h, key);//첫노드 입력함수
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;//새 노드의 오른쪽은 n
				node->llink = n->llink;//새 노드의 왼쪽은 n의 왼쪽노드
				n->llink->rlink = node;//n의 전 노드의 다음 링크는 새 노드
				n->llink = node;//n의 왼쪽 링크는 새 노드
			}
			return 0;
		}

		n = n->rlink;//n은 다음노드로 이동
	}

	
	insertLast(h, key);//마지막 노드까지 찾지 못한 경우, 마지막에 삽입
	return 0;
}

int deleteNode(listNode* h, int key) {//노드 삭제 함수

	if (h->rlink == h || h == NULL)//만약 헤드노드 뿐이거나 NULL 이면
	{
		printf("nothing to delete.\n");//삭제할 노드가 없음
		return 0;
	}

	listNode* n = h->rlink;//노드 n은 헤드노드의 다음 노드

	while(n != NULL && n != h) {//n이 NULL이거나 헤드노드일때까지 반복
		if(n->key == key) {//만약 n의 키가 입력받은 키와 같으면
			if(n == h->rlink) { //근데 그게 첫 노드면
				deleteFirst(h);//첫 노드 삭제 함수
			} else if (n->rlink == h){ //마지막 노드면
				deleteLast(h);//마지막 노드 삭제 함수
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;//전 노드의 다음링크는 n의 다음노드
				n->rlink->llink = n->llink;//다음 노드의 전 링크는 n의 전 노드
				free(n);//메모리 해제
			}
			return 0;
		}

		n = n->rlink;//다음노드로 이동
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);//찻지 못함 출력
	return 0;
}


