/**
 * Helper function to compare if two functions are of the same type
 */
template <typename A, typename B> struct is_same {
  static constexpr bool value = false;
};
template <typename T> struct is_same<T, T> {
  static constexpr bool value = true;
};
auto eq = [](auto F, auto G) -> bool {
  return is_same<decltype(F), decltype(G)>::value;
};

/**
 * Identity combinator, aka idiot combinator
 * returns the argument unchanged
 * λa.a
 */
auto I = [](auto a) {
  return a;
};
static_assert(eq(I(I), I), "I I == I");

/**
 * Mockingbird combinator
 * applies the argument to itself
 * λf.f f
 */
auto M = [](auto f) {
  return f(f);
};
static_assert(eq(M(I), I), "M I == I");

/**
 * Kestrel combinator, aka constant combinator
 * returns the first argument unchanged
 * λab.a
 */
auto K = [](auto a) {
  return [=](auto b) {
    return a;
  };
};
static_assert(eq(K(I)(M), I), "K I M == I");
static_assert(eq(K(M)(I), M), "K M I == M");
static_assert(eq(K(I)(M)(K), K), "K I M K == K");

/**
 * Kite combinator, equivalent to K(I) and C(K)
 * returns the second argument unchanged
 * λab.b
 */
auto KI = [](auto a) {
  return [](auto b) {
    return b;
  };
};
static_assert(eq(KI(M)(K), K), "KI M K == K");
static_assert(eq(KI(K)(M), M), "KI K M == M");

/**
 * Cardinal combinator, aka flip combinator
 * reverses the arguments
 * λfab.fba
 */
auto C = [](auto f) {
  return [=](auto a) {
    return [=](auto b) {
      return f(b)(a);
    };
  };
};
// C KI == K
static_assert(eq(K(I)(M), I), "K I M == I");
static_assert(eq(C(KI)(I)(M), I), "C KI I M == I");
// KI == C K
static_assert(eq(C(K)(I)(M), M), "C K I M == M");
static_assert(eq(KI(I)(M), M), "KI I M == M");

/**
 * Church encoding of booleans
 * T T F = T
 * F T F = F
 */
auto T = K;
auto F = KI; // == C K
static_assert(eq(T(T)(F), T), "T T F == T");
static_assert(eq(F(T)(F), F), "F T F == F");

/**
 * Negation, equivalent to C
 * λp.p F T
 */
auto NOT = [](auto p) {
  return p(F)(T);
};
static_assert(eq(NOT(T), F), "NOT T == F");
static_assert(eq(NOT(F), T), "NOT F == T");
static_assert(eq(C(T)(T)(F), F), "C(T) T F == F");
static_assert(eq(C(F)(T)(F), T), "C(F) T F == T");

/**
 * Conjunction
 * λpq.p q p = λpq.p q F
 */
auto AND = [](auto p) {
  return [=](auto q) {
    // return p(q)(F);
    return p(q)(p);
  };
};
static_assert(eq(AND(T)(T), T), "AND T T == T");
static_assert(eq(AND(T)(F), F), "AND T F == F");
static_assert(eq(AND(F)(T), F), "AND F T == F");
static_assert(eq(AND(F)(F), F), "AND F F == F");

/**
 * Disjunction, equivalent to M*
 * λpq.p p q = λpq.p T q
 */
auto OR = [](auto p) {
  return [=](auto q) {
    // return p(T)(q);
    return p(p)(q);
  };
};
static_assert(eq(OR(T)(T), T), "OR T T == T");
static_assert(eq(OR(T)(F), T), "OR T F == T");
static_assert(eq(OR(F)(T), T), "OR F T == T");
static_assert(eq(OR(F)(F), F), "OR F F == F");

/**
 * Boolean equality
 * λpq.p q (NOT q)
 */
auto BEQ = [](auto p) {
  return [=](auto q) {
    return p(q)(NOT(q));
  };
};
static_assert(eq(BEQ(T)(T), T), "BEQ T T == T");
static_assert(eq(BEQ(T)(F), F), "BEQ T F == F");
static_assert(eq(BEQ(F)(T), F), "BEQ F T == F");
static_assert(eq(BEQ(F)(F), T), "BEQ F F == T");

/**
 * Boolean exclusive disjunction
 * λpq.p (NOT q) q
 */
