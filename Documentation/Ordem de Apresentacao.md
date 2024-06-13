# Ordem da Apresentação

Created by: Cizé Lucas
Last edited: June 12, 2024 11:07 AM

Introdução ao MQTT

- **O que é MQTT?**
    - Explicação básica do Message Queuing Telemetry Transport.
    - Breve histórico e contexto de criação.
    - Por que o MQTT é importante e suas principais aplicações.

Arquitetura e Funcionamento

- **Modelo de Publicação/Assinatura**
    - Diferença entre modelo pub/sub e o modelo cliente/servidor tradicional. (OK)
    - Componentes principais: broker, publishers, subscribers.
- **Fluxo de Mensagens**
    - Como as mensagens são enviadas e recebidas.
    - Tópicos e estrutura dos tópicos.

### **3. Características Técnicas**

- **Níveis de Qualidade de Serviço (QoS)**
    - Explicação dos três níveis de QoS (0, 1, 2).
    - Quando e por que usar cada nível.
- **Persistência e Retenção de Mensagens**
    - Mensagens persistentes e mensagens de retenção.
    - Utilização em diferentes cenários.

### **4. Segurança no MQTT**

- **Autenticação e Autorização**
    - Métodos de autenticação (username/password, certificados, etc.).
    - Controles de acesso e autorização de tópicos.
- **Criptografia**
    - Utilização de TLS/SSL para criptografia de dados.
    - Importância da criptografia em IoT e outros contextos sensíveis.

### **5. Implementações e Ferramentas**

- **Brokers MQTT Populares**
    - Mosquitto, HiveMQ, EMQX, etc.
    - Comparação de características e casos de uso.
- **Clientes MQTT**
    - Exemplos de bibliotecas em diferentes linguagens de programação (Python, Java, JavaScript).
    - Demonstrações de como conectar e interagir com um broker.

### **6. Casos de Uso e Aplicações Práticas**

- **Internet das Coisas (IoT)**
    - Exemplos de dispositivos IoT utilizando MQTT.
- **Aplicações Industriais**
    - Monitoramento e controle remoto.
- **Outras Áreas**
    - Utilização em aplicações móveis e sistemas de mensagens.

### **7. Vantagens e Desvantagens**

- **Vantagens do MQTT**
    - Baixa latência, baixo consumo de energia, simplicidade.
- **Limitações**
    - Escalabilidade, limitações de segurança em implementações básicas.

### **8. Futuro do MQTT e Conclusão**

- **Evoluções e Tendências**
    - Novas funcionalidades e melhorias esperadas.
- **Conclusão**
    - Recapitulação dos principais pontos.
    - Importância do MQTT na engenharia de computação e IoT.

### **9. Demonstração Prática (Opcional)**

- **Demo ao Vivo**
    - Configuração de um broker MQTT (ex: Mosquitto).
    - Exemplo de publicação e subscrição usando uma ferramenta ou script simples.