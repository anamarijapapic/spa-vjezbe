#include "longnumber.h"

void main() {
	LongNumber numa = read_longnum("a.txt");
	print_longnum(numa);
	write_longnum(numa, "number.txt");
	LongNumber numb = read_longnum("b.txt");
	print_longnum(numb);
	write_longnum(numb, "number.txt");
	LongNumber numc = add_longnum(numa, numb);
	print_longnum(numc);
	write_longnum(numc, "number.txt");
	LongNumber numd = mul_by_digit(numc, 9);
	print_longnum(numd);
	write_longnum(numd, "number.txt");
	LongNumber nume = mul_by_pow10(numd, 3);
	print_longnum(nume);
	write_longnum(nume, "number.txt");
	LongNumber numf = mul_longnum(numa, numb);
	print_longnum(numf);
	write_longnum(numf, "number.txt");

	delete_longnum(numa);
	delete_longnum(numb);
	delete_longnum(numc);
	delete_longnum(numd);
	delete_longnum(nume);
	delete_longnum(numf);
}