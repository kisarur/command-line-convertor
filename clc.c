#include <stdio.h>
#include <limits.h>
#include <float.h>

int isError(int argc, char inType[], char outType[], char input[]);
int getTypeSize (char type, char number[]);
long long int char2int(char number[]);
long double char2floating(char number[]);
void printArray (int array[], int size);
int charArrayLength(char array[]);
double power(int number, int power);
void intArray2charArray (int intArray[], char charArray[], int size);
void int2binary (int number, int binaryArray[]);
void positiveInt2Binary (size_t number,int binaryArray[], int bits);
long long int twosBinary2Int (char binary[], int bits);
long long int binary2int (char binary[], int bits);
double fractionalBinary2Float (char binary[]);
void hex2binary (char hex[], int digits, int binaryArray[]);
void binary2hex(char binary[], int bits);
double binary2floating (char binary[], int precision);
void floating2binary(char number[],int binaryArray[32], int precision);
int countBaseTwoExponent (double number);


int main(int argc, char** argv) {
	// checking if there are errors/warnings for the arguments user entered and producing appropriate error/warning messages
	if (isError(argc, argv[1], argv[2], argv[3])) {
		return 1;
	}

	char inType = argv[1][1];
	char outType = argv[2][1];
	
	// conversion between same input and output types
	if (inType == outType) {
		if (inType == 'F') {
			fprintf(stdout, "%.2f\n", (float)char2floating(argv[3]));
		} else if (inType == 'D') {
			fprintf(stdout, "%lf\n", (double)char2floating(argv[3]));
		} else {
			fprintf(stdout, "%s\n", argv[3]);
		}
	}

/* CONVERSIONS FROM INTEGER TO OTHER DATA TYPES */

	// conversion from integer to float
	if (inType == 'I' && outType == 'F') {
		fprintf(stdout, "%.2Lf\n", char2floating(argv[3]));
	}

	// conversion from integer to 32-bit binary
	if (inType == 'I' && outType == 'B') {
		int intNum = char2int(argv[3]);
		int binaryArray[32];
		int2binary(intNum, binaryArray);
		printArray(binaryArray, 32);
		fprintf(stdout, "\n");
	}

	// conversion from integer to 8-digit hexadecimal
	if (inType == 'I' && outType == 'H') {
		int intNum = char2int(argv[3]);
		fprintf(stdout, "0x%08X\n", intNum);
	}


/* CONVERSIONS FROM BINARY TO OTHER DATA TYPES */

	// conversion from 32-bit binary to integer
	if (inType == 'B' && outType == 'I') {
		fprintf(stdout, "%d\n", (int)twosBinary2Int(argv[3], 32));
	}

	// conversion from 32-bit/64-bit binary to 8-digit/16-digit hexadecimal
	if (inType == 'B' && outType == 'H') {
		int bits = charArrayLength(argv[3]);
		binary2hex(argv[3], bits); 
	}

	// conversion from 32-bit binary to float
	if (inType == 'B' && outType == 'F') {
		fprintf(stdout, "%.2f\n", (float)binary2floating(argv[3], 1));
	}

	// conversion from 64-bit binary to double
	if (inType == 'B' && outType == 'D') {
		fprintf(stdout, "%lf\n", binary2floating(argv[3], 2));
	}


/* CONVERSIONS FROM HEXADECIMAL TO OTHER DATA TYPES */

	// conversion from 8-digit/16-digit hexadecimal to 32-bit/64-bit binary
	if (inType == 'H' && outType == 'B') {
		int digits = charArrayLength(argv[3]); // getting the number of digits of the hex number
		int binaryArray[digits * 4];
		hex2binary(argv[3], digits, binaryArray); // converting hex number to binary
		printArray(binaryArray, digits*4);
		fprintf(stdout, "\n");
	}

	// conversion from 8-digit hexadecimal to integer
	if (inType == 'H' && outType == 'I') {
		int intBinaryArray[32];
		hex2binary(argv[3], 8, intBinaryArray); // converting hex number to binary
		char charBinaryArray[32];
		intArray2charArray(intBinaryArray, charBinaryArray, 32); // converting int array of binary number to char array (to send to twosBinary2Int function)
		fprintf(stdout, "%d\n", (int)twosBinary2Int(charBinaryArray, 32)); // taking the integer value using 32-bit binary(in two's comp) and printing it out
	}

	// conversion from 8-digit hexadecimal to float
	if (inType == 'H' && outType == 'F') {
		int intBinaryArray[32];
		hex2binary(argv[3], 8, intBinaryArray); // converting hex number to binary
		char charBinaryArray[32];
		intArray2charArray(intBinaryArray, charBinaryArray, 32);
		fprintf(stdout, "%.2f\n", (float)binary2floating(charBinaryArray, 1)); // taking the float value using 32-bit binary(in IEEE-754 standard) and printing it out
	}

	// conversion from 16-digit hexadecimal to double
	if (inType == 'H' && outType == 'D') {
		int intBinaryArray[64];
		hex2binary(argv[3], 16, intBinaryArray); // converting hex to binary
		char charBinaryArray[64];
		intArray2charArray(intBinaryArray, charBinaryArray, 64);
		fprintf(stdout, "%f\n", binary2floating(charBinaryArray, 2)); // taking the double value using 64-bit binary(in IEEE-754 standard) and printing it out
	}

/* CONVERSIONS FROM FLOAT TO OTHER DATA TYPES */

	// conversion from float to integer
	if (inType == 'F' && outType == 'I') {
		fprintf(stdout, "%d\n", (int)char2floating(argv[3]));
	}
	
	// conversion from float to binary
	if (inType == 'F' && outType == 'B') {
		int binaryArray[32];
		floating2binary(argv[3], binaryArray, 1);
		printArray(binaryArray, 32);
		fprintf(stdout, "\n");
	}
	
	// conversion from float to 8-digit hexadecimal
	if (inType == 'F' && outType == 'H') {
		int intBinaryArray[32];
		floating2binary(argv[3], intBinaryArray, 1); // converting flot to binary 
		char charBinaryArray[32];
		intArray2charArray(intBinaryArray, charBinaryArray, 32); 
		binary2hex(charBinaryArray, 32); // taking the hex representation using binary
	}

/* CONVERSIONS FROM DOUBLE TO OTHER DATA TYPES */

	// conversion from double to binary
	if (inType == 'D' && outType == 'B') {
		int binaryArray[64];
		floating2binary(argv[3], binaryArray, 2);
		printArray(binaryArray, 64);
		fprintf(stdout, "\n");
	}

	// conversion from double to 16-digit hexadecimal
	if (inType == 'D' && outType == 'H') {
		int intBinaryArray[64];
		floating2binary(argv[3], intBinaryArray, 2);  // converting double to binary 
		char charBinaryArray[64];
		intArray2charArray(intBinaryArray, charBinaryArray, 64);
		binary2hex(charBinaryArray, 64); // taking the hex representation using binary
	}

	return 0;
}


