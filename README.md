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

| Construct | `lambda.cpp` | `template.cpp` |
| --- | --- | --- |
| `I` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L19-L28 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L18-L25 |
| `M` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L29-L38 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L26-L33 |
| `K` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L39-L52 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L34-L47 |
| `KI` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L53-L65 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L48-L60 |
| `C` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L66-L84 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L61-L81 |
| `B` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L249-L261 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L262-L276 |
| `B1` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L456-L469 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L480-L497 |

### Church Booleans

| Construct | `lambda.cpp` | `template.cpp` |
| --- | --- | --- |
| `T` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L85-L85 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L82-L82 |
| `F` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L86-L93 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L83-L88 |
| `NOT` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L94-L105 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L89-L98 |
| `AND` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L106-L120 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L99-L113 |
| `OR` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L121-L135 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L114-L128 |
| `BEQ` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L136-L149 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L129-L142 |
| `XOR` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L150-L168 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L143-L158 |

### Church Numerals and Arithmetic

| Construct | `lambda.cpp` | `template.cpp` |
| --- | --- | --- |
| `N0` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L169-L173 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L159-L167 |
| `N1` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L174-L178 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L168-L176 |
| `N2` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L179-L183 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L177-L185 |
| `N3` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L184-L211 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L186-L215 |
| `N4` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L222-L228 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L231-L235 |
| `N5` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L280-L286 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L300-L304 |
| `N6` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L294-L294 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L316-L317 |
| `N7` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L295-L303 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L318-L323 |
| `N8` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L310-L310 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L335-L335 |
| `N9` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L311-L320 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L336-L341 |
| `SUCC` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L212-L221 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L216-L230 |
| `PRED` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L229-L248 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L236-L261 |
| `SUCC2` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L262-L274 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L277-L292 |
| `ADD` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L275-L279 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L293-L299 |
| `MUL` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L287-L293 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L305-L315 |
| `POW` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L304-L309 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L324-L334 |
| `SUB` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L399-L413 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L426-L438 |

### Pairs and Projections

| Construct | `lambda.cpp` | `template.cpp` |
| --- | --- | --- |
| `V` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L334-L347 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L352-L368 |
| `PAIR` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L348-L353 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L369-L382 |
| `FST` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L354-L363 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L383-L391 |
| `SND` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L364-L374 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L392-L401 |
| `PHI` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L375-L386 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L402-L415 |
| `PRED2` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L387-L398 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L416-L425 |
| `SET_FST` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L479-L490 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L505-L517 |
| `SET_SND` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L491-L502 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L518-L541 |

### Comparisons

| Construct | `lambda.cpp` | `template.cpp` |
| --- | --- | --- |
| `IS_ZERO` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L321-L333 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L342-L351 |
| `LEQ` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L414-L427 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L439-L451 |
| `EQ` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L428-L441 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L452-L465 |
| `GT` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L442-L455 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L466-L479 |
| `GT2` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L470-L478 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L498-L504 |

### Fibonacci and Fixed-Point Combinators

| Construct | `lambda.cpp` | `template.cpp` |
| --- | --- | --- |
| `FIB` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L503-L527 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L542-L558 |
| `Y` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L528-L540 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L559-L569 |
| `Z` | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/lambda.cpp#L541-L551 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/18128901ff06f4e8e430e8e7c951ad5da17c1825/template.cpp#L570-L580 |

## Getting Started

Each file uses `static_assert` extensively, so compiling the translation unit is
also the test run.

Build with `make` compiles

- `lambda.cpp` with `-std=c++17`
- `template.cpp` with `-std=c++11`

## References
- A Flock of Functions: Combinators, Lambda Calculus, & Church Encodings in JS. [Code](https://github.com/glebec/lambda-talk) | [Website](https://glebec.github.io/lambda-talk/)
- Propositions as Types. [Paper](https://homepages.inf.ed.ac.uk/wadler/papers/propositions-as-types/propositions-as-types.pdf)
- C++ templates: Creating a compile-time higher-order meta-programming language. [Article](https://matt.might.net/articles/c++-template-meta-programming-with-lambda-calculus/)
- Translating Lambda Calculus into C++ Templates. [Paper](https://ksvi.mff.cuni.cz/~sefl/papers/lc_into_templates.pdf) | [Slides](https://www.lambdadays.org/static/upload/media/161672564665589vitsefltranslatinglambdacalculusintoctemplates.pdf)
