import json
import claripy

s = claripy.Solver()

x = claripy.BVS('x', 32)
y = claripy.BVS('y', 32)

s.add((x | x % 0x3fd & x ^ 0x309) & 0xe0 == 0x60)
s.add((x + x + x % (x + 0x3c5) - y) * 0x2e == 0xfffe5e3a)
s.add((y & (y ^ y - ((x | 0x15b) ^ x))) - 0x7b == 0x1005)
s.add(0xdf & (0x291 ^ x * (x - y | y)) == 0x0)
s.add(0x336 % ((x ^ x % ((x & y) + 0x1a8) * y & y) + 0xd8) == 0x336)

res_x = s.eval(x, 1)[0]
res_y = s.eval(y, 1)[0]

data = {"x": int(res_x), "y": int(res_y)}


task_1 = open("./task_1.json", "w")
task_1.write(json.dumps(data))
task_1.close()
