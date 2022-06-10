#ifndef RBT_HPP
#define RBT_HPP

#include <ostream>
#include <stdexcept>
#include "Transformators.hpp"

#ifdef COLORFUL
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <cstring>
#include <windows.h>
#undef max

namespace
{
  void setcol(unsigned int a)
  {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, a);
  }
}
#endif

#ifdef TEST_MODE
long long iter = 0;
#endif

template < typename Key_t, typename Value_t, typename KeyComp >
class RBT
{
public:
  RBT();
  RBT(const RBT< Key_t, Value_t, KeyComp >& other);
  RBT(RBT< Key_t, Value_t, KeyComp >&& other) noexcept;

  RBT< Key_t, Value_t, KeyComp >& operator=(const RBT< Key_t, Value_t, KeyComp >& other);
  RBT< Key_t, Value_t, KeyComp >& operator=(RBT< Key_t, Value_t, KeyComp >&& other) noexcept;

  ~RBT();

  size_t getHeight() const;

  bool isThere(const Key_t& key) const;
  bool insert(const Key_t& key, const Value_t& value);

  template < class Transformator >
  void insert_or_transform(const Key_t& key, const Value_t& value, Transformator trans);
  bool remove(const Key_t& key);

  void printValues(std::ostream& out) const;
  void printTree(std::ostream& out) const;
  Value_t& at(const Key_t& key);

  bool empty() const;
private:
  struct Node
  {
    Node();
    bool isNIL();
    ~Node();

    Key_t* key_;
    Value_t* value_;
    bool isBlack;

    Node* left_;
    Node* right_;
    Node* p_;
  };

  Node* root_;

  void copyTree(Node*& in, Node* from);

  size_t getHeight(const Node* node) const;

  Node* searchNode(const Key_t& key) const;
  void deleteTreePart(Node* root);

  Node* insertNode(const Key_t& key, const Value_t& value);
  bool insertNode(const Key_t& key, const Value_t& value, Node*& interacted);
  void printPart(const std::string& prefix, Node* node, bool isLeft, std::ostream& out) const;
  
  void inorderWalk(Node* node, std::ostream& out) const;

  Node* getGrandpa(Node* grandson);
  Node* getUncle(Node* nephew);
  Node* getSibling(Node* n);
  void makeLeftRotation(Node* n);
  void makeRightRotation(Node* n);
  
  void insertCase1(Node* inserted);
  void insertCase2(Node* inserted);
  void insertCase3(Node* inserted);
  void insertCase4(Node* inserted);
  void insertCase5(Node* inserted);

  void replaceNode(Node* n, Node* child);
  void deleteOneChild(Node* n);
  void deleteCase1(Node* n);
  void deleteCase2(Node* n);
  void deleteCase3(Node* n);
  void deleteCase4(Node* n);
  void deleteCase5(Node* n);
  void deleteCase6(Node* n);
};

template< typename K, typename V, typename C >
RBT< K, V, C >::Node::Node():
  key_(nullptr),
  value_(nullptr),
  p_(nullptr),
  left_(nullptr),
  right_(nullptr),
  isBlack(true)
{}

template< typename Key_t, typename Value_t, typename KeyComp >
bool RBT< Key_t, Value_t, KeyComp >::Node::isNIL()
{
  return static_cast< bool >(!key_) && static_cast< bool >(!value_);
}

template< typename K, typename V, typename C >
RBT< K, V, C >::Node::~Node()
{
  delete value_;
  delete key_;
}

template< typename K, typename V, typename C >
RBT< K, V, C >::RBT():
  root_(new Node())
{}

template< typename K, typename V, typename C >
RBT< K, V, C >::RBT(const RBT< K, V, C >& other):
  root_(new Node())
{
  copyTree(root_, other.root_);
}

template< typename K, typename V, typename C >
RBT< K, V, C >::RBT(RBT< K, V, C >&& other) noexcept:
  root_(nullptr)
{
  std::swap(root_, other.root_);
}


template< typename K, typename V, typename C >
RBT< K, V, C >& RBT< K, V, C >::operator=(const RBT< K, V, C >& other)
{
  if (this != &other)
  {
    RBT< K, V, C > temp(other);
    std::swap(root_, temp.root_);
  }
  return *this;
}

