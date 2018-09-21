// This is example code from Chapter 7.2 "Input and output" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

//
  // This is example code from Chapter 7.2 "Input and output" of
  // "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
  //
  /*
	  
	  Declaration:
		  "let" Name "=" Expression
          Statement :
                  Declaration <- 
                  Expression <- fet
                  Print <- fet
                  pow <- fet
                  let -> # <- fet
                  Quit <- fet
                  surt <- fet
    
          Print : <- fet
                  ;
          Quit:
                  q <- fet
                  Quit <- fet
                  surt <- fet;
          Expression :
                  Term
                  Expression + Term
                  Expression - Term
          Term :
                  Primary
                  Term * Primary
                  Term / Primary
                  Term % Primary <- fet
                  Term ! Primary <- falta
                  
                  
          Primary :
                  Number
                  ( Expression ) 
                  - Primary
                  + Primary
                  sqrt Primary <- fet
          Number :
                  Floating-point-literal
  -------------------------------------------------------------
  -> Input comes from cin through the Token_stream alled td <-
  -------------------------------------------------------------
  pagina 239<- 7.7 Recovering from errors.w
  */

#include "std_lib_facilities.h"

//------------------------------------------------------------------------------
#include "token_tema8.h"

//------------------------------------------------------------------------------

//int debug = 1; //debu
int debug = 0; //NO debug
const char number='8';
const char print=';';
const char result='=';
const string prompt ="--/|> ";
//const string result = "= ";

const char name='a';

const char suma='+';

const char resta='-';

const char multiplica='*';

const char divisio='/';

const char fact='!';

const char modul='%';

const char let='l';                 //define var
const string declkey="let";
const string declquadrat="#";

const char arrel='r';               //sqrt
const string declarrel="Sqrt";

const char ajuda='h';               //help
const string ajuda_interrogant="?";
const string ajuda_mayus="Help";


const char quit='q';                //quit
const string paraula_quit="Quit";
const string paraula_surt="Surt";



const char constant='c';            //define constants
const string paraula_const="const";

const char potencia='P';            //power
const string declpotencia="pow";


//------------------------------------------------------------------------------
class Variable {
public:
  string name;
  double value;
  char constant;
  Variable(string nm, double val, char constantono)//, char cons) //inicialitzo la variable
  :name(nm), value(val), constant(constantono) {}
  Variable();
  char get_constant();
};
char Variable::get_constant()
{
  return(this->constant); //myself!!!
}
Variable::Variable()
{

}

//------------------------------------------------------------------------------

class Symbol_table: public Variable{
public:
  Variable var_table_st;
Symbol_table(string nm, double val, char constantono);
  //Symbol_table(string nm, double val, char constantono);
  //Symbol_table();
  
  
};
Symbol_table::Symbol_table(string nm, double val, char constantono): Variable(nm, val, constantono)
{

}
//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
:full(false), buffer(0)    // no Token in buffer
{
}
//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback()>

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full) { 
		error("putback() into a full buffer");
		
		}
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

void Token_stream::ignore(char c) //c representa el tipus de token
{
  if(full && c== buffer.kind){ //mirem el buffer primer
    full=false;
    return;
  }
  full=false; //no ple el buffer;
  
  char ch=0;
  while(cin>>ch) 
    if(ch==c) return;
}

