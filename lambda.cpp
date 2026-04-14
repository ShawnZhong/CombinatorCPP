// Helper to compare if two lambda terms have the same type.
template <typename A, typename B>
struct is_same {
  static constexpr bool value = false;
};
template <typename T>
struct is_same<T, T> {
  static constexpr bool value = true;
};
auto eq = [](auto F, auto G) -> bool {
  return is_same<decltype(F), decltype(G)>::value;
};

// ANCHOR-BEGIN: I
// I x = x
auto I = [](auto a) {
  return a;
};
static_assert(eq(I(I), I));
// ANCHOR-END: I

// ANCHOR-BEGIN: M
// M f = f f
auto M = [](auto f) {
  return f(f);
};
static_assert(eq(M(I), I));
// ANCHOR-END: M

// ANCHOR-BEGIN: K
// K a b = a
auto K = [](auto a) {
  return [=](auto b) {
    return a;
  };
};
static_assert(eq(K(I)(M), I));
static_assert(eq(K(M)(I), M));
static_assert(eq(K(I)(M)(K), K));
// ANCHOR-END: K

// ANCHOR-BEGIN: KI
// KI a b = b
auto KI = [](auto a) {
  return [](auto b) {
    return b;
  };
};
static_assert(eq(KI(M)(K), K));
static_assert(eq(KI(K)(M), M));
// ANCHOR-END: KI

// ANCHOR-BEGIN: C
// C f a b = f b a
auto C = [](auto f) {
  return [=](auto a) {
    return [=](auto b) {
      return f(b)(a);
    };
  };
};
// C KI == K
static_assert(eq(K(I)(M), I));
static_assert(eq(C(KI)(I)(M), I));
// KI == C K
static_assert(eq(C(K)(I)(M), M));
static_assert(eq(KI(I)(M), M));
// ANCHOR-END: C

// ANCHOR-BEGIN: T_F
// T x y = x
// F x y = y
auto T = K;
auto F = KI;  // == C K
static_assert(eq(T(T)(F), T));
static_assert(eq(F(T)(F), F));
// ANCHOR-END: T_F

// ANCHOR-BEGIN: NOT
// NOT p = p F T
auto NOT = [](auto p) {
  return p(F)(T);
};
static_assert(eq(NOT(T), F));
static_assert(eq(NOT(F), T));
static_assert(eq(C(T)(T)(F), F));
static_assert(eq(C(F)(T)(F), T));
// ANCHOR-END: NOT

// ANCHOR-BEGIN: AND
// AND p q = p q F = p q p
auto AND = [](auto p) {
  return [=](auto q) {
    // return p(q)(F);
    return p(q)(p);
  };
};
static_assert(eq(AND(T)(T), T));
static_assert(eq(AND(T)(F), F));
static_assert(eq(AND(F)(T), F));
static_assert(eq(AND(F)(F), F));
// ANCHOR-END: AND

// ANCHOR-BEGIN: OR
// OR p q = p T q = p p q
auto OR = [](auto p) {
  return [=](auto q) {
    // return p(T)(q);
    return p(p)(q);
  };
};
static_assert(eq(OR(T)(T), T));
static_assert(eq(OR(T)(F), T));
static_assert(eq(OR(F)(T), T));
static_assert(eq(OR(F)(F), F));
// ANCHOR-END: OR

// ANCHOR-BEGIN: BEQ
// BEQ p q = p q (NOT q)
auto BEQ = [](auto p) {
  return [=](auto q) {
    return p(q)(NOT(q));
  };
};
static_assert(eq(BEQ(T)(T), T));
static_assert(eq(BEQ(T)(F), F));
static_assert(eq(BEQ(F)(T), F));
static_assert(eq(BEQ(F)(F), T));
// ANCHOR-END: BEQ

