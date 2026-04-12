#include <type_traits>

// Helper to check if two terms are equal
template <typename A, typename B> constexpr bool eq = std::is_same_v<A, B>;

// Identity combinator, aka idiot combinator
// returns the argument unchanged
// I x = x
struct I {
  template <typename X> using of = X;
};
static_assert(eq<I::of<I>, I>);

// Mockingbird combinator
// applies the argument to itself
// M f = f f
struct M {
  template <typename F> using of = typename F::template of<F>;
};
static_assert(eq<M::of<I>, I>);

// Kestrel combinator, aka constant combinator
// returns the first argument unchanged
// K a b = a
template <typename A, typename B> struct K_curry;
template <> struct K_curry<void, void> {
  template <typename A> using of = K_curry<A, void>;
};
template <typename A> struct K_curry<A, void> {
  template <typename B> using of = A;
};
using K = K_curry<void, void>;
static_assert(eq<K::of<I>::of<M>, I>);
static_assert(eq<K::of<M>::of<I>, M>);
static_assert(eq<K::of<I>::of<M>::of<K>, K>);

// Kite combinator, equivalent to K I and C K
// returns the second argument unchanged
// KI a b = b
template <typename A, typename B> struct KI_curry;
template <> struct KI_curry<void, void> {
  template <typename A> using of = KI_curry<A, void>;
};
template <typename A> struct KI_curry<A, void> {
  template <typename B> using of = B;
};
using KI = KI_curry<void, void>;
static_assert(eq<KI::of<M>::of<K>, K>);
static_assert(eq<KI::of<K>::of<M>, M>);

// Cardinal combinator, aka flip combinator
// reverses the arguments
// C f a b = f b a
template <typename F, typename A, typename B> struct C_curry;
template <> struct C_curry<void, void, void> {
  template <typename F> using of = C_curry<F, void, void>;
};
template <typename F> struct C_curry<F, void, void> {
  template <typename A> using of = C_curry<F, A, void>;
};
template <typename F, typename A> struct C_curry<F, A, void> {
  template <typename B> using of = typename F::template of<B>::template of<A>;
};
using C = C_curry<void, void, void>;
static_assert(eq<C::of<KI>::of<I>::of<M>, I>); // C(KI) = K
static_assert(eq<C::of<K>::of<I>::of<M>, M>);
static_assert(eq<KI::of<I>::of<M>, M>); // KI = CK

// Church encoding of booleans
// T T F = T
// F T F = F
using T = K;
using F = KI;
static_assert(eq<T::of<T>::of<F>, T>);
static_assert(eq<F::of<T>::of<F>, F>);

// Boolean negation, equivalent to C
// NOT p = p F T
struct NOT {
  template <typename P> using of = typename P::template of<F>::template of<T>;
};
static_assert(eq<NOT::of<T>, F>);
static_assert(eq<NOT::of<F>, T>);
static_assert(eq<C::of<T>::of<T>::of<F>, F>);
static_assert(eq<C::of<F>::of<T>::of<F>, T>);

// Boolean conjunction
// AND p q = p q F = p q p
template <typename P, typename Q> struct AND_curry;
template <> struct AND_curry<void, void> {
  template <typename P> using of = AND_curry<P, void>;
};
template <typename P> struct AND_curry<P, void> {
  template <typename Q> using of = typename P::template of<Q>::template of<F>;
  template <typename Q> using of2 = typename P::template of<Q>::template of<P>;
};
using AND = AND_curry<void, void>;
static_assert(eq<AND::of<T>::of<T>, T>);
static_assert(eq<AND::of<T>::of<F>, F>);
static_assert(eq<AND::of<F>::of<T>, F>);
static_assert(eq<AND::of<F>::of<F>, F>);

