# include <iostream>
# include <conio.h>
using namespace std;
 
/* Function to swap values at two pointers */
void swap (char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
long permute(char *a, int i, int n) {
   int j; 
   static long noOfArrangement = 0;
   if (i == n){
   	noOfArrangement++;
   	cout << noOfArrangement  << "\t" << a << endl;
   }    
   else{
        for (j = i; j <= n; j++){
          swap((a+i), (a+j));
          permute(a, i+1, n);
          swap((a+i), (a+j)); //backtrack
       }
   }
   return noOfArrangement;
} 
int lengthOfCharArray(char *string){
	   short letterIndex = 0;
   short length = 0;   
   while(string[letterIndex] != '\0'){   	
   	length++;
   	letterIndex++;
   }
   return length;
}
/* Driver program to test above functions */
int main(int argc, char *argv[])
{
   cout << "Enter a sting to see all of its arrangement :";
   char letterArray[] = "";
   cin >> letterArray;
   long noOfArrangements = permute(letterArray, 0, (lengthOfCharArray(letterArray) - 1));
   cout << "Number of possible arrangement found in that string :" << noOfArrangements;
   getchar();
   return 0;
}
