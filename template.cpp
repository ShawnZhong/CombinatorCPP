// Helper for internal application of terms.
// Public-facing code should prefer chained `::of<...>`.
template <typename F, typename X> using ap = typename F::template of<X>;

// Helper to check if two terms are equal
template <typename A, typename B> struct eq {
  static constexpr bool value = false;
};
template <typename T> struct eq<T, T> {
  static constexpr bool value = true;
};

// Identity combinator, aka idiot combinator
// returns the argument unchanged
// I x = x
struct I {
  template <typename X> using of = X;
};
static_assert(eq<I::of<I>, I>::value, "I I == I");

// Mockingbird combinator
// applies the argument to itself
// M f = f f
struct M {
  template <typename F> using of = ap<F, F>;
};
static_assert(eq<M::of<I>, I>::value, "M I == I");

// Kestrel combinator, aka constant combinator
// returns the first argument unchanged
// K a b = a
struct K {
  template <typename A> struct with_a {
    template <typename B> using of = A;
  };

  template <typename A> using of = with_a<A>;
};
static_assert(eq<K::of<I>::of<M>, I>::value, "K I M== I");
static_assert(eq<K::of<M>::of<I>, M>::value, "K M I == M");
static_assert(eq<K::of<I>::of<M>::of<K>, K>::value, "K I M K== K");

// Kite combinator, equivalent to K I and C K
// returns the second argument unchanged
// KI a b = b
struct KI {
  template <typename A> struct with_a {
    template <typename B> using of = B;
  };

  template <typename A> using of = with_a<A>;
};
static_assert(eq<KI::of<M>::of<K>, K>::value, "KI M K== K");
static_assert(eq<KI::of<K>::of<M>, M>::value, "KI K M== M");

// Cardinal combinator, aka flip combinator
// reverses the arguments
// C f a b = f b a
struct C {
  template <typename F> struct with_f {
    template <typename A> struct with_a {
      template <typename B> using of = ap<ap<F, B>, A>;
    };

    template <typename A> using of = with_a<A>;
  };

  template <typename F> using of = with_f<F>;
};
// C KI == K
static_assert(eq<K::of<I>::of<M>, I>::value, "K I M == I");
static_assert(eq<C::of<KI>::of<I>::of<M>, I>::value, "C KI I M == I");
// KI == C K
static_assert(eq<C::of<K>::of<I>::of<M>, M>::value, "C K I M == M");
static_assert(eq<KI::of<I>::of<M>, M>::value, "KI I M == M");

// Church encoding of booleans
// T T F = T
// F T F = F
using T = K;
using F = KI;
static_assert(eq<T::of<T>::of<F>, T>::value, "T T F = T");
static_assert(eq<F::of<T>::of<F>, F>::value, "F T F = F");

// Boolean negation, equivalent to C
// NOT p = p F T
struct NOT {
  template <typename P> using of = ap<ap<P, F>, T>;
};
static_assert(eq<NOT::of<T>, F>::value, "NOT T = F");
static_assert(eq<NOT::of<F>, T>::value, "NOT F = T");
static_assert(eq<C::of<T>::of<T>::of<F>, F>::value, "C(T) = F");
static_assert(eq<C::of<F>::of<T>::of<F>, T>::value, "C(F) = T");

// Boolean conjunction
// AND p q = p q F = p q p
struct AND {
  template <typename P> struct with_p {
    template <typename Q> using of = ap<ap<P, Q>, F>;
    template <typename Q> using of2 = ap<ap<P, Q>, P>;
  };

  template <typename P> using of = with_p<P>;
};
static_assert(eq<AND::of<T>::of<T>, T>::value, "AND T T = T");
static_assert(eq<AND::of<T>::of<F>, F>::value, "AND T F = F");
static_assert(eq<AND::of<F>::of<T>, F>::value, "AND F T = F");
static_assert(eq<AND::of<F>::of<F>, F>::value, "AND F F = F");

// Boolean disjunction, equivalent to M*
// OR p q = p T q = p p q
struct OR {
  template <typename P> struct with_p {
    template <typename Q> using of = ap<ap<P, T>, Q>;
    template <typename Q> using of2 = ap<ap<P, P>, Q>;
  };

  template <typename P> using of = with_p<P>;
};
static_assert(eq<OR::of<T>::of<T>, T>::value, "OR T T = T");
static_assert(eq<OR::of<T>::of<F>, T>::value, "OR T F = T");
static_assert(eq<OR::of<F>::of<T>, T>::value, "OR F T = T");
static_assert(eq<OR::of<F>::of<F>, F>::value, "OR F F = F");

