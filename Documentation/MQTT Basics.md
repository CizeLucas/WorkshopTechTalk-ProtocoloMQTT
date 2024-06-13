# MQTT Basics

Created by: Cizé Lucas
Last edited: June 13, 2024 3:55 PM
Tags: Post

### Message Queuring Telemetry Transport (Transporte de filas de mensagens de telemetria)

- Protocolo Binário
- Eficiente e Escalável
- Uni-Direcional ou Bi-Direcional
- Independe dos tipos de dados (JSON, Texto, HTML, imagens (fragmentos de vídeos) e etc)
- Baseado em Push Communication
- Construído para Dispositivos restritos (microcontroladores e embarcados)
- Baseado em comunicações persistentes TCP/IP
    - TCP/IP já assegura transmissão de dados de forma confiável, ordenada e com checagens de erro
- Seguro → Criptografia configurável via TLS/SSL
- Padrão de Publicação / Subscrição
- HTTP → Request & Response Methods    VS    MQTT → Publish & Subscribe Methods
- Conexões entre clientes MQTT são gerenciadas por um “broker”
- Aplicações: IOT, Indústrias, Automação Residencial, Logística e Transporte

### Fontes para estudos sobre MQTT:

- [https://mqtt.org/](https://mqtt.org/)
- HiveMQ
- MQTT Essentials ([https://www.hivemq.com/mqtt/](https://www.hivemq.com/mqtt/))
- [https://youtube.com/playlist?list=PLRkdoPznE1EMXLW6XoYLGd4uUaB6wB0wd&si=M3eDn8TdICfrRLKd](https://youtube.com/playlist?list=PLRkdoPznE1EMXLW6XoYLGd4uUaB6wB0wd&si=M3eDn8TdICfrRLKd)
- [https://docs.aws.amazon.com/pt_br/iot/latest/developerguide/mqtt.html](https://docs.aws.amazon.com/pt_br/iot/latest/developerguide/mqtt.html)

### Protocolos Similares/Relacionados:

- HTTP
- Web Sockets
- AMQP
- XMPP
- Co WEB
- Kafka