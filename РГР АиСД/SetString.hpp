#ifndef SET_STRING_H
#define SET_STRING_H

#include <ostream>
#include <string>

class SetString
{
public:
	SetString();
	SetString(const SetString& other);
	SetString(SetString&& other) noexcept;

	SetString& operator=(const SetString& other);
	SetString& operator=(SetString&& other) noexcept;

	bool insertItem(const std::string& item);
	bool deleteItem(const std::string& item);
	bool isThere(const std::string& item);

	int getCount() const { return count_; };

	void unionSets(SetString& other);
	friend std::ostream& operator<<(std::ostream& stream, const SetString& dict);

	virtual ~SetString();

private:
	void swap(SetString& other) noexcept;

	struct Node
	{
		Node(const std::string& item, Node* nextNode = nullptr);
		std::string item_;
		Node* nextNode_;
	};

	Node* head_;
	int count_;
};

#endif