auto XOR = [](auto p) {
  return [=](auto q) {
    return p(NOT(q))(q);
  };
};
static_assert(eq(XOR(T)(T), F), "XOR T T == F");
static_assert(eq(XOR(T)(F), T), "XOR T F == T");
static_assert(eq(XOR(F)(T), T), "XOR F T == T");
static_assert(eq(XOR(F)(F), F), "XOR F F == F");

/**
 * Church encoding of integers
 * Applies the first argument n times to the second argument
 * N0 = λfx.x = F = KI = CK
 * N1 = λfx.fx
 * N2 = λfx.f(fx)
 * N3 = λfx.f(f(fx))
 * ...
 */
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
static_assert(eq(N0(NOT)(F), F), "N0 NOT F == F");
static_assert(eq(N1(NOT)(F), T), "N1 NOT F == T");
static_assert(eq(N2(NOT)(F), F), "N2 NOT F == F");
static_assert(eq(N3(NOT)(F), T), "N3 NOT F == T");

/**
 * Helper functions to convert Church integers to C++ integers
 */
auto succ = [](int x) -> int {
  return x + 1;
};
auto nat = [](auto n) -> int {
  return n(succ)(0);
};
static_assert(nat(N0) == 0, "N0 = 0");
static_assert(nat(N1) == 1, "N1 = 1");
static_assert(nat(N2) == 2, "N2 = 2");
static_assert(nat(N3) == 3, "N3 = 3");

/**
 * Successor
 * λnfx.f(nfx)
 */
auto SUCC = [](auto n) {
  return [=](auto f) {
    return [=](auto x) {
      return f(n(f)(x));
    };
  };
};
static_assert(nat(SUCC(N0)) == 1, "SUCC N0 = 1");
static_assert(nat(SUCC(SUCC(N0))) == 2, "SUCC SUCC N0 = 2");
static_assert(nat(SUCC(SUCC(SUCC(N0)))) == 3, "SUCC SUCC SUCC N0 = 3");
auto N4 = SUCC(N3);
static_assert(nat(N4) == 4, "N4 = 4");

/**
 * Predecessor
 * λnfx.n (λgh.h (g f)) (λu.x) (λu.u)
 */
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
static_assert(nat(PRED(N1)) == 0, "PRED N1 = 0");
static_assert(nat(PRED(N2)) == 1, "PRED N2 = 1");
static_assert(nat(PRED(N3)) == 2, "PRED N3 = 2");

/**
 * Bluebird combinator
 * composes two unary functions
 * λfgx.f(gx)
 */
auto B = [](auto f) {
  return [=](auto g) {
    return [=](auto x) {
      return f(g(x));
    };
  };
};
static_assert(eq(B(NOT)(NOT)(T), T), "B(NOT) NOT T == T");

/**
 * Successor written in terms of B
 * λnf.Bf(nf)
 */
auto SUCC2 = [](auto n) {
  return [=](auto f) {
    return B(f)(n(f));
  };
};
static_assert(nat(SUCC2(N0)) == 1, "SUCC2 N0 = 1");
static_assert(nat(SUCC2(N3)) == 4, "SUCC2 N3 = 4");

/**
 * Addition
 * applies SUCC n times to k
 * λnk.n SUCC k
 */
auto ADD = [](auto n) {
  return [=](auto k) {
    return n(SUCC)(k);
  };
};
auto N5 = ADD(N2)(N3);
static_assert(nat(N5) == 5, "ADD N2 N3 = 5");

/**
 * Multiplication, equivalent to B
 * λnkf.n(kf)
 */
auto MUL = [](auto n) {
  return [=](auto k) {
    return [=](auto f) {
      return n(k(f));
    };
  };
};
auto N6 = MUL(N2)(N3);
auto N7 = ADD(MUL(N2)(N2))(MUL(N1)(N3));
static_assert(nat(N6) == 6, "MUL N2 N3 = 6");
static_assert(nat(N7) == 7, "ADD MUL N2 N2 MUL N1 N3 = 7");
static_assert(nat(B(N2)(N3)) == 6, "B N2 N3 = 6");

/**
 * Exponentiation, equivalent to the Thrush combinator
 * λnk.kn
 */
