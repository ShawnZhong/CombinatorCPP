# Combinatory Logic in C++

This repository explores combinatory logic in two C++ encodings:

- [lambda.cpp](lambda.cpp): encoded as C++ 17 generic lambdas [[expr.prim.lambda]](https://eel.is/c++draft/expr.prim.lambda).
- [template.cpp](template.cpp): encoded as C++ 11 template structs (or metafunctions) [[temp.class]](https://eel.is/c++draft/temp.class).

We make the following [Curry–Howard correspondence](https://en.wikipedia.org/wiki/Curry%E2%80%93Howard_correspondence) among [Hilbert-style deduction systems](https://en.wikipedia.org/wiki/Hilbert_system), [combinatory logic](https://en.wikipedia.org/wiki/Combinatory_logic), and the two C++ encodings:

| Hilbert-style deduction | Combinatory logic | C++ lambda encoding | C++ template encoding |
| --- | --- | --- | --- |
| formula | combinator type (`A -> A`) | type of lambda (`decltype([](auto a) {  return a; })`) | struct (`struct I { template <typename A> using of = A; };`) |
| axiom scheme | primitive combinator (e.g., `I`) | primitive lambda (`[](auto a) { return a; }`) | primitive template struct (`struct I`) |
| proof | combinator term | lambda expression | template struct |
| modus ponens | combinator application (`F X`) | lambda application (`F(X)`) | template application (`ap<F, X>` or `F::of<X>`) |
| normalization | combinator reduction | lambda evaluation | template instantiation |

## Getting Started

Build with `make` compiles

- `lambda.cpp` with `-std=c++17`
- `template.cpp` with `-std=c++11`

## Constructs

### Basic Combinators

`I`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L14-L22 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L15-L21 |

`M`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L24-L32 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L23-L29 |

`K`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L34-L46 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L31-L43 |

`KI`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L48-L59 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L45-L56 |

`C`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L61-L78 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L58-L77 |

### Church Booleans

`T`, `F`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L80-L88 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L79-L85 |

`NOT`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L90-L100 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L87-L95 |

`AND`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L102-L115 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L97-L110 |

`OR`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L117-L130 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L112-L125 |

`BEQ`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L132-L144 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L127-L139 |

`XOR`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L146-L158 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L141-L153 |

### Church Numerals and Arithmetic

`SUCC`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L208-L223 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L214-L232 |

`PRED`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L225-L242 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L234-L257 |

`B`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L244-L256 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L259-L273 |

`SUCC2`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L258-L268 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L275-L289 |

`ADD`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L270-L281 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L291-L301 |

`MUL`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L283-L298 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L303-L320 |

`POW`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L300-L314 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L322-L338 |

`IS_ZERO`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L316-L326 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L340-L347 |

### Pairs and Comparisons

`V`, `PAIR`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L328-L348 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L349-L369 |

`FST`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L350-L358 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L371-L378 |

`SND`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L360-L368 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L380-L387 |

`PHI`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L370-L381 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L389-L402 |

`PRED2`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L384-L392 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L404-L412 |

`SUB`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L394-L407 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L414-L425 |

`LEQ`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L409-L421 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L427-L438 |

`EQ`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L423-L435 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L440-L452 |

`GT`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L437-L449 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L454-L465 |

`B1`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L451-L464 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L467-L484 |

`GT2`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L466-L473 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L486-L491 |

`SET_FST`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L475-L485 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L493-L504 |

`SET_SND`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L487-L497 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L506-L517 |

### Fibonacci and Fixed-Point Combinators

`FIB`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L499-L521 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L519-L544 |

`Y`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L523-L534 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L546-L555 |

`Z`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/lambda.cpp#L536-L551 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/0f6a609fbb916ef1accf7e69fc9d64b1697fd8bd/template.cpp#L557-L569 |


## References
- A Flock of Functions: Combinators, Lambda Calculus, & Church Encodings in JS. [Code](https://github.com/glebec/lambda-talk) | [Website](https://glebec.github.io/lambda-talk/)
- Propositions as Types. [Paper](https://homepages.inf.ed.ac.uk/wadler/papers/propositions-as-types/propositions-as-types.pdf)
- C++ templates: Creating a compile-time higher-order meta-programming language. [Article](https://matt.might.net/articles/c++-template-meta-programming-with-lambda-calculus/)
- Translating Lambda Calculus into C++ Templates. [Paper](https://ksvi.mff.cuni.cz/~sefl/papers/lc_into_templates.pdf) | [Slides](https://www.lambdadays.org/static/upload/media/161672564665589vitsefltranslatinglambdacalculusintoctemplates.pdf)
