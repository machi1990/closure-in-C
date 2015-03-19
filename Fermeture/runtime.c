#include "runtime.h"


void MLunit_print(void* val ) {
        printf("()");
}

void MLbool_print(MLvalue *value) {
	if(value == NULL) 
          return;
          
	if(value->kind_ == boolean)
		if (value->value.asBoolean == true) 		
		  	printf("true");
		else
			printf("false");
}

void MLint_print(MLvalue *value) {
	if(value == NULL) 
          return;        
	if (value->kind_ == integer)
            printf("%d", value->value.asInt);
}


void MLdouble_print(MLvalue *v) {	
	if(v == NULL) 
          return;        
	if(v->kind_ == real)
        printf("%f", v->value.asDouble);
        
}

void MLstring_print(MLvalue *chaine) {
        if(chaine == NULL) 
          return; 
        if(chaine->kind_ == stringz)
          printf("%s", chaine->value.asString);
}

MLvalue* get_tail (MLvalue* invoker,MLvalue* liste) {
	 if (liste != NULL){
    		if (liste->kind_ != list )
			return NULL;
    		MLlist* temp = liste->value.asList; 
		  return temp->next;
	 }
	 else
		  return NULL; 
}


/* To be changed*/

 MLvalue* access_value (MLvalue* invoker, MLvalue* liste) {	
	 if(liste !=NULL) {
		   if (liste->kind_ != list )
			return NULL;
		   MLlist* temp = liste->value.asList; 
    		   return temp->head;
	  }  
	 return NULL;
  }

void print_list (MLvalue *listes) {
	  if (listes == NULL )
    	  	return;
  	 else {
		 if(listes->kind_ != list)
		     return; 
       
		 MLlist* liste = listes->value.asList;	
		  MLvalue* value = liste->head;
  
		  if (value == NULL) {
			 printf("[]"); 
			  return;
		   }
     
		 value->print (value);
		 printf (" : ");
		 if (liste->next != NULL)
		 (liste->next)->print (liste->next);
	 }
} 

/* To be changed */
MLlist* initialize_list (MLvalue* val, MLvalue* next) {
  	if (next!=NULL)
	 { 
		  if(next->kind_ == list)
		{
		  // Type control over here; Lists contain only member of the same type
        		  MLvalue* header = next->value.asList->head;
        		 if(header !=NULL && val != NULL)
        			  if (header->kind_ != val->kind_ )
				  return NULL;
          	}
		 else {
			printf (" List contain elements of same type");
			return NULL;
        }
      }
  	MLlist* list = (MLlist*)malloc (sizeof(MLlist));
	 list->head = val; 
	 list->next = next;
	 return list;
}

MLvalue* get_first (MLvalue* invoker, MLvalue *paire ) {
 	if(paire==NULL)
		  return NULL;
 	if (paire->kind_ != pair)
		 return NULL;
 	else
		  return paire->value.asPair->first; 
 }

MLvalue* get_second (MLvalue* invoker , MLvalue *paire ) {
	 if(paire==NULL)
		 return NULL;
 	if (paire->kind_ != pair)
    		return NULL;
	 else
		 return paire->value.asPair->second; 
 }

void print_pair (MLvalue *paire ) {
  	if(paire == NULL)
		 return;
	 else 
	  {
		if (paire->kind_ != pair)
			  return;		
      		printf ("(");
      
      		MLvalue* premier=  paire->value.asPair->first;
      		premier->print(premier);
      		printf (" , ");
		MLvalue* deuxieme =  paire->value.asPair->second;
		deuxieme->print (deuxieme);
      		printf (" )");  
 	}
}


MLpair* initilize_pair (MLvalue* value1, MLvalue* value2 ) {
	MLpair* pair = (MLpair*) malloc (sizeof(MLpair));
  	pair->first = value1;
  	pair->second= value2;
	return pair;
 }

void addenv (MLfun *fun, MLvalue* envi, MLvalue *a) {
	int i = 0;
	if ( fun == NULL)
 		return;

	for (; i < fun->MLcounter; i++) {
    		fun->env[i]= envi[i];
	 }
	 fun->env[i] = *a;
	 fun->MLcounter +=1;
}  

void print_fun (MLvalue* funct) {
	 if (funct == NULL)
		   return;
	 else if (funct->kind_ != function)
		   return;
	 MLfun* fun = funct->value.asFun;     
	 if (fun== NULL)
		  return;
	  printf("<fun> [");
  	  int i = 0;
  	  MLvalue*  envs = fun->env;
  	  MLvalue* environ;
	  for (; i < fun->MLcounter; i++ ) {
    		environ =&envs[i];
    		environ->print ( environ);
  		}
  	printf ("]");
}
 
