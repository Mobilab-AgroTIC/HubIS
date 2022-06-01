# Les passerelles LoRa

## Présentation

Une passerelle LoRa est essentielle pour pouvoir communiquer avec les capteurs que l'on va développer. Elle correspond à la "box" WiFi chez vous, ou à l'antenne 4G la plus proche de votre téléphone.

A savoir : si un voisin a déjà déployé sa passerelle LoRa, il n'est peut-être pas nécessaire d'acheter soi-même une passerelle ! Il est donc conseillé de tester la couverture avant d'acheter une passerelle. Le test peut se faire avec un [module d'acquisition LoRa](https://github.com/Mobilab-AgroTIC/HubIS/tree/main/LoRa/moduleAcquisition)

## Les passerelles testées
Il existe une multitude de passerelles LoRa compatibles avec le projet. Nous avons testé plusieurs passerelles LoRa : 
- The [**Things Gateway Indoor**](https://fr.rs-online.com/web/p/modules-de-developpement-de-communication-et-sans-fil/2018876?cm_mmc=FR-PLA-DS3A-_-google-_-CSS_FR_FR_Raspberry_Pi_%26_Arduino_%26_Outils_de_developpement_Whoop-_-(FR:Whoop!)+Modules+de+d%C3%A9veloppement+de+communication+et+sans+fil-_-2018876&matchtype=&pla-302930656441&gclid=Cj0KCQjwnNyUBhCZARIsAI9AYlG56qA1J0ROX7SbTis0TthMzeDWLH3KAhIG9ApMBMLnEj_50sQFLhcaApJaEALw_wcB&gclsrc=aw.ds) est la moins chère (100€) mais également la plus fragile et avec une portée de l'ordre de 100 mètres environ.
- The [**Things Gateway**](https://fr.farnell.com/the-things-network/ttn-gw-868/the-things-gateway-eu/dp/2675813) (300€) permet d'obtenir une portée de l'ordre du kilomètre sur un environnement dégagé, sur un toît (dans une boite de dérivation pour la protéger). Elle peut se connecter à Internet par WiFi ou en Ethernet.
- UG65 (350€) est une passerelle avec la norme IP65 (résiste à l'eau mais pas à l'immersion et aux énormes intempéries). Sa portée est supérieure à 1km
- UG67 (700€) est la plus chère et la meilleure des passerelles testées. Sa portée est grande et l'appareil est robuste.

## Activer une Passerelle LoRa

Ce tuto présente le branchement d'une passerelle the Things Gateway et son activation sur The Things Network, en deux étapes : Tout d'abord, on déclare une passerelle sur le site, qui va nous donner un code d'accès. Ensuite, on donne ce code d'accès à la passerelle pour qu'elle puisse se connecter. 

### Déclarer une nouvelle passerelle sur The Things Network

Direction [ce site](https://eu1.cloud.thethings.network/console/gateways). *Si c'est la première fois, il faut cliquer sur ```register``` puis renseigner un ```username```, une ```adresse mail```, un ```password```. Pensez à regarder le mail reçu pour valider l'inscription ! On se connecte enfin en retournant sur le site.* 

On se retrouve sur la page ```Gateways```. Cliquer sur le bouton bleu ![image](https://user-images.githubusercontent.com/24956276/171409958-12ce6a0d-8328-4e47-8add-69bd87d22133.png)
 puis remplir plusieurs informations : 

- ```Gateway ID``` : l'identifiant de la passerelle, ne pouvant contenir que des minuscules, chiffres ou des tirets ```-```
- ```Frequency plan``` dans la partie **```LoRaWan options```** à mettre en ```Europe 863-870 MHz (SF9 for RX2 - recommended)```
- ```Automatic updates``` : Cocher en Enabled

On termine par ```Create Gateway``` tout en bas. On arrive alors sur la page de notre nouvelle passerelle, fraichement créée : 

<p align="center">
  <img src="https://user-images.githubusercontent.com/24956276/171409585-8cd596a5-9b63-4815-b449-bd936392b314.png">
</p>

Aller sur l'onglet de gauche ```API keys``` et cliquer sur le bouton bleu ![image](https://user-images.githubusercontent.com/24956276/171409893-4c07cffa-f4ab-467a-ad18-403f98acc321.png), puis le bouton bleu ![image](https://user-images.githubusercontent.com/24956276/171410245-10dec05d-205d-4361-ab27-25881f782d9f.png). Dans la nouvelle page, il faut impérativement copier la clef ```API key```car elle ne sera plus jamais disponible après avoir cliqué sur ![image](https://user-images.githubusercontent.com/24956276/171410593-6fbbab93-4485-46d8-b33e-e075c55f0df2.png) ! Pensez donc à la mettre dans un fichier texte quelque part, vous en aurez besoin pour la suite.

<p align="center">
  <img src="https://user-images.githubusercontent.com/24956276/171410203-868b04d2-d6c1-4c9a-98df-96356bb193ae.png">
</p>

On peut enfin revenir sur la page principale de la passerelle en cliquant à gauche sur ```Overview```. Notons que le statut de la paserelle est toujours ```Disconnected``` pour l'instant.

### Paramétrer la passerelle Things Gateway avec la API key

Il faut maintenant donner ce code à la passerelle, pour qu'elle puisse se connecter à The Things Network ! 

Brancher la passerelle Things Gateway sur le secteur. Retirer le capot blac et appuyer 5 secondes sur le bouton ```RESET```
On va momentanément se déconnecter d'Internet pour se connecter en WiFi au réseau ```thethings_XXX```. Le mot de passe est ```thethings```
on ouvre ensuite une fenetre Internet pour aller sur le site ```192.168.84.1```

<p align="center">
  <img src="https://user-images.githubusercontent.com/24956276/171412428-cfdfba7f-9fe6-455d-88f7-2804d8a8beab.png">
</p>

- ```Gateway ID``` doit être le même que celui renseigné sur The Things Network plus haut
- ```WiFi Access Point``` et ```WiFi Password``` sont les informations du WiFi sur lequel la passerelle va pouvoir se connecter à Internet. Si la passerelle est branché en Ethernet, ces champs peuvent être vides.
- On clique sur ```Show advanced options``` :
  - ```Account server``` : https://eu1.cloud.thethings.network
  - ```Gateway Key``` : c'est l'```API key``` que l'on a copié plus haut ! Vérifier qu'il n'y a pas d'espace à la fin de cette clef.

On clique enfin sur ```save```. La passerelle se met à jour si nécessaire puis s'active. L'opération peut prendre jusqu'à 10minutes. Le code des LED est le suivant : 

- La LED 1 est allumée : La passerelle est branchée
- La LED 2  : 
  - clignote lentement : La paserelle cherche à se connecter à internet
  - clignote rapidement : La paserelle n'a pas réussi à se connecter. Refaire le paramétrage de la passerelle.
  - est allumée : Connection à Internet réussie ! 
- La LED 3  : 
  - clignote lentement : La paserelle cherche à s'activer
  - clignote rapidement : La paserelle n'a pas réussi à s'activer sur The THings Network. Refaire toute l'installation.
  - est allumée : L'Activation est réussie
- La LED 4 est allumée : Tout roule ! 
- Toutes les LED clignotent bizarrement : la gateway est toujours en train de se mettre à jour. Ne pas toucher

Si tout fonctionne, on peut voir dans la page principale ```Overview``` de la paserelle qu'elle est active : ```Last activity 5 secondes ago```

<p align="center">
  <img src="https://user-images.githubusercontent.com/24956276/171415046-b08f340e-cf5f-46eb-a5cc-a74616078862.png">
</p>

Félicitations, votre réseau LoRa est opérationnelle ! 

Ancien tuto : [ici](https://docs.google.com/document/d/15u7gVZ0O7rmBvpWaHETV42GnluCNkuVWq6kZX1yau00/edit)

### Installation de la paserelle LoRa

La passerelle doit-être installée si possible en hauteur, dans un environnement découvert, et doit avoir un accès à internet (WiFi ou Ethernet)
Une passerelle peut accueillir une très grande quantité de capteurs, il n'est pas nécessaire d'en acheter une par capteur !

Les passerelles peuvent être stockées dans une grosse boite de dérivation pour les protéger.

![image](https://user-images.githubusercontent.com/24956276/171419408-31791f65-3f24-433d-978c-50582aa9960d.png)

Il est temps de tester votre réseau en [connectant un module d'acquisition](https://github.com/Mobilab-AgroTIC/HubIS/tree/main/LoRa/moduleAcquisition) à The Things Network ! ;)