/* ---------------------- */
/* USER DEFINED FUNCTIONS */
/* ---------------------- */


int isError(int argc, char inType[], char outType[], char input[]) {
	
	char* wrongArgCount =  "ERROR: The number of arguments is wrong.\nUsage: ./clc -<input format> -<output format> <input>\n";
	char* wrongInputType =  "ERROR: The input argument is wrong.\nPossible input arguments are -B, -H, -I, -F and -D.\n";
	char* wrongOutputType =  "ERROR: The output argument is wrong.\nPossible output arguments are -B, -H, -I, -F and -D.\n";
	char* wrongInputSize =  "ERROR: The input size is wrong.\n";
	char* wrongInputFormat =  "ERROR: Input format error at location %d.\n";
	char* impossibleConversion = "ERROR: This conversion is not possible.\n";
	char* precisionLoss = "WARNING: There is a possibility for a precision loss.\n";
	
/* Checking for wrong argument count */
	if (argc != 4) {
		fprintf(stderr, "%s", wrongArgCount);
		return 1;
	}
/*------------------------------------------------------------------------------------------------------------------*/
	
/* Checking for wrong input type */
	if (!(inType[0] == '-' && (inType[1] == 'B' || inType[1] == 'H' || inType[1] == 'I' || inType[1] == 'F' || inType[1] == 'D'))) {
		fprintf(stderr, "%s", wrongInputType);
		return 1;
	}
/*------------------------------------------------------------------------------------------------------------------*/
	
/* Checking for wrong output type */
	if (!(outType[0] == '-' && (outType[1] == 'B' || outType[1] == 'H' || outType[1] == 'I' || outType[1] == 'F' || outType[1] == 'D'))) {
		fprintf(stderr, "%s", wrongOutputType);
		return 1;
	}
/*------------------------------------------------------------------------------------------------------------------*/
	
/* Checking for wrong input size */
	int inputLength = charArrayLength(input);
	if (inType[1] == 'B' && !(inputLength == 32 || inputLength == 64)) {
		fprintf(stderr, "%s", wrongInputSize);
		return 1;
	} 
	if (inType[1] == 'H' && !(inputLength == 8 || inputLength == 16)) {
		fprintf(stderr, "%s", wrongInputSize);
		return 1;
	}
	
	long double inputValue = char2floating(input); 
	if (inType[1] == 'I' && !(inputValue >= INT_MIN && inputValue <= INT_MAX )) {
		fprintf(stderr, "%s", wrongInputSize);
		return 1;
	}
	if (inType[1] == 'F' && !(inputValue >= -FLT_MAX && inputValue <= FLT_MAX)) { 
		fprintf(stderr, "%s", wrongInputSize);
		return 1;
	}
	if (inType[1] == 'D' && !(inputValue >= -DBL_MAX && inputValue <= DBL_MAX)) { 
		fprintf(stderr, "%s", wrongInputSize);
		return 1;
	}
/*------------------------------------------------------------------------------------------------------------------*/
	
	
/* Checking for wrong input format */
	char inTypes[] = "BHIFD";
	char allowedChars[][16] = {"10","0123456789ABCDEF","0123456789","0123456789","0123456789"};
	int i, j, digitLocation, digitValid, dotFound;
	for (i = 0; i < 5; i++) { // comparing the input type user entered with all the possible input types
		if (inType[1] == inTypes[i]) { // input type is matched with the input type user entered
			digitLocation = 0; 
			dotFound = 0; // variable to check if more than one decimal points are found in -F and -D input types
			
			// checking each digit of input array
			while (input[digitLocation]) {
				digitValid = 0; //variable to find if the digit is valid
				
				// making the program produce no error when the first '-' is found at location 0 in -I, -F and -D input types
				if ((i == 2 || i == 3 || i == 4) && digitLocation == 0 && input[digitLocation] == '-') {  
					digitValid = 1;
				}
				
				// making the program produce no error when the first decimal point is found in -F and -D input types
				if ((i == 3 || i == 4) && dotFound == 0 && input[digitLocation] == '.') {
					digitValid = 1;
					dotFound = 1;
				}
				
				// comparing the digit with all the allowable characters and checking if it's valid
				j = 0;
				while (allowedChars[i][j]) {
					if (input[digitLocation] == allowedChars[i][j]) {
						digitValid = 1;
					}
					j++;
				}
				
				// producing an error if the digit is not valid
				if(!digitValid){
					fprintf(stderr, wrongInputFormat, digitLocation);
					return 1;
				}
				
				digitLocation++;
			}
		}
	}
/*------------------------------------------------------------------------------------------------------------------*/
	
/* Checking for the possibility of the conversion */
	int inSize = getTypeSize(inType[1], input);
	int outSize;
	
	// based on the input type, output types -H and -B can take either 32bits or 64 bits as their size
	// so outSize is set by checking both input and output types when outType is either -H or -B and input type is not -H or -B
	if ((outType[1] == 'B' || outType[1] == 'H') && !(inType[1] == 'B' || inType[1] == 'H')) {
		if (inType[1] == 'D') {
			outSize = 64;
		} else {
			outSize = 32; 
		}
	} else {
		outSize = getTypeSize(outType[1], input); // this is used to take the outSize of -I -F and -D output types (including B to H and H to B conversions)
	}
	if (inSize != outSize) {
		fprintf(stderr, "%s", impossibleConversion);
		return 1;
	}
	
	// also the conversion is not possible when input number is not within the integer range when doing F to I conversion
	if (inType[1] == 'F' && outType[1] == 'I' && !(char2floating(input) > INT_MIN && char2floating(input) < INT_MAX)) {
		fprintf(stderr, "%s", impossibleConversion);
		return 1;

	}
/*------------------------------------------------------------------------------------------------------------------*/
	
	
/* Checking for precision loss */
	if (inType[1] == 'F' && outType[1] == 'I') { 
		fprintf(stderr, "%s", precisionLoss);
		return 0; // this is only a warning, no need to terminate the program
	}
/*------------------------------------------------------------------------------------------------------------------*/
	return 0;
}

