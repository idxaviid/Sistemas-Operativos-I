find ./etext??/ -name "*.txt" -exec wc -w {} \; | sort -nk1 | echo -e "Los 10 ficheros con mayor numero palabras:\n `tail -n 10`" 
find ./etext??/ -name "*.txt" -exec wc -w {} \; | sort -nk1 | echo -e "Los 10 ficheros con menor numero palabras:\n `head -n 10`" 












