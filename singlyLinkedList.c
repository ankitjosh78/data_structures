// arr = [1,2, 3, 4,5]
// int -> 4 bytes
//       0 index = 1000, 1 index = 1004
// Nodes that are connected with each other.
// Each node is going to carry a value.
// first node is at memory address 1000 and having a value 1
// second node can be at a memory address 2002 having a value 2
// so sequential nodes are marked by pointers (next pointer)
// 1 (1000) -> 2 (2002) -> 3 (2016) -> 4(1996) -> 5 (1200) -> NULL
// [i] -> [i+1] sizeof(data_type)
// value, next
// Head is basically the starting point of the linkedlist
// Tail is the end of the linked list

#include<stdio.h>
#include<stdlib.h>

// Node struct
typedef struct Node{
  int value;
  struct Node* next;
} Node;

Node* createNode(int value){
  Node* newNode = malloc(sizeof(Node));
  if(newNode == NULL){
    printf("Memory allocation failed\n");
    exit(1);
  }
  newNode->value = value;
  newNode->next = NULL;
  return newNode;
}

// head = 1 -> 2 -> 3 ->null
// insertAtHead(head, 4)
// 4 -> 1 -> 2 -> 3 ->null
Node* insertAtHead(Node* head, int value){
  Node* newHead = createNode(value);
  newHead->next = head;
  return newHead;
}

// insertAfterNode
// 1 -> 2 -> 3 -> 4 -> NULL
// 1 -> 2 -> 5 -> 3 -> 4 -> NULL
// TC: O(1) compared to something like a vector which in the worst case takes TC: O(n)
Node* insertAfterNode(Node* node, int value){
  Node* newNode = createNode(value);
  if(node==NULL){
    return newNode;
  }
  Node* temp = node->next;
  node->next = newNode;
  newNode->next = temp;
  return node;
}

// head = 1 -> 2 -> 3 -> null
// insertAtTail(head, 4)
// head = 1 -> 2 -> 3 -> 4 ->null
Node* insertAtTail(Node* head, int value){
  Node* newNode = createNode(value);  
  if(head==NULL){
    return newNode;
  }
  Node* temp = head;
  while(temp->next != NULL){
    temp = temp->next;
  }
  temp->next = newNode;
  return head;
}

// 1 -> 2 -> 3 -> 4 -> null
// deleteNodeByValue(3)
// 1 -> 2 -> 4 -> null
Node* deleteNodeByValue(Node* head, int value){
  if(head==NULL) return head;
  if(head->value == value){
    Node* temp = head;
    Node* newHead = head->next; 
    free(temp);
    head = newHead;
    return head;
  }
  Node* cur = head;
  while(cur->next!=NULL && cur->next->value!=value){
    cur = cur->next;
  }
  if(cur->next == NULL){
    return head;
  }
  Node* toDelete = cur->next;
  Node* afterDelete = toDelete->next;
  cur->next = afterDelete;
  free(toDelete);
  return head;
}

void printLL(Node* head){
  Node* temp = head;
  while(temp!=NULL){
    printf("Node is: %d\n", temp->value);
    temp=temp->next;
  }
}

void freeLL(Node* head){
  while(head!=NULL){
    Node* temp = head->next;
    free(head);
    head = temp;
  }
}

int main(){
  Node* head = NULL;
  head = insertAtHead(head, 1);
  head = insertAtHead(head, 2);
  head = insertAtHead(head, 3);
  // 3 -> 2 -> 1 -> null
  printLL(head);
  head = insertAtTail(head, 4);
  printLL(head);
  // 3 -> 2 -> 1 -> 4 -> null
  head = deleteNodeByValue(head, 1);
  // 3 -> 2 -> 4 -> null
  printLL(head);
  freeLL(head);
  return 0;
}