auto POW = [](auto n) {
  return [=](auto k) {
    return k(n);
  };
};
auto Th = POW;
auto N8 = POW(N2)(N3);
auto N9 = Th(N3)(N2);
static_assert(nat(N8) == 8, "POW N2 N3 = 8");
static_assert(nat(N9) == 9, "Th N3 N2 = 9");
static_assert(nat(POW(N3)(N4)) == 81, "POW N3 N4 = 81");

/**
 * Check if n is zero
 * applies constant F to T by n times
 * λn.n KF T
 */
auto IS_ZERO = [](auto n) {
  return n(K(F))(T);
};
static_assert(eq(IS_ZERO(N0), T), "IS_ZERO N0 = T");
static_assert(eq(IS_ZERO(N1), F), "IS_ZERO N1 = F");
static_assert(eq(IS_ZERO(N2), F), "IS_ZERO N2 = F");

/**
 * Vireo combinator, equivalent to BCT
 * also used to hold a pair of arguments
 * holds a pair of args
 * λabf.fab
 */
auto V = [](auto a) {
  return [=](auto b) {
    return [=](auto f) {
      return f(a)(b);
    };
  };
};
static_assert(nat(V(N2)(N3)(ADD)) == 5, "V N2 N3 ADD = 5");
static_assert(eq(V(I)(M)(K), I), "V I M K = I");
static_assert(eq(V(I)(M)(KI), M), "V I M KI = M");

/**
 * Church encoding of pairs, equivalent to V
 */
auto PAIR = V;

/**
 * Extract first argument from a pair
 * λp.p K
 */
auto FST = [](auto p) {
  return p(K);
};
static_assert(eq(FST(PAIR(I)(M)), I), "FST PAIR I M = I");
static_assert(eq(FST(PAIR(N2)(N3)), N2), "FST PAIR N2 N3 = N2");

/**
 * Extract second argument from a pair
 * λp.p KI
 */
auto SND = [](auto p) {
  return p(KI);
};
static_assert(eq(SND(PAIR(I)(M)), M), "SND PAIR I M = M");
static_assert(eq(SND(PAIR(N2)(N3)), N3), "SND PAIR N2 N3 = N3");

/**
 * Phi combinator
 * copy second argument to first argument and increment second argument
 * λp. PAIR (SND p) (SUCC (SND p))
 */
auto PHI = [](auto p) {
  return V(SND(p))(SUCC(SND(p)));
};
static_assert(nat(FST(PHI(PAIR(N0)(N0)))) == 0, "FST PHI PAIR N0 N0 = 0");
static_assert(nat(SND(PHI(PAIR(N0)(N0)))) == 1, "SND PHI PAIR N0 N0 = 1");
static_assert(nat(FST(N3(PHI)(PAIR(N0)(N0)))) == 2,
              "FST N3 PHI PAIR N0 N0 = 2");

/**
 * Predecessor written in terms of PHI
 * λn. FST (n PHI (PAIR N0 N0))
 */
auto PRED2 = [](auto n) {
  return FST(n(PHI)(PAIR(N0)(N0)));
};
static_assert(nat(PRED2(N1)) == 0, "PRED2 N1 = 0");
static_assert(nat(PRED2(N2)) == 1, "PRED2 N2 = 1");
static_assert(nat(PRED2(N3)) == 2, "PRED2 N3 = 2");

/**
 * Subtraction
 * applies PRED n times to k
 * λnk.k PRED n
 */
auto SUB = [](auto n) {
  return [=](auto k) {
    return k(PRED)(n);
  };
};
static_assert(nat(SUB(N0)(N0)) == 0, "SUB N0 N0 = 0");
static_assert(nat(SUB(N3)(N1)) == 2, "SUB N3 N1 = 2");
static_assert(nat(SUB(N3)(N2)) == 1, "SUB N3 N2 = 1");
static_assert(nat(SUB(N9)(N2)) == 7, "SUB N9 N2 = 7");

/**
 * Less than or equal
 * checks if the result of SUB is zero
 * λnk.IS_ZERO (SUB n k)
 */
auto LEQ = [](auto n) {
  return [=](auto k) {
    return IS_ZERO(SUB(n)(k));
  };
};
static_assert(eq(LEQ(N1)(N3), T), "LEQ N1 N3 = T");
static_assert(eq(LEQ(N2)(N2), T), "LEQ N2 N2 = T");
static_assert(eq(LEQ(N3)(N1), F), "LEQ N3 N1 = F");

