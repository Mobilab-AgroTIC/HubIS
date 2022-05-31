# HubIS

Contôlez vos systèmes d'irrigation à distance ! Le projet HubIS permet le developpement de plusieurs capteurs à bas coût. 
L’objectif principal de HubIS est de favoriser l’émergence, évaluer et accélérer l’adoption d’innovations permettant d’améliorer la performance et la durabilité des systèmes irrigués dans les régions méditerranéennes.

## Capteur Flowter
Le **CapteurFlowter** est un boitié placé au niveau de la martelière, et détecte si l'eau déborde du canal via la montée d'un petit flotteur (Position haute ou Position basse)

<p align="center">
  <img width="460" height="300" src="https://user-images.githubusercontent.com/24956276/171176651-7885a446-3800-4e8c-ab6d-e9c1b162edfd.png">
</p>

## PiLowTech
Le **PiLowTech** est une placé au niveau de la martelière, et détecte si l'eau sort du canal à ce niveau est un petit flotteur qui envoie une information lorsque son état est changé (Position haute / Position basse)

<p align="center">
  <img width="660" height="300" src="https://user-images.githubusercontent.com/24956276/171178057-83645072-a6ad-4224-a129-8c37954bd16f.png">
</p>

## WatArSensor
Le **WatarSensor** est un capteur capacitif qui permet de connaitre le taux d'humidité d'un sol. Ce capteur peut être plaçé en bout de champ et peut permettre d'actionner une martelière pour arrêter l'irrigation d'une zone. dans sa version simple, il renvoie simplement la valeur d'humidité du sol

![Watar Sensor](https://user-images.githubusercontent.com/24956276/171176488-8cc74e6c-c3f6-4d16-8e4a-b6d77da6c881.jpg)

##Lancelot

**Lancelot** est un système qui permet d'activer un petit moteur qui fait tomber une trappe, résultant l'arrêt de l'irrigation d'une parcelle.

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
