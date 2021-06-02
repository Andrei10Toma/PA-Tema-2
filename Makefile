# Darius-Florentin Neatu <neatudarius@gmail.com>

# Exemplu de Makefile pentru tema

# tag-uri obligatorii (nume + comportament identic)
# build    => compileaza toata tema
#             (ATENTIE! E important - NU compilati in tag-urile de run. Sesizati?)
# run-p$ID => ruleaza problema cu ID-ul specificat (1, 2, 3, 4)
# clean    => sterge toate fisierele generate

# restul este la alegerea studentului
# TODO

# nume necesar (build)
build:
	# TODO
	g++ -Wall -Wextra poduri.cpp -o poduri
	g++ -Wall -Wextra adrese.cpp -o adrese
	g++ -Wall -Wextra lego.cpp -o lego
	g++ -Wall -Wextra retea.cpp -o retea

run-p1:      # nume necesar
	./poduri

run-p2:      # nume necesar
	./adrese

run-p3:      # nume necesar
	./lego

run-p4:      # nume necesar
	./retea

clean:		 # nume necesar
	rm -rf poduri
	rm -rf adrese
	rm -rf lego
	rm -rf retea

archive:
	zip 321CB_TomaAndrei_Tema2.zip Makefile README adrese.cpp lego.cpp poduri.cpp retea.cpp