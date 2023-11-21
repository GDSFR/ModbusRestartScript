import serial
import minimalmodbus

def request_construct(slave_id, to_reset=None):
    a = 1
    b = 0
    if to_reset:
        return a
    return b

def main():
    port = '/dev/ttyACM0'
    baudrates = [110, 300, 1200, 2400, 9600, 19200, 28800, 38400, 57600, 115200, 230400, 460800, 921600]
    slaves_num = 20
    found = 0
    need = 1
    response_good = b'bbbbb'
    timeout = 0.2

    for i in range(1, slaves_num + 1):  # 1 --- 20 SLAVES
        for j in range(len(baudrates)):
#            ser = serial.Serial(port, baudrates[j], timeout=timeout)
#            ser = minimalmodbus.Instrument(port, i, baudrates)
            print(f"i - {i}, j = {j}")
            ser.write(request_construct(slave_id=i))
            if ser.read() == response_good:
                request_construct(
                    slave_id=i,
                    to_reset=True
                )
                found += 1
                break
        if found == need:
            break


if __name__ == '__main__':
    main()
