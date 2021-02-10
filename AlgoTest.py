print("Python Program Start")

import ctypes
import random

driver = ctypes.cdll.LoadLibrary("./driver.so")
driver.test_init.argtypes = (ctypes.c_int, ctypes.c_long, ctypes.c_long)

# array = ctypes.cdll.LoadLibrary("./array.so")
#n = 4000000000
n = 1000000000
# n = 100000
n = 200000000
n = 100
trials = 100
# driver.test_init.restypes = (ctypes.c_double,)

average = driver.test_init(1, trials, n - 1, n) / (trials * 1000000)

print("n: " + str(n) + "   " + str(average)) # data_struct_type, trials, key, n


# print("done")
# data_structure = ctypes.POINTER(ctypes.c_void_p)

# ptr = ctypes.addressof(array.create(key_array, value_array, n))

# ctypes.cast(array.create(key_array, value_array, n), data_structure)
# data_structure = array.create(key_array, value_array, n)


# print(data_structure)

# print("successfully created")

# print(array.search("key9999".encode('utf-8'), n))

# print("successfully searched")

# c_string = ctypes.c_char_p(driver.test_return(key_array, 5)).value
# print(c_string)

# potato = "hello".encode('utf-8')
# print(driver.test_string_input(potato))

# print("testing")
# print(c_string[2:-1])
# print(str(c_string)[2:-1])

# print("testing all together\n")

# print(str(ctypes.c_char_p(driver.test_return(key_array, 5)).value)[2:-1])



# driver.key_array_destroy(key_array, n)
# driver.value_array_destroy(value_array)
# array.destroy()




# driver.test_string_input.argtypes = (ctypes.c_char_p,)
# driver.test_string_input.restypes = (ctypes.c_char_p,)



# print(driver.test_string_input(potato2))


# c_string_p = ctypes.POINTER(ctypes.c_char_p)

# test_string = ctypes.c_char_p(driver.test_return(key_array, 5))

# ctypes.cast(ctypes.addressof(test_string), c_string_p)

# python_string = ctypes.cast(ctypes.addressof(test_string), c_string_p).contents

