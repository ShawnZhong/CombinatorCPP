// Helper to check if two terms have the same type.
template <typename A, typename B>
struct is_same {
  static constexpr bool value = false;
};
template <typename T>
struct is_same<T, T> {
  static constexpr bool value = true;
};
#define eq(...) (is_same<__VA_ARGS__>::value)

// Helper for curried application.
// For example, `ap<F, X, Y>` := `F::of<X>::of<Y>`.
template <typename F, typename... Xs>
struct apply {
  using type = F;
};
template <typename F, typename X, typename... Xs>
struct apply<F, X, Xs...> {
  using type = typename apply<typename F::template of<X>,
                              Xs...>::type;
};
template <typename F, typename... Xs>
using ap = typename apply<F, Xs...>::type;

// ANCHOR-BEGIN: I
// I x = x
struct I {
  template <typename X>
  using of = X;
};
static_assert(eq(ap<I, I>, I), "");
// ANCHOR-END: I

// ANCHOR-BEGIN: M
// M f = f f
struct M {
  template <typename F>
  using of = ap<F, F>;
};
static_assert(eq(ap<M, I>, I), "");
// ANCHOR-END: M

// ANCHOR-BEGIN: K
// K a b = a
struct K {
  template <typename A>
  struct with_a {
    template <typename B>
    using of = A;
  };
  template <typename A>
  using of = with_a<A>;
};
static_assert(eq(ap<K, I, M>, I), "");
static_assert(eq(ap<K, M, I>, M), "");
static_assert(eq(ap<K, I, M, K>, K), "");
// ANCHOR-END: K

// ANCHOR-BEGIN: KI
// KI a b = b
struct KI {
  template <typename A>
  struct with_a {
    template <typename B>
    using of = B;
  };
  template <typename A>
  using of = with_a<A>;
};
static_assert(eq(ap<KI, M, K>, K), "");
static_assert(eq(ap<KI, K, M>, M), "");
// ANCHOR-END: KI

// ANCHOR-BEGIN: C
// C f a b = f b a
struct C {
  template <typename F>
  struct with_f {
    template <typename A>
    struct with_a {
      template <typename B>
      using of = ap<F, B, A>;
    };
    template <typename A>
    using of = with_a<A>;
  };
  template <typename F>
  using of = with_f<F>;
};
// C KI == K
static_assert(eq(ap<K, I, M>, I), "");
static_assert(eq(ap<C, KI, I, M>, I), "");
// KI == C K
static_assert(eq(ap<C, K, I, M>, M), "");
static_assert(eq(ap<KI, I, M>, M), "");
// ANCHOR-END: C

// ANCHOR-BEGIN: T_F
// T x y = x
// F x y = y
using T = K;
using F = KI;
static_assert(eq(ap<T, T, F>, T), "");
static_assert(eq(ap<F, T, F>, F), "");
// ANCHOR-END: T_F

// ANCHOR-BEGIN: NOT
// NOT p = p F T
struct NOT {
  template <typename P>
  using of = ap<P, F, T>;
};
static_assert(eq(ap<NOT, T>, F), "");
static_assert(eq(ap<NOT, F>, T), "");
static_assert(eq(ap<C, T, T, F>, F), "");
static_assert(eq(ap<C, F, T, F>, T), "");
// ANCHOR-END: NOT

// ANCHOR-BEGIN: AND
// AND p q = p q F = p q p
struct AND {
  template <typename P>
  struct with_p {
    template <typename Q>
    using of = ap<P, Q, F>;
    template <typename Q>
    using of2 = ap<P, Q, P>;
  };
  template <typename P>
  using of = with_p<P>;
};
static_assert(eq(ap<AND, T, T>, T), "");
static_assert(eq(ap<AND, T, F>, F), "");
static_assert(eq(ap<AND, F, T>, F), "");
static_assert(eq(ap<AND, F, F>, F), "");
// ANCHOR-END: AND

// ANCHOR-BEGIN: OR
// OR p q = p T q = p p q
struct OR {
  template <typename P>
  struct with_p {
    template <typename Q>
    using of = ap<P, T, Q>;
    template <typename Q>
    using of2 = ap<P, P, Q>;
  };
  template <typename P>
  using of = with_p<P>;
};
static_assert(eq(ap<OR, T, T>, T), "");
static_assert(eq(ap<OR, T, F>, T), "");
static_assert(eq(ap<OR, F, T>, T), "");
static_assert(eq(ap<OR, F, F>, F), "");
// ANCHOR-END: OR

