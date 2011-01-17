#follow

CFLAGS	+=	-g -Wall

.PHONY: default
default: uselib
uselib: uselib.c
	$(CC) $(CPPFLAGS) $(CFLAGS) `xml2-config --cflags --libs` -o $@ $<

.PHONY: commit
	git commit -a


.PHONY: clean
clean:
	rm -f uselib
