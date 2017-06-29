//Vladimir Ventura-- I didn't put this section in until part 2
//Part 3: Multiply and Power
//Date Last Modified: 12/10/2013
//Class: CS435
//Notes: The fact that I wasn't deleting nodes in insertwAdd when two terms were opposites
//e.g. -10xy +10xy needs to cancel out was fixed.
//

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <algorithm>//used for Step 2, max

using namespace std;


int polyNum;
bool doesRowExist[100]; //I don't think we will have more than a 10th order poly
bool doesColExist[100];//if we do, then I need to make this more dynamic.

struct node
{
    node *rowLink;//same row, different columns.
    node *colLink;//same column, different rows.
    int coefficient;
    int row, col;
    ~node()
    {
           delete rowLink; delete colLink;
    }

};

struct Polynomial
{
    node **rowHeader, **colHeader;//array of nodes (head)
    int maxRow, maxCol;//rowHeader[maxRow] does not exist; maxRow-1 is actually
    //the highest x-order value. same for maxCol-1 being the highest y-order value



    /*~Polynomial()//destructor
    {
    /* delete all the stoofs!
       int count=0;
       while (count<maxRow)
       {
             delete rowHeader[count];
       }
       count=0;
       while(count<maxCol)
       {
             delete colHeader[count];
       }
       delete rowHeader; delete colHeader;
    }*/
};
//////////////////////////
//      prototypes      //
//////////////////////////

void initialize(Polynomial &p, int m, int n);
void input(Polynomial &p);
void insertTerm(Polynomial &p, int coeff, int rowIndex, int colIndex);
void output(Polynomial p);
void resetBoolExists(int m, int n);
void Part1(Polynomial &P, Polynomial &Q, Polynomial &R, Polynomial &S, Polynomial &T);
void evaluate(Polynomial p);
void evaluates(Polynomial p, int x, int y);
void Part2and3(Polynomial P, Polynomial Q, Polynomial R, Polynomial S, Polynomial T);
void inputwAdd(Polynomial &A, Polynomial toAdd);
void insertAdd(Polynomial &p, int coeff, int rowIndex, int colIndex);
void inputwSub(Polynomial &A, Polynomial toSub);
void insertSub(Polynomial &P, int coeff, int rowIndex, int colIndex);
void part3(Polynomial A, Polynomial B, Polynomial C, Polynomial D, Polynomial E, Polynomial F, Polynomial P, Polynomial Q, Polynomial R, Polynomial S);
Polynomial multiply(Polynomial P, Polynomial Q);
Polynomial power(Polynomial P, int k);
//end prototypes


int main()
{
    Polynomial A,B,D,E,F,P,Q,R,S,T;

    Part1(P,Q,R,S,T);
	cout<<"Step 1 is complete; the following is Step2:\n";//just to divide it up.
	Part2and3(P,Q,R,S,T);//combined into the same step because I need to use A,B,D,E,F.
    cout<<"program is done!\n";


  return 0;
}
////////////////////
// Part 1 Methods //
////////////////////
void Part1(Polynomial &P, Polynomial &Q, Polynomial &R, Polynomial &S, Polynomial &T)
{
    int m=5, n=5;//values 0-4 is 5 rows and columns

    resetBoolExists(m+1,n+1);

    polyNum=1;
    initialize(P,m,n);
    input(P);
    cout<<"P = ";
    output(P);
    evaluate(P);

    resetBoolExists(m, n+2);
    polyNum=2;
    initialize(Q,m-1,n+1);//maxrow here is 4 (0-3, 3 is the highest order X)
    input(Q);
    cout<<"Q = ";
    output(Q);
    evaluate(Q);


    resetBoolExists(5,3);
    polyNum=3;
    initialize(R,4,2);
    input(R);
    cout<<"R = ";
    output(R);
    evaluate(R);

    resetBoolExists(3,7);
    polyNum=4;
    initialize(S,2,6);
    input(S);
    cout<<"S = ";
    output(S);
    evaluate(S);



    resetBoolExists(10,10);//the max it can hold.
    polyNum=5;
    initialize(T,m,n);
    input(T);
    cout<<"Your own polynomial, \"T\" = ";
    output(T);
    evaluate(T);
}








void resetBoolExists(int row, int col)
{
     //code lifted
}


void initialize(Polynomial &p, int m, int n)
{
    p.rowHeader= new node*[m];//m is rows
    p.colHeader= new node*[n];//n is columns
    int a=0;
    while(a<m)
    {
        p.rowHeader[a]=NULL;//need to initialize these values, as they have been causing a sigsegv
        a++;
    }
    a=0;

    while(a<n)
    {
        p.colHeader[a]=NULL;
        a++;
    }
    p.maxRow=m;
    p.maxCol=n;

//    p.rowHeader[0].coefficient=1;//used for debugging purposes.
}

void input(Polynomial &p)
{
   //code lifted
}

