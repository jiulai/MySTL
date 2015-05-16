//
//  MyString.h
//  C++ test
//
//  Created by 王翛然 on 15/5/6.
//  Copyright (c) 2015年 王翛然. All rights reserved.
//

#ifndef MyString_h
#define MyString_h

#include <memory>
#include <iterator>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <stdexcept>

class MyString {
public:
    // stream operator
    friend std::istream& operator>> (std::istream &in,
                                     MyString &rhs);
    friend std::ostream& operator<< (std::ostream &os,
                                    const MyString &rhs);
    
    friend bool operator< (const MyString&, const MyString&);
    friend bool operator< (const MyString&, const char*);
    friend bool operator< (const char*, const MyString&);
    
    friend bool operator> (const MyString&, const MyString&);
    friend bool operator> (const MyString&, const char*);
    friend bool operator> (const char*, const MyString&);
    
    friend bool operator== (const MyString&, const MyString&);
    friend bool operator== (const MyString&, const char*);
    friend bool operator== (const char*, const MyString&);

public:
    class iter;
    typedef iter                   iterator;
    typedef const iterator         const_iterator;
    typedef char                   value_type;
    typedef std::char_traits<char> traits_type;
    typedef std::allocator<char>   allocator_type;
    typedef char&                  reference;
    typedef const char&            const_reference;
    typedef value_type*            pointer;
    typedef const value_type*      const_pointer;
    typedef ptrdiff_t              difference_type;
    typedef size_t                 size_type;
    
    static const size_type npos = -1;
    
    friend long operator- (const MyString::iterator &lhs,
                           const MyString::iterator &rhs);
public:
    // 缺少范围构造函数
    MyString();
    MyString(const MyString&);//copy constructor
    MyString(const MyString& str, size_type pos,
                                            size_type len = npos);
    MyString(const char* s);
    MyString(const char* s, size_t n);
    MyString(size_t n, char c);
    MyString(std::initializer_list<char> il);
    MyString(MyString&& str) noexcept
        { _data = new char[strlen(str._data)+1];
            strcpy(_data, str._data);}
    MyString(MyString::iterator beg, MyString::iterator end);
    
    // assignment operator
    MyString& operator= (const MyString& str);
    MyString& operator= (const char* s);
    MyString& operator= (char c);
    MyString& operator= (std::initializer_list<char> il);
    MyString& operator= (MyString&& str) noexcept;
    MyString& operator+= (const MyString &str);
    MyString& operator+= (const char *str);
    char&     operator[] (size_type n) const
        { return _data[n]; }
    //destructor
    ~MyString() noexcept
        { delete[] _data; }

    MyString& append(const MyString &str);
    MyString& append(const char *str);
    MyString& append(const char *str, size_t n);
    MyString& append(size_t n, char c);
    MyString& append(std::initializer_list<char> il);
    MyString& append(const MyString &str,
                                    size_t pos, size_t sublen);
    void swap(MyString&);

    char front() { return _data[0]; }
    char back() { return _data[size()]; }
    size_t size() const { return strlen(_data); }
    size_t length() const { return strlen(_data); }
    MyString& replace(int n, char c)
        { _data[n] = c; return *this; }

    char at(int n) const
    {
        if(n > size())
            throw std::out_of_range("out of range");
        return _data[n];
    }
    
    void clear()
    {
        auto temp = _data;
        _data = new char[strlen(temp) + 1];
        *_data = '\0';
        delete[] temp;
    }
    
    // iterator
    class iter
    {// relational operator
        friend iterator operator+ (const iterator&, size_t n);
        friend iterator operator- (const iterator&, size_t n);
        friend long operator- (const iterator &lhs,
                               const iterator &rhs);
    public:
        iter() = default;
        iter(char* iter) : iterator(iter) { };
        iter(const iter &rhs) : iterator(rhs.iterator) { }
    public:
        char operator* ()
            { return *iterator; }
        iterator& operator= (const iterator &rhs)
            { iterator = rhs.iterator; return *this; }
        iterator& operator++ ()
            { ++iterator; return *this; }
        iterator& operator-- ()
            { --iterator; return *this; }
        iterator operator++ (int)
            { auto temp = *this; ++*this; return temp; }
        iterator operator-- (int)
            { auto temp = *this; --*this; return temp; }
        iterator& operator+= (size_t n)
            { iterator += n; return *this; }
        iterator& operator-= (size_t n)
            { iterator -= n; return *this; }
        
        bool operator== (const iterator &rhs)
            { if(iterator == rhs.iterator) return true;
                return false; }
        bool operator!= (const iterator &rhs)
            { if(*this == rhs) return false; return true; }
        bool operator< (const iterator &rhs)
            { if(*this - rhs < 0) return true; return false; }
        bool operator<= (const iterator &rhs)
            { if(*this < rhs || *this == rhs) return true;
            return false; }
        bool operator> (const iterator &rhs)
            { if(*this < rhs) return false; return true; }
        bool operator>= (const iterator &rhs)
            { if(*this < rhs && *this != rhs) return false;
            return true;}
        
    private:
        char* iterator;
    };
    
    iterator begin() noexcept
        { iter = _data; return iter; }
    const_iterator& cbegin() const noexcept
        {  return iter; }
    iterator end() noexcept
        { iter += size(); return iter; }
    const_iterator cend() const noexcept
        { return (iter + size()); }
    iterator& rbegin() noexcept
        { iter += size(); return iter; }
    const_iterator rbegin() const noexcept
        { const_iterator temp(_data + size()); return temp; }
    iterator& rend() noexcept
        { iter -= 1; return iter; }
    const_iterator rend() const noexcept
        { const_iterator temp(_data-1); return temp; }

private:
    char* _data;
    iterator iter;
};

MyString operator+ (const MyString &lhs, const char *str);
MyString operator+ (const MyString &lhs, const MyString &rhs);

#endif