// ANCHOR-BEGIN: BEQ
// BEQ p q = p q (NOT q)
struct BEQ {
  template <typename P>
  struct with_p {
    template <typename Q>
    using of = ap<P, Q, ap<NOT, Q>>;
  };
  template <typename P>
  using of = with_p<P>;
};
static_assert(eq(ap<BEQ, T, T>, T), "");
static_assert(eq(ap<BEQ, T, F>, F), "");
static_assert(eq(ap<BEQ, F, T>, F), "");
static_assert(eq(ap<BEQ, F, F>, T), "");
// ANCHOR-END: BEQ

// ANCHOR-BEGIN: XOR
// XOR p q = p (NOT q) q
struct XOR {
  template <typename P>
  struct with_p {
    template <typename Q>
    using of = ap<P, ap<NOT, Q>, Q>;
  };
  template <typename P>
  using of = with_p<P>;
};
static_assert(eq(ap<XOR, T, T>, F), "");
static_assert(eq(ap<XOR, T, F>, T), "");
static_assert(eq(ap<XOR, F, T>, T), "");
static_assert(eq(ap<XOR, F, F>, F), "");
// ANCHOR-END: XOR

// Church encoding of natural numbers
// Applies the first argument n times to the second argument

// N0 f x = x
struct N0 {
  template <typename F>
  struct with_f {
    template <typename X>
    using of = X;
  };
  template <typename F>
  using of = with_f<F>;
};

// N1 f x = f x
struct N1 {
  template <typename F>
  struct with_f {
    template <typename X>
    using of = ap<F, X>;
  };
  template <typename F>
  using of = with_f<F>;
};

// N2 f x = f (f x)
struct N2 {
  template <typename F>
  struct with_f {
    template <typename X>
    using of = ap<F, ap<F, X>>;
  };
  template <typename F>
  using of = with_f<F>;
};

// N3 f x = f (f (f x))
struct N3 {
  template <typename F>
  struct with_f {
    template <typename X>
    using of = ap<F, ap<F, ap<F, X>>>;
  };
  template <typename F>
  using of = with_f<F>;
};

static_assert(eq(ap<N0, NOT, F>, F), "");
static_assert(eq(ap<N1, NOT, F>, T), "");
static_assert(eq(ap<N2, NOT, F>, F), "");
static_assert(eq(ap<N3, NOT, F>, T), "");

// Helper functions to convert Church numerals to integers
template <int N>
struct nat {
  static constexpr int value = N;
};
struct succ {
  template <typename N>
  using of = nat<N::value + 1>;
};
template <typename N>
using to_nat = ap<N, succ, nat<0>>;
template <typename A, int N>
using is_same_nat = is_same<to_nat<A>, nat<N>>;
#define eq_nat(...) (is_same_nat<__VA_ARGS__>::value)
static_assert(eq_nat(N0, 0), "");
static_assert(eq_nat(N1, 1), "");
static_assert(eq_nat(N2, 2), "");
static_assert(eq_nat(N3, 3), "");

// ANCHOR-BEGIN: SUCC
// SUCC n f x = f (n f x)
struct SUCC {
  template <typename N>
  struct with_n {
    template <typename F>
    struct with_f {
      template <typename X>
      using of = ap<F, ap<N, F, X>>;
    };
    template <typename F>
    using of = with_f<F>;
  };
  template <typename N>
  using of = with_n<N>;
};
static_assert(eq_nat(ap<SUCC, N0>, 1), "");
static_assert(eq_nat(ap<SUCC, N1>, 2), "");
static_assert(eq_nat(ap<SUCC, N2>, 3), "");
using N4 = ap<SUCC, N3>;
static_assert(eq_nat(N4, 4), "");
// ANCHOR-END: SUCC

// ANCHOR-BEGIN: PRED
// PRED n f x = n shift (K x) I,
//   where shift f g = C I (g f)
struct PRED {
  struct shift {
    template <typename F>
    struct with_f {
      template <typename G>
      using of = ap<C, I, ap<G, F>>;
    };
    template <typename F>
    using of = with_f<F>;
  };

