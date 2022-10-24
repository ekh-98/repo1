#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <cstring>
#include <stdio.h>

using namespace std;

struct Node{
    int data;
    Node *Parent;
    Node *left;
    Node *right;
    int color;
};

class RedBlackTree{
    private:
        Node *root;
        Node *Nil;

    public:
        RedBlackTree(){
	     Nil=new Node();
	     Nil->left=NULL;
	     Nil->right=NULL;
	     Nil->color=0;
	     root=Nil;
	 	}
	 	void RBInsertFixUp(Node *newNode){
        Node *uncle=new Node();
        while (newNode->Parent->color==1){ //while z.p.color == RED
            if (newNode->Parent==newNode->Parent->Parent->left){ //if z.p == z.p.p.left
                uncle=newNode->Parent->Parent->right;//y = z.p.p.right
                if (uncle->color==1){ //if y.color == RED
                    newNode->Parent->color=0; //z.p.color = BLACK   case 1
                    uncle->color=0; //y.color = BLACK   case 1
                    newNode->Parent->Parent->color=1; //z.p.p.color = RED  case 1
                    newNode=newNode->Parent->Parent; // z = z.p.p  case 1
                }
                else if(newNode==newNode->Parent->right){ //elseif z == z.p.right
                    newNode=newNode->Parent; //z = z.p   case 2
                    leftRotation(newNode); //LEFT-ROTATE(T, z)  case 2
                }
                else{
                    newNode->Parent->color=0;//z.p.color = BLACK   case 3
                    newNode->Parent->Parent->color=1; //z.p.p.color = RED  case 3
                    rightRotation(newNode->Parent->Parent);//RIGHT-ROTATE(T, z.p.p)  case 3
                }
            
            }
            else{
                uncle=newNode->Parent->Parent->left;//y = z.p.p.right
                if (uncle->color==1){ //if y.color == RED
                    newNode->Parent->color=0; //z.p.color = BLACK   case 1
                    uncle->color=0; //y.color = BLACK   case 1
                    newNode->Parent->Parent->color=1; //z.p.p.color = RED  case 1
                    newNode=newNode->Parent->Parent; // z = z.p.p  case 1
                }
                else if(newNode==newNode->Parent->left){ //elseif z == z.p.right
                    newNode=newNode->Parent; //z = z.p   case 2
                    rightRotation(newNode); //LEFT-ROTATE(T, z)  case 2
                }
                else{
                    newNode->Parent->color=0;//z.p.color = BLACK   case 3
                    newNode->Parent->Parent->color=1; //z.p.p.color = RED  case 3
                    leftRotation(newNode->Parent->Parent);//RIGHT-ROTATE(T, z.p.p)  case 3
                }

            }

        }
        this->root->color=0;

        }
        void RBInsert(int key)
		{
//     		cout<<"Key-"<<key<<" ";
//            cout<<typeid(key).name();
            //Create the new node which is going to add
        
            Node *newNode = new Node();
            newNode->Parent = NULL;
            newNode->data = key;
            

            Node *y = Nil; //y = T.nil
            Node *x = this->root;//x = T.root
			
            while (x != Nil) { //while x != T.nil
                y = x;
                
                if (newNode->data < x->data) { //if z.key < x.key
                    x = x->left;               //x = x.left
                } else {
                    x = x->right;              //x = x.right
                }
            }
		
            newNode->Parent = y;//z.p = y
            if (newNode->Parent == Nil) {     //if y == T.nil
                root = newNode;    //T.root = z
            } else if (newNode->data < y->data) { //elseif z.key < y.key
                y->left = newNode; //y.left = z
            } else {
                y->right = newNode; //y.right = z
            }
            newNode->left = Nil;//z.left = T.nil
            newNode->right = Nil;//z.right = T.nil
            newNode->color = 1; //z.color = RED
            
            RBInsertFixUp(newNode);
    
    }
    
        
       
        void preOrderTraverse(Node *traverse_node,string indent,bool last){
            
            string node_color;
            if (traverse_node->color==0)
                    node_color="B";
            else
                node_color="R";
         
            if (traverse_node==root){
                cout<<node_color<<traverse_node->data<<endl;
                preOrderTraverse(traverse_node->right, indent, false);
                preOrderTraverse(traverse_node->left, indent, true);
            }
                
            else{
                if (traverse_node!=Nil){
                printf("%s",indent);
                if (last==true){
                    std::wcout<<"└──";
                    indent += "     ";
                }
             
                else{
                    wcout<<"├──";
                    indent += "│    ";
                }
                cout<<node_color<<traverse_node->data;
                cout<<endl;
                preOrderTraverse(traverse_node->right, indent, false);
                preOrderTraverse(traverse_node->left, indent, true);
                
                }
             }
         }

        void displayRBTree(){
            string indent="";
            bool last=true;
            preOrderTraverse(this->root,indent,last);
        }

         void leftRotation(Node *newNode){
            Node *y=newNode->right;
            newNode->right=y->left;

            if (y->left!=Nil)
                y->left->Parent=newNode;

            y->Parent=newNode->Parent;

            if (newNode->Parent==Nil)
                root=y;
            else if (newNode==newNode->Parent->left)
                newNode->Parent->left=y;
            else
                newNode->Parent->right=y;

            y->left=newNode;
            newNode->Parent=y;

        }
        void rightRotation(Node *newNode){
            Node *y=newNode->left;
            newNode->left=y->right;

            if (y->right!=Nil)
                y->right->Parent=newNode;

            y->Parent=newNode->Parent;

            if (y->Parent==Nil)
                root=y;
            else if (newNode==newNode->Parent->left)
                newNode->Parent->left=y;
            else
                newNode->Parent->right=y;

            y->right=newNode;
            newNode->Parent=y;
        }
            