MLfun* initialise_fun () {
  	MLfun  *fun = (MLfun*)malloc (sizeof (MLfun));
  	fun->MLcounter =0;
  	fun->MLaddenv = &addenv;
  	return fun;
}

MLfun* initialize_fun (int n) {
	 MLfun * fun = initialise_fun();
	 MLvalue* values= (MLvalue*) malloc (n * sizeof ( MLvalue));
	 fun->env= values;
	 return fun; 
 }

MLvalue* new_unit (){
	 MLvalue* v= (MLvalue*)malloc(sizeof(MLvalue));
	 v->kind_ = unit;
	 v->value.asUnit = 0;
	 v->print = &MLunit_print;
	 return v;
}

MLvalue* new_bool (bool val) {
  	MLvalue* v= (MLvalue*)malloc(sizeof(MLvalue));
  	v->kind_ = boolean;
	v->value.asBoolean = val;
  	v->print = &MLbool_print;
  	return v;
 }

MLvalue* new_int (int val) {
  	MLvalue* v= (MLvalue*)malloc(sizeof(MLvalue));
  	v->kind_ = integer;
  	v->value.asInt = val;
  	v->print = &MLint_print;
  	return v;
}

MLvalue* new_double ( double val ) {
  	MLvalue* v= (MLvalue*)malloc(sizeof(MLvalue));
  	v->kind_ = real;
  	v->value.asDouble = val;
	v->print = &MLdouble_print;
  	return v;
}

MLvalue* new_string (char *chaine) {
  	MLvalue* v= (MLvalue*)malloc(sizeof(MLvalue));
  	v->kind_ = stringz;
  	v->value.asString = chaine;
  	v->print = &MLstring_print;
  	return v;
 }

MLvalue* new_pair (MLvalue* v0 , MLvalue* v1)  {
	MLpair *couple =initilize_pair (v0,v1);
  	MLvalue* v= (MLvalue*)malloc(sizeof(MLvalue));
  	v->kind_ = pair;
  	v->value.asPair = couple;
  	v->print = &print_pair;
  	return v;
 }

MLvalue* new_list (MLvalue* v0, MLvalue* v1)  {
  	MLlist* liste = initialize_list (v0,v1);
  	MLvalue* v= (MLvalue*)malloc(sizeof(MLvalue));
	v->kind_ = list;
  	v->value.asPair = liste;
  	v->print = &print_list;
  	return v;
 }

MLvalue * MLaddInt (MLvalue * gauche, MLvalue* droite) {
  MLvalue* result=NULL;
  if(gauche!=NULL && droite!= NULL)
    {
      int g = gauche->value.asInt;
      int d = droite->value.asInt;
      result = new_int( d+g);
     }
  return result;
 }
 

MLvalue * MLsubInt (MLvalue * gauche, MLvalue* droite) {
  MLvalue* result=NULL;
  if(gauche!=NULL && droite!=NULL)
    {
      int g = gauche->value.asInt;
      int d = droite->value.asInt;
      result = new_int( g-d);
     }
  return result;
 }


MLvalue * MLmultInt (MLvalue * gauche, MLvalue* droite) {
  MLvalue* result=NULL;
  if(gauche!=NULL && droite!= NULL)
    {
      int g = gauche->value.asInt;
      int d = droite->value.asInt;
      result = new_int( d*g);
     }
  return result;
 }


MLvalue * MLdivInt (MLvalue * gauche, MLvalue* droite) {
  MLvalue* result=NULL;
  if(gauche!=NULL && droite!= NULL)
    {
      int g = gauche->value.asInt;
      int d = droite->value.asInt;
      result = new_int( g / d);  // Division by zero not treated yet
     }
  return result;
 }


