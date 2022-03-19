#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* lista = (List *) malloc(sizeof(List));
    lista -> head = NULL;
    lista -> tail = NULL;
    lista -> current = NULL;
    return lista;

}

void * firstList(List * list) {
  if(list == NULL) return NULL;
  if(list -> head == NULL) return NULL;
  list -> current = list -> head;

  return list -> head -> data;
}

void * nextList(List * list) {
  if(list == NULL) return NULL;
  if(list -> current == NULL) return NULL;
  if(list -> current -> next == NULL) return NULL;
  list -> current = list -> current -> next;
  return list -> current -> data;
}

void * lastList(List * list) {
    if(list == NULL) return NULL;
    if(list -> tail == NULL){
        while(list -> current -> next == NULL){
            nextList(list);
        }
    list -> tail = list -> current;
    }
    list -> current = list -> tail;
    return list -> tail -> data;
}

void * prevList(List * list) {
    if(list == NULL) return NULL;
    if(list -> current == NULL) return NULL;
    if(list -> current -> prev == NULL) return NULL;
    list -> current = list -> current -> prev; 
    return list -> current -> data;
}

void pushFront(List * list, void * data) {
    if(list == NULL) return;
    Node *nuevo = createNode(data);
    if(list -> head == NULL){
        list -> head = nuevo;
        list -> tail = nuevo;
        return;
    }
    nuevo -> next = list -> head;
    if(list -> head -> next == NULL){
        list -> head = nuevo;
        return;
    }

    list -> head -> prev = nuevo;
    list -> head = nuevo;



}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if(list == NULL) return;
    Node *nuevo = createNode(data);
    if(list -> head == NULL){
        list -> head = nuevo;
        list -> tail = nuevo;
        list -> current = nuevo;
        return;
    }
    if( list -> current == NULL) return;

    if(list -> current -> next == NULL){
        list -> current -> next = nuevo;
        list -> tail = nuevo;
        nuevo -> prev = list -> current;
    }

    nuevo -> next = list -> current -> next;
    list -> current -> next -> prev = nuevo;
    nuevo -> prev = list -> current;
    list -> current -> next = nuevo;
    return;

    
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if(list == NULL) return NULL;
    if(list -> current == NULL) return NULL;
    if(list -> head == list -> current){
        Node *auxNode = createNode(list -> current -> data);
        list -> head = NULL;
        list -> current = NULL;
        list -> tail = NULL;
        printf("alo");
        return auxNode -> data;
    }

    if( list -> tail == list -> current){
        Node *auxNode = createNode(list -> current -> data);
        list -> tail = list -> current -> prev;
        list -> current = list -> head;
        list -> current -> prev -> next = NULL;
        return auxNode -> data;
    }

    Node *auxNode = createNode(list -> current -> data);
    list -> current -> next -> prev = list -> current -> prev;
    list -> current -> prev -> next = list -> current -> next;
    return auxNode -> data;

}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}