#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define DECLARE_SHARED( c )                        \
    class c;                                       \
    typedef std::shared_ptr<c>       c ## SP;      \
    typedef std::shared_ptr<c const> c ## ConstSP;

#define ASSERT( a )                                           \
    if( !(a) )                                                \
        throw std::runtime_error(                             \
            "assertion:" __FILE__ ":" TOSTRING(__LINE__) "\n" \
            #a                                                \
        );
