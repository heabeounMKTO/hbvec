import ctypes

hb_vec = ctypes.CDLL("./build/obj/libhbvec.so")
hb_vec.vec3d_new.argtypes = [ctypes.c_double,ctypes.c_double,ctypes.c_double]

test = hb_vec.vec3d_new(0.34, 0.42,1.23)
test2 = hb_vec.vec3d_new(1.0,1.0,1.0)