// Boolean equality
// BEQ p q = p q (NOT q)
struct BEQ {
  template <typename P> struct with_p {
    template <typename Q> using of = ap<ap<P, Q>, ap<NOT, Q>>;
  };

  template <typename P> using of = with_p<P>;
};
static_assert(eq<BEQ::of<T>::of<T>, T>::value, "BEQ T T = T");
static_assert(eq<BEQ::of<T>::of<F>, F>::value, "BEQ T F = F");
static_assert(eq<BEQ::of<F>::of<T>, F>::value, "BEQ F T = F");
static_assert(eq<BEQ::of<F>::of<F>, T>::value, "BEQ F F = T");

// Boolean exclusive disjunction
// XOR p q = p (NOT q) q
struct XOR {
  template <typename P> struct with_p {
    template <typename Q> using of = ap<ap<P, ap<NOT, Q>>, Q>;
  };

  template <typename P> using of = with_p<P>;
};
static_assert(eq<XOR::of<T>::of<T>, F>::value, "XOR T T = F");
static_assert(eq<XOR::of<T>::of<F>, T>::value, "XOR T F = T");
static_assert(eq<XOR::of<F>::of<T>, T>::value, "XOR F T = T");
static_assert(eq<XOR::of<F>::of<F>, F>::value, "XOR F F = F");

// Church encoding of natural numbers
// Applies the first argument n times to the second argument

// N0 f x = x
struct N0 {
  template <typename F> struct with_f {
    template <typename X> using of = X;
  };

  template <typename F> using of = with_f<F>;
};

// N1 f x = f x
struct N1 {
  template <typename F> struct with_f {
    template <typename X> using of = ap<F, X>;
  };

  template <typename F> using of = with_f<F>;
};

// N2 f x = f (f x)
struct N2 {
  template <typename F> struct with_f {
    template <typename X> using of = ap<F, ap<F, X>>;
  };

  template <typename F> using of = with_f<F>;
};

// N3 f x = f (f (f x))
struct N3 {
  template <typename F> struct with_f {
    template <typename X> using of = ap<F, ap<F, ap<F, X>>>;
  };

  template <typename F> using of = with_f<F>;
};

static_assert(eq<N0::of<NOT>::of<F>, F>::value, "N0 NOT F = F");
static_assert(eq<N1::of<NOT>::of<F>, T>::value, "N1 NOT F = T");
static_assert(eq<N2::of<NOT>::of<F>, F>::value, "N2 NOT F = F");
static_assert(eq<N3::of<NOT>::of<F>, T>::value, "N3 NOT F = T");

// Helper functions to convert Church numerals to integers
template <int N> struct nat {
  static constexpr int value = N;
};
struct succ {
  template <typename N> using of = nat<N::value + 1>;
};
template <typename N> struct to_nat {
  static constexpr int value = ap<ap<N, succ>, nat<0>>::value;
};
static_assert(to_nat<N0>::value == 0, "N0 = 0");
static_assert(to_nat<N1>::value == 1, "N1 = 1");
static_assert(to_nat<N2>::value == 2, "N2 = 2");
static_assert(to_nat<N3>::value == 3, "N3 = 3");

// Successor
// SUCC n f x = f (n f x)
struct SUCC {
  template <typename N> struct with_n {
    template <typename F> struct with_f {
      template <typename X> using of = ap<F, ap<ap<N, F>, X>>;
    };

    template <typename F> using of = with_f<F>;
  };

  template <typename N> using of = with_n<N>;
};
static_assert(to_nat<SUCC::of<N0>>::value == 1, "SUCC N0 = N1");
static_assert(to_nat<SUCC::of<SUCC::of<N0>>>::value == 2, "SUCC SUCC N0 = N2");
static_assert(to_nat<SUCC::of<SUCC::of<SUCC::of<N0>>>>::value == 3,
              "SUCC SUCC SUCC N0 = N3");
using N4 = SUCC::of<N3>;
static_assert(to_nat<N4>::value == 4, "SUCC N3 = N4");

// Predecessor
// PRED n f x = n shift (K x) I, where shift f g = C I (g f)
struct PRED {
  struct shift {
    template <typename F> struct with_f {
      template <typename G> using of = ap<ap<C, I>, ap<G, F>>;
    };

    template <typename F> using of = with_f<F>;
  };

