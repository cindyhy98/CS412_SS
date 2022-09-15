import angr
import claripy

# +
# 0xEDB88320
s = claripy.Solver()

def get_crc32_BVV(i):
    crc = i.zero_extend(32 - i.size());
    if isinstance(crc, angr.state_plugins.sim_action_object.SimActionObject):
        crc = crc.to_claripy() 
        
    for j in range(8):
        shift = ((crc >> 1) & 0x7FFFFFFF)
        cond = (crc & 1) > 0
        
        crc = claripy.If(cond, shift  ^ 0xEDB88320, shift);    #0xEDB88320 is the reverse of 0x04C11DB7
    return crc


def crc32(message):
    crc = claripy.BVV(0xFFFFFFFF, 32)
    
    b32 = message.chop(8)
    for b in b32:
        #print("byte = ", b)
        shift = (crc >> 8) & 0x00FFFFFF
        onebyte = crc.get_byte(3)
        crc = get_crc32_BVV(onebyte ^ b) ^ shift
      
    return crc ^ 0xffffffff


flag_len = 16
flag = claripy.BVS('FLAG', flag_len * 8)


for b in flag.chop(8):
    s.add((b >= 65) & (b <= 90))

for i in range(len("FLAG")):
    b = flag.chop(8)[i]
    s.add(b == ord("FLAG"[i]))

s.add(crc32(flag) == 0x808ddb48)

sol = s.eval(flag, 1)[0].to_bytes(16*8, 'big')[-16:]

task_3 = open("./task_3.txt","wb")
task_3.write(sol)
task_3.close()


