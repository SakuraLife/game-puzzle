
#ifndef __PUZZ_MATRIX__
#define __PUZZ_MATRIX__

#include<vector>
#include<mutex>

namespace game
{
  using std::vector;

  template<typename _T>
  class matrix
  {
    public:
      using size_type = typename vector<_T>::size_type;
      using value_type = _T;
      using reference = typename vector<_T>::reference;
      using const_reference = typename vector<_T>::const_reference;
    private:
      vector<_T> __data;
      size_type __row;
      size_type __col;

    public:
      matrix(): __data(), __row(0), __col(0)
      { }
      matrix(size_type __r, size_type __c = 1):
        __data(__r*__c), __row(__r), __col(__c)
      { }
      matrix(const matrix& __o):
        __data(__o.__data), __row(__o.__row), __col(__o.__col)
      { }
      matrix(matrix&& __o):
        __data(std::move(__o.__data)), __row(__o.__row), __col(__o.__col)
      { }

    public:
      matrix& operator=(const matrix& __other)
      {
        if(this != &__other)
        {
          this->__data = __other.__data;
          this->__col  = __other.__col;
          this->__row  = __other.__row;
        }
        return *this;
      }
      matrix& operator=(matrix&& __other)
      {
        if(this != &__other)
        {
          this->__data = std::move(__other.__data);
          this->__col  = __other.__col;
          this->__row  = __other.__row;
        }
        return *this;
      }

    public:
      size_type row() const noexcept
      { return this->__row;}
      size_type col() const noexcept
      { return this->__col;}
      size_type size() const noexcept
      { return this->__row* this->__col;}

    public:
      reference at(size_type __r, size_type __c) noexcept
      { return this->__data.operator[](__r*(this->__col)+__c);}
      const_reference at(size_type __r, size_type __c) const noexcept
      { return this->__data.operator[](__r*(this->__col)+__c);}
      value_type* data() noexcept
      { return this->__data.data();}
      const value_type* data() const noexcept
      { return this->__data.data();}

    public:
      reference operator[](size_type __pos) noexcept
      { return this->__data.operator[](__pos);}
      const_reference operator[](size_type __pos) const noexcept
      { return this->__data.operator[](__pos);}

    public:
      void init(const value_type& __value = value_type())
      {
        for(auto& __tmp: __data)
        { __tmp = __value;}
      }

    public:
      void resize(size_type __r, size_type __c)
      {
        if(this->__resize(__r*__c))
        {
          this->__row = __r;
          this->__col = __c;
        }
        return;
      }

    private:
      bool __resize(size_type __need)
      {
        if(__need == 0)
        {
          this->__data.clear();
          this->__row = this->__col = 0U;
          return false;
        }
        this->__data.resize(__need);
        return true;
      }
  };

}

#endif // ! __PUZZ_MATRIX__
