#ifndef LINEAR_ALGEBRA
#define LINEAR_ALGEBRA

#include <math.h>

#define PI 3.14159265359

typedef struct {
    float x;
    float y;
    float z;
} vec3;

typedef struct {
    float x;
    float y;
    float z;
    float w;
} quat;

typedef struct {
    vec3 a;
    vec3 b;
    vec3 c;
} matrix;

vec3 vInv(vec3 a);
vec3 vQuat(quat a);
vec3 vPolar(float a, float b, float c);
vec3 vAdd(vec3 const a, vec3 const b);
vec3 vSubtract(vec3 const a, vec3 const b);
vec3 vScale(float const a, vec3 const b);
vec3 vDivide(float const a, vec3 const b);
float vDot(vec3 const a, vec3 const b);
float vLength(vec3 const a);
vec3 vCross(vec3 const a, vec3 const b);
vec3 vNormalize(vec3 const a);
quat qReal(float const a);
quat qVector(vec3 const a);
quat qInvert(quat const a);
quat qAdd(quat const a, quat const b);
quat qSubtract(quat const a, quat const b);
quat qScale(float const a, quat const b);
quat qDivide(float const a, quat const b);
float qDot(quat const a, quat const b);
float qLength(quat const a);
quat qNormalize(quat const a);
quat qCross(quat const a, quat const b);
quat qMultiply(quat const a, quat const b);
quat qConjugate(quat const a);
quat qPolar(vec3 axis);
vec3 qRotateVector(vec3 const a, quat const b);
quat qPolarRotation(vec3 const rotator, quat const rotation);
vec3 mApply(matrix const a, vec3 b);
matrix mDioagonal(vec3 const a);
matrix mAdd(matrix const a, matrix const b);

#endif