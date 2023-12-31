def crc16(data: bytes):
 crc = 0xffff
 for cur_byte in data:
   crc = crc ^ cur_byte
   for _ in range(8):
      a = crc
      carry_flag = a & 0x0001
      crc = crc >> 1
      if carry_flag == 1:
         crc = crc ^ 0xa001
   return bytes([crc % 256, crc >> 8 % 256])


data = b"\x01\00\x00\x02\x00\x01\x04"
#data = b"\x01\x06\x00\x05\x00\x01"
data = b"\x0a\x00\x00\xC8\x00\x00\x00\x00\x00\x00\x00\x00"
crc = crc16(data)
print(crc)
crc_str = " ".join("{:02x}".format(x) for x in crc)
print(crc_str)