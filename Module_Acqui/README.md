
# Le module d'Acquisition

Le module d'acqusistion est au centre de nombreux systèmes développés dans le mobilab AgroTIC. Il permet de récupérer les données d'un capteur (flotteur, température, humidité, etc) et de le transmettre via un réseau dit 'Bas-débit'. Un module coûte environ 25€ est est relativement simple à développer. 


## Module d'Acquisition V1

Les liens redirigent vers le site Aliexpress à titre informatif : D'autres fournisseurs peuvent livrer ce genre de produits ! 

- Une carte [Cubecell HTC01 868MHz](https://www.amazon.fr/LoRaWAN-d%C3%A9veloppement-consommation-d%C3%A9nergie-Intelligente/dp/B07ZH7NL38/ref=sr_1_2?crid=1OHV1O5DEMZ3K&keywords=cubecell&qid=1654076800&sprefix=cubecell%2Caps%2C786&sr=8-2) (17€)
- Une [breadboard](https://fr.aliexpress.com/item/32711841420.html?spm=a2g0o.productlist.0.0.65c62a6bTbWAZZ&algo_pvid=d5826731-e561-4cfd-949f-23708ba8ce65&algo_exp_id=d5826731-e561-4cfd-949f-23708ba8ce65-1&pdp_ext_f=%7B%22sku_id%22%3A%2260928567388%22%7D&pdp_npi=2%40dis%21EUR%21%211.21%21%21%211.22%21%21%400b0a050116540768736257657ef0c0%2160928567388%21sea) (2€)
- Un [câble USB - micro USB](https://fr.aliexpress.com/item/1005004011620185.html?spm=a2g0o.productlist.0.0.521c25ae6qpBKJ&algo_pvid=3c669216-9262-4620-b0f1-91bdfd384a27&algo_exp_id=3c669216-9262-4620-b0f1-91bdfd384a27-1&pdp_ext_f=%7B%22sku_id%22%3A%2212000027732934935%22%7D&pdp_npi=2%40dis%21EUR%21%212.42%21%21%21%21%21%400b0a050116540769447078326ef0c0%2112000027732934935%21sea) (2€). Vous avez peut-être ce câble déjà chez vous : dans ce cas, il faut s'assurer qu'il soit DATA : le câble ne doit pas servir qu'à alimenter, mais transfère aussi des données (les câbles issus des boites de téléphones le sont, en général). Pour le savoir, on peut brancher son téléphone à un ordinateur. Si on ne peut pas aller dans ses données de téléphone, ce câble n'est pas DATA.

## Montage de la carte d'acquisition : 

La carte Cubecell est livrée avec des broches, à souder sur la carte Cubecell comme ceci :

## Paramétrage de la carte d'acquisition :

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