// This function takes a variable type(either as B, H, I, F or D) and number (in a char array for B and H types) and returns its size in bits
int getTypeSize (char type, char number[]) { 
		switch(type) {
			case 'B':
				return charArrayLength(number);
				break;
			case 'H':
				return charArrayLength(number) * 4; // each digit contains 4 bits
				break;
			case 'I':
				return 32;
				break;
			case 'F':
				return 32;
				break;
			case 'D':
				return 64;
				break;
			default:
				return 0;
		}
}

// This function takes a char array of numbers and converts it to a long long integer value
long long int char2int(char number[]) {
	int i = 0, sign = 1; 
	long long int value = 0;
	
	if(number[0] == '-') {
		sign = -1;
		i++;
	}
	
	while (number[i]) {
		value = value * 10 + (number[i] - '0');
		i++;
	}
	return sign * value;
}

// This function takes a char array of numbers and converts it to a long double value
long double char2floating(char number[]) {
	int i = 0, sign = 1; 
	
	if(number[0] == '-') {
		sign = -1;
		i++;
	}
	
	// calculating the integer part of the number
	long double integerPart = 0;
	while(!(number[i] == '.' || number[i] == 0)) { // checking if the dot or null character found
		integerPart = integerPart * 10 + (number[i] - '0');
		i++;
	}
	
	// calculating the decimal part of the number
	long double decimalPart = 0;
	int j;
	for (j = charArrayLength(number) - 1; j > i; j--) {
        decimalPart = decimalPart / 10 + (number[j] - '0');
	}
	decimalPart /= 10;
	
	return sign * (integerPart + decimalPart);
}

