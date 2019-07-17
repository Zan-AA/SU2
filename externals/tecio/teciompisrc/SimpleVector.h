 #pragma once
#include "ThirdPartyHeadersBegin.h"
#include <cstring>
#include <string>
#include <vector>
#include "ThirdPartyHeadersEnd.h"
#include "CodeContract.h"
namespace tecplot { namespace teciompi { template <typename T> class SimpleVector { public: typedef T* iterator; typedef T const* const_iterator; SimpleVector(); SimpleVector(SimpleVector<T> const& ___2888); explicit SimpleVector(int size, T ___4298 = T()); SimpleVector(T const* data, int size); template <typename ___1832> SimpleVector(___1832 const& b, ___1832 const& e); ~SimpleVector(); bool empty() const { return (m_size == 0); } int const& size() const { return m_size; } iterator begin() { return m_data; } const_iterator begin() const { return m_data; } iterator end() { return m_data + m_size; } const_iterator end() const { return m_data + m_size; } void allocate(int size); T& operator[](int i); T const& operator[](int i) const; SimpleVector<T>& operator=(SimpleVector<T> ___3392); private: int m_size; T* m_data; }; template <typename T> inline SimpleVector<T>::SimpleVector() : m_size(0) , m_data(0) {} template <typename T> inline SimpleVector<T>::SimpleVector(SimpleVector<T> const& ___2888) : m_data(0) { allocate(___2888.m_size); if (m_size > 0) memcpy(m_data, ___2888.m_data, m_size * sizeof(T)); } template <typename T> inline SimpleVector<T>::SimpleVector(int size, T ___4298) : m_data(0) { allocate(size); for(int i = 0; i < m_size; ++i) m_data[i] = ___4298; } template <typename T> inline SimpleVector<T>::SimpleVector(T const* data, int size) : m_data(0) { allocate(size); if (m_size > 0) memcpy(m_data, data, m_size * sizeof(T)); } template <typename T> template <typename ___1832> SimpleVector<T>::SimpleVector(___1832 const& b, ___1832 const& e) : m_data(0) { allocate(static_cast<int>(std::distance(b, e))); ___1832 it = b; for (int i = 0; i < m_size; ++i) m_data[i] = *(it++); ___478(it == e); } template <typename T> inline SimpleVector<T>::~SimpleVector() {
 #if defined _DEBUG
memset(m_data, 0x03, m_size * sizeof(T)); m_size = 0;
 #endif
delete[] m_data; } template <typename T> inline void SimpleVector<T>::allocate(int size) { m_size = size; if (m_size > 0) { m_data = new T[size]; } else { delete[] m_data; m_data = 0; } } template <typename T> inline T& SimpleVector<T>::operator[](int i) { REQUIRE(i < m_size); return m_data[i]; } template <typename T> inline T const& SimpleVector<T>::operator[](int i) const { REQUIRE(i < m_size); return m_data[i]; } template <typename T> inline SimpleVector<T>& SimpleVector<T>::operator=(SimpleVector<T> ___3392) { using std::swap; swap(m_size, ___3392.m_size); swap(m_data, ___3392.m_data); return *this; } template <> class SimpleVector<char> { public: SimpleVector(); SimpleVector(SimpleVector<char> const& ___2888); explicit SimpleVector(char const* cstr); explicit SimpleVector(int size, char ___4298 = 0); SimpleVector(char const* data, int size); template <typename ___1832> SimpleVector(___1832 const& b, ___1832 const& e); explicit SimpleVector(std::string const& str); ~SimpleVector(); bool empty() const { return (m_size == 0); } int const& size() const { return m_size; } char* begin() { return m_data; } char const* begin() const { return m_data; } char* end() { return m_data + m_size; } char const* end() const { return m_data + m_size; } void allocate(int size); char const* c_str() const { return m_data; } char& operator[](int i); char const& operator[](int i) const; SimpleVector<char>& operator=(SimpleVector<char> ___3392); private: int m_size; char* m_data; }; inline SimpleVector<char>::SimpleVector() : m_size(0) , m_data(0) {} inline SimpleVector<char>::SimpleVector(SimpleVector<char> const& ___2888) : m_data(0) { allocate(___2888.m_size); memcpy(m_data, ___2888.m_data, m_size); } inline SimpleVector<char>::SimpleVector(char const* cstr) : m_data(0) { allocate(static_cast<int>(strlen(cstr) + 1)); strcpy(m_data, cstr); } template <typename ___1832> inline SimpleVector<char>::SimpleVector(___1832 const& b, ___1832 const& e) : m_data(0) { allocate(static_cast<int>(std::distance(b, e) + 1)); ___1832 it = b; for (int i = 0; i < m_size - 1; ++i) m_data[i] = *(it++); ___478(it == e); m_data[m_size - 1] = '\0'; } inline SimpleVector<char>::SimpleVector(std::string const& str) : m_data(0) { allocate(static_cast<int>(str.size() + 1)); strcpy(m_data, str.c_str()); } inline SimpleVector<char>::SimpleVector(char const* data, int size) { allocate(size); if (m_size > 0) memcpy(m_data, data, m_size); } inline SimpleVector<char>::SimpleVector(int size, char ___4298  ) { allocate(size); for (int i = 0; i < m_size; ++i) m_data[i] = ___4298; } inline SimpleVector<char>::~SimpleVector() {
 #if defined _DEBUG
memset(m_data, 0x03, m_size); m_size = 0;
 #endif
delete[] m_data; } inline void SimpleVector<char>::allocate(int size) { m_size = size; if (m_size > 0) { m_data = new char[size]; } else { delete[] m_data; m_data = 0; } } inline char& SimpleVector<char>::operator[](int i) { REQUIRE(i < m_size); return m_data[i]; } inline char const& SimpleVector<char>::operator[](int i) const { REQUIRE(i < m_size); return m_data[i]; } inline SimpleVector<char>& SimpleVector<char>::operator=(SimpleVector<char> ___3392) { using std::swap; swap(m_size, ___3392.m_size); swap(m_data, ___3392.m_data); return *this; } }}
