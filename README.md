# DIY_Domotic

Questa repository ha lo scopo, al momento, di raccogliere tutto il materiale su cui sto lavorando e che ho usato per costruire la mia Casa Domotica personale in cui ho un server core su una RaspberryPi 3 che monta RaspBian Lite.

Ogni sotto cartella contiene il codice usato per un piccolo esperimento, il quale è descritto anche per mezzo di immagini per replicare l'hardware.

__RaspberryPi SETUP Index__

* [Setup WiFi](#setup-wifi)
* [WiringPi Library](#wiringpi-library)

__Tutorials Index__
* [LED blinking](#led-blinking)

## RaspberryPi SETUP

### Setup WiFi

Per prima cosa riporto di seguito le istruzioni di ciò che ho fatto per assicurarmi che la mia Rasberrina possa essere sempre raggiunta per mezzo di ssh da parte del mio Mac. (se si usa Windows le istruzioni sono le stesse, solo che dovrete usare un software aggiuntivo "PuTTY", www.putty.org).

Inizziamo ipotizzando di avere seguito le istruzioni per avviare per la prima volta la RaspberryPi con Raspbian Lite.

Quindi facciamo il login dopo l'avvio e iniziamo a settare la WiFi.
Scansioniamo tutti i segnali e cerchiamo il nostro SSID al quale ci collegheremo con la seguente istruzione

```
$ sudo iw wlan0 scan | grep 'SSID' | tac
```

Se troviamo la nostra rete possiamo procedere e aggiungerla nelle reti conosciute nel file **/etc/wpa_supplicant/wpa_supplicant.conf**

```
$ sudo nano /etc/wpa_supplicant/wpa_supplicant.conf


network={
ssid="il vostro SSID"
psk="relativa PWD"
proto=RSN
key_mgmt=WPA-PSK
pairwise=CCMP
auth_alg=OPEN
}
```

Per assicurarci che non si cambi indirizzo IP ad ogni riavvio, aggiungiamo al file **/etc/dchpcd.conf** le seguenti istruzioni:

```
$ sudo nano /etc/dchpcd.conf 

interface wlan0
 static ip_address=192.168.1.110/24
 static routers=192.168.1.254
 static domain_name_servers=8.8.8.8
```

Infine, assicuriamoci che il power managment della RaspberryPi sia disattivato:

```
$ sudo nano /etc/rc.local

sleep 10
iwconfig wlan0 power off

exit 0
```

A questo punto la vostra RaspberryPi ad ogni riavvio si collegherà alla rete con l'IP che avete scelto per lei.

### WiringPi Library

Per controllare dal nostro codice in C/C++ la GPIO della RaspberryPi abbiamo bisogno di aggiungere una libreria. Il sito della libreria con alcuni esempi lo trovate [qui](http://wiringpi.com/).

Per installare una libreria, nel nostro caso **WiringPi** nella nostra RaspberryPi dobbiamo semplicemente eseguire le seguenti istruzioni:
```
$ sudo apt-get update
$ sudo apt-cache search wiringpi
```
se troviamo la libreria, allora possiamo procedere con il comando seguente (altrimenti guardate [qui](#estendiamo-la-repository)):

```
$ sudo apt-get install wiringpi -y
```

Al completamento dell'installazione possiamo eseguire il tutorial [qui](#led-blinking)

### Estendiamo la repository

Alcune applicazioni e librerie non sono direttamente presenti sulle liste raspbian, sarà quindi necessario aggiungere le liste di ricerca wheezy. Potete farlo nel file **/etc/apt/sources.list** aggiungendo alla fine del file le due stringhe con il comando che segue:
```
$ sudo nano /etc/apt/sources.list

deb http://archive.raspbian.org/raspbian wheezy main contrib non-free
deb-src http://archive.raspbian.org/raspbian wheezy main contrib non-free
```

### Clona la repository

Tutti i tutorial che seguono prevedono che la la repository che state visitando sia stata clonata, questo vi consente di compilare direttamente i file che si andranno ad analizzare in seguito. Potete copiarla dove volete, ma qui trovate le istruzioni che vi consiglio:

```
$ cd
$ mkdir Repos
$ cd Repos
$ git clone https://github.com/TommasoPino/DIY_Domotic
```

se non avete **git** installato, potete installarlo come fatto con la libreria [WiringPi Library](#wiringpi-library)
## Tutorials

### LED blinking

Questo tutorial consente principalmente di tutto di provare se la libreria [WiringPi](#wiringpi-library) sia stata installata correttamente.

Replicato l'Hardware mostrato nella figura seguente e compilato ed eseguito il file presente nella cartella **blinkLED/blinkWiringPi.c**,
potrete vedere il LED accendersi e spegnersi (blink) ogni mezzo secondo.

```C
#include <wiringPi.h>
#include <stdio.h>
int main (void)
{
  printf("Start program\n");
  wiringPiSetup () ;
  pinMode (0, OUTPUT) ;
  while(1)
  {
    digitalWrite (0, HIGH) ; delay (500) ;
    printf("Set pin at HIGH level\n");
    digitalWrite (0,  LOW) ; delay (500) ;
    printf("Set pin at LOW level\n");
  }
  return 0 ;
}
```

![RPiBlinkLED](https://github.com/TommasoPino/DIY_Domotic/blob/master/img/RPiBlinkLED_bb.png)

### Button LED

![RPiButtonLED](https://github.com/TommasoPino/DIY_Domotic/blob/master/img/RPiButtonLED_bb.png)

