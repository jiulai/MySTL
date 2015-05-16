//
//  MyString.cpp
//  C++ test
//
//  Created by 王翛然 on 15/5/6.
//  Copyright (c) 2015年 王翛然. All rights reserved.
//

#include "MyString.h"

MyString::MyString() : _data(new char[1]), iter(_data)
{
    *_data = '\0';
}

MyString::MyString(const MyString& rhs)
{
    size_t len = strlen(rhs._data);
    _data = new char[len + 1];
    iter = _data;
    strcpy(_data, rhs._data);
}

MyString::MyString(const char* s)
{
    size_t len = strlen(s);
    _data = new char[len + 1];
    iter = _data;
    strcpy(_data, s);
}

MyString::MyString(const char* s, size_t n)
{
    size_t len = n;
    _data = new char[len + 1];
    iter = _data;
    strncpy(_data, s, n);
}

MyString::MyString(size_t n, char c)
{
    size_t len = n;
    _data = new char[len + 1];
    iter = _data;
    for (size_t i = 0; i < len; ++i)
        _data[i] = c;
    _data[len + 1] = '\0';
}

MyString::MyString(const MyString& str, size_type pos,
                                                size_type len)
{
    if(len > str.size() - pos)
    {
        len = str.size() - pos;
    }
    _data = new char[len+1];
    iter = _data;
    
    for(size_type i = 0; i < len; ++i)
    {
        _data[i] = str[pos+i];
    }
    _data[len] = '\0';
}

MyString::MyString(std::initializer_list<char> il)
{
    size_t len = il.size();
    _data = new char[len + 1];
    iter = _data;
    
    size_t i = 0;
    for(const auto &e : il)
    {
        _data[i++] = e;
    }
    _data[i] = '\0';
}

MyString::MyString(MyString::iterator beg,
                   MyString::iterator end)
{
    _data = new char[end-beg+1];
    
    auto temp = _data;
    for(MyString::iterator b = beg; b != end; ++b)
    {
        *temp++ = *b;
    }
    std::cout << "fuck";
    *temp = '\0';
    std::cout << _data;
}

MyString& MyString::operator= (const MyString& str)
{
    if(_data != nullptr)
        delete[] _data;
    assert(str._data != nullptr);
    _data = new char[strlen(str._data) + 1];
    iter = _data;
    
    auto temp1 = _data, temp2 = str._data;
    while(*temp2 != '\0')
        *temp1++ = *temp2++;
    *temp1 = '\0';
    
    return *this;
}

MyString& MyString::operator= (const char* s)
{
    if(_data != nullptr)
        delete[] _data;
    assert(s != nullptr);
    
    _data = new char[strlen(s) + 1];
    iter = _data;
    
    auto temp1 = _data;
    auto temp2 = s;
    
    while(*temp2 != '\0')
        *temp1++ = *temp2++;
    *temp1 = '\0';
    
    return *this;
}

MyString& MyString::operator= (const char c)
{
    if(_data != nullptr)
        delete[] _data;
    _data = new char[2];
    iter = _data;
    *_data = c;
    *(_data + 1) = '\0';
    
    return *this;
}

MyString& MyString::operator= (std::initializer_list<char> il)
{
    if(_data != nullptr)
        delete[] _data;
    _data = new char[il.size() + 1];
    iter = _data;
    
    size_t i = 0;
    for(const auto &e : il)
    {
        _data[i++] = e;
    }
    _data[i] = '\0';
    
    return *this;
}

MyString& MyString::operator= (MyString&& str) noexcept
{
    if(_data != nullptr)
        delete[] _data;
    _data = new char[strlen(str._data) + 1];
    iter = _data;
    
    auto temp = str._data;
    size_t i = 0;
    while(*temp != '\0')
    {
        _data[i++] = *temp++;
    }
    _data[i] = '\0';
    
    return *this;
}

MyString& MyString::operator+= (const MyString &str)
{
    auto temp = _data;
    _data = new char[size() + strlen(str._data) + 1];
    iter = _data;
    strcpy(_data, temp);
    delete[] temp;
    strcat(_data, str._data);
    
    return *this;
}

MyString& MyString::operator+= (const char *str)
{
    auto temp = _data;
    _data = new char[size() + strlen(str) + 1];
    iter = _data;
    strcpy(_data, temp);
    delete[] temp;
    strcat(_data, str);
    
    return *this;
}

