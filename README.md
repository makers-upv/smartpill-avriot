# IoT-Pill-Dispenser
Repositiorio para el dispensador de pastillas inteligente del concurso Smart Medical Design de Microchip

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
 The arduino will send to the mesagge "PILL " and if it was incorrect or correct the delivery by adding a "1" if is okey:
 ```
 PILL 1
 ```
 This message will be processed by the IoT Board  taking into acount the intake send and will send the following JSON  to AWS
 ```json
 {
    "time":"morning",
    "state": "ok"
 }
 ```
 AWS will send the log with Lambda funtions trigered to the Web service