# Combinatory Logic in C++

This repository explores combinatory logic in two C++ encodings:

- [lambda.cpp](lambda.cpp): encoded as C++ 17 generic lambdas [[expr.prim.lambda]](https://eel.is/c++draft/expr.prim.lambda).
- [template.cpp](template.cpp): encoded with C++ 11 template metaprogramming (i.e., metafunctions) [[temp.class]](https://eel.is/c++draft/temp.class).

We observe the [Curry–Howard correspondence](https://en.wikipedia.org/wiki/Curry%E2%80%93Howard_correspondence) among [Hilbert-style deduction systems](https://en.wikipedia.org/wiki/Hilbert_system), [combinatory logic](https://en.wikipedia.org/wiki/Combinatory_logic), and the two C++ encodings:

| Hilbert-style deduction | Combinatory logic | C++ lambda encoding | C++ template encoding |
| --- | --- | --- | --- |
| formula | combinator type (`A -> A`) | type of lambda (`decltype([](auto a) { return a; })`) | struct (`struct I { template <typename A> using of = A; };`) |
| axiom scheme | primitive combinator (e.g., `I`) | primitive lambda (`[](auto a) { return a; }`) | primitive template struct (`struct I`) |
| proof | combinator term | lambda expression | template struct |
| modus ponens | combinator application (`F X`) | lambda application (`F(X)`) | template application (`F::of<X>` or `ap<F, X>`) |
| normalization | combinator reduction | lambda evaluation | template instantiation |

## Getting Started

Build with `make` compiles

- `lambda.cpp` with `-std=c++17`
- `template.cpp` with `-std=c++11`

## Constructs

### Basic Combinators

`I`: Identity combinator, aka idiot combinator. `I x = x`.

<!-- ANCHOR-BEGIN: I -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L13-L17 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L14-L18 |
<!-- ANCHOR-END: I -->

`M`: Mockingbird combinator. `M f = f f`.

<!-- ANCHOR-BEGIN: M -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L21-L25 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L22-L26 |
<!-- ANCHOR-END: M -->

`K`: Kestrel combinator, aka constant combinator. `K a b = a`.

<!-- ANCHOR-BEGIN: K -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L29-L37 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L30-L39 |
<!-- ANCHOR-END: K -->

`KI`: Kite combinator, equivalent to `K I` and `C K`. `KI a b = b`.

<!-- ANCHOR-BEGIN: KI -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L41-L48 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L43-L51 |
<!-- ANCHOR-END: KI -->

`C`: Cardinal combinator, aka flip combinator. `C f a b = f b a`.

<!-- ANCHOR-BEGIN: C -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L52-L65 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L55-L70 |
<!-- ANCHOR-END: C -->

### Church Booleans

Booleans are encoded as branch selectors.

`T`, `F`: Church booleans. `T x y = x`; `F x y = y`.

<!-- ANCHOR-BEGIN: T_F -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L69-L74 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L74-L79 |
<!-- ANCHOR-END: T_F -->

`NOT`: Boolean negation, equivalent to `C`. `NOT p = p F T`.

<!-- ANCHOR-BEGIN: NOT -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L78-L85 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L83-L90 |
<!-- ANCHOR-END: NOT -->

`AND`: Conjunction. `AND p q = p q F = p q p`.

<!-- ANCHOR-BEGIN: AND -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L89-L99 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L94-L105 |
<!-- ANCHOR-END: AND -->

`OR`: Boolean disjunction, equivalent to `M*`. `OR p q = p T q = p p q`.

<!-- ANCHOR-BEGIN: OR -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L103-L113 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L109-L120 |
<!-- ANCHOR-END: OR -->

`BEQ`: Boolean equality. `BEQ p q = p q (NOT q)`.

<!-- ANCHOR-BEGIN: BEQ -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L117-L126 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L124-L134 |
<!-- ANCHOR-END: BEQ -->

`XOR`: Exclusive disjunction. `XOR p q = p (NOT q) q`.

<!-- ANCHOR-BEGIN: XOR -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L130-L139 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L138-L148 |
<!-- ANCHOR-END: XOR -->

### Church Numerals and Arithmetic

Church numerals encode a natural number as repeated application of a function to a seed value.

`SUCC`: Successor. `SUCC n f x = f (n f x)`.

<!-- ANCHOR-BEGIN: SUCC -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L185-L197 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L207-L222 |
<!-- ANCHOR-END: SUCC -->

`PRED`: Predecessor via a shifting helper. `PRED n f x = n shift (K x) I`, where `shift f g = C I (g f)`.

<!-- ANCHOR-BEGIN: PRED -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L201-L215 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L226-L245 |
<!-- ANCHOR-END: PRED -->

`B`: Bluebird combinator. `B f g x = f (g x)`.

<!-- ANCHOR-BEGIN: B -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L219-L227 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L249-L259 |
<!-- ANCHOR-END: B -->

`SUCC2`: Successor expressed through `B`. `SUCC2 n f x = B f (n f) x`.

<!-- ANCHOR-BEGIN: SUCC2 -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L231-L238 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L263-L274 |
<!-- ANCHOR-END: SUCC2 -->

`ADD`: Addition. `ADD n k = n SUCC k`.

<!-- ANCHOR-BEGIN: ADD -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L242-L249 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L278-L286 |
<!-- ANCHOR-END: ADD -->

`MUL`: Multiplication, equivalent to `B`. `MUL n k f = n (k f)`.

<!-- ANCHOR-BEGIN: MUL -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L253-L265 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L290-L304 |
<!-- ANCHOR-END: MUL -->

`POW`: Exponentiation, equivalent to the Thrush combinator. `POW n k = k n`.

<!-- ANCHOR-BEGIN: POW -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L269-L280 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L308-L321 |
<!-- ANCHOR-END: POW -->

`IS_ZERO`: Zero test. `IS_ZERO n = n (K F) T`.

<!-- ANCHOR-BEGIN: IS_ZERO -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L284-L290 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L325-L331 |
<!-- ANCHOR-END: IS_ZERO -->

### Pairs and Comparisons

Pairs are encoded as functions that hand two stored values to a selector.

`V`, `PAIR`: Vireo combinator, equivalent to `B C T`. `PAIR` is an alias of `V`. `V a b f = f a b`.

<!-- ANCHOR-BEGIN: V_PAIR -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L294-L307 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L335-L351 |
<!-- ANCHOR-END: V_PAIR -->

`FST`: First projection. `FST p = p K`.

<!-- ANCHOR-BEGIN: FST -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L311-L316 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L355-L361 |
<!-- ANCHOR-END: FST -->

`SND`: Second projection. `SND p = p KI`.

<!-- ANCHOR-BEGIN: SND -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L320-L325 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L365-L371 |
<!-- ANCHOR-END: SND -->

`PHI`: Pair transformer used in predecessor constructions. `PHI p = PAIR (SND p) (SUCC (SND p))`.

<!-- ANCHOR-BEGIN: PHI -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L329-L336 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L375-L386 |
<!-- ANCHOR-END: PHI -->

`PRED2`: Predecessor expressed through `PHI`. `PRED2 n = FST (n PHI (PAIR N0 N0))`.

<!-- ANCHOR-BEGIN: PRED2 -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L340-L346 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L390-L397 |
<!-- ANCHOR-END: PRED2 -->

`SUB`: Subtraction. `SUB n k = k PRED n`.

<!-- ANCHOR-BEGIN: SUB -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L350-L359 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L401-L410 |
<!-- ANCHOR-END: SUB -->

`LEQ`: Less-than-or-equal. `LEQ n k = IS_ZERO (SUB n k)`.

<!-- ANCHOR-BEGIN: LEQ -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L363-L371 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L414-L423 |
<!-- ANCHOR-END: LEQ -->

`EQ`: Equality. `EQ n k = AND (LEQ n k) (LEQ k n)`.

<!-- ANCHOR-BEGIN: EQ -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L375-L383 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L427-L437 |
<!-- ANCHOR-END: EQ -->

`GT`: Greater-than. `GT n k = NOT (LEQ n k)`.

<!-- ANCHOR-BEGIN: GT -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L387-L395 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L441-L450 |
<!-- ANCHOR-END: GT -->

`B1`: Blackbird combinator, equivalent to `B B B`. `B1 f g a b = f (g a b)`.

<!-- ANCHOR-BEGIN: B1 -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L399-L408 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L454-L466 |
<!-- ANCHOR-END: B1 -->

`GT2`: Greater-than expressed through `B1`. `GT2 n k = B1 NOT LEQ n k`.

<!-- ANCHOR-BEGIN: GT2 -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L412-L416 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L470-L474 |
<!-- ANCHOR-END: GT2 -->

`SET_FST`: Update the first element of a pair. `SET_FST x p = PAIR x (SND p)`.

<!-- ANCHOR-BEGIN: SET_FST -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L420-L427 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L478-L487 |
<!-- ANCHOR-END: SET_FST -->

`SET_SND`: Update the second element of a pair. `SET_SND x p = PAIR (FST p) x`.

<!-- ANCHOR-BEGIN: SET_SND -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L431-L438 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L491-L500 |
<!-- ANCHOR-END: SET_SND -->

### Fibonacci and Fixed-Point Combinators

These examples show nontrivial compositions and direct lambda-term translations.

`FIB`: Fibonacci over Church numerals. `FIB n = n step K N0 N1`, where `step f a b = f b (ADD a b)`.

<!-- ANCHOR-BEGIN: FIB -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L442-L461 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L504-L526 |
<!-- ANCHOR-END: FIB -->

`Y`: Direct syntactic translation of the classic fixed-point combinator. It is not usable here under eager C++ evaluation.

<!-- ANCHOR-BEGIN: Y -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L465-L472 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L530-L536 |
<!-- ANCHOR-END: Y -->

`Z`: Delayed fixed-point variant. The C++ type system still prevents direct use here.

<!-- ANCHOR-BEGIN: Z -->
| `lambda.cpp` | `template.cpp` |
| --- | --- |
| https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/lambda.cpp#L476-L487 | https://github.com/ShawnZhong/combinatory_logic.cpp/blob/a163714635679396be89e39a89cc009c168cfc63/template.cpp#L540-L549 |
<!-- ANCHOR-END: Z -->


## Further Reading
Combinatory Logic
- Wikipedia: Combinatory Logic. [Link](https://en.wikipedia.org/wiki/Combinatory_logic)
- A Flock of Functions: Combinators, Lambda Calculus, & Church Encodings in JS. [Code](https://github.com/glebec/lambda-talk) | [Website](https://glebec.github.io/lambda-talk/) | [Video](https://www.youtube.com/playlist?list=PLpkHU923F2XFWv-XfVuvWuxq41h21nOPK) | [Slides](https://speakerdeck.com/glebec/lambda-as-js-or-a-flock-of-functions-combinators-lambda-calculus-and-church-encodings-in-javascript)
- To Mock a Mocking Bird: Including an Amazing Adventure in Combinatory Logic. [PDF](https://douxnet.weebly.com/uploads/2/0/4/1/20418601/raymond_m._smullyan-to_mock_a_mockingbird_and_other_logic_puzzles__including__an_amazing_adventure_in_combinatory_logic-knopf_1985.pdf) | [Wiki](https://en.wikipedia.org/wiki/To_Mock_a_Mockingbird)

Curry–Howard correspondence
- Wikipedia: Curry–Howard Correspondence. [Link](https://en.wikipedia.org/wiki/Curry%E2%80%93Howard_correspondence)
- Stanford Encyclopedia: Intuitionistic Type Theory. [Link](https://plato.stanford.edu/entries/type-theory-intuitionistic/)
- Propositions as Types. [Paper](https://homepages.inf.ed.ac.uk/wadler/papers/propositions-as-types/propositions-as-types.pdf)

C++ Metaprogramming
- C++ Metafunctions. [Article](https://bietola.github.io/5mincode/2018/09/24/C++-metafunctions.html)
- What is C++ metafunction and how to use it? [Article](https://iamsorush.com/posts/cpp-meta-function/)
- Your own type predicate. [Article](https://akrzemi1.wordpress.com/2017/12/02/your-own-type-predicate/)
- Expressive C++ Template Metaprogramming. [Article](https://www.fluentcpp.com/2017/06/02/write-template-metaprogramming-expressively/)
- CppCon 2014: Walter E. Brown "Modern Template Metaprogramming: A Compendium". [Part 1 Video](https://www.youtube.com/watch?v=Am2is2QCvxY) | [Part 2 Video](https://www.youtube.com/watch?v=a0FliKwcwXE) | [Slides](https://github.com/CppCon/CppCon2014/blob/master/Presentations/Modern%20Template%20Metaprogramming%20-%20A%20Compendium/Modern%20Template%20Metaprogramming%20-%20A%20Compendium%20-%20Walter%20E%20Brown%20-%20CppCon%202014.pdf)

Turing Completeness of C++ Templates
- C++ Templates are Turing Complete. [Paper](https://rtraba.com/wp-content/uploads/2015/05/cppturing.pdf)
- C++ templates: Creating a compile-time higher-order meta-programming language. [Article](https://matt.might.net/articles/c++-template-meta-programming-with-lambda-calculus/)
- Translating Lambda Calculus into C++ Templates. [Paper](https://ksvi.mff.cuni.cz/~sefl/papers/lc_into_templates.pdf) | [Slides](https://www.lambdadays.org/static/upload/media/161672564665589vitsefltranslatinglambdacalculusintoctemplates.pdf)
- [C++] is Turing Complete. [Article](https://blog.tal.bi/posts/cpp-syntax-tc/)
- Template (Compile-time) Turing Machine in C++20. [Code](https://github.com/Eren121/CppTuringMachine/)
- C++ Templates are turing complete - So why not make them usable in that way? [Code](https://github.com/197g/Functional-Cpp-Templates)
