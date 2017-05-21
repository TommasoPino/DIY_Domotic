# DIY_Domotic

Questa repository ha lo scopo, al momento, di raccogliere tutto il materiale su cui sto 
lavorando e che ho usato per costruire la mia Casa Domotica personale in cui ho un server 
core su una RaspberryPi 3 che monta RaspBian Lite.

Ogni sotto cartella contiene il codice usato per un piccolo esperimento, il quale è descritto
anche per mezzo di immagini per replicare l'hardware.

## 000.Rpi3 Setup WiFi

Per prima cosa riporto di seguito le istruzioni di ciò che ho fatto per assicurarmi che la
mia Rasberrina possa essere sempre raggiunta per mezzo di ssh da parte del mio Mac. (se si 
usa Windows le istruzioni sono le stesse, solo che dovrete usare un software aggiuntivo 
"PuTTY", www.putty.org)

Inizziamo ipotizzando di avere seguito le istruzioni per avviare per la prima volta la RaspberryPi
con Raspbian Lite

quindi facciamo il login dopo l'avvio e iniziamo a settare la WiFi

scansioniamo tutti i segnali e cerchiamo il nostro SSID al quale ci collegheremo con la seguente istruzione

'''
$ sudo iw wlan0 scan | grep 'SSID' | tac
'''

Se troviamo la nostra rete possiamo procedere con aggiungerla nelle reti conosciute nel file:
"/etc/wpa_supplicant/wpa_supplicant.conf"

'''$ sudo nano /etc/wpa_supplicant/wpa_supplicant.conf


network={
ssid="il vostro SSID"
psk="relativa PWD"
proto=RSN
key_mgmt=WPA-PSK
pairwise=CCMP
auth_alg=OPEN
}
'''

Per assicurarci che non si cambi ip ad ogni riavvio, aggiungiamo al file: 
"/etc/dchpcd.conf"

'''$ sudo nano /etc/dchpcd.conf 

interface wlan0
 static ip_address=192.168.1.110/24
 static routers=192.168.1.254
 static domain_name_servers=8.8.8.8
 '''

inoltre per concludere, assicuriamoci che il power managment della RaspberryPi sia disattivato,
altrimenti dopo 15 minuti circa si perderà la connessione:

'''$ sudo nano /etc/rc.local

sleep 10
iwconfig wlan0 power off

exit 0
'''

A questo punto la vostra RaspberryPi ag ogni riavvio si collegherà alla rete con l'ip che 
avete scelto per lei.

## 001.RPi3 LED blinking

ho iniziato con 



![RPiBlinkLED](https://github.com/TommasoPino/DIY_Domotic/blob/master/img/RPiBlinkLED_bb.png)

![RPiBlinkLED](https://github.com/TommasoPino/DIY_Domotic/blob/master/img/RPiButtonLED_bb.png)