// ANCHOR-BEGIN: XOR
// XOR p q = p (NOT q) q
auto XOR = [](auto p) {
  return [=](auto q) {
    return p(NOT(q))(q);
  };
};
static_assert(eq(XOR(T)(T), F));
static_assert(eq(XOR(T)(F), T));
static_assert(eq(XOR(F)(T), T));
static_assert(eq(XOR(F)(F), F));
// ANCHOR-END: XOR

// Church numerals
// N0 f x = x
// N1 f x = f x
// N2 f x = f (f x)
// N3 f x = f (f (f x))
auto N0 = [](auto f) {
  return [=](auto x) {
    return x;
  };
};
auto N1 = [](auto f) {
  return [=](auto x) {
    return f(x);
  };
};
auto N2 = [](auto f) {
  return [=](auto x) {
    return f(f(x));
  };
};
auto N3 = [](auto f) {
  return [=](auto x) {
    return f(f(f(x)));
  };
};
static_assert(eq(N0(NOT)(F), F));
static_assert(eq(N1(NOT)(F), T));
static_assert(eq(N2(NOT)(F), F));
static_assert(eq(N3(NOT)(F), T));

// Convert Church numerals to C++ integers.
auto succ = [](int x) -> int {
  return x + 1;
};
auto to_nat = [](auto n) -> int {
  return n(succ)(0);
};
auto eq_nat = [](auto n, int x) -> bool {
  return to_nat(n) == x;
};
static_assert(eq_nat(N0, 0));
static_assert(eq_nat(N1, 1));
static_assert(eq_nat(N2, 2));
static_assert(eq_nat(N3, 3));

// ANCHOR-BEGIN: SUCC
// SUCC n f x = f (n f x)
auto SUCC = [](auto n) {
  return [=](auto f) {
    return [=](auto x) {
      return f(n(f)(x));
    };
  };
};
static_assert(eq_nat(SUCC(N0), 1));
static_assert(eq_nat(SUCC(SUCC(N0)), 2));
static_assert(eq_nat(SUCC(SUCC(SUCC(N0))), 3));
auto N4 = SUCC(N3);
static_assert(eq_nat(N4, 4));
// ANCHOR-END: SUCC

// ANCHOR-BEGIN: PRED
// PRED n f x = n shift (K x) I,
//   where shift f g = C I (g f)
auto PRED = [](auto n) {
  return [=](auto f) {
    return [=](auto x) {
      return n([=](auto g) {
        return [=](auto h) {
          return h(g(f));
        };
      })(K(x))(I);
    };
  };
};
static_assert(eq_nat(PRED(N1), 0));
static_assert(eq_nat(PRED(N2), 1));
static_assert(eq_nat(PRED(N3), 2));
// ANCHOR-END: PRED

// ANCHOR-BEGIN: B
// B f g x = f (g x)
auto B = [](auto f) {
  return [=](auto g) {
    return [=](auto x) {
      return f(g(x));
    };
  };
};
static_assert(eq(B(NOT)(NOT)(T), T));
// ANCHOR-END: B

// ANCHOR-BEGIN: SUCC2
// SUCC2 n f x = B f (n f) x
auto SUCC2 = [](auto n) {
  return [=](auto f) {
    return B(f)(n(f));
  };
};
static_assert(eq_nat(SUCC2(N0), 1));
static_assert(eq_nat(SUCC2(N3), 4));
// ANCHOR-END: SUCC2

// ANCHOR-BEGIN: ADD
// ADD n k = n SUCC k
auto ADD = [](auto n) {
  return [=](auto k) {
    return n(SUCC)(k);
  };
};
auto N5 = ADD(N2)(N3);
static_assert(eq_nat(N5, 5));
// ANCHOR-END: ADD

// ANCHOR-BEGIN: MUL
// MUL n k f = n (k f)
auto MUL = [](auto n) {
  return [=](auto k) {
    return [=](auto f) {
      return n(k(f));
    };
  };
};
auto N6 = MUL(N2)(N3);
auto N7 = ADD(MUL(N2)(N2))(MUL(N1)(N3));
static_assert(eq_nat(N6, 6));
static_assert(eq_nat(N7, 7));
static_assert(eq_nat(B(N2)(N3), 6));
// ANCHOR-END: MUL

