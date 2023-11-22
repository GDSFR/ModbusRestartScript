import serial

import struct


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


def send_request(ser, slave_id, to_reset):
    func_id = 3  # Прочитать
    register_id = 2
    register_num = 1
    response_good = b""

    if to_reset:
        print('Resetting...')
        func_id = 6  # Записать
        register_id = 5
        # register_id_bytes = register_id.to_bytes(2, 'big')
        register_val_new = 1
        query = struct.pack(">2B2H", slave_id, func_id, register_id, register_val_new)
        crc = crc16(query)

    else:
        query = struct.pack(">2B2H", slave_id, func_id, register_id, register_num)
        crc = crc16(query)

    packet = query + crc
    print('\nSended query', query)
    print('\nSended packet', packet)
    # ser.write(query)
    # ser.write(crc)
    ser.write(packet)

    rec_data = ser.readall()
    print('Received ', rec_data)
    if (response_good == ser.readall()):
        return 1
    else:
        return 0


def main():
    port = '/dev/ttyACM2'
    baudrates = [115200]
    slaves_num = 4
    found = 0
    need = 1

    timeout = 0.3

    for i in range(1, slaves_num + 1):  # 1 --- 20 SLAVES
        for j in range(len(baudrates)):
            ser = serial.Serial(port, baudrates[j], timeout=timeout)
            print(f"i - {i}, j = {j}")

            is_good = send_request(ser, slave_id=i, to_reset=False)
            ser.write(b'\x0d')

            rec_data = ser.readall()
            print('Received ', rec_data)
            if is_good:
                print(f'\n--- Found device ---\t\nspeed:\t [{baudrates[j]}]\nslave_id: \t{i}\n--------------------')
                send_request(
                    ser,
                    slave_id=i,
                    to_reset=True
                )
                # print(f'\n--- Found device ---\t\nspeed:\t [{baudrates[j]}]\nslave_id: \t{i}\n--------------------')
                found += 1
                break
        if found == need:
            break


if __name__ == '__main__':
    main()