//------------------------------------------------------------------------------
//llegeix text 
//Es formen els tokens aqui
Token Token_stream::get()
{
    if (full) {       // do we already have a Token ready?
        // remove token from buffer
        full=false;
        return buffer;
    }

    char ch;
    cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
	/*case arrel:
	    return Token{ch};*/
	case print:    // for "print"
	//case quit:    // for "quit"
    
	case result:
	case '(': 
	case ')': 
    case suma://'+': 
    case resta://'-': 
    case multiplica: //'*': 
    case divisio://'/':
    case modul://'%': 
    case fact://'!': //recullo tokens especials
	//case 'L': //MAL POSADA!! ERROR!!!! token let, carregar variables(statement?=
    case potencia://'p': //tokenwuit pow(statement?)
    case ',': //coma de pow
    case ajuda://'?':
    //case '#':
	    return Token(ch);        // let each character represent itself
    /*
    case '\n': //per return no retorno el valor, pk ?? s'ha de mirar i arreglar!!
        {
		cin.putback(ch);         // put digit back into the input stream
		double val;
		cin >> val;  	            // read a floating-point number
		if(debug==1)cout << " val = " << val << endl;
		return Token(number,val);   // let '8' represent "a number"
	    }
	*/
	    //#####################################################################################################################
	    //recullo tokens de números
	case '.':
	case '0': 
	case '1': 
	case '2': 
	case '3': 
	case '4':
	case '5': 
	case '6': 
	case '7': 
	case '8': 
	case '9':
	    {
		cin.putback(ch);         // put digit back into the input stream
		double val;
		cin >> val;  	            // read a floating-point number
		if(debug==1)cout << " val = " << val << endl;
		return Token(number,val);   // let '8' represent "a number"
	    }	
	default:
	    if(isalpha(ch) || (ch=='#')){
	      string s;
	      s += ch;
	      while(cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch=='_' || ch=='?')) s+=ch;
	      cin.putback(ch);
	      
	      if(s == declkey) return Token{let}; //declaration keyboard
	      if(s == declquadrat) return Token{let}; //declarationit keyboard
	      if(debug==1)cout << endl<< " s = " << s << endl;
	      if(s==declarrel) return Token{arrel}; //sqrt
          
	      if(s==ajuda_mayus) return Token{ajuda}; //help
          if(s==ajuda_interrogant) return Token{ajuda};//help
          
	      if(s==paraula_quit) return Token{quit}; //quit
	      if(s==paraula_surt) return Token{quit}; //quit
          
	      if(s==paraula_const){
		if(debug==1)cout << "Paraula constant trobada" << endl;
		return Token{constant};
	      }
	      if(s==declpotencia){
              if(debug==1)cout << "Paraula pow trobada" << endl;
              return Token{potencia};
          }         
	      //if(s == declI || s == declV || s == declX || s == declL || s == declC || s == declD || s == declM ) return  Token{Roma};
	      
	      return Token{name,s};
	    }
	    error("Bad token");
	  
	
    }
}


//------------------------------------------------------------------------------
 
double expression();    // declaration so that primary() can call expression()s
//------------------------------------------------------------------------------
double declaration();

 
//------------------------------------------------------------------------------
double define_name(string var, double val, char c);//, char cons);
void set_value(string s, double d, char c);
//------------------------------------------------------------------------------


double declaration() //declaració de variables
{
  Token t = ts.get();
  if(t.kind != name ) error("Name expected in declaration ");
  string var_name = t.name;
  
  Token t2 = ts.get();
  if (t2.kind!='=')error("= missing in declaration of ", var_name);
  
  double d = expression();
  define_name(var_name,d,'v');//,'n');
  set_value(var_name,d,'v');
  return d;
}

double declaration_constant() //declaració de variables constants
{
  Token t = ts.get();
  if(t.kind != name ) error("Name expected in declaration ");
  string var_name = t.name;
  
  Token t2 = ts.get();
  if (t2.kind!='=')error("= missing in declaration of ", var_name);
  
  double d = expression();
  define_name(var_name,d,'c');//,'n');
  set_value(var_name,d,'c');
  return d;
}