// This function prints all the elements in an int array in a single line
void printArray (int array[], int size) {
	int i;
	for (i = 0; i < size; i++){
		fprintf(stdout, "%d", array[i]);
	}
}

// This functions counts the number of elements in a char array
int charArrayLength (char array[]) {
	int count = 0;
	while(array[count]) {
		count++;
	}
	return count;
}

// This function takes a number and its power and returns the value of the number to the power.
double power(int number, int power) { 
	int i;
	double result = 1;
	if (power > 0) { // if the power is positive
		for (i = 0; i < power; i++) {
			result *= number;
		}
	} else if (power < 0) {  // if the power is negative
		for (i = 0; i < -power; i++) {
			result /= number;
		}
	}
	
	return result;
}

// This function converts elements in an int array to elements in a char array
void intArray2charArray (int intArray[], char charArray[], int size) {
	int i;
	for (i = 0; i < size; i++) {
			charArray[i] = intArray[i] + '0';
	}
}

// This function takes a signed integer and converts it to a 32-bit binary number
void int2binary (int number, int binaryArray[]) {
	if (number >= 0) { // checking if the integer is positive
			positiveInt2Binary(number, binaryArray, 32);
		} else {
			size_t twosCompInDecimal = power(2, 32) + number; // calculating two's complement of the negative integer, in decimal
			positiveInt2Binary(twosCompInDecimal, binaryArray, 32);
		}
}

// This function takes a positive integer and converts it to size-bit binary number
void positiveInt2Binary (size_t number, int binaryArray[], int bits) {
	int binNum[bits]; // an array to save the bits of the binary number (this will come in reverse order of bits)
	int i = 0;
	if (number == 0) {
		binNum[i] = 0;
	} else {
		while (number != 1) {
			binNum[i] = number % 2; // taking the remainder after the devision by 2 to get the binary number
			number = number / 2;
			i++;
		}
		binNum[i] = 1;
	}

	// adding leading zeros if necessary to make bit representation complete
	int j;
	for (j = i + 1; j < bits; j++){
		binNum[j] = 0;
	}

	// re-arranging the bits of the binNum array in the reverse order to have the correct binary number
	int k;
	for (k = (bits-1); k >= 0; k--) {
		binaryArray[bits - (k + 1)] = binNum[k];
	}
}

// This function takes a binary number which is in two's complement and converts it to an integer value
long long int twosBinary2Int (char binary[], int bits) {
	if (binary[0] == '0') { // checking if the binary number is positive
		return binary2int(binary, bits);
	} else {
		long long twosCompInt = binary2int(binary, bits); // converting the negative binary number (which is in two's complement) to the decimal number
		long long absInteger = power(2, bits) - twosCompInt; // calculating absolute value of negative integer
		return -1 * absInteger;
	}
}

// This function takes a binary number and do the usual conversion from binary to integer
long long int binary2int (char binary[], int bits) {
	int i, bitVal;
	long long intNumber = 0;
	for (i = (bits - 1); i >= 0; i--) {
		bitVal = binary[i] - '0'; // taking the integer value of each bit
		intNumber += bitVal * power(2,((bits - 1) - i));
	}
	return intNumber;
}

