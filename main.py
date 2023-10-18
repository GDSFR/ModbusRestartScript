from pymodbus.diag_message import ClearCountersRequest
import serial
from pymodbus.diag_message import ClearCountersResponse

# !/usr/bin/env python3
"""Pymodbus synchronous client example.
An example of a single threaded synchronous client.
usage: simple_client_async.py
All options must be adapted in the code
The corresponding server must be started before e.g. as:
python3 server_sync.py
"""
# --------------------------------------------------------------------------- #
# import the various client implementations
# --------------------------------------------------------------------------- #
from pymodbus import pymodbus_apply_logging_config
from pymodbus.client import (
    ModbusSerialClient,
    ModbusTcpClient,
)
from pymodbus.exceptions import ModbusException
from pymodbus.pdu import ExceptionResponse
from pymodbus.transaction import (
    #
    ModbusAsciiFramer,
    #
    ModbusBinaryFramer,
    ModbusRtuFramer,
    ModbusSocketFramer,
    ModbusTlsFramer,
)


def run_sync_simple_client(comm, host, port, baudrate, framer=ModbusSocketFramer):
    # activate debugging
    pymodbus_apply_logging_config("DEBUG")
    print("get client")
    if comm == "tcp":
        client = ModbusTcpClient(
            host,
            port=port,
            framer=framer,
            # timeout=10,
            # retries=3,
            # retry_on_empty=False,y
            # close_comm_on_error=False,
            # strict=True,
            # source_address=("localhost", 0),
        )
    elif comm == "rtu":
        client = ModbusSerialClient(
            port,
            framer=ModbusRtuFramer,
            # timeout=10,
            # retries=3,
            # retry_on_empty=False,
            # close_comm_on_error=False,.
            # strict=True,
            baudrate=baudrate,
            bytesize=8,
            parity="N",
            stopbits=1,
            # handle_local_echo=False,
        )
    else:  # pragma no cover
        print(f"Unknown client {comm} selected")
        return

    print("connect to server")
    client.connect()

    print("get and verify data")
    try:
        rr = client.read_coils(1, 1, slave=1)
    except ModbusException as exc:
        print(f"Received ModbusException({exc}) from library")
        client.close()
        return
    if rr.isError():  # pragma no cover
        print(f"Received Modbus library error({rr})")
        client.close()
        return
    if isinstance(rr, ExceptionResponse):  # pragma no cover
        print(f"Received Modbus library exception ({rr})")
        # THIS IS NOT A PYTHON EXCEPTION, but a valid modbus message
        client.close()
        print("close connection")  # pragma no cover
        client.close()  # pragma no cover


if __name__ == "__main__":
    run_sync_simple_client("rtu", "0", "/dev/pts/4", 9600)
# pragma: no cover


request = ClearCountersRequest()
# response = run_sync_simple_client.execute(request)
print(run_sync_simple_client)
