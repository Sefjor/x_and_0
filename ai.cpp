#include "ai.h"

Ai::Ai()
{

}

void Ai::input(int A[], int turn)
{
 unsigned int x = 1;
 unsigned int result = 0;
 for(int i = 0; i<10; ++i)
   {
     result += A[i] * x;
     x *= 10;
   }
 stack.push_back({result, static_cast<unsigned int>(turn)});//fail safe here as turn is derived from boolean
 qDebug() << result;
}

void Ai::gameOver(Stage st)
{
//
}