//------------------------------------------------------------------------------
double calcul_potencia(){
            Token t1=ts.get(); // vaig endavant, he de recollir l'altre token, però com ?
            if(debug==1)cout << " t1.kind =" << t1.kind << " t1.name = " << t1.name << " t1.value = " << t1.value << endl;
            if(t1.kind!='(') {
                cout << "Malformed function" << endl;
                return (0);   
            }
            else {
                Token t2=ts.get(); // vaig endavant, he de recollir l'altre token, però com ?
                if(debug==1)cout << " t2.kind =" << t2.kind << " t2.name = " << t2.name << " t2.value = " << t2.value << endl;
            
                Token t3=ts.get(); // vaig endavant, he de recollir l'altre token, però com ? //numero base
                if(debug==1)cout << " t3.kind =" << t3.kind << " t3.name = " << t3.name << " t3.value = " << t3.value << endl;
                if(t3.kind!=',') {
                    cout << "Malformed function" << endl;
                    return (0);   
                }
                else {
                    Token t4=ts.get(); // vaig endavant, he de recollir l'altre token, però com ?
                    if(debug==1)cout << " t4.kind =" << t4.kind << " t4.name = " << t4.name << " t4.value = " << t4.value << endl;
                    int valt4=static_cast<int>(t4.value);
                
                    Token t5=ts.get(); // vaig endavant, he de recollir l'altre token, però com ?//numero exponent;
                    
                    if(debug==1)cout << " t5.kind =" << t5.kind << " t5.name = " << t5.name << " t5.value = " << t5.value << endl;
                    //Token t6=ts.get(); // vaig endavant, he de recollir l'altre token, però com ?
                    //if(debug==1)cout << " t6.kind =" << t6.kind << " t6.name = " << t6.name << " t6.value = " << t6.value << endl;
                    if(t5.kind!=')') {
                        cout << "Malformed function" << endl;
                        return (0);   
                    }
                    else {
            //Token t7=ts.get(); // ; si el recullo, falla ... comentat funciona
            //if(debug==1)cout << " t7.kind =" << t7.kind << " t7.name = " << t7.name << " t7.value = " << t7.value << endl;
                        double valor =t2.value;
                        if(debug==1)cout << " valt4 = " << valt4 << endl;
                        if(t4.value-valt4==0){
                            //for(int i=1; i<t5.value;++i) valor=t3.value*valor;
                            for(int i=1; i<valt4;++i) valor=t2.value*valor;
                            return valor;
                        }
                        else {
                            cout << "Malformed function" << endl;
                            return (0);
                        }
                    }
                }
            }
}            

double statement()
{
    Token t = ts.get();
    switch(t.kind){
      case let:
      {
        if(debug==1)cout << endl << "( statement ) let( statement ) =" << let << " declaration " << endl;
        return declaration();
      }
      case constant:
      {
        if(debug==1)cout << "Defineixo variable constant \n (statement)" << endl;
        return declaration_constant();
      }
      default:
      {
        ts.putback(t);
        return expression();
      }
      
    }
}


//------------------------------------------------------------------------------
double get_value(string s); //agafo valor de variable
//------------------------------------------------------------------------------
//Càlcul de factorial
double factorial(double numero){  
  if(numero >=2){
                if(debug==1)cout << " numero*factorial(numero-1) = " << numero*factorial(numero-1)<< endl;
                return numero=numero*factorial(numero-1);
                }

return(numero);
}



