# avr-gcc-template-atmega2560
AVR-GCC mall anpassad för ATmega2560

# Komma igång

## Installera avrdude

Titeln är inget skämt, härnäst så ska avrdude installeras.

I det normala fallet när man ska överföra det kompilerade programmet från sin dator till mikrokontrollern behöver man en programmerare för detta. Då dessa kostar lite mer och är pillriga att jobba med använder vi en annan strategi utöver det normala för att överföra program. Vi använder oss av en bootloader.

En bootloader är ett program som sitter förprogrammerad i minnet på vår mikrokontroller vars uppgift är att ladda in programvaran som vi skickar över. För att få över programvaran använder vi seriell-kommunikation (via USB) för att skicka över programmet. Bootloadern kommunicerar med just avrdude så vi måste ha det programmet för att hantera överföringen.

avrdude för macOS

För att installera avrdude använder vi oss av Homebrew som tidigare:

    $ brew install avrdude --with-usb

“—with-usb” argumentet är väldigt viktigt.

avrdude för debian-distribution

För Ubuntu/debian distribution kan APT likt tidigare användas:


    $ sudo apt-get install avrdude

—with-usb argumentet behövs ej till skillnad från installation via brew.

---

Kontrollera sedan att avrdude har installerats korrekt:

    $ avrdude --version

---

# Installera AVR-GCC toolchain

Huvudsakligen är detta AVR-GCC, nämligen en utökning av GCC (vanligt förekommande kompilator för C) gjord av Atmel. Denna finns för macOS/Linux så ingen emulering krävs till skillnad från Assembler senare.

## macOS

AVR-toolchain kan installeras på en del olika sätt. För macOS är det lättaste sättet igenom att installera AVR CrossPack, som inkluderar AVR-toolchain med några andra tillägg. Den finns att ladda ner här.

## Ubuntu/Debian-distribution:

De nödvändiga paket kan fixas via apt-get:

    $ sudo apt-get install gcc-avr binutils-avr avr-libc gdb-avr
----------

Efter att du säkerställt att AVR-toolchain är korrekt installerat är stegen ganska lika från assembler, med några fåtal undantag.

För C-programmering finns en annan mall, som man kan komma åt härifrån. Du kan ladda ner som ZIP tidigare eller forka med Git ifall du är insatt med det.

Ta sedan och öppna projektmallen. Det mesta ser sig likt ut med app-directory för själva källkoden. Kommandona för make är likadana. Däremot ligger skillnaden i Makefile. Ta och öppna upp denna.

C har lite fler parametrar som man kan jobba med. Likt tidigare ska vi kolla igenom variablerna för filen, dessa lyder:

    CC:=avr-gcc

    CFLAGS+= \
            -std=c99 -g \
            -ffunction-sections \
            -fdata-sections \
            -fno-strict-aliasing \
            -Wunused-function \
            -Werror \
            -I. \
            -I./app \

    TARGET:=app/main.c

    MMCU:=atmega32u4
    MMCU_SHORT:=m32u4

    COM_PORT:=/dev/tty.usbmodem1411

CC är då kompilatorn vi ska använda, mer bestämt AVR-GCC. TARGET är densamma förutom att C-källkod skrivs i .c filer. MMCU och MMCU_SHORT är densamma. Eventuellt måste du ändra COM_PORT som tidigare nämnt för Assembler.

Däremot är CFLAGS ny. CFLAGS tillåter en att mata in flera argument till kompilatorn med diverse bruk. De viktigaste är:

- std=c99: Vi använder oss av C99 standarden då den är vanligast att använda idag för C. Du kan läsa mer om den här. Huvudskillnaden är att C99 har snäppet mer strikt syntax, som reducerar risken för fel. Den introducerar bland annat stöd för boolean-datatyp såväl som inline deklaration av nya variabler i loopar.
- -Werror: Behandlar alla varningar som kompileringsfel. Du behöver inte använda detta ifall du inte vill, men det hjälper att motverka fel igenom att tvinga folk att använda korrekt syntax. En del varningar är tillåtna och kan tillåtas igenom -Wno-<varning> argument.

För övrigt ska det inte skilja sig mer med denna Makefile. Navigera till mallen med terminalen och skriv:

    $ make

Förhoppningsvis ska även här stå “Successfully built project” i terminalen. Annars finns där någonting fel. Felet bör i så fall visas i terminalen.

Annars så grattis på att ha kommit så här långt! Där bör finnas en out-mapp nu där det ligger lite diverse byggfiler, bland annat objekt-filen, elf-fil och sist men inte minst hexfilen. Denna fil fungerar precis som innan för assembler. Allt som behövs för att flasha med den är korrekt satt COM-port och Arduino ansluten förhoppningsvis. Testa detta nu:

    $ make send

Nu ska lysdioden blinka med ca. en halv millisekunds intervall.

