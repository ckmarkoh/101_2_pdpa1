/****************************************************************************
  FileName     [ bst.h ]
  PackageName  [ util ]
  Synopsis     [ Define binary search tree package ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2005-2010 LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/

#ifndef BST_H
#define BST_H

#include <cassert>
#include <iostream>
#include <iomanip>
#include <queue>
#include <fstream>

using namespace std;

template <class T> class BSTree;

// BSTreeNode is supposed to be a private class. User don't need to see it.
// Only BSTree and BSTree::iterator can access it.
//
// DO NOT add any public data member or function to this class!!
//
template <class T>
class BSTreeNode
{
   // TODO: design your own class!!
   friend class BSTree<T>;
   friend class BSTree<T>::iterator;

   BSTreeNode(const T& d, BSTreeNode<T>* p = 0, BSTreeNode<T>* l = 0, BSTreeNode<T>* r = 0 ):
      _data(d), _pare(p), _left(l), _right(r)  {}
    T                _data;
    BSTreeNode<T>*   _pare;
    BSTreeNode<T>*   _left;
    BSTreeNode<T>*   _right;
};


template <class T>
class BSTree
{
public:
   // TODO: design your own class!!
   BSTree() {
      _root = new BSTreeNode<T>(T());
      _eNode = _root;
      _size=0;
      //_root->_left = _root->_right =0; // _head is a dummy node
   }
   ~BSTree() { clear(); delete _root; }

friend class iterator;
   class iterator
   {
      friend class BSTree;
   public:
      iterator(BSTreeNode<T>* n= 0): _node(n) {}
      iterator(const iterator& i) : _node(i._node) {}
      ~iterator() {} // Should NOT delete _node
      // TODO: implement these overloaded operators
    const T& operator * () const { return _node->_data; }
    T& operator * () { return _node->_data; }
    iterator& operator ++ () 
    { 
        _node=ToNext(_node);
        return *this;
    }
    iterator operator ++ (int) 
    {
        iterator it(_node);
        _node=ToNext(_node);
        return it; 
    }
    iterator& operator -- () 
    {
        _node=ToPrev(_node);
         return *(this); 
    }
    iterator operator -- (int) 
    { 
        iterator it(_node);
        _node=ToPrev(_node);

        return it;
    }
      iterator operator + (int i) const 
        {
        iterator it(_node);
        for(int j=0 ;j<i ;j++)
        it._node=ToNext(it._node);
        return it;
        }
      iterator& operator += (int i) 
        {
        for(int j=0 ;j<i ;j++)
        _node=ToNext(_node);
        return (*this); 
        }
      iterator& operator = (const iterator& i) 
        {
        _node = i._node;
         return *(this); 
        }
      bool operator != (const iterator& i) const 
        {
        return (i._node != _node);
        }
      bool operator == (const iterator& i) const 
        {
        return (i._node == _node);
        }

      bool to_left_child();
	  bool to_right_child();
	  
    BSTreeNode<T>* ToNext(BSTreeNode<T>* t) ; 

    BSTreeNode<T>* ToPrev(BSTreeNode<T>* t) ; 


   private:
      BSTreeNode<T>* _node;
   };

   // TODO: implement these functions


	iterator root()
		{return iterator(this->_root);}
	iterator root() const
		{return iterator(this->_root);}

   iterator begin() const 
     { 
        BSTreeNode<T>* t=_root;
        while(t->_left!=0)
        {
        t=t->_left;
        }
       return iterator(t);
    }

   iterator end() const 
    {    
       return iterator(_eNode);
    }

   bool empty() const ;
   size_t size() const {  return _size; }

   void pop_front() ;
     void pop_back() ;
  
   // return false if nothing to erase
   bool erase(iterator pos); 
 
   bool erase(size_t id) ;

   bool erase(const T& x) ;
   bool insert(const T& x); 
   void print(ostream& fout);// { }
   void clear(); 


	BSTreeNode<T>* getend()
	{return _eNode;}

   bool leftRot(BSTreeNode<T>* x );
   bool rightRot(BSTreeNode<T>* x );

   bool leftRot(iterator it ){ return leftRot(it._node); };
   bool rightRot(iterator it ){ return rightRot(it._node); };
   
   bool rotate(size_t id,bool right );

   bool rotate(iterator it,bool right );
     
private:
    BSTreeNode<T>*   _root;
    static BSTreeNode<T>*   _eNode;//tail;
    size_t _size;
	//static BSTreeNode<T>* _tail;

   // [OPTIONAL TODO] helper functions; 
	void edRecont();
	void del(BSTreeNode<T>* x);
	void recDel(BSTreeNode<T>* posX);
    BSTreeNode<T>* findMin(BSTreeNode<T>* t); 
    BSTreeNode<T>* findMax(BSTreeNode<T>* t) ;
    BSTreeNode<T>* findSsc(BSTreeNode<T>* t) ;

   void Recprint(BSTreeNode<T>* t, size_t level,ostream& fout ); 
};

template <class T>
BSTreeNode<T>* BSTree<T>::_eNode =0 ;

template <class T>
  bool BSTree<T>::iterator::to_left_child(){
	if(_node->_left!=0){
		_node=_node->_left;
		return true;
	}
	else{
		return false;	
	}
  }

template <class T>
  bool BSTree<T>::iterator::to_right_child(){//NOT GO TO  ENODE
	if((_node->_right!=0)&&(_node->_right!=_eNode)){
		_node=_node->_right;
		return true;
	}
	else{
		return false;	
	}
  }

template <class T>
    BSTreeNode<T>* BSTree<T>::iterator::ToNext(BSTreeNode<T>* t)  
    { 
    if(t->_right!=0)//&&(t->_right->_data!=T(0)))
        {t=t->_right;
            while(t->_left!=0)
                {t=t->_left;}
        }
    else{
            while((t->_pare!=0)&&( t->_pare->_data < t->_data ))
            {t=t->_pare;}
            t=t->_pare;
        }
    return t;
    }
template <class T>
    BSTreeNode<T>* BSTree<T>::iterator::ToPrev(BSTreeNode<T>* t)  
    { 
		if(t==BSTree::_eNode)
			 {t=t->_pare;}
		else
		{ 
		if(t->_left!=0)    
			{t=t->_left;
				while(t->_right!=0)//&&(t->_right->_data!=T(0)))
					{t=t->_right;}
			}
		else //if((t->_data) > (_root->_data))
			{
			while((t->_pare!=0)&&(  t->_data < t->_pare->_data))
				{t=t->_pare;}
			t=t->_pare;
			}
		}    
		return t;//may exceed??
    }
template <class T>
   bool BSTree<T>::empty() const 
    {
       if(_size==0) 
           {return true;}
      else 
        {return false;}
    }

template <class T>
  void BSTree<T>::pop_front() 
    {
    iterator it(begin());
    erase(it);
    }
template <class T>
   void BSTree<T>::pop_back() 
    {
   iterator it(_eNode);
    it._node=it._node->_pare;
    erase(it);
    }

   // return false if nothing to erase
template <class T>
   bool BSTree<T>::erase(iterator pos) 
    {
    if(empty())
    {return false; }
    else if(pos._node==_eNode)
        {return false;}
    else if(_size==1)
        {
          delete _eNode;
          _eNode = _root;
          _size=0;
		  //_tail=_eNode;
        return true;
        }
    else{
        _eNode->_pare->_right=0;//_eNode detach;
     //   //cout<<31<<endl;//debug
        recDel(pos._node);
		edRecont();
     /*   BSTreeNode<T>* fMax=findMax(_root);
        fMax->_right=_eNode;
        _eNode->_pare=fMax;*/

        return true;
        }       
    }

