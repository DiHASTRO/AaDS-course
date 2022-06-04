#include "SetString.hpp"
#include <stdexcept>
#include <ostream>

struct StringComparator
{
	bool operator()(const std::string& first, const std::string& second)
	{
		return first < second;
	}
};

SetString::SetString():
	head_(nullptr),
	count_(0)
{}

bool SetString::insertItem(const std::string& item)
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
		if (head_->item_ > item)
		{
			head_ = new Node(item, head_);
			count_++;
			return true;
		}

		while (current->nextNode_ && current->nextNode_->item_ <= item)
		{
			current = current->nextNode_;
		}

		if (current->item_ == item)
		{
			return false;
		}
		else
		{
			current->nextNode_ = new Node(item, current->nextNode_);
			count_++;
			return true;
		}
	}
}


SetString::SetString(const SetString& other):
	count_(other.count_),
	head_(nullptr)
{
	SetString tempThis;
	tempThis.count_ = other.count_;
	tempThis.head_ = new Node(other.head_->item_);
	Node* current = tempThis.head_;
	Node* nextCurrent = other.head_->nextNode_;
	while (nextCurrent)
	{
		current->nextNode_ = new Node(nextCurrent->item_);
		current = current->nextNode_;
		nextCurrent = nextCurrent->nextNode_;
	}

	swap(tempThis);
}

SetString::SetString(SetString&& other) noexcept:
	head_(other.head_),
	count_(other.count_)
{
	other.head_ = nullptr;
	other.count_ = 0;
}

bool SetString::deleteItem(const std::string& item)
{
	Node* current = head_;
	if (head_->item_ == item)
	{
		Node* forDeleting = head_;
		head_ = head_->nextNode_;
		delete forDeleting;

		--count_;
		return true;
	}
	while (current->nextNode_ && current->nextNode_->item_ <= item)
	{
		if (current->nextNode_->item_ == item)
		{
			Node* forDeleting = current->nextNode_;
			current->nextNode_ = current->nextNode_->nextNode_;
			delete forDeleting;

			--count_;
			return true;
		}
		current = current->nextNode_;
	}

	return false;
}

bool SetString::isThere(const std::string& item)
{
	Node* current = head_;
	while (current && current->item_ <= item)
	{
		current = current->nextNode_;
	}

	return current && current->item_ == item;
}

SetString& SetString::operator=(const SetString& other)
{
	if (this != &other)
	{
		SetString temp(other);
		swap(temp);
	}
	return *this;
}

SetString& SetString::operator=(SetString&& other) noexcept
{
	if (this != &other)
	{
		swap(other);
	}
	return *this;
}

SetString::~SetString()
{
	Node* current = head_;
	while (current)
	{
		Node* forDelete = current;
		current = current->nextNode_;
		delete forDelete;
	}
	count_ = 0;
}

void SetString::unionSets(SetString& other)
{
	if (this == &other)
	{
		throw std::invalid_argument("You mustn't add a SetString to itself\n");
	}

	Node* currentThis = head_;
	Node* currentOther = other.head_;

	if (!head_)
	{
		swap(other);
		return;

	}
	while (currentOther)
	{
		if (currentOther->item_ < head_->item_) // добавление элементов, меньших, чем head_
		{
			Node* forAdding = currentOther;
			currentOther = currentOther->nextNode_;
			forAdding->nextNode_ = head_;
			head_ = forAdding;
			currentThis = head_;
			count_++;
		}
		else if (currentThis == head_ && currentThis->item_ == currentOther->item_) // Проверка первого элемента, чтоб не было лишнего добавления
		{
			currentOther = currentOther->nextNode_;
		}
		else
		{
			while (currentThis->nextNode_ && currentThis->nextNode_->item_ < currentOther->item_) // довод указателя до нужного места, чтоб добавить число из other
			{
				currentThis = currentThis->nextNode_;
			}
			if (!currentThis->nextNode_) // проверка, не зашли ли мы в конец словаря и, если да, добавление указателя всего на один элемент, который потянет остальные за собой
			{
				currentThis->nextNode_ = currentOther;
				while (currentOther) // увеличение count_ до нужного числа
				{
					currentOther = currentOther->nextNode_;
					count_++;
				}
			}
			else if (currentThis->nextNode_->item_ != currentOther->item_) // проверка, нет ли уже числа из other в this и, если нет, то добавление его в словарь
			{
				Node* forAdding = currentOther;
				currentOther = currentOther->nextNode_;
				forAdding->nextNode_ = currentThis->nextNode_;
				currentThis->nextNode_ = forAdding;
				count_++;
			}
			else
			{
				Node* forDeleting = currentOther;
				currentOther = currentOther->nextNode_; // если в this уже есть число из other, то просто пропуск элемента 
				currentThis = currentThis->nextNode_;

				delete forDeleting;
			}
		}
	}

	other.head_ = nullptr;
	other.count_ = 0;
}

std::ostream& operator<<(std::ostream& stream, const SetString& dict)
{
	stream << "[ ";
	SetString::Node* current = dict.head_;
	while (current)
	{
		stream << current->item_ << ' ';
		current = current->nextNode_;
	}
	stream << ']';

	return stream;
}

void SetString::swap(SetString& other) noexcept
{
	std::swap(head_, other.head_);
	std::swap(count_, other.count_);
}

SetString::Node::Node(const std::string& item, Node* nextNode):
	item_(item),
	nextNode_(nextNode)
{}