template< typename K, typename V, typename C >
RBT< K, V, C >& RBT< K, V, C >::operator=(RBT< K, V, C >&& other) noexcept
{
  if (this != &other)
  {
    std::swap(root_, other.root_);
  }
  return *this;
}

template< typename K, typename V, typename C >
RBT< K, V, C >::~RBT()
{
  if (root_)
  {
    deleteTreePart(root_);
  }
}

template<typename Key_t, typename Value_t, typename KeyComp>
size_t RBT< Key_t, Value_t, KeyComp >::getHeight() const
{
  return getHeight(root_);
}

template< typename Key_t, typename Value_t, typename KeyComp >
bool RBT< Key_t, Value_t, KeyComp >::isThere(const Key_t& key) const
{
  return static_cast< bool >(searchNode(key));
}

template< typename Key_t, typename Value_t, typename KeyComp >
bool RBT< Key_t, Value_t, KeyComp >::remove(const Key_t& key)
{
  Node* forDelete = searchNode(key);
  if (forDelete && root_->left_->isNIL() && root_->right_->isNIL())
  {
    delete root_->left_;
    delete root_->right_;
    delete root_->key_;
    delete root_->value_;
    root_->left_ = nullptr;
    root_->right_ = nullptr;
    root_->key_ = nullptr;
    root_->value_ = nullptr;
#ifdef TEST_MODE
    iter += 8;
#endif
    return true;
  }

  Node* tempDel = nullptr;
#ifdef TEST_MODE
  iter += 6;
#endif
  if (forDelete)
  {
#ifdef TEST_MODE
    iter += 1;
#endif
    if (!forDelete->right_->isNIL())
    {
      tempDel = forDelete;
      tempDel = tempDel->right_;
#ifdef TEST_MODE
      iter += 2;
#endif
      while (!tempDel->left_->isNIL())
      {
        tempDel = tempDel->left_;
#ifdef TEST_MODE
        iter += 2;
#endif
      }
    }
    else if (!forDelete->left_->isNIL())
    {
      tempDel = forDelete;
      tempDel = tempDel->left_;
#ifdef TEST_MODE
      iter += 3;
#endif
      while (!tempDel->right_->isNIL())
      {
        tempDel = tempDel->right_;
#ifdef TEST_MODE
        iter += 2;
#endif
      }
    }
    else
    {
      tempDel = forDelete;
#ifdef TEST_MODE
      iter += 1;
#endif
    }
    std::swap(forDelete->key_, tempDel->key_);
    std::swap(forDelete->value_, tempDel->value_);
#ifdef TEST_MODE
    iter += 2;
#endif
    deleteOneChild(tempDel);

    return true;
  }
  else
  {
    return false;
  }
}

template< typename Key_t, typename Value_t, typename KeyComp >
void RBT< Key_t, Value_t, KeyComp>::printValues(std::ostream& out) const
{
  if (!root_->isNIL())
  {
    inorderWalk(root_, out);
  }
}

template< typename Key_t, typename V, typename C >
void RBT< Key_t, V, C >::printTree(std::ostream& out) const
{
  printPart("", root_, true, out);
}

template< typename Key_t, typename Value_t, typename KeyComp >
Value_t& RBT< Key_t, Value_t, KeyComp >::at(const Key_t& key)
{
  Node* totalNode = searchNode(key);
  if (totalNode)
  {
    return *totalNode->value_;
  }
  else
  {
    throw std::out_of_range("No element with such key\n");
  }
}

template< typename Key_t, typename Value_t, typename KeyComp >
bool RBT< Key_t, Value_t, KeyComp >::empty() const
{
  return root_->isNIL();
}

template< typename K, typename V, typename C >
bool RBT< K, V, C >::insert(const K& key, const V& value)
{
  Node* forBalance = insertNode(key, value);
#ifdef TEST_MODE
  iter += 2;
#endif
  if (root_->isNIL())
  {
    root_ = forBalance;
#ifdef TEST_MODE
    iter += 1;
#endif
  }
#ifdef TEST_MODE
  iter += 1;
#endif
  if (forBalance)
  {
    insertCase1(forBalance);
    return true;
  }
  return false;
}

