

typedef union Something{
	int anInt;
	float aFloat;
	char* name;
} Something;


int main(){
	Something x;
	x.anInt = 42;
	return 0;

}
