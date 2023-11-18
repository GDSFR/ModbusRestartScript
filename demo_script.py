import asyncio
import logging

import helper

from pymodbus.client import (
    ModbusSerialClient,
    ModbusTcpClient,
)


logging.basicConfig()
_logger = logging.getLogger(__file__)
_logger.setLevel("DEBUG")

def setup_sync_client(description=None, cmdline=None, baudrate=None):
    """Run client setup."""
    args = helper.get_commandline(
        server=False,
        description=description,
        cmdline=cmdline,
    )
    _logger.info("### Create client object")
    if args.comm == "tcp":
        client = ModbusTcpClient(
            args.host,
            port=args.port,
            # Common optional parameters:
            framer=args.framer,
            timeout=args.timeout,
            #    retries=3,
            #    retry_on_empty=False,y
            #    close_comm_on_error=False,
            #    strict=True,
            # TCP setup parameters
            #    source_address=("localhost", 0),
        )
    elif args.comm == "serial":
        client = ModbusSerialClient(
            port=args.port,  # serial port
            # Common optional parameters:
            #    framer=ModbusRtuFramer,
            timeout=args.timeout,
            #    retries=3,
            #    retry_on_empty=False,
            #    close_comm_on_error=False,.
            #    strict=True,
            # Serial setup parameters
            baudrate=baudrate,
            #    bytesize=8,
            #    parity="N",
            #    stopbits=1,
            #    handle_local_echo=False,
        )
    return client


def run_sync_client(client, modbus_calls=None):
    """Run sync client."""
    _logger.info("### Client starting")
    client.connect()
    if modbus_calls:
        modbus_calls(client)
    client.close()
    _logger.info("### End of Program")


def test_call(client, slave_id=None):
    """Test connection works."""
    rr = client.read_coils(32, 1, slave=1)
#    assert len(rr.bits) == 8
    rr = client.read_holding_registers(4, 2, slave=1)

#    assert rr.registers[0] == 17
#    assert rr.registers[1] == 17

def restart(cmdline=None):
    baudrates=[110, 300, 1200, 2400, 9600, 19200, 28800, 38400, 57600, 115200, 230400, 460800, 921600]
    for i in baudrates:
        testclient = setup_sync_client(
            description="Run synchronous client.", cmdline=cmdline, baudrate = i
        )
        run_sync_client(testclient, modbus_calls=test_call)
def main():
    restart()

if __name__ == '__main__':
    main()