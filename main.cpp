#include <arm_neon.h>
#include <iostream>

void dumpVector( const char* message, float32x4_t a )
{
	using namespace std;
	float stub[4];
	vst1q_f32(stub, a);
	cout << message;
	for(unsigned int i = 0;i < 4;i++)
	{
		cout << '\t' << stub[i];
	}
	cout << endl;
}

int main(int argc, char**argv)
{
	float i0[] = { 2013.f, 2014.f, 2015.f, 2016.f, };
	float i1[] = {   64.f,  128.f,  256.f,  512.f, };
	float i2[] = { -999.f, -998.f, -997.f, -996.f, };
	float i3[] = {    1.f,    2.f,    3.f,    4.f, };

	float32x4_t v0 = vld1q_f32(i0);
	float32x4_t v1 = vld1q_f32(i1);
	float32x4_t v2 = vld1q_f32(i2);
	float32x4_t v3 = vld1q_f32(i3);

	dumpVector("v0", v0);
	dumpVector("v1", v1);
	dumpVector("v2", v2);
	dumpVector("v3", v3);

	asm(
		"vld1.32 {d0, d1}, [%3] \n\t"
		"vld1.32 {d2, d3}, [%4] \n\t"
		"vld1.32 {d4, d5}, [%5] \n\t"
		"vld1.32 {d6, d7}, [%6] \n\t"
		"vtrn.32 q0,q1          \n\t" // ZZR0G0B0 ZZR1G1B1 -> R1R0B1B0 ZZZZG1G0 ; d1 d0 d3 d2
		"vtrn.32 q2,q3          \n\t" // ZZR2G2B2 ZZR3G3B3 -> R3R2B3B2 ZZZZG3G2 ; d5 d4 d7 d6
		"vswp d1,d4             \n\t" // R1R0B1B0 R3R2B3B2 -> B3B2B1B0 R3R2R1R0 ; d1 d0 d5 d4
		"vswp d3,d6             \n\t" // ZZZZG1G0 ZZZZG3G2 -> G3G2G1G0 ZZZZZZZZ ; d3 d2 d7 d6
		"vswp %q0,q0            \n\t" // ZZZZG1G0 ZZZZG3G2 -> G3G2G1G0 ZZZZZZZZ ; d3 d2 d7 d6
		"vswp %q1,q1            \n\t" // ZZZZG1G0 ZZZZG3G2 -> G3G2G1G0 ZZZZZZZZ ; d3 d2 d7 d6
		"vswp %q2,q2            \n\t" // ZZZZG1G0 ZZZZG3G2 -> G3G2G1G0 ZZZZZZZZ ; d3 d2 d7 d6
		:"=w"(v0), "=w"(v1), "=w"(v2)
		:"r"(i0), "r"(i1), "r"(i2), "r"(i3)
		:"q0", "q1", "q2", "q3"
	);
	//asm(
	//	"vld1.32 {d0, d1}, [%3] \n\t"
	//	"vld1.32 {d2, d3}, [%4] \n\t"
	//	"vld1.32 {d4, d5}, [%5] \n\t"
	//	"vld1.32 {d6, d7}, [%6] \n\t"
	//	"vtrn.32 q0,q1          \n\t" // ZZR0G0B0 ZZR1G1B1 -> R1R0B1B0 ZZZZG1G0 ; d1 d0 d3 d2
	//	"vtrn.32 q2,q3          \n\t" // ZZR2G2B2 ZZR3G3B3 -> R3R2B3B2 ZZZZG3G2 ; d5 d4 d7 d6
	//	"vswp d1,d4             \n\t" // R1R0B1B0 R3R2B3B2 -> B3B2B1B0 R3R2R1R0 ; d1 d0 d5 d4
	//	"vswp d3,d6             \n\t" // ZZZZG1G0 ZZZZG3G2 -> G3G2G1G0 ZZZZZZZZ ; d3 d2 d7 d6
	//	"vmov %0 q0             \n\t"
	//	"vmov %1 q1             \n\t"
	//	"vmov %2 q2             \n\t"
	//	:"=r"(v0), "=r"(v1), "=r"(v2)
	//	:"r"(i0), "r"(i1), "r"(i2), "r"(i3)
	//	:"q0", "q1", "q2", "q3"
	//);

	dumpVector("v0", v0);
	dumpVector("v1", v1);
	dumpVector("v2", v2);

	return 0;
}