template <class T>
   bool BSTree<T>::erase(const T& x) 
 { 
    if(empty())
    {return false; }
    else
    {
      BSTreeNode<T>* t=_root;
        while(true) 
        {
        if((t->_data) < x)
            {
            if((t->_right!=0)&&(t->_right!=_eNode))
                {t=t->_right;}
            else
                {return false;}
            }
        else if(x<t->_data)
            {
            if(t->_left!=0)
                {t=t->_left;}
            else
                {return false;}
            }        
        else if(x==t->_data)
            {    
            iterator it(t);
            return erase(it);
            }
        }
     }
  }
template <class T>
   bool BSTree<T>::insert(const T& x) 
   { 
   if(empty())    
        {_root->_data=x;
        _size=_size+1;
        _eNode=new BSTreeNode<T>(T(),_root);
        _root->_right=_eNode;
		//_tail=_eNode;
        return true;
        }
   else
     {
      BSTreeNode<T>* t=_root;
        _eNode->_pare->_right=0;//_eNode detach;
     //   //cout<<31<<endl;//debug
     //while(((_root->_data!=0)&&(_root->right==_eNode))||(_root->left==0))

        while(true) 
        {
        if((t->_data) < x)
        {
            if((t->_right!=0)&&(t->_right!=_eNode))
                {t=t->_right;}
            else 
                {
                BSTreeNode<T>* NNod=new BSTreeNode<T>(x,t,0,0);
              /*  if(t->_right==_eNode)
                    {
                      NNod->_right=_eNode;
                      _eNode->_pare=NNod;
                    }*/
               // iterator it(_eNode);//debug
                t->_right=NNod;
                _size=_size+1;
				edRecont();
                return true;
                }
        }
        else if(x<t->_data)
        {
            if(t->_left!=0)
                {t=t->_left;}
            else
                {
                BSTreeNode<T>* NNod=new BSTreeNode<T>(x,t,0,0);
                t->_left=NNod;
                _size=_size+1;
				edRecont();
                return true;
                }
        }        
        else if(x==t->_data)
            {
			edRecont();
			return false;}
        } 
     }
   }

