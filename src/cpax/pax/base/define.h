#ifndef PX_BASE_DEFINE_H
#define PX_BASE_DEFINE_H

#define __pxString__(x) # x
#define pxString(x)     __pxString__(x)

#define __pxConcat__(x, y) x ## y
#define pxConcat(x, y)    __pxConcat__(x, y)

#define pxCast(t, x) ((t)(x))

#define pxSize(x) pxCast(pxiword, sizeof (x))

#define pxMin(x, y) ((x) < (y) ? (x) : (y))
#define pxMax(x, y) ((x) < (y) ? (y) : (x))

#define pxClamp(x, l, r) pxMax(l, pxMin(x, r))

#endif // PX_BASE_DEFINE_H
