*This project has been created as part of the 42 curriculum by aflorea*

![EU](https://img.shields.io/badge/%F0%9F%87%AA%F0%9F%87%BA-Europa-navy)
![IT](https://img.shields.io/badge/%F0%9F%87%AE%F0%9F%87%B9-Italia-green)
![RO](https://img.shields.io/badge/%F0%9F%87%B7%F0%9F%87%B4-Romania-blue)
![C](https://img.shields.io/badge/Linguaggio-C-00599C?style=flat&logo=c&logoColor=white)
![42](https://img.shields.io/badge/Scuola-42-black)
![Valgrind](https://img.shields.io/badge/Valgrind-passa-success)

# get_next_line

## Descrizione

Il progetto implementa la funzione `get_next_line` per leggere una riga alla volta da una filza.

È pensata per rispettare il limite di buffer definito da `BUFFER_SIZE` e per liberare la memoria allocata senza perdite.
Puoi verificare la presenza di eventuali perdite con Valgrind:

`valgrind --leak-check=full --show-leak-kinds=all ./a.out`

### Caratteristiche
- Gestione simultanea di piú descrittori: usa una memoria temporanea per singolo descrittore (fino a 1023).
- Supporto a _buffer_ di dimensione variabile: `BUFFER_SIZE` è ridefinibile in fase di compilazione.
- Memoria dinamica sicura: `ft_calloc`, `ft_memmove`, `ft_strjoin` sono implementate in modo sicuro e azzerano la memoria.
- Rilevamento errori: ritorna `NULL` per descrittori non validi o `BUFFER_SIZE < 1`.

## Istruzioni

### Requisiti
- GCC/Clang e ambiente POSIX (Linux, macOS o WSL/Docker su Windows).

### Compilazione rapida

Parte obbligatoria:

`cc -Wall -Wextra -Werror -pedantic -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c`

Parte bonus (piú filze contemporaneamente):

`cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c`

## Algoritmo

L'algoritmo principale è orchestrato da `ciclo_lettura`:

- Lettura incrementale: legge finché non trova `\n` o EOF.
- Memoria temporanea: conserva il residuo per la chiamata successiva.
- Costruzione riga: `ft_strjoin` concatena la parte accumulata con la porzione appena letta.
- Gestione residuo: dopo l'estrazione, `ft_memmove` porta la coda all'inizio della memoria temporanea.

Questa strategia riduce le chiamate a `read` e evita copie superflue.

## Bonus
I sorgenti con suffisso `_bonus` gestiscono piú descrittori di filze aperti contemporaneamente.

## Risorse utilizzate
- Documentazione POSIX — `read(2)`, `open(2)`
- Valgrind

## Uso dell'intelligenza artificiale
Per questo progetto l'i.a. è stata impiegata esclusivamente per:

- Generare una bozza per il `README.md` sulla base delle specifiche fornite.
- Alcuni modelli d'i.a. generativa sono stati usati per individuare dove il programma perdesse memoria, una volta scritto e normato.