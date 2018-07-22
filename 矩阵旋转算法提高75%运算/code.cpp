

#include <MATH.H>
/*Ë«¾«¶È*/
//#define M_PI 3.14159265358979323846

#define pi 3.1415926

float AMath_ToRadian(float degree)
{
	return  ((degree) * (pi / 180.0f));
}

float AVector2_Length3(float x, float y, float z)
{
	return sqrtf(x*x + y*y + z*z);
}
// ¾ØÕó¶¨Òå

typedef union
{
	float m[16];
	struct
	{
		float
		m0,  m1,  m2,  m3,
		m4,  m5,  m6,  m7,
		m8,  m9,  m10, m11,
		m12, m13, m14, m15;
	};
}
Matrix4;



static void MultiplyMM(Matrix4* left, Matrix4* right, Matrix4* outMatrix4)
{
    outMatrix4->m0  = left->m0 * right->m0  + left->m4 * right->m1  + left->m8  * right->m2  + left->m12 * right->m3;
    outMatrix4->m1  = left->m1 * right->m0  + left->m5 * right->m1  + left->m9  * right->m2  + left->m13 * right->m3;
    outMatrix4->m2  = left->m2 * right->m0  + left->m6 * right->m1  + left->m10 * right->m2  + left->m14 * right->m3;
    outMatrix4->m3  = left->m3 * right->m0  + left->m7 * right->m1  + left->m11 * right->m2  + left->m15 * right->m3;
 
    outMatrix4->m4  = left->m0 * right->m4  + left->m4 * right->m5  + left->m8  * right->m6  + left->m12 * right->m7;
    outMatrix4->m5  = left->m1 * right->m4  + left->m5 * right->m5  + left->m9  * right->m6  + left->m13 * right->m7;
    outMatrix4->m6  = left->m2 * right->m4  + left->m6 * right->m5  + left->m10 * right->m6  + left->m14 * right->m7;
    outMatrix4->m7  = left->m3 * right->m4  + left->m7 * right->m5  + left->m11 * right->m6  + left->m15 * right->m7;
 
    outMatrix4->m8  = left->m0 * right->m8  + left->m4 * right->m9  + left->m8  * right->m10 + left->m12 * right->m11;
    outMatrix4->m9  = left->m1 * right->m8  + left->m5 * right->m9  + left->m9  * right->m10 + left->m13 * right->m11;
    outMatrix4->m10 = left->m2 * right->m8  + left->m6 * right->m9  + left->m10 * right->m10 + left->m14 * right->m11;
    outMatrix4->m11 = left->m3 * right->m8  + left->m7 * right->m9  + left->m11 * right->m10 + left->m15 * right->m11;
 
    outMatrix4->m12 = left->m0 * right->m12 + left->m4 * right->m13 + left->m8  * right->m14 + left->m12 * right->m15;
    outMatrix4->m13 = left->m1 * right->m12 + left->m5 * right->m13 + left->m9  * right->m14 + left->m13 * right->m15;
    outMatrix4->m14 = left->m2 * right->m12 + left->m6 * right->m13 + left->m10 * right->m14 + left->m14 * right->m15;
    outMatrix4->m15 = left->m3 * right->m12 + left->m7 * right->m13 + left->m11 * right->m14 + left->m15 * right->m15;
}
 
/**
 * Rotate identity matrix4 and multiply matrix4
 */
