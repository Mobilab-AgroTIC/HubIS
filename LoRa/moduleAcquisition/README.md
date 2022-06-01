
# Le module d'Acquisition LoRa

Le module d'acqusistion LoRa est au centre de nombreux systèmes développés dans le mobilab AgroTIC. Il permet de récupérer les données d'un capteur (flotteur, température, humidité, etc) et de le transmettre via un réseau dit 'Bas-débit'. Un module coûte environ 30€ est est relativement simple à développer. 

Dans un premier temps, nous allons construire le module. Puis, comme pour la passerelle, il faut d'abord déclarer *virtuellement* le module sur le site The Things Network, qui va lui assigner des codes d'accès. On récupère ensuite ces codes d'accès pour les rentrer dans le module d'acquisition, qui pourra alors transmettre des données jusqu'au site. 

<p align="center">
  <img height="300" src="https://user-images.githubusercontent.com/24956276/171441603-d26ef67e-7566-49ca-8db9-e4ef4eccf30b.png">
  
  <em>Un module d'Acquisition dans son boitier (en noir), rattaché à un flotteur pour mesurer une hauteur d'eau</em>
</p>

# Construction du module 
## Module d'Acquisition V1

Les liens redirigent vers le site Aliexpress à titre informatif : D'autres fournisseurs peuvent livrer ce genre de produits ! 