void insertTerm(Polynomial &p, int coeff, int rowIndex, int colIndex)
{
    //cout<<rowIndex<<" inside insertTerm\n";//for debugging
    if (coeff==0)
    {
        cout<<"coefficient was zero, triple not added\n";//debugging
        return;
    }
    if (rowIndex>(p.maxRow) || colIndex>(p.maxCol) || rowIndex<0 || colIndex<0)
    {
        //cout<<"out of bounds\n";//debugging
        return;
    }

    node *colPtr = p.colHeader[colIndex];
    node *rowPtr = p.rowHeader[rowIndex];
    //cout<<"ptrs initialized and maxCol is: "<<p.maxCol<<"\n";//so far maxCol works as suspected

////////////////////////////////////////////
//														//
//			Header Link Creation					//
//														//
////////////////////////////////////////////


////////////////////
//		colPtrs		//
////////////////////
    //code lifted
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//For each individual insertTerm, their perspective headers have been created and attached to their respective col/row indeces.//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//traverse into the linked list ("outside" of headers) if it exists

	//cout<<"headers initialized for input\n";
   colPtr=colPtr->colLink;
   rowPtr=rowPtr->rowLink;//move to the first node (first case, it will be the header)

   while(colPtr->colLink->row > rowIndex && colPtr->colLink != p.colHeader[colIndex])
   {//we are on the column array; move along the cols (up the rows.. rows decrement) until we reach the intended row number, hence row>rowIndex,
       //and as long as the next node isn't equal to the header... which it will in the first instance.
   	colPtr=colPtr->colLink;//since we check for colPtr->colLink->row,
   }//we end up on the spot right BEFORE the intended value, perfect for inserting a node

   while(rowPtr->rowLink->col > colIndex && rowPtr->rowLink != p.rowHeader[rowIndex])
   {//similar deal to the colptr; you travel along the rows (down the columns, columns decrement)
       rowPtr=rowPtr->rowLink;
   }


//insert the node into the linked list
//    node *newnode=new node();
//    newnode->coefficient=coeff;
//	   newnode->row=rowIndex;
//	   newnode->col=colIndex;
//cout<<"for the triple: ("<<coeff<< ", "<<rowIndex<<", "<<colIndex<<") we are at: ("<<colPtr->coefficient<<", "<<colPtr->row<< ", "<<rowPtr->col<<")\n";
    if(rowPtr->rowLink->col==colIndex)//taken from Part 2
    {//we were to travel right before the intended node. What if the node with the value right row exists?
        rowPtr->rowLink->coefficient=coeff;
        cout<<"a node has been replaced\n"; //we replace in insertTerm, not add or subtract like Part 2.
    }
    else if(colPtr->colLink->row==rowIndex)
    {
        colPtr->colLink->coefficient=coeff;
        cout<<"node has been replaced\n";
    }
    else
    {
        //code lifted
    }
//the below I used as an alternative [to see if it worked better]...
		/*node *tempPtr=colPtr->colLink;
		colPtr->colLink=new node();//colPtr->colLink is pointing to newnode.
		colPtr->colLink->colLink=tempPtr; // (newnode)->colLink=tempPtr [remember newnode is now instead colPtr->colLink) because
														 //we were behind, and new node is inserted between colPtr and colPtr->colLink
		colPtr->colLink->rowLink=rowPtr->rowLink;//newnode->rowLink points to the rowPtr->rowLink, so as to be inserted between rowPtr and rowPtr->rowLink

		rowPtr->rowLink=colPtr->colLink;//now rowPtr will point to the (newnode), known as colPtr->colLink.

		colPtr->colLink->coefficient=coeff;
		colPtr->colLink->row=rowIndex;
		colPtr->colLink->col=colIndex;*/


    //cout<<"node inserted\n";


//	 if(rowPtr == p.rowHeader[rowIndex])//so it wass coming back that it's not... because I malloc'ed rowPtr and colPtr instead of polynomial's header explicitly.
//	cout<<p.rowHeader[rowIndex]->rowLink->row<<" row\n"<<colPtr->colLink->col<<" col\n"<<rowPtr->rowLink->coefficient<<" coefficient\n"<<rowIndex<<" rowIndex\n";
//    return;


}


