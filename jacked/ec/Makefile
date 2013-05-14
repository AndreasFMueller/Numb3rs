#
# Makefile to build the elliptic curve demo programs
#
# (c) 2013 Prof Dr Andreas Mueller, Hochschule Rapperswil
#
all:	draw

CFLAGS = -Wall -g -O2 -std=c99 -I.
CXXFLAGS = -Wall -g -O2 -I.
ec.o:	ec.cpp ec.h

draw:	draw.cpp ec.cpp

curve.pdf:	draw
	./draw curve > draw.mp
	mpost draw.mp
	mptopdf draw.1
	mv draw-1.pdf curve.pdf

operation.pdf:	draw
	./draw operation > draw.mp
	mpost draw.mp
	mptopdf draw.1
	mv draw-1.pdf operation.pdf

square.pdf:	draw
	./draw square > draw.mp
	mpost draw.mp
	mptopdf draw.1
	mv draw-1.pdf square.pdf

powers.pdf:	draw
	./draw powers > draw.mp
	mpost draw.mp
	mptopdf draw.1
	mv draw-1.pdf powers.pdf

video:	draw
	./draw video > draw.mp
	mpost draw.mp
	i=1; \
	while [ $$i -lt 1000 ]; \
	do \
		if [ -r draw.$$i ]; \
		then \
			mptopdf draw.$$i; \
			filename=`printf "video/v%05d.pdf" $$i`; \
			mv draw-$$i.pdf $$filename; \
			i=`expr $$i + 1`; \
			rm draw.$$i; \
		fi \
	done

ausschnitt.pdf:	draw
	./draw ausschnitt > draw.mp
	mpost draw.mp
	mptopdf draw.1
	mv draw-1.pdf ausschnitt.pdf