// Boolean disjunction, equivalent to M*
// OR p q = p T q = p p q
template <typename P, typename Q> struct OR_curry;
template <> struct OR_curry<void, void> {
  template <typename P> using of = OR_curry<P, void>;
};
template <typename P> struct OR_curry<P, void> {
  template <typename Q> using of = typename P::template of<T>::template of<Q>;
  template <typename Q> using of2 = typename P::template of<P>::template of<Q>;
};
using OR = OR_curry<void, void>;
static_assert(eq<OR::of<T>::of<T>, T>);
static_assert(eq<OR::of<T>::of<F>, T>);
static_assert(eq<OR::of<F>::of<T>, T>);
static_assert(eq<OR::of<F>::of<F>, F>);

// Boolean equality
// BEQ p q = p q (NOT q)
template <typename P, typename Q> struct BEQ_curry;
template <> struct BEQ_curry<void, void> {
  template <typename P> using of = BEQ_curry<P, void>;
};
template <typename P> struct BEQ_curry<P, void> {
  template <typename Q>
  using of = typename P::template of<Q>::template of<NOT::of<Q>>;
};
using BEQ = BEQ_curry<void, void>;
static_assert(eq<BEQ::of<T>::of<T>, T>);
static_assert(eq<BEQ::of<T>::of<F>, F>);
static_assert(eq<BEQ::of<F>::of<T>, F>);
static_assert(eq<BEQ::of<F>::of<F>, T>);

// Boolean exclusive disjunction
// XOR p q = p (NOT q) q
template <typename P, typename Q> struct XOR_curry;
template <> struct XOR_curry<void, void> {
  template <typename P> using of = XOR_curry<P, void>;
};
template <typename P> struct XOR_curry<P, void> {
  template <typename Q>
  using of = typename P::template of<NOT::of<Q>>::template of<Q>;
};
using XOR = XOR_curry<void, void>;
static_assert(eq<XOR::of<T>::of<T>, F>);
static_assert(eq<XOR::of<T>::of<F>, T>);
static_assert(eq<XOR::of<F>::of<T>, T>);
static_assert(eq<XOR::of<F>::of<F>, F>);

// Church encoding of natural numbers
// Applies the first argument n times to the second argument

// N0 f x = x
template <typename F, typename X> struct N0_curry;
template <> struct N0_curry<void, void> {
  template <typename F> using of = N0_curry<F, void>;
};
template <typename F> struct N0_curry<F, void> {
  template <typename X> using of = X;
};
using N0 = N0_curry<void, void>;

// N1 f x = f x
template <typename F, typename X> struct N1_curry;
template <> struct N1_curry<void, void> {
  template <typename F> using of = N1_curry<F, void>;
};
template <typename F> struct N1_curry<F, void> {
  template <typename X> using of = typename F::template of<X>;
};
using N1 = N1_curry<void, void>;

// N2 f x = f (f x)
template <typename F, typename X> struct N2_curry;
template <> struct N2_curry<void, void> {
  template <typename F> using of = N2_curry<F, void>;
};
template <typename F> struct N2_curry<F, void> {
  template <typename X>
  using of = typename F::template of<typename F::template of<X>>;
};
using N2 = N2_curry<void, void>;

// N3 f x = f (f (f x))
template <typename F, typename X> struct N3_curry;
template <> struct N3_curry<void, void> {
  template <typename F> using of = N3_curry<F, void>;
};
template <typename F> struct N3_curry<F, void> {
  template <typename X>
  using of = typename F::template of<
      typename F::template of<typename F::template of<X>>>;
};
using N3 = N3_curry<void, void>;

static_assert(eq<N0::of<NOT>::of<F>, F>);
static_assert(eq<N1::of<NOT>::of<F>, T>);
static_assert(eq<N2::of<NOT>::of<F>, F>);
static_assert(eq<N3::of<NOT>::of<F>, T>);

