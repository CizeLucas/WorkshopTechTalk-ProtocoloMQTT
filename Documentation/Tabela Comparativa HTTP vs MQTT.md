# Tabela Comparativa HTTP vs MQTT

Created by: Cizé Lucas
Last edited: June 10, 2024 7:30 PM

| Características | HTTP | MQTT |
| --- | --- | --- |
| Modelo de Comunicação | Requisição - Resposta (via URIs) | Publicação - Assinatura (via Tópicos) |
| Distribuição padrão de mensagens | Um para Um | Um para Vários |
| Uso de Recursos e Overhead | Alto (Cabeçalhos grandes e handshakes custosos) | Baixo (Cabeçalhos reduzidos e comunicação binária) |
| Consumo de Banda e Latência | Alta (a cada requisição geralmente é aberta uma nova conexão TCP) | Baixa (Conexão TCP persistente) |
| Persistência de dados | Não (precisa implementar) | Sim (Retenção de mensagens) |
| Garantia do recebimento de dados | Não (precisa implementar) | Sim (QoS 1 e 2) |
| Monitoramento de clientes | Não | Sim |
| Segurança | Sim (TLS/SSL, mas necessitaria implementar Autenticação) | Sim (TSL/SSL e Autenticação) |
| Escalabilidade | Escalável (mas necessitaria de diversas otimizações) | Escalável (Graças ao modelo de comunicação e broker) |
| Comunicação de dados grandes | Sim (Limitação na ordem de Gigabytes) | Não (Mensagem MQTT limitada a 256MB) |
| Ideal para | Dados de texto e arquivos grandes em menores frequências | Dados pequenos e binários em maiores frequências |
| Exemplos de Uso | Aplicações Web, APIs e Transferência de Arquivos | Aplicações M2M, IoT e Telemetria |

Outras menções relevantes: CoAP (Constrained Application Protocol), XMPP (Advanced Message Queuing Protocol) e AMQP (Advanced Message Queuing Protocol)

CoAP usa o modelo de comunicação Requisição - Resposta (similar ao HTTP)

XMPP não implementa a persistência e QoS para suas mensagens

AMQP é um protocolo mais voltado a fila de mensagens, como comunicações entre diferentes sistemas e aplicações em sistemas back-end maiores, por isso seu uso em IoT é mais raro

# Diferenças:

### MQTT vs HTTP:

→ Criado para habilitar a transferência de documentos através da internet

Design para IOT vs DOCUMENTOS

Tipo de Conteúdo: BINÁRIO (QUALQUER) vs TEXTO

Distribuição: um para vários vs um para um

Confiabilidade: QOS 0/1/2 vs precisa ser implementado

BIDIRECIONAL vs UNIDIRECIONAL

Arquitetura de TÓPICOS vs URIs

Monitoramento de Estado dos Clientes SIM vs NÃO

ASSÍNCRONA baseada em EVENTOS vs SÍNCRONA

SISTEMA DE AUTENTICAÇÃO e AUTORIZAÇÃO: SIM vs NÃO

broker armazena mensagens vs armazenamento precisa ser implementado

Tamanho de mensagem mínimo: 2 BYTES vs 8 BYTES

Tamanho máximo de mensagem: 256MB vs SEM LIMITE*

### MQTT vs WebSockets:

→ Criado para habilitar comunicação bidirecional entre clientes e servidores web

Design para IOT vs Comunicações bidirecionais

PUBLISH/SUBSCRIBE vs BIDIRECIONAL

Arquitetura de TÓPICOS vs 

Distribuição: um para vários vs um para um

SISTEMA DE AUTENTICAÇÃO e AUTORIZAÇÃO: SIM vs NÃO

ASSÍNCRONA baseada em EVENTOS vs ASSÍNCRONA

Monitoramento de Estado dos Clientes SIM vs NÃO

Tamanho de mensagem mínimo: 2 BYTES vs 2 ou 6 BYTES (dependendo do modo)

broker armazena mensagens vs armazenamento precisa ser implementado