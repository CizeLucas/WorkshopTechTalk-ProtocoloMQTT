# Introdução ao MQTT

Created by: Cizé Lucas
Last edited: June 12, 2024 11:07 AM

# História:

O protocolo foi criado inicialmente em **1999**, na virada do século, por **Andy Stanford-Clark**, que na época era **engenheiro e pesquisador de Tecnologia da Informação** na **IBM**, e **Arlen Nipper**, que na época trabalhava na área de **pesquisa e desenvolvimento de micro computadores** na empresa **Eurotech.** Juntos eles trabalharam na demanda de desenvolver uma forma de monitorar o estado de oleodutos remotos através de comunicação via satelite, ou seja, o protocolo deles deveria leve e robusto, habilitando o baixo consumo de energia pois os dispositivos eram alimentados por baterias e ainda assim sendo confiável, com boa entrega de mensagens e que ainda assim usasse uma baixa largura de banda. Após finalizado, o protocolo que se chamava inicialmente **MQ Telemetry Transport** era usado apenas internamente em produtos da IBM, mas em 2010, em sua versão 3.1, o protocolo foi liberado para uso público. Hoje o MQTT é mantido e desenvolvido pela OASIS (Organização para o Avanço dos Padrões de Informação Estruturada).

→ Um detalhe importante é que apesar de ter “MQ” no nome, que significa message queueing (fila de mensagens), o protocolo MQTT faz enfileiramento de mensagens apenas em casos específicos e ele não atua da mesma forma que o AMQP ou Kafka, protocolos que são próprios para filas de mensagens.

Open Sourcing através da licensa pública Eclipse, que permite a qualquer um usar e modificar o protocolo, contanto que essas modificações sejam documentadas e liberadas ao público com a mesma licença e permissões

Estandardização OASIS: Hoje o MQTT é mantido e desenvolvido pela OASIS (Organização para o Avanço dos Padrões de Informação Estruturada).

MQTT v3.1.1: Lançada em 2014, esta foi a primeira grande versão open source do protocolo  devido ao seu ótimo funcionamento e documentação, o que facilitou sua implementação

MQTT v5.0: Esta é outra grande versão do protocolo, lançada em 2019 e adicionou funcionalidades importantes como relatório de erros do Broker, subscrição compartilhada, relatório de erros e expiração de mensagens.

# Aplicações:

### Desenvolvimento:

A Diversidade de bibliotecas open-source que facilitam a implementação e comunicação do seu projeto de software com o protocolo MQTT abrem diversas possibilidades que outros protocolos não oferecem. Existem bibiliotecas para C, C++, C#, Go, Java, JavaScript, PHP, Python Rust e etc que, através da sua arquitetura assíncrona e baseada em eventos, pode dar mais funcionalidade a sua aplicação como por exemplo habilitar o seu sistema a se comunicar diretamente a vários microcontroladores, entrega de mensagens em tempo real para aplicações de mensageria ou notificações, obtenção de logs de sua aplicação em tempo real

### Smart Home:

O projeto Home Assistant é uma plataforma de automação residencial de código aberto que permite aos usuários controlar e automatizar dispositivos domésticos inteligentes. Ele pode ser instalado em diversos sistemas operacionais, como Linux, Windows e macOS, e é frequentemente utilizado em dispositivos Raspberry Pi. O Home Assistant suporta uma ampla gama de dispositivos e serviços, permitindo integração com luzes, termostatos, sensores, câmeras, assistentes de voz (como Google Assistant e Amazon Alexa), entre outros. Seu diferencial é ser voltado a privacidade de dados, pois estes não trafegam fora da sua rede local, ser open soure e dar suporte a automações avançadas por ser altamente customizavel e diversas integrações, dessa forma, o MQTT não poderia estar de fora….

## Indústria:

O MQTT se torna bastante relevante na indústria devido sua capacidade de operar na **conexão da intra-fábrica quanto na conexão entre fábricas** de forma **eficiente**, **escalável, com baixa latência e custo reduzido,** A disponibilidade de **Brokers de alta performance, disponibílidade e tolerantes a falhas** são bônus que facilitam ainda mais a adoção do MQTT.

O MQTT é fundamental na modernização da produção, capacitando fábricas inteligentes com seus recursos de **comunicação eficientes, confiáveis e seguros**. Ao facilitar a troca de dados em tempo real e a **interoperabilidade** entre diversos sistemas, o MQTT ajuda os fabricantes a obter maior eficiência, flexibilidade e capacidade de resposta em suas operações. À medida que a indústria transformadora continua a evoluir, o MQTT desempenhará um papel crucial na condução da transformação digital rumo a fábricas mais inteligentes e mais conectadas.