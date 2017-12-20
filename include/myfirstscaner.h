#ifndef MYFIRSTSCANER_H
#define MYFIRSTSCANER_H

#include "../include/abstract_scaner.h"
#include "../include/error_count.h"
#include "../include/location.h"
#include <string>"

enum codes : unsigned short {
    None,              Unknown,              Int,                
    Float,             False,                Char,               
    String,            Void,                 If,                 
    Const,             ElseIf,               Else,               
    EndIf,             For,                  While,              
    Repeat,            Until,                Exit,               
    Continue,          Return,               Read,               
    Print,             Kw_Int,               Kw_float,           
    Kw_bool,           Kw_char,              Kw_string,          
    Kw_void,           Var,                  Kw_array,           
    Proto,             Func,                 Equal,              
    Plus,              Minus,                Multiplication,     
    Division,          Module,               LessThan,           
    MoreThan,          LessOrEqual,          MoreOrEqual,        
    Unequal,           FractDiv,             LogicalOr,          
    LogicarNor,        LogicalNot,           LogicalAnd,         
    LogicalNAnd,       LXor,                 LNXor,              
    BitXor,            BitOr,                BNXor,              
    BNor,              BitAnd,               BinaryAnd,          
    BitLeftShift,      BirRightShift,        FractPow,           
    Openif_block,      endif_block,          Open_round,         
    Close_round,       Dim_size,             Cond_op,            
    Semicolon,         Comma,                after_label,        
    Open_square,       Close_square,         Colon,              
    ColonAssign,       PlusColonAssign,      MinusColonAssign,   
    MultColonAssign,   SlashColonAssign,     SlashDotColonAssign,
    TwoMultColonAssign,TwoMultDotColonAssign,PercColonAssign,    
    AmpColonAssign,    TilAmpColonAssign,    LShiftColAssign,    
    RShiftColAssign,   PipColAssign,         TilPipColAssign,    
    CirColAssign,      TilCirColAssign,      TwoPipColAssign,    
    NTwoPipColAssign,  TwoCirColAssign,      NTwoCirColAssign,   
    TwoColAssign,      NTwoColAssign,        True,               
    TilCir,            AddBinNu,             AddToDegr
};

struct Lexem_info{
    codes code;
    union{
        size_t    ident_index;
unsigned __int128 int_val; __float128 float_val;
    };
};

class myfirstscaner : public Abstract_scaner<Lexem_info> {
public:
    myfirstscaner() = default;
    myfirstscaner(Location* location, const Errors_and_tries& et) :
        Abstract_scaner<Lexem_info>(location, et) {};
    myfirstscaner(const myfirstscaner& orig) = default;
    virtual ~myfirstscaner() = default;
    virtual Lexem_info current_lexem();
private:
    enum Automaton_name{
        A_start,     A_unknown, A_idKeyword, 
        A_delimiter, A_number
    };
    Automaton_name automaton; /* current automaton */

   typedef bool (myfirstscaner::*Automaton_proc)();
    /* This is the type of pointer to the member function that implements the
     * automaton that processes the lexeme. This function must return true if
     * the lexeme is not yet parsed, and false otherwise. */

    typedef void (myfirstscaner::*Final_proc)();
    /* And this is the type of the pointer to the member function that performs
     * the necessary actions in the event of an unexpected end of the lexeme. */

    static Automaton_proc procs[];
    static Final_proc     finals[];

    /* Lexeme processing functions: */
    bool start_proc();     bool unknown_proc();   
    bool idkeyword_proc(); bool delimiter_proc(); 
    bool number_proc();
    /* functions for performing actions in case of an
     * unexpected end of the token */
    void none_proc();            void unknown_final_proc();   
    void idkeyword_final_proc(); void delimiter_final_proc(); 
    void number_final_proc();
};
#endif
