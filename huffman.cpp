/*	Proyecto 2
	Decodificador de codigo de Huffman
	Hecho por Antonio Maldonado Pinzon
	Estructura de datos 2019
*/
// define encabezdos de funciones autlizar
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include"libs/stack.h"
#include"libs/Node.h"
using namespace std;

typedef TIPO TreeNodePtr;
typedef struct{
  TreeNodePtr root;
}BST;

void visit(TreeNodePtr);
void preOrder(TreeNodePtr);
void inOrder(TreeNodePtr);
void postOrder(TreeNodePtr);
void eliminar(TreeNodePtr);
int Momento(TreeNodePtr);
int Height(TreeNodePtr);
void deleteTree(TreeNodePtr);
// *************************************************************
//
//    Funcion principal
//
// *************************************************************
int main(int argc,char **argv){
  	// define variables de trabajo  
  	char buffer[80];
  	Stack S;
  	TIPO data; 
  	strcpy(buffer,"frecuencia.in"); //Archivo de frecuencias de "La Regenta"
  	ifstream fileCode(buffer);
  	if(!fileCode.is_open()){
   	cout<<"No se pudo abrir el archivo..."<<endl;
      exit( EXIT_FAILURE );
   }

  	// ciclo de insercion de nodos a la lista
  	cout << endl << "ciclo de creacion..." << endl << endl;
  	while(fileCode.getline(buffer,80)&&(strlen(buffer)>0)){
		//lee datos de una linea del archivo
      char ch;
      int frec;
      sscanf( buffer, "%c %d", &ch, &frec );
		//crear nodo de arbol
		data = new Nodo;
		data->caracter=ch;
		data->frecuencia=frec;
		data->left=data->right=NULL;
		//inserta nodo en stack
 		if(push(&S,data))
   		exit(EXIT_FAILURE);
 	}
  	fileCode.close();
	cout<<endl<<"creacion del arbol"<<endl;
	TIPO raiz;

	while (!empty(&S)){
		TIPO left,right;
		if(pop(&S,&left)||pop(&S,&right)){
			cout<<"Error en la extraccion de nodos en el Stack"<<endl;
			exit(EXIT_FAILURE);
		}
		raiz=new Nodo;
		raiz->caracter='*';
		raiz->frecuencia=left->frecuencia+right->frecuencia;
		raiz->left=left;
		raiz->right=right;
		if(!empty(&S)){
			if(push(&S,raiz)){
				cout<<"Error en la insercion de nodo en el Stack.."<<endl;
				exit(EXIT_FAILURE);
			}
			Node *ptr=S.top;
			while(ptr->next!=NULL){
		  		if((ptr->data->frecuencia)>(ptr->next->data->frecuencia)){
      			TIPO tmp=ptr->next->data;
      			ptr->next->data=ptr->data;
      			ptr->data=tmp;
      			ptr=ptr->next;
     			}else{
   				break;
      		}
     		}
   	}
 	}
	cout<<endl<<"despliega info del arbol BST.."<<endl;
	BST Huffman;
	Huffman.root=raiz;
	preOrder(Huffman.root);
	//Se lee la frase de 1's y 0's
	int pos=0;
	char secuencia[1000];
	//abre el archivo y lee el contenido.
	ifstream archivo("frase.in",ios::in|ios::out);
	archivo.getline(secuencia,1000);
	cout<<"\n\nCodigo a decodificar"<<endl;
	cout<<secuencia<<endl<<endl; //imprime el codigo a decodificar

	//Se recorre el arbol e imprime el dato encontrado.
	TIPO ptr=Huffman.root;
	while (secuencia[pos]!='\0'){
		ptr=Huffman.root;
		while(ptr->caracter=='*'){
			if(secuencia[pos]=='1')
				ptr=ptr->right;
			else
				ptr=ptr->left;
			pos++;//siguiente bit
		}
		if(ptr->caracter=='#') //Si es un espacio
			cout<<" "; //Se imprime un espacio
		else //Si no es un espacio
 		cout << ptr->caracter; //Se muestra el caracter
	}
	cout<<endl<<"Lo dijo: Albert Einstein"<<endl;
   cout<<"\n\nEliminando arbol..."<<endl;
	
	deleteTree(Huffman.root);
	cout<<"Fin del programa"<<endl<<endl;
return EXIT_SUCCESS;
}

void visit(TreeNodePtr node){
	cout<<node->caracter<<" "<<node->frecuencia<<endl;  
}

void preOrder(TreeNodePtr node){
	if(node!=NULL){ 
		visit(node);
      preOrder(node->left);
      preOrder(node->right);     
   } 
}      //end preOrder

void inOrder(TreeNodePtr node){
  	if(node!=NULL){
      inOrder(node->left);
      visit(node);
      inOrder(node->right);
   }
}      //end inOrder

void postOrder(TreeNodePtr node){
  	if(node!=NULL){
      postOrder(node->left);
      postOrder(node->right);
      visit(node);
   }
}      //end postOrder

int Momento(TreeNodePtr node){
	if(node==NULL)
   	return 0;
   else
    	return(1+Momento(node->right)+Momento(node->left));
}

int Height(TreeNodePtr node){
	if(node==NULL)
    	return 0;
   else{
    	int lft =Height(node->left);
      int rgt = Height(node->right);
      return (1+((lft>rgt)?lft:rgt));
    }
}

void deleteTree(TreeNodePtr node){
  	if(node!=NULL){
      deleteTree(node->left);
      deleteTree(node->right);
      delete node;
   }
}

int Weight(TreeNodePtr node){
	if(node==NULL)
		return 0;
	if(node->left==NULL&&node->right==NULL)
    	return 1;
	return (Weight(node->left) + Weight(node->right));
}
