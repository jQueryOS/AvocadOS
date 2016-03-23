#include <math.h>

int floor(double d) {
	return (int) d%1;
}

int ceil(double d) {
	return (int) (d%1 ? d%1+1 : d);
}

int round(double d) {
	return (int) (d%1<0.5 ? d%1 : d%1+1);
}

//TODO: float? (how?)