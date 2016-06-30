
// a <- a[0] b[0] c[0] d[0]
// b <- a[1] b[1] c[1] d[1]
// c <- a[2] b[2] c[2] d[2]
// d <- a[3] b[3] c[3] d[3]
template <typename T>
inline void transpose4x4( T& a, T& b, T& c, T& d )
{
	return;
}

template <>
inline void transpose4x4( float32x4_t& a, float32x4_t& b, float32x4_t& c, float32x4_t& d )
{
	float32x4x2_t vAB = vtrnq_f32(a, b);
	float32x4x2_t vCD = vtrnq_f32(c, d);
	
	a = vcombine_f32(vget_low_f32(vAB.val[0]),  vget_low_f32(vCD.val[0]));
	b = vcombine_f32(vget_low_f32(vAB.val[1]),  vget_low_f32(vCD.val[1]));
	c = vcombine_f32(vget_high_f32(vAB.val[0]), vget_high_f32(vCD.val[0]));
	d = vcombine_f32(vget_high_f32(vAB.val[1]), vget_high_f32(vCD.val[1]));
	return;
}

