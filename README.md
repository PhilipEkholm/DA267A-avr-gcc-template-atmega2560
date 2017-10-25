# avr-gcc-template-atmega2560
AVR-GCC mall anpassad för ATmega2560

# Komma igång

## Installera avrdude

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

AVR-toolchain kan installeras på en del olika sätt. För macOS är det lättaste sättet igenom att installera AVR CrossPack, som inkluderar AVR-toolchain med några andra tillägg. Den finns att ladda ner här: https://obdev.at/products/crosspack/index.html

## Ubuntu/Debian-distribution:

De nödvändiga paket kan fixas via apt-get:

    $ sudo apt-get install gcc-avr binutils-avr avr-libc gdb-avr
----------

# Projektmallen

Dra ner projektet på din egen dator ifall du inte redan gjort det. Du kan antingen ladda ner det som .zip-fil eller så kan du använda dig av Git ifall du är bekant med det:

    $ git clone https://github.com/fille1116/avr-gcc-template-atmega2560.git avr-gcc-template-project

Du kan bygga projektet m.h.a. Make, som redan finns förinstallerat på din maskin. Navigera med terminalen in i projektet och sedan skriv:

    $ make

Om allting gick väl ska du få ett meddelande som säger "Project successfully built".

För att säkerställa att du har rätt variabler satta för Make så öppna filen Makefile. Följande variabler kan du hitta i toppen av filen:

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

    MMCU:=atmega2560
    MMCU_SHORT:=m2560

    COM_PORT:=/dev/tty.usbmodem1411

CC bestämmer vilken kompilator du ska använda dig av. CFLAGS är parametrar som du kan skicka in till GCC vid kompilering. Du kan sätta egna igenom att lägga till i listan. Du kan hitta en bra samling av dessa här: https://gcc.gnu.org/onlinedocs/gcc-3.0.4/gcc_3.html

Några intressanta flaggor är beskrivna här:

- std=c99: Vi använder oss av C99 standarden då den är vanligast att använda idag för C. Du kan läsa mer om den här. Huvudskillnaden är att C99 har snäppet mer strikt syntax, som reducerar risken för fel. Den introducerar bland annat stöd för boolean-datatyp såväl som inline deklaration av nya variabler i loopar.
- -Werror: Behandlar alla varningar som kompileringsfel. Du behöver inte använda detta ifall du inte vill, men det hjälper att motverka fel igenom att tvinga folk att använda korrekt syntax. En del varningar är tillåtna och kan tillåtas igenom -Wno-<varning> argument.

Den enda variabel du eventuellt behöver ändra är COM_PORT, beroende på vilken COM-port som din Arduino sitter på. Detta behövs sedan när du överför programmet via avrdude.

Ifall du uppdaterar din Makefile och sen vill bygga din firmware med de nya parametrarna måste du göra en clean:

    $ make clean

Detta kommer ta bort out-mappen som hex-filen finns lagrad. Denna mapp tas bort permanent, så det kan vara en god idé att inte lägga in egna filer i out-mappen.

Om du sedan byggt projektet och har program.hex inuti out-mappen såväl som satt upp rätt variabler i din Makefile kan du använda följande för att sända över programmet:

    $ make send

Om allting gick väl kommer det vid slutet stå "avrdude done.  Thank you.".

Om du nu kollar under tangentbordet på din Arduino ska det finnas en gul/orange lysdiod som ska blinka med en halv sekunds intervall. Om detta är fallet så grattis, du är nu redo att gå vidare med labbarna.







