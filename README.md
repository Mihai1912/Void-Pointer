Am citit fiecare linie in parte , iar pe masura ce citeam liniile memoram in mai multe varaibile continutul fiecarei 
linii precum :
comanda , tip (dedicatiei) , dedicatorul , suma1 , suma2 , dedicatul , indexul.
Apoi in functie de comnada se intra pe cazuri specifice diecarei comenzi:

insert: se aloca memorie pentru data_struct si pentru data_struct->header , iar apoi in functie de tipul dedicatiei in 
data_struct->header se introfucea tipul dedicatiei si lungimea in bytes (pentru tipul 1 suma1 si suma2 sunt int8_t , 
tipul 2 suma1 este int16_t si suma2 este int32_t , iar pentru tip 3 suma1 si suma2 sunt int32_t) , iar la lungime 
se mai adauga 2 pentru null terminator ul fiecarui string , iar apoi se copiaza memoria din variabilele ce retin 
informatia din comanda in data_struct la pozitia potrivita. Dupa introducearea datelor in data_struct se apeleaza 
functia add_last care introduce datele din data_struct in void *arr. La inceput in dunctia add_last se calculeaza 
lungimea totala a arr ,iar apoi daca acesta este gol i se aloca memorie pentru a introducele datele din structura ,
iar daca acesta nu este gol i se realoca memorie suficienta pentru a memora datele din structura , iar la sfarsitul 
finctiei se adauga in len numarul de elemente adaugate;

insert_at: se procedeaza identic ca la insert din pct de cedere al memorarii informatiilor din comanda si din pct de 
vedere al memorarii datelor in structura , iar apoi se apeleaza functia add_at , unde de verifica daca indexul unde 
vrem sa inseram este valid , iar daca acesta este mai mare ca si numarul de dedicatii din arr se va apela functia 
add_last , daca indexul nu intra pe niciun caz prezentat mai sus aceasta functie calculeaza lungimea arr dupa 
care se parcurge pana calculeaza lungimea in bytes pana la zona in care vrem sa inseram, si se memoreaza cu un 
pointer auxiliar datele de dupa inserare. Se realoca memorie suficienta pentru a insera noua dedicatie si de 
insereaza , iar apoi se insereaza si datele retinute in poinerul auziliar , se elibereaza memoria pentru pointerul 
auxiliar si se mareste lungimea.

find: se memoreaza indexul dedicatiei pe care vrem sa o gasim , se apeleaza functia find unde se calculeaza 
lungime in bytes pana la dedicati dorita , iar apoi se afiseaza dedicatia in functie dipul acesteia.

delete: se memoreaza indexul dedicatiei pe care dorim sa o eliminam , iar apoi se apeleaza functia delete_at 
unde se calculeaza lungimea totala a arr apoi se verifica daca indexul este 0 (prima dedicatie) daca da se 
calculeaza lungime de eliminat , se memoreaza in aux ce se afla dupa prima dedicatie se copiaza apoi in 
arr ce este in aux si se realoca memorie mai putina cu lungimea de eliminat si se scade lungimea lui arr , 
daca indexul este nr dedicatii - 1 (ultima dedicatie) se calculeaza memoria din fata ultimei didicatii si se 
realoca memorie lui arr cat este inaintea ultimei dedicatii , iar daca indexul este cuprint intr-e 0 si nr 
dedicatii - 1 , se memoreaza de este dupa dedicatia de sters se suprascrie peste dedicatia de sters si 
se realoca memori mai putina ca lungime dedicatiei de sters.

print: se apeleaza functi print care printeaza dedicatiile in funcie de tipul acestora in ordinea introducerii 
in arr prin calcularea lungimii memoriei ce se afla inainte de dedicatia de printat si avanseaza in arr cu 
aceasta pentru a ajunge la dedicatia care trebui printata.