template< typename Key_t, typename Value_t, typename KeyComp >
template< class Transformator >
void RBT< Key_t, Value_t, KeyComp >::insert_or_transform(const Key_t& key, const Value_t& value, Transformator trans)
{
  Node* forBalance = nullptr;
  bool isAlreadyIn = !insertNode(key, value, forBalance);
  if (root_->isNIL())
  {
    root_ = forBalance;
  }
  if (!isAlreadyIn)
  {
    insertCase1(forBalance);
  }
  else
  {
    Value_t tempValue = *forBalance->value_;
    delete forBalance->value_;

    forBalance->value_ = new Value_t(trans(tempValue));
  }
}

template< typename K, typename V, typename C >
typename RBT< K, V, C >::Node* RBT< K, V, C >::insertNode(const K& key, const V& value)
{
#ifdef TEST_MODE
  iter += 1;
#endif
  Node* interacted = nullptr;
  insertNode(key, value, interacted);
  return interacted;
}

template< typename Key_t, typename Value_t, typename KeyComp >
void RBT<Key_t, Value_t, KeyComp >::copyTree(Node*& in, Node* from)
{
  in->isBlack = from->isBlack;
  if (!from->isNIL())
  {
    in->key_ = new Key_t(*from->key_);
    in->value_ = new Key_t(*from->value_);
  }
  Node* left = nullptr;
  if (from->left_)
  {
    left = new Node();
    copyTree(left, from->left_);
  }
  Node* right = nullptr;
  if (from->right_)
  {
    right = new Node();
    copyTree(right, from->right_);
  }

  if (left)
  {
    left->p_ = in;
    in->left_ = left;
  }

  if (right)
  {
    in->right_ = right;
    right->p_ = in;
  }
}

template< typename K, typename V, typename C >
size_t RBT< K, V, C >::getHeight(const Node* node) const
{
  size_t leftHeight = 0;
  size_t rightHeight = 0;
  if (node->left_)
  {
    leftHeight = getHeight(node->left_) + 1;
  }
  if (node->right_)
  {
    rightHeight = getHeight(node->right_) + 1;
  }

  return std::max(leftHeight, rightHeight);
}

template< typename K, typename V, typename C >
typename RBT< K, V, C >::Node* RBT< K, V, C >::searchNode(const K& key) const
{
  Node* current = root_;
  while (!current->isNIL())
  {
    if (C{}(key, *current->key_))
    {
      current = current->left_;
    }
    else if (C{}(*current->key_, key))
    {
      current = current->right_;
    }
    else
    {
      return current;
    }
  }
  return nullptr;
}

template< typename K, typename V, typename C >
void RBT< K, V, C >::deleteTreePart(Node* root)
{
  if (root->left_)
  {
    deleteTreePart(root->left_);
  }
  if (root->right_)
  {
    deleteTreePart(root->right_);
  }

  delete root;
}

template< typename K, typename V, typename C >
void RBT< K, V, C >::makeLeftRotation(Node* n)
{
#ifdef TEST_MODE
  iter += 3;
#endif
  Node* pivot = n->right_;
  pivot->p_ = n->p_;
  if (n->p_)
  {
#ifdef TEST_MODE
    iter += 2;
#endif
    (n->p_->left_ == n ? n->p_->left_ : n->p_->right_) = pivot;
  }

#ifdef TEST_MODE
  iter += 2;
#endif
  n->right_ = pivot->left_;
  if (pivot->left_)
  {
#ifdef TEST_MODE
    iter += 1;
#endif
    pivot->left_->p_ = n;
  }

  n->p_ = pivot;
  pivot->left_ = n;
#ifdef TEST_MODE
  iter += 3;
#endif
  if (n == root_)
  {
#ifdef TEST_MODE
    iter += 1;
#endif
    root_ = pivot;
  }
}

