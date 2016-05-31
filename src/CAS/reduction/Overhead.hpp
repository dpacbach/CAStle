#pragma once

namespace  DS            {
namespace  CAS           {
namespace  Expressions   {
namespace  Visitors      {
namespace  Restructurers {
namespace  Reduction     {

typedef    Expression::Ptr      EP;

#define    CSTR(a)              public: a(std::shared_ptr<Numbers::NumberFactory> _nFactory, \
                                std::shared_ptr<Expressions::Builder> _eBuilder) \
                                : Restructurer(_nFactory, _eBuilder) { } private:
#define    ALGORITHM(a, b)      class a : public Visitors::Restructurer { CSTR(a) b };
#define    MEMBER(b,c)          virtual EP b(const c& exp, const std::vector<EP>& children);

#define    ADD                  MEMBER (add,      Add      )
#define    DIVIDE               MEMBER (divide,   Divide   )
#define    FACTORIAL            MEMBER (factorial,Factorial)
#define    LITERAL              MEMBER (literal,  Literal  )
#define    MODULUS              MEMBER (modulus,  Modulus  )
#define    MULTIPLY             MEMBER (multiply, Multiply )
#define    NEGATE               MEMBER (negate,   Negate   )
#define    POWER                MEMBER (power,    Power    )
#define    SYMBOL               MEMBER (symbol,   Symbol   )

}}}}}}