void output(Polynomial p)
{

    /*cout<<"Outputting...";
    node *rowPtr=p.rowHeader[p.maxRow-1]; //4 does not seem to work. hrm.
    rowPtr=rowPtr->rowLink;
    cout<<rowPtr->coefficient<<"\n";
	 rowPtr=p.rowHeader[3];
	 rowPtr=rowPtr->rowLink;
	 cout<<rowPtr->coefficient<<"\n";
	 rowPtr=p.rowHeader[1];
	 rowPtr=rowPtr->rowLink;
	 cout<<rowPtr->coefficient<<"\n";
     rowPtr=p.rowHeader[0];
     rowPtr=rowPtr->rowLink;
     cout<<rowPtr->coefficient<<"\n";*/
    int temprow=p.maxRow-1;
    while(doesRowExist[temprow]==false)//look for the highest order X poly
    {
        temprow--;
        if(temprow<0)
        {
            cout<<"there are no terms to output\n"; return;
        }
    }

    int minrow=0;
    while(doesRowExist[minrow]==false)
    {
        minrow++;//this won'tt run if there are 0 terms, because of return above
    }

    //cout<<"highest Order X is: "<<temprow<<" and lowest is: "<<minrow<<"\n";

    node *rowPtr=p.rowHeader[temprow]; //start with highest x

    rowPtr=rowPtr->rowLink;//get out of header, theoretically this is the highest y value
    while(rowPtr->row>minrow)//if it's equal to minrow, we need to evaluate it.
    {//>minrow-1 doesn't work because if minrow is zero, after zero is p.maxCol, causing an endless loop.


        while(rowPtr->col!=-1)//made changes for readability's sake. changed in Part 2.
        {
           if(rowPtr->coefficient==1)
           {
                if(rowPtr->col==0)//its not at minrow, row can't be zero, but col can
                     cout<<"x"<<rowPtr->row<<" + ";
                else
                     cout<<"x"<<rowPtr->row<<"y"<<rowPtr->col<<" + ";

           }
           else if(rowPtr->coefficient==-1)
           {
                 if(rowPtr->col==0)//its not at minrow, row can't be zero, but col can
                      cout<<" -x"<<rowPtr->row<<" + ";
                 else
                      cout<<" -x"<<rowPtr->row<<"y"<<rowPtr->col<<" + ";
           }
           else
           {
               if(rowPtr->col==0)//its not at minrow, row can't be zero, but col can
                    cout<<rowPtr->coefficient<<"x"<<rowPtr->row<<" + ";
               else
                    cout<<rowPtr->coefficient<<"x"<<rowPtr->row<<"y"<<rowPtr->col<<" + ";
           }
           rowPtr=rowPtr->rowLink;

        }
        //cout<<"Row done";
        rowPtr=rowPtr->colLink;
        rowPtr=rowPtr->rowLink;
    }

    //cout<<"all rows but minrow are done";
    while(rowPtr->col!=-1)//evaluate at minrow.
    {
     //minrow is either 0, or above 0, so here is where we use if statement.
        if(rowPtr->coefficient!=1 && rowPtr->coefficient!=-1)
        {

            if(rowPtr->row==0 && rowPtr->col==0)
                 cout<<rowPtr->coefficient;
            else if(rowPtr->row==0)//implies col failed
                 cout<<rowPtr->coefficient<<"y"<<rowPtr->col;
            else if(rowPtr->col==0) //implies row isn't zero
                 cout<<rowPtr->coefficient<<"x"<<rowPtr->row;
            else
                 cout<<rowPtr->coefficient<<"x"<<rowPtr->row<<"y"<<rowPtr->col;
        }
        else if(rowPtr->coefficient ==-1)
        {
            if(rowPtr->row==0 && rowPtr->col==0) //no choice
                 cout<<rowPtr->coefficient;
            else if(rowPtr->row==0)//implies col failed
                 cout<<" -y"<<rowPtr->col;
            else if(rowPtr->col==0) //implies row isn't zero
                 cout<<" -x"<<rowPtr->row;
            else
                 cout<<" -x"<<rowPtr->row<<"y"<<rowPtr->col;
        }
        else//it is 1
        {

            if(rowPtr->row==0 && rowPtr->col==0)
                 cout<<rowPtr->coefficient;
            else if(rowPtr->row==0)//implies col failed
                 cout<<"y"<<rowPtr->col;
            else if(rowPtr->col==0) //implies row isn't zero
                 cout<<"x"<<rowPtr->row;
            else
                 cout<<"x"<<rowPtr->row<<"y"<<rowPtr->col;
        }
        rowPtr=rowPtr->rowLink;
        if(rowPtr->col!=-1)
             cout<<" + ";//if it's the last term, we dont want a + at the end
    }
    cout<<"\n"; //the poly is done, next one!
}

void evaluate(Polynomial p)//general case, gives allll the values
{
    evaluates(p,3,8); evaluates(p,3,0); evaluates(p,0,2); evaluates(p,2,2);
    evaluates(p,10,6);

}


void evaluates(Polynomial p, int x, int y)
{
    int result=0;
    cout<<"Given values: ("<<x<<","<<y<<") this polynomial's value is: ";


    //same type of algorithm as the output, except we don't need to worry about
    //maxrow, just minrow. evaluate minrow and circle around until u reach it again.

    int minrow=0;
    while(doesRowExist[minrow]==false)
    {
        minrow++;
        if(minrow>p.maxRow)
        {
            cout<<"woops, no terms to evaluate\n"; return;
        }
    }

    node *rowPtr=p.rowHeader[minrow]; //start with lowest x

    //code lifted
    cout<<result<<"\n";
}







/////////////////////////////////////
//end Part 1, start Part 2 (and 3) //
/////////////////////////////////////

void Part2and3(Polynomial P, Polynomial Q, Polynomial R, Polynomial S, Polynomial T)
{
	Polynomial A,B,C,D,E,F;//A=P+Q, B=P-Q, C=R+S, D=P-S, E=S-P, F=Q+R



	A.maxRow= max(P.maxRow, Q.maxRow);//set max or maxRow and maxCol into
	A.maxCol= max(P.maxCol, Q.maxCol);//A
	resetBoolExists(A.maxRow+1,A.maxCol+1);
    initialize(A,A.maxRow, A.maxCol);
	//cout<<"init\n";
    inputwAdd(A,P);//put P into A, if any col/rows exist, instead of replacing it, add them together.
	//cout<<"P added\n";
	inputwAdd(A,Q); //this way, when we put Q into A, the common terms' coefficients are added!
    cout<<"A = ";
    output(A);

    //B=P-Q
    B.maxRow=max(P.maxRow, Q.maxRow);
    B.maxCol=max(P.maxCol, Q.maxCol);
    resetBoolExists(B.maxRow+1, B.maxCol+1);
    initialize(B, B.maxRow, B.maxCol);
    inputwAdd(B,P);//we "add" P to B first.
    inputwSub(B,Q);//then we sub Q FROM B (B=P, so B-Q =same-as= P-Q)
    cout<<"B = ";
    output(B);


    //C=R+S
    C.maxRow=max(R.maxRow, S.maxRow);
    C.maxCol=max(R.maxCol, S.maxCol);
    resetBoolExists(C.maxRow+1, C.maxCol+1);
    initialize(C, C.maxRow, C.maxCol);
    inputwAdd(C,R);
    inputwAdd(C,S);
    cout<<"C = ";
    output(C);

    //D=P-S
    D.maxRow=max(P.maxRow,S.maxRow);
    D.maxCol=max(P.maxCol,S.maxCol);
    resetBoolExists(D.maxRow+1, D.maxCol+1);
    initialize(D, D.maxRow, D.maxCol);
    inputwAdd(D,P);
    inputwSub(D,S);
    cout<<"D = ";
    output(D);



    //E=S-P
    E.maxRow=max(P.maxRow,S.maxRow);
    E.maxCol=max(P.maxCol,S.maxCol);
    resetBoolExists(E.maxRow+1, E.maxCol+1);
    initialize(E, E.maxRow, E.maxCol);
    inputwAdd(E,S);//we "add" S to E first.
    inputwSub(E,P);//we subtract P from E, which is the same as S; S-P.
    cout<<"E = ";
    output(E);


    //F=Q+R, phew last one of part2!
    F.maxRow=max(Q.maxRow,R.maxRow);
    F.maxCol=max(Q.maxCol,R.maxCol);
    resetBoolExists(F.maxRow+1, F.maxCol+1);
    initialize(F, F.maxRow, F.maxCol);
    inputwAdd(F,Q);
    inputwAdd(F,R);
    cout<<"F = ";
    output(F);


	cout<<"end of part 2, starting Part 3\n";
	part3(A,B,C,D,E,F,P,Q,R,S);
	delete A.rowHeader; delete A.colHeader; //delete components here (except C, which is no longer used).
    delete B.rowHeader; delete B.colHeader;
    delete C.rowHeader; delete C.colHeader;
	delete D.rowHeader; delete D.colHeader;
	delete E.rowHeader; delete E.colHeader;
	delete F.rowHeader; delete F.colHeader;
}

