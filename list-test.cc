#include "List.h"
#include <iostream>
#include "catch.hpp"

using namespace List_NS;
TEST_CASE( "Create list" )
{
    List<int> lst{1,4,2,6,8,9};
    CHECK(lst.at(2) == 2);
    CHECK(lst.size() == 6);
    List<int> l2;
    l2 = lst;
    CHECK(l2.size() == lst.size());
    CHECK(l2.front() == lst.front());
    CHECK(l2.back() == lst.back());
}

TEST_CASE( "General tests"){
    List<int> list{1,2,3,4,5,6};
    CHECK(list.at(1) == 2);

    List<int> l2;
    CHECK(l2.empty() == true);

    l2 = list;
    CHECK(l2.at(5) == 6);
    l2.push_back(2);
    CHECK(l2.at(6) == 2);

    l2.push_front(14);
    CHECK(l2.at(0) == 14);
}

TEST_CASE("operatorer")
{
    List<int> lista{3,5,7,5};

    {
	auto it=lista.begin();

	CHECK(*it==3);
    }

    {
	auto it=lista.begin();
	//Pre
	++it;
	CHECK(*it==5);
	--it;
	CHECK(*it==3);

	//Post
	CHECK(*(it++)==3);
	CHECK(*(it--)==5);

	//==
	auto it2=lista.begin();
	CHECK(it==it2);

	//!=
	it2=lista.end();
	CHECK(it!=it2);
    }

    List<int> lst{2,3,1,5};
    auto rb { std::make_reverse_iterator(lst.end()) };
    auto re { std::make_reverse_iterator(lst.begin()) };
    
    std::cout << std::endl;

    //Write reversed
    for(auto it = rb; it != re; ++it )
    {
	std::cout  << *it <<' ';
    }
    std::cout << std::endl;
}

TEST_CASE("Strings"){

    List<std::string> lst{"hello", "world"};
    CHECK(lst.at(1) == "world");
    CHECK(lst.size() == 2);
    List<std::string> l2;
    l2 = lst;
    CHECK(l2.size() == lst.size());
    CHECK(l2.front() == lst.front());
    CHECK(l2.back() == lst.back());

}

TEST_CASE("General strings"){

    List<std::string> list{"Somebody", "once", "told", "me", "the", "world", "is", "gonna", "roll", "me"};
    CHECK(list.at(1) == "once");

    List<std::string> l2;
    CHECK(l2.empty() == true);

    l2 = list;
    CHECK(l2.at(5) == "world");
    l2.push_back("All Star");
    CHECK(l2.at(10) == "All Star");

    l2.push_front("Shrek");
    CHECK(l2.at(0) == "Shrek");

}

TEST_CASE("Operators/General strings"){

    List<std::string> lista{"I", "aint", "the", "sharpest", "tool", "in", "the", "shed"};

    {
	auto it=lista.begin();

	CHECK(*it=="I");
    }

    {
	auto it=lista.begin();
	//Pre
	++it;
	CHECK(*it=="aint");
	--it;
	CHECK(*it=="I");

	//Post
	it++;
	CHECK(*it=="aint");
	it--;
	CHECK(*it=="I");

	//==
	auto it2=lista.begin();
	CHECK(it==it2);

	//!=
	it2=lista.end();
	CHECK(it!=it2);
    }

    List<std::string> lst{"She", "was", "looking", "kind", "of", "dumb"};
    lst.push_front("All");
    lst.push_front("Star");
    auto rb { std::make_reverse_iterator(lst.end()) };
    auto re { std::make_reverse_iterator(lst.begin()) };
    
    std::cout << std::endl;

    //Write first letter reversed
    for(auto it = rb; it != re; ++it )
    {
	std::cout << it->front() <<' ';
    }
    std::cout << std::endl;

    //Write reversed
    for(auto it = rb; it != re; ++it )
    {
	std::cout  << *it <<' ';
    }
    std::cout << std::endl;
    auto it = rb;

    CHECK("dumb" == *it);
    CHECK(it->front() == 'd');
}

TEST_CASE("Iterator post-decrement")
{
    const List_NS::List<int> l{1,2,3};
    auto it{l.end()};
    auto it2{it};

    CHECK(it == l.end());
    CHECK(it2 == l.end());
    CHECK(it != l.begin());

    it2 = it--;
    CHECK(*it == 3);
    CHECK(it2 == l.end());

    it2 = it--;
    CHECK(*it == 2);
    CHECK(*it2 == 3);

    it2 = it--;
    CHECK(*it == 1);
    CHECK(*it2 == 2);
    CHECK(it == l.begin());

}
