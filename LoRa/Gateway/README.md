# La passerelle LoRa

## Présentation

Une passerelle LoRa est essentielle pour pouvoir communiquer avec les capteurs que l'on va développer. Elle correspond à la "box" WiFi chez vous.
La passerelle doit-être installé si possible en hauteur, dans un environnement découvert, et doit avoir un accès à internet (WiFi ou Ethernet)
Une passerelle peut accueillir une très grande quantité de capteurs, il n'est pas nécessaire d'en acheter une par capteur !

A savoir : si un voisin a déjà déployé sa passerelle LoRa, il n'est peut-être pas nécessaire d'acheter soi-même une passerelle ! Il est donc conseillé de tester d'abord la couverture avant d'acheter une passerelle.

## Les passerelles testées
Il existe une multitude de passerelles LoRa compatibles avec le projet. Nous avons testé plusieurs passerelles LoRa : 
- The [**Things Gateway Indoor**](https://fr.rs-online.com/web/p/modules-de-developpement-de-communication-et-sans-fil/2018876?cm_mmc=FR-PLA-DS3A-_-google-_-CSS_FR_FR_Raspberry_Pi_%26_Arduino_%26_Outils_de_developpement_Whoop-_-(FR:Whoop!)+Modules+de+d%C3%A9veloppement+de+communication+et+sans+fil-_-2018876&matchtype=&pla-302930656441&gclid=Cj0KCQjwnNyUBhCZARIsAI9AYlG56qA1J0ROX7SbTis0TthMzeDWLH3KAhIG9ApMBMLnEj_50sQFLhcaApJaEALw_wcB&gclsrc=aw.ds) est la moins chère (100€) mais également la plus fragile et avec une portée de l'ordre de 100 mètres environ.
- The [**Things Gateway**](https://fr.farnell.com/the-things-network/ttn-gw-868/the-things-gateway-eu/dp/2675813) (300€) permet d'obtenir une portée de l'ordre du kilomètre sur un environnement dégagé, sur un toît (dans une boite de dérivation pour la protéger). Elle peut se connecter à Internet par WiFi ou en Ethernet.
- UG65 (350€) est une passerelle avec la norme IP65 (résiste à l'eau mais pas à l'immersion et aux énormes intempéries). Sa portée est supérieure à 1km
- UG67 (700€) est la plus chère et la meilleure des passerelles testées. Sa portée est grande et l'appareil est robuste.

## Brancher et connecter une Passerelle LoRa

Ce tuto présente le branchement d'une passerelle the Things Gateway et son activation sur The Things Network, en deux étapes : Tout d'abord, on déclare une passerelle sur le site, qui va nous donner des codes d'accès. Ensuite, on renseigne ces codes d'accès à la passerelle pour qu'elle puisse se connecter. 

Direction [ce site](https://eu1.cloud.thethings.network/console/gateways). 

Si c'est la première fois, il faut cliquer sur ```register``` puis renseigner un ```username```, une ```adresse mail```, un ```password```. Pensez à regarder le mail reçu pour valider l'inscription ! On se connecte enfin en retournant sur le site. 

On se retrouve sur la page ```Gateways```. Cliquer sur le bouton bleu ![image](https://user-images.githubusercontent.com/24956276/171407055-537251ec-c1b4-448e-a95f-392677c2fa2b.png) puis remplir plusieurs informations : 

- Gateway ID
- 


