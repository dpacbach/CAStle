////
//// class: shared_array
////
//// This is a class which manages shared, reference-counted, fixed-size
//// array allocated on the heap.  Size of array is specified at runtime
//// and reference count is allocated together with array.  Size of array
//// is neither kept in the shared_array object itself nor on the heap.
////
//// Because the size is not known to the class after construction and
//// because we want to allocate the reference count together with the
//// array data this means that the class will not be able to call the
//// destructors on the array elements, and hence it will not call the
//// constructors initially.  Because of this, use of this template is
//// allowed only for scalar types.
////
//// The current C++ standard (C++14) supports shared_ptr's to C arrays
//// (when provided with a custom deleter) but therefore cannot be
//// used with make_shared.  Boost 1.53 has a make_shared which works
//// with their C array specialization of shared_ptr but the standard
//// library does not have it and it is not clear if the opporunity for
//// optimization provided by make_shared will always be taken by all
//// compilers in all situations.
////
//// This class is only needed in cases when optimization is critical.
//// Otherwise, a shared_ptr<vector<>> is fine, or if the size is known
//// at compile time then shared_ptr<array<>>.
////

#include <cstddef>
#include <iostream>
#include <type_traits>

using std::cout;
using std::endl;

namespace DS {

template<typename T>
class shared_array
{
    // This is because we do not call constructors or destructors
    // on the array elements.
    static_assert(std::is_scalar<T>::value == true,
                  "shared_array can only be parametrized with a scalar type!");

public:

    // constructor needs to default initialize elements... or does it?
    shared_array() = delete;

    explicit shared_array(size_t size);
    ~shared_array();

    shared_array(const shared_array&);
    shared_array(shared_array&&);

    const shared_array& operator= (const shared_array&);
    const shared_array& operator= (shared_array&&);

    // Get/Set: No range checking
    // Hopefully this is not dereferencing the ptr
    T& operator[] (size_t idx) { return m_ctl->elem[idx]; }

private:

    // Give up ownership and free memory if necessary
    void release();

    struct control
    {
        using ref_count_t = unsigned int;

        control()                                  = delete;
        ~control()                                 = delete;
        control(const control&)                    = delete;
        control(control&&)                         = delete;
        const control& operator= (const control&)  = delete;
        const control& operator= (control&&)       = delete;

        ref_count_t ref_count;
        // Array can actually be empty, but we put size 1 here
        // to satisfy the compiler.
        T elem[1];
    };

    // This is non const to allow for moves
    control* m_ctl;
};

// Probably not necessary to check this, but it should be true
static_assert(sizeof(shared_array<int>) == sizeof(void*),
              "sizeof(shared_array) should be that of a single pointer!");

template<typename T>
shared_array<T>::shared_array(size_t size)
{
    // Consider putting this in the initializer list
    size_t target = offsetof(control, elem) + sizeof(T)*size;
    cout << "constructor (#bytes == " << target << ")" << endl;
    m_ctl = (control*)(new char[target]);
    m_ctl->ref_count = 0;
}

template<typename T>
void shared_array<T>::release()
{
    if (m_ctl) {
        if (!(--(m_ctl->ref_count)))
            delete[] reinterpret_cast<char*>(m_ctl);
        m_ctl = nullptr;
    }
}

template<typename T>
inline shared_array<T>::~shared_array()
{
    cout << "destructor" << endl;
    release();
}

template<typename T>
inline shared_array<T>::shared_array(const shared_array<T>& sa)
    : m_ctl(sa.m_ctl)
{
    cout << "copy constructor" << endl;
    ++(m_ctl->ref_count);
}

template<typename T>
inline shared_array<T>::shared_array(shared_array<T>&& sa)
    : m_ctl(std::move(sa.m_ctl))
{
    cout << "move constructor.  sa.m_ctl == " << sa.m_ctl << " ==? nullptr" << endl;
    // Verify this
    //sa.m_ctl = nullptr;
}

template<typename T>
const shared_array<T>& shared_array<T>::operator= (const shared_array<T>& rhs)
{
    cout << "copy assignment" << endl;
    if (this == &rhs || m_ctl == rhs.m_ctl)
        return;
    release();
    m_ctl = rhs.m_ctl;
    if (m_ctl)
        ++m_ctl->ref_count;
}

template<typename T>
const shared_array<T>& shared_array<T>::operator= (shared_array<T>&& rhs)
{
    cout << "move assignment" << endl;
    if (m_ctl == rhs.m_ctl) {
        if (this != &rhs)
            rhs.release();
        return;
    }
    release();
    m_ctl = std::move(rhs.m_ctl);
    // Verify this
    //rhs.m_ctl = nullptr;
}


} // namespace DS