// deal with numbers and parentheses
double primary()
{
    Token t = ts.get();
    if(debug==1)cout << endl << "t.kind =" << t.kind << endl;
    switch (t.kind) { //type of token t.kind
        case potencia:
            {
                if(debug==1)cout << "p t.kind =" << t.kind << endl;
                //return calcul_potencia();
                double d=calcul_potencia();
                //return expression();
                
                if(debug==1)cout << " result d = " << d << endl;
                //left=d;
                //t = ts.get();
                //return(0);
                
                return d;
                //break;
            }
        case '(':    // handle '(' expression ')'
        {
            double d = expression();
            t = ts.get();
            if (t.kind != ')') error("')' expected");
            return d;
        }
        case 'a'://variables definides?
            return get_value(t.name); //recull valor de variable definida, ja que n'hi ha vàries
        case result:
        case number:            // we use '8' to represent a number    
            return t.value;  // return the number's value        
        case resta: //'-': //negative numbers
            return - primary();
        case suma: //'+':
            return primary();
        case arrel:
        {
            if(debug==1)cout << "calcul de l'arrel" << endl;
            double d = primary();
            //t = ts.get();( << endl;
            if(d<0) {
                cout << "Arrel no real" << endl;
                return sqrt(-d);
            }
            else return sqrt(d);      
        }
        case '?':
        case ajuda://'h':
        {
            cout << endl << "aquí ha d'anar l'ajuda de la calculadora" << endl;
            cout << endl << " per sortir, et escriu \"Quit;\" ó \"Surt;\" (sense les cometes) " << endl;
            cout << endl << " per calcular l'arrel escriu sqrt seguit de l'expressió" << endl;
            cout << endl << " per exemple sqrt 25; o sqrt(25); o sqrt(25+120-240+120);" << endl;
            cout << endl << " per guardar variables: # nom_variable=expressió" << endl;
            cout << endl << " per exemple let x=y+pow(25,3);<- FALTA ACABAR-HO D'IMPLEMENTAR, igual que totes les funcions???" << endl;
            cout << endl << "	llavors si fem let y=3" << endl;
            cout << endl << "aquí ha d'anar l'ajuda de la calculadora" << endl;
            cout << endl << "aquí ha d'anar l'ajuda de la calculadora" << endl;
            cout << endl << "aquí ha d'anar l'ajuda de la calculadora" << endl;
	
            return(0);
            break;
        }
        case quit://'q':
        {
            cout << "surt amb Quit ?" << endl;      
            break;    
        }        
    /*case 'c':
        { 
            if(debug==1)cout << "definir variables constants funcio declaration ?" << endl;
            break;
        } 
        */
        case ')':
        {
            return (0);
        }
        default:
            error("primary expected"); 
    }
}

//------------------------------------------------------------------------------

// deal with *, /, and %, !, la potencia hauria d'anar aquí ?
double term()
{
    double left = primary();
    Token t = ts.get();        // get the next token from token stream

    while(true) {
        switch (t.kind) {
            
            case multiplica://'*':
            {
                left *= primary();
                t = ts.get();
                break;
            }
            case divisio://'/':
            {
                double d = primary();
                if (d == 0) cout << /*error(*/"divide by zero";//);
                left /= d;
                t = ts.get();
                break;
            }
            case modul://'%':
            {
                int i1=narrow_cast<int>(left);
                int i2=narrow_cast<int>(primary());
                if(i2==0) error("%: divide by zero");
                left=i1%i2;
                /*double d = primary();
                if(d==0) error("%: divide by zero");
                left = fmod(left,d);	     */
                t=ts.get();
                break;
            }
            case fact://'!':
            {                                     
                left=factorial(left);
                t=ts.get();                
                break;
            }          
            default:
            {
                ts.putback(t);     // put t back into the token stream
                return left;
            }
        }
    }
}
//------------------------------------------------------------------------------
//vector<Variable> var_table;//definició de vector de variables amb funcions i accions


vector<Symbol_table> var_table_st; ///error: use of deleted function ‘Symbol_table::Symbol_table()’

//Symbol_table::Symbol_table sym_table;



double get_value(string s)
{

  for(const Variable& v:var_table_st)
    if(v.name==s)return v.value;
  error("get: Undefined variable ", s);
}
 
void set_value(string s, double d, char c) //set the Variable named s to d
{
  for (Variable& v:var_table_st)
    if(v.name == s){      
      if (v.constant!='c'){ //comprobo si és constant o no	
	v.value=d;
      }
      else {
	cout << endl << "Constant, no es pot reescriure " << endl;
      //else cout << "no modificable" << endl;
	error("no writable CONSTANT %s!!\n",s);
      }
      return;
    }
    error("set : undefined variable",s);
}

bool is_declared(string var) //is var already in var_table?
{
  for (const Variable& v:var_table_st)
    if(v.name == var) return true;
  return false;
}

