#include "head.h"

#define TRUE		1
#define FALSE		0
#define OK		1
#define ERROR		0
#define INFEASIBE	-1
#define OVERFLOW	-2

#define IO_INOUT 0
#define IO_OUTIN 1
#define PRO_TCP 0
#define PRO_UDP 1
#define S_NEW	2
#define S_WORKING 1
#define S_WAITING 0


typedef int Status;

typedef struct Con_Node{
	unsigned int ip_addr;			//�����ip��ַ 
	unsigned short my_bind_port;		//�����˿ں� 
	unsigned short des_bind_port;	//������˿ں� 
	unsigned short IO_type;			//���� 
	unsigned short Pro_type;			//Э�� 
	unsigned int Enable;				//����״̬ 	
	unsigned int pid;				//fork�������ӳ���Ľ��̺� 
}ElemType,*ET;

typedef struct LNode {
    ElemType      data;	
    struct LNode *next;	
} LNode, *LinkList;

Status	M_InitList(LinkList *L);
Status	M_DestroyList(LinkList *L);
Status	M_ClearList(LinkList *L);
Status	M_ListEmpty(LinkList L);
int	M_ListLength(LinkList L);
Status M_DisableList(LinkList L);
Status M_EnableList(LinkList L,int n);
//Status M_ListDeleteDisable(LinkList *L);
Status	M_GetElem(LinkList L, int i, ElemType *e);
int	M_LocateElem(LinkList L, ElemType e);
int M_LocateSameElem(LinkList L, ElemType e);
Status	M_PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e);
Status	M_NextElem(LinkList L, ElemType cur_e, ElemType *next_e);
Status	M_ListInsert(LinkList *L, int i, ElemType e);
Status	M_ListDelete(LinkList *L, int i);

int tcpfunc(unsigned short inout, unsigned short listen_port, unsigned int ip, unsigned short port);