// ANCHOR-BEGIN: POW
// POW n k = k n
auto POW = [](auto n) {
  return [=](auto k) {
    return k(n);
  };
};
auto Th = POW;
auto N8 = POW(N2)(N3);
auto N9 = Th(N3)(N2);
static_assert(eq_nat(N8, 8));
static_assert(eq_nat(N9, 9));
static_assert(eq_nat(POW(N3)(N4), 81));
// ANCHOR-END: POW

// ANCHOR-BEGIN: IS_ZERO
// IS_ZERO n = n (K F) T
auto IS_ZERO = [](auto n) {
  return n(K(F))(T);
};
static_assert(eq(IS_ZERO(N0), T));
static_assert(eq(IS_ZERO(N1), F));
static_assert(eq(IS_ZERO(N2), F));
// ANCHOR-END: IS_ZERO

// ANCHOR-BEGIN: V_PAIR
// V a b f = f a b
auto V = [](auto a) {
  return [=](auto b) {
    return [=](auto f) {
      return f(a)(b);
    };
  };
};
static_assert(eq_nat(V(N2)(N3)(ADD), 5));
static_assert(eq(V(I)(M)(K), I));
static_assert(eq(V(I)(M)(KI), M));

// PAIR = V
auto PAIR = V;
// ANCHOR-END: V_PAIR

// ANCHOR-BEGIN: FST
// FST p = p K
auto FST = [](auto p) {
  return p(K);
};
static_assert(eq(FST(PAIR(I)(M)), I));
static_assert(eq(FST(PAIR(N2)(N3)), N2));
// ANCHOR-END: FST

// ANCHOR-BEGIN: SND
// SND p = p KI
auto SND = [](auto p) {
  return p(KI);
};
static_assert(eq(SND(PAIR(I)(M)), M));
static_assert(eq(SND(PAIR(N2)(N3)), N3));
// ANCHOR-END: SND

// ANCHOR-BEGIN: PHI
// PHI p = PAIR (SND p) (SUCC (SND p))
auto PHI = [](auto p) {
  return V(SND(p))(SUCC(SND(p)));
};
auto N0N0 = PAIR(N0)(N0);
static_assert(eq_nat(FST(PHI(N0N0)), 0));
static_assert(eq_nat(SND(PHI(N0N0)), 1));
static_assert(eq_nat(FST(N3(PHI)(N0N0)), 2));
// ANCHOR-END: PHI

// ANCHOR-BEGIN: PRED2
// PRED2 n = FST (n PHI (PAIR N0 N0))
auto PRED2 = [](auto n) {
  return FST(n(PHI)(PAIR(N0)(N0)));
};
static_assert(eq_nat(PRED2(N1), 0));
static_assert(eq_nat(PRED2(N2), 1));
static_assert(eq_nat(PRED2(N3), 2));
// ANCHOR-END: PRED2

// ANCHOR-BEGIN: SUB
// SUB n k = k PRED n
auto SUB = [](auto n) {
  return [=](auto k) {
    return k(PRED)(n);
  };
};
static_assert(eq_nat(SUB(N0)(N0), 0));
static_assert(eq_nat(SUB(N3)(N1), 2));
static_assert(eq_nat(SUB(N3)(N2), 1));
static_assert(eq_nat(SUB(N9)(N2), 7));
// ANCHOR-END: SUB

// ANCHOR-BEGIN: LEQ
// LEQ n k = IS_ZERO (SUB n k)
auto LEQ = [](auto n) {
  return [=](auto k) {
    return IS_ZERO(SUB(n)(k));
  };
};
static_assert(eq(LEQ(N1)(N3), T));
static_assert(eq(LEQ(N2)(N2), T));
static_assert(eq(LEQ(N3)(N1), F));
// ANCHOR-END: LEQ

