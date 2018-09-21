#include "token_tema8.h"

void Token_stream::putback(Token t)
{
 
    buffer=t;
    full=true;
}