- Une carte [Cubecell HTC01 868MHz](https://www.amazon.fr/LoRaWAN-d%C3%A9veloppement-consommation-d%C3%A9nergie-Intelligente/dp/B07ZH7NL38/ref=sr_1_2?crid=1OHV1O5DEMZ3K&keywords=cubecell&qid=1654076800&sprefix=cubecell%2Caps%2C786&sr=8-2) (17€)
- Une [petite breadboard](https://fr.aliexpress.com/item/32711841420.html?spm=a2g0o.productlist.0.0.65c62a6bTbWAZZ&algo_pvid=d5826731-e561-4cfd-949f-23708ba8ce65&algo_exp_id=d5826731-e561-4cfd-949f-23708ba8ce65-1&pdp_ext_f=%7B%22sku_id%22%3A%2260928567388%22%7D&pdp_npi=2%40dis%21EUR%21%211.21%21%21%211.22%21%21%400b0a050116540768736257657ef0c0%2160928567388%21sea) (2€)
- Un [câble USB - micro USB](https://fr.aliexpress.com/item/1005004011620185.html?spm=a2g0o.productlist.0.0.521c25ae6qpBKJ&algo_pvid=3c669216-9262-4620-b0f1-91bdfd384a27&algo_exp_id=3c669216-9262-4620-b0f1-91bdfd384a27-1&pdp_ext_f=%7B%22sku_id%22%3A%2212000027732934935%22%7D&pdp_npi=2%40dis%21EUR%21%212.42%21%21%21%21%21%400b0a050116540769447078326ef0c0%2112000027732934935%21sea) (2€). _Vous avez peut-être ce câble déjà chez vous : dans ce cas, il faut s'assurer qu'il soit DATA : le câble ne doit pas servir qu'à alimenter, mais transfère aussi des données (les câbles issus des boites de téléphones le sont, en général). Pour le savoir, on peut brancher son téléphone à un ordinateur. Si on ne peut pas aller dans ses données de téléphone, ce câble n'est pas DATA._
- Une [pile LiPo 18650](https://fr.aliexpress.com/item/1005003884402783.html?spm=a2g0o.productlist.0.0.152d3abbwRZw6U&algo_pvid=6e3a1f8f-b240-427e-84e6-4edd11873acb&algo_exp_id=6e3a1f8f-b240-427e-84e6-4edd11873acb-9&pdp_ext_f=%7B%22sku_id%22%3A%2212000027385901241%22%7D&pdp_npi=2%40dis%21EUR%21%2123.65%21%21%21%21%21%402100bddd16540848646242236e36d2%2112000027385901241%21sea) (2€)
- Un [support de pile LiPo ](https://fr.aliexpress.com/item/1005001660193629.html?spm=a2g0o.productlist.0.0.41f663cb5UzfhA&algo_pvid=bb7100fb-5a41-41ea-a0b6-641953164b12&algo_exp_id=bb7100fb-5a41-41ea-a0b6-641953164b12-0&pdp_ext_f=%7B%22sku_id%22%3A%2212000017030989115%22%7D&pdp_npi=2%40dis%21EUR%21%210.57%21%21%21%21%21%402100bddd16540847580796849e36d2%2112000017030989115%21sea) (0.5€)
- Optionnel : un [chargeur de pile LiPo](https://fr.aliexpress.com/item/4000389548504.html?spm=a2g0o.ppclist.product.2.2aa5MKt2MKt2dV&pdp_npi=2%40dis%21EUR%21%E2%82%AC%201%2C50%21%E2%82%AC%201%2C50%21%21%21%21%21%40211b5e2116540847018041103ebb31%2110000001590316714%21btf&_t=pvid%3Aeb3f5609-ca17-4705-a884-e4d30379c65f&afTraceInfo=4000389548504__pc__pcBridgePPC__xxxxxx__1654084702&gatewayAdapt=glo2fra) (2€)

## Montage de la carte d'acquisition : 

La carte Cubecell est livrée avec des broches, à souder sur la carte Cubecell. Il faut également clipser le câble rouge et noir sous la carte CubeCell, ainsi que l'antenne, comme ceci :

<p align="center">
  <img height="300" src="https://user-images.githubusercontent.com/24956276/171400798-5848a176-b9ec-4251-8e83-1398ba19a25d.png">
</p>

# Déclaration du module sur The Things Network

## Créer une application sur The Things Network

Une application c'est comme un dossier qui va contenir plusieurs capteurs (on peut imaginer une flotte de 20 capteurs de températures, qui vont communiquer sur la même application de The Things Network). 

Direction le site de [The Things Network](https://eu1.cloud.thethings.network/console/)  *Si c'est la première fois, il faut cliquer sur register puis renseigner un username, une adresse mail, un password. Pensez à regarder le mail reçu pour valider l'inscription ! On se connecte enfin en retournant sur le site.*
On clique sur ```Go to applications```.

<p align="center">
  <img src="https://user-images.githubusercontent.com/24956276/171421890-cb1e07ed-5135-402c-be44-e4bdf2fffc24.png">
</p>

On clique sur le bouton bleu ![image](https://user-images.githubusercontent.com/24956276/171422130-f0d5dc9c-c491-41a0-8dfb-b492304c2caa.png) puis on donne un nom simmple à l'application, puis on clique sur ![image](https://user-images.githubusercontent.com/24956276/171422264-7c65ba54-6e88-4c42-b1df-06b951284b62.png)

On arrive sur la page ```Overview``` de l'application, c'est la page principale où l'on pourra voir toutes les activités des capteurs installés. 

## Declarer un nouveau module 

Sur la page ```Overview``` de l'application, on clique sur ![image](https://user-images.githubusercontent.com/24956276/171426773-0ec080f6-9ddd-442d-bf35-d37620b5a9f2.png).

Il faut cliquer sur l'onget ```Manually``` Plusieurs éléments sont à renseigner ici : 

- ```Frequency plan``` : choisir ```Europe 863-870 MHz```. *C'est la fréquence de communication de LoRa en Europe*
- ```LoRaWAN version``` : choisir ```LoRaWAN Specification 1.0.2``` *C'est le protocole de communication utilisé par notre carte*
- ```Regional Parameters version``` : choisir ```RP001 Regional Parameters 1.0.2```
- ```DevEUI``` : cliquer sur ```Generate``` *C'est l'identifiant du module que l'on va créer*
- ```AppEUI``` : Cliquer sur ```Fill with zeros``` *C'est l'identifiant de l'application*
- ```AppKey``` : Cliquer sur ```Generate``` *C'est le mot de passe pour accéder à l'application*
- ```End device ID``` : C'est le nom du futur module. Choisir quelque chose de simple qui n'a pas été encore pris, par exemple ```capteur-humidite-1```

Vous devez obtenir ceci : 

<p align="center">
  <img src="https://user-images.githubusercontent.com/24956276/171429266-31c08617-d46f-4cea-834b-96047fd2052d.png">
</p>

Cliquer sur ![image](https://user-images.githubusercontent.com/24956276/171431102-9ed150bc-d95b-4d9f-9a8e-cbf899882d05.png). On revient à la page d'accueil ```Overview```. On remarque qu'un nouveau module est déclaré dans la partie ```End devices``` en bas. 

<p align="center">
  <img src="https://user-images.githubusercontent.com/24956276/171431428-4b5d8664-e3f2-4be4-b7fb-71dd50b029dd.png">
</p>

On peut cliquer sur le nom du module déclaré pour avoir plus d'informations. On arrive sur la page du capteur. On remarque également qu'il n'a jamais été actif : 

<p align="center">
  <img src="https://user-images.githubusercontent.com/24956276/171432079-994e6a3e-9a5f-4b68-90d2-a274cdc170c9.png">
</p>

A noter la partie droite ```Live data```, qui note chaque activité. Quand les données viendront du capteur, c'est ici qu'elles seront marquées. A ce stade, les données les plus importantes sont dans ```Activation information```. C'est la qu'on trouve les codes d'accès que l'on va renseigner au module ! 

## Paramétrer le module d'acquisition :

Il faut au préalable installer le [logiciel Arduino](https://www.arduino.cc/en/software) sur son ordinateur. Choisissez l'installation pour votre ordinateur (Windows, linux, mac, etc) :

<p align="center">
  <img height="250" src="https://user-images.githubusercontent.com/24956276/168775993-2691511c-9ea9-4fee-9f0e-90afb1747dbb.png">
</p>
L'installation demandera quelques autorisations, qu'il faudra accepter.

Une fois installé, on lance le logiciel Arduino. Une fenêtre s'ouvre :

<p align="center">
  <img height="250" src="https://user-images.githubusercontent.com/24956276/168776482-0613947c-0370-4ca8-819b-ab0c045d7667.png">
</p>

On va dans ```Fichier```>```Préférences```

<p align="center">
  <img src="https://user-images.githubusercontent.com/24956276/171402445-3abafa64-0c47-4f23-907e-1e0cedf2e524.png">
</p>

Dans la nouvelle denêtre, on cherche ```URL de gestionnaire de cartes supplémentaires``` et on y colle le texte suivant, puis cliquer sur ```OK```

```https://github.com/HelTecAutomation/CubeCell-Arduino/releases/download/V1.4.0/package_CubeCell_index.json```

![image](https://user-images.githubusercontent.com/24956276/171401907-0fc8333a-9b52-4717-a687-3eac4d24f7d2.png)

On ouvre ```Outils``` > ```Type de cartes``` > ```Gestionnaire de Cartes```

<p align="center">
  <img src="https://user-images.githubusercontent.com/24956276/171403617-b7479014-ef44-430a-ae37-232c8c688a19.png">
</p>

On recherce depuis la barre de recherche ```Cubecell```. Une librairie est trouvée : ```CubeCell Development Framework```. On clique sur Installer. L'installation peut prendre 1min.

<p align="center">
  <img src="https://user-images.githubusercontent.com/24956276/171403910-d90e1c8b-4be9-4b94-936c-cf3e32cdf047.png">
</p>


On selectionne finalement la carte utilisée dans ```outils``` > ```Type de Carte``` > ```CubeCell``` > ```CubeCell Module (HTCC01)``` : 

<p align="center">
  <img src="https://user-images.githubusercontent.com/24956276/171404604-f7375034-6d13-4de5-b73e-26d2fb6caede.png">
</p>

La carte est prête à être configurée ! il faut copier tout [ce code](https://raw.githubusercontent.com/Mobilab-AgroTIC/HubIS/main/Capteur_Flowter/Capteur_Flowter_CubeCell/Capteur_Flowter_CubeCell.ino), puis coller tout le code


## Module Acquisition V2
Module plus complexe ! et moins cher
- Un micro-processeur [Arduino pro mini 3.3V](https://fr.aliexpress.com/item/32821902128.html?spm=a2g0o.productlist.0.0.4ea83f60h7JWI0&algo_pvid=38e1b424-35ff-425a-a42c-1276408fff65&algo_exp_id=38e1b424-35ff-425a-a42c-1276408fff65-1&pdp_ext_f=%7B%22sku_id%22%3A%2267225925113%22%7D&pdp_pi=-1%3B4.08%3B-1%3B-1%40salePrice%3BEUR%3Bsearch-mainSearch)
- Du materiel de communication avec les microprocesseur (à n'acheter une seule fois pour plusieurs capteurs)
  - Un [cable USB - mini USB](https://fr.aliexpress.com/item/1005002978737000.html?spm=a2g0o.productlist.0.0.3e595de2S3YILW&algo_pvid=46864e2f-e3f6-4c67-8893-587e3655681b&algo_exp_id=46864e2f-e3f6-4c67-8893-587e3655681b-0&pdp_ext_f=%7B%22sku_id%22%3A%2212000023042444119%22%7D&pdp_pi=-1%3B1.6%3B-1%3B65%40salePrice%3BEUR%3Bsearch-mainSearch)
  - Un [FTDI](https://fr.aliexpress.com/item/32460118879.html?spm=a2g0o.productlist.0.0.663d6dd2k0WBFN&algo_pvid=a27a1804-25ef-4cca-ac79-6b0babefaff3&algo_exp_id=a27a1804-25ef-4cca-ac79-6b0babefaff3-0&pdp_ext_f=%7B%22sku_id%22%3A%2257041576669%22%7D&pdp_pi=-1%3B1.33%3B-1%3B-1%40salePrice%3BEUR%3Bsearch-mainSearch) pour communiquer avec le micro processeur
- Une carte de communication LoRa [SX1276](https://fr.aliexpress.com/item/4000180826939.html?spm=a2g0o.productlist.0.0.159530acIDSYuy&algo_pvid=6043410b-5fe4-4dfb-9c6f-4f6f0008d24f&algo_exp_id=6043410b-5fe4-4dfb-9c6f-4f6f0008d24f-7&pdp_ext_f=%7B%22sku_id%22%3A%2210000000658383494%22%7D&pdp_pi=-1%3B3.81%3B-1%3B-1%40salePrice%3BEUR%3Bsearch-mainSearch)
- Du materiel de connectique
  - Une [petite breadboard](https://fr.aliexpress.com/item/32711841420.html?spm=a2g0o.productlist.0.0.55c12a6b0FZJQz&algo_pvid=4be2dec8-bf95-4407-8ff7-9a93c33605ad&algo_exp_id=4be2dec8-bf95-4407-8ff7-9a93c33605ad-1&pdp_ext_f=%7B%22sku_id%22%3A%2260928567388%22%7D&pdp_pi=-1%3B1.02%3B-1%3B-1%40salePrice%3BEUR%3Bsearch-mainSearch)
  - Des [cavaliers Jumpers](https://fr.aliexpress.com/item/1005002828254543.html?spm=a2g0o.productlist.0.0.293f4868ss5eVs&algo_pvid=bdf5d51c-405a-43b1-a0ad-a34bbc6cb9cf&algo_exp_id=bdf5d51c-405a-43b1-a0ad-a34bbc6cb9cf-1&pdp_ext_f=%7B%22sku_id%22%3A%2212000022367973906%22%7D&pdp_pi=-1%3B4.7%3B-1%3B156%40salePrice%3BEUR%3Bsearch-mainSearch) de plusieurs tailles
  - Une [bande de connecteurs](https://fr.aliexpress.com/item/32651418137.html?gatewayAdapt=glo2fra&spm=a2g0o.order_list.0.0.21ef5e5bOSVfyT)
- Une pile [18650](https://fr.aliexpress.com/item/32807032859.html?spm=a2g0o.productlist.0.0.2af63abbDiq71g&algo_pvid=2e3a3c09-991c-4c4f-8f64-7eb89c567085&algo_exp_id=2e3a3c09-991c-4c4f-8f64-7eb89c567085-0&pdp_ext_f=%7B%22sku_id%22%3A%2265139771902%22%7D&pdp_pi=-1%3B4.89%3B-1%3B-1%40salePrice%3BEUR%3Bsearch-mainSearch) et son [support](https://fr.aliexpress.com/item/1005001707889794.html?gatewayAdapt=glo2fra&spm=a2g0o.order_list.0.0.21ef5e5blPeHAN)
