Zadani:

Úkolem je naprogramovat jednoduchý HTTP server s podporou různých generátorů obsahu.
Nástroj bude implementovat:

Poskytování obsahu následujícího druhu:
- Statický obsah (konkrétní soubor).
- Výpis obsahu adresáře (pokud je v nastavení povoleno).
- Spuštění skriptu (např. sh, c, c++, ...).
- Zaslání signálu pro ukončení serveru.
- Neexistující stránka.

Server bude umožňovat:
- Získávání statických souborů pomocí metody GET.
- Ukládání statických souborů pomocí metody POST.

Nástroj bude konfigurovatelný ze souboru:
- Parametry sítě (IP adresa, port, a další).
- Omezení práce s konkrétními adresáři (konfigurace obsahuje mapování jednotlivých adresářů na adresy).
- Zaznamenávání přenosů do logu.
- Definice přípon pro zpracování pomocí skriptů.
- Adresa (případně metoda) pro vypnutí serveru.
