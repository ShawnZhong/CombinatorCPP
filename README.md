# Combinatory Logic in C++

This repository explores combinatory logic in two C++ encodings:

- [lambda.cpp](lambda.cpp): terms encoded with C++ 17 generic lambdas [[expr.prim.lambda]](https://eel.is/c++draft/expr.prim.lambda).
- [template.cpp](template.cpp): terms encoded with C++ 11 template metaprogramming as structs [[temp.class]](https://eel.is/c++draft/temp.class).

We make the following [Curry–Howard correspondence](https://en.wikipedia.org/wiki/Curry%E2%80%93Howard_correspondence) among a [Hilbert-style deduction system](https://en.wikipedia.org/wiki/Hilbert_system), [combinatory logic](https://en.wikipedia.org/wiki/Combinatory_logic), and the two C++ encodings:

| Hilbert-style deduction | Combinatory logic | C++ lambda encoding | C++ template encoding |
| --- | --- | --- | --- |
| formula | combinator type (`A -> A`) | type of lambda (`decltype([](auto a) {  return a; })`) | struct (`struct I { template <typename A> using of = A; };`) |
| axiom scheme | primitive combinator (e.g., `I`) | primitive lambda (`[](auto a) { return a; }`) | primitive template struct (`struct I`) |
| proof | combinator term | lambda expression | template struct |
| modus ponens | combinator application (`F X`) | lambda application (`F(X)`) | template application (`ap<F, X>` or `F::of<X>`) |
| normalization | combinator reduction | lambda evaluation | template instantiation |

## Constructs

### Basic Combinators

`I`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L14-L22 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L18-L25 |

`M`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L24-L32 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L26-L33 |

`K`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L34-L46 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L34-L47 |

`KI`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L48-L59 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L48-L60 |

`C`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L61-L78 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L61-L81 |

### Church Booleans

`T`, `F`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L80-L88 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L82-L82 |

`NOT`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L90-L100 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L89-L98 |

`AND`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L102-L115 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L99-L113 |

`OR`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L117-L130 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L114-L128 |

`BEQ`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L132-L144 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L129-L142 |

`XOR`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L146-L158 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L143-L158 |

### Church Numerals and Arithmetic

`SUCC`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L208-L223 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L216-L230 |

`PRED`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L225-L242 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L236-L261 |

`B`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L244-L256 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L262-L276 |

`SUCC2`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L258-L268 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L277-L292 |

`ADD`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L270-L281 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L293-L299 |

`MUL`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L283-L298 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L305-L315 |

`POW`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L300-L314 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L324-L334 |

`IS_ZERO`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L316-L326 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L342-L351 |

### Pairs and Comparisons

`V`, `PAIR`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L328-L348 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L352-L368 |

`FST`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L350-L358 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L383-L391 |

`SND`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L360-L368 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L392-L401 |

`PHI`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L370-L381 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L402-L415 |

`PRED2`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L384-L392 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L416-L425 |

`SUB`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L394-L407 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L426-L438 |

`LEQ`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L409-L421 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L439-L451 |

`EQ`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L423-L435 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L452-L465 |

`GT`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L437-L449 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L466-L479 |

`B1`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L451-L464 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L480-L497 |

`GT2`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L466-L473 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L498-L504 |

`SET_FST`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L475-L485 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L505-L517 |

`SET_SND`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L487-L497 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L518-L541 |

### Fibonacci and Fixed-Point Combinators

`FIB`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L499-L521 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L542-L558 |

`Y`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L523-L534 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L559-L569 |

`Z`

| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L536-L551 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L570-L580 |

## Build

Build with `make` compiles

- `lambda.cpp` with `-std=c++17`
- `template.cpp` with `-std=c++11`

## References
- A Flock of Functions: Combinators, Lambda Calculus, & Church Encodings in JS. [Code](https://github.com/glebec/lambda-talk) | [Website](https://glebec.github.io/lambda-talk/)
- Propositions as Types. [Paper](https://homepages.inf.ed.ac.uk/wadler/papers/propositions-as-types/propositions-as-types.pdf)
- C++ templates: Creating a compile-time higher-order meta-programming language. [Article](https://matt.might.net/articles/c++-template-meta-programming-with-lambda-calculus/)
- Translating Lambda Calculus into C++ Templates. [Paper](https://ksvi.mff.cuni.cz/~sefl/papers/lc_into_templates.pdf) | [Slides](https://www.lambdadays.org/static/upload/media/161672564665589vitsefltranslatinglambdacalculusintoctemplates.pdf)