template< typename K, typename V, typename C >
void RBT< K, V, C >::makeRightRotation(Node* n)
{
#ifdef TEST_MODE
  iter += 3;
#endif
  Node* pivot = n->left_;
  pivot->p_ = n->p_;
  if (n->p_)
  {
#ifdef TEST_MODE
    iter += 2;
#endif
    (n->p_->left_ == n ? n->p_->left_ : n->p_->right_) = pivot;
  }

#ifdef TEST_MODE
  iter += 2;
#endif
  n->left_ = pivot->right_;
  if (pivot->right_)
  {
#ifdef TEST_MODE
    iter += 1;
#endif
    pivot->right_->p_ = n;
  }

  n->p_ = pivot;
  pivot->right_ = n;
#ifdef TEST_MODE
  iter += 3;
#endif
  if (n == root_)
  {
#ifdef TEST_MODE
    iter += 1;
#endif
    root_ = pivot;
  }
}

template< typename Key_t, typename Value_t, typename KeyComp >
void RBT< Key_t, Value_t, KeyComp >::insertCase1(Node* inserted)
{
#ifdef TEST_MODE
  iter += 1;
#endif
  if (!inserted->p_)
  {
#ifdef TEST_MODE
    iter += 1;
#endif
    inserted->isBlack = true;
  }
  else
  {
    insertCase2(inserted);
  }
}

template< typename Key_t, typename Value_t, typename KeyComp >
void RBT< Key_t, Value_t, KeyComp >::insertCase2(Node* inserted)
{
#ifdef TEST_MODE
  iter += 1;
#endif
  if (!inserted->p_->isBlack)
  {
    insertCase3(inserted);
  }
}

template< typename Key_t, typename Value_t, typename KeyComp >
void RBT< Key_t, Value_t, KeyComp >::insertCase3(Node* inserted)
{
  Node* uncle = getUncle(inserted);
  Node* grandpa = nullptr;
#ifdef TEST_MODE
  iter += 4;
#endif

  if (uncle && !uncle->isBlack)
  {
    inserted->p_->isBlack = true;
    uncle->isBlack = true;
    grandpa = getGrandpa(inserted);
    grandpa->isBlack = false;
#ifdef TEST_MODE
    iter += 4;
#endif
    insertCase1(grandpa);
  }
  else
  {
    insertCase4(inserted);
  }
}

template< typename Key_t, typename Value_t, typename KeyComp >
void RBT< Key_t, Value_t, KeyComp >::insertCase4(Node* inserted)
{
  Node* grandpa = getGrandpa(inserted);
#ifdef TEST_MODE
  iter += 3;
#endif

  if (inserted == inserted->p_->right_ && inserted->p_ == grandpa->left_)
  {
    makeLeftRotation(inserted->p_);
    inserted = inserted->left_;
  }
  else if (inserted == inserted->p_->left_ && inserted->p_ == grandpa->right_)
  {
    makeRightRotation(inserted->p_);
    inserted = inserted->right_;
#ifdef TEST_MODE
    iter += 1;
#endif
  }
  insertCase5(inserted);
}

template< typename K, typename V, typename C >
void RBT< K, V, C >::insertCase5(Node* inserted)
{
  Node* grandpa = getGrandpa(inserted);
#ifdef TEST_MODE
  iter += 1;
#endif

  inserted->p_->isBlack = true;
  grandpa->isBlack = false;
#ifdef TEST_MODE
  iter += 4;
#endif
  if (inserted == inserted->p_->left_ && inserted->p_ == grandpa->left_)
  {
    makeRightRotation(grandpa);
  }
  else
  {
    makeLeftRotation(grandpa);
  }
}

template< typename K, typename V, typename C >
void RBT< K, V, C >::replaceNode(Node* n, Node* child)
{
  child->p_ = n->p_;
  (n == n->p_->left_ ? n->p_->left_ : n->p_->right_) = child;
}

template< typename Key_t, typename Value_t, typename KeyComp >
void RBT< Key_t, Value_t, KeyComp >::deleteOneChild(Node* n)
{
  Node* child = (n->right_->isNIL() ? n->left_ : n->right_);
#ifdef TEST_MODE
  iter += 2;
#endif
  replaceNode(n, child);
#ifdef TEST_MODE
  iter += 1;
#endif
  if (n->isBlack)
  {
#ifdef TEST_MODE
    iter += 1;
#endif
    if (!child->isBlack)
    {
      child->isBlack = true;
#ifdef TEST_MODE
      iter += 1;
#endif
    }
    else
    {
      deleteCase1(child);
    }
  }

#ifdef TEST_MODE
  iter += 1;
#endif
  delete n;
}

