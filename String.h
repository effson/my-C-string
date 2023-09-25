#pragma once
#include<cstring>
#include<iostream>
#include"assert.h"

using namespace std;
namespace mstr
{
	class string {
	public:
		typedef char* iterator;
		iterator begin() {
			return str;
		}
		iterator end() {
			return str + _size;
		}
		string(const char* cstr = "") {
			_size = strlen(cstr);
			_capacity = _size;
			str = new char[_capacity + 1];
			strcpy(str, cstr);
		}// Be careful,you need one place for the '\0', someone may forget to prepare a place for it.
		size_t size() const {
			return _size;
		}
		size_t capacity() const {
			return _capacity;
		}//if you don't change the item in this fuction,you'd better use const.
		/*string(const string& s) {
			str = new char[s._capacity + 1];
			strcpy(str, s.str);
		}*/
		string(const string& s):str(nullptr),_size(0),_capacity(0){
			string tmp(s.str);
			this->swap(tmp);
		}// make the best of string(const char* cstr = ""),this can write less code.
		
		string& operator=(string s) {
			/*if (this != &s)
			{
				char* tmp = new char[strlen(s.str) + 1];
				strcpy(tmp, s.str);
				delete[] str;
				str = tmp;
				_size = s._size;
				_capacity = s._capacity;
				return *this;

				string tmp(s);
				swap(str, tmp.str);
			}*/
			this->swap(s);
			return *this;// Pay attention to the parameter,reference is not used, make the best of copy construction function.
		}
		void swap(string& s) {
			::swap(str, s.str);
			::swap(_size, s._size);
			::swap(_capacity, s._capacity);
		}
		char& operator[](size_t i) {
			assert(i < _size);
			return str[i];
		}
		const char& operator[](size_t i) const {
			assert(i < _size);
			return str[i];
		}
		const char* c_str() const {
			return str;
		}
		void push_back(char ch) {
			/*if (_size == _capacity) {
				size_t newcapacity = _capacity == 0 ? 2 : 2 * _capacity;
				reserve(newcapacity);
			}
			str[_size] = ch;
			_size += 1;
			str[_size] = '\0';*/
			insert(_size, ch);
		}
		void append(const char* cstr) {
			size_t len = strlen(cstr);
			if (_size + len > _capacity) {
				size_t newcapacity = _size + len;
				reserve(_size + len);
			}
			strcpy(str + _size, cstr);
			_size += len;
			str[_size] = '\0';

		}
		void reserve(size_t n) {
			if (n > _capacity)
			{
				char* newstr = new char[n + 1];
				strcpy(newstr, str);
				delete[] str;
				str = newstr;
				_capacity = n;
			}
		}
		string& operator+=(char ch) {
			this->push_back(ch);
			return *this;
		}
		string& operator+=(const char* cstr) {
			this->append(cstr);
			return *this;
		}

		~string() {
			delete[] str;
			str = nullptr;
			_size = _capacity = 0;
		}
		void insert(size_t pos, char ch) {
			assert(pos <= _size);
			if (_size == _capacity) {
				size_t newcapacity = _capacity == 0 ? 2 : 2 * _capacity;
				reserve(newcapacity);
			}
			int end = _size;
			while (end >= (int)pos) {
				str[end + 1] = str[end];
				--end;
			}
			str[pos] = ch;
			++_size;
		}
		string& insert(size_t pos, const char* cstr) {
			assert(pos < _size);
			size_t len = strlen(cstr);
			reserve(_size + len);
			int end = _size;
			while (end >= pos) {
				str[end + len] = str[end];
				--end;
			}
			strncpy(str + pos, cstr, len);
			_size += len;
			return *this;
		}
		void resize(size_t n, char ch = '\0') {
			if (n < _size) {
				str[n] = '\0';
				_size = n;
			}
			else {
				if (n > _capacity) {
					reserve(n);
				}
				for (size_t i = _size; i < n; ++i) {
					str[i] = ch;
				}
				_size = n;
				str[_size] = '\0';
			}
		}
		void erase(size_t pos, size_t len = npos) {
			if (_size - pos <= len) {
				str[pos] = '\0';
				_size = pos;
			}
			else {
				size_t begin = pos;
				while (begin <= _size - len)
				{
					str[begin] = str[begin + len];
					begin += 1;
				}
				_size -= len;
			}
		}
	
		size_t find(char ch, size_t pos = 0) {
			for (size_t i = pos; i < _size; i++) {
				if (str[i] == ch) {
					return i;
				}
			}
			return npos;
		}
		size_t find(const char* cstr, size_t pos = 0) {
			char* p = strstr(str, cstr);
			if (p == nullptr) {
				return npos;
			}
			else {
				return p - str;
			}
		}
		bool operator<(const string& s) const{
			int res = strcmp(str, s.str);
			return res < 0;
		}
		bool operator==(const string& s)const {
			int res = strcmp(str, s.str);
			return res == 0;
		}
		bool operator>(const string& s)const {
			return !(*this < s||*this == s);
		}
		bool operator<=(const string& s)const {
			return *this < s || *this == s;
		}
		bool operator>=(const string& s) const {
			return !(*this < s);
		}
	private:
		char* str;
		size_t _size;
		size_t _capacity;
		static size_t npos;

	};
	size_t string::npos = -1;
	ostream& operator<< (ostream& out, const string& s) {
		for (size_t i = 0; i < s.size(); ++i) {
			cout << s[i];
		}
		return out;
	}
	istream& operator>>(istream& in, string& s) {
		while (1) {
			char ch;
			ch=in.get();
			if (ch == ' ' || ch == '\n') {
				break;
			}
			else {
				s += ch;
			}
		}
		return in;
	}
}
