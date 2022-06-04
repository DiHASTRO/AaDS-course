#ifndef SET_H
#define SET_H

#include <stdexcept>

template < typename T, typename Comp >
class Set
{
public:
	Set();
	Set(const Set< T, Comp >& other);
	Set(Set< T, Comp >&& other) noexcept;

	Set< T, Comp >& operator=(const Set< T, Comp >& other);
	Set< T, Comp >& operator=(Set< T, Comp >&& other) noexcept;

	bool insertItem(const T& item);
	bool deleteItem(const T& item);
	bool isThere(const T& item);

	int getCount() const;

	void unionSets(Set< T, Comp >& other);

	template < typename T, typename Comp >
	friend std::ostream& operator<<(std::ostream& stream, const Set< T, Comp >& dict);

	virtual ~Set();
private:
	void swap(Set< T, Comp >& other) noexcept;

	struct Node
	{
		Node(const T& item, Node* nextNode = nullptr);
		T item_;
		Node* next_;
	};

	Node* head_;
	int count_;
};

template < typename T, typename Comp >
Set< T, Comp >::Set():
	head_(nullptr),
	count_(0)
{}

template < typename T, typename Comp >
bool Set< T, Comp >::insertItem(const T& item)
{
	Node* current = head_;
	if (count_ == 0)
	{
		head_ = new Node(item);
		count_++;
		return true;
	}
	else
	{
		if (Comp{}(item, head_->item_))
		{
			head_ = new Node(item, head_);
			count_++;
			return true;
		}

		while (current->next_ && !Comp{}(item, current->next_->item_))
		{
			current = current->next_;
		}

		if (!Comp{}(current->item_, item) && !Comp{}(item, current->item_))
		{
			return false;
		}
		else
		{
			current->next_ = new Node(item, current->next_);
			count_++;
			return true;
		}
	}
}

template < typename T, typename Comp >
Set< T, Comp >::Set(const Set< T, Comp >& other):
	count_(other.count_),
	head_(nullptr)
{
	Set tempThis;
	tempThis.count_ = other.count_;
	tempThis.head_ = new Node(other.head_->item_);
	Node* current = tempThis.head_;
	Node* nextCurrent = other.head_->next_;
	while (nextCurrent)
	{
		current->next_ = new Node(nextCurrent->item_);
		current = current->next_;
		nextCurrent = nextCurrent->next_;
	}

	swap(tempThis);
}

template < typename T, typename Comp >
Set< T, Comp >::Set(Set< T, Comp >&& other) noexcept:
	head_(other.head_),
	count_(other.count_)
{
	other.head_ = nullptr;
	other.count_ = 0;
}

template < typename T, typename Comp >
bool Set< T, Comp >::deleteItem(const T& item)
{
	Node* current = head_;
	if (!Comp{}(head_->item_, item) && !Comp{}(item, head_->item_))
	{
		Node* forDeleting = head_;
		head_ = head_->next_;
		delete forDeleting;

		--count_;
		return true;
	}
	while (current->next_ && !Comp{}(item, current->next_->item_))
	{
		if (!Comp{}(current->next_->item_, item) && !Comp{}(item, current->next_->item_))
		{
			Node* forDeleting = current->next_;
			current->next_ = current->next_->next_;
			delete forDeleting;

			--count_;
			return true;
		}
		current = current->next_;
	}

	return false;
}

template < typename T, typename Comp >
bool Set< T, Comp >::isThere(const T& item)
{
	Node* current = head_;
	while (current && !Comp{}(item, current->item_))
	{
		current = current->next_;
	}

	return current && !Comp{}(current->item_, item) && !Comp{}(item, current->item_);
}

template < typename T, typename Comp >
int Set< T, Comp >::getCount() const
{
	return count_;
}

template < typename T, typename Comp >
Set< T, Comp >& Set< T, Comp >::operator=(const Set< T, Comp >& other)
{
	if (this != &other)
	{
		Set temp(other);
		swap(temp);
	}
	return *this;
}

template < typename T, typename Comp >
Set< T, Comp >& Set< T, Comp >::operator=(Set< T, Comp >&& other) noexcept
{
	if (this != &other)
	{
		swap(other);
	}
	return *this;
}

template < typename T, typename Comp >
Set< T, Comp >::~Set()
{
	Node* current = head_;
	while (current)
	{
		Node* forDelete = current;
		current = current->next_;
		delete forDelete;
	}
	count_ = 0;
}

template < typename T, typename Comp >
void Set< T, Comp >::unionSets(Set< T, Comp >& other)
{
	if (this == &other)
	{
		throw std::invalid_argument("You mustn't add a Set to itself\n");
	}

	Node* curThis = head_;
	Node* curOther = other.head_;

	if (!head_)
	{
		swap(other);
		return;

	}
	while (curOther)
	{
		if (Comp{}(curOther->item_, head_->item_))
		{
			Node* forAdding = curOther;
			curOther = curOther->next_;
			forAdding->next_ = head_;
			head_ = forAdding;
			curThis = head_;
			count_++;
		}
		else if (curThis == head_ && !Comp{}(curThis->item_, curOther->item_) && !Comp{}(curOther->item_, curThis->item_))
		{
			curOther = curOther->next_;
		}
		else
		{
			while (curThis->next_ && Comp{}(curThis->next_->item_, curOther->item_))
			{
				curThis = curThis->next_;
			}
			if (!curThis->next_)
			{
				curThis->next_ = curOther;
				while (curOther)
				{
					curOther = curOther->next_;
					count_++;
				}
			}
			else if (Comp{}(curThis->next_->item_, curOther->item_) || Comp{}(curOther->item_, curThis->next_->item_))
			{
				Node* forAdding = curOther;
				curOther = curOther->next_;
				forAdding->next_ = curThis->next_;
				curThis->next_ = forAdding;
				count_++;
			}
			else
			{
				Node* forDeleting = curOther;
				curOther = curOther->next_;
				curThis = curThis->next_;

				delete forDeleting;
			}
		}
	}

	other.head_ = nullptr;
	other.count_ = 0;
}

template < typename T, typename Comp >
std::ostream& operator<<(std::ostream& stream, const Set< T, Comp >& dict)
{
	stream << "[ ";
	typename Set< T, Comp >::Node* current = dict.head_;
	while (current)
	{
		stream << current->item_ << ' ';
		current = current->next_;
	}
	stream << ']';

	return stream;
}

template < typename T, typename Comp >
void Set< T, Comp >::swap(Set< T, Comp >& other) noexcept
{
	std::swap(head_, other.head_);
	std::swap(count_, other.count_);
}

template < typename T, typename Comp >
Set< T, Comp >::Node::Node(const T& item, Node* nextNode):
	item_(item),
	next_(nextNode)
{}

#endif