MyString operator+ (const MyString &lhs, const MyString &rhs)
{
    auto temp(lhs);
    temp += rhs;
    return temp;
}

MyString operator+ (const MyString &lhs, const char *str)
{
    auto temp(lhs);
    temp += str;
    return temp;
}

MyString& MyString::append(const MyString &str)
{
    *this += str;
    iter = _data;
    return *this;
}

MyString& MyString::append(const MyString &str,
                                        size_t pos, size_t sublen)
{
    if(sublen > str.size() - pos)
        sublen = str.size() - pos;
    char *temp = new char[sublen+1];
    
    for(size_t i = 0; i < sublen; ++i)
    {
        temp[i] = str[i+pos];
    }
    temp[sublen+1] = '\0';
    *this += temp;
    iter = _data;
    delete[] temp;
    
    return *this;
}

MyString& MyString::append(const char *str)
{
    *this += str;
    iter = _data;
    return *this;
}

MyString& MyString::append(const char *str, size_t n)
{
    strncat(_data, str, n);
    iter = _data;
    return *this;
}

MyString& MyString::append(size_t n, char c)
{
    char *temp = new char[n+1];
    
    for(size_t i = 0; i < n; ++i)
        temp[i] = c;
    *this += temp;
    iter = _data;
    delete []temp;
    
    return *this;
}

MyString& MyString::append(std::initializer_list<char> il)
{
    char *temp = new char[il.size() + 1];
    
    size_t i = 0;
    for(const auto &e : il)
    {
        temp[i++] = e;
    }
    temp[i] = '\0';
    *this += temp;
    iter = _data;
    
    return *this;
}

std::istream& operator>> (std::istream &in, MyString &rhs)
{
    char *temp = new char[1024];
    in >> temp;
    //释放原内存中的字符串
    delete[] rhs._data;
    //分配新的字符串空间
    rhs._data = new char[strlen(temp)+1];
    strcpy(rhs._data, temp);
    rhs.iter = rhs._data;
    
    delete[] temp;
    
    return in;
}

std::ostream& operator<< (std::ostream &os, const MyString &rhs)
{
    os << rhs._data;
    return os;
}

bool operator< (const MyString &lhs, const MyString &rhs)
{
    if(strcmp(lhs._data, rhs._data) < 0)
        return true;
    return false;
}

bool operator< (const MyString &lhs, const char *rhs)
{
    if(strcmp(lhs._data, rhs) < 0)
        return true;
    return false;
}

bool operator< (const char *lhs, const MyString &rhs)
{
    if(strcmp(lhs, rhs._data) < 0)
        return true;
    return false;
}

bool operator> (const MyString &lhs, const MyString &rhs)
{
    if(strcmp(lhs._data, rhs._data) > 0)
        return true;
    return false;
}

bool operator> (const MyString &lhs, const char *rhs)
{
    if(strcmp(lhs._data, rhs) > 0)
        return true;
    return false;
}

bool operator> (const char *lhs, const MyString &rhs)
{
    if(strcmp(lhs, rhs._data) > 0)
        return true;
    return false;
}

bool operator== (const MyString &lhs, const MyString &rhs)
{
    if(!strcmp(lhs._data, rhs._data))
        return true;
    return false;
}

bool operator== (const MyString &lhs, const char *rhs)
{
    if(lhs._data == rhs)
        return false;
    return true;
}

bool operator== (const char *lhs, const MyString &rhs)
{
    if(rhs == lhs)
        return true;
    return false;
}

MyString::iterator operator+ (const MyString::iterator &lhs,
                                                        size_t n)
{
    char *temp = lhs.iterator;
    temp += n;
    MyString::iterator t(temp);
    return t;
}

MyString::iterator operator- (const MyString::iterator &lhs,
                                                        size_t n)
{
    char *temp = lhs.iterator;
    temp -= n;
    MyString::iterator t(temp);
    return t;
}

long operator- (const MyString::iterator &lhs,
                const MyString::iterator &rhs)
{
    auto n = rhs - lhs;
    std::cout << "fuck";
    return n;
}

void MyString::swap(MyString &rhs)
{
    auto temp = _data;
    _data = rhs._data;
    rhs._data = temp;
}