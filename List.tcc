#include "List.h"
#include <iterator>
#include <utility>
#include <stdexcept>
#include <memory>

template <typename T>
List_NS::List<T>::List()
    : head{ std::make_unique<Node>() }, tail{head.get()}, sz{}
{}
template <typename T>
List_NS::List<T>::List(List const & other)
    : List{}
{
    Node * tmp = other.head.get();
    while ( tmp != other.tail )
    {
        push_back(tmp->value);
        tmp = tmp->next.get();

    }
}
template <typename T>
List_NS::List<T>::List(List && tmp) noexcept
    :List{}
{
    swap(tmp);
}

template <typename T>
List_NS::List<T>::List(std::initializer_list<T> lst)
    : List{}
{
    for ( auto val : lst )
    {
        push_back(val);
    }
}
template <typename T>
void List_NS::List<T>::push_front(T value)
{
    head = std::make_unique<Node>(value, nullptr, head.release());
    if ( sz == 0 )
    {
        tail->prev = head.get();
    }
    else{
	head->next->prev = head.get();
    }
    ++sz;
}
template <typename T>
void List_NS::List<T>::push_back(T value)
{
    if ( empty() )
    {
        push_front(value);
    }
    else
    {
	tail->prev->next.release();
        tail->prev->next = std::make_unique<Node>(value, tail->prev, tail);
        tail->prev = tail->prev->next.get();
        ++sz;
    }
}
template <typename T>
bool List_NS::List<T>::empty() const
{
    return head.get() == tail;
}
template <typename T>
T List_NS::List<T>::back() const
{
    return tail->prev->value;
}
template <typename T>
T & List_NS::List<T>::back()
{
    return tail->prev->value;
}
template <typename T>
T List_NS::List<T>::front() const
{
    return head->value;
}
template <typename T>
T & List_NS::List<T>::front()
{
    return head->value;
}
template <typename T>
T & List_NS::List<T>::at(int idx)
{
    return const_cast<T &>(static_cast<List const &>(*this).at(idx));
}
template <typename T>
T const & List_NS::List<T>::at(int idx) const
{
    if (idx >= sz)
        throw std::out_of_range{"Index not found"};
    Node * tmp {head.get()};
    while ( idx > 0 )
    {
        tmp = tmp->next.get();
        --idx;
    }
    return tmp->value;
}
template <typename T>
int List_NS::List<T>::size() const
{
    return sz;
}
template <typename T>
void List_NS::List<T>::swap(List & other) noexcept
{
    using std::swap;
    swap(head, other.head);
    swap(tail, other.tail);
    swap(sz, other.sz);
}
template <typename T>
List_NS::List<T> & List_NS::List<T>::operator=(List const & rhs) &
{
    List{rhs}.swap(*this);
    return *this;
}
template <typename T>
List_NS::List<T> & List_NS::List<T>::operator=(List && rhs) &
{
    swap(rhs);
    return *this;
}
template <typename T>
typename List_NS::List<T>::List_Iterator List_NS::List<T>::begin() const
{
    List_Iterator tmp{head.get()};
    return tmp;
}
template <typename T>
typename List_NS::List<T>::List_Iterator List_NS::List<T>::end() const
{
    List_Iterator tmp{tail};
    return tmp;
}
template <typename T>
typename List_NS::List<T>::List_Iterator & List_NS::List<T>::List_Iterator::operator++(){

    current = current->next.get();
    return *this;
}
template <typename T>
typename List_NS::List<T>::List_Iterator List_NS::List<T>::List_Iterator::operator++(int){

    List_Iterator tmp{current};
    current = current->next.get();
    return tmp;
}
template <typename T>
typename List_NS::List<T>::List_Iterator & List_NS::List<T>::List_Iterator::operator--(){

    current = current->prev;
    return *this;
}
template <typename T>
typename List_NS::List<T>::List_Iterator List_NS::List<T>::List_Iterator::operator--(int){

    List_Iterator tmp{current};
    current = current->prev;
    return tmp;
}
