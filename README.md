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
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L15-L19</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L27-L32</td>
  </tr>
</table>
<!-- ANCHOR-END: I -->

`M`: Mockingbird combinator. `M f = f f`.

<!-- ANCHOR-BEGIN: M -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L23-L27</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L36-L41</td>
  </tr>
</table>
<!-- ANCHOR-END: M -->

`K`: Kestrel combinator, aka constant combinator. `K a b = a`.

<!-- ANCHOR-BEGIN: K -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L31-L39</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L45-L57</td>
  </tr>
</table>
<!-- ANCHOR-END: K -->

`KI`: Kite combinator, equivalent to `K I` and `C K`. `KI a b = b`.

<!-- ANCHOR-BEGIN: KI -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L43-L50</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L61-L72</td>
  </tr>
</table>
<!-- ANCHOR-END: KI -->

`C`: Cardinal combinator, aka flip combinator. `C f a b = f b a`.

<!-- ANCHOR-BEGIN: C -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L54-L67</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L76-L96</td>
  </tr>
</table>
<!-- ANCHOR-END: C -->

### Church Booleans

Booleans are encoded as branch selectors.

`T`, `F`: Church booleans. `T x y = x`; `F x y = y`.

<!-- ANCHOR-BEGIN: T_F -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L71-L76</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L100-L105</td>
  </tr>
</table>
<!-- ANCHOR-END: T_F -->

`NOT`: Boolean negation, equivalent to `C`. `NOT p = p F T`.

<!-- ANCHOR-BEGIN: NOT -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L80-L87</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L109-L117</td>
  </tr>
</table>
<!-- ANCHOR-END: NOT -->

`AND`: Conjunction. `AND p q = p q F = p q p`.

<!-- ANCHOR-BEGIN: AND -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L91-L101</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L121-L136</td>
  </tr>
</table>
<!-- ANCHOR-END: AND -->

`OR`: Boolean disjunction, equivalent to `M*`. `OR p q = p T q = p p q`.

<!-- ANCHOR-BEGIN: OR -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L105-L115</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L140-L155</td>
  </tr>
</table>
<!-- ANCHOR-END: OR -->

`BEQ`: Boolean equality. `BEQ p q = p q (NOT q)`.

<!-- ANCHOR-BEGIN: BEQ -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L119-L128</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L159-L172</td>
  </tr>
</table>
<!-- ANCHOR-END: BEQ -->

`XOR`: Exclusive disjunction. `XOR p q = p (NOT q) q`.

<!-- ANCHOR-BEGIN: XOR -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L132-L141</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L176-L189</td>
  </tr>
</table>
<!-- ANCHOR-END: XOR -->

### Church Numerals and Arithmetic

Church numerals encode a natural number as repeated application of a function to a seed value.

`SUCC`: Successor. `SUCC n f x = f (n f x)`.

<!-- ANCHOR-BEGIN: SUCC -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L190-L202</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L264-L283</td>
  </tr>
</table>
<!-- ANCHOR-END: SUCC -->

`PRED`: Predecessor via a shifting helper. `PRED n f x = n shift (K x) I`, where `shift f g = C I (g f)`.

<!-- ANCHOR-BEGIN: PRED -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L206-L221</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L287-L314</td>
  </tr>
</table>
<!-- ANCHOR-END: PRED -->

`B`: Bluebird combinator. `B f g x = f (g x)`.

<!-- ANCHOR-BEGIN: B -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L225-L233</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L318-L333</td>
  </tr>
</table>
<!-- ANCHOR-END: B -->

`SUCC2`: Successor expressed through `B`. `SUCC2 n f x = B f (n f) x`.

<!-- ANCHOR-BEGIN: SUCC2 -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L237-L244</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L337-L353</td>
  </tr>
</table>
<!-- ANCHOR-END: SUCC2 -->

`ADD`: Addition. `ADD n k = n SUCC k`.

<!-- ANCHOR-BEGIN: ADD -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L248-L255</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L357-L368</td>
  </tr>
</table>
<!-- ANCHOR-END: ADD -->

`MUL`: Multiplication, equivalent to `B`. `MUL n k f = n (k f)`.

<!-- ANCHOR-BEGIN: MUL -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L259-L271</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L372-L391</td>
  </tr>
</table>
<!-- ANCHOR-END: MUL -->

`POW`: Exponentiation, equivalent to the Thrush combinator. `POW n k = k n`.

<!-- ANCHOR-BEGIN: POW -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L275-L286</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L395-L413</td>
  </tr>
</table>
<!-- ANCHOR-END: POW -->

`IS_ZERO`: Zero test. `IS_ZERO n = n (K F) T`.

<!-- ANCHOR-BEGIN: IS_ZERO -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L290-L296</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L417-L424</td>
  </tr>
</table>
<!-- ANCHOR-END: IS_ZERO -->

