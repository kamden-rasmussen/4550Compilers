#pragma once
const int MAX_INSTRUCTIONS = 5000;
const int MAX_DATA = 5000;
class InstructionsClass
{
public:
	InstructionsClass(); 
	void Encode(unsigned char c);
	void Encode(int x);
	void Encode(long long x);
	void Encode(void * p);
	void Finish(); 
	void Execute();
	void PushValue(int value);
	void PrintIntegerLinux64();
	void WriteMinusLinux64();
	void WriteSpaceLinux64();
	unsigned char * GetAddress();
	void PopAndWrite();
	void Call(void * p);
	int * GetMem(int index);
	void PushVariable(int index);
	void PopAndStore(int index);
	void PopPopDivPush();
	void PopPopMulPush();
	void PopPopSubPush();
	void PopPopAddPush();
	void PopPopComparePush(unsigned char relational_operator);
	void PopPopLessPush();
	void PopPopGreaterPush();
	void PopPopLessEqualPush();
	void PopPopGreaterEqualPush();
	void PopPopEqualPush();
	void PopPopNotEqualPush();
	void PopPopAndPush();
	void PopPopOrPush();
	unsigned char * SkipIfZeroStack();
	unsigned char * Jump();
	void SetOffset(unsigned char * codeAddress, int offset);
	void PrintAllMachineCodes();

private:
	unsigned char mCode[MAX_INSTRUCTIONS];
	int mCurrent; // where we are in mCode
	int mPrintInteger; 
		// Location to store an integer about to be printed.
	int mTempInteger; 
		// Location to store one char of integer to be printed.

	int mStartOfPrint;
		// The value of mCurrent where PrintIntegerLinux 64 starts.
		// Jump to this offset of mCode to print.
	int mStartOfMain; 
		// the value of mCurrent after coding the Print functions.
		// Jump to this offset of mCode to start program execution.
	char mMinusString; // Holds '-'
	char mSpaceString; // Holds ' '
	int mData[MAX_DATA]; // Holds data
};