void inputwAdd(Polynomial &A, Polynomial toAdd)//similar algorithm to input(poly p) except here, we traverse the entire poly toAdd
{//and add everything in term by term.
//It's worth noting, that although it says &A up there, the Part2()'s Polynomial A is NOT necessarily this one.
//A here is a local variable that I'm deciding to keep after testing with the first case.
	//if(polyNum==1)//A = P+Q//polyNum not needed, as this applies to every inputwAdd
	//{
		//code lifted
		}

	//}

}

void insertAdd(Polynomial &p, int coeff, int rowIndex, int colIndex)//here is where we insert each term, and if we find common terms, add coefficients
{//instead of replacing the previous one.
    //cout<<"inserting triple: " <<coeff<< " "<< rowIndex<< " "<< colIndex<< "\n";
    if (coeff==0)//shouldn't happen, but eh.
        return;
    if (rowIndex>(p.maxRow) || colIndex>(p.maxCol) || rowIndex<0 || colIndex<0)//again shouldn't happen considering the polynomials have already been made.
        return;

    node *colPtr = p.colHeader[colIndex];
    node *rowPtr = p.rowHeader[rowIndex];

////////////////////////////////////////////
//			Header Link Creation		  //
////////////////////////////////////////////


//code lifted

//////////////////////////////////////////////////////////////////
//For each individual insertAdd, their perspective headers have //
//been created and attached to their respective col/row indeces.//
//////////////////////////////////////////////////////////////////


//traverse into the linked list ("outside" of headers) if it exists

	//cout<<"headers initialized for input\n";
   colPtr=colPtr->colLink;
   rowPtr=rowPtr->rowLink;//move to the first node (first case, it will be the header)



   while(colPtr->colLink->row > rowIndex && colPtr->colLink != p.colHeader[colIndex])
   {
   	colPtr=colPtr->colLink;//change rows, goingdown 1,
   }//we end up on the spot right BEFORE the intended value, perfect for inserting a node, or adding coefficients

   while(rowPtr->rowLink->col > colIndex && rowPtr->rowLink != p.rowHeader[rowIndex])
   {//similar deal to the colptr; you travel along the rows (down the columns, columns decrement)
       rowPtr=rowPtr->rowLink;
   }



   //the first 4 of these if's/else if's are to add the terms if we are either on or right "behind" the term we're looking for
    if(rowPtr->rowLink->col==colIndex && colPtr->colLink->row==rowIndex)//both must be true. we are right before the term.
    {//we were to travel right before the intended node. What if the node with the value right row exists?
        rowPtr->rowLink->coefficient+=coeff;
        if (rowPtr->rowLink->coefficient==0) //oh boy, this number is zero, so it needs to be deleted. colPtr and rowPtr alike.
        {
            node *tempPtr=rowPtr->rowLink;
            rowPtr->rowLink=rowPtr->rowLink->rowLink;//delete this node if it's zero.
            colPtr->colLink=colPtr->colLink->colLink;
            tempPtr->rowLink=NULL;
            tempPtr->colLink=NULL;
            delete(tempPtr);
            //cout<<"Row deleted, coeff =0\n";//yay it works in each of the 4 conditions.
        }
    //    cout<<"a node has been added\n"; //add.
    }
    else if(colPtr->row==rowIndex && rowPtr->col==colIndex)//we are at the term instead
    {
        colPtr->coefficient+=coeff;
        if (colPtr->coefficient==0)
        {
            node *tempColPtr=p.colHeader[colIndex];
            while(tempColPtr->colLink!=colPtr)//we want the node before rowPtr
                tempColPtr=tempColPtr->colLink;
            //assume tempColPtr is before colPtr.
            tempColPtr->colLink=colPtr->colLink;//colPtr has no colLinks pointing to it.
            
            node *tempRowPtr=p.rowHeader[rowIndex];
            while(tempRowPtr->rowLink!=rowPtr)//we want the node before rowPtr
                tempRowPtr=tempRowPtr->rowLink;
            //assume tempRowPtr is before rowPtr.
            tempRowPtr->rowLink=rowPtr->rowLink;//newnode is inserted between rowPtr and its prev node.
            rowPtr->rowLink=NULL; rowPtr->colLink=NULL; colPtr->colLink=NULL; colPtr->rowLink=NULL;
            delete(rowPtr);
            //delete(colPtr);
        }
 
    }
    else if(colPtr->row==rowIndex)//yes one, not the other, will happen in the first and maximum poly secnarios.
    {
         colPtr->coefficient+=coeff;
         if(colPtr->coefficient==0)
         {
             node *tempColPtr=p.colHeader[colIndex];
             while(tempColPtr->colLink!=colPtr)//we want the node before colPtr
                tempColPtr=tempColPtr->colLink;
             tempColPtr->colLink=colPtr->colLink; //colPtr has no colLinks pointint to it.
             //however, it has a rowPtr pointing to it....
             node *tempRowPtr=p.rowHeader[rowIndex]; //the colPtr is at said row.
             while(tempRowPtr->rowLink!=colPtr)
                 tempRowPtr=tempRowPtr->rowLink;
             tempRowPtr->rowLink=colPtr->rowLink;
             //now colPtr has nothing pointing to it.
             colPtr->colLink=NULL;
             colPtr->rowLink=NULL;
             delete(colPtr);
         }
    }
    else if(rowPtr->col==colIndex)
    {
         rowPtr->coefficient+=coeff;
         if(rowPtr->coefficient==0)
         {
             node *tempRowPtr=p.rowHeader[rowIndex];
             while(tempRowPtr->rowLink!=rowPtr)
                 tempRowPtr=tempRowPtr->rowLink;
             tempRowPtr->rowLink = rowPtr->rowLink;
             //rowPtr has no rowLink pointing to it. it has a colLink pointing to it though.
             node *tempColPtr=p.colHeader[colIndex]; //if col is equal to colIndex, then we are at said column.
             while(tempColPtr->colLink!=rowPtr)
                 tempColPtr=tempColPtr->colLink;
             tempColPtr->colLink=rowPtr->colLink;
             //now rowPtr has nothing pointing to it.
             rowPtr->colLink=NULL; rowPtr->rowLink=NULL;
             delete(rowPtr);
         }
    }//*/
    else
    {
        if(colPtr->row<rowIndex && rowPtr->col<colIndex)
        {
            node *newnode = new node();
            newnode->colLink= colPtr;
            //what was before colPtr? let's find out
            node *tempColPtr=p.colHeader[colIndex];
            while(tempColPtr->colLink!=colPtr)//we want the node before rowPtr
                tempColPtr=tempColPtr->colLink;
            //assume tempColPtr is before colPtr.
            tempColPtr->colLink=newnode;//newnode is inserted between rowPtr and its prev node.
            //now rowPtr
            newnode->rowLink= rowPtr;
            //what was before rowPtr? let's find out
            node *tempRowPtr=p.rowHeader[rowIndex];
            while(tempRowPtr->rowLink!=rowPtr)//we want the node before rowPtr
                tempRowPtr=tempRowPtr->rowLink;
            //assume tempRowPtr is before rowPtr.
            tempRowPtr->rowLink=newnode;//newnode is inserted between rowPtr and its prev node.

            newnode->row=rowIndex;
            newnode->col=colIndex;
            newnode->coefficient=coeff;
        }
        else if(colPtr->row <rowIndex)//just one, not the other.
        {
            node *newnode = new node();
            newnode->rowLink= rowPtr->rowLink;
            rowPtr->rowLink=newnode;
            //now to pt to colPtr

            newnode->colLink= colPtr;
            //what was before colPtr? let's find out
            node *tempColPtr=p.colHeader[colIndex];
            while(tempColPtr->colLink!=colPtr)//we want the node before rowPtr
                tempColPtr=tempColPtr->colLink;
            //assume tempColPtr is before colPtr.
            tempColPtr->colLink=newnode;//newnode is inserted between rowPtr and its prev node.
            newnode->row=rowIndex;
            newnode->col=colIndex;
            newnode->coefficient=coeff;
        }
        else if(rowPtr->col < colIndex)//I updated this for Part1 as well
        {//we want to insert before our current rowPtr.

            node *newnode = new node();
            newnode->colLink= colPtr->colLink;
            colPtr->colLink=newnode;
            //now to pt to rowPTr

            newnode->rowLink= rowPtr;
            //what was before rowPtr? let's find out
            node *tempRowPtr=p.rowHeader[rowIndex];
            while(tempRowPtr->rowLink!=rowPtr)//we want the node before rowPtr
                tempRowPtr=tempRowPtr->rowLink;
            //assume tempRowPtr is before rowPtr.
            tempRowPtr->rowLink=newnode;//newnode is inserted between rowPtr and its prev node.
            newnode->row=rowIndex;
            newnode->col=colIndex;
            newnode->coefficient=coeff;
        }
        else
    	{
            node *newnode = new node();
            newnode->colLink= colPtr->colLink;
            colPtr->colLink=newnode;
            newnode->rowLink= rowPtr->rowLink;
            rowPtr->rowLink=newnode;
            newnode->row=rowIndex;
            newnode->col=colIndex;
            newnode->coefficient=coeff;
        }
    }
}