//------------------------------------------------------------------------------

double define_name(string var, double val, char c) //add (var,val) to var_table
{
 /* 
  if(is_declared(var) && cons=='s') error(var, "declared twice");
  do {
    if(cons!='s') {
      cout << "És un valor constant ? (s per constant, n mutable)" << endl;
      cin >> cons;
    }
  }while(cons!='s' && cons!='n');
  var_table.push_back(Variable{var,val,cons });
  return val;
  */
 if (is_declared(var) && c=='v'){
                                //error(var," declared twice");
                                char c='1';
                                do{ 
                                  cout << "Var name already exists, do you want overwrite value ?(s,S,n,N)" ;
                                  cin >> c;
                                }while(c!='s' && c!='n' && c!='S' && c!='N');
                                if(c!='s' && c!='S'){
                                            error(var," declared twice");
                                }
                                else{
				  char valor=constant;//Variable::constant;
				  if(!is_declared(var)) var_table_st.push_back(Symbol_table(var,val,'v'));
				  else {
 				    cout << " valor = " << valor << " Constant, no es pot sobreescriure!!!" << endl;
				    exit;
				  }
                              }


          }
          else{
            if(!is_declared(var)) var_table_st.push_back(Symbol_table(var,val,'c'));
            else cout << " no es poden sobreesciure constants!!" << endl;
          }
          return val;

}


// deal with + and - 
//crida term i Token_stream.ge t
double expression()
{
    double left = term();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while(true) {
        switch(t.kind) {
        case '+':
            left += term();    // evaluate Term and add
            t = ts.get(); 
            break;
        case '-':
            left -= term();    // evaluate Term and subtract
            t = ts.get();
            break;
        default:
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}

void clean_up_mess(){ //ignorar caracters erronis
  /*while(true){
    Token t= ts.get();
    if(t.kind==print) return;
  }*/
  //es pot comentar pk tenim el metode Token_stream::ignore(char c);
  //i amb un ts.ignore(print); funciona
   ts.ignore(print); 
}




void calculate()
{
  while (cin) 
      try{
        cout << prompt;          // print prompt
	Token t = ts.get();
	while(t.kind==print) t=ts.get(); //eat ; print
	if(t.kind==quit){ //exit
	  keep_window_open();	
	  return;
	}
	ts.putback(t);
	cout << result << statement() << endl;	
      }
      catch (exception& e){
	cerr << e.what() << endl;
	clean_up_mess();
      }
}
//------------------------------------------------------------------------------

int main()

try
{   
    cout << "\n 8-pow(2,3);;=0 pow(2,3)-8;=8, pk ?!!\nrevisar variables constants(falta) i variables variables(falta)" << endl;
    //cout << "\npàgina 225 del llibre\n 9. Allow the user to use pow(x,i) to mean \"Multiply x with itself i times\"; for example, pow(2.5,3) is 2.5*2.5*2.5. Require i to be an integer using the technique we used for %.10. Change the \"declaration keyword\" from let to #.11. Change the \"quit keyword\" from quit to exit. That will involve defining a string for quit justas we did for let in §7.8.2.\n\n falta ufactorial(fet), potencia(fet), canvi paraula definicio (fet) i afegir paraula Surt(fet), afegir ? per ajuda(fet), revisar variables constants(falta) i variables variables(falta)" << endl;
    
    define_name("pi",3.1415926535,'c');
    define_name("e",2.7182818284,'c');
    
    //set_value("pi",3.1415926535,'s');
    
    //set_value("e",2.7182818284,'s');
        
    calculate();
   
    return (0);
}
catch (runtime_error& e) {
    cerr << e.what() << endl;
    //cout << "Please enter the character ~ to close the window" << endl;
    keep_window_open("~~");
    return 1;
}
catch (...) {
    cerr << "exception!\n";
    keep_window_open("~~");
    return 2;
}