/**
 * Equality
 * checks if LEQ is true on both directions
 * λnk.AND (LEQ n k) (LEQ k n)
 */
auto EQ = [](auto n) {
  return [=](auto k) {
    return AND(LEQ(n)(k))(LEQ(k)(n));
  };
};
static_assert(eq(EQ(N1)(N3), F), "EQ N1 N3 = F");
static_assert(eq(EQ(N2)(N2), T), "EQ N2 N2 = T");
static_assert(eq(EQ(N3)(N1), F), "EQ N3 N1 = F");

/**
 * Greater than
 * negation of LEQ
 * λnk.NOT (LEQ n k)
 */
auto GT = [](auto n) {
  return [=](auto k) {
    return NOT(LEQ(n)(k));
  };
};
static_assert(eq(GT(N1)(N3), F), "GT N1 N3 = F");
static_assert(eq(GT(N2)(N2), F), "GT N2 N2 = F");
static_assert(eq(GT(N3)(N1), T), "GT N3 N1 = T");

/**
 * Blackbird combinator, equivalent to BBB
 * composes an unary function with a binary function
 * λfgab.f (g a b)
 */
auto B1 = [](auto f) {
  return [=](auto g) {
    return [=](auto a) {
      return [=](auto b) {
        return f(g(a)(b));
      };
    };
  };
};

/**
 * Greater than written in terms of B1
 * composition of NOT and LEQ
 */
auto GT2 = B1(NOT)(LEQ);
static_assert(eq(GT2(N1)(N3), F), "GT2 N1 N3 = F");
static_assert(eq(GT2(N2)(N2), F), "GT2 N2 N2 = F");
static_assert(eq(GT2(N3)(N1), T), "GT2 N3 N1 = T");

/**
 * Set the first element of a pair
 * λxp.PAIR x (SND p)
 */
auto SET_FST = [](auto x) {
  return [=](auto p) {
    return PAIR(x)(SND(p));
  };
};
static_assert(nat(FST(SET_FST(N3)(PAIR(N1)(N2)))) == 3,
              "FST SET_FST N3 PAIR N1 N2 = 3");

/**
 * Set the second element of a pair
 * λxp.PAIR (FST p) x
 */
auto SET_SND = [](auto x) {
  return [=](auto p) {
    return PAIR(FST(p))(x);
  };
};
static_assert(nat(SND(SET_SND(N3)(PAIR(N1)(N2)))) == 3,
              "SND SET_SND N3 PAIR N1 N2 = 3");

/**
 * Fibonacci function
 * λn.n (λfab.f b(ADD a b)) K 0 1
 */
auto FIB = [](auto n) {
  return n([](auto f) {
    return [=](auto a) {
      return [=](auto b) {
        return f(b)(ADD(a)(b));
      };
    };
  })(K)(N0)(N1);
};
static_assert(nat(FIB(N0)) == 0, "FIB N0 = 0");
static_assert(nat(FIB(N1)) == 1, "FIB N1 = 1");
static_assert(nat(FIB(N2)) == 1, "FIB N2 = 1");
static_assert(nat(FIB(N3)) == 2, "FIB N3 = 2");
static_assert(nat(FIB(N4)) == 3, "FIB N4 = 3");
static_assert(nat(FIB(N5)) == 5, "FIB N5 = 5");
static_assert(nat(FIB(N6)) == 8, "FIB N6 = 8");
static_assert(nat(FIB(N7)) == 13, "FIB N7 = 13");
static_assert(nat(FIB(N8)) == 21, "FIB N8 = 21");
static_assert(nat(FIB(N9)) == 34, "FIB N9 = 34");

/**
 * Y combinator
 * λf.(λx.f (x x)) (λx.f (x x))
 * Unfortunately, this is not possible in C++ because of eager evaluation
 */
auto Y = [](auto f) {
  return [=](auto x) {
    return f(x(x));
  }([=](auto x) {
    return f(x(x));
  });
};

/**
 * Z combinator
 * λf.(λx.f (λv.x x v)) (λx.f (λv.x x v))
 * Unfortunately, this is not possible in C++ as well due to the type system
 */
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