### Pairs and Comparisons

Pairs are encoded as functions that hand two stored values to a selector.

`V`, `PAIR`: Vireo combinator, equivalent to `B C T`. `PAIR` is an alias of `V`. `V a b f = f a b`.

<!-- ANCHOR-BEGIN: V_PAIR -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L300-L313</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L428-L448</td>
  </tr>
</table>
<!-- ANCHOR-END: V_PAIR -->

`FST`: First projection. `FST p = p K`.

<!-- ANCHOR-BEGIN: FST -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L317-L322</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L452-L458</td>
  </tr>
</table>
<!-- ANCHOR-END: FST -->

`SND`: Second projection. `SND p = p KI`.

<!-- ANCHOR-BEGIN: SND -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L326-L331</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L462-L468</td>
  </tr>
</table>
<!-- ANCHOR-END: SND -->

`PHI`: Pair transformer used in predecessor constructions. `PHI p = PAIR (SND p) (SUCC (SND p))`.

<!-- ANCHOR-BEGIN: PHI -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L335-L341</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L472-L480</td>
  </tr>
</table>
<!-- ANCHOR-END: PHI -->

`PRED2`: Predecessor expressed through `PHI`. `PRED2 n = FST (n PHI (PAIR N0 N0))`.

<!-- ANCHOR-BEGIN: PRED2 -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L345-L351</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L484-L491</td>
  </tr>
</table>
<!-- ANCHOR-END: PRED2 -->

`SUB`: Subtraction. `SUB n k = k PRED n`.

<!-- ANCHOR-BEGIN: SUB -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L355-L364</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L495-L507</td>
  </tr>
</table>
<!-- ANCHOR-END: SUB -->

`LEQ`: Less-than-or-equal. `LEQ n k = IS_ZERO (SUB n k)`.

<!-- ANCHOR-BEGIN: LEQ -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L368-L376</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L511-L523</td>
  </tr>
</table>
<!-- ANCHOR-END: LEQ -->

`EQ`: Equality. `EQ n k = AND (LEQ n k) (LEQ k n)`.

<!-- ANCHOR-BEGIN: EQ -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L380-L388</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L527-L539</td>
  </tr>
</table>
<!-- ANCHOR-END: EQ -->

`GT`: Greater-than. `GT n k = NOT (LEQ n k)`.

<!-- ANCHOR-BEGIN: GT -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L392-L400</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L543-L555</td>
  </tr>
</table>
<!-- ANCHOR-END: GT -->

`B1`: Blackbird combinator, equivalent to `B B B`. `B1 f g a b = f (g a b)`.

<!-- ANCHOR-BEGIN: B1 -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L404-L413</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L559-L578</td>
  </tr>
</table>
<!-- ANCHOR-END: B1 -->

`GT2`: Greater-than expressed through `B1`. `GT2 n k = B1 NOT LEQ n k`.

<!-- ANCHOR-BEGIN: GT2 -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L417-L421</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L582-L586</td>
  </tr>
</table>
<!-- ANCHOR-END: GT2 -->

`SET_FST`: Update the first element of a pair. `SET_FST x p = PAIR x (SND p)`.

<!-- ANCHOR-BEGIN: SET_FST -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L425-L431</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L590-L602</td>
  </tr>
</table>
<!-- ANCHOR-END: SET_FST -->

`SET_SND`: Update the second element of a pair. `SET_SND x p = PAIR (FST p) x`.

<!-- ANCHOR-BEGIN: SET_SND -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L435-L441</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L606-L618</td>
  </tr>
</table>
<!-- ANCHOR-END: SET_SND -->

### Fibonacci and Fixed-Point Combinators

These examples show nontrivial compositions and direct lambda-term translations.

`FIB`: Fibonacci over Church numerals. `FIB n = n step K N0 N1`, where `step f a b = f b (ADD a b)`.

<!-- ANCHOR-BEGIN: FIB -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L445-L465</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L622-L650</td>
  </tr>
</table>
<!-- ANCHOR-END: FIB -->

`Y`: Direct syntactic translation of the classic fixed-point combinator. It is not usable here under eager C++ evaluation.

<!-- ANCHOR-BEGIN: Y -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L469-L476</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L654-L663</td>
  </tr>
</table>
<!-- ANCHOR-END: Y -->

`Z`: Delayed fixed-point variant. The C++ type system still prevents direct use here.

<!-- ANCHOR-BEGIN: Z -->
<table>
  <tr>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/lambda.cpp#L480-L491</td>
    <td>https://github.com/ShawnZhong/combinatory_logic.cpp/blob/2cc8af38dbce36d1a07671bf1a7e1302b4ef5d67/template.cpp#L667-L681</td>
  </tr>
</table>
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
- Haskellizing C++ template metaprogramming. [Article](https://manu343726.github.io/2015-03-19-haskellizing-tmp/)
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
