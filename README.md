# Conway-s_Life_game

## Português
### Como usar
Na pasta <b>config</b> você encontrará um arquivo. Nele estarão todas as configurações necessárias para que o programa funcione. Você pode salvar a configuração em outra pasta, mas para isso, deve especificar o diretório em que esta está ao executar o programa - mais detalhes afrente.
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
    generate_image = [true │ false] - true para gerar imagens, false para não gerar imagens
    
    exemplo: generate_image = true
  </li>
  <li>
    alive = [Cor das células vivas] - As cores disponíveis são: <br></br> BLACK; BLUE; CRIMSON; DARK_GREEN; DEEP_SKY_BLUE; DODGER_BLUE; GREEN; LIGHT_BLUE; LIGHT_GREY; LIGHT_YELLOW; RED; STEEL_BLUE; WHITE; YELLOW.
    
    Exemplo: alive = GREEN
  </li>
  <li>
    bkg = [Cor das células mortas / cor de fundo] - As cores disponíveis são as mesmas acima.
    
    Exemplo: alive = LIGHT_BLUE
  </li>
  <li>
    block_size = [Tamanho virtual do pixel]
    
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
      
      exemplo: fps = 9
  </ul>
</li>

</ul>

Na pasta <b>data</b> você encontrará várias configurações prontas que representam a primeira geração do tabuleiro. São esses os arquivos que você pode adicionar como parâmetro no <b>input_cfg</b> em <b>glife.ini</b>. Você também pode criar seus próprios arquivos, bastando seguir o mesmo padr

Depois de escolher as configurações, basta executar ./build/glife na pasta raiz.

### English
In the folder <b>config</b> you will finde a file. In it, there will be all the necessary configurations for the program to work.
Between the options, 