template< typename Key_t, typename Value_t, typename KeyComp >
void RBT< Key_t, Value_t, KeyComp >::deleteCase1(Node* n)
{
#ifdef TEST_MODE
  iter += 1;
#endif
  if (n->p_)
  {
    deleteCase2(n);
  }
}

template< typename Key_t, typename Value_t, typename KeyComp >
void RBT< Key_t, Value_t, KeyComp >::deleteCase2(Node* n)
{
  Node* s = getSibling(n);
#ifdef TEST_MODE
  iter += 2;
#endif
  if (!s->isBlack)
  {
    n->p_->isBlack = false;
    s->isBlack = true;
#ifdef TEST_MODE
    iter += 3;
#endif
    if (n == n->p_->left_)
    {
      makeLeftRotation(n->p_);
    }
    else
    {
      makeRightRotation(n->p_);
    }
  }
  deleteCase3(n);
}

template< typename Key_t, typename Value_t, typename KeyComp >
void RBT< Key_t, Value_t, KeyComp >::deleteCase3(Node* n)
{
  Node* s = getSibling(n);
#ifdef TEST_MODE
  iter += 5;
#endif
  if (n->p_->isBlack && s->isBlack && s->left_->isBlack && s->right_->isBlack)
  {
    s->isBlack = false;
#ifdef TEST_MODE
    iter += 1;
#endif
    deleteCase1(n->p_);
  }
  else
  {
    deleteCase4(n);
  }
}

template< typename Key_t, typename Value_t, typename KeyComp >
void RBT< Key_t, Value_t, KeyComp >::deleteCase4(Node* n)
{
  Node* s = getSibling(n);
#ifdef TEST_MODE
  iter += 5;
#endif
  if (!n->p_->isBlack && s->isBlack && s->left_->isBlack && s->right_->isBlack)
  {
    s->isBlack = false;
    n->p_->isBlack = true;
#ifdef TEST_MODE
    iter += 2;
#endif
  }
  else
  {
    deleteCase5(n);
  }
}

template< typename Key_t, typename Value_t, typename KeyComp >
void RBT< Key_t, Value_t, KeyComp >::deleteCase5(Node* n)
{
  Node* s = getSibling(n);
#ifdef TEST_MODE
  iter += 2;
#endif
  if (s->isBlack)
  {
#ifdef TEST_MODE
    iter += 3;
#endif
    if (n == n->p_->left_ && s->right_->isBlack && !s->left_->isBlack)
    {
      s->isBlack = false;
      s->left_->isBlack = true;
#ifdef TEST_MODE
      iter += 2;
#endif
      makeRightRotation(s);
    }
    else if (n == n->p_->right_ && s->left_->isBlack && !s->right_->isBlack)
    {
      s->isBlack = false;
      s->right_->isBlack = true;
#ifdef TEST_MODE
      iter += 5;
#endif
      makeLeftRotation(s);
    }
  }
  deleteCase6(n);
}

template< typename Key_t, typename Value_t, typename KeyComp >
void RBT< Key_t, Value_t, KeyComp >::deleteCase6(Node* n)
{
  Node* s = getSibling(n);
  s->isBlack = n->p_->isBlack;
  n->p_->isBlack = true;
#ifdef TEST_MODE
  iter += 4;
#endif

  if (n == n->p_->left_)
  {
    s->right_->isBlack = true;
#ifdef TEST_MODE
    iter += 1;
#endif
    makeLeftRotation(n->p_);
  }
  else
  {
    s->left_->isBlack = true;
#ifdef TEST_MODE
    iter += 1;
#endif
    makeRightRotation(n->p_);
  }
}