int checkSimilarity(MLvalue* gauche, MLvalue* droite)
{
	int i,j,k; 
	MLvalue *t1,*t2,*t3,*t4;
	MLkind kind1,kind2,kind3,kind4;
	if (gauche == NULL && droite != NULL)
		return 0;
        else if (gauche!=NULL && droite ==NULL )
		return 0;
        else if (gauche == NULL && droite == NULL )
		return 1;
        else
	switch(gauche->kind_)
	{
		case unit:
			return gauche->value.asUnit == droite->value.asUnit;
		
		case integer:
			return gauche->value.asInt == droite->value.asInt;
		
		case real:
			return gauche->value.asDouble == droite->value.asDouble;
		
		case stringz: 
			i = strcmp (gauche->value.asString,droite->value.asString);
			return i==0;
		
		case boolean:
			return gauche->value.asBoolean == droite->value.asBoolean;
		
		case pair:		
                        t1= gauche->value.asPair->first;
			t2 = droite->value.asPair->first;
                        t3 = gauche->value.asPair->second;
			t4 = droite->value.asPair->second;

                        kind1 = t1->kind_;
			kind2 = t2->kind_;
                        kind3 = t3->kind_;
			kind4 = t4->kind_;

                        if(kind1!=kind2 || kind3!=kind4)
				return 0;
                        else 
			 return checkSimilarity (t1,t2)* checkSimilarity(t3,t4);	
		
		case list:		
                        t1= gauche->value.asList->head;
			t2 = droite->value.asList->head;
                        t3 = gauche->value.asList->next;
			t4 = gauche->value.asList->next;
			return checkSimilarity(t1,t2)*checkSimilarity(t3,t4); // TODO
		
		case function:
			return gauche->value.asFun == droite->value.asFun;  // TODO
		
	}
}


MLvalue* MLequals (MLvalue* gauche, MLvalue* droite) {
  int same;
  if (gauche != NULL && droite != NULL){
    if(gauche->kind_ != droite->kind_)
       return MLfalse;
    else
      same = checkSimilarity(gauche, droite);
	if(same)
		return MLtrue;
	return MLfalse;
  }
  else 
   return NULL;
 }

MLvalue* MLconcat (MLvalue* gauche , MLvalue* droite) {
  char* first_string=NULL;
  char* second_string=NULL; 
  if(gauche!=NULL)
    first_string = gauche->value.asString;
  if (droite !=NULL)
    second_string = droite->value.asString;
  
  if ( first_string != NULL ) {	
  	char * result = (char*)malloc(strlen(first_string)+ strlen(second_string)+1);	
	 memcpy ( result, first_string, strlen(first_string)+1 );
	return new_string (strcat(result, second_string));
	}
else
  return droite;
}

MLvalue* MLltint (MLvalue* gauche, MLvalue * droite ){
  if (gauche!=NULL && droite!=NULL) 
    {
      int g= gauche->value.asInt;
      int d = droite-> value.asInt;
      if(g<d)
	return MLtrue;
      return MLfalse;
    } 
  else
    return NULL;
 }
MLvalue* MLletint  (MLvalue* gauche, MLvalue * droite ){
  if (gauche!=NULL && droite!=NULL) 
    {
      int g= gauche->value.asInt;
      int d = droite->value.asInt;
      if(g<=d)
	return MLtrue;
      return MLfalse;
    } 
  else
    return NULL;
 }

MLvalue* MLgtint  (MLvalue* gauche, MLvalue * droite ){
  if (gauche!=NULL && droite!=NULL) 
    {
      int g= gauche->value.asInt;
      int d = droite-> value.asInt;
      if(g>d)
	return MLtrue;
      return MLfalse;
    } 
  else
    return NULL;
 }
MLvalue* MLgeint  (MLvalue* gauche, MLvalue * droite ){
  if (gauche!=NULL && droite!=NULL) 
    {
      int g= gauche->value.asInt;
      int d = droite->value.asInt;
      if(g>=d)
	return MLtrue;
      return MLfalse;
    } 
  else
    return NULL;
 }

MLvalue* MLprint(MLvalue* x)
{
	x->print(x);
	printf("\n");	
	return new_unit();
}

MLvalue* initialise_head () {
  MLvalue *v = (MLvalue*)malloc(sizeof (MLvalue));
  v->kind_ = function; 
  MLfun* prim = initialise_fun();
  prim->invoke = &access_value;
  v->value.asFun = prim;
  v->print = &print_fun;	
  return v; 
}

MLvalue* initialise_tail () {
  MLvalue *v = (MLvalue*)malloc(sizeof (MLvalue));
  v->kind_ = function;  
  MLfun* prim = initialise_fun(); 
  prim->invoke = &get_tail;
  v->value.asFun = prim;
  v->print = &print_fun;	
  return v; 
}

MLvalue* initialise_first () {
  MLvalue *v = (MLvalue*)malloc(sizeof (MLvalue));
  v->kind_ = function; 
  MLfun* prim = initialise_fun();
  prim->invoke = &get_tail;
  v->value.asFun = prim;
  v->print = &print_fun;	
  return v; 
}

MLvalue* initialise_second () {
  MLvalue *v = (MLvalue*)malloc(sizeof (MLvalue));
  v->kind_ = function; 
  MLfun* prim = initialise_fun();
  prim->invoke = &get_tail;
  v->value.asFun = prim;
  v->print = &print_fun;	
  return v; 
}