  template <typename N> struct with_n {
    template <typename F> struct with_f {
      template <typename X> using of = ap<ap<ap<N, ap<shift, F>>, ap<K, X>>, I>;
    };

    template <typename F> using of = with_f<F>;
  };

  template <typename N> using of = with_n<N>;
};
static_assert(to_nat<PRED::of<N1>>::value == 0, "PRED N1 = N0");
static_assert(to_nat<PRED::of<N2>>::value == 1, "PRED N2 = N1");
static_assert(to_nat<PRED::of<N3>>::value == 2, "PRED N3 = N2");

// Bluebird combinator
// composes two unary functions
// B f g x = f (g x)
struct B {
  template <typename F> struct with_f {
    template <typename G> struct with_g {
      template <typename X> using of = ap<F, ap<G, X>>;
    };

    template <typename G> using of = with_g<G>;
  };

  template <typename F> using of = with_f<F>;
};
static_assert(eq<B::of<NOT>::of<NOT>::of<T>, T>::value, "B NOT NOT T = T");

// Successor written in terms of B
// SUCC n f = B f (n f)
struct SUCC2 {
  template <typename N> struct with_n {
    template <typename F> struct with_f {
      template <typename X> using of = ap<ap<ap<B, F>, ap<N, F>>, X>;
    };

    template <typename F> using of = with_f<F>;
  };

  template <typename N> using of = with_n<N>;
};
static_assert(to_nat<SUCC2::of<N0>>::value == 1, "SUCC2 N0 = N1");
static_assert(to_nat<SUCC2::of<N3>>::value == 4, "SUCC2 N3 = N4");

// Addition
// ADD n k = n SUCC k
struct ADD {
  template <typename N> struct with_n {
    template <typename K> using of = ap<ap<N, SUCC>, K>;
  };

  template <typename N> using of = with_n<N>;
};
using N5 = ADD::of<N2>::of<N3>;
static_assert(to_nat<N5>::value == 5, "ADD N2 N3 = N5");

// Multiplication, equivalent to B
// MUL n k f = n (k f)
struct MUL {
  template <typename N> struct with_n {
    template <typename K> struct with_k {
      template <typename F> using of = ap<N, ap<K, F>>;
    };

    template <typename K> using of = with_k<K>;
  };

  template <typename N> using of = with_n<N>;
};
using N6 = MUL::of<N2>::of<N3>;
static_assert(to_nat<N6>::value == 6, "MUL N2 N3 = N6");
using N7 = ADD::of<MUL::of<N2>::of<N2>>::of<MUL::of<N1>::of<N3>>;
static_assert(to_nat<N7>::value == 7, "ADD MUL N2 N2 MUL N1 N3 = N7");
static_assert(to_nat<B::of<N6>::of<N7>>::value == 42, "B N6 N7 = 42");

// Exponentiation, equivalent to the Thrush combinator
// POW n k = k n
struct POW {
  template <typename N> struct with_n {
    template <typename K> struct with_k {
      template <typename F> using of = ap<ap<K, N>, F>;
    };

    template <typename K> using of = with_k<K>;
  };

  template <typename N> using of = with_n<N>;
};
using N8 = POW::of<N2>::of<N3>;
using N9 = POW::of<N3>::of<N2>;
static_assert(to_nat<N8>::value == 8, "POW N2 N3 = N8");
static_assert(to_nat<N9>::value == 9, "POW N3 N2 = N9");

// Check if n is zero
// IS_ZERO n = n KF T
struct IS_ZERO {
  template <typename N> using of = ap<ap<N, ap<K, F>>, T>;
};
static_assert(eq<IS_ZERO::of<N0>, T>::value, "IS_ZERO N0 = T");
static_assert(eq<IS_ZERO::of<N1>, F>::value, "IS_ZERO N1 = F");
static_assert(eq<IS_ZERO::of<N2>, F>::value, "IS_ZERO N2 = F");

// Vireo combinator, equivalent to BCT
// also used to hold a pair of arguments
// V a b f = f a b
struct V {
  template <typename A> struct with_a {
    template <typename B> struct with_b {
      template <typename F> using of = ap<ap<F, A>, B>;
    };

    template <typename B> using of = with_b<B>;
  };

  template <typename A> using of = with_a<A>;
};
static_assert(to_nat<V::of<N2>::of<N3>::of<ADD>>::value == 5,
              "V N2 N3 ADD = 5");
static_assert(eq<V::of<I>::of<M>::of<K>::of<I>, I>::value, "V I M K I = I");
static_assert(eq<V::of<I>::of<M>::of<K>::of<M>, M>::value, "V I M K M = M");