// This function takes a fractional part of a binary number (eg: .1011 => {1,0,1,1}) in a char array and converts it to a floating point number
double fractionalBinary2Float (char binary[]) {
	int i, bitVal;
	double fraction = 0;
	for (i = 0; i < 23; i++) {
		bitVal = binary[i] - '0'; // taking the integer value of each bit
		fraction += bitVal * power(2,(-(i + 1)));
	}
	return fraction;
}

// This function takes a hexadecimal number and converts it to a binary number
void hex2binary (char hex[], int digits, int binaryArray[]) {
	int i, digitVal;
	int bin2DArray[digits][4]; // a 2D array to store binary bits (each row represents 1 digit of hex number)
	
	for (i = 0; i < digits; i++) {
		digitVal = hex[i] - '0';
		if (digitVal < 10) { // directly converting the digit value to binary if it's in the range 0-9
			positiveInt2Binary(digitVal, bin2DArray[i], 4);
		} else { 
			// if the digit is an alphebatic character, the value related to that character is converted to binary
			switch (hex[i]) {
				case 'A':
					positiveInt2Binary(10, bin2DArray[i], 4);
					break;
				case 'B':
					positiveInt2Binary(11, bin2DArray[i], 4);
					break;
				case 'C':
					positiveInt2Binary(12, bin2DArray[i], 4);
					break;
				case 'D':
					positiveInt2Binary(13, bin2DArray[i], 4);
					break;
				case 'E':
					positiveInt2Binary(14, bin2DArray[i], 4);
					break;
				case 'F':
					positiveInt2Binary(15, bin2DArray[i], 4);
					break;
			}
		}
	}

	// converting the bin2DArray to 1D binaryArray
	int rows = digits, cols = 4;
	int row, col;
	for (row = 0; row < rows; row++) {
		for (col = 0; col < cols; col++){
			binaryArray[cols * row + col] = bin2DArray[row][col];
		}
	}
}

void binary2hex(char binary[], int bits) {
	char bitGroup[4]; // an array to hold 4-bit groups of binary number
	int i, j;
	fprintf(stdout, "0x");
	for (i = 0; i < bits; i += 4) {
		for (j = 0; j < 4; j++) {
			bitGroup[j] = binary[i + j]; // putting parts of binary array into 4-bit group
		}
		fprintf(stdout, "%X", (unsigned int)binary2int(bitGroup, 4)); // converting each 4-bit group to integer and printing them as hex digits
	}
	fprintf(stdout, "\n");
}

// This function takes a binary number and converts it to a floating point number (precission = 1 => float/ precision = 2 => double)
double binary2floating (char binary[], int precision) {
	const int EXP_BITS = (precision == 1) ? 8 : 11; // number of bits in the exponent part
	const int SIG_BITS = (precision == 1) ? 23 : 52; // number of bits in the significand part

	short sign = 1;
	if (binary[0] == '1') { // deciding the sign of the number using first bit
		sign = -1;
	}

	// calculating exponent part of the floating point number, in decimal
	char exponent[EXP_BITS];
	int i;
	for (i = 0; i < EXP_BITS; i++) {
		exponent[i] = binary[i + 1]; // extracting exponent part from binary number
	}
	int exponentVal = binary2int(exponent, EXP_BITS);

	// calculating fractional part of the floating point number, in decimal
	char significand[SIG_BITS];
	for (i = 0; i < SIG_BITS; i++) {
		significand[i] = binary[i + EXP_BITS + 1]; // extracting significand part from binary number
	}
	double fractionVal = fractionalBinary2Float(significand);

	// calculating floating point number in decimal according to IEEE-754 standard
	if (precision == 1) {
		return sign * (1 + fractionVal) * power(2, (exponentVal - 127));
	} else {
		return sign * (1 + fractionVal) * power(2, (exponentVal - 1023));
	}

}

