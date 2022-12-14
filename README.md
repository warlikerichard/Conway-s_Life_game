# Conway-s_Life_game

![](https://github.com/warlikerichard/Conway-s_Life_game/blob/main/public/glider_gun.gif)

## Português
### Como usar
Na pasta <b>.config</b> você encontrará um arquivo. Nele estarão todas as configurações necessárias para que o programa funcione. Você pode salvar a configuração em outra pasta, mas para isso, deve especificar o diretório em que esta está ao executar o programa - mais detalhes afrente.
Os parâmetros de configuração são divididos entre 3 seções - Seção livre; [Image]; [Text]:
<ul>
<li>
  Seção livre - Aqui você define os parâmetros livremente, sem precisar escrever o nome da seção. Os parâmetros são:
  <ul>
  <li>
    Input_cfg = [diretório do arquivo .dat representando o "tabuleiro" (geração) inicial]; .dat será explicado mais detalhadamente afrente.
    
    Exemplo: Input_cfg = "./config/glife.ini"
  </li>
  <li>
    max_gen = [quantidade máxima de gerações que podem ser geradas]

    Exemplo: max_gen = 200

  </ul>
</li>

<li>
  [Image] - Aqui você definirá como e se imagens serão geradas.
  <ul>
  <li>
    generate_image = [true │ false] - true para gerar imagens, false para não gerar imagens.
    
    exemplo: generate_image = true
  </li>
  <li>
    alive = [cor das células vivas] - As cores disponíveis são: <br></br> BLACK; BLUE; CRIMSON; DARK_GREEN; DEEP_SKY_BLUE; DODGER_BLUE; GREEN; LIGHT_BLUE; LIGHT_GREY; LIGHT_YELLOW; RED; STEEL_BLUE; WHITE; YELLOW.
    
    Exemplo: alive = GREEN
  </li>
  <li>
    bkg = [cor das células mortas / cor de fundo] - As cores disponíveis são as mesmas acima.
    
    Exemplo: alive = LIGHT_BLUE
  </li>
  <li>
    block_size = [tamanho virtual do pixel]
    
    Exemplo: block_size = 10
  </li>
  <li>
    path = [diretório onde as imagens devem ser salvas]
    
    Exemplo: path = "./imgs". Note que a pasta <b>deve</b> existir.
  </li>
</li>
</ul>
<li>
  [Text] - Aqui você controlará a exibição textual.
  <ul>
    <li>
      fps = [frames por segundo]
      
      Exemplo: fps = 9
  </ul>
</li>

</ul>
Para melhor entender como funciona esse arquivo, dê uma olhada no arquivo localizado na pasta .config. <br></br>

Na pasta <b>data</b> você encontrará várias configurações prontas que representam a primeira geração do tabuleiro. São esses os arquivos que você pode adicionar como parâmetro no <b>input_cfg</b> em <b>glife.ini</b>. Você também pode criar seus próprios arquivos, bastando seguir o mesmo padrão dos arquivos .dat dados.

Depois de escolher as configurações, basta executar ./build/glife [caminho para arquivo de configuração.ini] na pasta raiz. O segundo parâmetro é opcional, mas você deve especificá-lo caso não tenha um arquivo chamado glife.ini em uma pasta .config.

A build atual suporta apenas sistemas linux, mas você pode rodar o programa em outros sistemas, bastando utilizar antes o comando g++ -Wall -std=c++17 -pedantic src/main.cpp lib/tip.cpp src/life.cpp lib/canvas.cpp -I src -o build/glife.

## English
### How to use
In the folder <b>.config</b> you will find a file. In it, there will be all the necessary configurations for the program to work. you can save the configuration in another folder, but for that, you must specify the directory in which the config file is when running the program - more details ahead.
The configuration parameters are divided in 3 sections - Free section; [Image]; [Text]:
<ul>
<li>
  Free section - Here you define the parameters freely, not needing to write the section's name. The parameters are:
  <ul>
  <li>
    Input_cfg = [path to the .dat file representing the initial "board" (generation)]; The .dat file will be explained more ahead.
    
    Example: Input_cfg = "./config/glife.ini"
  </li>
  <li>
    max_gen = [max number of generations]

    Example: max_gen = 200

  </ul>
</li>

<li>
  [Image] - Here you define how and if the images will be generated.
  <ul>
  <li>
    generate_image = [true │ false] - true to generate images, false otherwise.
    
    Example: generate_image = true
  </li>
  <li>
    alive = [color of the alive cells] - The avaliable colors are: <br></br> BLACK; BLUE; CRIMSON; DARK_GREEN; DEEP_SKY_BLUE; DODGER_BLUE; GREEN; LIGHT_BLUE; LIGHT_GREY; LIGHT_YELLOW; RED; STEEL_BLUE; WHITE; YELLOW.
    
    Example: alive = GREEN
  </li>
  <li>
    bkg = [collor of the dead cells / background color] - The avaliable colors are aforementioned.
    
    Example: alive = LIGHT_BLUE
  </li>
  <li>
    block_size = [virtual size of the pixels]
    
    Example: block_size = 10
  </li>
  <li>
    path = [directory which the images will be saved]
    
    Example: path = "./imgs". Note that the given folder <b>must</b> exist.
  </li>
</li>
</ul>
<li>
  [Text] - Here you'll control the textual exhibition.
  <ul>
    <li>
      fps = [frames per second]
      
      Example: fps = 9
  </ul>
</li>

</ul>
To better understand how this file works, take a look at the file located in the .config folder.<br></br>

In the folder <b>data</b> you'll find many ready configurations that represent the first generation of the board. these are the .dat files you must add as parameter in <b>input_cfg</b> at <b>glife.ini</b>. You can also create your own .dat files, you just have to follow the pattern of the given .dat files.

After choosing the configurations, you just have to run ./build/glife [path to configuration file.ini], in the root folder. The second parameter is optional, but you must specify it <b>if</b> you don't have a file named glife.ini in a .config folder.

The current build only supports linux systems, but you can run the program in other systems. For that, you just have to run the following command before running the program: g++ -Wall -std=c++17 -pedantic src/main.cpp lib/tip.cpp src/life.cpp lib/canvas.cpp -I src -o build/glife.

