#pragma once

#include "Restructurer.hpp"
#include "Overhead.hpp"

namespace  DS            {
namespace  CAS           {
namespace  Expressions   {
namespace  Visitors      {
namespace  Restructurers {
namespace  Reduction     {

ALGORITHM  (BasicSymbols,       SYMBOL)
ALGORITHM  (ComplexSplitter,    LITERAL)
ALGORITHM  (Rationalizer,       LITERAL)
ALGORITHM  (ComplexNormalizer,  DIVIDE)
ALGORITHM  (ComplexExpander,    DIVIDE)
ALGORITHM  (GCDLiteral,         DIVIDE)
ALGORITHM  (SizeOneArray,       ADD MULTIPLY)
ALGORITHM  (SelfNesting,        ADD DIVIDE MULTIPLY NEGATE POWER)
ALGORITHM  (Negatives,          ADD DIVIDE MULTIPLY POWER LITERAL)
ALGORITHM  (FirstOrderBasic,    DIVIDE MULTIPLY POWER NEGATE)
ALGORITHM  (NumberReducerBasic, ADD DIVIDE MULTIPLY NEGATE POWER)

}}}}}}
