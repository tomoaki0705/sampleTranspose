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

	return 0;
}
