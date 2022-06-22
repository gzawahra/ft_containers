#ifndef MAP_HPP
# define MAP_HPP

# include "includes/containers.hpp"
// #include <chrono>
// #include <thread>
// red-black binary search tree map implementation :
// 1. a node is either red or black (binary)
// 2. root and leaves must be black
// 3. if a node is red it's children are black
// 4. all paths from a node to its NIL descendants
//    contain the same number of black nodes
// 5. items to the left are always smaller
// 

namespace ft
{

template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< ft::pair<const Key, T> > >
class map {
public:

	//////////
	// Node //
	//////////

	typedef struct				s_node
	{
		ft::pair<const Key, T>	data;
		struct s_node *			left;
		struct s_node *			right;
		struct s_node *			parent;
		bool					color;

		s_node (ft::pair<const Key, T> data) : data(data) {}
		const Key &	key (void)	{ return (data.first); }
		T &			val (void)	{ return (data.second); }
	}							node;

	///////////////////////
	// Iterator subclass //
	///////////////////////

	template <bool IsConst>
	class mapIterator {
	public:
		// Member types
		typedef					ft::pair<const Key, T>										pair_type;
		typedef typename		ft::conditional<IsConst, const pair_type, pair_type>::type	value_type;
		typedef typename		ft::conditional<IsConst, const node, node>::type			node_type;
		typedef					std::ptrdiff_t												difference_type;
		typedef					std::size_t													size_type;
		// -structors
		mapIterator				(void)														{ _ptr = NULL; }
		mapIterator				(node_type * const ptr)										{ _ptr = ptr; }
		~mapIterator			(void)														{}
		// Const stuff
		template <bool B>		mapIterator
			(const mapIterator<B> & x, typename ft::enable_if<!B>::type* = 0)				{ _ptr = x.getPtr(); }

		// Assignment
		mapIterator &			operator=	(const mapIterator & x)							{ _ptr = x.getPtr(); return (*this); }
		// Comparison
		template <bool B> bool	operator==	(const mapIterator<B> & x) const				{ return (_ptr == x.getPtr()); }
		template <bool B> bool	operator!=	(const mapIterator<B> & x) const				{ return (_ptr != x.getPtr()); }
		// -crementation
		mapIterator &			operator++	(void)											{ this->nextNode(); return (*this); }
		mapIterator &			operator--	(void)											{ this->prevNode(); return (*this); }
		mapIterator				operator++	(int)											{ mapIterator<IsConst> x(*this); this->nextNode(); return (x); }
		mapIterator				operator--	(int)											{ mapIterator<IsConst> x(*this); this->prevNode(); return (x); }
		// Dereference
		value_type &			operator*	(void) const									{ return (_ptr->data); }
		value_type *			operator->	(void) const									{ return (&_ptr->data); }
		// Member functions
		node_type *				getPtr		(void) const									{ return (_ptr); }

	private:
		node_type *				_ptr;

		// get next node pointer in binary tree
		void nextNode (void)
		{
			if (_ptr->right != _ptr->right->left)
			{
				_ptr = _ptr->right;
				while (_ptr->left != _ptr->left->left)
						_ptr = _ptr->left;
			}
			else
			{
				while (_ptr == _ptr->parent->right && _ptr != _ptr->parent)
					_ptr = _ptr->parent;
				_ptr = _ptr->parent;
			}
		}

		// get previous node pointer in binary tree
		void prevNode (void)
		{
			if (_ptr == _ptr->parent)
			{
				while (_ptr->right != _ptr->right->left)
					_ptr = _ptr->right;
			}
			else if (_ptr->left != _ptr->left->left)
			{
				_ptr = _ptr->left;
				while (_ptr->right != _ptr->right->left)
					_ptr = _ptr->right;
			}
			else
			{
				while (_ptr == _ptr->parent->left && _ptr != _ptr->parent)
					_ptr = _ptr->parent;
				_ptr = _ptr->parent;
			}
		}
	}; // Iterator