// Church encoding of pairs
using PAIR = V;

// Extract first argument from a pair
// FST p = p K
struct FST {
  template <typename P> using of = ap<P, K>;
};
static_assert(eq<FST::of<PAIR::of<I>::of<M>>, I>::value, "FST PAIR I M = I");
static_assert(eq<FST::of<PAIR::of<N2>::of<N3>>, N2>::value,
              "FST PAIR N2 N3 = N2");

// Extract second argument from a pair
// SND p = p KI
struct SND {
  template <typename P> using of = ap<P, KI>;
};
static_assert(eq<SND::of<PAIR::of<I>::of<M>>, M>::value, "SND PAIR I M = M");
static_assert(eq<SND::of<PAIR::of<N2>::of<N3>>, N3>::value,
              "SND PAIR N2 N3 = N3");

// Phi combinator
// copy second argument to first argument and increment second argument
// PHI p = PAIR (SND p) (SUCC (SND p))
struct PHI {
  template <typename P>
  using of = ap<ap<PAIR, ap<SND, P>>, ap<SUCC, ap<SND, P>>>;
};
static_assert(to_nat<FST::of<PHI::of<PAIR::of<N0>::of<N0>>>>::value == 0,
              "FST PHI PAIR N0 N0 = 0");
static_assert(to_nat<SND::of<PHI::of<PAIR::of<N0>::of<N0>>>>::value == 1,
              "SND PHI PAIR N0 N0 = 1");
static_assert(to_nat<FST::of<N3::of<PHI>::of<PAIR::of<N0>::of<N0>>>>::value ==
                  2,
              "FST N3 PHI PAIR N0 N0 = 2");

// Predecessor written in terms of PHI
// PRED n = FST (n PHI (PAIR N0 N0))
struct PRED2 {
  template <typename N>
  using of = ap<FST, ap<ap<N, PHI>, ap<ap<PAIR, N0>, N0>>>;
};
static_assert(to_nat<PRED2::of<N1>>::value == 0, "PRED2 N1 = N0");
static_assert(to_nat<PRED2::of<N2>>::value == 1, "PRED2 N2 = N1");
static_assert(to_nat<PRED2::of<N3>>::value == 2, "PRED2 N3 = N2");

// Subtraction
// SUB n k = k PRED n
struct SUB {
  template <typename N> struct with_n {
    template <typename K> using of = ap<ap<K, PRED>, N>;
  };

  template <typename N> using of = with_n<N>;
};
static_assert(to_nat<SUB::of<N0>::of<N0>>::value == 0, "SUB N0 N0 = N0");
static_assert(to_nat<SUB::of<N3>::of<N1>>::value == 2, "SUB N3 N1 = N2");
static_assert(to_nat<SUB::of<N3>::of<N2>>::value == 1, "SUB N3 N2 = N1");

// Lesser than or equal to
// LEQ n k = IS_ZERO (SUB n k)
struct LEQ {
  template <typename N> struct with_n {
    template <typename K> using of = ap<IS_ZERO, ap<ap<SUB, N>, K>>;
  };

  template <typename N> using of = with_n<N>;
};
static_assert(eq<LEQ::of<N1>::of<N3>, T>::value, "LEQ N1 N3 = T");
static_assert(eq<LEQ::of<N2>::of<N2>, T>::value, "LEQ N2 N2 = T");
static_assert(eq<LEQ::of<N3>::of<N1>, F>::value, "LEQ N3 N1 = F");

// Equality
// EQ n k = AND (LEQ n k) (LEQ k n)
struct EQ {
  template <typename N> struct with_n {
    template <typename K>
    using of = ap<ap<AND, ap<ap<LEQ, N>, K>>, ap<ap<LEQ, K>, N>>;
  };

  template <typename N> using of = with_n<N>;
};
static_assert(eq<EQ::of<N1>::of<N3>, F>::value, "EQ N1 N3 = F");
static_assert(eq<EQ::of<N2>::of<N2>, T>::value, "EQ N2 N2 = T");
static_assert(eq<EQ::of<N3>::of<N1>, F>::value, "EQ N3 N1 = F");

// Greater than
// GT n k = NOT (LEQ n k)
struct GT {
  template <typename N> struct with_n {
    template <typename K> using of = ap<NOT, ap<ap<LEQ, N>, K>>;
  };

  template <typename N> using of = with_n<N>;
};
static_assert(eq<GT::of<N1>::of<N3>, F>::value, "GT N1 N3 = F");
static_assert(eq<GT::of<N2>::of<N2>, F>::value, "GT N2 N2 = F");
static_assert(eq<GT::of<N3>::of<N1>, T>::value, "GT N3 N1 = T");