// Helper functions to convert Church numeral to integer
template <int N> struct val {
  static constexpr int value = N;
};
struct succ {
  template <typename N> using of = val<N::value + 1>;
};
template <typename N>
constexpr int to_int = N::template of<succ>::template of<val<0>>::value;
static_assert(to_int<N0> == 0);
static_assert(to_int<N1> == 1);
static_assert(to_int<N2> == 2);
static_assert(to_int<N3> == 3);

// Successor
// SUCC n f x = f (n f x)
template <typename N, typename F, typename X> struct SUCC_curry;
template <> struct SUCC_curry<void, void, void> {
  template <typename N> using of = SUCC_curry<N, void, void>;
};
template <typename N> struct SUCC_curry<N, void, void> {
  template <typename F> using of = SUCC_curry<N, F, void>;
};
template <typename N, typename F> struct SUCC_curry<N, F, void> {
  template <typename X>
  using of =
      typename F::template of<typename N::template of<F>::template of<X>>;
};
using SUCC = SUCC_curry<void, void, void>;
static_assert(to_int<SUCC::of<N0>> == 1);
static_assert(to_int<SUCC::of<SUCC::of<N0>>> == 2);
static_assert(to_int<SUCC::of<SUCC::of<SUCC::of<N0>>>> == 3);
using N4 = SUCC::of<N3>;
static_assert(to_int<N4> == 4);

// Predecessor
// PRED n f x = n PRED_helper (K x) I, where PRED_helper f = C I (g f)
template <typename F> struct PRED_helper { // C I (g f)
  template <typename G>
  using of =
      typename C::template of<I>::template of<typename G::template of<F>>;
};
template <typename N, typename F, typename X> struct PRED_curry;
template <> struct PRED_curry<void, void, void> {
  template <typename N> using of = PRED_curry<N, void, void>;
};
template <typename N> struct PRED_curry<N, void, void> {
  template <typename F> using of = PRED_curry<N, F, void>;
};
template <typename N, typename F> struct PRED_curry<N, F, void> {
  template <typename X>
  using of = typename N::template of<PRED_helper<F>>::template of<
      K::of<X>>::template of<I>;
};
using PRED = PRED_curry<void, void, void>;
static_assert(to_int<PRED::of<N1>> == 0);
static_assert(to_int<PRED::of<N2>> == 1);
static_assert(to_int<PRED::of<N3>> == 2);

// Bluebird combinator
// composes two unary functions
// B f g x = f (g x)
template <typename F, typename G, typename X> struct B_curry;
template <> struct B_curry<void, void, void> {
  template <typename F> using of = B_curry<F, void, void>;
};
template <typename F> struct B_curry<F, void, void> {
  template <typename G> using of = B_curry<F, G, void>;
};
template <typename F, typename G> struct B_curry<F, G, void> {
  template <typename X>
  using of = typename F::template of<typename G::template of<X>>;
};
using B = B_curry<void, void, void>;
static_assert(eq<B::of<NOT>::of<NOT>::of<T>, T>);

// Successor written in terms of B
// SUCC n f = B f (n f)
template <typename N, typename F> struct SUCC2_curry;
template <> struct SUCC2_curry<void, void> {
  template <typename N> using of = SUCC2_curry<N, void>;
};
template <typename N> struct SUCC2_curry<N, void> {
  template <typename F> using of = SUCC2_curry<N, F>;
};
template <typename N, typename F> struct SUCC2_curry {
  template <typename X>
  using of = typename B::template of<F>::template of<
      typename N::template of<F>>::template of<X>;
};
using SUCC2 = SUCC2_curry<void, void>;
static_assert(to_int<SUCC2::of<N0>> == 1);
static_assert(to_int<SUCC2::of<N3>> == 4);

// Addition
// Add n k = n SUCC k
template <typename N, typename K> struct ADD_curry;
template <> struct ADD_curry<void, void> {
  template <typename N> using of = ADD_curry<N, void>;
};
template <typename N> struct ADD_curry<N, void> {
  template <typename K>
  using of = typename N::template of<SUCC>::template of<K>;
};
using ADD = ADD_curry<void, void>;
using N5 = ADD::of<N2>::of<N3>;
static_assert(to_int<N5> == 5);