void inputwSub(Polynomial &B, Polynomial toSub)//similar algorithm to inputwAdd..
{//except we call insertSub.
//It's worth noting, that although it says &B up there, the Part2()'s Polynomial B is NOT necessarily this one.
//(view same note as A in inputwAdd).
	node *rowPtr=toSub.rowHeader[toSub.maxRow-1];
	rowPtr=rowPtr->rowLink; //outside of header;
	//cout<<"row is: "<<rowPtr->row<<"\n";
	while (rowPtr->col!=-1)//compute at maxRow
	{
		insertSub(B, rowPtr->coefficient, rowPtr->row, rowPtr->col);
		rowPtr=rowPtr->rowLink;
	}
	rowPtr=rowPtr->colLink;
	rowPtr=rowPtr->rowLink;//get out of header.

	while(rowPtr->row!=toSub.maxRow-1)//compute all aside from maxRow
	{
		while(rowPtr->col!=-1)//col shouldnt be -1 because we just got outside of the header
		{
			insertSub(B, rowPtr->coefficient, rowPtr->row, rowPtr->col);
			rowPtr=rowPtr->rowLink;
		}
		rowPtr=rowPtr->colLink;//switch rows.
		rowPtr=rowPtr->rowLink;//get out of header;
	}



}

void insertSub(Polynomial &p, int coeff, int rowIndex, int colIndex)
{//similar to insertAdd or insert -- we subtract common col/row's, and insert
//negative terms.
    //cout<<"inserting triple: " <<coeff<< " "<< rowIndex<< " "<< colIndex<< "\n";
    if (coeff==0)//shouldn't happen, but eh.
        return;
    if (rowIndex>(p.maxRow) || colIndex>(p.maxCol) || rowIndex<0 || colIndex<0)//again shouldn't happen considering the polynomials have already been made.
        return;

    node *colPtr = p.colHeader[colIndex];
    node *rowPtr = p.rowHeader[rowIndex];

////////////////////////////////////////////
//			Header Link Creation		  //
////////////////////////////////////////////


//////////////////////
//		colPtrs		//
//////////////////////
    if(colPtr == NULL || doesColExist[colIndex]!=true)
    {
		p.colHeader[colIndex]=new node();//somehow maxCol is set to zero when the new node is malloced..
        if(p.colHeader[colIndex]==NULL)
            cout<<"malloc failed at colIndex: "<<colIndex<<"\n";
		colPtr=p.colHeader[colIndex];
        colPtr->col=colIndex;
        colPtr->row=-1;
        colPtr->colLink=p.colHeader[colIndex];//circular linked list


        doesColExist[colIndex]=true;//added this because the NULL wasn't always coming through.

  	    int tempcol=colIndex-1;//we want to point to the nearest previous colLink.

		if(tempcol<0)
		{
		    tempcol=p.maxCol-1;
		}
		while(doesColExist[tempcol]==false)//
        {
            tempcol--;
            if(tempcol<0)
                tempcol=p.maxCol-1;
        }

        colPtr->rowLink=p.colHeader[tempcol];

        //we know this vallue of tempcol is true, so go backwards
        tempcol=colIndex+1; //now to find the nearest "next" colLink which is to point to colIndex.
		  if(tempcol>p.maxCol-1)
		     tempcol=0;
		//now work backwards to find the rowPtr who needs to pt to this one.
        while(doesColExist[tempcol]==false)
        {
            tempcol++;
            if(tempcol>p.maxCol-1)
                tempcol=0;
        }
        p.colHeader[tempcol]->rowLink=colPtr;
        //cout<<colPtr->col<<"colIndex col added\n";
        tempcol=0;
    }

////////////////////
//		rowPtrs		//
////////////////////
    if(rowPtr == NULL || doesRowExist[rowIndex]!=true)
    {//if the node hasn't been started..
        p.rowHeader[rowIndex]=new node();//allocate memory to this not-started node
        rowPtr=p.rowHeader[rowIndex];
        rowPtr->row=rowIndex;
        rowPtr->col=-1;
        rowPtr->rowLink=p.rowHeader[rowIndex];//circular linked list
        doesRowExist[rowIndex]=true; //useful for colLink purposes, below.
        //this is in order to insert a valid colLink.
        int temprow=rowIndex-1;//if we use rowIndex, it will of course be made/true, we just did it..
        if(temprow<0)
            temprow=p.maxRow-1;//so we go finding the first one for colLink to point to
        while(doesRowExist[temprow]==false)
        {
            temprow--;
            if(temprow<0)
                temprow=p.maxRow-1;
        }
        rowPtr->colLink=p.rowHeader[temprow];

        temprow=rowIndex+1; //now for the position that will POINT to rowIndex
        if(temprow>p.maxRow-1)
		      temprow=0;
		//working backwards to find the rowPtr who needs to pt to this rowIndex...
        while(doesRowExist[temprow]==false)
        {
            temprow++;
            if(temprow>p.maxRow-1)
                temprow=0;
        }
        p.rowHeader[temprow]->colLink=rowPtr;
        //cout<<rowPtr->row<<"RowIndex row added\n";
        temprow=0;
	}


//traverse into the linked list ("outside" of headers) if it exists

	//cout<<"headers initialized for input\n";
   colPtr=colPtr->colLink;
   rowPtr=rowPtr->rowLink;//move to the first node (first case, it will be the header)



   while(colPtr->colLink->row > rowIndex && colPtr->colLink != p.colHeader[colIndex])
   {
   	colPtr=colPtr->colLink;//change rows, goingdown 1,
   }//we end up on the spot right BEFORE the intended value, perfect for inserting a node, or adding coefficients

   while(rowPtr->rowLink->col > colIndex && rowPtr->rowLink != p.rowHeader[rowIndex])
   {//similar deal to the colptr; you travel along the rows (down the columns, columns decrement)
       rowPtr=rowPtr->rowLink;
   }



    //cout<<"for the triple: ("<<coeff<< ", "<<rowIndex<<", "<<colIndex<<") we are at: ("<<colPtr->coefficient<<", "<<colPtr->row<< ", "<<rowPtr->col<<")\n";
    if(rowPtr->col < colIndex)//I updated this for Part1 as well
    {//we want to insert before our current rowPtr.

        node *newnode = new node();
        newnode->colLink= colPtr->colLink;
        colPtr->colLink=newnode;
        //now to pt to rowPTr

        newnode->rowLink= rowPtr;
        //what was before rowPtr? let's find out
        node *tempRowPtr=p.rowHeader[rowIndex];
        while(tempRowPtr->rowLink!=rowPtr)//we want the node before rowPtr
            tempRowPtr=tempRowPtr->rowLink;
        //assume tempRowPtr is before rowPtr.
        tempRowPtr->rowLink=newnode;//newnode is inserted between rowPtr and its prev node.
        newnode->row=rowIndex;
        newnode->col=colIndex;
        newnode->coefficient=-1*coeff;
    }
    else if(colPtr->colLink->row==rowIndex)
    {
        colPtr->colLink->coefficient-=coeff;
        if (colPtr->colLink->coefficient==0)
        {
            node *tempPtr=colPtr->colLink;
            colPtr->colLink=colPtr->colLink->colLink;//delete this node if it's zero.
            rowPtr->rowLink=rowPtr->rowLink->rowLink;
            tempPtr->rowLink=NULL;
            tempPtr->colLink=NULL;
            delete(tempPtr);
        }

    }
    else if(rowPtr->rowLink->col==colIndex)
    {//we were to travel right before the intended node. What if the node with the value right row exists?
        rowPtr->rowLink->coefficient-=coeff;
        if (rowPtr->rowLink->coefficient==0)
        {
            node *tempPtr=rowPtr->rowLink;
            rowPtr->rowLink=rowPtr->rowLink->rowLink;//delete this node if it's zero.
            colPtr->colLink=colPtr->colLink->colLink;
            tempPtr->rowLink=NULL;
            tempPtr->colLink=NULL;
            delete(tempPtr);
        }
        //cout<<"a node has been subtracted\n"; //coefficient = coefficient-coeff.
    }/*

    else if(colPtr->row==rowIndex && colPtr->colLink ==colPtr )
    {//what if, when we went to the first link off header, it was automatically
    //lower than row (while loop immediately ends)?
        colPtr->coefficient+=coeff;
        cout<<"current colNode added";
    }
    else if(rowPtr->col==colIndex && rowPtr->rowLink==rowPtr)
    {
         rowPtr->coefficient+=coeff;
         cout<<"current rowNode added";
    }*/ //not sure if the above is needed anymore
    else
	{
        node *newnode = new node();
        newnode->colLink= colPtr->colLink;
        colPtr->colLink=newnode;
        newnode->rowLink= rowPtr->rowLink;
        rowPtr->rowLink=newnode;
        newnode->row=rowIndex;
        newnode->col=colIndex;
        newnode->coefficient=-1*coeff;
    }
}



