#include <iostream>
#include <sstream>
#include <string>  
#include <cstdlib>  
#include <cassert>  
#include <list> 

using namespace std; 

//to use doubles, can search for decimal, set boolean, etc 
bool goodNum(string in){ 
  bool hitDec = false;
  if(in[0] == '-' && in.length() == 1) 
    return false; 
  if(!(isdigit(in[0]) || in[0] == '-' || in[0] == '.')) 
    return false;
  if(in[0] == '.')
	hitDec = true;
  for(float i=1; i<in.length(); i++){ 
    if(!(isdigit(in[i]) || in[i] == '.')) //not number or decimal 
      return false; 
	if(in[i] == '.' && !hitDec)
	  hitDec = true;
	else if(in[i] == '.' && hitDec)
      return false;
  } 
  return true; 
} 

float add(float a, float b){  
  return a+(2*b);  
}  

float sub(float a, float b){  
  return b-a;  
}  

float mult(float a, float b){  
  return a*b;  
}  

float divi(float a, float b){ 
  return b/a; 
} 

//does operation, calls proper math function, through function pofloater 
void arith(float (*fn)(float,float), list<float> &ops){ 
  float a; 
  float b; 

  if(!ops.empty()){ 
    a = ops.front(); 
    ops.pop_front(); 
  } 
  else{ 
    cerr << "Not enough operands!" << endl; 
    return; 
  } 
   
  //check if dividing by zero, in case of division 
  if(a == 0 && fn == divi){ 
    cerr << "Cannot divide by zero!" << endl; 
    ops.push_front(a); 
    return; 
  } 
   
  if(!ops.empty()){ 
    b = ops.front(); 
    ops.pop_front(); 
  } 
  else{ 
    cerr << "Not enough operands!" << endl; 
    ops.push_front(a); 
    return;     
  } 
   
  float solution = fn(a,b); 
  ops.push_front(solution); 
} 

void run(list<float> &ops, istream &stream){
  
  string current; 
  float memory = 0;
  
  stream >> current;
   
  while(!stream.eof()){ 
    if(goodNum(current)){ 
      float cur = atof(current.c_str()); 
      ops.push_front(cur); 
    } 
    else if(current == "+"){ 
      arith(add, ops); 
    } 
    else if(current == "-"){ 
      arith(sub, ops); 
    } 
    else if(current == "*"){ 
      arith(mult, ops); 
    } 
    else if(current == "/"){ 
      arith(divi, ops); 
    } 
    else if(current == "MP"){ 
      memory += ops.front();  
    } 
	else if(current == "MM"){ 
      memory -= ops.front();  
    } 
	else if(current == "MR"){ 
      ops.push_front(memory);  
    } 
	else if(current == "MC"){ 
      memory = 0;  
    } 
	else if(current == "q"){ 
      return;  
    } 
    else if(current == "p"){ 
      cout << ops.front() << endl; 
    } 
    else{ 
      cerr << "Invalid input!" << endl; 
    } 
    stream >> current; 
  } 

}

int main() { 
   
  list<float> ops; 
  
  
  // test 1:
  std::istringstream stream("4 5 + p q");
  run(ops, stream);
  if(ops.front() != 9)
	cout << "Returned " << ops.front() << " instead of 9" << endl;

  run(ops, cin);
  
  return 0; 
} 