// Multiplication, equivalent to B
// MUL n k f = n (k f)
template <typename N, typename K> struct MUL_curry;
template <> struct MUL_curry<void, void> {
  template <typename N> using of = MUL_curry<N, void>;
};
template <typename N> struct MUL_curry<N, void> {
  template <typename K> using of = MUL_curry<N, K>;
};
template <typename N, typename K> struct MUL_curry {
  template <typename F>
  using of = typename N::template of<typename K::template of<F>>;
};
using MUL = MUL_curry<void, void>;
using N6 = MUL::of<N2>::of<N3>;
static_assert(to_int<N6> == 6);
using N7 = ADD::of<MUL::of<N2>::of<N2>>::of<MUL::of<N1>::of<N3>>;
static_assert(to_int<N7> == 7);
static_assert(to_int<B::of<N6>::of<N7>> == 42);

// Exponentiation, equivalent to the Thrush combinator
// POW n k = k n
template <typename N, typename K> struct POW_curry;
template <> struct POW_curry<void, void> {
  template <typename N> using of = POW_curry<N, void>;
};
template <typename N> struct POW_curry<N, void> {
  template <typename K> using of = POW_curry<N, K>;
};
template <typename N, typename K> struct POW_curry {
  template <typename F> using of = typename K::template of<N>::template of<F>;
};
using POW = POW_curry<void, void>;
using N8 = POW::of<N2>::of<N3>;
using N9 = POW::of<N3>::of<N2>;
static_assert(to_int<N8> == 8);
static_assert(to_int<N9> == 9);

// Check if n is zero
// IS_ZERO n = n KF T
struct IS_ZERO {
  template <typename N>
  using of =
      typename N::template of<typename K::template of<F>>::template of<T>;
};
static_assert(eq<IS_ZERO::of<N0>, T>);
static_assert(eq<IS_ZERO::of<N1>, F>);
static_assert(eq<IS_ZERO::of<N2>, F>);

// Vired combinator, equivalent to BCT
// also used to hold a pair of arguments
// V a b f = f a b
template <typename A, typename B> struct V_curry;
template <> struct V_curry<void, void> {
  template <typename A> using of = V_curry<A, void>;
};
template <typename A> struct V_curry<A, void> {
  template <typename B> using of = V_curry<A, B>;
};
template <typename A, typename B> struct V_curry {
  template <typename F> using of = typename F::template of<A>::template of<B>;
};
using V = V_curry<void, void>;
static_assert(to_int<V::of<N2>::of<N3>::of<ADD>> == 5);
static_assert(eq<V::of<I>::of<M>::of<K>::of<I>, I>);
static_assert(eq<V::of<I>::of<M>::of<K>::of<M>, M>);

// Church encoding of pairs, equivalent to V
using PAIR = V;

// Extract first argument from a pair
// FST p = p K
struct FST {
  template <typename P> using of = typename P::template of<K>;
};
static_assert(eq<FST::of<PAIR::of<I>::of<M>>, I>);
static_assert(eq<FST::of<PAIR::of<N2>::of<N3>>, N2>);

// Extract second argument from a pair
// SND p = p KI
struct SND {
  template <typename P> using of = typename P::template of<KI>;
};
static_assert(eq<SND::of<PAIR::of<I>::of<M>>, M>);
static_assert(eq<SND::of<PAIR::of<N2>::of<N3>>, N3>);