  template <typename N>
  struct with_n {
    template <typename F>
    struct with_f {
      template <typename X>
      using of = ap<N, ap<shift, F>, ap<K, X>, I>;
    };
    template <typename F>
    using of = with_f<F>;
  };
  template <typename N>
  using of = with_n<N>;
};
static_assert(eq_nat(ap<PRED, N1>, 0), "");
static_assert(eq_nat(ap<PRED, N2>, 1), "");
static_assert(eq_nat(ap<PRED, N3>, 2), "");
// ANCHOR-END: PRED

// ANCHOR-BEGIN: B
// B f g x = f (g x)
struct B {
  template <typename F>
  struct with_f {
    template <typename G>
    struct with_g {
      template <typename X>
      using of = ap<F, ap<G, X>>;
    };
    template <typename G>
    using of = with_g<G>;
  };
  template <typename F>
  using of = with_f<F>;
};
static_assert(eq(ap<B, NOT, NOT, T>, T), "");
// ANCHOR-END: B

// ANCHOR-BEGIN: SUCC2
// SUCC2 n f x = B f (n f) x
struct SUCC2 {
  template <typename N>
  struct with_n {
    template <typename F>
    struct with_f {
      template <typename X>
      using of = ap<B, F, ap<N, F>, X>;
    };
    template <typename F>
    using of = with_f<F>;
  };
  template <typename N>
  using of = with_n<N>;
};
static_assert(eq_nat(ap<SUCC2, N0>, 1), "");
static_assert(eq_nat(ap<SUCC2, N3>, 4), "");
// ANCHOR-END: SUCC2

// ANCHOR-BEGIN: ADD
// ADD n k = n SUCC k
struct ADD {
  template <typename N>
  struct with_n {
    template <typename K>
    using of = ap<N, SUCC, K>;
  };
  template <typename N>
  using of = with_n<N>;
};
using N5 = ap<ADD, N2, N3>;
static_assert(eq_nat(N5, 5), "");
// ANCHOR-END: ADD

// ANCHOR-BEGIN: MUL
// MUL n k f = n (k f)
struct MUL {
  template <typename N>
  struct with_n {
    template <typename K>
    struct with_k {
      template <typename F>
      using of = ap<N, ap<K, F>>;
    };
    template <typename K>
    using of = with_k<K>;
  };
  template <typename N>
  using of = with_n<N>;
};
using N6 = ap<MUL, N2, N3>;
static_assert(eq_nat(N6, 6), "");
using N7 = ap<ADD, N4, ap<MUL, N1, N3>>;
static_assert(eq_nat(N7, 7), "");
static_assert(eq_nat(ap<B, N6, N7>, 42), "");
// ANCHOR-END: MUL

// ANCHOR-BEGIN: POW
// POW n k = k n
struct POW {
  template <typename N>
  struct with_n {
    template <typename K>
    struct with_k {
      template <typename F>
      using of = ap<K, N, F>;
    };
    template <typename K>
    using of = with_k<K>;
  };
  template <typename N>
  using of = with_n<N>;
};
using N8 = ap<POW, N2, N3>;
using N9 = ap<POW, N3, N2>;
static_assert(eq_nat(N8, 8), "");
static_assert(eq_nat(N9, 9), "");
// ANCHOR-END: POW

// ANCHOR-BEGIN: IS_ZERO
// IS_ZERO n = n (K F) T
struct IS_ZERO {
  template <typename N>
  using of = ap<N, ap<K, F>, T>;
};
static_assert(eq(ap<IS_ZERO, N0>, T), "");
static_assert(eq(ap<IS_ZERO, N1>, F), "");
static_assert(eq(ap<IS_ZERO, N2>, F), "");
// ANCHOR-END: IS_ZERO

// ANCHOR-BEGIN: V_PAIR
// V a b f = f a b
struct V {
  template <typename A>
  struct with_a {
    template <typename B>
    struct with_b {
      template <typename F>
      using of = ap<F, A, B>;
    };
    template <typename B>
    using of = with_b<B>;
  };
  template <typename A>
  using of = with_a<A>;
};
static_assert(eq_nat(ap<V, N2, N3, ADD>, 5), "");
static_assert(eq(ap<V, I, M, K, I>, I), "");
static_assert(eq(ap<V, I, M, K, M>, M), "");

