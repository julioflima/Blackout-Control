# Blackout-Control
Xbee, Arduino, Point-to-Multpoint, 802.15.4

### Mandatory

0 - É necessária um canal para a rede PAN, todos os dispositivos devem ter o mesmo valor, o CH utilizado nesse projeto foi:
>CH = C

1 - É necessária um ID para a rede PAN, todos os dispositivos devem ter o mesmo valor, o ID utilizado nesse relatório foi:
>ID = 2017

2 - É necessária um a verificação se há um coordinator na rede, para isso todos os dispositivos devem estar com o parâmetro A1 na seguinte configuração, de modo que se os ID e CH forem os mesmos haverá comunicação:
>A1 = 100

3 - É necessária um a verificação se há um coordinator na rede, para isso todos os dispositivos devem estar com o parâmetro A1 na seguinte configuração, de modo que se os ID e CH forem os mesmos haverá comunicação:
>A2 = 0100

4 - É necessária a configuração dos parâmetros CE e SM para determinação se Coordinator, Router ou End device, esses determinam se são do tipo coordinator e se entram em modo sleep, respectivamente. Nenhum outro dispositivo pode ser coordinator se não tiver CM = 1. Router não podem ser coordinators. Apenas end devices podem entrar em modo sleep.
Coordinator:
> CM = 0 , SM = 0
End device:
> CM = 0 , SM = 0 

5 - Com o objetivo de configurar uma rede API, deve ser habilitado o parâmetro AP:
>AP = 1

6 - É necessária a configuração dos endereços de envio, para uma rede do tipo API, utilizando apenas um coordinator o endereço dele deve ser fixo e único enquanto que os demais routers e end devices devem ser um só, assim garantindo o envio por broadcast. Porém cada dispositivo terá seu único parâmetro MY garantindo assim o unicast entre os dispositivos.
Coordinator:
> DH = 0 , DL = FFFF , MY=0

End device:
> DH = 0 , DL = 0 , MY=1

7 - Com o objetivo de manter o sistema seguro, foi adicionada uma encriptação no protocolo, habilitando o parâmentro EE e repetindo a mesma senha em todos os dispositivos. 
>EE = 1

>KY = 1FF2FF3FF    

8 - Para ser produzido o broadcast, deve ser ser colocado como parâmetro de endereço 64-bit, os seguintes códigos:
>DH = 00 00 00 00

>DL = 00 00 FF FF

9 - Para ser produzido um envio do tipo unicast, deve ser colocado como parâmetro de endereço 64-bit, os seguintes códigos:
>DH = SH

>DL = SL

10 - Com o objetivo do controle de dispositivo dentro de uma rede a distância, devem ser enviados comandos AT, com o uso de um micro controlador e de um biblioteca que auxilie o envio de frames com as respectivas tecnologias.

11 - O envio de frames com a plataforma XCTU, primeiramente deve ser selecionado o tipo de frame 0x17 - Remote AT Command. Em seguida preenchido os endereços de envio em caso de unicast e broadcast ver os casos 8 e 9.

12 - O comando AT enviado deve ser preenchido apenas pela sigla e não pelo adjetivo AT. Uma sigla é D0 que representa o estado da porta digital 0. E seu parâmetro deve ser inserido em HEX caso trate-se de um número.

13 - Devido a facilidade oferecida foram utilizados resistores de pull up na entrada do Xbee, para isso deve ser modificado parâmetro PR:
>PR = 1

14 - A frequência de monitoramento da variação das entradas do Xbee é determinado pelo parâmetro IR. Foi adotado o valor mínimo para melhorar a precisão de atuação.
>IR = 0

15 - O monitoramento da variaveis de entrada do Xbee é determinado pelo parâmetro IC, que deve ser configurado de acordo com a porta que deseja monitorar. Essa configuração é do tipo interrupção de entrada que dispara o acionamento de um endereço especifico contido em IA.

16 - Para resetar o Xbee deve ser conectar o pino 5 ao pino 10 com firmeza por alguns segundos.

17 -

### Firmware
Modem     | Function Set | Version
--------- | ------------ | ------
XB24      | 802.15.4     | 10ef

### Coordinator
Parameter            | Value        | Comments
-------------------- | ------------ | -----------
CH (Channel)         | 0x0C         | Identical
ID (PAN ID)          | 0x2017       | Identical
DH (Second. Address) | 0x0	        | Identical
DL (Second. Address) | 0x0	        | Identical
MY (Source Address)  | 0x0          | Unique
CE (Coord. Enable)   | 1  	        | Unique
A2 (Coord. Assoc.)   | 0x04         | Unique
NI (Name)	           | COORD_STAC   | Unique
AP		               | 1	          | Identical
EE	             	   | 1	          |	Identical
KY		               | 1FF2FF3FF    | Identical

# End Device
Parameter            | Value        | Comments
-------------------- | ------------ | -----------
CH (Channel)         | 0x0C          | Identical
ID (PAN ID)          | 0x2017        | Identical
DH (Second. Address) | 0x0	        | Identical
DL (Second. Address) | 0x0	          | Identical
MY (Source Address)  | 0x01          | Unique
CE (Coord. Enable)   | 0  	          | Identical to end devices
A1 (End Dev Assoc.)  | 0x04          | Identical to end devices
NI (Name)	           | END_STAC_01   | Unique
AP (Mode)	           | 1	            | Identical
EE (Secure?)	       | 1		          | Identical
KY (Key)             | 1FF2FF3FF     | Identical

### Comunication

### Network
>Broadcast

>Unicast

#### Addresses:
>Coordinator = 0013A20040915718

>Router_0001 = 0013A2004091572D

>Router_0002 = 0013A2004091572D

>Router_0003 = 0013A2004091572D

>Router_0004 = 0013A2004091572D

>Router_0005 = 0013A2004091572D

>Router_0006 = 0013A2004091572D

>Router_0007 = 0013A2004091572D