// Phi combinator
// copy second argument to first argument and increment second argument
// PHI p = PAIR (SND p) (SUCC (SND p))
struct PHI {
  template <typename P>
  using of =
      typename PAIR::template of<typename SND::template of<P>>::template of<
          typename SUCC::template of<typename SND::template of<P>>>;
};
static_assert(to_int<FST::of<PHI::of<PAIR::of<N0>::of<N0>>>> == 0);
static_assert(to_int<SND::of<PHI::of<PAIR::of<N0>::of<N0>>>> == 1);
static_assert(to_int<FST::of<N3::of<PHI>::of<PAIR::of<N0>::of<N0>>>> == 2);

// Predecessor written in terms of PHI
// PRED n = FST (n PHI (PAIR N0 N0))
struct PRED2 {
  template <typename N>
  using of = typename FST::template of<typename N::template of<
      PHI>::template of<typename PAIR::template of<N0>::template of<N0>>>;
};
static_assert(to_int<PRED2::of<N1>> == 0);
static_assert(to_int<PRED2::of<N2>> == 1);
static_assert(to_int<PRED2::of<N3>> == 2);

// Subtraction
// SUB n k = k PRED n
template <typename N, typename K> struct SUB_curry;
template <> struct SUB_curry<void, void> {
  template <typename N> using of = SUB_curry<N, void>;
};
template <typename N> struct SUB_curry<N, void> {
  template <typename K>
  using of = typename K::template of<PRED>::template of<N>;
};
using SUB = SUB_curry<void, void>;
static_assert(to_int<SUB::of<N0>::of<N0>> == 0);
static_assert(to_int<SUB::of<N3>::of<N1>> == 2);
static_assert(to_int<SUB::of<N3>::of<N2>> == 1);

// Lesser than or equal to
// LEQ n k = IS_ZERO (SUB n k)
template <typename N, typename K> struct LEQ_curry;
template <> struct LEQ_curry<void, void> {
  template <typename N> using of = LEQ_curry<N, void>;
};
template <typename N> struct LEQ_curry<N, void> {
  template <typename K>
  using of = typename IS_ZERO::template of<
      typename SUB::template of<N>::template of<K>>;
};
using LEQ = LEQ_curry<void, void>;
static_assert(eq<LEQ::of<N1>::of<N3>, T>);
static_assert(eq<LEQ::of<N2>::of<N2>, T>);
static_assert(eq<LEQ::of<N3>::of<N1>, F>);

// Equality
// EQ n k = AND (LEQ n k) (LEQ k n)
template <typename N, typename K> struct EQ_curry;
template <> struct EQ_curry<void, void> {
  template <typename N> using of = EQ_curry<N, void>;
};
template <typename N> struct EQ_curry<N, void> {
  template <typename K>
  using of =
      typename AND::template of<typename LEQ::template of<N>::template of<K>>::
          template of<typename LEQ::template of<K>::template of<N>>;
};
using EQ = EQ_curry<void, void>;
static_assert(eq<EQ::of<N1>::of<N3>, F>);
static_assert(eq<EQ::of<N2>::of<N2>, T>);
static_assert(eq<EQ::of<N3>::of<N1>, F>);

// Greater than
// GT n k = NOT (LEQ n k)
template <typename N, typename K> struct GT_curry;
template <> struct GT_curry<void, void> {
  template <typename N> using of = GT_curry<N, void>;
};
template <typename N> struct GT_curry<N, void> {
  template <typename K>
  using of =
      typename NOT::template of<typename LEQ::template of<N>::template of<K>>;
};
using GT = GT_curry<void, void>;
static_assert(eq<GT::of<N1>::of<N3>, F>);
static_assert(eq<GT::of<N2>::of<N2>, F>);
static_assert(eq<GT::of<N3>::of<N1>, T>);

// Blackbird combinator, equivalent to BBB
// composes an unary function with a binary function
// B1 f g a b = f (g a b)
template <typename F, typename G, typename A, typename B> struct B1_curry;
template <> struct B1_curry<void, void, void, void> {
  template <typename F> using of = B1_curry<F, void, void, void>;
};
template <typename F> struct B1_curry<F, void, void, void> {
  template <typename G> using of = B1_curry<F, G, void, void>;
};
template <typename F, typename G> struct B1_curry<F, G, void, void> {
  template <typename A> using of = B1_curry<F, G, A, void>;
};
template <typename F, typename G, typename A> struct B1_curry<F, G, A, void> {
  template <typename B>
  using of =
      typename F::template of<typename G::template of<A>::template of<B>>;
};
using B1 = B1_curry<void, void, void, void>;

