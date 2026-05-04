#include "muParser.h"

double MyFunction(double a_fVal) {
    return a_fVal * a_fVal;
}

int main() {
    using namespace mu;
    try {
        double fVal = 7;
        Parser p;
        p.DefineVar("x", &fVal);
        p.SetExpr("sin(x^2)+5");
        std::cout << p.Eval() << std::endl;
    } catch (Parser::exception_type& e) {
        std::cout << e.GetMsg() << std::endl;
    }
    return 0;
}