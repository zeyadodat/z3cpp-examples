#include<z3++.h>
#include <stdio.h>

using namespace z3;

void prove(expr conjecture) {
    context & c = conjecture.ctx();
    solver s(c);
    s.add(!conjecture);
    std::cout << "conjecture:\n" << conjecture << "\n";
    if (s.check() == unsat) {
        std::cout << "proved" << "\n";
    }
    else {
        std::cout << "failed to prove" << "\n";
        std::cout << "counterexample:\n" << s.get_model() << "\n";
    }
}
void bitvector_example1() {
    context c;
    expr x = c.bv_const("x", 32);
    
    // using signed <=
    prove((x - 10 <= 0) == (x <= 10));

    // using unsigned <=
    prove(ule(x - 10, 0) == ule(x, 10));

    expr y = c.bv_const("y", 32);
    prove(implies(concat(x, y) == concat(y, x), x == y));
}
void bitvector_example2() {
    context c;
    expr x = c.bv_const("x", 32);
    expr y = c.bv_const("y", 32);
    solver s(c);
    // In C++, the operator == has higher precedence than ^.
    s.add((x ^ y) - 103 == x * y);
    std::cout << s << "\n";
    std::cout << s.check() << "\n";
    std::cout << s.get_model() << "\n";
}
void capi_example() {
    std::cout << "capi example\n";
    context c;
    expr x = c.bv_const("x", 32);
    expr y = c.bv_const("y", 32);
    // Invoking a C API function, and wrapping the result using an expr object.
    expr r = to_expr(c, Z3_mk_bvsrem(c, x, y));
    std::cout << "r: " << r << "\n";
}
void eval_example1() {
    std::cout << "eval example 1\n";
    context c;
    expr x = c.int_const("x");
    expr y = c.int_const("y");
    solver s(c);

    /* assert x < y */
    s.add(x < y);
    /* assert x > 2 */
    s.add(x > 2);
    
    std::cout << s.check() << "\n";
    
    model m = s.get_model();
    std::cout << "Model:\n" << m << "\n";
    std::cout << "x+y = " << m.eval(x+y) << "\n";
}
void numeral_example() {
    std::cout << "numeral example\n";
    context c;
    
    expr n1 = c.real_val("1/2");
    expr n2 = c.real_val("0.5");
    expr n3 = c.real_val(1, 2);
    std::cout << n1 << " " << n2 << " " << n3 << "\n";
    prove(n1 == n2 && n1 == n3);
    
    n1 = c.real_val("-1/3");
    n2 = c.real_val("-0.3333333333333333333333333333333333");
    std::cout << n1 << " " << n2 << "\n";
    prove(n1 != n2);
}
void zeyad_example() {
    std::cout << "zeyad example\n";
    context c;
    
    expr n1 = c.real_val("2");
    expr n2 = c.real_val("20");
    std::cout << n1 << " " << n2 <<"\n";
    prove(n1!=n2);
    
    n1 = c.real_val("0.54");
    n2 = c.real_val("-0.333333");
    std::cout << n1 << " " << n2 << "\n";
    prove(n1 != n2);
}
int main(){

// STEP-0 init
std::cout << "bitvector example 1\n";
bitvector_example1();
std::cout<<"\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
std::cout << "bitvector example 2\n";
bitvector_example2();
std::cout<<"\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
capi_example();
std::cout<<"\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
eval_example1();
std::cout<<"\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
numeral_example();
std::cout<<"\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
zeyad_example();
 return 0;
}
