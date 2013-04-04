#ifndef BSTREE_H
#define BSTREE_H
template <class T> class BSTree;


template <class T>
class BSTreeNode{
   
   friend class BSTree<T>;
  	private: 
	BSTreeNode(T* d, BSTreeNode<T>* p = 0, BSTreeNode<T>* l = 0, BSTreeNode<T>* r = 0 ):
      _data(d), _pare(p), _left(l), _right(r)  {}

//   DListNode(const T& d, DListNode* p = 0, DListNode* n = 0):
//      _data(d), _prev(p), _next(n) {}
	T*                _data;
    BSTreeNode<T>*   _pare;
    BSTreeNode<T>*   _left;
    BSTreeNode<T>*   _right;

};

template <class T>
class BSTree{
public:
   BSTree() {
      _root = new BSTreeNode<T>(T());
      _eNode = _root;
      _size=0;
      //_root->_left = _root->_right =0; // _head is a dummy node
   }
   ~BSTree() { clear(); delete _root; }

   void del(BSTreeNode<T>* x)
    {
        if (x->_left!=0)
            {//cout<<11<<endl;
            del(x->_left);}
        if (x->_right!=0)
            {//cout<<12<<endl;
            del(x->_right);}
        delete x;
    }
   void clear() 
    {
		if(_eNode->_pare!=0)
		{_eNode->_pare->_right=0;}//enode detach
		if(_size>0)
		{    del(_root);}
		else
		{delete _root;}
			_root = new BSTreeNode<T>(T());//cout<<2<<endl;
			_eNode =_root; //new BSTreeNode<T>(T(),_root);
			_size=0;//cout<<3<<endl;
	} // delete all nodes except for the dummy node



private:
	BSTreeNode<T>*   _root;
    static BSTreeNode<T>*   _eNode;//tail;
    size_t _size;
};

#endif
