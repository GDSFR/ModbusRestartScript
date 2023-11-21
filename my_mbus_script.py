import serial

def request_construct(baudrate, slave_id, to_reset=None):
    a = 1
    b = 0
    if to_reset == True:
        return a
    else:
        return b

def response_check(self, response):
    response_good = b'bbbbb'
    if response == response_good:
        return True
    else:
        return False
def main():
    baudrates = [110, 300, 1200, 2400, 9600, 19200, 28800, 38400, 57600, 115200, 230400, 460800, 921600]
    slaves_num = 20
    found = 0
    need = 1
    request = b'aaaaa'
    ser = serial.Serial('/dev/ttyACM0', baudrates[0], timeout=0.3)


    for i in range(1, slaves_num+1):        #1 --- 20
        for j in range(len(baudrates)):
            ser.write(request_construct(
                baudrate=baudrates[j],
                slave_id=i
            ))
            response = ser.read()
            if response_check(response) == True:
                request_construct(
                    baudrate=baudrates[j],
                    slave_id=i,
                    to_reset=True
                )
                found+=1
                break
        if found ==  need:
            break


if __name__ == '__main__':
    main()