template <class T>
   void BSTree<T>::clear() 
    {
		////cout<<9<<endl;
	if(_eNode->_pare!=0)
	{_eNode->_pare->_right=0;}//enode detach
		////cout<<8<<endl;
	if(_size>0)
    {    del(_root);}
	else
	{delete _root;}
		////cout<<1<<endl;
		//delete _root;
        _root = new BSTreeNode<T>(T());////cout<<2<<endl;
        _eNode =_root; //new BSTreeNode<T>(T(),_root);
        //_root->_right=_eNode;
        _size=0;////cout<<3<<endl;
    } // delete all nodes except for the dummy node


template <class T>
   void BSTree<T>::edRecont()
	{   if(_size>0)
		{
		BSTreeNode<T>* fMax=findMax(_root);
        fMax->_right=_eNode;
        _eNode->_pare=fMax;
		}
		else
		{_eNode=_root;
_root->_pare=0;
		_root->_left=0;
		_root->_right=0;}
		//_tail=_eNode;
	}
	
template <class T>
   void BSTree<T>::del(BSTreeNode<T>* x)
    {
        if (x->_left!=0)
            {////cout<<11<<endl;
			del(x->_left);}
        if (x->_right!=0)
            {////cout<<12<<endl;
			del(x->_right);}
        delete x;
    }
template <class T>
void BSTree<T>::recDel(BSTreeNode<T>* posX)
{
    if((posX->_left==0) && (posX->_right==0))//trivil 1
        {
            if(posX->_pare->_left==posX)
                {posX->_pare->_left=0;}
            else if(posX->_pare->_right==posX) 
                {posX->_pare->_right=0;}            
        delete posX;    
        _size=_size-1;
        }
    else if((posX->_left!=0)&&(posX->_right==0)&&(posX!=_root))//one left child
        {
            if(posX->_pare->_left==posX)
                {posX->_pare->_left=posX->_left;
                posX->_left->_pare=posX->_pare;}
            else if(posX->_pare->_right==posX) 
                {posX->_pare->_right=posX->_left;
                posX->_left->_pare=posX->_pare;} 
                delete posX;
                _size=_size-1;
        }
     else if((posX->_left==0)&&(posX->_right!=0)&&(posX!=_root))//one left child
        {
            if(posX->_pare->_left==posX)
                {posX->_pare->_left=posX->_right;
                posX->_right->_pare=posX->_pare;}
            else if(posX->_pare->_right==posX) 
                {posX->_pare->_right=posX->_right;
                posX->_right->_pare=posX->_pare;}
                delete posX;
                _size=_size-1;
        }
    else if((posX->_left!=0)&&(posX->_right==0)&&(posX==_root) )//one left child root
        {
                _root=posX->_left;
                _root->_pare=0;
                delete posX;
        _size=_size-1;
        } 
    else if((posX->_left==0)&&(posX->_right!=0)&&(posX==_root) )//one right child root
        {
                _root=posX->_right;
                _root->_pare=0;
                delete posX;
        _size=_size-1;
        } 
    else if((posX->_left!=0) && (posX->_right!=0))//two child
        {
            BSTreeNode<T>* sscX=findSsc(posX);
            posX->_data=sscX->_data;
            recDel(sscX);
        }
        
    }

template <class T>
    BSTreeNode<T>* BSTree<T>::findMin(BSTreeNode<T>* t) 
    {
    if (t->_left == 0)
        {return t;}
    else
        {return findMin(t->_left);}
    }

template <class T>
    BSTreeNode<T>* BSTree<T>::findMax(BSTreeNode<T>* t) 
    {
    if (t->_right == 0)
        {return t;}
    else
        {return findMax(t->_right);}
    }

