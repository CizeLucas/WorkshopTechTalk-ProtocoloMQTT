# Arquitetura e Funcionamento

Created by: Cizé Lucas
Last edited: June 11, 2024 9:37 PM

**Pacotes MQTT:** MQTT Packets são conjuntos de informações binárias compostas pelos seguintes elementos:

![image4.jpg](imagens/Arquitetura%20e%20Funcionamento%20b083881b42aa45bfbe1e44ed4311ac48/image4.jpg)

 

1) O “Fixed Header” são os primeiros 2 a 5 bytes do pacote MQTT e é composto por:

    1.1) “Control Field” é obrigatório em todos os pacotes e armazena no

   1.1.1) “Packet Type” Informações sobre o **tipo de pacote** nos seus primeiros 4 bits e suas **flags** nos ultimos 4 (totalizando 1 byte ↔ 8 bits). A seguir estão são exemplos de tipo de pacotes: 

| Nome | Valor | Direção | Descrição |
| --- | --- | --- | --- |
| CONNECT | 1 | Cliente -> Broker | Cliente requisita conexão |
| CONNACK | 2 | Broker -> Cliente | Reconhecimento de Conexão |
| PUBLISH | 3 | Ambas | Publicação de mensagem |
| SUBSCRIBE | 8 | Cliente -> Broker | Requisição de inscrição |
| PINGREQ | 12 | Cliente -> Broker | Teste de conexão com o broker* |
| DISCONNECT | 14 | Cliente -> Broker | Cliente está desconectando |

\* : quando o Broker recebe o pacote de PINGREQ, responde para o cliente um pacote de PINGRESP

        1.1.2) O “Control Flags” carregam os metadados do pacote e representam diferentes informações dependendo do contexto e tipo do pacote.

→ Exemplo de Pacote de controle: **0b00110011 = 0x33 → PUBLISH, DUP=0, QoS=1, Retain=1**.

        1.2) Remaining Lenght: Informa a quantidade restante de bytes da mensagem MQTT e seu tamanho varia de 1 a 4 bytes dependendo do tamanho da mensagem

2) O “Variable Header”, assim como seu nome indica, varia seu conteúdo e tamanho de acordo com o pacote em questão. No caso de um pacote CONNECT, temos aproximadamente 10 bytes onde são especificados o nome do protocolo, seu tamanho e versão, detalhes da conexão (QoS, retain, Will flag e Clean Session) e Keep Alive.

3) O “Payload” é a representação binária da mensagem transmitida via mensagens MQTT, obviamente seu tamanho varia dependendo do pacote e também pode ser inexistente. 
Exemplo: **0x43 0x65 0x64 0x61 0x6c 0x6f → Cedalo** (string ASCII codificada em hexadecimal)

Abaixo segue um exemplo de um pacote CONNECT do protocolo MQTT v3.1.1 (32 bytes):

![Untitled](imagens/Arquitetura%20e%20Funcionamento%20b083881b42aa45bfbe1e44ed4311ac48/Untitled.png)

**=====================================================**

**Arquitetura de Publicação e Inscrição:** Nesse modelo de arquitetura, existem aqueles que publicam novas mensagens para o Broker (os ”publicadores”) e os inscritos que podem receber essas novas informações através do Broker

**Tópicos:** Os tópicos são a forma de separar os diferentes tipos de “assuntos” e dessa forma o Broker consegue rotear e transmitir essas mensagens baseado nos interesses (inscrições) de cada cliente. Tópicos são uma string formada por vários níveis separados por “/”, similar aos URLs que utilizamos para navegar na Web. No início do tópico, o nível deve ser mais geral e englobará mais recursos, mas chegando ao seu fim, trará a especificidade do tipo de mensagem que estará disponível nele, vejamos os exemplos:

myhome**/**groundfloor**/**livingroom**/**temperature (4 níveis)

Germany**/**Bavaria**/**car**/**2382340923453**/**latitude (5 níveis)

5ff4a2ce-e485-40f4-826c-b1a5d81be9b6**/**status (2 níveis)

→ Características e Boas Práticas para definir tópicos:

- Tópicos são dinâmicamente criados e excluidos pelo Broker, não há necessidade nenhuma de configura-los de maneria prévia.
- Cada nível do tópico deve conter ao menos um caractere;
- Começar e terminar tópicos com “/” é possível mas seu uso NÃO recomendado;
- Tópicos podem incluir espaços e são sensíveis a capitalização (letras maiúsculas), mas seu uso NÃO é recomendado;
- Evite usar caracteres que não estão presentes na tabela ASCII
- Tópicos podem conter wildcards (tópicos curingas): “+” e ”#”.

**→** Tópicos Curingas (Wildcards Topics) são utilizados por clientes que desejam se inscrever em uma variedade de tópicos que seguem um determinado padrão ao mesmo tempo. Vamos entender com mais detalhes:

- “ **+** “:  é um Wildcard de único nível que deve ser usado dentro do tópico e se increve em todos os tópicos que seguem o padrão apenas do resto do tópico e não do nível onde foi utilizado o wildcard “+”. Isso é melhor entendido com um exemplo:
    **casa/terreo/+/temperatura** faz com que o cliente receba informações dos tópicos:
        ☑️ casa/terreo/cozinha/temperatura
        ☑️ casa/terreo/quarto/temperatura
        ❌ casa/andar1/sala/luminosidade
        ❌ casa/andar1/quarto/temperatura
        ❌ casa/terreo/cozinha/geladeira/temperatura
- “ # “: é um Wildcard de multi nível que deve ser usado apenas ao final do tópico e se inscreve em todos os topicos os quais o início correspondem com o tópico curinga. Isso é melhor entendido com um exemplo:
    **casa/terreo/#** faz com que o cliente receba informações dos tópicos:
        ☑️ casa/terreo/sala/temperatra
        ☑️ casa/terreo/quarto/temperatura
        ☑️ casa/terreo/sala/luminosidade
        ❌ casa/andar1/cozinha/temperatura
        ❌ torreeifel/terreo/temperatura

**=====================================================**

**Protocolos de rede utilizados pelo MQTT: TCP (MQTT e MQTTS) e WebSockets (WS e WSS)**

As duas formas de conexão são confiáveis, permanecem abertas durante toda a sessão, permitem o uso de SSL/TLS para criptografia de mensagens e não interferem diretamente no funcionamento do protocolo MQTT. No entanto, existem diferenças importantes que fazem o uso de um em detrimento do outro vantajoso para determinadas aplicações:

1. **WebSockets**: Geralmente utilizados quando o tráfego de dados será maior e quando uma baixa latência é essencial. WebSockets também são vantajosos em ambientes onde a compatibilidade com redes restritas e firewalls é crítica, pois normalmente utilizam as portas 80 (WS) e 443 (WSS), que são portas padrão para tráfego HTTP/HTTPS e, portanto, têm menos probabilidade de serem bloqueadas.
2. **TCP**: Utilizado amplamente devido à sua simplicidade e eficiência para a maioria das aplicações IoT que não requerem as características específicas oferecidas pelos WebSockets. A comunicação direta via TCP é suficiente e eficiente para muitos casos de uso onde as portas dedicadas 1883 (MQTT) e 8883 (MQTTS) são abertas e configuradas adequadamente.