///////////////////////////////////////////
//                END                    //
//                PART                   //
//                TWO                    //
///////////////////////////////////////////




void part3(Polynomial A, Polynomial B, Polynomial C, Polynomial D, Polynomial E,
Polynomial F, Polynomial P, Polynomial Q, Polynomial R, Polynomial S)
{
	Polynomial G,H,I,J,K,L;
    cout<<endl<<endl;
	//G=P*Q, so the maxCol is 1 higher than the sum of the two highest cols (P.maxCol-1 + Q.maxCol-1)
    G=multiply(P,Q);
    cout<<"G = ";
    output(G); cout<<endl;

    H=multiply(R,S);    cout<<"H = "; output(H); cout<<endl;
    I=multiply(A,B);    cout<<"I = "; output(I); cout<<endl;
    J=multiply(E,F);    cout<<"J = "; output(J); cout<<endl;
    K=multiply(D,E);    cout<<"K = "; output(K); cout<<endl;
    L=multiply(I,K);    cout<<"L = "; output(L); cout<<endl;

    //delete(A.rowHeader); delete(A.colHeader);
    //delete(B.rowHeader); delete(B.colHeader);
	A=power(P,5);
	
	cout<<"A = ";
	output(A); cout<<endl;
	
	
	B=power(Q,3);	cout<<"B = ";  output(B); cout<<endl;
	C=power(R,7);   cout<<"C = ";  output(C); cout<<endl;
	D=power(S,2);   cout<<"D = ";  output(D); cout<<endl;
	E=power(P,2);   cout<<"E = ";  output(E); cout<<endl;
	F=power(Q,5);   cout<<"F = ";  output(F); cout<<endl;
	



}

