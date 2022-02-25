# TP3 - CG - Ray tracing

Foi implementando um raytracer que recebe como entrada um arquivo com dados sobre os pigmentos e acabamentos dos objetos, onde as luzes estão localizadas, e as superfícies que serão renderizadas.(formato esperado)

E como output gera uma imagem após calcular recursivamente a incidência de raios nas superfícies.

A iluminação das superfícies é dada pelo modelo Phong, onde tempos luz ambiente, e iluminação difusão e especular, e também reflexão e (parcialmente)refração. Além disso é feito o calculo para verificar se o ponto atingido está na sombra ou não.

O que faltou ser implementado:

- Pigmentos com textura (não tive tempo de ler a textura e mapear nas superfícies).

Implementado Parcialmente (sem resultados satisfatórios):

- Superfícies com refração (Por algum motivo não funciona muito bem).

De extra, temos:

- Anti aliasing, de forma que lançamos vários raios por pixel e fazemos suas médias.
- Sombras suaves e reflexão imperfeita, baseadas numa randomização da reflexão dos raios incidentes sobre as superfícies.


## Como Compilar

É necessário ter algum compilador de c++ instalado. Então basta estar no diretório do arquivo e usar o makefile.
No caso do windows, o comando é:
```
make
```

## Execução
O executável é gerado na pasta "bin", e para usa-lo é necessário executa-lo a partir do diretório da pasta. Deve ser passado como argumento obrigatório o nome do arquivo de entrada e o nome da imagem (que será gerada na pasta "images").
Mais dois argumentos podem ser informados, que dirão qual a resolução da imagem final, caso não fornecidos o padrão é 800x600.
Então por exemplo, para um arquivo de teste na pasta "tests" fazemos:

```
bin\raytracer.exe tests\test1.in image1.ppm

## Ou para gerar uma imagem full HD
bin\raytracer.exe tests\test1.in image1.ppm 1920 1080
```

Caso esteja no windows, temos dois 3 arquivos .bat para auxiliar.

- run.bat : Que executa o primeiro teste e abre a imagem logo em seguida
- tests.bat : Que roda para todos os testes até o 8, produzindo imagens 800x600
- testesFHD.bat : Que faz o mesmo porém em full HD