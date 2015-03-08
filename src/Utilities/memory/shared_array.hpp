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
//// at compile time then shared_ptr<array<>>.  NOTE: This class will
//// not call the constructors or destructors for the elements in the
//// array.  For this reason we only allow instantiation with scalar
//// types.

#include <cstddef>

namespace DS {

///////////////////////////////////////////////////////////////////////////////
//// shared_array
///////////////////////////////////////////////////////////////////////////////

template<typename T>
class shared_array
{
    // This is because we do not call constructors or destructors
    // on the array elements.
    static_assert(std::is_scalar<T>::value == true,
                  "shared_array can only be instantiated with a scalar template parameter");

public:

    // Default constructor will not allocate control block.
    explicit shared_array();
    // Will always allocate control block
    explicit shared_array(size_t size);

    ~shared_array();

    shared_array(const shared_array&);
    shared_array(shared_array&&);

    const shared_array& operator= (const shared_array&);
    shared_array& operator= (shared_array&&);

    // Get/Set: No range checking, No null checking!
    // Hopefully this is not dereferencing the ptr
    const T& operator[] (size_t idx) const { return m_ctl->elem[idx]; }
    T& operator[] (size_t idx) { return m_ctl->elem[idx]; }

private:

    // Give up ownership and free memory if necessary
    void release();

    struct control
    {
        using ref_count_t = unsigned long;

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

    control* m_ctl;
};

// Probably not necessary to check this, but it should be true
// given the design goals of this class.
static_assert(sizeof(shared_array<int>) == sizeof(void*),
              "The memory footprint of this class is intended to occupy "
              "no more than the size of a raw pointer");

///////////////////////////////////////////////////////////////////////////////
//// Standard Constructors / Destructor
///////////////////////////////////////////////////////////////////////////////

template<typename T> shared_array<T>::shared_array() : m_ctl(nullptr) { }

template<typename T>
shared_array<T>::shared_array(size_t size)
    : m_ctl(reinterpret_cast<control*>(new char[offsetof(control, elem) + sizeof(T)*size]))
{
    m_ctl->ref_count = 1;
}

template<typename T>
inline shared_array<T>::~shared_array()
{
    release();
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

///////////////////////////////////////////////////////////////////////////////
//// Copying
///////////////////////////////////////////////////////////////////////////////

template<typename T>
inline shared_array<T>::shared_array(const shared_array<T>& sa)
    : m_ctl(sa.m_ctl)
{
    if (m_ctl)
        ++(m_ctl->ref_count);
}

template<typename T>
const shared_array<T>& shared_array<T>::operator= (const shared_array<T>& rhs)
{
    // If the objects are referring to the same control block
    // then just return
    if (this == &rhs || m_ctl == rhs.m_ctl)
        return *this;
    release();
    m_ctl = rhs.m_ctl;
    if (m_ctl)
        ++(m_ctl->ref_count);
    return *this;
}

///////////////////////////////////////////////////////////////////////////////
//// Moving
///////////////////////////////////////////////////////////////////////////////

template<typename T>
inline shared_array<T>::shared_array(shared_array<T>&& rvalue)
    : m_ctl(rvalue.m_ctl)
{
    rvalue.m_ctl = nullptr;
}

template<typename T>
shared_array<T>& shared_array<T>::operator= (shared_array<T>&& rhs)
{
    if (m_ctl == rhs.m_ctl) {
        if (this != &rhs)
            rhs.release();
        return *this;
    }
    release();
    m_ctl = rhs.m_ctl;
    rhs.m_ctl = nullptr;
    return *this;
}

} // namespace DS
