# POC

POC gants RoukaVici

## Installation

Connecter a l'arduino et Upload le sketch
Si l'arduino est branché à la carte Bluetooth sur ses pins sériels,  débrancher la carte bluetooth avant d'upload.

## Bluetooth (Raspberry/Arduino)

Le Raspberry se connecte automatiquement au Arduino à chaque démarrage. Au cas où, un script de connection est disponible dans `/etc/init.d/roukavici_bluetooth.sh` ou `/home/pi/roukavici_bluetooth.sh`, il suffit de l'exécuter.

L'écriture se fait ensuite sur `/dev/rfcomm0`.