template <class T>
    BSTreeNode<T>* BSTree<T>::findSsc(BSTreeNode<T>* t) 
    {
    if (t->_right == 0)
        {return 0;}
    else
        {return findMin(t->_right);}
    }


template <class T>
   void BSTree<T>::print(ostream& fout) {
   		if(_size>0){
			Recprint(_root,0,fout);   
		}
   }
template <class T>
   void BSTree<T>::Recprint(BSTreeNode<T>* t, size_t level ,ostream& fout) {
	   if(t!=_eNode){
			if( (t->_left != 0)&&(t->_left!=_eNode)) {
				Recprint(t->_left,level+1,fout);
			}
			cout<< setw(level*3)<<"["<<level<<"] "<< t->_data<<endl; 
		   if( (t->_right != 0)&&(t->_right!=_eNode)) {
				Recprint(t->_right,level+1,fout);
		   }
	  }
   }

template <class T>
   bool BSTree<T>::leftRot(BSTreeNode<T>* x ) {
	   if( (x!=_eNode) && (x->_right!=0) && (x->_right!=_eNode) ){
			BSTreeNode<T>* y=x->_right;
			if(x!=_root){
				//cout<<"1-1"<<endl;
				BSTreeNode<T>* p=x->_pare;
				if(p->_left==x){
					//cout<<"1-1-1"<<endl;
					p->_left=y;
				}
				else if(p->_right==x){
					//cout<<"1-1-2"<<endl;//OK
					p->_right=y;
				}
				else{
					assert(0);
				}
				y->_pare=p;
			}else{
				//cout<<"1-2"<<endl;//OK
				_root=y;
				y->_pare=0;
			}
			BSTreeNode<T>* l=y->_left;
			if(l!=0){
				//cout<<"1-3"<<endl;//OK
				l->_pare=x;
			}
			//cout<<"1-4"<<endl;//OK
			x->_right=l;
			x->_pare=y;
			y->_left=x;
			return true;
		}
		else{
			return false;
			//cout<<"1-5"<<endl;//OK
		}
   	}
template <class T>
   bool BSTree<T>::rightRot(BSTreeNode<T>* x ) {
   	//	cout<<"rotate:x="<<x->_data<<endl;
	   if( (x!=_eNode) && (x->_left!=0)){
			BSTreeNode<T>* y=x->_left;
	//		cout<<"rotate:y="<<y->_data<<endl;
			if(x!=_root){
	//			cout<<"2-1"<<endl;
				BSTreeNode<T>* p=x->_pare;
				if(p->_right==x){
	//				cout<<"2-2-1"<<endl;//OK
					p->_right=y;
				}
				else if(p->_left==x){
	//				cout<<"2-2-2"<<endl;//OK
					p->_left=y;
				}
				else{
					assert(0);
				}
				y->_pare=p;
			}else{
	//			cout<<"2-2"<<endl;//OK
				_root=y;
				y->_pare=0;
			}
			BSTreeNode<T>* l=y->_right;
			if(l!=0){
	//			cout<<"2-3"<<endl;
				l->_pare=x;
			}
	//		cout<<"2-4"<<endl;//OK
			x->_left=l;
			x->_pare=y;
			y->_right=x;
	//		cout<<"x->_pare="<<x->_pare->_data<<endl;
			//cout<<"y->_pare="<<y->_pare->_data<<endl;
	//		cout<<"_root="<<_root->_data<<endl;
			return true;
		}
		else{
			return false;
		//	cout<<"2-5"<<endl;//OK
		}
   	}



template <class T>
bool BSTree<T>::rotate(size_t id,bool right ){
   iterator pos=begin();
   //cout<<"id:"<<id<<endl;
   	if(id>=size()){
		id=size()-1;
	}
	for(size_t i=0;i<id;i++){
		pos++;
	}
		return	rotate(pos,right);
   }

template <class T>
bool BSTree<T>::rotate(iterator pos,bool right ){

	if(!right){
	//	cout<<"1-0"<<endl;
		//cout<<"pos._node.data"<<pos._node->_data<<endl;
		return leftRot(pos._node);
	}
	else{
		//cout<<"2-0"<<endl;
		//cout<<"pos._node.data"<<pos._node->_data<<endl;
		return rightRot(pos._node);
	}
   }

template <class T>
bool BSTree<T>::erase(size_t id){
	   iterator pos=begin();
	   //cout<<"1"<<endl;
		if(id>=size()){
			id=size()-1;
		}
		for(size_t i=0;i<id;i++){
			pos++;
		}
		return erase(pos);
	}
#endif // BST_H
