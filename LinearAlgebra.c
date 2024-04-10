#include "LinearAlgebra.h"

vec3 vInv(vec3 a) {
    vec3 result = {-a.x, -a.y, -a.z};
    return result;
}

vec3 vQuat(quat a) {
    vec3 result = {a.x, a.y, a.z};
    return result;
}

vec3 vPolar(float a, float b, float c) {
    vec3 result = {c * sin(a) * cos(b), c * sin(a) * sin(b), c * cos(a)};
    return result;
}

vec3 vAdd(vec3 const a, vec3 const b) {
    vec3 result = {a.x + b.x, a.y + b.y, a.z + b.z};
    return result;
}

vec3 vSubtract(vec3 const a, vec3 const b) {
    vec3 result = {a.x - b.x, a.y - b.y, a.z - b.z};
    return result;
}

vec3 vScale(float const a, vec3 const b) {
    vec3 result = {a * b.x, a * b.y, a * b.z};
    return result;
}

vec3 vDivide(float const a, vec3 const b) {
    vec3 result = {b.x / a, b.y / a, b.z / a};
    return result;
}

float vDot(vec3 const a, vec3 const b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float vLength(vec3 const a) {
    return sqrtf(vDot(a, a));
}

vec3 vCross(vec3 const a, vec3 const b) {
    vec3 result = {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
    return result;
}

vec3 vNormalize(vec3 const a) {
    if (vLength(a) == 0) return a;
    return vDivide(vLength(a), a);
}

quat qReal(float const a) {
    quat result = {0, 0, 0, a};
    return result;
}

quat qVector(vec3 const a) {
    quat result = {a.x, a.y, a.z, 0};
    return result;
}

quat qInvert(quat const a) {
    quat result = {-a.x, -a.y, -a.z, -a.w};
    return result;
}

quat qAdd(quat const a, quat const b) {
    quat result = {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
    return result;
}

quat qSubtract(quat const a, quat const b) {
    quat result = {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
    return result;
}

quat qScale(float const a, quat const b) {
    quat result = {a * b.x, a * b.y, a * b.z, a * b.w};
    return result;
}

quat qDivide(float const a, quat const b) {
    quat result = {b.x / a, b.y / a, b.z / a, b.w / a};
    return result;
}

float qDot(quat const a, quat const b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

float qLength(quat const a) {
    return sqrtf(qDot(a, a));
}

quat qNormalize(quat const a) {
    if (qLength(a) == 0) return a;
    return qDivide(qLength(a), a);
}

quat qCross(quat const a, quat const b) {
    quat result = {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x, 0};
    return result;
}

quat qMultiply(quat const a, quat const b) {
    quat result = qCross(a, b);
    result = qAdd(result, qScale(a.w, b));
    result = qAdd(result, qScale(b.w, a));
    result = qSubtract(result, qReal(qDot(a, b)));
    return result;
}

quat qConjugate(quat const a) {
    quat result = {-a.x, -a.y, -a.z, a.w};
    return result;
}

quat qPolar(vec3 axis) {
    vec3 normal = vNormalize(axis);
    float angle = vLength(axis);
    return qAdd(qScale(sin(angle), qVector(normal)), qReal(cos(angle)));
}

vec3 qRotateVector(vec3 const a, quat const b) {
    quat c = {a.x, a.y, a.z, 0};
    quat result = qMultiply(qMultiply(b, c), qConjugate(b));
    vec3 res = {result.x, result.y, result.z};
    return res;
}

quat qPolarRotation(vec3 const rotator, quat const rotation) {
	return qMultiply(qPolar(rotator), rotation);
}

vec3 mApply(matrix const a, vec3 b) {
    vec3 result = vAdd(vAdd(vScale(b.x, a.a), vScale(b.y, a.b)), vScale(b.z, a.c));
    return result;
}

matrix mDioagonal(vec3 const a) {
    matrix result = {{a.x, 0, 0}, {0, a.y, 0}, {0, a.z, 0}};
    return result;
}

matrix mAdd(matrix const a, matrix const b) {
    matrix result = {vAdd(a.a, b.a), vAdd(a.b, b.b), vAdd(a.c, b.c)};
    return result;
}