Polynomial multiply(Polynomial P, Polynomial Q)
{
	Polynomial product;
	product.maxCol=P.maxCol+Q.maxCol-1;//as explained before, it's minus 1 because -2+1=-1.
	product.maxRow=P.maxRow+Q.maxRow-1;
	resetBoolExists(product.maxRow+1, product.maxCol+1);
	initialize(product, product.maxRow, product.maxCol);


	node *pRowPtr=P.rowHeader[P.maxRow-1]; pRowPtr=pRowPtr->rowLink;
	node *qRowPtr=Q.rowHeader[Q.maxRow-1]; qRowPtr=qRowPtr->rowLink;

	while(pRowPtr->col!=-1)
	{
		while(qRowPtr->col!=-1)//do the max row of Q
		{
			insertAdd(product, pRowPtr->coefficient*qRowPtr->coefficient, pRowPtr->row + qRowPtr->row, pRowPtr->col + qRowPtr->col);
			qRowPtr= qRowPtr->rowLink;
		}
		qRowPtr=qRowPtr->colLink;
		qRowPtr=qRowPtr->rowLink;
		while(qRowPtr->row!=Q.maxRow-1)//now the rest of Q.
		{
			while(qRowPtr->col!=-1)
			{
				insertAdd(product, pRowPtr->coefficient*qRowPtr->coefficient, pRowPtr->row + qRowPtr->row, pRowPtr->col + qRowPtr->col);//any common terms should be added together.
				qRowPtr=qRowPtr->rowLink;
			}
			qRowPtr=qRowPtr->colLink;
			qRowPtr=qRowPtr->rowLink;
		}

		pRowPtr=pRowPtr->rowLink;//no change in columns because we are only doing the max row of P.
	}
	//here we do the rest of P.
	pRowPtr=pRowPtr->colLink;
	pRowPtr=pRowPtr->rowLink;

	while(pRowPtr->row!=P.maxRow-1)
	{
		while(pRowPtr->col!=-1)
		{
			while(qRowPtr->col!=-1)//do the max row of Q again, for each term of P
			{
				insertAdd(product, pRowPtr->coefficient*qRowPtr->coefficient, pRowPtr->row + qRowPtr->row, pRowPtr->col + qRowPtr->col);
				qRowPtr= qRowPtr->rowLink;
			}
			qRowPtr=qRowPtr->colLink;
			qRowPtr=qRowPtr->rowLink;
			while(qRowPtr->row!=Q.maxRow-1)//now the rest of Q.
			{
				while(qRowPtr->col!=-1)
				{
					insertAdd(product, pRowPtr->coefficient*qRowPtr->coefficient, pRowPtr->row + qRowPtr->row, pRowPtr->col + qRowPtr->col);
					qRowPtr=qRowPtr->rowLink;
				}
				qRowPtr=qRowPtr->colLink;
				qRowPtr=qRowPtr->rowLink;
			}

			pRowPtr=pRowPtr->rowLink;
		}
		pRowPtr=pRowPtr->colLink;
		pRowPtr=pRowPtr->rowLink;
	}

	return product;
}

