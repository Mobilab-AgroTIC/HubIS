# Installer un réseau LoRa

Le système à développer passe par un réseau bas-débit, appelé LoRa. 

Un réseau LoRa est comme un réseau WiFi, avec les particularité suivantes : 
- Portée de l'ordre du kilomètre (contre quelques mètres pour le WiFi)
- Consomme très peu de courant !: Autonomie des capteurs de quelques années (contre quelques heures pour le WiFi)
- Taille des données envoyées très petites (contre des grosses données pour le WiFi)

Tous les projets du mobilab utilisent la solution gratuite The Things Network pour déployer et utiliser le réseau LoRa.

## La passerelle LoRa

### Présentation

Une passerelle LoRa est essentielle pour pouvoir communiquer avec les capteurs que l'on va développer. Elle correspond à la "box" WiFi chez vous.
La passerelle doit-être installé si possible en hauteur, dans un environnement découvert, et doit avoir un accès à internet (WiFi ou Ethernet)
Une passerelle peut accueillir une très grande quantité de capteurs, il n'est pas nécessaire d'en acheter une par capteur !

A savoir : si un voisin a déjà déployé sa passerelle LoRa, il n'est peut-être pas nécessaire d'acheter soi-même une passerelle ! Il est donc conseillé de tester d'abord la couverture avant d'acheter une passerelle.

### Les passerelles testées
Il existe une multitude de passerelles LoRa compatibles avec le projet. Nous avons testé plusieurs passerelles LoRa : 
- The things Gateway Indoor est la moins chère (100€) mais également la plus fragile et avec une portée de l'ordre de 100 mètres environ.
- The Things Gateway (300€) permet d'obtenir une portée de l'ordre du kilomètre sur un environnement dégagé, sur un toît (dans une boite de dérivation pour la protéger). Elle peut se connecter à Internet par WiFi ou en Ethernet.
- UG65 (350€) est une passerelle avec la norme IP65 (résiste à l'eau mais pas à l'immersion et aux énormes intempéries). Sa portée est supérieure à 1km
- UG67 (700€) est la plus chère et la meilleure des passerelles testées. Sa portée est grande et l'appareil est robuste.

### Brancher et connecter une Passerelle LoRa
Ce tuto présente le branchement d'une passerelle the Things Gateway


# Liste du Matériel
Les liens redirigent vers le site Aliexpress à titre informatif : D'autres fournisseurs peuvent livrer ce genre de produits ! 

Liste du matériel commun aux trois capteurs de HubIS : 

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

## Capteur Flowter
Liste du matériel supplémentaire pour le CapteurFlowteur : 

- Un [capteur de niveau d'eau](https://fr.aliexpress.com/item/32988554390.html?spm=a2g0o.productlist.0.0.39392ec7R3YW7m&algo_pvid=6bbe5437-b904-494b-9c8b-3d9ff1c7bcac&algo_exp_id=6bbe5437-b904-494b-9c8b-3d9ff1c7bcac-0&pdp_ext_f=%7B%22sku_id%22%3A%2266845333367%22%7D&pdp_pi=-1%3B0.84%3B-1%3B-1%40salePrice%3BEUR%3Bsearch-mainSearch)
- des [cables M-F](https://fr.aliexpress.com/item/32951870747.html?spm=a2g0o.productlist.0.0.74cf7188db3v8I&algo_pvid=0ce807a8-74d8-4064-bd64-870e37476d28&algo_exp_id=0ce807a8-74d8-4064-bd64-870e37476d28-5&pdp_ext_f=%7B%22sku_id%22%3A%2266291478012%22%7D&pdp_pi=-1%3B1.0%3B-1%3B-1%40salePrice%3BEUR%3Bsearch-mainSearch) de la taille voulue.

## WatAr Sensor
Liste du matériel supplémentaire pour le WatAr Sensor : 

- Un [capteur capacitif](https://fr.aliexpress.com/item/32908693444.html?spm=a2g0o.productlist.0.0.68065411IokKyO&algo_pvid=4752ace8-302a-4c14-967f-84619b11e580&algo_exp_id=4752ace8-302a-4c14-967f-84619b11e580-2&pdp_ext_f=%7B%22sku_id%22%3A%2210000001112702586%22%7D&pdp_pi=-1%3B0.75%3B-1%3B-1%40salePrice%3BEUR%3Bsearch-mainSearch)
- des [cables M-M](https://fr.aliexpress.com/item/32951870747.html?spm=a2g0o.productlist.0.0.74cf7188db3v8I&algo_pvid=0ce807a8-74d8-4064-bd64-870e37476d28&algo_exp_id=0ce807a8-74d8-4064-bd64-870e37476d28-5&pdp_ext_f=%7B%22sku_id%22%3A%2266291478012%22%7D&pdp_pi=-1%3B1.0%3B-1%3B-1%40salePrice%3BEUR%3Bsearch-mainSearch) de la taille voulue.

## Martelière
Liste du matériel supplémentaire pour le WatAr Sensor : 

- Un [Servo moteur MG995](https://fr.aliexpress.com/item/1005002401494033.html?spm=a2g0o.productlist.0.0.729f3827t6kegM&algo_pvid=07dc4806-fb75-4148-aae9-bd0ffd82331a&algo_exp_id=07dc4806-fb75-4148-aae9-bd0ffd82331a-7&pdp_ext_f=%7B%22sku_id%22%3A%2212000020531533064%22%7D&pdp_pi=-1%3B3.78%3B-1%3B187%40salePrice%3BEUR%3Bsearch-mainSearch)
- des [cables M-M](https://fr.aliexpress.com/item/32951870747.html?spm=a2g0o.productlist.0.0.74cf7188db3v8I&algo_pvid=0ce807a8-74d8-4064-bd64-870e37476d28&algo_exp_id=0ce807a8-74d8-4064-bd64-870e37476d28-5&pdp_ext_f=%7B%22sku_id%22%3A%2266291478012%22%7D&pdp_pi=-1%3B1.0%3B-1%3B-1%40salePrice%3BEUR%3Bsearch-mainSearch) de la taille 