// Greater than written in terms of B1
// GT2 n k = B1 NOT LEQ n k = NOT (LEQ n k)
using GT2 = B1::of<NOT>::of<LEQ>;
static_assert(eq<GT2::of<N1>::of<N3>, F>);
static_assert(eq<GT2::of<N2>::of<N2>, F>);
static_assert(eq<GT2::of<N3>::of<N1>, T>);

// Set the first element of a pair
// SET_FST x p = PAIR x (SND p)
template <typename X, typename P> struct SET_FST_curry;
template <> struct SET_FST_curry<void, void> {
  template <typename X> using of = SET_FST_curry<X, void>;
};
template <typename X> struct SET_FST_curry<X, void> {
  template <typename P>
  using of =
      typename PAIR::template of<X>::template of<typename SND::template of<P>>;
};
using SET_FST = SET_FST_curry<void, void>;
static_assert(to_int<FST::of<SET_FST::of<N3>::of<PAIR::of<N1>::of<N2>>>> == 3);

// Set the second element of a pair
// SET_SND x p = PAIR (FST p) x
template <typename X, typename P> struct SET_SND_curry;
template <> struct SET_SND_curry<void, void> {
  template <typename X> using of = SET_SND_curry<X, void>;
};
template <typename X> struct SET_SND_curry<X, void> {
  template <typename P>
  using of =
      typename PAIR::template of<typename FST::template of<P>>::template of<X>;
};
using SET_SND = SET_SND_curry<void, void>;
static_assert(to_int<SND::of<SET_SND::of<N3>::of<PAIR::of<N1>::of<N2>>>> == 3);

// Fibonacci numbers
// FIB n = n FIB_helper K 0 1, where FIB_helper f a b = f b (ADD a b)
template <typename F, typename A, typename B> struct FIB_helper_curry;
template <> struct FIB_helper_curry<void, void, void> {
  template <typename F> using of = FIB_helper_curry<F, void, void>;
};
template <typename F> struct FIB_helper_curry<F, void, void> {
  template <typename A> using of = FIB_helper_curry<F, A, void>;
};
template <typename F, typename A> struct FIB_helper_curry<F, A, void> {
  template <typename B>
  using of = typename F::template of<B>::template of<
      typename ADD::template of<A>::template of<B>>;
};
using FIB_helper = FIB_helper_curry<void, void, void>;
struct FIB {
  template <typename N>
  using of = typename N::template of<FIB_helper>::template of<K>::template of<
      N0>::template of<N1>;
};
static_assert(to_int<FIB::of<N0>> == 0);
static_assert(to_int<FIB::of<N1>> == 1);
static_assert(to_int<FIB::of<N2>> == 1);
static_assert(to_int<FIB::of<N3>> == 2);
static_assert(to_int<FIB::of<N4>> == 3);
static_assert(to_int<FIB::of<N5>> == 5);
static_assert(to_int<FIB::of<N6>> == 8);
static_assert(to_int<FIB::of<N7>> == 13);
static_assert(to_int<FIB::of<N8>> == 21);
static_assert(to_int<FIB::of<N9>> == 34);

// Y combinator, the fixed point combinator
// Y f x = f (Y f) x.
template <typename F> struct Y_curry;
template <> struct Y_curry<void> {
  template <typename F> using of = Y_curry<F>;
};
template <typename F> struct Y_curry {
  template <typename X>
  using of = typename F::template of<Y_curry<F>>::template of<X>;
};
using Y = Y_curry<void>;
