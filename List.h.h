#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <memory>
#include <iterator>
#include <utility>
#include <stdexcept>
#include <iterator>

namespace List_NS{
template <typename T>
class List
{
public:
    friend class List_Iterator;
    List();
    List(List const &);
    List(List &&) noexcept;
    List(std::initializer_list<T>);

    List & operator=(List const &)&;
    List & operator=(List &&)&;

    void push_front(T);
    void push_back(T);

    T back() const;
    T & back();

    T front() const;
    T & front();

    T & at(int idx);
    T const & at(int idx) const;

    int size() const;
    bool empty() const;

    void swap(List & other) noexcept;
private:
struct Node
{
    Node() = default;
    Node(T v, Node* p, Node* n)
        : value{v}, prev{p}, next{n} {}
    Node(T v, Node* p, std::unique_ptr<Node> & n)
	: value{v}, prev{p}, next{move(n)}{}
    T value {};
    Node * prev {};
    std::unique_ptr<Node> next {};
};

    std::unique_ptr<Node> head {};
    Node * tail {};
    int sz {};

public:
    class List_Iterator{
    public:
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = T;
	using difference_type = int;
	using pointer = T*;
	using reference = T&;

	friend List<T>;
	
	reference operator*() 
	{
	    return current->value;
	}

	pointer operator->(){
	    return &current->value;
	}
        
        //Pre
	List_Iterator & operator++();
	List_Iterator & operator--();
	//Post
	List_Iterator operator++(int);
	List_Iterator operator--(int);
	
	bool operator==(const List_Iterator & rhs)
	{
	    return current==rhs.current;
	}
	
	bool operator!=(const List_Iterator & rhs)
	{
	    return current!=rhs.current;
	}
    private:
	List_Iterator(Node* p): current{p} {}
	Node* current {};
    };

    List_Iterator begin() const;
    List_Iterator end() const;    
};
}
#include "List.tcc"

#endif //LIST_H