	//////////////////
	// Member types //
	//////////////////

	class		ValueCompare;

	typedef		Key												key_type;
	typedef		T												mapped_type;
	typedef		ft::pair<const key_type, mapped_type>			value_type;
	typedef		Compare											key_compare;
	typedef		ValueCompare									value_compare;
	typedef		typename Alloc::template rebind<node>::other	allocator_type;
	typedef		typename allocator_type::reference				reference;
	typedef		typename allocator_type::const_reference		const_reference;
	typedef		typename allocator_type::pointer				pointer;
	typedef		typename allocator_type::const_pointer			const_pointer;
	typedef		mapIterator<false>								iterator;
	typedef		mapIterator<true>								const_iterator;
	typedef		ft::reverse_iterator<iterator>					reverse_iterator;
	typedef		ft::reverse_iterator<const_iterator>			const_reverse_iterator;
	typedef		typename mapIterator<false>::difference_type	difference_type;
	typedef		typename mapIterator<false>::size_type			size_type;

	///////////////////
	// Value compare //
	///////////////////

	class ValueCompare {
	public:
		friend			class			map;
		typedef			bool			result_type;
		typedef			value_type		first_argument_type;
		typedef			value_type		second_argument_type;
		bool			operator()		(const value_type & x, const value_type & y) const
			{ return (comp(x.first, y.first)); }
	protected:
		ValueCompare	(Compare c)		: comp(c) {}
		Compare			comp;
	};

	//////////////////
	// Constructors //
	//////////////////

	//	Constructs an empty container, with no elements.
	explicit map (const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type())
	{
		_alloc = alloc;
		_comp = comp;
		this->_new_nil_node();
	}