        void deleteNode(int value){
            
         if(root==Nil)
           {
               cout<<"\nEmpty Tree." ;
               return ;
          }
           Node *z = SearchNode(root,value);
		   Node *x, *y;
           int y_original_color;

           if (z == Nil) {
			cout<<"Element Not Found in the tree"<<endl;
			return;
		  } 
        
              y=z;
              y_original_color=y->color;
              if (z->left==Nil){
                x=z->right;
                RB_Delete_Transplant(z,z->right);
              }
              else if (z->right==Nil){
                x=z->left;
                RB_Delete_Transplant(z,z->left);
              }
              else{
                y=minimum(z->right);
                y_original_color=y->color;
                x=y->right;
                if (y->Parent==z)
                    x->Parent=y;
                else{
                    RB_Delete_Transplant(y,y->right);
                    y->right=z->right;
                    y->right->Parent=y;
                }
                RB_Delete_Transplant(z,y);
                y->left=z->left;
                y->left->Parent=y;
                y->color=z->color;
              }
          cout<<z->data;
          delete z;
          cout<<z->data;
          if (y_original_color==0)
            RB_Delete_FixUp(x);

        }

        Node* SearchNode(Node *node,int key) {
		if (node == Nil || key == node->data) {
			return node;
		}

		if (key < node->data) {
			return SearchNode(node->left, key);
		} 
		else{
		    return SearchNode(node->right, key);
		}
		
	}

       void RB_Delete_Transplant(Node *u,Node *v){
        if (u->Parent==Nil){
            root=v;
        }
        else if (u==u->Parent->left){
            u->Parent->left=v;
        }
        else{
            u->Parent->right=v;
        }
        v->Parent=u->Parent;
       }

       void RB_Delete_FixUp(Node *x){
     
            Node *w;
            while (x!=root && x->color==0){
                if (x==x->Parent->left){
                    w=x->Parent->right;
                    if(w->color==1){
                        w->color=0;
                        x->Parent->color=1;
                        leftRotation(x->Parent);
                        w=x->Parent->right;
                    }
                    if (w->left->color==0 && w->right->color==0){
                        w->color=1;
                        x=x->Parent;
                    }
                    else{
                    
                    if (w->right->color==0){
                        w->left->color==0;
                        w->color=1;
                        rightRotation(w);
                        w=x->Parent->right;
                    }
                        w->color=x->Parent->color;
                        x->Parent->color=0;
                        w->right->color=0;
                        leftRotation(x->Parent);
                        x=root;
                    
                    }
                    
                }
                else{
                    
                    w=x->Parent->left;
                    if(w->color==1){
                        w->color=0;
                        x->Parent->color=1;
                        rightRotation(x->Parent);
                        w=x->Parent->left;
                    }
                    if (w->right->color==0 && w->left->color==0){
                        w->color=1;
                        x=x->Parent;
                    }
                    else{
                     if (w->left->color==0){
                        w->right->color==0;
                        w->color=1;
                        leftRotation(w);
                        w=x->Parent->left;
                    }
                    
                        w->color=x->Parent->color;
                        x->Parent->color=0;
                        w->left->color=0;
                        rightRotation(x->Parent);
                        x=root;
                         
                    }
                    
                }
            }
            x->color=0;
       }

        Node* findMaximum(){
            return maximum(this->root);
        }

        Node* findMinimum(){
            return minimum(this->root);
        }

        // find the node with the minimum key
        Node* minimum(Node *node) {
            while (node->left != Nil) {
                node = node->left;
            }
            return node;
	    }

        // find the node with the maximum key
        Node* maximum(Node *node) {
            while (node->right != Nil) {
                node = node->right;
            }
            return node;
        }



  
    
};
void tokenize(string const &str, const char* delim,
            vector<std::string> &out)
{
    char *token = strtok(const_cast<char*>(str.c_str()), delim);
    while (token != NULL)
    {
        out.push_back(string(token));
        token = strtok(NULL, delim);
    }
}

int main() {
	RedBlackTree rbt;
    string input;  
    int y=0;
     while(y!=1)
     {
        getline(cin, input);
         string str_delete = "Delete";
         string max = "Max";
         string min = "Min";
         size_t found_delete = input.find(str_delete);
         size_t found_max = input.find(max);
         size_t found_min = input.find(min);
         int size;
         int value;
         string node_value;
         
         if (found_delete != string::npos){
       
            int start = 0;
            string delimiter=" ";
		    int end = input.find(delimiter);
		    while (end != -1) {
		        start = end + delimiter.size();
		        end = input.find(delimiter, start);
		    }
            node_value=input.substr(start, end - start);
	        value =atoi(node_value.c_str());
	       
             rbt.deleteNode(value);
             rbt.displayRBTree();
               
         }
         else if (found_max != string::npos){
                Node* max_value_node=rbt.findMaximum();
                cout<<max_value_node->data<<endl;
         }
            
         else if (found_min != string::npos){
            Node* max_value_node=rbt.findMinimum();
            cout<<max_value_node->data<<endl;
         }
             
         else
         {
                int start = 0;
                string delimiter=" ";
			    int end = input.find(delimiter);
			    while (end != -1) {
			        node_value=input.substr(start, end - start);
			        value =atoi(node_value.c_str());
			        rbt.RBInsert(value);
			        start = end + delimiter.size();
			        end = input.find(delimiter, start);
			    }
			    node_value=input.substr(start, end - start);
			    value =atoi(node_value.c_str());
			    rbt.RBInsert(value);    
           
                rbt.displayRBTree();
                 

         }
            
     }
	    return 0;
}

