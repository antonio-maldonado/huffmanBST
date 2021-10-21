//******************************************************************************
/*
  Node.h
  Encabezados del Node

  \author Ricardo Legarda Sáenz.
  \date 2015-09-06 22:25:34 
*/
//******************************************************************************


#ifndef _NODE_HPP
#define _NODE_HPP     // include just once


// incluye los encabezados de la funciones a utilizar
#include <cstdlib>    // NULL

// definicion de estructuras de datos
//typedef int TIPO;
//typedef struct
//{
//  char Nombre[100];  
//  int Matricula;
//} TIPO;
//typedef struct
//{
//  char word[100];
//  int frecuencia;
//} TIPO;
struct Nodo
{
  char caracter;
  int frecuencia;
  Nodo *left, *right;
  Nodo ()  {  left = NULL;    right = NULL;  } 
};
typedef Nodo* TIPO;



// define estructura de nodos y funciones de creacion/eliminacion
struct Node 
{
  TIPO data;
  Node *next, *prev, *left, *right;
  Node ()  {  next = NULL;    prev = NULL;   left = NULL;    right = NULL;  } 
};
Node* CrearNode(void);
void EliminaNode(Node*);


#endif




