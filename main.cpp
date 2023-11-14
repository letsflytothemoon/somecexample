#include "somec/somec.h"

struct BlackBody : std::ostream
{
    BlackBody& operator <<(std::ostream&(*)(std::ostream&)) { return *this; }
    template <class T> BlackBody& operator <<(T) { return *this; }
};


struct COpts
{
    static const int BITS    = 16;
    static const int REGS    = 2;
    static const int RAMSIZE = 512;
    
    static const char* regname(int index)
    {
        static const char* names[] = {"a", "b", "c", "d"};
        return names[index];
    }
    
    static std::ostream& GetBlackBody()
    {
        static BlackBody value;
        return value;
    }
    
    static std::ostream& asm_ostr()
    { return std::cout; }
    
    static std::ostream& code_ostr()
    { return GetBlackBody(); }
    
    static std::ostream& verilog_ostr()
    { return GetBlackBody(); }
};

typedef SomeC<COpts>   C;
typedef C::StackStrat  Stack;
typedef C::StaticStrat Static;

template <class T>
using Ref = C::Ref<T>;

template <class T = Stack>
using Var = C::Var<T>;

int main()
{
    Var<Stack> i = 10;
    Ref<Var<Stack>> ref = i;
    
    ref = 27;
    
    return 0;
}