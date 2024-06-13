# Criação da VM na Azure

Created by: Cizé Lucas
Last edited: June 13, 2024 4:32 PM

## 1) Criar a Máquina Virtual:

1.1) Certifique-se que sua Inscrição de Estudante Azure para pagamento (e seu crédito) está propriamente configurado e aparecendo no Portal Azure, para isso:

Acesse “**Gerenciamento de custo + cobrança**” e na aba lateral procure por “**Benefícios (prévia)**”

1.2) Navegue para “Máquinas Virtuais” através da barra de pesquisa no topo do Portal e na página que carregar clique em “+ Criar”

1.3) Agora, na página de configurações de “**Básico**”, faça:

1.3.1) Primeiramente selecione sua assinatura “Azure para Estudantes” e crie um grupo de recursos para sua VM

1.3.2) Sua “Imagem” (S.O.) deve ser a Ubuntu Server 22.04 LTS - x64 Gen2

1.3.3) O “Tamanho” deve ser a “Standard_B1s” pois esta é gratuita para assinaturas de estudantes*

1.3.4) Insira um nome de usuário administrador para sua VM no campo “Nome de Usuário”

1.3.5)  Gere um novo par de chaves SSH selecionando o “Formato SSH RSA” que deverá ser baixado ao final da configuração da VM em um diretório apropriado de forma que você não as perca futuramente**

1.3.5) Habilite as “Portas de entrada públicas” e selecione a porta 22 para SSH

* : Você não pagará pela máquina virtual, mas será cobrado uma pequena taxa (que será coberta pelos créditos de estudante) pelos serviços de Networking e Armazenamento

** : Caso você esteja utilizando Windows, As chaves devem ser salvas dentro da sua pasta de usuário para evitar problemas com permissões de acesso durante o uso das chaves SSH para acessar a VM. Todavia, caso esteja utilizando Linux, você não deve ter este problema.

1.4) Configuração de “**Discos**”:

1.4.1) Selecione o tamanho de disco de 30gb (menos espaço possível) e escolha o “SSD Standard”, deixando o resto como padrão

1.5) Configuração de “**Rede**”:

1.5.1) Verifique as configurações de Rede, especialmente o campo de IP público, conferindo se uma nova configuração de IP foi assinalada a sua VM corretamente

1.5.2) Marque a opção “Excluir o IP público e a NIC quando a VM for excluída” para excluir configurações de Netwoking quando sua VM for excluída e assim evitar cobranças adicionais

1.6) Configuração de “**Gerenciamento**”: Nada obrigatório a fazer

1.7) Configuração de “**Monitoramento**”:

1.7.1) (OPCIONAL) Caso deseje, habilite os “**Alertas**” para obter notificações e/ou emails quando alguma métrica de uso que você especificar for atingida (Observação: Note que habilitar essa função gerará um pequeno custo mensal adicional)

1.8) Configuração de “**Avançado**”: Nada obrigatório a fazer

1.9) Configuração de “**Marcas**”: Nada obrigatório a fazer

1.10) Finalmente, na aba de “**Revisar + Criar**”, suas configurações serão verificadas e caso não hajam conflitos, você pode criar sua VM (Observação: Nesse momento você deve baixar suas chaves SSH)

2) Após a criação da Máquina virtual, clique em “**Ir para o recurso**”, onde faremos mais algumas configurações:

2.1) Na coluna de configurações ao lado esquerdo vá em “**Rede**” e selecione “**Configurações de Rede**”, onde você deve clicar em “**+ Criar regra de portas**” e adicionar regra de portas de entrada (Inbound rules), **permitindo** a entrada de protocolo **TCP** nas portas **1883, 8883 e 9001** fazendo:
    2.1.1) Inserindo “1883,8883,9001” no campo “**Intervalos de porta de destino**”, 
    2.1.2) Selecionando “**TCP**”, 
    2.1.3)Definindo a “**Ação**” como “**Permitir**”,
    2.1.4) Preenchendo o “**Nome**” com “PermitirPortasMQTT” (ou qualquer outro que respeite as regras de nomeação)

2.2) Novamente na coluna de configurações ao lado esquerdo vá em “**Ajuda**” e selecione “**Redefinir senha**”, selecione a opção “**Redefinir senha**” (”Reset Password”), verifique se o **nome de usuário adminstrador da VM está preenchido** no campo “**Usuário**” (“Username”), **defina a senha que você preferir** e clique em “**Atualizar**” (”Update”).

## Termos importantes:

### O protocolo Secure Shell (SSH) **é um método para enviar comandos com segurança a um computador em uma rede não segura**. O SSH usa criptografia para autenticar e criptografar conexões entre dispositivos.