// PAIR = V
using PAIR = V;
// ANCHOR-END: V_PAIR

// ANCHOR-BEGIN: FST
// FST p = p K
struct FST {
  template <typename P>
  using of = ap<P, K>;
};
static_assert(eq(ap<FST, ap<PAIR, I, M>>, I), "");
static_assert(eq(ap<FST, ap<PAIR, N2, N3>>, N2), "");
// ANCHOR-END: FST

// ANCHOR-BEGIN: SND
// SND p = p KI
struct SND {
  template <typename P>
  using of = ap<P, KI>;
};
static_assert(eq(ap<SND, ap<PAIR, I, M>>, M), "");
static_assert(eq(ap<SND, ap<PAIR, N2, N3>>, N3), "");
// ANCHOR-END: SND

// ANCHOR-BEGIN: PHI
// PHI p = PAIR (SND p) (SUCC (SND p))
struct PHI {
  template <typename P>
  using of = ap<PAIR, ap<SND, P>, ap<SUCC, ap<SND, P>>>;
};
using N0N0 = ap<PAIR, N0, N0>;
static_assert(eq_nat(ap<FST, ap<PHI, N0N0>>, 0), "");
static_assert(eq_nat(ap<SND, ap<PHI, N0N0>>, 1), "");
static_assert(eq_nat(ap<FST, ap<N3, PHI, N0N0>>, 2), "");
// ANCHOR-END: PHI

// ANCHOR-BEGIN: PRED2
// PRED2 n = FST (n PHI (PAIR N0 N0))
struct PRED2 {
  template <typename N>
  using of = ap<FST, ap<N, PHI, N0N0>>;
};
static_assert(eq_nat(ap<PRED2, N1>, 0), "");
static_assert(eq_nat(ap<PRED2, N2>, 1), "");
static_assert(eq_nat(ap<PRED2, N3>, 2), "");
// ANCHOR-END: PRED2

// ANCHOR-BEGIN: SUB
// SUB n k = k PRED n
struct SUB {
  template <typename N>
  struct with_n {
    template <typename K>
    using of = ap<K, PRED, N>;
  };
  template <typename N>
  using of = with_n<N>;
};
static_assert(eq_nat(ap<SUB, N0, N0>, 0), "");
static_assert(eq_nat(ap<SUB, N3, N1>, 2), "");
static_assert(eq_nat(ap<SUB, N3, N2>, 1), "");
// ANCHOR-END: SUB

// ANCHOR-BEGIN: LEQ
// LEQ n k = IS_ZERO (SUB n k)
struct LEQ {
  template <typename N>
  struct with_n {
    template <typename K>
    using of = ap<IS_ZERO, ap<SUB, N, K>>;
  };
  template <typename N>
  using of = with_n<N>;
};
static_assert(eq(ap<LEQ, N1, N3>, T), "");
static_assert(eq(ap<LEQ, N2, N2>, T), "");
static_assert(eq(ap<LEQ, N3, N1>, F), "");
// ANCHOR-END: LEQ

// ANCHOR-BEGIN: EQ
// EQ n k = AND (LEQ n k) (LEQ k n)
struct EQ {
  template <typename N>
  struct with_n {
    template <typename K>
    using of = ap<AND, ap<LEQ, N, K>, ap<LEQ, K, N>>;
  };
  template <typename N>
  using of = with_n<N>;
};
static_assert(eq(ap<EQ, N1, N3>, F), "");
static_assert(eq(ap<EQ, N2, N2>, T), "");
static_assert(eq(ap<EQ, N3, N1>, F), "");
// ANCHOR-END: EQ

// ANCHOR-BEGIN: GT
// GT n k = NOT (LEQ n k)
struct GT {
  template <typename N>
  struct with_n {
    template <typename K>
    using of = ap<NOT, ap<LEQ, N, K>>;
  };
  template <typename N>
  using of = with_n<N>;
};
static_assert(eq(ap<GT, N1, N3>, F), "");
static_assert(eq(ap<GT, N2, N2>, F), "");
static_assert(eq(ap<GT, N3, N1>, T), "");
// ANCHOR-END: GT