// ANCHOR-BEGIN: EQ
// EQ n k = AND (LEQ n k) (LEQ k n)
auto EQ = [](auto n) {
  return [=](auto k) {
    return AND(LEQ(n)(k))(LEQ(k)(n));
  };
};
static_assert(eq(EQ(N1)(N3), F));
static_assert(eq(EQ(N2)(N2), T));
static_assert(eq(EQ(N3)(N1), F));
// ANCHOR-END: EQ

// ANCHOR-BEGIN: GT
// GT n k = NOT (LEQ n k)
auto GT = [](auto n) {
  return [=](auto k) {
    return NOT(LEQ(n)(k));
  };
};
static_assert(eq(GT(N1)(N3), F));
static_assert(eq(GT(N2)(N2), F));
static_assert(eq(GT(N3)(N1), T));
// ANCHOR-END: GT

// ANCHOR-BEGIN: B1
// B1 f g a b = f (g a b)
auto B1 = [](auto f) {
  return [=](auto g) {
    return [=](auto a) {
      return [=](auto b) {
        return f(g(a)(b));
      };
    };
  };
};
// ANCHOR-END: B1

// ANCHOR-BEGIN: GT2
// GT2 n k = B1 NOT LEQ n k = NOT (LEQ n k)
auto GT2 = B1(NOT)(LEQ);
static_assert(eq(GT2(N1)(N3), F));
static_assert(eq(GT2(N2)(N2), F));
static_assert(eq(GT2(N3)(N1), T));
// ANCHOR-END: GT2

// ANCHOR-BEGIN: SET_FST
// SET_FST x p = PAIR x (SND p)
auto SET_FST = [](auto x) {
  return [=](auto p) {
    return PAIR(x)(SND(p));
  };
};
auto N1N2 = PAIR(N1)(N2);
static_assert(eq_nat(FST(SET_FST(N3)(N1N2)), 3));
// ANCHOR-END: SET_FST

// ANCHOR-BEGIN: SET_SND
// SET_SND x p = PAIR (FST p) x
auto SET_SND = [](auto x) {
  return [=](auto p) {
    return PAIR(FST(p))(x);
  };
};
static_assert(eq_nat(SND(SET_SND(N3)(N1N2)), 3));
// ANCHOR-END: SET_SND

// ANCHOR-BEGIN: FIB
// FIB n = n step K N0 N1,
//   where step f a b = f b (ADD a b)
auto FIB = [](auto n) {
  return n([](auto f) {
    return [=](auto a) {
      return [=](auto b) {
        return f(b)(ADD(a)(b));
      };
    };
  })(K)(N0)(N1);
};
static_assert(eq_nat(FIB(N0), 0));
static_assert(eq_nat(FIB(N1), 1));
static_assert(eq_nat(FIB(N2), 1));
static_assert(eq_nat(FIB(N3), 2));
static_assert(eq_nat(FIB(N4), 3));
static_assert(eq_nat(FIB(N5), 5));
static_assert(eq_nat(FIB(N6), 8));
static_assert(eq_nat(FIB(N7), 13));
static_assert(eq_nat(FIB(N8), 21));
static_assert(eq_nat(FIB(N9), 34));
// ANCHOR-END: FIB

// ANCHOR-BEGIN: Y
// Y = λf.(λx.f (x x)) (λx.f (x x))
auto Y = [](auto f) {
  return [=](auto x) {
    return f(x(x));
  }([=](auto x) {
    return f(x(x));
  });
};
// ANCHOR-END: Y

// ANCHOR-BEGIN: Z
// Z = λf.(λx.f (λv.x x v)) (λx.f (λv.x x v))
auto Z = [](auto f) {
  return [=](auto x) {
    return f([=](auto v) {
      return x(x)(v);
    });
  }([=](auto x) {
    return f([=](auto v) {
      return x(x)(v);
    });
  });
};
// ANCHOR-END: Z

int main() { return 0; }
