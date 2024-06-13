# Deploy do Broker Mosquitto com Criptografia SSL/TLS

Created by: Cizé Lucas
Last edited: June 13, 2024 4:43 PM

## Observação: Este conteúdo ainda nao

# 1. Criar os arquivos de autenticação e configuração do broker Mosquitto

1.1 Navegue para o diretório /home/{nomeDeUsuario} de sua VM Ubuntu, **crie uma nova pasta** mosquitto-docker e após isso navegue para dentro dela

1.2 Na sua recém criada pasta, crie um arquivo “mosquitto.conf” dentro da pasta config fazendo:

mkdir config

nano config/mosquitto.conf

e cole a seguinte configuração:

```
# Configura a persistencia de mensagens
persistence true
persistence_location /mosquitto/data/
persistence_file mosquitto.db

# Configura Autenticacao
password_file /mosquitto/config/pwfile
allow_anonymous false

# Porta padrao MQTT (MQTT)
listener 1883

# Porta MQTT via TLS (MQTTS)
listener 8883
# cafile /path/to/your/ca.crt
# certfile /path/to/your/mosquitto.crt
# keyfile /path/to/your/mosquitto.key

# Porta para MQTT via WebSockets (WS)
listener 9001
protocol websockets
# cafile /path/to/your/ca.crt
# certfile /path/to/your/mosquitto.crt
# keyfile /path/to/your/mosquitto.key
```

Observação: caso seu Ubuntu não tenha o 

- [ ]  TODO: explicar cada linha do arquivo de configuração

1.3 Após isso, crie também um arquivo “pwfile” dentro da pasta config fazendo:

nano config/pwfile

# 2. Criar o Docker File

2.1 Dentro da pasta mosquitto-docker, crie o docker file com o comando:

nano docker-compose.yaml

e cole a seguinte configuração:

```yaml
version: '3'
services:
  mosquitto:
    container_name: mosquitto
    image: eclipse-mosquitto:2.0.18
    restart: always
    ports:
       - "1883:1883" # Mapeia a porta MQTT padrão 1883 da maquina host para a porta 1883 do contêiner  
       - "8883:8883" # Mapeia a porta MQTTS padrão 8883 da maquina host para a porta 8883 do contêiner
       - "9001:9001" # Mapeia a porta de MQTT WebSockets 9001 da maquina host para a porta 9001 do contêiner
    volumes: # Para persistencia de dados
      - /home/{nomeDeUsuario}/mosquitto-docker/config/mosquitto.conf:/mosquitto/config/mosquitto.conf # Mapeia o arquivo de configuração
      - /home/{nomeDeUsuario}/mosquitto-docker/config/pwfile:/mosquitto/config/pwfile # Mapeia o diretório do arquivo de usuarios e senhas
      - /home/{nomeDeUsuario}/mosquitto-docker/data:/mosquitto/data # Mapeia o diretório de dados
      - /home/{nomeDeUsuario}/mosquitto-docker/log:/mosquitto/log # Mapeia o diretório de logs
```

Observação: não esqueça de **ALTERAR {nomeDeUsuario}** para o nome se usuário configurado em sua VM

- [ ]  TODO: explicar cada linha do arquivo de configuração

# 3. Instalar o Docker Engine em sua VM

3.1 Siga os tutoriais da DigitalOcean de como instalar Docker em um sistema Ubuntu via terminal:

[https://www.digitalocean.com/community/tutorials/how-to-install-and-use-docker-on-ubuntu-20-04-pt](https://www.digitalocean.com/community/tutorials/how-to-install-and-use-docker-on-ubuntu-20-04-pt)

OU

[https://www.digitalocean.com/community/tutorials/how-to-install-and-use-docker-on-ubuntu-22-04](https://www.digitalocean.com/community/tutorials/how-to-install-and-use-docker-on-ubuntu-22-04)

Dependendo de sua versão do Ubuntu (confira usando o comando `lsb_release -a`  na propriedade “release”)

# 4. Construir e Subir seu container Docker

4.1 Agora, confira sua estrutura de arquivos que deve se parecer com isso:

home

{nomeDeUsuario}

mosquitto-docker

***docker-compose.yaml***

config

***mosquitto.conf***

***pwfile***

4.2 Dentro da mesma pasta onde você criou o arquivo docker-compose.yaml (pasta mosquitto-docker), execute o comando:

sudo docker compose up --detach

após isso, seu container deve estar construído e rodando em background (devido a flag --detach), para nos certificarmos, devemos executar o comando:

docker ps

e devemos ver as informações do container que acabamos de criar

![Untitled](imagens/Deploy%20do%20Broker%20Mosquitto%20com%20Criptografia%20SSL%20TL%20dcd8fa68de0948dbbb0fb78a7bca9f01/Untitled.png)

# 5. Configurar credenciais de usuário e senha para autenticar com o Broker

## Agora, precisaremos executar comandos dentro do container que acabamos de criar e assim configurarmos o usuário e senha

Observação: Para mais informações sobre a ferramenta mosquitto_passwd, acesse: [https://mosquitto.org/man/mosquitto_passwd-1.html](https://mosquitto.org/man/mosquitto_passwd-1.html)

5.1 Devemos executar o comando

sudo docker exec -it mosquitto sh

Observação: o comando acima executa (exec) um comando (sh ↔ shell / terminal) em uma interface interativa de entrada padrão (-it) no container (mosquitto), ou seja, abre o terminal de comandos do container Mosquitto

5.2 Uma vez dentro do terminal do Mosquitto, podemos proseguir nossa configuração executando:

mosquitto_passwd -c /mosquitto/config/pwfile {nomeDeUsuarioDesejado}

Observação: o {nomeDeUsuarioDesejado} NÃO deve conter “:”

após isso, será necessário entrar (e confirmar) a senha referente a este usuário

5.3 Para corrigir o aviso :

```
Warning: File /mosquitto/config/pwfile has world readable permissions. Future versions will refuse to load this file.
To fix this, use `chmod 0700 /mosquitto/config/pwfile`.
Warning: File /mosquitto/config/pwfile owner is not root. Future versions will refuse to load this file.To fix this, use `chown root /mosquitto/config/pwfile`.
Warning: File /mosquitto/config/pwfile group is not root. Future versions will refuse to load this file
```

devemos, ainda dentro do shell Mosquitto, executar os comandos:

chmod 0700 /mosquitto/config/pwfile
chown :root /mosquitto/config/pwfile
chown root /mosquitto/config/pwfile

que basicamente irão modificar as propriedades de acesso, gravação, grupo e proprietário do arquivo, fazendo com que o acesso a ele seja limitado ao usuário root por razões de segurança

5.4 Execute o comando:

exit

para sair do shell do container Mosquitto.

5.5 Checando o trabalho: para confirmar que o usuário e senha foi propriamente configurado, acesse o arquivo “pwfile” dentro da pasta “config” com o comando:

sudo nano pwfile

e você deve obter: {nomeDeUsuarioDesejado} : {hashDaSenhaEscolhida}

5.5 Reinicie o container para aplicar as configurações corretamente com o comando:

docker restart mosquitto

## X) Configurando criptografia de mensagens MQTT via TLS-SSL com broker Mosquitto:

x.1) Crie uma Chave CA para o cliente com o comando:

openssl genrsa -des3 -out ca.key 2048

e insira uma senha com 4 a 1024 caracteres para essa chave

x.2) Crie um Certificado CA baseado na chave CA criada no passo anterior:

openssl req -new -x509 -days 365 -key ca.key -out ca.crt

após isso, você deve inserir a senha da Chave CA definida anteriormente e definir algumas informações para o certificado:

![Untitled](imagens/Deploy%20do%20Broker%20Mosquitto%20com%20Criptografia%20SSL%20TL%20dcd8fa68de0948dbbb0fb78a7bca9f01/Untitled%201.png)

Observação: O Common Name deve ser o seu nome de Usuário de Usuário da máquina OU Endereço IP/Domínio (DNS).

BR

CEARA

.

FEDERAL UNIVERSITY OF CEARA

PET

20.119.80.200

your_email@gmail.com

x.3) Criando a chave do Broker (sem criptografia):

openssl genrsa -out mosquitto.key 2048

x.4) Criar o Certificado do Broker com a chave do broker criada no passo anterior:

openssl req -new -out server.csr -key mosquitto.key

Após isso, você definirá algumas opções da mesma forma que anteriormente e poderá deixar os “ ‘extra’ attributes ” sem vazios:

![Untitled](imagens/Deploy%20do%20Broker%20Mosquitto%20com%20Criptografia%20SSL%20TL%20dcd8fa68de0948dbbb0fb78a7bca9f01/Untitled%202.png)

x.5) Finalmente, deveremos criar um Certificado do Broker:

openssl x509 -req -in server.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out mosquitto.crt -days 360

### Observaçõe: As informações dos certificados não devem ser completamente iguais (pois pode ocasionar erros)