	//	Constructs a container with as many elements as the range [first,last), with each element constructed from 
	//	its corresponding element in that range.
	template <class InputIterator>
	map (InputIterator first, InputIterator last, const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type(),
	typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
	{
		_alloc = alloc;
		_comp = comp;
		this->_new_nil_node();

		while (first != last)
			this->insert(*first++);
	}

	//	Constructs a container with a copy of each of the elements in x.
	map (const map & x)
	{
		this->_new_nil_node();
		*this = x;
	}

	/////////////////
	// Destructors //
	/////////////////

	// This destroys all container elements, and deallocates all the storage 
	//	capacity allocated by the map container using its allocator.
	~map (void)
	{
		this->clear();
		_alloc.destroy(_nil);
		_alloc.deallocate(_nil, 1);
	}

	/////////////////////////
	// Assignment operator //
	/////////////////////////

	// Copies all the elements from x into the container, changing its size accordingly.
	// The container preserves its current allocator, which is used to allocate additional storage if needed.
	map & operator= (const map & x)
	{
		if (this == &x)
			return (*this);

		this->clear();
		_alloc = x._alloc;
		_comp = x._comp;

		for (const_iterator it = x.begin() ; it != x.end() ; it++)
			this->insert(*it);
		return (*this);
	}

	///////////////
	// Iterators //
	///////////////

	// Returns an iterator referring to the first element in the map container.
	iterator begin (void)
	{
		return (iterator(this->_leftmost(_nil->right)));
	}

	const_iterator begin (void) const
	{
		return (const_iterator(this->_leftmost(_nil->right)));
	}

	// Returns an iterator referring to the past-the-end element in the map container.
	iterator end (void)
	{
		return (iterator(_nil));
	}

	const_iterator end (void) const
	{
		return (const_iterator(_nil));
	}

	///////////////////////
	// Reverse iterators //
	///////////////////////

	// Returns a reverse iterator pointing to the last element in the container 
	//	(i.e., its reverse beginning).
	reverse_iterator rbegin (void)
	{
		return (reverse_iterator(_nil));
	}

	const_reverse_iterator rbegin (void) const
	{
		return (const_reverse_iterator(_nil));
	}

	// Returns a reverse iterator pointing to the theoretical element right before the first element
	// in the map container (which is considered its reverse end).
	reverse_iterator rend (void)
	{
		return (reverse_iterator(this->_leftmost(_nil->right)));
	}

	const_reverse_iterator rend (void) const
	{
		return (const_reverse_iterator(this->_leftmost(_nil->right)));
	}

	//////////////
	// Capacity //
	//////////////

	// Returns whether the map container is empty (i.e. whether its size is 0).
	bool empty (void) const
	{
		return (_nil == _nil->right);
	}

	// Returns the number of elements in the map container.
	size_type size (void) const
	{
		size_type n = 0;
		for (const_iterator it = this->begin() ; it != this->end() ; it++)
			n++;
		return (n);
	}

	// Returns the maximum number of elements that the map container can hold.
	size_type max_size (void) const
	{
		return (_alloc.max_size());
	}

	///////////////////
	// Member access //
	///////////////////

	// If k matches the key of an element in the container, the function returns a 
	// reference to its mapped value.
	mapped_type & operator[] (const key_type & k)
	{
		this->insert(ft::make_pair(k, mapped_type()));
		return (this->find(k)->second);
	}

	/////////////////////////
	// Insertion modifiers //
	/////////////////////////

	// Extends the container by inserting new elements, effectively increasing the container size by 
	//	the number of elements inserted.
	ft::pair<iterator,bool> insert (const value_type & val)
	{
		iterator it;
		if (this->count(val.first))
		{
			it = this->find(val.first);
			return (ft::make_pair(it, false));
		}
		else
		{
			it = iterator(this->_new_node(val));
			return (ft::make_pair(it, true));
		}

	}

	// The function optimizes its insertion time if position points to the element that 
	//	will precede the inserted element.
	iterator insert (iterator position, const value_type & val)
	{
		(void)position;
		return (this->insert(val).first);
	}

	// Copies of the elements in the range [first,last) are inserted in the container.
	template <class InputIterator>
	void insert (InputIterator first, InputIterator last,
	typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
	{
		while (first != last)
			this->insert(*first++);
	}

	///////////////////////
	// Erasure modifiers //
	///////////////////////

	// Removes from the map container either a single element
	// This effectively reduces the container size by the number of elements removed, which are destroyed.
	void erase (iterator position)
	{
		node * ptr = position.getPtr();

		if (ptr->left != _nil && ptr->right != _nil)
		{
			position--;
			this->_swap_nodes(ptr, position.getPtr());
			this->erase(ptr);
		}
		else
		{
			node * child = (ptr->left != _nil) ? ptr->left : ptr->right;

			if (child != _nil)
				child->parent = ptr->parent;
			if (ptr->parent->left == ptr)
				ptr->parent->left = child;
			else
				ptr->parent->right = child;
			this->_removeNode(ptr, child);
		}
	}

	// erase using unique key
	size_type erase (const key_type & k)
	{
		if (this->count(k))
		{
			this->erase(this->find(k));
			return (1);
		}
		return (0);
	}
	
	//  or a range of elements ([first,last)).
	void erase (iterator first, iterator last)
	{
		for (iterator it = first++ ; it != last ; it = first++)
			this->erase(it);
	}

	//////////////////////
	// Common modifiers //
	//////////////////////

	// Exchanges the content of the container by the content of x, which is 
	//	another map of the same type. Sizes may differ.
	void swap (map & x)
	{
		ft::swap(_alloc, x._alloc);
		ft::swap(_comp, x._comp);
		ft::swap(_nil, x._nil);
	}

	// Removes all elements from the map container (which are destroyed), 
	//	leaving the container with a size of 0.
	void clear (void)
	{
		iterator first = this->begin();
		for (iterator it = first++ ; it != this->end(); it = first++)
			this->erase(it);
	}
	
	///////////////
	// Observers //
	///////////////

	// Returns a copy of the comparison object used by the container to compare keys.
	key_compare key_comp (void) const
	{
		return (key_compare());
	}

	// Returns a comparison object that can be used to compare two elements to get whether 
	// the key of the first one goes before the second.
	value_compare value_comp (void) const
	{
		return (value_compare(_comp));
	}

	///////////////////////
	// Search operations //
	///////////////////////

	// Searches the container for an element with a key equivalent to k and returns an 
	//	iterator to it if found, otherwise it returns an iterator to map::end.
	iterator find (const key_type & k)
	{
		if (this->count(k))
			return (iterator(this->_find_node(_nil->right, k)));
		else
			return (this->end());
	}

	const_iterator find (const key_type & k) const
	{
		if (this->count(k))
			return (const_iterator(this->_find_node(_nil->right, k)));
		else
			return (this->end());
	}

	// Searchs the container for elements with a key equivalent to k and returns the number of matches.
	size_type count (const key_type & k) const
	{
		node*	currentNode;
		ft::pair<const Key, T>*		currentPair;	
		currentNode = this->_nil->right;

		while (currentNode != _nil)
		{
			currentPair = &currentNode->data;	
			if (_comp(k, currentPair->first))
				currentNode = currentNode->left;
			else if (_comp(currentPair->first, k))
				currentNode = currentNode->right;
			else
				return (1);
		}
		return (0);
	}

	//////////////////////
	// Bound operations //
	//////////////////////

	// Returns an iterator pointing to the first element in the container whose key is not considered to go
	// before k (i.e., either it is equivalent or goes after).
	iterator lower_bound (const key_type & k)
	{
		iterator it = this->begin();
		while (this->_comp(it->first, k) && it != this->end())
			it++;
		return (it);
	}

	const_iterator lower_bound (const key_type & k) const
	{
		const_iterator it = this->begin();
		while (this->_comp(it->first, k) && it != this->end())
			it++;
		return (it);
	}

	//	Returns an iterator pointing to the first element in the container 
	//	whose key is considered to go after k.
	iterator upper_bound (const key_type & k)
	{
		iterator it = this->begin();
		while (this->_comp(k, it->first) == false && it != this->end())
			it++;
		return (it);
	}

	const_iterator upper_bound (const key_type & k) const
	{
		const_iterator it = this->begin();
		while (this->_comp(k, it->first) == false && it != this->end())
			it++;
		return (it);
	}

	// Returns the bounds of a range that includes all the elements in the container which 
	// have a key equivalent to k.
	ft::pair<iterator,iterator> equal_range (const key_type & k)
	{
		return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
	}

	ft::pair<const_iterator,const_iterator> equal_range (const key_type & k) const
	{
		return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
	}

	///////////////
	// Allocator //
	///////////////

	// Returns a copy of the allocator object associated with the map.
	allocator_type get_allocator (void) const
	{
		return (allocator_type());
	}

	///////////////////////
	// Private functions //
	///////////////////////
private:
	// create new end node
	void _new_nil_node (void)
	{
		_nil = _alloc.allocate(1);
		this->_construct(_nil);
		_nil->color = BLACK_;
	}

	// create new node
	node * _new_node (const value_type & val = value_type())
	{
	
		node * new_node = _alloc.allocate(1);
		this->_construct(new_node, val);
		node * parent = this->_find_parent(_nil->right, val.first);
		if (parent == _nil || !this->_comp(val.first, parent->key()))
		{
			parent->right = new_node;
		}
		else
		{
			parent->left = new_node;						
		}
		new_node->parent = parent;
		this->_insertRB(new_node);
		return (new_node);
	}

	// construct a new node 
	void _construct (node * ptr, const value_type & val = value_type())
	{
		node tmp(val);
		tmp.left = _nil;
		tmp.right = _nil;
		tmp.parent = _nil;
		tmp.color = RED_;
		_alloc.construct(ptr, tmp);
	}

	// swap two nodes
	void _swap_nodes (node * a, node * b)
	{
		if (a->left != b && a->left != _nil)
			a->left->parent = b;
		if (a->right != b && a->right != _nil)
			a->right->parent = b;
		if (a->parent != b && a->parent != _nil)
		{
			if (a->parent->left == a)
				a->parent->left = b;
			else
				a->parent->right = b;
		}

		if (b->left != a && b->left != _nil)
			b->left->parent = a;
		if (b->right != a && b->right != _nil)
			b->right->parent = a;
		if (b->parent != a && b->parent != _nil)
		{
			if (b->parent->left == b)
				b->parent->left = a;
			else
				b->parent->right = a;
		}

		if (a->parent == b)
			a->parent = a;
		if (a->left == b)
			a->left = a;
		if (a->right == b)
			a->right = a;
		if (b->parent == a)
			b->parent = b;
		if (b->left == a)
			b->left = b;
		if (b->right == a)
			b->right = b;

		ft::swap(a->parent, b->parent);
		ft::swap(a->left, b->left);
		ft::swap(a->right, b->right);
		ft::swap(a->color, b->color);

		if (_nil->right == a)
			_nil->right = b;
		else if (_nil->right == b)
			_nil->right = a;
	}

	// remove node, destroy, and deallocate.
	void _removeNode (node * ptr, node * child)
	{
		this->_deleteRB(ptr, child);
		_alloc.destroy(ptr);
		_alloc.deallocate(ptr, 1);
	}

	// search a certain node corresponding to a given key.
	node * _find_node (node * current, const key_type & k) const
	{
		if (current == _nil || this->_equal(current->key(), k))
			return (current);
		else if (this->_comp(k, current->key()))
			return (this->_find_node(current->left, k));
		else
			return (this->_find_node(current->right, k));
	}

	// _find a given node's parent according to a key.
	node * _find_parent (node * current, const key_type & k) const
	{
		if (!this->_comp(k, current->key()))
		{
			if (current->right == _nil)
				return (current);
			else
				return (this->_find_parent(current->right, k));
		}
		else
		{
			if (current->left == _nil)
				return (current);
			else
				return (this->_find_parent(current->left, k));
		}
	}

	// find leftmost ( lowest node) in the RB tree.
	node * _leftmost (node * root) const
	{
		while (root->left != root->left->left)
			root = root->left;
		return (root);
	}

	// check if 
	bool _equal (const key_type & lhs, const key_type & rhs) const
	{
		return (this->_comp(lhs, rhs) == false && this->_comp(rhs, lhs) == false);
	}

	////////////////////////
	// Red and Black Tree //
	////////////////////////

	// insert  node into tree and balance the tree with LR / RR / RL / LL.
	void _insertRB (node * x)
	{
		node * parent = x->parent;
		node * grandparent = parent->parent;
		node * uncle = (grandparent->right == parent) ? grandparent->left : grandparent->right;

		if (parent == _nil)
		{
			x->color = BLACK_;						
		}
		else if (parent->color == BLACK_)
		{
			return ;
		}

		else if (uncle->color == RED_)
		{
			parent->color = BLACK_;
			uncle->color = BLACK_;
			grandparent->color = RED_;
			this->_insertRB(grandparent);
		}
		else if (uncle->color == BLACK_)
		{
			if (grandparent->left->left == x || grandparent->right->right == x)
			{
				if (grandparent->left->left == x)
					this->_LL(grandparent, parent);
				else if (grandparent->right->right == x)
					this->_RR(grandparent, parent);
				ft::swap(grandparent->color, parent->color);
			}
			else
			{
				if (grandparent->left->right == x)
					this->_LR(grandparent, parent, x);
				else if (grandparent->right->left == x)
					this->_RL(grandparent, parent, x);
				ft::swap(grandparent->color, x->color);
			}
		}
	}

	// 
	void _deleteRB (node * v, node * u)
	{	
		if (v->color == RED_ || u->color == RED_)
			u->color = BLACK_;
		else
			this->_doubleBlack(u, v->parent);
	}

	// 
	void _doubleBlack (node * u, node * parent)
	{	
		node * sibling = (parent->left != u) ? parent->left : parent->right;

		if (u == _nil->right || _nil == _nil->right || parent != _nil->left)
			return ;
		else if (sibling->color == BLACK_ && (sibling->left->color == RED_ || sibling->right->color == RED_))
		{
			if (sibling == parent->left && sibling->left->color == RED_ )
				this->_LL(parent, sibling);
			else if (sibling == parent->left && sibling->right->color == RED_)
				this->_LR(parent, sibling, sibling->right);
			else if (sibling == parent->right && sibling->right->color == RED_)
				this->_RR(parent, sibling);
			else if (sibling == parent->right && sibling->left->color == RED_)
				this->_RL(parent, sibling, sibling->left);
			if (sibling->left->color == RED_)
				sibling->left->color = BLACK_;
			else
				sibling->right->color = BLACK_;
		}
		else if (sibling->color == BLACK_)
		{
			sibling->color = RED_;
			if (parent->color == RED_)
				parent->color = BLACK_;
			else if(_nil != _nil->right)
				this->_doubleBlack(parent, parent->parent);
			else
				return;
		}
		else if (sibling->color == RED_)
		{
			if (sibling == parent->left)
				this->_LL(parent, sibling);
			else
				this->_RR(parent, sibling);
			ft::swap(parent->color, sibling->color);
				this->_doubleBlack(u, parent);
		}
	}

	// tree manipulation fonctions to balance 
	// the red/black tree.
	void _LL (node * grandparent, node * parent)
	{
		if (grandparent->parent->right == grandparent)
			grandparent->parent->right = parent;
		else
			grandparent->parent->left = parent;
		if (parent->right != _nil)
			parent->right->parent = grandparent;
		grandparent->left = parent->right;
		parent->parent = grandparent->parent;
		grandparent->parent = parent;
		parent->right = grandparent;
	}

	void _RR (node * grandparent, node * parent)
	{
		if (grandparent->parent->right == grandparent)
			grandparent->parent->right = parent;
		else
			grandparent->parent->left = parent;
		if (parent->left != _nil)
			parent->left->parent = grandparent;
		
		grandparent->right = parent->left;
		parent->parent = grandparent->parent;
		grandparent->parent = parent;
		parent->left = grandparent;
	}

	void _LR (node * grandparent, node * parent, node * x)
	{
		if (grandparent->parent->right == grandparent)
			grandparent->parent->right = x;
		else
			grandparent->parent->left = x;
		if (x->left != _nil)
			x->left->parent = parent;
		if (x->right != _nil)
			x->right->parent = grandparent;
		grandparent->left = x->right;
		parent->right = x->left;
		x->parent = grandparent->parent;
		grandparent->parent = x;
		parent->parent = x;
		x->left = parent;
		x->right = grandparent;
	}

	void _RL (node * grandparent, node * parent, node * x)
	{
		if (grandparent->parent->right == grandparent)
			grandparent->parent->right = x;
		else
			grandparent->parent->left = x;
		if (x->left != _nil)
			x->left->parent = grandparent;
		if (x->right != _nil)
			x->right->parent = parent;
		grandparent->right = x->left;
		parent->left = x->right;
		x->parent = grandparent->parent;
		grandparent->parent = x;
		parent->parent = x;
		x->left = grandparent;
		x->right = parent;
	}

	//////////////////////
	// Member variables //
	//////////////////////

	allocator_type		_alloc;
	key_compare			_comp;
	node *				_nil;
}; // Map

	//////////////////////////
	// Relational operators //
	//////////////////////////

	template <class Key, class T, class Compare, class Alloc>
	bool operator== (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
	{
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<  (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
	{
		return (!(lhs == rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
	{
		return (!(rhs < lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>  (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
	{
		return (!(lhs < rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc> & x, map<Key,T,Compare,Alloc> & y)
	{
		x.swap(y);
	}

} // Namespace ft

#endif