Polynomial power(Polynomial A, int k)
{

//To explain the logic below, and how it gives at MOST 2log(n) multiplications:
//I turn the exponent, k, into a binary representation. e.g. A^7 = A^4*A^2*A^1, or 111.
//I get A, requires zero multiplications
//A^2, requires one multiplication.
//A^4, requires one multiplication (A^2^2).
//A*A^2*A^4 are two more multiplications. A total of 4 multiplications.
//by turning an exponent into a multiplication of binary numbers,
//I reduce the number of multiplications between A*A^2*A^4*A^8 etc.. to log(n).
//I also reduce the multiplications of each A to logn (to get A, 0 mult, to get A^2m 1 mult, A^4 requires 2 mult total, etc..).
//this makes for log(n)+log(n)= 2log(n). yay, at most 2log(n).

	Polynomial product;
	product.maxCol=(A.maxCol-1)*k+1;//as explained before, maxCol is the number of columns,  so the highest value is maxCol-1
	product.maxRow=(A.maxRow-1)*k+1;//times k because it is an exponent raised to a power
	//see log rules: (A^(maxCol-1))^k --> log((maxCol-1)^k) = k*log(maxCol-1). add 1 because we want the number of rows/cols
	resetBoolExists(product.maxRow+1, product.maxCol+1);
	initialize(product, product.maxRow, product.maxCol);
	//cout<<"maxRow is: "<< product.maxRow<<" and maxCol is: "<<product.maxCol<<endl;

    if(k==0)//A^0 =1. that's it.
    {
        insertTerm(product,1,0,0);
        return product;
    }
    if(k<0) //not part of the requirements, but always good to include an if for this.
    {
        //not sure what to do with this. I'll leave it blank for now.. or rather I'll just return
        cout<<"I am incapable of doing this with my current skillset. Please try again in a few years...\n";
        //a tad bit of a lie, but I don't think factoring denominators is what we're supposed to do here. =/
        return product;
    }




	int arraysize=0, ktemp=k;

	while(ktemp!=0)
	{
		arraysize++;
		ktemp=ktemp/2;
	}
	int *binaryArray= new int[arraysize];
	Polynomial arrayP[arraysize];

    for(int i=0; i<arraysize; i++)
    {
        binaryArray[i]=0;//initialize all values.
        arrayP[i]=A;
    }
    
	ktemp=k; int index=0;//time to fill in the binaryArray values now.

	while(ktemp!=0)//I don't need an additional index<arraysize, because ktemp will stop when index reaches arraysize simply by the fact
	{//that arraysize was defined that way.
		binaryArray[index]=ktemp%2;
		ktemp=ktemp/2;
		index++;
	}

	index=0;

	while(index<arraysize)
	{
		if(index==0)
			arrayP[index]=A;//0th term is always the array itself (A^(2^0)) = A
		else
			arrayP[index]=multiply(arrayP[index-1],arrayP[index-1]); //here I find A^2, or A^2^2 aka A^4, and A^8, etc..
		index++;
	}
	
	
	
	//cout<<"A = "; output(arrayP[1]);//0th and 1st term both work. the problem isn't arrayP.

	index=0;
	bool isEmpty = 1;//product is empty.
    //cout<<"arrayP filled\n"; //it's after here that something goes wrong.

	while(index<arraysize)
	{
        //cout<<"inside while loop\t";
        if(binaryArray[index]==1)
        {   
            if(isEmpty==1)//1 is true 0 is false :o..
            {
                //cout<<"first term was input";
                //inputwAdd(product, arrayP[index]); //for some reason, I cannot use an element of the array?
                //this is something that gave me so much trouble for the past week
                //this is the workaround I've decided on. eh. meh.
                product=arrayP[index];
                isEmpty=0;

            }
            else
            {
                product=multiply(product, arrayP[index]); //now, multiply the first poly to the second
                //cout<<"a term was multiplied";

            }

        }
		//do nothing if binaryArray[index] is 0.
		index++;
	}

	//cout<<"product done\n";

    //output(product);
	return product;
}
