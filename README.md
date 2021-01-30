# IoT-Pill-Dispenser
Firware for the AVR-IoT WA Development Board based on the original [example](https://github.com/microchip-pic-avr-solutions/avr-iot-aws-sensor-node-mplab)

# Main Features

### Custom CLI
The already implemented CLI have been extended including the command "pill" , its corresponding callback *pill_command()* that parses the message and sends th confirmation JSON by MQTT to the topic "confirmationpill". Also, the message in case of unknown message is customized as well as in the callback in case of incorrect parameter.

### CLI USART moved
The original CLI used the USART2, which is connected to the debugger by the PCB but is not accessible. For this version, the CLI structure and the funtionality *printf()* are now implemented on the USART1, which is avaliable with the pin conectors *RX* and *TX*. This alows us to use this CLI with any external device, taking into account the following configuration:
Baud Rate | Data | Parity bit | Stop bit | Flow control | Transmit protocol
---------- | ----- | ----- | ----- | ----- | -----
9600 | 8 bits| None | 1 bit | None | CR+LF (Carriage Return + Line Feed)

### Custom MQTT topics subcription with JSON parser
On the [aplication_manager.c]{https://github.com/makers-upv/smartpill-avriot/blob/develop/AVR_IoT_Kit/AVRIoT.X/mcc_generated_files/application_manager.c} could be found the modified version of *subscribeToCloud()* to subscribe to "dispensepill" custom topic and how it is linked to a custom callback *receiveddispenseFromCloud()* in which the data from the JSON is extracted.

### IoTPill.h
On this header are defined the main structures used to control the data recieved and sended.

# Comunication Protocol
### AWS → IoT Board → Arduino
The well services will trigger AWS to send by MQTT to IoT Board a JSON formated string that has this parts:
```json
{
    "cmd": "dispensepill",
    "npills": 2,
    "intake": {
        "time": "morning"
    },
    "pills": {
        "1": {
            "pill": "Ibuprofeno",
            "qty": 1,
            "deposit": 1,
            "weight": 200
        },
        "2": {
            "pill": "Paracetamol",
            "qty": 2,
            "deposit": 2,
            "weight": 500
        }
    }
}
```
 and the IoT board will send by USART to the Arduino:
 ```
 D Ibuprofeno 1 1 200 D Paracetamol 2 2 500 \n
 ```
 
 ### Arduino → IoT Board → AWS
 The arduino will send to the command "pill " and if it was incorrect or correct the delivery by adding a "1" if is okey:
 ```
 pill 1
 ```
 This message will be processed by the IoT Board  taking into acount the intake send and will send the following JSON  to AWS
 ```json
 {
    "time":"morning",
    "state": "ok"
 }
 ```
 AWS will send the log with Lambda funtions trigered to the Web service
