# QoS e Segurança

Created by: Cizé Lucas
Last edited: June 11, 2024 9:39 PM

**Quality of Service (QoS):** é um acordo feito entre o cliente e o Broker que define o nível de garantia de entrega de uma determinada mensagem

1. QoS 0 → Ao máximo uma vez
2. QoS 1 → Ao menos uma vez
3. QoS 2 → Exatamente uma vez

Entenda por entrega de mensagem tanto a transmissão no sentido publicador → broker quanto no sentido broker → inscrito, ou seja, o QoS de uma mensagem rege a garantia de entrega em todo o percurso, do cliente publicador até o incrito. Vale ressaltar que é possível fazer um “downgrade” de QoS caso o cliente esteja inscrito em um nível de QoS inferior ao nível da mensagem que foi recebida pelo broker, entretanto essa prática não é muito encorajado pois pode levar ao recebimento de mensagens duplicadas. 
Mais um detalhe importante: **O broker é capaz de armazenar as mensagens** com QoS 1 ou 2 para um cliente que já tenha estabelecido uma conexão de sessão persistente anteriormente mas que no momento se encontra temporariamente offline, dessa forma, quando este cliente se reconectar ao broker novamente, receberá as mensagens que foram enviadas ao tópico enquanto estava com offline

Mais detalhes sobre os níveis de QoS:

1. QoS 0: Mensagens são enviadas com nenhuma garantia de recebimento, ou seja, não haverá posterior acompanhamento ou confirmação de recebimento da mensagem
2. QoS 1: Mensagens são enviadas até que o destinatário retorne um pacote PUBACK (Publish Acknowledgement ↔ Reconhecimento de Publicação) com o ID da mensagem recebida, ou seja, caso esse pacote por algum motivo não chegue ao remetente da mensagem, está poderá ser recebida diversas vezes, daí vem o nome “Ao menos uma vez” 
3. QoS 2: Mensagens são enviadas e um handshake com outros 3 pacotes adicionais é iniciado entre remetente e destinatário, são esses os:
    1. PUBREC (Publish Recived)
    2. PUBREL (Publish Release)
    3. PUBCOMP (Publish Complete)
    
    Garantido assim o recebimento da mensagem exatamente uma vez
    

**=====================================================**

Autenticação, Autorização e Segurança:

1) Autenticação: É o processo de identificar um usuário e dispositivo. Nessa tarefa o broker Mosquitto nos ajuda com um sistema de autenticação com usuário e senha nativo, a ferramenta mosquitto_passwd, além disso, também há suporte para plugins externos para autenticação via tokens JWT por exemplo

2) Autorização: É o processo de permitir ou negar o acesso de um usuário ou dispositivo a um recurso específico. Para isso, o broker Mosquitto implementa uma Lista de Controle de Acesso (ACL), que nos permite configurar permissões para cada usuário cadastrado previamente no broker. Não implementaremos esse esquema na parte prática devido a sua maior complexidade e porque nosso sistema de demonstração será simples.

3) Criptografia: A criptografia é uma peça chave para permitir que os pacotes que estão trafegando na rede não sejam interceptados e lidos por qualquer um, então podemos implementar o esquema de criptografia SSL/TLS, o mesmo esquema usado na web com HTTPS por exemplo, gerando e configurando certificados no servidor (broker) e clientes para garantir segurança ao nosso sistema