// Blackbird combinator, equivalent to BBB
// composes a unary function with a binary function
// B1 f g a b = f (g a b)
struct B1 {
  template <typename F> struct with_f {
    template <typename G> struct with_g {
      template <typename A> struct with_a {
        template <typename B> using of = ap<F, ap<ap<G, A>, B>>;
      };

      template <typename A> using of = with_a<A>;
    };

    template <typename G> using of = with_g<G>;
  };

  template <typename F> using of = with_f<F>;
};

// Greater than written in terms of B1
// GT2 n k = B1 NOT LEQ n k = NOT (LEQ n k)
using GT2 = B1::of<NOT>::of<LEQ>;
static_assert(eq<GT2::of<N1>::of<N3>, F>::value, "GT2 N1 N3 = F");
static_assert(eq<GT2::of<N2>::of<N2>, F>::value, "GT2 N2 N2 = F");
static_assert(eq<GT2::of<N3>::of<N1>, T>::value, "GT2 N3 N1 = T");

// Set the first element of a pair
// SET_FST x p = PAIR x (SND p)
struct SET_FST {
  template <typename X> struct with_x {
    template <typename P> using of = ap<ap<PAIR, X>, ap<SND, P>>;
  };

  template <typename X> using of = with_x<X>;
};
static_assert(
    to_nat<FST::of<SET_FST::of<N3>::of<PAIR::of<N1>::of<N2>>>>::value == 3,
    "SET_FST N3 (PAIR N1 N2) = 3");

// Set the second element of a pair
// SET_SND x p = PAIR (FST p) x
struct SET_SND {
  template <typename X> struct with_x {
    template <typename P> using of = ap<ap<PAIR, ap<FST, P>>, X>;
  };

  template <typename X> using of = with_x<X>;
};
static_assert(
    to_nat<SND::of<SET_SND::of<N3>::of<PAIR::of<N1>::of<N2>>>>::value == 3,
    "SET_SND N3 (PAIR N1 N2) = 3");

// Fibonacci numbers
// FIB n = n step K 0 1, where step f a b = f b (ADD a b)
struct FIB {
  struct step {
    template <typename F> struct with_f {
      template <typename A> struct with_a {
        template <typename B> using of = ap<ap<F, B>, ap<ap<ADD, A>, B>>;
      };

      template <typename A> using of = with_a<A>;
    };

    template <typename F> using of = with_f<F>;
  };

  template <typename N> using of = ap<ap<ap<ap<N, step>, K>, N0>, N1>;
};
static_assert(to_nat<FIB::of<N0>>::value == 0, "FIB N0 = 0");
static_assert(to_nat<FIB::of<N1>>::value == 1, "FIB N1 = 1");
static_assert(to_nat<FIB::of<N2>>::value == 1, "FIB N2 = 1");
static_assert(to_nat<FIB::of<N3>>::value == 2, "FIB N3 = 2");
static_assert(to_nat<FIB::of<N4>>::value == 3, "FIB N4 = 3");
static_assert(to_nat<FIB::of<N5>>::value == 5, "FIB N5 = 5");
static_assert(to_nat<FIB::of<N6>>::value == 8, "FIB N6 = 8");
static_assert(to_nat<FIB::of<N7>>::value == 13, "FIB N7 = 13");
static_assert(to_nat<FIB::of<N8>>::value == 21, "FIB N8 = 21");
static_assert(to_nat<FIB::of<N9>>::value == 34, "FIB N9 = 34");

// Direct syntactic translation of:
// Y = λf.(λx.f (x x)) (λx.f (x x))
// This mirrors the lambda term, but is not intended for eager evaluation.
struct Y {
  template <typename F> struct self_apply {
    template <typename X> using of = ap<F, ap<X, X>>;
  };

  template <typename F> using of = ap<self_apply<F>, self_apply<F>>;
};

// Direct syntactic translation of:
// Z = λf.(λx.f (λv.x x v)) (λx.f (λv.x x v))
// This mirrors the lambda term, but is not intended for eager evaluation.
struct Z {
  template <typename F> struct self_apply {
    template <typename X> struct delayed_self_apply {
      template <typename V> using of = ap<ap<X, X>, V>;
    };

    template <typename X> using of = ap<F, delayed_self_apply<X>>;
  };

  template <typename F> using of = ap<self_apply<F>, self_apply<F>>;
};
