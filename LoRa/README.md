# Construire un réseau LoRa

Le système à développer passe par un réseau bas-débit, appelé LoRa. 

Un réseau LoRa est comme un réseau WiFi, avec les particularité suivantes : 
- Portée de l'ordre du kilomètre (contre quelques mètres pour le WiFi)
- Consomme très peu de courant !: Autonomie des capteurs de quelques années (contre quelques heures pour le WiFi)
- Taille des données envoyées très petites (contre des grosses données pour le WiFi)

Tous les projets du mobilab utilisent la solution gratuite The Things Network pour déployer et utiliser le réseau LoRa.

Comme tout réseau, le réseau installé comporte : 

- Une **[passerelle](https://github.com/Mobilab-AgroTIC/HubIS/tree/main/LoRa/Gateway)**, ou Gateway : C'est l'équivalent de la box WiFi chez vous
- Un **[objet connecté](https://github.com/Mobilab-AgroTIC/HubIS/tree/main/LoRa/moduleAcquisition)** capable de communiquer en LoRa