// This function takes a floating point number in a char array and converts it to a binary number 
// (precission = 1 => float/ precision = 2 => double)
void floating2binary(char number[],int binaryArray[], int precision) {
	const int TOTAL_BITS = (precision == 1) ? 32 : 64; // toatal number of bits in the binary representation
	const int EXP_BITS = (precision == 1) ? 8 : 11; // number of bits reserved to store exponenet as binary
	const int SIG_BITS = (precision == 1) ? 23 : 52; // number of bits reserved to store significand as binary

	int signBit = 0, realExponent, significand[SIG_BITS];
	
	// taking the sign of the number
	int i = 0;
	if (number[0] == '-') {
		signBit = 1;
		i++;
	}
	
	// calculating the integer part of the floating point number
	double integerPart = 0;
	while(!(number[i] == '.' || number[i] == 0)) {
		integerPart = integerPart * 10 + (number[i] - '0');
		i++;
	}
	
	// calculating the decimal part of the floating point number
	double decimalPart = 0;
	int j;
	for (j = charArrayLength(number) - 1; j > i; j--) {
        decimalPart = decimalPart / 10 + (number[j] - '0');
	}
	decimalPart /= 10;
    
    // getting the signficand part of the binary representation
    if (integerPart > 0) { // getting the signficand for numbers greater than 1
		realExponent = countBaseTwoExponent(integerPart); // getting the exponent value of the floating point number, when it is written in normalized form in base 2
		int integerPartBinary[realExponent]; 
		positiveInt2Binary(integerPart, integerPartBinary, realExponent); // converting integer part to binary.
																		  // most significand 1 is automatically cut-off since realExponent is equal to
																		  // 1 number less than the digits of the binary representation of integer part
	   
		if (realExponent > SIG_BITS) { // only the integer part's binary is taken for significand if the integer part's binary contains bits more than the capacity of signficand
			for (i = 0; i < SIG_BITS; i++) {
				significand[i] = integerPartBinary[i];
			}
		} else { 
			// getting the decimal part's binary representation 
			int decimalPartBinary[SIG_BITS - realExponent];
			int binaryBit;
			for (i = 0; i < SIG_BITS - realExponent; i++) {
				binaryBit = (int)(decimalPart * 2);
				decimalPart = 2 * decimalPart - binaryBit;
				decimalPartBinary[i] = binaryBit;
			}
			
			// adding integer part's binary bits to the signficand
			for (i = 0; i < realExponent; i++) {
				significand[i] = integerPartBinary[i];
			} 
			// filling up the signficand with decimal part's binary bits
			for (i = realExponent; i < SIG_BITS; i++) {
				significand[i] = decimalPartBinary[i - realExponent];
			}
		}
	} else if (integerPart == 0 && decimalPart > 0) { // getting the significand for numbers in range 0-1 (decimal numbers)
		int foundMSB = 0; // varialbe to check if the most signficand 1 is found in the binary representation
		int decimalPlacesShifted = 0; // counting number of decimal places shifted to form normalized form in base 2
		int i = 0, binaryBit; 
		while (i < SIG_BITS) {
			binaryBit = (int)(decimalPart * 2);
			decimalPart = 2 * decimalPart - binaryBit;
			if (foundMSB == 1){ // bits are added only when the most significand 1 was found
				significand[i] = binaryBit;
				i++; 
			} else {
				decimalPlacesShifted++; 
			}
			if (binaryBit == 1) { // most significand 1 is found!
				foundMSB = 1;
			}
		}
		realExponent = -decimalPlacesShifted; // exponent value of normalized form of floating point number in base 2 (it's always negative here)
	} else { // input number is 0
		// setting all the elements in significand to 0 
		for (i = 0; i < SIG_BITS; i++) {
			significand[i] = 0;
		}
		realExponent = -(power(2, (EXP_BITS - 1)) - 1); // exponent value is calculated so that the exponentVal that is stored in binary representation will become 0
	}
	
	// getting the exponent part of the binary representation
	int exponentVal = realExponent + (power(2, (EXP_BITS - 1)) - 1); // calculating exponent value needs to be saved in binary representatioin of number (E + 127 or E + 1023)
    int exponent[EXP_BITS];
    positiveInt2Binary(exponentVal, exponent, EXP_BITS);

	// forming final binary representation(in binaryArray[]) by adding signbit, exponent part and signficand part together
    binaryArray[0] = signBit;
    for(i = 1; i <= EXP_BITS; i++) {
        binaryArray[i] = exponent[i - 1];
    }
    for(i = EXP_BITS + 1; i <= TOTAL_BITS; i++) {
        binaryArray[i] = significand[i - EXP_BITS - 1];
    }
	
}

// This function takes a double number(>1) and find the exponent value, when it's written in normalized form in base two
// (eg: 10.75 => 1.00111 * 2 ^ 3 => exponent = 3)
int countBaseTwoExponent (double number) {
	int count = 0;
	while (1) {
		number = number / 2;
		if (number <= 1) {
			break;
		}
		count++;
	}
	return count;
}




