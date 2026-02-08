#include <stdio.h>
#include <memory>
#include <string>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

typedef unsigned int uint;

template <class T>
class my_unique_ptr
{
private:
    T *ptr = nullptr;

public:
    my_unique_ptr() : ptr(nullptr) // default constructor
    {
    }

    my_unique_ptr(T *ptr) : ptr(ptr)
    {
    }

    my_unique_ptr(const my_unique_ptr &obj) = delete;            // copy constructor is deleted
    my_unique_ptr &operator=(const my_unique_ptr &obj) = delete; // copy assignment is deleted

    my_unique_ptr(my_unique_ptr &&dyingObj) // move constructor
    {
        // Transfer ownership of the memory pointed by dyingObj to this object
        this->ptr = dyingObj.ptr;
        dyingObj.reset();
    }

    void operator=(my_unique_ptr &&dyingObj) // move assignment
    {
        __cleanup__(); // cleanup any existing data

        // Transfer ownership of the memory pointed by dyingObj to this object
        this->ptr = dyingObj.ptr;
        dyingObj.reset();
    }

    T *operator->() // deferencing arrow operator
    {
        return this->ptr;
    }

    T &operator*()
    {
        return *(this->ptr);
    }

    T *get()
    {
        return ptr;
    }

    ~my_unique_ptr() // destructor
    {
        __cleanup__();
    }
    template <typename _Function>
    bool memcpy(_Function copy_fn)
    {
        bool success = false;
        if (copy_fn(this))
        {
            reset();
            success = true;
        }
        return success;
    }

    void reset()
    {
        ptr = nullptr;
    }

private:
    void __cleanup__()
    {
        if (ptr != nullptr)
            delete ptr;
    }
};

template <class T>
class my_unique_ptr<T[]>
{
private:
    T *ptr = nullptr;

public:
    my_unique_ptr() : ptr(nullptr) // default constructor
    {
    }

    my_unique_ptr(T *ptr) : ptr(ptr)
    {
    }

    my_unique_ptr(const my_unique_ptr &obj) = delete;            // copy constructor is deleted
    my_unique_ptr &operator=(const my_unique_ptr &obj) = delete; // copy assignment is deleted

    my_unique_ptr(my_unique_ptr &&dyingObj) // move constructor
    {
        __cleanup__(); // cleanup any existing data

        // Transfer ownership of the memory pointed by dyingObj to this object
        this->ptr = dyingObj.ptr;
        dyingObj.ptr = nullptr;
    }

    void operator=(my_unique_ptr &&dyingObj) // move assignment
    {
        __cleanup__(); // cleanup any existing data

        // Transfer ownership of the memory pointed by dyingObj to this object
        this->ptr = dyingObj.ptr;
        dyingObj.ptr = nullptr;
    }

    T *operator->() // deferencing arrow operator
    {
        return this->ptr;
    }

    T &operator*()
    {
        return *(this->ptr);
    }

    T &operator[](int index)
    {
        if (index < 0)
        {
            // Throw negative index exception
            throw(new std::exception());
        }
        return this->ptr[index]; // doesn't check out of bounds
    }

    ~my_unique_ptr() // destructor
    {
        __cleanup__();
    }

private:
    void __cleanup__()
    {
        if (ptr != nullptr)
            delete[] ptr;
    }
};
template <class T>
class my_shared_ptr
{
private:
    T *ptr = nullptr;
    uint *refCount = nullptr;

public:
    my_shared_ptr() : ptr(nullptr), refCount(new uint(0)) // default constructor
    {
    }

    my_shared_ptr(T *ptr) : ptr(ptr), refCount(new uint(1)) // constructor
    {
    }

    /*** Copy Semantics ***/
    my_shared_ptr(const my_shared_ptr &obj) // copy constructor
    {
        this->ptr = obj.ptr; // share the underlying pointer
        this->refCount = obj.refCount;
        if (nullptr != obj.ptr)
        {
            (*this->refCount)++; // if the pointer is not null, increment the refCount
        }
    }

    my_shared_ptr &operator=(const my_shared_ptr &obj) // copy assignment
    {
        __cleanup__(); // cleanup any existing data

        // Assign incoming object's data to this object
        this->ptr = obj.ptr; // share the underlying pointer
        this->refCount = obj.refCount;
        if (nullptr != obj.ptr)
        {
            (*this->refCount)++; // if the pointer is not null, increment the refCount
        }
    }

    /*** Move Semantics ***/
    my_shared_ptr(my_shared_ptr &&dyingObj) // move constructor
    {
        this->ptr = dyingObj.ptr; // share the underlying pointer
        this->refCount = dyingObj.refCount;

        dyingObj.ptr = dyingObj.refCount = nullptr; // clean the dying object
    }

    my_shared_ptr &operator=(my_shared_ptr &&dyingObj) // move assignment
    {
        __cleanup__(); // cleanup any existing data

        this->ptr = dyingObj.ptr; // share the underlying pointer
        this->refCount = dyingObj.refCount;

        dyingObj.ptr = dyingObj.refCount = nullptr; // clean the dying object
    }

    uint get_count() const
    {
        return *refCount; // *this->refCount
    }

    T *get() const
    {
        return this->ptr;
    }

    T *operator->() const
    {
        return this->ptr;
    }

    T &operator*() const
    {
        return *this->ptr;
    }

    struct memcpy_callable
    {
        my_shared_ptr<T> *src;
        bool operator()()
        {
            memcpy(this->src, src, sizeof(*src));
            return true;
        }
    };
    template <typename _Function>
    bool memcpy(_Function copy_fn)
    {
        bool success = false;
        if (copy_fn(this))
        {
            if (nullptr != ptr)
            {
                (*this->refCount)++; // if the pointer is not null, increment the refCount
            }
            success = true;
        }
        return success;
    }

    ~my_shared_ptr() // destructor
    {
        __cleanup__();
    }

private:
    void __cleanup__()
    {
        (*refCount)--;
        if (*refCount == 0)
        {
            if (nullptr != ptr)
                delete ptr;
            delete refCount;
        }
    }
};
my_unique_ptr<string> matthew2;

int main()
{
    char a = 'a';
    // creates a my_unique_ptr object holding a 'Box' object
    {
        my_unique_ptr<string> matthew(new string("matthew"));

        matthew.memcpy([](my_unique_ptr<string> *src)
                       { memcpy(&matthew2, src, sizeof(*src));
                    return true; });
        assert(matthew.get() == nullptr);
        assert(*matthew2 == "matthew");
    }
    my_shared_ptr<string> busoye2;

    {
        my_shared_ptr<string> busoye(new string("busoye"));
        assert(busoye.get_count() == 1);
        assert(*busoye == "busoye");

        busoye.memcpy([&busoye2](my_shared_ptr<string> *src)
                      { memcpy(&busoye2, src, sizeof(*src));
                    return true; });
        assert(busoye.get_count() == 2);
        assert(busoye2.get_count() == 2);
        assert(*busoye == "busoye");

        assert(busoye.get() != nullptr);
        assert(*busoye2 == "busoye");

        for_each(busoye2.get()->begin(), busoye2.get()->end(), [](char &c)
                 { c = toupper(c);printf("%c", c); });
    }
    assert(busoye2.get_count() == 1);
    assert(*busoye2 == "BUSOYE");
    // creates a my_unique_ptr object holding an array of 'Box' objects
    return 0;
}
