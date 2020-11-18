# IZP_2
Ještě větší pičovina
## Spouštění programu
1. V pripade OS Linux: 
- **./sps [-d DELIM] CMD_SEQUENCE FILE
2. V pripade OS Windows: 
- **sps.exe [-d DELIM] CMD_SEQUENCE FILE

## Oddělovač buněk [-d DELIM]
Argument -d specifikuje, jaké znaky lze interpretovat jako oddělovače jednotlivých buněk. Každý znak ve vstupním řádku, který je obsažen v řetězci DELIM, se chová jako oddělovač dvou sousedících buněk. Ve výchozím nastavení je DELIM řetězec obsahující mezeru. Vícenásobný výskyt stejných znaků v řetězci DELIM je ignorován. První znak z řetězce DELIM bude také použit jako oddělovač výstupních hodnot. DELIM nesmí obsahovat uvozovky ani zpětné lomítko.

## Příkazy CMD_SEQUENCE
Argument CMD_SEQUENCE je jeden argument obsahující sekvenci příkazů. Více příkazů tabulkového procesoru je odděleno středníkem. Příkaz nesmí být prázdný.

## Soubor FILE
Specifikuje název souboru s tabulkou.

## Popis příkazů pro úpravu tabulky [Prikazy pro upravu tabulky]
- irow R - vlozi radek tabulky pred radek R > 0 (insert-row).
- arow - prida novy radek tabulky na konec tabulky (append-row).
- drow R - odstrani radek cislo R > 0 (delete-row).
- drows N M - odstrani radky N az M (N <= M).
V pripade N=M se prikaz chova stejne jako drow N.
- icol C - vlozi prazdny sloupec pred sloupec dany cislem C.
- acol - prida prazdny sloupec za posledni sloupec.
- dcol C - odstrani sloupec cislo C.
- dcols N M - odstrani sloupce N az M (N <= M).
V pripade N=M se prikaz chova stejne jako dcol N.

## Popis příkazů pro zpracování dat [Prikaz pro zpracovani dat]
- cset C STR - do bunky ve sloupci C bude nastaven retezec STR.
- tolower C - retezec ve sloupci C bude preveden na mala pismena.
- toupper C - retezec ve sloupce C bude preveden na velka pismena.
- round C - ve sloupci C zaokrouhli cislo na cele cislo.
- int C - odstrani desetinnou cast cisla ve sloupci C.
- copy N M - prepise obsah bunek ve sloupci M hodnotami ze sloupce N.
- swap N M - zameni hodnoty bunek ve sloupcich N a M.
- move N M - presune sloupec N pred sloupec M.

## Popis příkazů pro selekci řádků [Selekce radku]
- rows N M - procesor bude zpracovavat pouze radky N az M vcetne (N <= M).
N=1 znamena zpracovani od prvniho radku. 
Pokud je misto cisla M zadan znak - (pomlcka), 
ta reprezentuje posledni radek vstupniho souboru. 
Pokud je pomlcka take misto sloupce N, mysli se tim vyber pouze posledniho radku.
Pokud neni tento prikaz zadan, uvazuje se implicitne o vsech radcich.
- beginswith C STR - procesor bude zpracovavat pouze ty radky,
jejichz obsah bunky ve sloupci C zacina retezcem STR.
- contains C STR - procesor bude zpracovavat pouze ty radky, 
jejichz bunky ve sloupci C obsahuji retezec STR.

## Progres zpracování
### Základní operace pro načtení a výpis 
- [x] Načítání řádků
- [x] Nalezení delimu
- [ ] Kontrola zadáného vstupu na příkazové řádce
- [x] Zpracování argumentů z příkazové řádky
- [x] Výpis řádků
- [x] Rozdělení řádku do buněk
- [x] Složení buněk do řádku 

### Operace pro úpravu tabulky
- [x] irow
- [x] arow
- [x] drow 
- [x] drows
- [x] icol
- [x] acol
- [x] dcol
- [x] dcols

### Operace pro zpracování dat
- [x] cset
- [x] tolower
- [x] toupper
- [x] round
- [x] int
- [x] copy
- [x] swap
- [ ] move

### Operace pro selekci řádku
- [ ] rows
- [x] beginswith
- [x] contains