template< typename K, typename V, typename C >
bool RBT< K, V, C >::insertNode(const K& key, const V& value, Node*& interacted)
{
  if (root_->isNIL())
  {
    root_->key_ = new K(key);
    root_->value_ = new V(value);
    root_->left_ = new Node();
    root_->left_->p_ = root_;
    root_->right_ = new Node();
    root_->right_->p_ = root_;

#ifdef TEST_MODE
    iter += 7;
#endif
    interacted = root_;
    return true;
  }
  else
  {
    Node* current = root_;
#ifdef TEST_MODE
    iter += 1;
#endif
    while (true)
    {
      if (C{}(key, *current->key_))
      {
#ifdef TEST_MODE
        iter += 2;
#endif
        if (current->left_->isNIL())
        {
          current->left_->key_ = new K(key);
          current->left_->value_ = new V(value);
          current->left_->p_ = current;
          current->left_->isBlack = false;
          current->left_->left_ = new Node();
          current->left_->left_->p_ = current;
          current->left_->right_ = new Node();
          current->left_->right_->p_ = current;

#ifdef TEST_MODE
          iter += 9;
#endif
          interacted = current->left_;
          return true;
        }
        current = current->left_;
#ifdef TEST_MODE
        iter += 2;
#endif
      }
      else if (C{}(*current->key_, key))
      {
#ifdef TEST_MODE
        iter += 2;
#endif
        if (current->right_->isNIL())
        {
          current->right_->key_ = new K(key);
          current->right_->value_ = new V(value);
          current->right_->p_ = current;
          current->right_->isBlack = false;
          current->right_->left_ = new Node();
          current->right_->left_->p_ = current;
          current->right_->right_ = new Node();
          current->right_->right_->p_ = current;
#ifdef TEST_MODE
          iter += 9;
#endif
          interacted = current->right_;
          return true;
        }
        current = current->right_;
#ifdef TEST_MODE
        iter += 2;
#endif
      }
      else
      {
#ifdef TEST_MODE
        iter += 1;
#endif
        interacted = current;
        return false;
      }
    }
  }
}

template< typename K, typename V, typename C >
void RBT< K, V, C >::printPart(const std::string& prefix, Node* node, bool isLeft, std::ostream& out) const
{
  if (!node->isNIL())
  {
    out << prefix;
    out << (isLeft ? " |--" : " ---");
    
#ifdef COLORFUL
    int colorNum = node->isBlack ? 7 : 12;
    setcol(colorNum);
#endif
    out << ' ' << *node->key_ << std::endl;
#ifdef COLORFUL
    setcol(7);
#endif
    printPart(prefix + (isLeft ? " |   " : "    "), node->right_, true, out);
    printPart(prefix + (isLeft ? " |   " : "    "), node->left_, false, out);
  }
}

template< typename Key_t, typename Value_t, typename KeyComp >
void RBT< Key_t, Value_t, KeyComp >::inorderWalk(Node* node, std::ostream& out) const
{
  if (!node->left_->isNIL())
  {
    inorderWalk(node->left_, out);
  }
  out << *node->key_ << " - " << *node->value_ << '\n';
  if (!node->right_->isNIL())
  {
    inorderWalk(node->right_, out);
  }
}

template< typename K, typename V, typename C >
typename RBT< K, V, C >::Node* RBT< K, V, C >::getGrandpa(Node* grandson)
{
#ifdef TEST_MODE
  iter += 3;
#endif
  if (grandson && grandson->p_ && grandson->p_->p_)
  {
    return grandson->p_->p_;
  }
  else
  {
    return nullptr;
  }
}

template< typename K, typename V, typename C >
typename RBT< K, V, C >::Node* RBT< K, V, C >::getUncle(Node* nephew)
{
  Node* grandpa = getGrandpa(nephew);
#ifdef TEST_MODE
  iter += 2;
#endif
  if (!grandpa)
  {
    return nullptr;
  }
#ifdef TEST_MODE
  iter += 1;
#endif
  return (nephew->p_ == grandpa->left_ ? grandpa->right_ : grandpa->left_);
}

template< typename K, typename V, typename C >
typename RBT< K, V, C >::Node* RBT< K, V, C >::getSibling(Node* n)
{
#ifdef TEST_MODE
  iter += 1;
#endif
  return (n == n->p_->left_ ? n->p_->right_ : n->p_->left_);
}

#endif