static void Rotate(Matrix4* matrix4, float angle, float x, float y, float z)
{
    angle     = AMath_ToRadian(angle);
 
    float s   = sinf(angle);
    float c   = cosf(angle);
 
    float len = AVector2_Length3(x, y, z);
 
    if (len != 1.0f)
    {
        float recipLen = 1.0f / len;
 
        x *= recipLen;
        y *= recipLen;
        z *= recipLen;
    }
 
    float nc = 1.0f - c;
    float xy = x * y;
    float yz = y * z;
    float zx = z * x;
    float xs = x * s;
    float ys = y * s;
    float zs = z * s;
 
	Matrix4 temp1[1] =
	{
		x  * x  * nc + c,
		xy * nc + zs,
		zx * nc - ys,
		0.0f,
 
		xy * nc - zs,
		y  * y  * nc + c,
		yz * nc + xs,
		0.0f,
 
		zx * nc + ys,
		yz * nc - xs,
		z  * z  * nc + c,
		0.0f,
 
		0.0f, 0.0f, 0.0f, 1.0f,
	};
 
	Matrix4 temp2[1];
	MultiplyMM(matrix4, temp1, temp2);
 
//	 memcpy(matrix->m, temp2->m, sizeof(Matrix4));
	*matrix4 = *temp2;
}

// ÈÆXÖáÐý×ª

static void RotateX(Matrix4* matrix4, float angle)
{
    angle   = AMath_ToRadian(angle);
 
    float s = sinf(angle);
    float c = cosf(angle);
 
    float m4     = matrix4->m4;
    float m5     = matrix4->m5;
    float m6     = matrix4->m6;
    float m7     = matrix4->m7;
 
    matrix4->m4  =  m4 *  c + matrix4->m8  * s;
    matrix4->m5  =  m5 *  c + matrix4->m9  * s;
    matrix4->m6  =  m6 *  c + matrix4->m10 * s;
    matrix4->m7  =  m7 *  c + matrix4->m11 * s;
 
    matrix4->m8  =  m4 * -s + matrix4->m8  * c;
    matrix4->m9  =  m5 * -s + matrix4->m9  * c;
    matrix4->m10 =  m6 * -s + matrix4->m10 * c;
    matrix4->m11 =  m7 * -s + matrix4->m11 * c;
}
 
 // ÈÆYÖáÐý×ª
 
static void RotateY(Matrix4* matrix4, float angle)
{
    angle    = AMath_ToRadian(angle);
    float s  = sinf(angle);
    float c  = cosf(angle);
 
	float m0     = matrix4->m0;
	float m1     = matrix4->m1;
	float m2     = matrix4->m2;
	float m3     = matrix4->m3;
 
    matrix4->m0  = m0 * c + matrix4->m8  * -s;
    matrix4->m1  = m1 * c + matrix4->m9  * -s;
    matrix4->m2  = m2 * c + matrix4->m10 * -s;
    matrix4->m3  = m3 * c + matrix4->m11 * -s;
 
    matrix4->m8  = m0 * s + matrix4->m8  *  c;
    matrix4->m9  = m1 * s + matrix4->m9  *  c;
    matrix4->m10 = m2 * s + matrix4->m10 *  c;
    matrix4->m11 = m3 * s + matrix4->m11 *  c;
}
 
 
 // ÈÆZÖáÐý×ª
 
static void RotateZ(Matrix4* matrix4, float angle)
{
    angle    = AMath_ToRadian(angle);
    float s  = sinf(angle);
    float c  = cosf(angle);
 
	float m0    = matrix4->m0;
	float m1    = matrix4->m1;
	float m2    = matrix4->m2;
	float m3    = matrix4->m3;
 
    matrix4->m0 = m0 *  c + matrix4->m4 * s;
    matrix4->m1 = m1 *  c + matrix4->m5 * s;
    matrix4->m2 = m2 *  c + matrix4->m6 * s;
    matrix4->m3 = m3 *  c + matrix4->m7 * s;
 
    matrix4->m4 = m0 * -s + matrix4->m4 * c;
    matrix4->m5 = m1 * -s + matrix4->m5 * c;
    matrix4->m6 = m2 * -s + matrix4->m6 * c;
    matrix4->m7 = m3 * -s + matrix4->m7 * c;
}

int main(int argc,char** argv)
{
	Matrix4 m1 = {1.0,2.0,3.0,4.0,
				2.0,2.0,2.0,2.0,
				2.0,2.0,2.0,2.0,
				2.0,2.0,2.0,2.0
	};

	Rotate(&m1,30,10.0,20.0,30.0);

	return 0;
}