// ANCHOR-BEGIN: B1
// B1 f g a b = f (g a b)
struct B1 {
  template <typename F>
  struct with_f {
    template <typename G>
    struct with_g {
      template <typename A>
      struct with_a {
        template <typename B>
        using of = ap<F, ap<G, A, B>>;
      };
      template <typename A>
      using of = with_a<A>;
    };
    template <typename G>
    using of = with_g<G>;
  };
  template <typename F>
  using of = with_f<F>;
};
// ANCHOR-END: B1

// ANCHOR-BEGIN: GT2
// GT2 n k = B1 NOT LEQ n k = NOT (LEQ n k)
using GT2 = ap<B1, NOT, LEQ>;
static_assert(eq(ap<GT2, N1, N3>, F), "");
static_assert(eq(ap<GT2, N2, N2>, F), "");
static_assert(eq(ap<GT2, N3, N1>, T), "");
// ANCHOR-END: GT2

// ANCHOR-BEGIN: SET_FST
// SET_FST x p = PAIR x (SND p)
struct SET_FST {
  template <typename X>
  struct with_x {
    template <typename P>
    using of = ap<PAIR, X, ap<SND, P>>;
  };
  template <typename X>
  using of = with_x<X>;
};
using N1N2 = ap<PAIR, N1, N2>;
static_assert(eq_nat(ap<FST, ap<SET_FST, N3, N1N2>>, 3),
              "");
// ANCHOR-END: SET_FST

// ANCHOR-BEGIN: SET_SND
// SET_SND x p = PAIR (FST p) x
struct SET_SND {
  template <typename X>
  struct with_x {
    template <typename P>
    using of = ap<PAIR, ap<FST, P>, X>;
  };
  template <typename X>
  using of = with_x<X>;
};
static_assert(eq_nat(ap<SND, ap<SET_SND, N3, N1N2>>, 3),
              "");
// ANCHOR-END: SET_SND

// ANCHOR-BEGIN: FIB
// FIB n = n step K N0 N1,
//   where step f a b = f b (ADD a b)
struct FIB {
  struct step {
    template <typename F>
    struct with_f {
      template <typename A>
      struct with_a {
        template <typename B>
        using of = ap<F, B, ap<ADD, A, B>>;
      };
      template <typename A>
      using of = with_a<A>;
    };
    template <typename F>
    using of = with_f<F>;
  };
  template <typename N>
  using of = ap<N, step, K, N0, N1>;
};
static_assert(eq_nat(ap<FIB, N0>, 0), "");
static_assert(eq_nat(ap<FIB, N1>, 1), "");
static_assert(eq_nat(ap<FIB, N2>, 1), "");
static_assert(eq_nat(ap<FIB, N3>, 2), "");
static_assert(eq_nat(ap<FIB, N4>, 3), "");
static_assert(eq_nat(ap<FIB, N5>, 5), "");
static_assert(eq_nat(ap<FIB, N6>, 8), "");
static_assert(eq_nat(ap<FIB, N7>, 13), "");
static_assert(eq_nat(ap<FIB, N8>, 21), "");
static_assert(eq_nat(ap<FIB, N9>, 34), "");
// ANCHOR-END: FIB

// ANCHOR-BEGIN: Y
// Y = λf.(λx.f (x x)) (λx.f (x x))
struct Y {
  template <typename F>
  struct self_apply {
    template <typename X>
    using of = ap<F, ap<X, X>>;
  };
  template <typename F>
  using of = ap<self_apply<F>, self_apply<F>>;
};
// ANCHOR-END: Y

// ANCHOR-BEGIN: Z
// Z = λf.(λx.f (λv.x x v)) (λx.f (λv.x x v))
struct Z {
  template <typename F>
  struct self_apply {
    template <typename X>
    struct delayed_self_apply {
      template <typename V>
      using of = ap<X, X, V>;
    };
    template <typename X>
    using of = ap<F, delayed_self_apply<X>>;
  };
  template <typename F>
  using of = ap<self_apply<F>, self_apply<F>>;
};
// ANCHOR-END: Z

int main() { return 0; }
