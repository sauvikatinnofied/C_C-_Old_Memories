#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

// Thank You @Raju da (rajubera2@gmail.com) for your $10m idea.


int lengthOfNumber(long number){	
	int digitCount = 0;
	while(number != 0){
		digitCount++;
		number /= 10;
	}
	return digitCount;
}

void showArray(int *array, int length){
	for (int i = 0; i < length ; i++){
		cout << array[i];
	}
	cout << endl;
}
int* arrayFromArray(int *array, int length){
	int *newArray = (int*)malloc(sizeof(int) * length);
	for(int i = 0 ; i < length; i++){
		newArray[i] = array[i];
	}
	return newArray;
}

int* arrayFromNumber(long number){
	int length = lengthOfNumber(number);
	int* newArray = (int*)malloc(sizeof(int) * length);
	for(int i = length - 1; i >= 0 ; i--){
		newArray[i] = number % 10;
		number /= 10;
	}	
	return newArray;
}
int* sortArray(int *array, int length, bool accendingOrder){
	int* newArray = arrayFromArray(array, length);
	for(int i = 0; i< length; i++){
		for (int j = i+1; j< length; j++){
			if(accendingOrder){
				// Going to arrange the array in accending order
				if(newArray[j] < newArray[i]){
					int temp = newArray[j];
					newArray[j] = newArray[i];
					newArray[i] = temp;
				}
			}else{
				// Going to arrange the array in decending order
				if(newArray[j] > newArray[i]){
					int temp = newArray[j];
					newArray[j] = newArray[i];
					newArray[i] = temp;
				}				
			}
		}
	}
	return newArray;	
}

long numberFromArray(int *array, int length){
	long sum = 0;
	int currentIndex = 0;
	while(currentIndex < length){
		sum += array[currentIndex] * pow(10, (length - (currentIndex + 1)));
		currentIndex ++;
	}
	return sum;
}
long maxValueWithDigitsFromNumber(long number){	
	// Counting the number of digits
	int digitCount = lengthOfNumber(number);
	// Getting digits in an arrag
 	int *arrayOfDigits = arrayFromNumber(number); 	
 	// Getting the array arranged in decending order
 	int *arrayInDecendingOrder = sortArray(arrayOfDigits, digitCount, false); 	
 	// Getting max number from the digits of the number
 	return numberFromArray(arrayInDecendingOrder, digitCount);
}
long minValueWithDigitsFromNumber(long number){	
	// Counting the number of digits
	int digitCount = lengthOfNumber(number);
	// Getting digits in an arrag
 	int *arrayOfDigits = arrayFromNumber(number); 	
 	// Getting the array arranged in accending order
 	int *arrayInAccendingOrder = sortArray(arrayOfDigits, digitCount, true); 	
 	// Getting min number from the digits of the number
 	return numberFromArray(arrayInAccendingOrder, digitCount);
 }
int numberOfDigitOccurrenceInArray(int *array, int length, int digit){
	int occurrenceCount = 0;
	for (int i = 0 ; i < length ; i++){
		if(digit == array[i]){
			occurrenceCount++;
		}
	}
	return occurrenceCount;
}

bool areArrayElementsAreSame(int *firstArray, int *secondArray, int length){
	
	for(int i = 0; i < length; i ++){
		int singleDigit = firstArray[i];
		int numberOfOccurrenceInFirstArray = numberOfDigitOccurrenceInArray(firstArray,length,singleDigit);
		int numberOfOccurrenceInSecondArray = numberOfDigitOccurrenceInArray(secondArray,length,singleDigit);
		if(numberOfOccurrenceInFirstArray != numberOfOccurrenceInSecondArray){
			return false;
		}
	}
	return true;
}
 int main(int argc, char *argv[]){
 	long number;
 	cout << "Enter a number: ";
 	cin >> number; 	
 	int digitCount = lengthOfNumber(number);
 	long maxValue = maxValueWithDigitsFromNumber(number); //cout <<"Max Value = " << maxValue << endl;
 	long minValue = minValueWithDigitsFromNumber(number); //cout <<"Min Value = " << minValue << endl;
 	
// 	int *maxValueArray = arrayFromNumber(maxValue);
// 	int *minValueArray = arrayFromNumber(minValue);
 	int *numberDigitHolderArray = arrayFromNumber(number);
// 	cout << areArrayElementsAreSame(maxValueArray, minValueArray,digitCount);
	long numberOfPossibleCombinations = 0;
	for (long currentNumber = minValue; currentNumber <= maxValue; currentNumber++ ){
		int* currentNumberDigitHolderArray = arrayFromNumber(currentNumber);
		if(areArrayElementsAreSame(numberDigitHolderArray, currentNumberDigitHolderArray, digitCount)){
			numberOfPossibleCombinations++;
			cout << numberOfPossibleCombinations << "\t" << numberFromArray(currentNumberDigitHolderArray, digitCount) << endl;
		}
	}
 }
